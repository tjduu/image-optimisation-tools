/**
 * @file Slice.h
 * @brief Declaration of the Slice class for managing 2D slices extracted from 3D volumes.
 *
 * The Slice class encapsulates a two-dimensional slice extracted from a three-dimensional volume, including its dimensions,
 * pixel data, and the number of channels per pixel. It provides functionality for accessing and modifying pixel values,
 * and saving the slice as a PNG file.
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

#ifndef ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_SLICE_H
#define ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_SLICE_H
#include <memory>
#include <string>

/**
 * @class Slice
 * @brief Represents a 2D slice extracted from a 3D volume.
 */
class Slice {
public:
    /**
     * @brief Constructs a Slice with specified dimensions and data.
     * @param width The width of the slice.
     * @param height The height of the slice.
     * @param channels The number of channels per pixel.
     * @param data The pixel data for the slice.
     */
    Slice(int width, int height, int channels, std::unique_ptr<unsigned char[]> data);

    /**
     * @brief Copy constructor, creates a deep copy of another Slice object.
     * @param other The Slice object to copy from.
     */
    Slice(const Slice& other);

    /**
     * @brief Move constructor, transfers ownership of data from another Slice object.
     * @param other The Slice object to move from.
     */
    Slice(Slice&& other) noexcept;

    /**
     * @brief Saves the slice as a PNG file to the specified path.
     * @param filename Path to the file where the slice will be saved.
     * @return true if the slice was successfully saved; false otherwise.
     */
    [[nodiscard]] bool save(const std::string& filename) const;

    /**
     * @brief Returns the width of the slice.
     * @return Width in pixels.
     */
    [[nodiscard]] int getWidth() const;

    /**
     * @brief Returns the height of the slice.
     * @return Height in pixels.
     */
    [[nodiscard]] int getHeight() const;

    /**
     * @brief Returns the number of color channels in the slice.
     * @return Number of channels.
     */
    [[nodiscard]] int getChannels() const;

    /**
     * @brief Gets the intensity value of a pixel at the specified location and channel.
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @param channel The channel index of the pixel.
     * @return The intensity value of the pixel at (x, y) in the specified channel.
     */
    [[nodiscard]] unsigned char getPixel(int x, int y, int channel) const;

    /**
     * @brief Sets the intensity value of a pixel at the specified location and channel.
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @param channel The channel index of the pixel.
     * @param value The new intensity value for the pixel at (x, y) in the specified channel.
     */
    void setPixel(int x, int y, int channel, unsigned char value);

private:
    int width, height, channels;///< Dimensions of the slice and number of channels per pixel.
    std::unique_ptr<unsigned char[]> data;///< Pixel data for the slice.
};

#endif //ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_SLICE_H
