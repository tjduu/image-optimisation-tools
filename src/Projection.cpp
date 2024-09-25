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

#include "Projection.h"

// Function to generate Maximum Intensity Projection (MIP) from a 3D volume
Image Projection::maximumIntensityProjection(const Volume& volume, int z_start, int z_end){
    // Get dimensions of the volume
    int width = volume.getWidth();
    int height = volume.getHeight();
    
    // Create a new image for the maximum intensity projection
    Image outputImg(width, height, 1);

    // Determine the range of slices to iterate over
    int startZ = (z_start == -1) ? 0 : z_start - 1;
    int endZ = (z_end == -1) ? volume.getDepth() : z_end;

    // Iterate through each pixel in the output image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char maxIntensity = 0; // Initialize max intensity
            
            // Iterate through each slice in the volume
            for (int z = startZ; z < endZ; ++z) {
                // Get intensity value at (x, y) in the current slice
                unsigned char intensity = volume.getVoxel(x, y, z, 0);
                // Update max intensity if current intensity is greater
                maxIntensity = std::max(maxIntensity, intensity);
            }

            // Set the maximum intensity value at (x, y) in the output image
            outputImg.setPixel(x, y, 0, maxIntensity);
        }
    }

    return outputImg;
}

// Function to generate Minimum Intensity Projection (mIP) from a 3D volume
Image Projection::minimumIntensityProjection(const Volume& volume, int z_start, int z_end){
    // Get dimensions of the volume
    int width = volume.getWidth();
    int height = volume.getHeight();
    
    // Create a new image for the minimum intensity projection
    Image mipImage(width, height, 1);

    // Determine the range of slices to iterate over
    int startZ = (z_start == -1) ? 0 : z_start - 1;
    int endZ = (z_end == -1) ? volume.getDepth() : z_end;

    // Iterate through each pixel in the output image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char minIntensity = 255; // Initialize min intensity to maximum value
            
            // Iterate through each slice in the volume
            for (int z = startZ; z < endZ; ++z) {
                // Get intensity value at (x, y) in the current slice
                unsigned char intensity = volume.getVoxel(x, y, z, 0);
                // Update min intensity if current intensity is smaller
                minIntensity = std::min(minIntensity, intensity);
            }

            // Set the minimum intensity value at (x, y) in the output image
            mipImage.setPixel(x, y, 0, minIntensity);
        }
    }

    return mipImage;
}

// Function to generate Average Intensity Projection (AIP) from a 3D volume
Image Projection::averageIntensityProjection(const Volume& volume, int z_start, int z_end){
    // Get dimensions of the volume
    int width = volume.getWidth();
    int height = volume.getHeight();
    
    // Create a new image for the average intensity projection
    Image mipImage(width, height, 1);

    // Determine the range of slices to iterate over
    int startZ = (z_start == -1) ? 0 : z_start - 1;
    int endZ = (z_end == -1) ? volume.getDepth() : z_end;

    // Iterate through each pixel in the output image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int sumIntensity = 0; // Initialize sum intensity to 0
            
            // Iterate through each slice in the volume
            for (int z = startZ; z < endZ; ++z) {
                // Get intensity value at (x, y) in the current slice
                unsigned char intensity = volume.getVoxel(x, y, z, 0);
                // Update sum intensity
                sumIntensity += intensity;
            }

            // Calculate z range
            int zRange = endZ - startZ;

            // Calculate average intensity
            unsigned char averageIntensity = sumIntensity / zRange;

            // Set the average intensity value at (x, y) in the output image
            mipImage.setPixel(x, y, 0, averageIntensity);
        }
    }

    return mipImage;
}

// Function to swap two elements
void Projection::swap(unsigned char& a, unsigned char& b) {
    unsigned char temp = a;
    a = b;
    b = temp;
}

// Function to sort the array using partitioning
int Projection::partition(unsigned char* arr, int low, int high) {
    // Choose the pivot element
    unsigned char pivot = arr[high];
    int i = low - 1;

    // Partition the array
    for (int j = low; j < high; ++j) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    // Swap the pivot element with the element at the partition index
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Function to sort the array using QuickSort
void Projection::quickSort(unsigned char* arr, int low, int high) {
    // Recursively sort the array
    if (low < high) {
        // Find the partition index
        int pivot = partition(arr, low, high);
        // Sort the elements before and after the partition index
        quickSort(arr, low, pivot - 1);
        // Sort the elements after the partition index
        quickSort(arr, pivot + 1, high);
    }
}

// Function to check depth of the volume and choose the correct median intensity projection function
Image Projection::medianIntensityProjection(const Volume& volume, int z_start, int z_end) {
    // Get the depth of the volume
    int depth = volume.getDepth();

    // Check if the depth is less than 100
    if (depth < 500) {
        return medianIntensityProjection_quickSort(volume, z_start, z_end);
    } else {
        return medianIntensityProjection_histogram(volume, z_start, z_end);
    }
}

// Function to calculate median intensity projection
Image Projection::medianIntensityProjection_quickSort(const Volume& volume, int z_start, int z_end) {
    // Get dimensions of the volume
    int width = volume.getWidth();
    int height = volume.getHeight();

    // Create a new image for the median intensity projection
    Image mipImage(width, height, 1);

    // Determine the range of slices to iterate over
    int startZ = (z_start == -1) ? 0 : z_start - 1;
    int endZ = (z_end == -1) ? volume.getDepth() : z_end;

    // Iterate through each pixel in the output image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int bufferSize = endZ - startZ; // Number of elements in the buffer
            auto* intensityBuffer = new unsigned char[bufferSize]; // Allocate memory for the intensity buffer

            // Fill the intensity buffer with intensity values from the volume
            for (int z = startZ; z < endZ; ++z) {
                intensityBuffer[z - startZ] = volume.getVoxel(x, y, z, 0);
            }

            // Sort the intensity buffer using QuickSort
            quickSort(intensityBuffer, 0, bufferSize - 1);

            // Find the median intensity value
            unsigned char medianIntensity;
            // Check if the number of elements is even or odd
            if (bufferSize % 2 == 0) {
                medianIntensity = (intensityBuffer[bufferSize / 2 - 1] + intensityBuffer[bufferSize / 2]) / 2;
            } else {
                medianIntensity = intensityBuffer[bufferSize / 2];
            }

            // Set the median intensity value at (x, y) in the output image
            mipImage.setPixel(x, y, 0, medianIntensity);

            // Deallocate memory for the intensity buffer
            delete[] intensityBuffer;
        }
    }

    return mipImage;
}

Image Projection::medianIntensityProjection_histogram(const Volume& volume, int z_start, int z_end) {
    int width = volume.getWidth();
    int height = volume.getHeight();

    Image mipImage(width, height, 1);

    int startZ = (z_start == -1) ? 0 : z_start - 1;
    int endZ = (z_end == -1) ? volume.getDepth() : z_end;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::vector<int> histogram(256, 0); // Histogram for intensity values

            // Fill the histogram with intensity values for the current pixel
            for (int z = startZ; z < endZ; ++z) {
                unsigned char intensity = volume.getVoxel(x, y, z, 0);
                histogram[intensity]++;
            }

            // Find the median intensity value using the histogram
            int medianIndex = (endZ - startZ) / 2 + ((endZ - startZ) % 2);
            unsigned char medianIntensity = 0;
            int count = 0;
            for (int i = 0; i < 256; ++i) {
                count += histogram[i];
                if (count >= medianIndex) {
                    medianIntensity = i;
                    // Check if the number of slices is even
                    if ((endZ - startZ) % 2 == 0) {
                        // Check if the next intensity value is the same
                        if (histogram[i] > 1 && count > medianIndex) {
                            medianIntensity = i;
                        } else {
                        // Find the next intensity value
                        while (histogram[++i] == 0);
                        medianIntensity = (medianIntensity + i) / 2;
                        }
                    }
                    break;
                }
            }

            mipImage.setPixel(x, y, 0, medianIntensity);
        }
    }

    return mipImage;
}
