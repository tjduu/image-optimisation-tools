/*
 * Group: Ziggurat
 *
 * Members:
 * - Xiaoye Zhang (GitHub: acse-xz4019)
 * - Melissa Sim (GitHub: acse-mys20)
 * - Wenhao Hong (GitHub: acse-wh623)
 * - Javonne Porter (GitHub: acse-jp2923)
 * - Tianju (Tim) Du (GitHub: edsml-td323)
 * - Wenxin Li (GitHub: edsml-wl123)
 */

#include <iostream>
#include <cmath>
#include <algorithm>
#include "Filter.h"
#include "Projection.h"

using namespace std;

// Helper functions to convert Image to vector and vice versa
std::vector<std::vector<unsigned char>> Filter::ConvertImageToVector(const Image& image) {
    int width = image.getWidth();
    int height = image.getHeight();

    std::vector<std::vector<unsigned char>> result(height, std::vector<unsigned char>(width));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Assuming the image is grayscale, so only the first channel is needed
            unsigned char pixelValue = image.getPixel(x, y, 0);
            result[y][x] = pixelValue;
        }
    }

    return result;
}

// Helper function to convert a 2D gradient vector to an Image
Image Filter::convertGradientToImage(const std::vector<std::vector<unsigned char>>& gradient, int width, int height) {
    Image resultImage(width, height, 1);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            resultImage.setPixel(x, y, 0, gradient[y][x]);
        }
    }

    return resultImage;
}

// Helper function to generate a Gaussian distribution value
float Filter::gaussian(float x, float y, float z, float sigma) {
    return std::exp(-(x * x + y * y + z * z) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
}


// Function to apply a median filter to an image
Image Filter::medianBlur(Image& image, int kernel_size) {
    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();
    int bufferSize = kernel_size * kernel_size;

    // Create a copy of the image to store the filtered result
    Image filteredImage = image;

    // Calculate the radius of the kernel
    int radius = kernel_size / 2;
    // Calculate half size of the kernel area for median index
    int median_index = (kernel_size * kernel_size) / 2;

    // Vector to hold pixel values from the kernel area
//    std::vector<unsigned char> window;                             // old
    auto* window = new unsigned char[kernel_size * kernel_size];     // new

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int k = 0; k < channels; ++k) {
//                window.clear();                                    //old

                // Collect pixel values from the kernel area
                for (int iy = -radius; iy <= radius; ++iy) {
                    for (int ix = -radius; ix <= radius; ++ix) {
                        int readX = std::min(std::max(x + ix, 0), width - 1);
                        int readY = std::min(std::max(y + iy, 0), height - 1);
//                        window.push_back(image.getPixel(readX, readY, k));                                        //old
                        window[(iy + radius) * kernel_size + (ix + radius)] = image.getPixel(readX, readY, k);        //new
                    }
                }

                // Sort the pixel values to find the median
                Projection::quickSort(window, 0, bufferSize - 1);                                                    //new
//                std::nth_element(window.begin(), window.begin() + median_index, window.end());                     //old

                unsigned char median_value;

//                //Handle even-sized kernel by averaging two middle values
//                if (kernel_size % 2 == 0) {
//                    // Find the second median value
//                    std::nth_element(window.begin(), window.begin() + median_index - 1, window.end());
//                    // Calculate the average of the two median values
//                    median_value = (window[median_index] + window[median_index - 1]) / 2;
//                } else {
//                    // For an odd-sized kernel, take the median value
//                    median_value = window[median_index];
//                }
                // Check if the number of elements is even or odd
                if (bufferSize % 2 == 0) {                                                                        //new version
                    median_value = (window[bufferSize / 2 - 1] + window[bufferSize / 2]) / 2;                    //new version
                } else {                                                                                          //new version
                    median_value = window[bufferSize / 2];                                                        //new version
                }                                                                                                 //new version
                
                // Set the median value to the corresponding pixel on the filtered image
                filteredImage.setPixel(x, y, k, median_value);
            }
        }
    }

    // Copy the filtered data back to the original image
    return filteredImage;// assuming operator= is properly defined
}

Image Filter::histomedianBlur(Image& image, int kernel_size) {
    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();

    Image filteredImage = image; // Assuming there's a copy constructor

    int radius = kernel_size / 2;
    std::vector<int> histogram(256, 0); // Histogram for counting sort

    for (int k = 0; k < channels; ++k) {
        for (int y = 0; y < height; ++y) {
            histogram.assign(256, 0); // Reset the histogram for each row

            // Initialize histogram for the first window in this row
            for (int iy = -radius; iy <= radius; ++iy) {
                for (int ix = -radius; ix <= radius; ++ix) {
                    int readX = std::max(ix, 0);
                    int readY = std::max(y + iy, 0);
                    readX = std::min(readX, width - 1);
                    readY = std::min(readY, height - 1);
                    unsigned char pixelValue = image.getPixel(readX, readY, k);
                    histogram[pixelValue]++;
                }
            }

            // Find the median for the first window
            int median = Filter::findMedianHist(histogram, kernel_size * kernel_size);
            filteredImage.setPixel(0, y, k, median);

            for (int x = 1; x < width; ++x) {
                // Subtract pixel counts for the outgoing column
                for (int iy = -radius; iy <= radius; ++iy) {
                    int colOutX = std::max(x - radius - 1, 0);
                    int colOutY = std::min(std::max(y + iy, 0), height - 1);
                    unsigned char outgoingPixel = image.getPixel(colOutX, colOutY, k);
                    histogram[outgoingPixel]--;
                }

                // Add pixel counts for the incoming column
                for (int iy = -radius; iy <= radius; ++iy) {
                    int colInX = std::min(x + radius, width - 1);
                    int colInY = std::min(std::max(y + iy, 0), height - 1);
                    unsigned char incomingPixel = image.getPixel(colInX, colInY, k);
                    histogram[incomingPixel]++;
                }

                // Find the median for the current window
                median = Filter::findMedianHist(histogram, kernel_size * kernel_size);
                filteredImage.setPixel(x, y, k, median);
            }
        }
    }
    return filteredImage; // Assuming operator= is properly defined
}

// Function to apply a box blur to an image
Image Filter::boxBlur(Image &image, int kernel_size) {
    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();

    // Create a temporary image to store the intermediate results
    Image tempImage(width, height, channels);
    // Create the result image to store the final results
    Image resultImage(width, height, channels);

    // Calculate the radius of the kernel
    int radius = kernel_size / 2;
    bool isKernelEven = kernel_size % 2 == 0;

    // Horizontal pass
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int k = 0; k < channels; ++k) {
                unsigned int sum = 0;
                int count = 0;

                for (int ix = -radius; ix <= radius + (isKernelEven ? 1 : 0); ++ix) {
                    int currentX = std::min(std::max(x + ix, 0), width - 1);
                    sum += image.getPixel(currentX, y, k);
                    count++;
                }

                tempImage.setPixel(x, y, k, static_cast<unsigned char>(sum / count));
            }
        }
    }

    // Vertical pass
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int k = 0; k < channels; ++k) {
                unsigned int sum = 0;
                int count = 0;

                for (int iy = -radius; iy <= radius + (isKernelEven ? 1 : 0); ++iy) {
                    int currentY = std::min(std::max(y + iy, 0), height - 1);
                    sum += tempImage.getPixel(x, currentY, k);
                    count++;
                }

                // The result should be stored in resultImage, not the original image
                resultImage.setPixel(x, y, k, static_cast<unsigned char>(sum / count));
            }
        }
    }

    // Return the result image containing the blurred image data
    return resultImage;
}

// Function to apply Gaussian blur to an image
Image Filter::gaussianBlur(Image& image, int kernelSize, float sigma) {
        if (kernelSize % 2 == 0) {
            throw std::invalid_argument("Kernel size must be odd");
        }

        int width = image.getWidth();
        int height = image.getHeight();
        int channels = image.getChannels();
        int radius = kernelSize / 2;
        std::vector<float> kernel(kernelSize * kernelSize);
        float sum = 0.0f; // For normalizing the kernel
        
        Image resultImage(width, height, channels);
        // Create Gaussian kernel
        for (int i = 0; i < kernelSize; ++i) {
            for (int j = 0; j < kernelSize; ++j) {
                int x = i - radius;
                int y = j - radius;
                float exponent = -(x * x + y * y) / (2.0f * sigma * sigma);
                kernel[i * kernelSize + j] = std::exp(exponent) / (2.0f * M_PI * sigma * sigma);
                sum += kernel[i * kernelSize + j];
            }
        }

        // Normalize the kernel
        for (float &value : kernel) {
            value /= sum;
        }

        // Apply Gaussian blur
        Image tempImage(width, height, channels); // Create a temporary image for the output
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int c = 0; c < channels; ++c) {
                    float blurredPixel = 0.0f;

                    for (int ky = -radius; ky <= radius; ++ky) {
                        for (int kx = -radius; kx <= radius; ++kx) {
                            int pixelPosX = std::clamp(x + kx, 0, width - 1);
                            int pixelPosY = std::clamp(y + ky, 0, height - 1);
                            blurredPixel += image.getPixel(pixelPosX, pixelPosY, c) * kernel[(ky + radius) * kernelSize + (kx + radius)];
                        }
                    }

                    tempImage.setPixel(x, y, c, static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, blurredPixel))));
                }
            }
        }

        // Copy the blurred tempImage data back to the original image
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int c = 0; c < channels; ++c) {
                    resultImage.setPixel(x, y, c, tempImage.getPixel(x, y, c));
                }
            }
        }
       return resultImage;
    }

// Function to convert RGB images to grayscale
Image Filter::grayScale(Image &inputImg) {
    // Check if the image is already grayscale
    if (inputImg.getChannels() == 1)
    {
        return inputImg;
    }

    // Check if the image has 1, 3, or 4 channels
    else if (inputImg.getChannels() != 3 && inputImg.getChannels() != 4)
    {
        throw std::invalid_argument("Image must have 1, 3, or 4 channels to be converted to grayscale");
    }

    int width = inputImg.getWidth();
    int height = inputImg.getHeight();

    // Create a new Image object to store the grayscale image
    Image outputImg = Image(width, height, 1);

    // For each pixel in the image, calculate the grayscale value
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            unsigned char r = inputImg.getPixel(x, y, 0);
            unsigned char g = inputImg.getPixel(x, y, 1);
            unsigned char b = inputImg.getPixel(x, y, 2);

            auto gray = static_cast<unsigned char>(0.2126 * r + 0.7152 * g + 0.0722 * b);

            // Set grayscale value for the pixel
            outputImg.setPixel(x, y, 0, gray);
        }
    }
    return outputImg;
}

// Function to apply a brightness adjustment to an image
Image Filter::setBrightness(Image &inputImg, int value, bool autoBrightness)
{
    int width = inputImg.getWidth();
    int height = inputImg.getHeight();
    int channels = inputImg.getChannels();

    Image outputImg = Image(width, height, channels);

    int totalIntensity = 0;
    int totalPixels = width * height * channels;

    // Check if autoBrightness is true
    if (autoBrightness)
    {
        // Set value to 0, to be calculated later
        value = 0;
    }

    // Check if the brightness value is within the valid range
    if (value < -255 || value > 255)
    {
        throw std::invalid_argument("Brightness value must be in the range [-255, 255]");
    }

    // Apply the brightness adjustment to each pixel
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            for (int c = 0; c < channels; ++c)
            {
                int allPixels = inputImg.getPixel(x, y, c);

                // If autobrightness is true, calculate the total intensity
                if (autoBrightness){
                    totalIntensity += allPixels;
                }

                else {
                    // Add the brightness value to the pixel intensity
                    int newValue = allPixels + value;
                    newValue = std::max(0, std::min(newValue, 255));
                    outputImg.setPixel(x, y, c, newValue);
                }
            }
        }
    }

    if (autoBrightness){
        // Calculate the average intensity
        int averageIntensity = totalIntensity / totalPixels;
        // Set the brightness to make the average intensity 128
        value = 128 - averageIntensity;
        return setBrightness(inputImg, value, false);
    } 

    return outputImg;
}

// Function to convert RGB images to HSL
Image Filter::RGBtoHSL(Image &image) {
    int width = image.getWidth();
    int height = image.getHeight();
    // int channels = image.getChannels();

    Image outputImg = Image(width, height, 3);

    // Iterate through each pixel in the image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Get the RGB values of the pixel
            double r = image.getPixel(x, y, 0) / 255.0;
            double g = image.getPixel(x, y, 1) / 255.0;
            double b = image.getPixel(x, y, 2) / 255.0;

            double max = std::max({r, g, b});
            double min = std::min({r, g, b});
            double delta = max - min;

            double h, s, l;

            // Calculate lightness
            l = (max + min) / 2.0;

            // Calculate saturation
            if (delta == 0) {
                s = 0;
            } else {
                s = delta / (1 - std::abs(2 * l - 1));
            }

            // Calculate hue
            if (delta == 0) {
                h = 0;
            } else {
                if (max == r) {
                    h = 60 * std::fmod((g - b) / delta, 6);
                } else if (max == g) {
                    h = 60 * ((b - r) / delta + 2);
                } else {
                    h = 60 * ((r - g) / delta + 4);
                }
            }

            // Set the HSL values for the pixel
            outputImg.setPixel(x, y, 0, h/360 *255);
            outputImg.setPixel(x, y, 1, s* 255);
            outputImg.setPixel(x, y, 2, l*255);
        }
    }
    return outputImg;
}

// Function to convert HSL images to RGB
Image Filter::HSLtoRGB(Image &inputImg){
    int width = inputImg.getWidth();
    int height = inputImg.getHeight();
    // int channels = inputImg.getChannels();

    Image outputImg = Image(width, height, 3);

    // Iterate through each pixel in the image
    for (int y = 0; y < height; ++y){
        for (int x = 0; x < width; ++x){
            // Get the HSL values of the pixel
            // Note capitalised variables to not confuse between
            // x, position and X utilised
            // for the HSL to RGB conversion
            double H = inputImg.getPixel(x, y, 0) / 255.0 * 360;
            double S = inputImg.getPixel(x, y, 1) / 255.0;
            double L = inputImg.getPixel(x, y, 2) / 255.0;

            double C = (1 - std::abs(2 * L - 1)) * S;
            double X = C * (1 - std::abs(std::fmod(H / 60, 2) - 1));
            double M = L - C / 2;

            double R, G, B;

            // Calculate RGB values
            if (H >= 0 && H < 60) {
                R = C;
                G = X;
                B = 0;
            } else if (H >= 60 && H < 120) {
                R = X;
                G = C;
                B = 0;
            } else if (H >= 120 && H < 180) {
                R = 0;
                G = C;
                B = X;
            } else if (H >= 180 && H < 240) {
                R = 0;
                G = X;
                B = C;
            } else if (H >= 240 && H < 300) {
                R = X;
                G = 0;
                B = C;
            } else {
                R = C;
                G = 0;
                B = X;
            }

            // Set the RGB values for the pixel
            outputImg.setPixel(x, y, 0, (R + M) * 255);
            outputImg.setPixel(x, y, 1, (G + M) * 255);
            outputImg.setPixel(x, y, 2, (B + M) * 255);

        }
    }

    return outputImg;
}

// Function to apply histogram equalization to an image
Image Filter::histogramEqualization(Image &inputImg, const bool &isHSV){
    int width = inputImg.getWidth();
    int height = inputImg.getHeight();
    int channels = inputImg.getChannels();

    // Create new output image
    Image outputImg = Image(width, height, channels);

    // Check if 1, 3, or 4 channels
    if (channels == 3 || channels == 4){
        // Check if to convert to HSV or HSL
        if (isHSV){
            Image hsvImg = rgb_to_hsv(inputImg);
            // Perform histogram equalization on the lightness channel (L)
            Image equalisedImg = calculateHistogramEqualization(hsvImg, 2);
            // Convert back from HSL to RGB
            outputImg = hsv_to_rgb(equalisedImg);
        }
        else{
            // transform RGB to HSL
            Image hslImg = RGBtoHSL(inputImg);
            // Perform histogram equalization on the lightness channel (L)
            Image equalisedImg = calculateHistogramEqualization(hslImg, 2);
            // Convert back from HSL to RGB
            outputImg = HSLtoRGB(equalisedImg);
        }
    }

    else if (channels == 1){
        // Perform histogram equalization on the single channel
        outputImg = calculateHistogramEqualization(inputImg, 0);
    }

        // If the image has an invalid number of channels
    else{
        throw std::invalid_argument("Image must have 1, 3, or 4 channels to be converted to grayscale");
    }

    return outputImg;

}

Image Filter::calculateHistogramEqualization(Image &inputImg, int channelIndex) {
    int width = inputImg.getWidth();
    int height = inputImg.getHeight();
    int channels = inputImg.getChannels();

    Image outputImg = Image(width, height, channels);

    // Initialize histogram array
    int histogram[256] = {0};
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int intensity = inputImg.getPixel(x, y, channelIndex);
            histogram[intensity]++;
        }
    }

    // Calculate CDF
    int cdf[256] = {0};
    cdf[0] = histogram[0];
    for (int i = 1; i < 256; ++i) {
        cdf[i] = cdf[i-1] + histogram[i];
    }

    // Find the minimum CDF value (remove 0 values)
    int minCDF = cdf[0];
    for (int i = 1; i < 256; ++i) {
        if (cdf[i] != 0) {
            minCDF = cdf[i];
            break;
        }
    }

    // Find the minimum and maximum intensity values
    int newValues[256];
    for (int i = 0; i < 256; ++i) {
        newValues[i] = static_cast<int>(255.0 * (cdf[i] - minCDF) / (width * height - minCDF));
    }

    // Apply histogram equalization to the specified channel
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (channels > 1) {
                // Preserve other channels' values
                for (int c = 0; c < channels; ++c) {
                    if (c != channelIndex) {
                        outputImg.setPixel(x, y, c, inputImg.getPixel(x, y, c));
                    }
                }
            }
            int originalIntensity = inputImg.getPixel(x, y, channelIndex);
            int adjustedIntensity = newValues[originalIntensity];
            outputImg.setPixel(x, y, channelIndex, adjustedIntensity);
        }
    }

    return outputImg;
}

// Function to apply salt and pepper noise to an image
Image Filter::salt_and_pepper(Image image, const double &proportion, const bool &rgb) {
    int w = image.getWidth();
    int h = image.getHeight();
    int c = image.getChannels();
    srand(static_cast<unsigned int>(time(0)));
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (random_number() < proportion) {
                // Randomly set the pixel to either 0 or 255
                unsigned char color = random_number() < 0.5 ? 0 : 255;
                if (rgb) {
                    // Apply noise to all channels
                    for (int channel = 0; channel < c; ++channel) {
                        image.setPixel(x, y, channel, color);
                    }
                } else {
                    image.setPixel(x, y, 0, color); // Assuming grayscale affects only the first channel
                }
            }
        }
    }
    return image;
}

// Function to apply a threshold to an image
Image Filter::threshold(Image& image, const double &thresholdValue, const bool &rgb, bool isHSV) {
    int width = image.getWidth();
    int height = image.getHeight();
    Image resultImage(width, height, 1); // Output is a single-channel image for thresholded results.

    if (!rgb) {
        // Grayscale thresholding
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                unsigned char pixelValue = image.getPixel(x, y, 0);
                unsigned char newValue = (pixelValue >= thresholdValue) ? 255 : 0;
                resultImage.setPixel(x, y, 0, newValue);
            }
        }
    } else {
        // Convert the entire RGB image to HSV or HSL once before thresholding
        Image convertedImage = isHSV ? rgb_to_hsv(image) : RGBtoHSL(image);

        // Apply thresholding based on the V/L channel
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                unsigned char channelValue = convertedImage.getPixel(x, y, 2); // Use V/L channel
                unsigned char newValue = (channelValue >= thresholdValue) ? 255 : 0;
                resultImage.setPixel(x, y, 0, newValue); // Set pixel in the result image
            }
        }
    }

    return resultImage;
}

// Function to generate a random number between 0 and 1
double Filter::random_number(){
    double random = (double) rand() / RAND_MAX;
    return random;
}

// Function to convert RGB images to HSV
Image Filter::rgb_to_hsv(Image& image) {
    int width = image.getWidth();
    int height = image.getHeight();
    int channels = image.getChannels();

    // Assuming the input image is in RGB format
    if (channels < 3) {
        throw std::runtime_error("rgb_to_hsv requires an image with at least 3 channels (RGB).");
    }

    // Create a new image to store the HSV values, maintaining the input image dimensions but forcing 3 channels
    Image hsvImage(width, height, 3);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float r = image.getPixel(x, y, 0) / 255.0f;
            float g = image.getPixel(x, y, 1) / 255.0f;
            float b = image.getPixel(x, y, 2) / 255.0f;

            float max = std::max({r, g, b});
            float min = std::min({r, g, b});
            float delta = max - min;

            float h, s, v;
            v = max;

            if (delta < 0.00001f) {
                s = 0;
                h = 0; // Undefined, maybe nan?
            } else {
                s = (max > 0.0f) ? (delta / max) : 0.0f;

                if (r >= max) {
                    h = (g - b) / delta; // Between yellow & magenta
                } else if (g >= max) {
                    h = 2.0f + (b - r) / delta; // Between cyan & yellow
                } else {
                    h = 4.0f + (r - g) / delta; // Between magenta & cyan
                }

                h *= 60.0f; // Convert to degrees

                if (h < 0.0f) {
                    h += 360.0f;
                }
            }

            hsvImage.setPixel(x, y, 0, static_cast<unsigned char>((h / 360.0f) * 255)); // H: 0-360 degrees -> scaled to 0-255
            hsvImage.setPixel(x, y, 1, static_cast<unsigned char>(s * 255)); // S: 0-1 -> scaled to 0-255
            hsvImage.setPixel(x, y, 2, static_cast<unsigned char>(v * 255)); // V: 0-1 -> scaled to 0-255
        }
    }

    return hsvImage;
}

// Function to convert HSV images to RGB
Image Filter::hsv_to_rgb(const Image& hsvImage) {
    int width = hsvImage.getWidth();
    int height = hsvImage.getHeight();
    // Assuming the output RGB image will have 3 channels.
    Image rgbImage(width, height, 3);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float h = hsvImage.getPixel(x, y, 0) * (360.0f / 255.0f); // Rescale to 0-360
            float s = hsvImage.getPixel(x, y, 1) / 255.0f; // Scale to 0-1
            float v = hsvImage.getPixel(x, y, 2) / 255.0f; // Scale to 0-1

            float c = v * s; // Chroma
            float xVal = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
            float m = v - c;

            float rPrime, gPrime, bPrime;

            if (h >= 0 && h < 60) {
                rPrime = c;
                gPrime = xVal;
                bPrime = 0;
            } else if (h >= 60 && h < 120) {
                rPrime = xVal;
                gPrime = c;
                bPrime = 0;
            } else if (h >= 120 && h < 180) {
                rPrime = 0;
                gPrime = c;
                bPrime = xVal;
            } else if (h >= 180 && h < 240) {
                rPrime = 0;
                gPrime = xVal;
                bPrime = c;
            } else if (h >= 240 && h < 300) {
                rPrime = xVal;
                gPrime = 0;
                bPrime = c;
            } else {
                rPrime = c;
                gPrime = 0;
                bPrime = xVal;
            }

            // Convert to RGB format
            auto r = static_cast<unsigned char>((rPrime + m) * 255);
            auto g = static_cast<unsigned char>((gPrime + m) * 255);
            auto b = static_cast<unsigned char>((bPrime + m) * 255);

            // Set RGB pixel values
            rgbImage.setPixel(x, y, 0, r);
            rgbImage.setPixel(x, y, 1, g);
            rgbImage.setPixel(x, y, 2, b);
        }
    }

    return rgbImage;
}

// Helper function to apply an edge operator to an image
Image Filter::applyEdgeOperator(Image& image, const int kernelX[3][3], const int kernelY[3][3]) {
    auto imageVector = ConvertImageToVector(image);
    int width = image.getWidth();
    int height = image.getHeight();
    std::vector<std::vector<unsigned char>> gradient(height, std::vector<unsigned char>(width, 0));

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int sumX = 0, sumY = 0;
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    sumX += imageVector[y + ky][x + kx] * kernelX[ky + 1][kx + 1];
                    sumY += imageVector[y + ky][x + kx] * kernelY[ky + 1][kx + 1];
                }
            }
            int magnitude = std::sqrt(sumX * sumX + sumY * sumY);
            magnitude = std::min(255, std::max(0, magnitude));
            gradient[y][x] = static_cast<unsigned char>(magnitude);
        }
    }

    return convertGradientToImage(gradient, width, height);
}

// Function to apply the Sobel operator edge detection to an image
Image Filter::applySobelOperator(Image& image) {
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    return applyEdgeOperator(image, Gx, Gy);
}

// Function to apply the Prewitt operator edge detection to an image
Image Filter::applyPrewittOperator(Image& image) {
    int Gx[3][3] = {{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}};

    return applyEdgeOperator(image, Gx, Gy);
}

// Function to apply the Scharr operator edge detection to an image
Image Filter::applyScharrOperator(Image& image) {
    int Gx[3][3] = {{-3, 0, 3}, {-10, 0, 10}, {-3, 0, 3}};
    int Gy[3][3] = {{-3, -10, -3}, {0, 0, 0}, {3, 10, 3}};

    return applyEdgeOperator(image, Gx, Gy);
}

// Function to apply the Roberts Cross operator edge detection to an image
Image Filter::applyRobertsCrossOperator(Image& image) {
    int Gx[4] = {1, 0, 0, -1};
    int Gy[4] = {0, 1, -1, 0};
    int width = image.getWidth();
    int height = image.getHeight();
    Image resultImage(width, height, 1);

    for (int y = 0; y < height - 1; ++y) {
        for (int x = 0; x < width - 1; ++x) {
            // Applying Gx
            int pixelValue00 = image.getPixel(x, y, 0);
            int pixelValue11 = image.getPixel(x + 1, y + 1, 0);
            int sumX = pixelValue00 - pixelValue11;

            // Applying Gy
            int pixelValue01 = image.getPixel(x, y + 1, 0);
            int pixelValue10 = image.getPixel(x + 1, y, 0);
            int sumY = pixelValue01 - pixelValue10;

            // Compute gradient
            int magnitude = std::min(255, std::max(0, static_cast<int>(std::sqrt(sumX * sumX + sumY * sumY))));
            resultImage.setPixel(x, y, 0, magnitude);
        }
    }

    // Handle the last row and column
    for (int y = 0; y < height; ++y)
        resultImage.setPixel(width - 1, y, 0, 0);
    for (int x = 0; x < width; ++x)
        resultImage.setPixel(x, height - 1, 0, 0);

    return resultImage;
}

// Create a 3D Gaussian kernel
std::vector<std::vector<std::vector<float>>> Filter::create3DKernel(int kernelSize, float sigma) {
    std::vector<std::vector<std::vector<float>>> kernel(kernelSize, std::vector<std::vector<float>>(kernelSize, std::vector<float>(kernelSize)));
    int halfSize = kernelSize / 2;
    float sum = 0.0f; // For normalization

    // Create the 3D kernel
    for (int x = -halfSize; x <= halfSize; ++x) {
        for (int y = -halfSize; y <= halfSize; ++y) {
            for (int z = -halfSize; z <= halfSize; ++z) {
                kernel[x + halfSize][y + halfSize][z + halfSize] = gaussian(x, y, z, sigma);
                sum += kernel[x + halfSize][y + halfSize][z + halfSize];
            }
        }
    }

    // Normalize the kernel
    for (int x = 0; x < kernelSize; ++x) {
        for (int y = 0; y < kernelSize; ++y) {
            for (int z = 0; z < kernelSize; ++z) {
                kernel[x][y][z] /= sum;
            }
        }
    }

    return kernel;
}

void Filter::apply3DGaussianBlur(Volume& volume, int kernelSize, float sigma) {
    auto kernel = create3DKernel(kernelSize, sigma);
    int width = volume.getWidth();
    int height = volume.getHeight();
    int depth = volume.getDepth();

    // Temporary volume to store the blurred data
    Volume tempVolume(volume);

    for (int z = 0; z < depth; ++z) {
        std::cout << "Blurring Depth: " << z + 1 << " / " << depth << std::endl;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                std::vector<float> newValue(volume.getChannels(), 0.0f);

                for (int kz = -kernelSize/2; kz <= kernelSize/2; ++kz) {
                    for (int ky = -kernelSize/2; ky <= kernelSize/2; ++ky) {
                        for (int kx = -kernelSize/2; kx <= kernelSize/2; ++kx) {
                            int sz = std::clamp(z + kz, 0, depth - 1);
                            int sy = std::clamp(y + ky, 0, height - 1);
                            int sx = std::clamp(x + kx, 0, width - 1);

                            for (int channel = 0; channel < volume.getChannels(); ++channel) {
                                unsigned char voxelValue = volume.getVoxel(sx, sy, sz, channel);
                                newValue[channel] += voxelValue * kernel[kz + kernelSize/2][ky + kernelSize/2][kx + kernelSize/2];
                            }
                        }
                    }
                }

                for (int channel = 0; channel < volume.getChannels(); ++channel) {
                    tempVolume.setVoxel(x, y, z, channel, static_cast<unsigned char>(std::min(std::max(static_cast<int>(newValue[channel]), 0), 255)));
                }
            }
        }
    }

    volume = std::move(tempVolume);
}

void Filter::apply3DMedianFilter(Volume& volume, int kernelSize) {
    if (kernelSize % 2 == 0) {
        throw std::invalid_argument("Kernel size must be odd.");
    }

    int width = volume.getWidth();
    int height = volume.getHeight();
    int depth = volume.getDepth();
    int channels = volume.getChannels();
    int offset = kernelSize / 2;
    int bufferSize = kernelSize * kernelSize * kernelSize;

    Volume tempVolume(volume);

    for (int z = 0; z < depth; ++z) {
        std::cout << "Applying Median Filter at Depth: " << z + 1 << " / " << depth << std::endl;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int channel = 0; channel < channels; ++channel) {
                    auto* neighborhood = new unsigned char[bufferSize];                                        //new version
//                    std::vector<unsigned char> neighborhood;                                                                      //old version

                    for (int kz = -offset; kz <= offset; ++kz) {
                        for (int ky = -offset; ky <= offset; ++ky) {
                            for (int kx = -offset; kx <= offset; ++kx) {
                                int nz = std::clamp(z + kz, 0, depth - 1);
                                int ny = std::clamp(y + ky, 0, height - 1);
                                int nx = std::clamp(x + kx, 0, width - 1);

                                neighborhood[(kz + offset) * kernelSize * kernelSize + (ky + offset) * kernelSize + (kx + offset)] = volume.getVoxel(nx, ny, nz, channel);    //new version
//                                neighborhood.push_back(volume.getVoxel(nx, ny, nz, channel));                                    //old version
                            }
                        }
                    }

//                    std::nth_element(neighborhood.begin(), neighborhood.begin() + neighborhood.size() / 2, neighborhood.end());    //old version
                    // Sort the neighborhood using Projection::quickSort
                    Projection::quickSort(neighborhood, 0, bufferSize - 1);                                  //new version

                    // Find the median intensity value
                    unsigned char median;                                                                   //new version
                    // Check if the number of elements is even or odd
                    if (bufferSize % 2 == 0) {                                                             //new version
                        median = (neighborhood[bufferSize / 2 - 1] + neighborhood[bufferSize / 2]) / 2;    //new version
                    } else {                                                                                //new version
                        median = neighborhood[bufferSize / 2];                                             //new version
                    }                                                                                        //new version

//                    unsigned char median = neighborhood[neighborhood.size() / 2];//old version
                    tempVolume.setVoxel(x, y, z, channel, median);
                }
            }
        }
    }

    volume = std::move(tempVolume);
}

int Filter::findMedianHist(const std::vector<int>& histogram, int windowSize) {
    int count = 0;
    int medianIndex = (windowSize - 1) / 2; // For a zero-based index array
    for (int i = 0; i < histogram.size(); i++) {
        count += histogram[i];
        if (count > medianIndex) {
            return i; // The median value
        }
    }
    return -1; // Error case, should not happen if histogram is correctly filled
}

int Filter::findMedianHist3D(const std::vector<int>& histogram, int windowSize) {
    int count = 0;
    int medianIndex = (windowSize - 1) / 2; // For a zero-based index array
    for (size_t i = 0; i < histogram.size(); i++) {
        count += histogram[i];
        if (count > medianIndex) {
            return static_cast<int>(i); // The median value
        }
    }
    return -1; // Error case, should not happen if histogram is correctly filled
}

void Filter::volumeMedianFilter(Volume& volume, int kernelSize) {
    // Ensure that the kernel size is odd to have a central voxel
    if (kernelSize % 2 == 0) {
        std::cerr << "Kernel size must be odd." << std::endl;
        return;
    }

    int numChannels = volume.getChannels();
    int width = volume.getWidth();
    int height = volume.getHeight();
    int depth = volume.getDepth();
    int halfKernel = kernelSize / 2;

    std::vector<std::vector<int>> histograms(numChannels, std::vector<int>(256, 0));
    Volume filteredVolume(width, height, depth, numChannels);

    for (int z = 0; z < depth; ++z) {
        for (int y = 0; y < height; ++y) {
            for (int c = 0; c < numChannels; ++c) { // Initialize histograms for the first window in each row
                std::fill(histograms[c].begin(), histograms[c].end(), 0);
                for (int dz = -halfKernel; dz <= halfKernel; ++dz) {
                    for (int dy = -halfKernel; dy <= halfKernel; ++dy) {
                        for (int dx = -halfKernel; dx <= halfKernel; ++dx) {
                            int nx = std::min(std::max(0 + dx, 0), width - 1);
                            int ny = std::min(std::max(y + dy, 0), height - 1);
                            int nz = std::min(std::max(z + dz, 0), depth - 1);
                            unsigned char voxelValue = volume.getVoxel(nx, ny, nz, c);
                            histograms[c][voxelValue]++;
                        }
                    }
                }
            }

            for (int x = 0; x < width; ++x) {
                for (int c = 0; c < numChannels; ++c) {
                    // Find the median using the histogram for the current channel
                    unsigned char medianValue = findMedianHist3D(histograms[c], kernelSize * kernelSize * kernelSize);
                    filteredVolume.setVoxel(x, y, z, c, medianValue);

                    // Update histograms by sliding the window
                    if (x < width - 1) {
                        for (int dy = -halfKernel; dy <= halfKernel; ++dy) {
                            for (int dz = -halfKernel; dz <= halfKernel; ++dz) {
                                int ny = std::min(std::max(y + dy, 0), height - 1);
                                int nz = std::min(std::max(z + dz, 0), depth - 1);
                                // Subtract the voxel that is left behind as the window slides
                                unsigned char voxelOut = volume.getVoxel(std::max(x - halfKernel, 0), ny, nz, c);
                                histograms[c][voxelOut]--;
                                // Add the voxel that comes into the window as it slides
                                unsigned char voxelIn = volume.getVoxel(std::min(x + halfKernel + 1, width - 1), ny, nz, c);
                                histograms[c][voxelIn]++;
                            }
                        }
                    }
                }
            }
        }
        // Optionally, print progress
        std::cout << "Processing on depth: " << z << std::endl;
    }
    // Update the original volume with the filtered data
    for (int z = 0; z < depth; ++z) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int c = 0; c < numChannels; ++c) {
                    volume.setVoxel(x, y, z, c, filteredVolume.getVoxel(x, y, z, c));
                }
            }
        }
    }
}
void Filter::apply3DMedianHistFilter(Volume& volume, int kernelSize) {
    Filter filter; // Create an instance of the Filter class
    filter.volumeMedianFilter(volume, kernelSize); // Call the volumeMedianFilter function using the instance
}