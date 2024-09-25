/**
 * @file Filter.h
 * @brief Declaration of the Filter class for performing image processing operations.
 *
 * The Filter class offers a collection of static methods for performing various image processing operations,
 * including blurring, edge detection, color space conversion, and more. These operations are essential in
 * fields like computer vision and digital image processing.
 *
 * Group Name: Ziggurat
 *
 * Members:
 * - Xiaoye Zhang (GitHub: acse-xz4019)
 * - Melissa Sim (GitHub: acse-mys20)
 * - Wenhao Hong (GitHub: acse-wh623)
 * - Javonne Porter (GitHub: acse-jp2923)
 * - Tianju (Tim) Du (GitHub: edsml-td323)
 * - Wenxin Li (GitHub: edsml-wl123)
 *
 */

#ifndef ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_FILTER_H
#define ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_FILTER_H

#include "Image.h"
#include "Volume.h"

#include <vector>
#include <stdexcept>

/**
 * @class Filter
 * @brief Contains static methods for image processing operations.
 * 
 * Methods within this class apply various image processing techniques to `Image` objects,
 * facilitating operations such as blurring, edge detection, and color space conversions.
 * The class functions are static, allowing for easy access without the need to instantiate objects.
 *
 */
class Filter {
public:

    /**
     * @brief Applies a median blur filter to an image using a specified kernel size.
     * @param image Reference to the input image.
     * @param kernel_size Size of the kernel. Must be an odd number.
     * @return A new Image object with the median blur applied.
     */
    static Image medianBlur(Image& image, int kernel_size);

    /**
     * @brief Applies a histogram-based median blur filter to an image using a specified kernel size.
     *
     * You can manually change to use this version by uncommenting the function in the main.cpp file line 356.
     *
     * @param image Reference to the input image.
     * @param kernel_size Size of the kernel. Must be an odd number.
     * @return A new Image object with the histogram-based median blur applied.
     */
    static Image histomedianBlur(Image& image, int kernel_size);

    /**
     * @brief Applies a box blur filter to an image using a specified kernel size.
     * @param image Reference to the input image.
     * @param kernel_size Size of the kernel. Must be an odd number.
     * @return A new Image object with the box blur applied.
     */
    static Image boxBlur(Image& image, int kernel_size);

    /**
    * @brief Applies a Gaussian blur filter to an image using a specified kernel size and sigma value.
    * @param image Reference to the input image.
    * @param kernelSize Size of the kernel.
    * @param sigma Standard deviation of the Gaussian kernel.
    * @return A new Image object with the Gaussian blur applied.
    */
    static Image gaussianBlur(Image& image, int kernelSize, float sigma);

    /**
     * @brief Converts image from 3 channels (RGB) to 1 channel (grayscale).
     * The grayscale image has a single channel with pixel values ranging from 0 to 255.
     * @param image A reference to the input image to be processed.
     * @return A grayscaled image, or the original image if it is already grayscaled.
    */
    static Image grayScale(Image &inputImg);

    /**
     * @brief Adjusts the brightness of the image.of an input image by adding a specified value to each pixel value.
     * Or automatically adjust the brightness of an image.
     * @param image A reference to the input image to be processed.
     * @param value The value to be added to each pixel value.
     * @param autoBrightness A boolean value to determine whether to automatically adjust the brightness of the image.
     * @return The image with adjusted brightness.
    */
    static Image setBrightness(Image &image, int value, bool autoBrightness=false);

    /**
     * @brief Applies a 3x3 Sobel operator to an input image for edge detection.
     * 
     * The Sobel operator is a common edge detection operator that computes 
     * and approximation of the gradient of the image intensity function to highlight edges
     * (areas of high intensity change). Utilising a weighted coefficient for horizontal
     * and vertical gradients.
     * 
     * @param image The input Image object to which the Sobel operator will be applied.
     * @return The image after applying the Sobel operator for edge detection.
    */
    static Image applySobelOperator(Image& image);

    /**
     * @brief Applies a 3x3 Prewitt operator to an input image for edge detection.
     * 
     * The Prewitt operator is another common edge detection operator that computes
     * the gradient of the image intensity function to highlight edges
     * (areas of high intensity change). Utilising equal weight for horizontal 
     * and vertical gradients.
     * 
     * @param image The input Image object to which the Prewitt operator will be applied.
     * @return The image after applying the Prewitt operator for edge detection.
    */
    static Image applyPrewittOperator(Image& image);

    /**
     * @brief Applies a 3x3 Scharr operator to an input image for edge detection.
     * 
     * The Scharr operator is a more rotationally symmetric edge detection operator
     * that computes the gradient of the image intensity function. It is more
     * sensitive to diagonal edges than the Sobel and Prewitt operators.
     * 
     * @param image The input Image object to which the Scharr operator will be applied.
     * @return The image after applying the Scharr operator for edge detection.
    */
    static Image applyScharrOperator(Image& image);

    /**
     * @brief Applies a 2x2 Roberts Cross operator to an input image for edge detection.
     * 
     * The Roberts Cross operator is a simple edge detection operator that computes
     * the gradient of the image intensity function using a pair of 2x2 convolution kernels.
     * 
     * @param image The input Image object to which the Roberts Cross operator will be applied.
     * @return The image after applying the Roberts Cross operator for edge detection.
    */
    static Image applyRobertsCrossOperator(Image& image);

    /**
     * @brief Applies a 3D Gaussian blur filter to a volume using a specified kernel size and standard deviation.
     * @param volume The input Volume object to be filtered.
     * @param kernelSize The size of the kernel for the 3D Gaussian blur filter. Size must be odd number (e.g. 3x3x3, 5x5x5, etc.).
     * @param sigma The standard deviation of the Gaussian kernel.
     * @return The filtered volume after applying the 3D Gaussian blur filter.
    */
    static void apply3DGaussianBlur(Volume& volume, int kernelSize, float sigma);

    /**
     * @brief Applies a 3D median filter to a volume using a specified kernel size.
     * Replaces each voxel value with the median value of the neighboring voxels within the kernel..
     * @param volume The input Volume object to be filtered.
     * @param kernelSize The size of the kernel for the 3D median filter. Size must be odd number (e.g. 3x3x3, 5x5x5, etc.).
     * @return The filtered volume after applying the 3D median filter.
    */
    static void apply3DMedianFilter(Volume& volume, int kernelSize);

    /**
     * @brief Adjusts the contrast of an input image by scaling the pixel values
     * so that they span the full range of intensity values (0-255).
     * @param image The input Image object to which the contrast adjustment will be applied.
     * @param isHSV A boolean value to determine whether to convert the image to HSV (true) or HSL (false) colour space.
     * @return The image with adjusted contrast.
    */
    static Image histogramEqualization(Image &image, const bool &isHSV);

    /**
     * @brief Called by the histogramEqualization function to calculate the histogram of an image and apply histogram equalization to the image.
     * @param image The input Image object to be processed.
     * @param channel The channel index of the image to be processed. 
     *                (e.g. for single channel will be set to 0 and 
     *                for RGB will be set to 2 (L / V channel in HSV and HSL colour space))
     * @return The image with histogram equalization applied.
    */
    static Image calculateHistogramEqualization(Image &image, int channel);

    /**
     * @brief Applies a salt-and-pepper noise filter to an input image by setting a proportion of pixel values either 0 (black) or 255 (white).
     * The proportion of pixels is user defined, and the pixels are set to noise randomly.
     * @param image The input Image object to which the salt-and-pepper noise filter will be applied.
     * @param proportion The proportion of pixel values (0.0 to 1.0) to be set as noise.
     * @param rgb A boolean value to determine whether to apply the filter to RGB channels or the grayscale image.
     * @return The image with salt-and-pepper noise filter applied.
    */
    static Image salt_and_pepper(Image image, const double &proportion, const bool &rgb);

    /**
     * @brief Applies a threshold filter to an input image by setting pixel values
     * above a specified threshold to 255 (white) and pixel values below the threshold to 0 (black).
     * The thresholding can be applied either to a single channel (for grayscale images) 
     * or to the value/lightness channel of a RGB image converted to HSV or HSL color space.
     * 
     * @param image The input Image object to which the threshold filter will be applied.
     * @param thresholdValue The threshold value for the filter.
     * @param rgb A boolean value to determine whether to apply the filter to RGB channels(true) or the grayscale image (false).
     * @param isHSV A boolean value to determine whether to convert the image to HSV colour space (true) or HSL colour space (false).
     * @return The image with threshold filter applied.
    */
    static Image threshold(Image& image, const double &thresholdValue, const bool &rgb, bool isHSV);

    /**
     * @brief Randomly generate a number between 0 and 1.
     * @return A random number between 0 and 1.
    */
    static double random_number();

    /**
     * @brief Converts an RGB image to HSL (Hue, Saturation, Lightness) color space.
     * By separating the intensity information (lightness) from the color information (hue and saturation)
     * of each pixel in the image.
     *  
     * @param image The input RGB image to be converted.
     * @return The image converted to HSL color space.
    */
    static Image RGBtoHSL(Image &image);

    /**
     * @brief Converts an HSL (Hue, Saturation, Lightness) image to RGB color space.
     * By combining the intensity information (lightness) with the color information (hue and saturation)
     * of each pixel in the image.
     *  
     * @param image The input HSL image to be converted.
     * @return The image converted to RGB color space.
    */
    static Image HSLtoRGB(Image &image);

    /**
     * @brief Converts an RGB image to HSV (Hue, Saturation, Value) color space.
     * The HSV color space separates the intensity information (value) 
     * from the color information (hue and saturation) of each pixel in the image.
     *  
     * @param image The input RGB image to be converted.
     * @return The image converted to HSV color space.
    */
    static Image rgb_to_hsv(Image &image);

    /**
     * @brief Converts an HSV (Hue, Saturation, Value) image to RGB color space.
     * The HSV color space separates the intensity information (value) 
     * from the color information (hue and saturation) of each pixel in the image.
     *  
     * @param image The input HSV image to be converted.
     * @return The image converted to RGB color space.
    */
    static Image hsv_to_rgb(const Image &hsvImage);

    /**
     * @brief Genearates a 3D kernel based on the Gaussian distribution, which can
     * be used for applying a Gaussian blur in three dimensions. The kernel is normalized
     * so that the sum of all elements is 1.
     *
     * @param kernelSize The size of the kernel (must be an odd number). This is the length of one side of the cube.
     * @param sigma The standard deviation of the Gaussian distribution.
     * @return A 3D vector containing the Gaussian kernel.
    */
    static std::vector<std::vector<std::vector<float>>> create3DKernel(int kernelSize, float sigma);

      /**
     * @brief Applies a median filter with histogram-based optimization to a 3D volume.
     *
     * This function applies a median filter to each voxel in a 3D volume. The median filter
     * is a non-linear digital filtering technique, often used to remove noise from images or signals.
     * The filter allows for edge-preserving smoothing, as it replaces each voxel value with the
     * median value in its local neighborhood defined by the kernelSize. The histogram-based
     * approach is used for efficient computation.
     *
     * You can manually change to use this version by uncommenting the function in the main.cpp file line 719.
     *
     * @param volume Reference to the Volume object to be filtered.
     * @param kernelSize Integer representing the size of the cube kernel, which defines the
     *                   neighborhood over which the median is computed.
     */
    static void apply3DMedianHistFilter(Volume& volume, int kernelSize);


private:
    /**
     * @brief Converts an image to a 2D vector of pixel values.
     * Each pixel value is represented as a vector of unsigned char values.
     * It assumes the image is in grayscale and therefore sets pixel values 
     * to the first channel of the image.
     * Helper function for applying edge operators.
     * 
     * @param image The input grayscale image to be converted.
     * @return A 2D vector of unsigned char values representing a pixel's grayscale value.
    */
    static std::vector<std::vector<unsigned char>> ConvertImageToVector(const Image& image);

    /**
     * @brief Converts a 2D vector of pixel values to a new Image object.
     * Each pixel value is represented as a vector of unsigned char values.
     * It assumes the image is in grayscale and therefore sets pixel values directly 
     * to the first channel of the image.
     * Helper function for applying edge operators.
     * 
     * @param pixelValues A 2D vector of unsigned char values representing a pixel's grayscale value.
     * @param width The width of the image.
     * @param height The height of the image.
     * @return An Image object created from the 2D vector of pixel values.
    */
    static Image convertGradientToImage(const std::vector<std::vector<unsigned char>>& gradient, int width, int height);

    /**
     * @brief Applies an edge operator to an input image using a specified kernel.
     * The edge operator computes the gradient of the image intensity function to highlight edges (areas of high intensity change).
     * 
     * @param image The input Image object to which the edge operator will be applied.
     * @param kernelX The kernel for the horizontal gradient component.
     * @param kernelY The kernel for the vertical gradient component.
     * @return A new Image object after applying the edge operator.
    */
    static Image applyEdgeOperator(Image& image, const int kernelX[3][3], const int kernelY[3][3]);


    /**
     * @brief Calculates he value of the Gaussian distribution for a given point based on the standard deviation sigma.
     * The Gaussian distribution is used to create a kernel for a Gaussian blur operation.
     * 
     * @param x Float value representing the x-coordinate of the point.
     * @param y Float value representing the y-coordinate of the point.
     * @param z Float value representing the z-coordinate of the point.
     * @param sigma Float value representing the standard deviation of the Gaussian distribution.
     * @return The volume after applying the 3D convolution operation.
    */
    static float gaussian(float x, float y, float z, float sigma);

     /**
    * @brief Finds the median value from a histogram.
    *
    * Given a histogram of values and the size of the window over which the median is sought,
    * this function calculates the median value. The histogram represents the frequency of each
    * intensity value within the window, and the median is the intensity value that divides the
    * cumulative distribution into two equal halves. This method is particularly efficient for
    * finding medians in a moving window, such as when applying a median filter to an image.
    *
    * @param histogram A vector of integers representing the histogram of intensity values.
    * @param windowSize Integer representing the total number of elements in the window, used to
    *                   determine the midpoint of the cumulative distribution.
    * @return Integer value representing the median intensity found in the histogram.
    */
    static int findMedianHist(const std::vector<int>& histogram, int windowSize);

    /**
    * @brief Finds the median value from a 3D histogram similar to findMedianHist
    * @param histogram A vector of integers representing the histogram of intensity values.
    * @param windowSize Integer representing the total number of elements in the window, used to
    *                   determine the midpoint of the cumulative distribution.
    * @return Integer value representing the median intensity found in the histogram.

    **/
    static int findMedianHist3D(const std::vector<int>& histogram, int windowSize);
    /**
     * @brief Applies a median filter to a 3D volume.
     *
     * The function operates on a 3D volume by applying a median filter to each voxel. The filter
     * considers a local neighborhood around each voxel defined by the kernelSize and computes the
     * median intensity value within that window. This median value replaces the original intensity
     * value of the voxel. The median filtering process is done in-place; hence, the original volume
     * data is modified. An odd kernel size ensures a symmetric window around each voxel.
     *
     * @note The kernel size must be odd to define a central voxel.
     *
     * @param volume Reference to the Volume object representing the 3D data to be filtered.
     * @param kernelSize Size of the cubic kernel used for the median filtering. It represents
     *                   the length of the edge of the cube. The kernelSize must be an odd number.
     */
    void volumeMedianFilter(Volume& volume, int kernelSize);
};

#endif //ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_FILTER_H