/**
 * @file Volume.h
 * @brief Declaration of the Volume class.
 *
 * The Volume class encapsulates a three-dimensional volume data, constructed from a series of two-dimensional image slices.
 * It offers functionality to load image slices from a directory or a list of filenames, access individual slices or voxels,
 * modify voxel values, and retrieve properties of the volume such as dimensions and pixel data. Additionally, a Volume can be
 * directly constructed with specified dimensions and channel count, with voxel values initialized to zero.
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
 */

#ifndef ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_VOLUME_H
#define ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_VOLUME_H

#include "Image.h"
#include "Slice.h"
#include <vector>
#include <string>
#include <memory>
#include <filesystem>
#include <stdexcept>
#include <algorithm>
#include <regex>

namespace fs = std::filesystem;

/**
 * @class Volume
 * @brief Manages a 3D volume constructed from 2D image slices.
 *
 * A Volume object holds the data for a 3D volume, including its width, height, depth, and the number of channels (e.g., RGB channels).
 * It allows for the modification of voxel values within the volume, accessing individual slices, and constructing new volumes with
 * specified dimensions. The class supports loading volume data from image files stored in a directory or specified via a list of filenames.
 *
 */
class Volume {
public:
    /**
     * @brief Constructs a Volume object from a folder path.
     * @param folderPath A std::string representing the path to the folder containing image slices.
     */
    explicit Volume(const std::string& folderPath);

    /**
     * @brief Constructs a Volume object from a list of filenames.
     * @param filenames A std::vector<std::string> containing the file names of the image slices.
     */
    explicit Volume(const std::vector<std::string>& filenames);

    /**
     @brief Constructs a Volume object with specified dimensions and initializes voxel values to zero.
     * @param width Width of the volume in pixels.
     * @param height Height of the volume in pixels.
     * @param depth Number of slices in the volume.
     * @param channels Number of color channels per voxel.
     */
    explicit Volume(int width, int height, int depth, int channels);

    /**
     * @brief Move constructor, transfers ownership of resources from another Volume object.
     * @param other The Volume object to move from.
     */
    Volume(Volume&& other) noexcept;

    /**
     * @brief Copy constructor, creates a deep copy of another Volume object.
     * @param other Another Volume object to copy from.
     */
    Volume(const Volume& other);

    /**
     * @brief Move assignment operator, transfers ownership of resources from another Volume object.
     * @param other Another Volume object to assign from.
     * @return A reference to this Volume object.
     */
    Volume& operator=(Volume&& other) noexcept;

    /**
     * @brief Destructor, cleans up allocated resources.
     */
    ~Volume();

    /**
     * @brief Deleted copy assignment operator to prevent copying.
     */
    Volume& operator=(const Volume&) = delete;

    /**
     * @brief Sets the value of a specific voxel in the volume.
     * @param x The x-coordinate of the voxel.
     * @param y The y-coordinate of the voxel.
     * @param z The z-coordinate of the voxel.
     * @param channel The color channel of the voxel.
     * @param value The value to set the voxel to.
     */
    void setVoxel(int x, int y, int z, int channel, unsigned char value);

    /**
     * @brief Retrieves the value of a specific voxel in the volume.
     * @param x The x-coordinate of the voxel.
     * @param y The y-coordinate of the voxel.
     * @param z The z-coordinate of the voxel.
     * @param channel The color channel of the voxel.
     * @return The value of the voxel.
     */
    [[nodiscard]] unsigned char getVoxel(int x, int y, int z, int channel) const;

    /**
     * @brief Retrieves a slice of the volume at a specified index.
     * @param index The index of the slice to retrieve.
     * @return A std::shared_ptr<Image> pointing to the image slice.
     */
    [[nodiscard]] std::shared_ptr<Image> getSlice(int index) const;

    /**
     @brief Retrieves a slice of the volume along the XZ plane at a specified position.
     * @param y The position of the slice in the y-axis.
     * @return Unique pointer to
     */
    [[nodiscard]] std::unique_ptr<Slice> getSliceXZ(int y) const;

    /**
     @brief Retrieves a slice of the volume along the YZ plane at a specified position.
     * @param x The position of the slice in the x-axis.
     * @return Unique pointer to
     */
    [[nodiscard]] std::unique_ptr<Slice> getSliceYZ(int x) const;

    /**
     * @brief Retrieves the raw data of the entire volume.
     * @return Pointer to the raw volume data.
     */
    [[nodiscard]] unsigned char* getVolumeData() const;

    /**
     * @brief Returns the width of the volume.
     * @return The width of the volume in pixels.
     */
    [[nodiscard]] int getWidth() const;

    /**
     * @brief Returns the height of the volume.
     * @return The height of the volume in pixels.
     */
    [[nodiscard]] int getHeight() const;

    /**
     * @brief Returns the number of slices (depth) of the volume.
     * @return The number of slices in the volume.
     */
    [[nodiscard]] int getDepth() const;

    /**
     * @brief Returns the number of color channels per voxel in the volume.
     * @return The number of channels per pixel.
     */
    [[nodiscard]] int getChannels() const;

private:
    std::vector<std::shared_ptr<Image>> slices; ///< Stores the volume's image slices.
    unsigned char* data; ///< Pointer to the raw volume data.
    int width, height, depth, channels; ///< Volume dimensions and number of channels.

    void loadImagesFromFolder(const std::string& folderPath);///< Load images from a folder.
    void loadImagesFromFilenames(const std::vector<std::string>& filenames);///< Load images from a list of filenames.
    void generate3DVolumeFromSlices();///< Generate 3D volume data from slices.
};

#endif //ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_VOLUME_H
