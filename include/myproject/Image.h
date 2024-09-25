/**
 * @file Image.h
 * @brief Declaration of the Image class for image manipulation and processing.
 *
 * The Image class encapsulates data and operations for an image, supporting image creation from files,
 * specification of dimensions and channels, and manipulation of pixel values. It integrates functionalities
 * to load, save, and access image data, enabling the development of image processing tasks.
 *
 * Group: Ziggurat
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

#ifndef ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_IMAGE_H
#define ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_IMAGE_H
#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <cstring>

/**
 * @class Image
 * @brief Manages image data and operations.
 *
 * The Image class provides a flexible interface for working with images in memory. It allows for creating images
 * from file paths or initializing them with specific dimensions and channel counts. Pixel data is managed dynamically,
 * supporting deep copy operations and pixel-wise manipulation. This class is suitable as a foundational component
 * in applications involving image processing, analysis, and visualization.
 *
 */
class Image
{
public:
    /**
     * @brief Constructs an Image object by loading an image from a specified file.
     * @param filename The path to the image file as a reference to a string.
     * @throw std::runtime_error if the file cannot be loaded or is not a valid image file.
     */
    Image(const std::string &filename);

    /**
     * @brief Constructs an Image object with specified dimensions and channel count, initializing pixels to default values.
     * @param width The width of the image. (Number of pixels in the x-direction)
     * @param height The height of the image. (Number of pixels in the y-direction)
     * @param channels The number of channels in the image. (e.g., 3 for RGB, 4 for RGBA)
    */
    Image(int width, int height, int channels);

    /**
     * @brief Constructs an Image object with specified dimensions, channel count, and initial pixel data.
     * @param width The width of the image. (Number of pixels in the x-direction)
     * @param height The height of the image. (Number of pixels in the y-direction)
     * @param channels The number of channels in the image. (e.g., 3 for RGB, 4 for RGBA)
     * @param pixelData A pointer to the pixel data as an array of unsigned char values.
     */
    Image(int width, int height, int channels, const unsigned char* pixelData);

    /**
     * @brief Copy constructor that creates a deep copy of another Image object.
     * @param inputImg The Image object to copy.
     */
    Image(const Image &inputImg);

    /**
     * @brief Default constructor that initializes an empty Image object.
     */
    Image();

    /**
     * @brief Copy assignment operator that assigns the image data from another Image object to this one.
     * @param inputImg The Image object to copy.
     * @return A reference to this Image object.
     */
    Image &operator=(const Image &inputImg);

    /**
     * @brief Destructor that frees allocated memory for the image data.
     */
    ~Image();

    /**
     * @brief Returns the width of the image.
     * @return The width of the image.
     */
    int getWidth() const;

    /**
     * @brief Returns the height of the image.
     * @return The height of the image.
     */
    int getHeight() const;

    /**
     * @brief Returns the number of color channels in the image.
     * @return The number of channels in the image.
     */
    int getChannels() const;

    /**
     * @brief Retrieves the value of a specific pixel and channel.
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @param channel The channel index of the pixel.
     * @return The pixel value at the specified coordinates and channel.
     */
    unsigned char getPixel(int x, int y, int channel) const;

    /**
     * @brief Sets the value for a specific pixel and channel.
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @param channel The channel index of the pixel.
     * @param value New value for the pixel.
     */
    void setPixel(int x, int y, int channel, unsigned char value);

    /**
     * @brief Saves the image to a file.
     * @param filename Path where the image will be saved.
     * @throw std::runtime_error if the image cannot be saved.
     */
    void save(const std::string &filename) const;

    /**
     * @brief Sets the image data.
     * @param newData Pointer to the new image data.
     * @throw std::invalid_argument if newData is null.
     */
    void setData(const unsigned char* newData);

    /**
     * @brief Accesses the raw image data.
     * @return Pointer to the image data.
     */
    const unsigned char* getData() const;

private:
    int width; ///< Width of the image as pixels in the x-direction
    int height; ///< Height of the image as pixels in the y-direction
    int channels; ///< Number of channels in the image (e.g., 3 for RGB, 4 for RGBA)
    unsigned char *data; ///< Image data stored as a one-dimensional array of unsigned char values
};

#endif //ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_IMAGE_H
