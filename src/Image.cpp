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

#include "Image.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif

Image::Image(const std::string &filename)
{
    // Load image data from file using stbi_load function
    data = stbi_load(filename.c_str(), &width, &height, &channels, STBI_default);
    if (!data)
    {
        // Throws a runtime error if the image cannot be loaded (e.g. file not found, invalid format, etc.)
        throw std::runtime_error("Failed to load image: " + filename);
    }
}

Image::Image(int width, int height, int channels) : width(width), height(height), channels(channels)
{
    // Allocate memory for image data
    data = new unsigned char[width * height * channels];
}

Image::Image(const Image &inputImg) : width(inputImg.width), height(inputImg.height), channels(inputImg.channels)
{
    // Allocate memory for image data based on input image size
    size_t dataSize = width * height * channels;
    data = new unsigned char[dataSize];
    for (size_t i = 0; i < dataSize; ++i)
    {
        // Copy image data from input image to new image
        data[i] = inputImg.data[i];
    }
}

// Default constructor initializes an empty image with zero width, height, and channels
Image::Image() : width(0), height(0), channels(0), data(nullptr) {}

Image::Image(int width, int height, int channels, const unsigned char* pixelData)
        : width(width), height(height), channels(channels), data(new unsigned char[width * height * channels]) {
    // Copy the pixel data into this Image's data array
    if (pixelData != nullptr) {
        std::memcpy(data, pixelData, width * height * channels);
    }
}

Image &Image::operator=(const Image &inputImg)
{
    // Check for self-assignment
    if (this != &inputImg)
    {
        // Free existing memory
        delete[] data;
        // Set image dimensions and allocate memory for new image data
        width = inputImg.width;
        height = inputImg.height;
        channels = inputImg.channels;
        size_t dataSize = width * height * channels;
        data = new unsigned char[dataSize];

        // Copy image data from input image to this image
        for (size_t i = 0; i < dataSize; ++i)
        {
            data[i] = inputImg.data[i];
        }

    }
    return *this;
}

Image::~Image()
{
    // Free memory allocated for image data
    delete[] data;
    data = nullptr;
}

int Image::getWidth() const
{
    return width;
}

int Image::getHeight() const
{
    return height;
}

int Image::getChannels() const
{
    return channels;
}

unsigned char Image::getPixel(int x, int y, int channel) const
{
    // Return pixel value at specified coordinates and channel
    return data[(y * width + x) * channels + channel];
}

void Image::setPixel(int x, int y, int channel, unsigned char value)
{
    // Set pixel value at specified coordinates and channel
    data[(y * width + x) * channels + channel] = value;
}

void Image::save(const std::string &filename) const
{
    // Save image data to file using stbi_write_png function
    int success = stbi_write_png(filename.c_str(), width, height, channels, data, STBI_default);
    if (!success)
    {
        // Throws a runtime error if the image cannot be saved (e.g. invalid filename, insufficient permissions, etc.)
        throw std::runtime_error("Failed to save image: " + filename);
    }
}

void Image::setData(const unsigned char* newData) {
    // Check if new data pointer is null
    if (newData == nullptr) {
        // Throws an invalid argument exception if the new data pointer is null
        throw std::invalid_argument("New data pointer is null.");
    }

    // Copy new image data to this image
    size_t dataSize = width * height * channels;
    // Copy the new data to the internal data buffer of the image
    std::memcpy(data, newData, dataSize);
}

const unsigned char* Image::getData() const {
    return data;
}