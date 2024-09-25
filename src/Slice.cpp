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

#include "Slice.h"
#include "stb_image_write.h"
#include <algorithm> // For std::copy
#include <cstring>   // For std::memcpy

Slice::Slice(int width, int height, int channels, std::unique_ptr<unsigned char[]> data)
        : width(width), height(height), channels(channels), data(std::move(data)) {}

Slice::Slice(const Slice& other)
        : width(other.width), height(other.height), channels(other.channels),
          data(std::make_unique<unsigned char[]>(width * height * channels)) {
    std::copy(&other.data[0], &other.data[width * height * channels], &data[0]);
}

Slice::Slice(Slice&& other) noexcept
        : width(other.width), height(other.height), channels(other.channels), data(std::move(other.data)) {
    other.width = 0;
    other.height = 0;
    other.channels = 0;
    other.data = nullptr;
}

bool Slice::save(const std::string& filename) const {
    if (!data) {
        return false;
    }
    return stbi_write_png(filename.c_str(), width, height, channels, data.get(), width * channels) != 0;
}

//get the width of the slice
int Slice::getWidth() const {
    return width;
}

//get the height of the slice
int Slice::getHeight() const {
    return height;
}

//get the number of channels in the slice
int Slice::getChannels() const {
    return channels;
}

//get the intensity value of a pixel at the specified location and channel
unsigned char Slice::getPixel(int x, int y, int channel) const {
    return data[(y * width + x) * channels + channel];
}

//set the intensity value of a pixel at the specified location and channel
void Slice::setPixel(int x, int y, int channel, unsigned char value) {
    data[(y * width + x) * channels + channel] = value;
}
