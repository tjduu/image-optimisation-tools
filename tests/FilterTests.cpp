/*
Group Name: Ziggurat

Members:
- Tianju (Tim) Du (GitHub: edsml-td323)
- Melissa Sim (GitHub: acse-mys20)
- Xiaoye Zhang (GitHub: acse-xz4019)
- Wenhao Hong (GitHub: acse-wh623)
- Javonne Porter (GitHub: acse-jp2923)
- Wenxin Li (GitHub: edsml-wl123)
*/

#include <set>
#include "FilterTests.h"
#include "ProjectionTests.h"

void FilterTests::testMedianBlur() {
    std::cout << "Testing MedianBlur..." << std::endl;

    // Create a test image with known values
    int width = 3, height = 3, channels = 1; // Simple 3x3 grayscale image
    Image testImage(width, height, channels);

    // Initialize with a simple pattern where medianBlur should have a visible effect
    unsigned char testData[9] = {
            100, 150, 100,
            150, 200, 150,
            100, 150, 100
    };

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            testImage.setPixel(x, y, 0, testData[y * width + x]);
        }
    }

    // Apply medianBlur with a kernel size of 3
    Image resultImage = Filter::medianBlur(testImage, 3);

    // Expected result: the middle pixel should be the median of the 3x3 block
    unsigned char expectedMedianValue = 150; // In this simple case, the median is 150

    // Verify the result
    unsigned char resultMedianValue = resultImage.getPixel(1, 1, 0); // Center pixel value after blur

    if (resultMedianValue != expectedMedianValue) {
        std::cerr << "MedianBlur test FAILED." << std::endl;
        return; // Optionally, throw an exception or assert failure here
    }

    std::cout << "MedianBlur test passed." << std::endl;
}

void FilterTests::testBoxBlur() {
    std::cout << "Testing BoxBlur..." << std::endl;

    // Create a test image with distinct values for easy verification
    int width = 5, height = 5, channels = 1; // Simple 5x5 grayscale image
    Image testImage(width, height, channels);

    // Fill the image with a gradient for a visible effect of the box blur
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            testImage.setPixel(x, y, 0, (unsigned char)((x + y) * 255 / (width + height - 2)));
        }
    }

    // Apply boxBlur with a kernel size of 3
    Image resultImage = Filter::boxBlur(testImage, 3);

    // Verify the result by checking a few key pixels, such as the center and near the edges
    bool testPassed = true;

    // Example: Check the center pixel
    int sum = 0, count = 0;
    for (int y = 1; y <= 3; ++y) {
        for (int x = 1; x <= 3; ++x) {
            sum += testImage.getPixel(x, y, 0);
            count++;
        }
    }
    unsigned char expectedCenterValue = sum / count;
    unsigned char resultCenterValue = resultImage.getPixel(2, 2, 0);
    if (resultCenterValue != expectedCenterValue) {
        testPassed = false;
    }

    // Optionally, check more pixels around edges or other locations based on kernel size and image dimensions

    if (!testPassed) {
        std::cerr << "BoxBlur test FAILED." << std::endl;
        // Optionally, throw an exception or assert failure here
        return;
    }

    std::cout << "BoxBlur test passed." << std::endl;
}

void FilterTests::testGaussianBlur() {
    std::cout << "Testing GaussianBlur..." << std::endl;

    // Create a simple test image
    int width = 3, height = 3, channels = 1; // Simple 3x3 grayscale image
    Image testImage(width, height, channels);

    // Initialize the test image with a sharp contrast
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Set the central pixel significantly brighter than the surrounding pixels
            unsigned char value = (x == 1 && y == 1) ? 255 : 0;
            testImage.setPixel(x, y, 0, value);
        }
    }

    // Apply GaussianBlur with a specific kernel size and sigma (standard deviation)
    int kernelSize = 3;
    float sigma = 1.0;
    Image resultImage = Filter::gaussianBlur(testImage, kernelSize, sigma);

    // Verify the result by checking that the blur has been applied
    // Gaussian blur should smooth the sharp contrast between the center and its surroundings
    bool testPassed = true;
    unsigned char centralValue = resultImage.getPixel(1, 1, 0);
    unsigned char adjacentValue = resultImage.getPixel(1, 0, 0); // Pixel above the center

    // The central value should be less than the original 255 due to spreading of intensity
    // Adjacent pixels should now have a value greater than 0
    if (centralValue == 255 || adjacentValue == 0) {
        testPassed = false;
    }

    // Additional checks can be performed here, such as verifying that the blur effect decreases with distance from the center

    if (!testPassed) {
        std::cerr << "GaussianBlur test FAILED." << std::endl;
        // Optionally, assert failure or throw an exception here
        return;
    }

    std::cout << "GaussianBlur test passed." << std::endl;
}

void FilterTests::testGrayScale() {
    std::cout << "Testing GrayScale..." << std::endl;

    // Create a test RGB image with known values
    int width = 2, height = 2, channels = 3; // 2x2 RGB image
    Image testImage(width, height, channels);

    // Initialize the image with arbitrary color values
    // Pixel 1 (Red dominant)
    testImage.setPixel(0, 0, 0, 255); // R
    testImage.setPixel(0, 0, 1, 0);   // G
    testImage.setPixel(0, 0, 2, 0);   // B

    // Pixel 2 (Green dominant)
    testImage.setPixel(1, 0, 0, 0);   // R
    testImage.setPixel(1, 0, 1, 255); // G
    testImage.setPixel(1, 0, 2, 0);   // B

    // Pixel 3 (Blue dominant)
    testImage.setPixel(0, 1, 0, 0);   // R
    testImage.setPixel(0, 1, 1, 0);   // G
    testImage.setPixel(0, 1, 2, 255); // B

    // Pixel 4 (White, equal RGB components)
    testImage.setPixel(1, 1, 0, 255); // R
    testImage.setPixel(1, 1, 1, 255); // G
    testImage.setPixel(1, 1, 2, 255); // B

    // Apply grayscale transformation
    Image resultImage = Filter::grayScale(testImage);

    // Verify the result by checking each pixel's grayscale value
    bool testPassed = true;
    unsigned char expectedGrayscaleValues[4];

    // Calculate expected grayscale values using the updated formula
    expectedGrayscaleValues[0] = static_cast<unsigned char>(0.2126 * 255 + 0.7152 * 0 + 0.0722 * 0); // Red dominant
    expectedGrayscaleValues[1] = static_cast<unsigned char>(0.2126 * 0 + 0.7152 * 255 + 0.0722 * 0); // Green dominant
    expectedGrayscaleValues[2] = static_cast<unsigned char>(0.2126 * 0 + 0.7152 * 0 + 0.0722 * 255); // Blue dominant
    expectedGrayscaleValues[3] = static_cast<unsigned char>(0.2126 * 255 + 0.7152 * 255 + 0.0722 * 255); // White

    // Check each pixel against the expected grayscale value
    if (resultImage.getPixel(0, 0, 0) != expectedGrayscaleValues[0] ||
        resultImage.getPixel(1, 0, 0) != expectedGrayscaleValues[1] ||
        resultImage.getPixel(0, 1, 0) != expectedGrayscaleValues[2] ||
        resultImage.getPixel(1, 1, 0) != expectedGrayscaleValues[3]) {
        testPassed = false;
    }

    if (!testPassed) {
        std::cerr << "GrayScale test FAILED." << std::endl;
        // Optionally, assert failure or throw an exception here
        return;
    }

    std::cout << "GrayScale test passed." << std::endl;
}

void FilterTests::testSetBrightness() {
    std::cout << "Testing SetBrightness..." << std::endl;

    // Create a simple grayscale test image
    int width = 2, height = 2, channels = 1; // 2x2 single-channel (grayscale) image
    Image testImage(width, height, channels);

    // Initialize the image with mid-range values for clear visibility of brightness adjustment
    testImage.setPixel(0, 0, 0, 100); // Top-left
    testImage.setPixel(1, 0, 0, 150); // Top-right
    testImage.setPixel(0, 1, 0, 50);  // Bottom-left
    testImage.setPixel(1, 1, 0, 200); // Bottom-right

    // Apply brightness adjustment
    int adjustment = 60; // Increase brightness by 60
    Image resultImage = Filter::setBrightness(testImage, adjustment, false);

    // Verify the result by checking each pixel's value
    bool testPassed = true;
    unsigned char expectedValues[4] = {
            static_cast<unsigned char>(std::min(100 + adjustment, 255)), // Clamped to 255 if over
            static_cast<unsigned char>(std::min(150 + adjustment, 255)),
            static_cast<unsigned char>(std::min(50 + adjustment, 255)),
            static_cast<unsigned char>(std::min(200 + adjustment, 255))
    };

    // Check each pixel against the expected adjusted value
    if (resultImage.getPixel(0, 0, 0) != expectedValues[0] ||
        resultImage.getPixel(1, 0, 0) != expectedValues[1] ||
        resultImage.getPixel(0, 1, 0) != expectedValues[2] ||
        resultImage.getPixel(1, 1, 0) != expectedValues[3]) {
        testPassed = false;
    }

    if (!testPassed) {
        std::cerr << "SetBrightness test FAILED." << std::endl;
        // Optionally, assert failure or throw an exception here
        return;
    }

    std::cout << "SetBrightness test passed." << std::endl;
}

void FilterTests::test_setBrightness_manual(){
    // Create a sample input image
    Image inputImg(2, 2, 3);
    inputImg.setPixel(0, 0, 0, 100);
    inputImg.setPixel(0, 0, 1, 150);
    inputImg.setPixel(0, 0, 2, 200);

    inputImg.setPixel(1, 0, 0, 50);
    inputImg.setPixel(1, 0, 1, 100);
    inputImg.setPixel(1, 0, 2, 150);

    inputImg.setPixel(0, 1, 0, 25);
    inputImg.setPixel(0, 1, 1, 75);
    inputImg.setPixel(0, 1, 2, 125);

    inputImg.setPixel(1, 1, 0, 175);
    inputImg.setPixel(1, 1, 1, 225);
    inputImg.setPixel(1, 1, 2, 255);

    // Test setting brightness manually
    Filter filter;
    Image outputImg = filter.setBrightness(inputImg, 50, false);

    // Test if the output image has the correct brightness
    assert(outputImg.getPixel(0, 0, 0) == 150);
    assert(outputImg.getPixel(0, 0, 1) == 200);
    assert(outputImg.getPixel(0, 0, 2) == 250);

    assert(outputImg.getPixel(1, 0, 0) == 100);
    assert(outputImg.getPixel(1, 0, 1) == 150);
    assert(outputImg.getPixel(1, 0, 2) == 200);

    assert(outputImg.getPixel(0, 1, 0) == 75);
    assert(outputImg.getPixel(0, 1, 1) == 125);
    assert(outputImg.getPixel(0, 1, 2) == 175);

    assert(outputImg.getPixel(1, 1, 0) == 225);
    assert(outputImg.getPixel(1, 1, 1) == 255);
    assert(outputImg.getPixel(1, 1, 2) == 255);

    std::cout << "setBrightness manually value tests passed successfully!" << std::endl;
}

void FilterTests::test_setBrightness_auto(){

    // Create a sample input image
    Image inputImg(2, 2, 3);
    inputImg.setPixel(0, 0, 0, 100);
    inputImg.setPixel(0, 0, 1, 150);
    inputImg.setPixel(0, 0, 2, 200);

    inputImg.setPixel(1, 0, 0, 50);
    inputImg.setPixel(1, 0, 1, 100);
    inputImg.setPixel(1, 0, 2, 150);

    inputImg.setPixel(0, 1, 0, 25);
    inputImg.setPixel(0, 1, 1, 75);
    inputImg.setPixel(0, 1, 2, 125);

    inputImg.setPixel(1, 1, 0, 175);
    inputImg.setPixel(1, 1, 1, 225);
    inputImg.setPixel(1, 1, 2, 255);

    // Test setting brightness manually
    Filter filter;
    Image outputImg = filter.setBrightness(inputImg, 50, true);

    // Calculate average brightness of the input image
    int avgBrightness = (100 + 150 + 200 + 50 + 100 + 150 + 25 + 75 + 125 + 175 + 225 + 255) / 12;
    int value = 128 - avgBrightness;

    // Test if the output image has the correct average brightness
    assert(outputImg.getPixel(0, 0, 0) == 100 + value);
    assert(outputImg.getPixel(0, 0, 1) == 150 + value);
    assert(outputImg.getPixel(0, 0, 2) == 200 + value);

    assert(outputImg.getPixel(1, 0, 0) == 50 + value);
    assert(outputImg.getPixel(1, 0, 1) == 100 + value);
    assert(outputImg.getPixel(1, 0, 2) == 150 + value);

    assert(outputImg.getPixel(0, 1, 0) == 25 + value);
    assert(outputImg.getPixel(0, 1, 1) == 75 + value);
    assert(outputImg.getPixel(0, 1, 2) == 125 + value);

    assert(outputImg.getPixel(1, 1, 0) == 175 + value);
    assert(outputImg.getPixel(1, 1, 1) == 225 + value);
    assert(outputImg.getPixel(1, 1, 2) == 255 + value);

    std::cout << "setBrightness automatically tests passed successfully!" << std::endl;
}

void FilterTests::test_setBrightness() {
    srand(time(nullptr));
    // Generate a random image
    Image inputImg = ProjectionTests::generateRandomImage(5, 5, 3);

    // Test setting brightness manually
    Filter filter;
    // Generate random value for value
    int value = rand() % 256;
    Image outputImg = filter.setBrightness(inputImg, value, false);

    // Check that all pixels increased by 50
    for (int y = 0; y < inputImg.getHeight(); ++y) {
        for (int x = 0; x < inputImg.getWidth(); ++x) {
            for (int c = 0; c < inputImg.getChannels(); ++c) {
                if (inputImg.getPixel(x, y, c) + value > 255) {
                    // Check if the pixel value is capped at 255
                    assert(outputImg.getPixel(x, y, c) == 255);
                }
                else if (inputImg.getPixel(x, y, c) + value < 0){
                    // Check if the pixel value is capped at 0
                    assert(outputImg.getPixel(x, y, c) == 0);
                }
                else {
                    // Check if the pixel value is increased by value amount for each pixel
                    assert(outputImg.getPixel(x, y, c) == inputImg.getPixel(x, y, c) + value);
                }
            }
        }
    }

    // Check if output image has the same dimensions as the input image
    assert(outputImg.getWidth() == inputImg.getWidth());
    assert(outputImg.getHeight() == inputImg.getHeight());

    std::cout << "setBrightness random image tests passed successfully!" << std::endl;
}



void FilterTests::testSaltAndPepper() {
    std::cout << "Testing SaltAndPepper..." << std::endl;

    // Create a simple grayscale test image
    int width = 100, height = 100, channels = 1; // 100x100 single-channel (grayscale) image for statistical significance
    Image testImage(width, height, channels);

    // Initialize the image with a constant value for simplicity
    unsigned char initialValue = 128;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            testImage.setPixel(x, y, 0, initialValue);
        }
    }

    // Apply salt-and-pepper noise
    double noiseDensity = 0.05; // 5% noise density
    Image resultImage = Filter::salt_and_pepper(testImage, noiseDensity, false); // Assuming false for RGB since it's a grayscale image

    // Count the number of altered (salt and pepper) pixels
    int alteredPixels = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (resultImage.getPixel(x, y, 0) == 0 || resultImage.getPixel(x, y, 0) == 255) {
                alteredPixels++;
            }
        }
    }

    // Calculate the actual density of altered pixels
    double actualDensity = static_cast<double>(alteredPixels) / (width * height);

    // Verify that the actual density is within a reasonable range of the specified density
    // Allowing a margin of error since this is a stochastic process
    double marginOfError = 0.01; // Allowing a 1% margin
    bool testPassed = std::abs(actualDensity - noiseDensity) <= marginOfError;

    if (!testPassed) {
        std::cerr << "SaltAndPepper test FAILED." << std::endl;
        std::cerr << "Expected density: " << noiseDensity << ", Actual density: " << actualDensity << std::endl;
        // Optionally, assert failure or throw an exception here
        return;
    }

    std::cout << "SaltAndPepper test passed." << std::endl;
}

void FilterTests::test_salt_and_pepper(){
    std::cout << "Testing SaltAndPepper..." << std::endl;
    srand(static_cast<unsigned int>(time(0)));

    Image img;
    img = Image("../../Images/gracehopper.png");
    img = Filter::salt_and_pepper(img, 1.0, true);

    int min = 0;
    int max = 0;
    double it = 0;

    // loop thorugh image
    for (int y = 0; y < img.getHeight(); ++y){
        for(int x = 0; x < img.getWidth(); ++x){
            it += 1;
            for (int c = 0; c < img.getChannels(); ++c){

                int pixel_value = static_cast<int>(img.getPixel(x, y, c));
                switch (pixel_value){
                    case 0:
                        min += 1;
                        break;

                    case 255:
                        max += 1;
                        break;

                    default:
                        break;
                }

            }
        }
    }

    // make sure we have nearly 50% min vals
    assert ((static_cast<double>(min) / (it*img.getChannels())) - 0.5 < 0.02);

    // make sure we have nearly 50% max vals
    assert (static_cast<double>(max)/(it*img.getChannels()) - 0.5 < 0.02);

    // check we have roughly 50/50 pixels (2% error allowed)
    assert ((abs(static_cast<double>(min) - static_cast<double>(max))/it) < 0.02 );

    std::cout << "SaltAndPepper test passed." << std::endl;
}

void FilterTests::testThreshold() {
    std::cout << "Testing Threshold..." << std::endl;

    // Create a simple grayscale test image
    int width = 4, height = 4, channels = 1; // 4x4 single-channel (grayscale) image
    Image testImage(width, height, channels);

    // Initialize the image with a gradient for a clear thresholding effect
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            testImage.setPixel(x, y, 0, x * 64); // Simple gradient: 0, 64, 128, 192
        }
    }

    // Apply thresholding
    unsigned char thresholdValue = 128;
    Image resultImage = Filter::threshold(testImage, thresholdValue, false, false); // Assuming false for RGB and HSV

    // Verify the result by checking each pixel's value against the threshold
    bool testPassed = true;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char pixelValue = resultImage.getPixel(x, y, 0);
            if (x * 64 >= thresholdValue) {
                // Expecting pixel to be white (255) if above or equal to the threshold
                if (pixelValue != 255) {
                    testPassed = false;
                }
            } else {
                // Expecting pixel to be black (0) if below the threshold
                if (pixelValue != 0) {
                    testPassed = false;
                }
            }
        }
    }

    if (!testPassed) {
        std::cerr << "Threshold test FAILED." << std::endl;
        // Optionally, assert failure or throw an exception here
        return;
    }

    std::cout << "Threshold test passed." << std::endl;
}

void FilterTests::test_threshold(){
    std::cout << "Testing Threshold..." << std::endl;
    srand(static_cast<unsigned int>(time(0)));

    Image img;
    img = Image("../../Images/dimorphos.png");
    img = Filter::threshold(img, 40, false, false);

    int min = 0;
    int max = 0;
    double it = 0;

    std::set<int> pixel_vals;

    // loop thorugh image
    for (int y = 0; y < img.getHeight(); ++y){
        for(int x = 0; x < img.getWidth(); ++x){
            for(int c = 0; c < img.getChannels(); ++c){

                pixel_vals.insert(static_cast<int>( img.getPixel(x, y, c)));

            }
        }
    }
    // check we only have 2 types of values
    assert (pixel_vals.size() == 2);

    std::cout << "Threshold test passed." << std::endl;
};

void FilterTests::test_rgb_to_hsv(){
    std::cout << "Testing RGBtoHSV..." << std::endl;
    Image img(2, 2, 3);

    // Set each pixel's value to 100
    for(int y = 0; y < img.getHeight(); ++y) {
        for(int x = 0; x < img.getWidth(); ++x) {
            for(int c = 0; c < img.getChannels(); c++){
                img.setPixel(x, y, c, y*50 + c*50);

            }
        }
    }

    // set true values
    std::vector<double> actual_vals{210.0, 1.0, 0.392156, 210.0, 1.0, 0.392156, 210.0, 0.666666, 0.588235, 210.0, 0.666666, 0.588235};

    // scale vals
    // hue
    actual_vals[0] = actual_vals[0] / 360.0 * 255.0;
    actual_vals[3] = actual_vals[3] / 360.0 * 255.0;
    actual_vals[6] = actual_vals[6] / 360.0 * 255.0;
    actual_vals[9] = actual_vals[9] / 360.0 * 255.0;

    // s/v
    actual_vals[1] *= 255.0;
    actual_vals[2] *= 255.0;
    actual_vals[4] *= 255.0;
    actual_vals[5] *= 255.0;
    actual_vals[7] *= 255.0;
    actual_vals[8] *= 255.0;
    actual_vals[10] *= 255.0;
    actual_vals[11] *= 255.0;

    // convert to hsv
    // checkpoint!!!
    // Image new_img = Filter::rgb_to_hsv(img);
    Image new_img = Filter::rgb_to_hsv(img);
    int it = 0;

    // check pixels against true values
    for(int y = 0; y < img.getHeight(); ++y) {
        for(int x = 0; x < img.getWidth(); ++x) {
            for(int c = 0; c < img.getChannels(); c++){
                double pixel_value = static_cast<double>(new_img.getPixel(x, y, c));
                assert ((pixel_value - actual_vals[it]) < 0.001);
                it += 1;

            }
        }
    }
    std::cout << "RGBtoHSV test passed." << std::endl;
}

void FilterTests::test_hsv_to_rgb(){
    std::cout << "Testing HSVtoRGB..." << std::endl;
    Image img(2, 2, 3);

    for(int y = 0; y < img.getHeight(); ++y) {
        for(int x = 0; x < img.getWidth(); ++x) {
            for(int c = 0; c < img.getChannels(); c++){
                img.setPixel(x, y, c, y*50 + c*50);

            }
        }
    }

    Image converted_img = Filter::rgb_to_hsv(img);
    Image pred_orig_img = Filter::hsv_to_rgb(converted_img);
    bool equal = ProjectionTests::compareImages(img, pred_orig_img,1);
    assert(equal);

    std::cout << "HSVtoRGB test passed." << std::endl;
}

void FilterTests::test_rgb_to_hsl(){
    std::cout << "Testing RGBtoHSL..." << std::endl;
    Image img(2, 2, 3);

    for(int y = 0; y < img.getHeight(); ++y) {
        for(int x = 0; x < img.getWidth(); ++x) {
            for(int c = 0; c < img.getChannels(); c++){
                img.setPixel(x, y, c, y*50 + c*50);

            }
        }
    }

    // set true values
    std::vector<double> actual_vals{210.0, 1.0, 0.196078, 210.0, 1.0, 0.196078, 210.0, 0.5, 0.392157, 210.0, 0.5, 0.392157};

    // scale vals
    // hue
    actual_vals[0] = actual_vals[0] / 360.0 * 255.0;
    actual_vals[3] = actual_vals[3] / 360.0 * 255.0;
    actual_vals[6] = actual_vals[6] / 360.0 * 255.0;
    actual_vals[9] = actual_vals[9] / 360.0 * 255.0;

    // s/l
    actual_vals[1] *= 255.0;
    actual_vals[2] *= 255.0;
    actual_vals[4] *= 255.0;
    actual_vals[5] *= 255.0;
    actual_vals[7] *= 255.0;
    actual_vals[8] *= 255.0;
    actual_vals[10] *= 255.0;
    actual_vals[11] *= 255.0;

    // convert to hsv
    Image new_img = Filter::RGBtoHSL(img);
    int it = 0;

    // check pixels against true values
    for(int y = 0; y < img.getHeight(); ++y) {
        for(int x = 0; x < img.getWidth(); ++x) {
            for(int c = 0; c < img.getChannels(); c++){
                float pixel_value = static_cast<float>(new_img.getPixel(x, y, c));
                assert ((pixel_value - actual_vals[it]) < 1);
                it += 1;
            }
        }
    }
    std::cout << "RGBtoHSL test passed." << std::endl;
}

void FilterTests::test_hsl_to_rgb(){

    Image img(2, 2, 3);

    // Set each pixel's value to 100
    for(int y = 0; y < img.getHeight(); ++y) {
        for(int x = 0; x < img.getWidth(); ++x) {
            for(int c = 0; c < img.getChannels(); c++){
                img.setPixel(x, y, c, y*50 + c*50);

            }
        }
    }

    Image converted_img = Filter::RGBtoHSL(img);
    Image pred_orig_img = Filter::HSLtoRGB(converted_img);
    bool equal = ProjectionTests::compareImages(img, pred_orig_img, 1);
    assert(equal);

}

void FilterTests::testHistogramEqualization() {
    std::cout << "Testing HistogramEqualization..." << std::endl;

    // Create a simple grayscale test image with limited contrast
    int width = 4, height = 4, channels = 1; // 4x4 single-channel (grayscale) image
    Image testImage(width, height, channels);

    // Initialize the image with two intensity levels
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char intensity = (x * 50); // Half low intensity, half high intensity
            testImage.setPixel(x, y, 0, intensity);
        }
    }

    // Apply histogram equalization
    Image resultImage = Filter::histogramEqualization(testImage, false); // Assuming false for isHSV

    // Verify the result by ensuring the intensity range has been expanded
    unsigned char minIntensity = 255, maxIntensity = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char pixelValue = resultImage.getPixel(x, y, 0);
            if (pixelValue < minIntensity) {
                minIntensity = pixelValue;
            }
            if (pixelValue > maxIntensity) {
                maxIntensity = pixelValue;
            }
        }
    }

    // Check that the full intensity range is now utilized
    bool testPassed = minIntensity < 50 && maxIntensity > 200; // The original range was [50, 200]

    if (!testPassed) {
        std::cerr << "HistogramEqualization test FAILED." << std::endl;
        std::cerr << "Expected expanded intensity range, got min: " << (int)minIntensity << ", max: " << (int)maxIntensity << std::endl;
        // Optionally, assert failure or throw an exception here
        return;
    }

    std::cout << "HistogramEqualization test passed." << std::endl;
}

void FilterTests::test_histogramEqualization(){
        std::cout << "Testing HistogramEqualization..." << std::endl;
        // Generate random numbers for image dimensions and number of channels
        int height = rand() % 10 + 1;
        int width = rand() % 10 + 1;
        // Random from [1, 3, or 4]
        int numChannel1 = 1;
        int numChannel2 = 3;
        int numChannel3 = 4;


        // Generate random image 1 channel image
        Image inputImg1 = ProjectionTests::generateRandomImage(width, height, numChannel1);
        Image inputImg2 = ProjectionTests::generateRandomImage(width, height, numChannel2);
        Image inputImg3 = ProjectionTests::generateRandomImage(width, height, numChannel3);

        // Test histogram equalization
        Filter filter;
        Image outputImg1 = filter.histogramEqualization(inputImg1, false);
        Image outputImg2 = filter.histogramEqualization(inputImg2, false);
        Image outputImg3 = filter.histogramEqualization(inputImg3, false);

        // Check if the output image has the same dimensions as the input image
        assert(outputImg1.getWidth() == inputImg1.getWidth());
        assert(outputImg1.getHeight() == inputImg1.getHeight());
        assert(outputImg2.getWidth() == inputImg2.getWidth());
        assert(outputImg2.getHeight() == inputImg2.getHeight());
        assert(outputImg3.getWidth() == inputImg3.getWidth());
        assert(outputImg3.getHeight() == inputImg3.getHeight());


        // Check that the largest pixel value is 255 and smallest is 0
        unsigned char min1 = 255;
        unsigned char min2 = 255;
        unsigned char min3 = 255;
        unsigned char max1 = 0;
        unsigned char max2 = 0;
        unsigned char max3 = 0;

        for (int y = 0; y < outputImg1.getHeight(); ++y) {
            for (int x = 0; x < outputImg1.getWidth(); ++x) {
                for (int c = 0; c < outputImg1.getChannels(); ++c) {
                    if (outputImg1.getPixel(x, y, c) < min1) {
                        min1 = outputImg1.getPixel(x, y, c);
                    }
                    if (outputImg1.getPixel(x, y, c) > max1) {
                        max1 = outputImg1.getPixel(x, y, c);
                    }
                }
            }
        }

        assert(min1 == 0);
        assert(max1 == 255);

        for (int y = 0; y < outputImg2.getHeight(); ++y) {
            for (int x = 0; x < outputImg2.getWidth(); ++x) {
                for (int c = 0; c < outputImg2.getChannels(); ++c) {
                    if (outputImg2.getPixel(x, y, c) < min2) {
                        min2 = outputImg2.getPixel(x, y, c);
                    }
                    if (outputImg2.getPixel(x, y, c) > max2) {
                        max2 = outputImg2.getPixel(x, y, c);
                    }
                }
            }
        }

        assert(min2 == 0);
        assert(max2 == 255);

        for (int y = 0; y < outputImg3.getHeight(); ++y) {
            for (int x = 0; x < outputImg3.getWidth(); ++x) {
                for (int c = 0; c < outputImg3.getChannels(); ++c) {
                    if (outputImg3.getPixel(x, y, c) < min3) {
                        min3 = outputImg3.getPixel(x, y, c);
                    }
                    if (outputImg3.getPixel(x, y, c) > max3) {
                        max3 = outputImg3.getPixel(x, y, c);
                    }
                }
            }
        }

        assert(min3 == 0);
        assert(max3 == 255);

        std::cout << "histogramEqualization tests passed successfully!" << std::endl;
}

void FilterTests::test_calculateHistogramEqualization() {
    // Generate a random 4x4 input image
    Image inputImg = ProjectionTests::generateRandomImage(2, 2, 1);

    // Test histogram equalization
    Filter filter;
    Image outputImg = filter.histogramEqualization(inputImg, false);

    // Get all pixel values into a vector
    std::vector<unsigned char> pixelValues;
    for (int y = 0; y < inputImg.getHeight(); ++y) {
        for (int x = 0; x < inputImg.getWidth(); ++x) {
            pixelValues.push_back(outputImg.getPixel(x, y, 0));
        }
    }

    // If smallest pixel value is 0 and largest is 255, then the histogram equalization is correct
    unsigned char min = *std::min_element(pixelValues.begin(), pixelValues.end());
    unsigned char max = *std::max_element(pixelValues.begin(), pixelValues.end());

    assert(min == 0);
    assert(max == 255);

    // Sort the pixel values using selection sort
    ProjectionTests::selectionSort(pixelValues);

    // Check if the smallest pixel value is 0 and the largest is 255
    assert(pixelValues[0] == 0);
    assert(pixelValues[1] == 85);
    assert(pixelValues[2] == 170);
    assert(pixelValues[pixelValues.size() - 1] == 255);

    std::cout << "calculateHistogramEqualization tests passed successfully!" << std::endl;
}



void FilterTests::testApplySobelOperator() {
    std::cout << "Testing ApplySobelOperator..." << std::endl;

    // Create a simple 5x5 grayscale test image
    int width = 5, height = 5, channels = 1;
    Image testImage(width, height, channels);

    // Initialize the image with a vertical edge in the middle
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char intensity = (x < 3) ? 0 : 255; // Left half is black, right half is white
            testImage.setPixel(x, y, 0, intensity);
        }
    }

    // Apply Sobel Operator
    Image resultImage = Filter::applySobelOperator(testImage);

    // Direct verification: Inspect a few strategic points instead of sweeping through
    bool edgeEnhanced = resultImage.getPixel(2, 1, 0) > resultImage.getPixel(1, 1, 0) &&
                        resultImage.getPixel(3, 1, 0) > resultImage.getPixel(4, 1, 0) &&
                        resultImage.getPixel(2, 2, 0) > resultImage.getPixel(1, 2, 0) &&
                        resultImage.getPixel(3, 2, 0) > resultImage.getPixel(4, 2, 0);

    if (!edgeEnhanced) {
        std::cerr << "ApplySobelOperator test FAILED. Edge was not detected as expected." << std::endl;
    } else {
        std::cout << "ApplySobelOperator test passed." << std::endl;
    }
}

void FilterTests::testApplyPrewittOperator() {
    std::cout << "Testing ApplyPrewittOperator..." << std::endl;

    // Create a simple 5x5 grayscale test image
    int width = 5, height = 5, channels = 1;
    Image testImage(width, height, channels);

    // Initialize the image with a vertical edge in the middle
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char intensity = (x < 2) ? 0 : 255; // Left half is black, right half is white
            testImage.setPixel(x, y, 0, intensity);
        }
    }

    // Apply Prewitt Operator
    Image resultImage = Filter::applyPrewittOperator(testImage);

    // Verify that the Prewitt operator highlights the edge
    // Direct verification: Inspect a few strategic points instead of sweeping through
    bool edgeEnhanced = resultImage.getPixel(1, 1, 0) > resultImage.getPixel(0, 1, 0) &&
                        resultImage.getPixel(2, 1, 0) > resultImage.getPixel(3, 1, 0) &&
                        resultImage.getPixel(1, 2, 0) > resultImage.getPixel(0, 2, 0) &&
                        resultImage.getPixel(2, 2, 0) > resultImage.getPixel(3, 2, 0);

    if (!edgeEnhanced) {
        std::cerr << "ApplyPrewittOperator test FAILED. Edge was not detected as expected." << std::endl;
    } else {
        std::cout << "ApplyPrewittOperator test passed." << std::endl;
    }
}

void FilterTests::testApplyScharrOperator() {
    std::cout << "Testing ApplyScharrOperator..." << std::endl;

    // Create a simple 5x5 grayscale test image
    int width = 5, height = 5, channels = 1;
    Image testImage(width, height, channels);

    // Initialize the image with a vertical edge in the middle
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char intensity = (x < 3) ? 0 : 255; // Left half is black, right half is white
            testImage.setPixel(x, y, 0, intensity);
        }
    }

    // Apply Scharr Operator
    Image resultImage = Filter::applyScharrOperator(testImage);

    // Verify that the Scharr operator highlights the edge
    // Check for a significant gradient at the edge (around the middle columns)
    // Verify that the Prewitt operator highlights the edge
    // Direct verification: Inspect a few strategic points instead of sweeping through
    bool edgeEnhanced = resultImage.getPixel(2, 1, 0) > resultImage.getPixel(1, 1, 0) &&
                        resultImage.getPixel(3, 1, 0) > resultImage.getPixel(4, 1, 0) &&
                        resultImage.getPixel(2, 2, 0) > resultImage.getPixel(1, 2, 0) &&
                        resultImage.getPixel(3, 2, 0) > resultImage.getPixel(4, 2, 0);

    if (!edgeEnhanced) {
        std::cerr << "ApplyScharrOperator test FAILED. Edge was not detected as expected." << std::endl;
    } else {
        std::cout << "ApplyScharrOperator test passed." << std::endl;
    }
}

void FilterTests::testApplyRobertsCrossOperator() {
    std::cout << "Testing ApplyRobertsCrossOperator..." << std::endl;

    // Create a simple 4x4 grayscale test image
    int width = 4, height = 4, channels = 1;
    Image testImage(width, height, channels);

    // Initialize the image with a diagonal edge
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char intensity = (y > x) ? 255 : 0; // Diagonal division: top-left is white, bottom-right is black
            testImage.setPixel(x, y, 0, intensity);
        }
    }

    // Apply Roberts Cross Operator
    Image resultImage = Filter::applyRobertsCrossOperator(testImage);

//    // Print testImage and resultImage for visual verification (optional)
//    std::cout << "testImage: " << std::endl;
//    for (int y = 0; y < height; ++y) {
//        for (int x = 0; x < width; ++x) {
//            std::cout << (int)testImage.getPixel(x, y, 0) << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    std::cout << "resultImage: " << std::endl;
//    for (int y = 0; y < height; ++y) {
//        for (int x = 0; x < width; ++x) {
//            std::cout << (int)resultImage.getPixel(x, y, 0) << " ";
//        }
//        std::cout << std::endl;
//    }

    // Directly verify specific pixel values around the diagonal edge
    bool edgeDetectedCorrectly = true;
    // Ideally, pixels on the edge should have higher intensity, and adjacent pixels should have lower intensity.
    // We can check a few strategic pixels to assert this.
    if (resultImage.getPixel(1, 1, 0) <= 128 || resultImage.getPixel(2, 2, 0) <= 128) { // Checking pixels just on the edge
        edgeDetectedCorrectly = false;
    }

    if (resultImage.getPixel(0, 2, 0) > 128 || resultImage.getPixel(3, 1, 0) > 128) { // Checking pixels just off the edge
        edgeDetectedCorrectly = false;
    }

    if (!edgeDetectedCorrectly) {
        std::cerr << "ApplyRobertsCrossOperator test FAILED. Edge detection did not match expected pattern." << std::endl;
    } else {
        std::cout << "ApplyRobertsCrossOperator test passed." << std::endl;
    }
}

double FilterTests::calculateSliceVariance(const std::shared_ptr<Image>& slice) {
    double sum = 0.0, sumSquared = 0.0;
    int pixels = slice->getWidth() * slice->getHeight();
    for (int y = 0; y < slice->getHeight(); ++y) {
        for (int x = 0; x < slice->getWidth(); ++x) {
            unsigned char pixel = slice->getPixel(x, y, 0); // 假设单通道
            sum += pixel;
            sumSquared += pixel * pixel;
        }
    }
    double mean = sum / pixels;
    return (sumSquared / pixels) - (mean * mean);
}

double FilterTests::calculateSliceVariance(const std::shared_ptr<Slice>& slice) {
    double sum = 0.0, sumSquared = 0.0;
    int pixels = slice->getWidth() * slice->getHeight();
    for (int y = 0; y < slice->getHeight(); ++y) {
        for (int x = 0; x < slice->getWidth(); ++x) {
            unsigned char pixel = slice->getPixel(x, y, 0); // 假设单通道
            sum += pixel;
            sumSquared += pixel * pixel;
        }
    }
    double mean = sum / pixels;
    return (sumSquared / pixels) - (mean * mean);
}

void FilterTests::test3DGaussianBlur(Volume& volume) {

    // Get mid-slice indices
    int midX = volume.getWidth() / 2;
    int midY = volume.getHeight() / 2;
    int midZ = volume.getDepth() / 2;
    // a new volume to store the original volume
    Volume originalVolume = volume;

    // Calculate variance before blur
    double originalVarianceXY = FilterTests::calculateSliceVariance(originalVolume.getSlice(midZ)); // XY plane
    double originalVarianceXZ = FilterTests::calculateSliceVariance(originalVolume.getSliceXZ(midY)); // XZ plane
    double originalVarianceYZ = FilterTests::calculateSliceVariance(originalVolume.getSliceYZ(midX)); // YZ plane
    //print every element in the volume
//    for (int z = 0; z < originalVolume.getDepth(); ++z) {
//        std::shared_ptr<Image> slice = originalVolume.getSlice(z);
//        for (int y = 0; y < slice->getHeight(); ++y) {
//            for (int x = 0; x < slice->getWidth(); ++x) {
//                std::cout << (int)slice->getPixel(x, y, 0) << " ";
//            }
//            std::cout << std::endl;
//        }
//    }

    // Apply 3D Gaussian blur
    Filter::apply3DGaussianBlur(volume, 3, 1.0);
    // Assuming the blur is applied in-place, now we get the slices again for blurred variance calculation
    double blurredVarianceXY = FilterTests::calculateSliceVariance(volume.getSlice(midZ)); // XY plane
    double blurredVarianceXZ = FilterTests::calculateSliceVariance(volume.getSliceXZ(midY)); // XZ plane
    double blurredVarianceYZ = FilterTests::calculateSliceVariance(volume.getSliceYZ(midX)); // YZ plane
    //print every element in the volume
//    for (int z = 0; z < volume.getDepth(); ++z) {
//        std::shared_ptr<Image> slice = volume.getSlice(z);
//        for (int y = 0; y < slice->getHeight(); ++y) {
//            for (int x = 0; x < slice->getWidth(); ++x) {
//                std::cout << (int)slice->getPixel(x, y, 0) << " ";
//            }
//            std::cout << std::endl;
//        }
//    }

    // Output variance comparison results
    std::cout << "Original Variance XY: " << originalVarianceXY << ", Blurred Variance XY: " << blurredVarianceXY << std::endl;
    std::cout << "Original Variance XZ: " << originalVarianceXZ << ", Blurred Variance XZ: " << blurredVarianceXZ << std::endl;
    std::cout << "Original Variance YZ: " << originalVarianceYZ << ", Blurred Variance YZ: " << blurredVarianceYZ << std::endl;

    // Verify variance decreased
    if (blurredVarianceXY < originalVarianceXY && blurredVarianceXZ < originalVarianceXZ && blurredVarianceYZ < originalVarianceYZ) {
        std::cout << "Test Passed: Variance decreased in all directions after blur." << std::endl;
    } else {
        std::cout << "Test Failed: Variance did not decrease as expected in all directions." << std::endl;
    }
}

void FilterTests::testCreate3DKernel(int kernelSize, float sigma) {
    std::cout << "Testing create3DKernel with size " << kernelSize << " and sigma " << sigma << "..." << std::endl;

    auto kernel = Filter::create3DKernel(kernelSize, sigma);

    // Verify kernel dimensions
    assert(kernel.size() == kernelSize);
    for (const auto& plane : kernel) {
        assert(plane.size() == kernelSize);
        for (const auto& row : plane) {
            assert(row.size() == kernelSize);
        }
    }

    // Verify kernel sum equals 1
    float sum = 0.0f;
    for (const auto& plane : kernel) {
        for (const auto& row : plane) {
            for (float value : row) {
                sum += value;
            }
        }
    }
    assert(abs(sum - 1.0f) < 1e-5);

    // Verify central value is the maximum
    float centralValue = kernel[kernelSize / 2][kernelSize / 2][kernelSize / 2];
    for (const auto& plane : kernel) {
        for (const auto& row : plane) {
            for (float value : row) {
                assert(value <= centralValue);
            }
        }
    }

    std::cout << "create3DKernel test passed." << std::endl;
}

void FilterTests::test3DMedianFilter() {
    std::cout << "Testing 3D Median Filter..." << std::endl;

    // Create a simple test volume
    int width = 5, height = 5, depth = 5, channels = 1; // Simple 5x5x5 volume, single-channel
    Volume testVolume(width, height, depth, channels);

    // Fill the volume with increasing values, except for one voxel which is set higher
    for (int z = 0; z < depth; ++z) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                unsigned char value = static_cast<unsigned char>((x + y + z) % 256);
                testVolume.setVoxel(x, y, z, 0, value);
            }
        }
    }
    // Set one voxel in the center to a significantly higher value
    testVolume.setVoxel(width / 2, height / 2, depth / 2, 0, 255);

    // Apply the 3D median filter
    Filter::apply3DMedianFilter(testVolume, 3);

    // Verify that the voxel previously set to a higher value has been adjusted
    unsigned char centralValue = testVolume.getVoxel(width / 2, height / 2, depth / 2, 0);
    if (centralValue == 255) {
        std::cerr << "3D Median Filter test FAILED: Central value was not adjusted as expected." << std::endl;
        return;
    }

    std::cout << "3D Median Filter test passed." << std::endl;
}