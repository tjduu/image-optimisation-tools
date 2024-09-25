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

#include "Volume.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include "Slice.h"
#include <cstring>
#include <iostream>

// custom comparison function for natural sorting
bool naturalSort(const std::string& a, const std::string& b) {
    std::regex re("(\\d+)");
    std::sregex_iterator it_a(a.begin(), a.end(), re), it_b(b.begin(), b.end(), re);
    std::sregex_iterator end;

    // compare each matched number
    while (it_a != end && it_b != end) {
        int num_a = std::stoi(it_a->str());
        int num_b = std::stoi(it_b->str());

        if (num_a != num_b) {
            return num_a < num_b;
        }
        ++it_a;
        ++it_b;
    }

    // if all numbers are equal, sort based on original string
    return a < b;
}

// custom sorting function for natural sorting
void customSort(std::vector<std::string>& files) {
    for (size_t i = 1; i < files.size(); ++i) {
        std::string key = files[i];
        int j = i - 1;

        // 将files[i]移动到它在前面子数组中的正确位置
        while (j >= 0 && naturalSort(key, files[j])) {
            files[j + 1] = files[j];
            j = j - 1;
        }
        files[j + 1] = key;
    }
}

// Volume constructor that loads images from a folder
Volume::Volume(const std::string& folderPath) : data(nullptr), width(0), height(0), depth(0), channels(0) {
    loadImagesFromFolder(folderPath);
    generate3DVolumeFromSlices();
}

// Volume constructor that loads images from a list of filenames
Volume::Volume(const std::vector<std::string>& filenames) : data(nullptr), width(0), height(0), depth(0), channels(0) {
    loadImagesFromFilenames(filenames);
    generate3DVolumeFromSlices();
}

// Volume constructor that Constructs an Volume object with given shape and use 0 to hold the position.
Volume::Volume(int width, int height, int depth, int channels) : data(nullptr), width(width), height(height), depth(depth), channels(channels) {
    size_t totalSize = static_cast<size_t>(width) * height * depth * channels;
    data = new unsigned char[totalSize];
    std::memset(data, 0, totalSize);
}

// Volume destructor
Volume::~Volume() {
    if (data) {
        stbi_image_free(data);
    }
}

// Move constructor for Volume class
Volume::Volume(Volume&& other) noexcept : slices(std::move(other.slices)), data(other.data), width(other.width), height(other.height), depth(other.depth), channels(other.channels) {
    other.data = nullptr;
    other.width = 0;
    other.height = 0;
    other.depth = 0;
    other.channels = 0;
}

// Move assignment operator for Volume class
Volume& Volume::operator=(Volume&& other) noexcept {
    if (this != &other) {
        slices = std::move(other.slices);
        stbi_image_free(data); // Free existing data
        data = other.data;
        width = other.width;
        height = other.height;
        depth = other.depth;
        channels = other.channels;
        other.data = nullptr;
        other.width = 0;
        other.height = 0;
        other.depth = 0;
        other.channels = 0;
    }
    return *this;
}

Volume::Volume(const Volume& other)
        : width(other.width), height(other.height), depth(other.depth), channels(other.channels) {
    // Copy the slices. Assuming Image has a copy constructor.
    slices.reserve(other.slices.size());
    for (const auto& slice : other.slices) {
        slices.push_back(std::make_shared<Image>(*slice));
    }

    // Deep copy of the raw volume data.
    size_t totalSize = static_cast<size_t>(width) * height * depth * channels;
    data = new unsigned char[totalSize];
    std::memcpy(data, other.data, totalSize);
}

// Load images from a folder path
void Volume::loadImagesFromFolder(const std::string& folderPath) {
    std::vector<std::string> imagePaths;
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        // check if the entry is ending with .png
        if (entry.path().extension() == ".png") {
            imagePaths.push_back(entry.path().string());
        }
    }
    loadImagesFromFilenames(imagePaths);
}

// Load images from a list of filenames
void Volume::loadImagesFromFilenames(const std::vector<std::string>& filenames) {
    std::vector<std::string> sortedFilenames = filenames;
    customSort(sortedFilenames);

    for (const auto& filename : sortedFilenames) {
        // print what file is being loaded
        std::cout << "Loading file:" << filename << std::endl;
        auto image = std::make_shared<Image>(filename);
        slices.push_back(image);
    }
}

// Generate 3D volume data from slices
void Volume::generate3DVolumeFromSlices() {
    if (slices.empty()) {
        throw std::runtime_error("Volume is empty, no slices to generate 3D data from.");
    }

    width = slices[0]->getWidth();
    height = slices[0]->getHeight();
    channels = slices[0]->getChannels();
    depth = static_cast<int>(slices.size());

    size_t singleImageSize = width * height * channels;
    size_t totalSize = singleImageSize * depth;
    data = new unsigned char[totalSize];
    for (size_t i = 0; i < slices.size(); ++i) {
        std::memcpy(data + i * singleImageSize, slices[i]->getData(), singleImageSize);
    }
}

// Get a slice of the volume at the specified index
//std::shared_ptr<Image> Volume::getSlice(int index) const {
//    if (index < 0 || index >= getDepth()) {
//        throw std::out_of_range("Slice index is out of range.");
//    }
//    return slices[index];
//}
std::shared_ptr<Image> Volume::getSlice(int index) const {
    if (index < 0 || index >= getDepth()) {
        throw std::out_of_range("Slice index is out of range.");
    }

    size_t singleSliceSize = static_cast<size_t>(width) * height * channels;
    const unsigned char* sliceData = data + index * singleSliceSize;

    // Create a new Image object for the slice
    auto sliceImage = std::make_shared<Image>(width, height, channels, sliceData);
    return sliceImage;
}

std::unique_ptr<Slice> Volume::getSliceXZ(int y) const {
    if (y < 0 || y >= height) {
        throw std::out_of_range("Y coordinate out of range.");
    }

    auto sliceData = std::make_unique<unsigned char[]>(width * depth * channels);
    for (int z = 0; z < depth; ++z) {
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < channels; ++c) {
                int volIndex = ((z * height + y) * width + x) * channels + c;
                int sliceIndex = (z * width + x) * channels + c;
                sliceData[sliceIndex] = data[volIndex];
            }
        }
    }
    return std::make_unique<Slice>(width, depth, channels, std::move(sliceData));
}

std::unique_ptr<Slice> Volume::getSliceYZ(int x) const {
    if (x < 0 || x >= width) {
        throw std::out_of_range("X coordinate out of range.");
    }

    auto sliceData = std::make_unique<unsigned char[]>(height * depth * channels);
    for (int z = 0; z < depth; ++z) {
        for (int y = 0; y < height; ++y) {
            for (int c = 0; c < channels; ++c) {
                int volIndex = ((z * height + y) * width + x) * channels + c;
                int sliceIndex = (z * height + y) * channels + c;
                sliceData[sliceIndex] = data[volIndex];
            }
        }
    }
    return std::make_unique<Slice>(height, depth, channels, std::move(sliceData));
}

void Volume::setVoxel(int x, int y, int z, int channel, unsigned char value) {
    if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth || channel < 0 || channel >= channels) {
        throw std::out_of_range("Voxel coordinates or channel out of range.");
    }

    int index = ((z * height + y) * width + x) * channels + channel;
    data[index] = value;
}

unsigned char Volume::getVoxel(int x, int y, int z, int channel) const {
    if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth || channel < 0 || channel >= channels) {
        throw std::out_of_range("Voxel coordinates or channel out of range.");
    }

    int index = ((z * height + y) * width + x) * channels + channel;
    return data[index];
}


// Save a slice of the volume to a file
unsigned char* Volume::getVolumeData() const {
    return data;
}

// Get the width of the volume
int Volume::getWidth() const {
    return width;
}

// Get the height of the volume
int Volume::getHeight() const {
    return height;
}

// Get the depth of the volume
int Volume::getDepth() const {
    return depth;
}

// Get the number of channels in the volume
int Volume::getChannels() const {
    return channels;
}