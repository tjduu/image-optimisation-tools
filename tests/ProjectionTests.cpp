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

#include "ProjectionTests.h"
#include "../include/myproject/Projection.h"
#include "../include/myproject/Volume.h"
#include "../include/myproject/Image.h"

#include <iostream>
#include <cassert>
#include <filesystem>
#include <cstdlib>
#include <string>
#include <dirent.h>

// Function to generate Image object with random pixel values
Image ProjectionTests::generateRandomImage(int width, int height, int channels) {

    // Create an Image object with random pixel values
    Image img(width, height, channels);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < channels; ++c) {
                img.setPixel(x, y, c, rand() % 256);
            }
        }
    }
    return img;
}

// Function to compare two Image objects
bool ProjectionTests::compareImages(const Image& img1, const Image& img2, int tolerance) {
    // Check if dimensions match
    if (img1.getWidth() != img2.getWidth() || img1.getHeight() != img2.getHeight() || img1.getChannels() != img2.getChannels()) {
        return false;
    }

    // Iterate through each pixel and compare
    for (int y = 0; y < img1.getHeight(); ++y) {
        for (int x = 0; x < img1.getWidth(); ++x) {
            for (int c = 0; c < img1.getChannels(); ++c) {
                // Compare pixel values with tolerance
                if (std::abs(img1.getPixel(x, y, c) - img2.getPixel(x, y, c)) > tolerance) {
                    return false; // Images are different
                }
            }
        }
    }

    return true; // Images are the same within tolerance
}

// Function used to test the calculateHistogramEqualization function
void ProjectionTests::selectionSort(std::vector<unsigned char>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            // Swap arr[i] and arr[minIndex]
            unsigned char temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

// Function to list files in a directory
std::vector<std::string> listFilesInDirectory(const std::string& directoryPath) {
    std::vector<std::string> filenames;
    DIR *dir;
    struct dirent *entry;

    // Open directory
    dir = opendir(directoryPath.c_str());
    if (dir == nullptr) {
        std::cerr << "Error opening directory" << std::endl;
        return filenames;
    }

    // Read directory entries
    while ((entry = readdir(dir)) != nullptr) {
        // Filter out "." and ".." entries
        if (std::strcmp(entry->d_name, ".") != 0 && std::strcmp(entry->d_name, "..") != 0) {
            // Construct full path to file
            std::string filePath = directoryPath + "/" + entry->d_name;
            // Add file path to vector
            filenames.push_back(filePath);
        }
    }

    // Close directory
    closedir(dir);

    return filenames;
}

// Function to generate 10 random images and save them to a folder
Volume ProjectionTests::generateVolume() {
    // Seed the random number generator
    srand(42);

    // Create the folder if it doesn't exist
    std::string folderName = "./tests/test_images";
    std::string createDirCommand = "mkdir -p " + folderName; // Linux/macOS command
#ifdef _WIN32
    createDirCommand = "mkdir " + folderName; // Windows command
#endif
    system(createDirCommand.c_str());

    for (int i = 0; i < 10; ++i) {
        Image img = generateRandomImage(5, 5, 1);
        std::string filePath = folderName + "/image_" + std::to_string(i) + ".png";
        img.save(filePath);
    }

    // Get filenames for the test images
    std::string directoryPath = "../../tests/test_images/projection_test";
    std::vector<std::string> filenames = listFilesInDirectory(directoryPath);

    Volume volume(filenames);

    return volume;
}

void ProjectionTests::test_maximumIntensityProjection(const Volume& volume){

    // Test on entire volume
    Image mipImage = Projection::maximumIntensityProjection(volume, -1, -1);

    // Check if the output image has the correct dimensions
    assert(mipImage.getWidth() == volume.getWidth());
    assert(mipImage.getHeight() == volume.getHeight());
    assert(mipImage.getChannels() == volume.getChannels());

    // Check if the maximum intensity values are correct
    // Known as the seed is set and manually calculated and checked
    std::vector<unsigned char> maxIntensities = {240, 241, 248, 241, 252,
                                                 241, 237, 241, 215, 247,
                                                 248, 251, 251, 248, 231,
                                                 250, 246, 225, 243, 235,
                                                 246, 227, 244, 225, 241};

    // Generate a 5x5 image with the maximum intensity values
    Image expectedMIP(5, 5, 1);
    for (int y = 0; y < expectedMIP.getHeight(); ++y) {
        for (int x = 0; x < expectedMIP.getWidth(); ++x) {
            expectedMIP.setPixel(x, y, 0, maxIntensities[y * expectedMIP.getWidth() + x]);
        }
    }

    // Check if the output image is correct
    int tolerance = 1;
    assert(compareImages(mipImage, expectedMIP, tolerance));

    // Check if z_start and z_end work
    Image mipImage2 = Projection::maximumIntensityProjection(volume, 4, 7);

    // Check if the output image has the correct dimensions
    assert(mipImage2.getWidth() == volume.getWidth());
    assert(mipImage2.getHeight() == volume.getHeight());
    assert(mipImage2.getChannels() == volume.getChannels());

    // Check values
    std::vector<unsigned char> maxIntensities2 = {240, 113, 94, 241, 178, 
                                                148, 152, 241, 159, 217, 
                                                141, 251, 166, 248, 217, 
                                                135, 246, 182, 231, 225, 
                                                123, 227, 215, 225, 180 };

    // Generate a 5x5 image with the maximum intensity values
    Image expectedMIP2(5, 5, 1);
    for (int y = 0; y < expectedMIP2.getHeight(); ++y) {
        for (int x = 0; x < expectedMIP2.getWidth(); ++x) {
            expectedMIP2.setPixel(x, y, 0, maxIntensities2[y * expectedMIP2.getWidth() + x]);
        }
    }

    assert(compareImages(mipImage2, expectedMIP2, tolerance));

    std::cout << "maximumIntensityProjection tests passed successfully!" << std::endl;
}

void ProjectionTests::test_minimumIntensityProjection(const Volume& volume){

    // Test on entire volume
    Image mipImage = Projection::minimumIntensityProjection(volume, -1, -1);

    // Check if the output image has the correct dimensions
    assert(mipImage.getWidth() == volume.getWidth());
    assert(mipImage.getHeight() == volume.getHeight());
    assert(mipImage.getChannels() == volume.getChannels());

    // Check if the minimum intensity values are correct
    // Known as the seed is set and manually calculated and checked
    std::vector<unsigned char> minIntensities = {57, 27, 20, 17, 36,
                                                 9, 1, 82, 9, 12,
                                                 7, 7, 3, 31, 32,
                                                 34, 27, 29, 19, 25,
                                                 3, 0, 1, 11, 0};

    // Generate a 5x5 image with the minimum intensity values
    Image expectedMIP(5, 5, 1);
    for (int y = 0; y < expectedMIP.getHeight(); ++y) {
        for (int x = 0; x < expectedMIP.getWidth(); ++x) {
            expectedMIP.setPixel(x, y, 0, minIntensities[y * expectedMIP.getWidth() + x]);
        }
    }

    // Check if the output image is correct
    int tolerance = 1;
    assert(compareImages(mipImage, expectedMIP, tolerance));

    // Test for a subset of the volume
    Image mipImage2 = Projection::minimumIntensityProjection(volume, 4, 7);

    // Check if the output image has the correct dimensions
    assert(mipImage2.getWidth() == volume.getWidth());
    assert(mipImage2.getHeight() == volume.getHeight());
    assert(mipImage2.getChannels() == volume.getChannels());

    // Check if the minimum intensity values are correct
    // Known as the seed is set and manually calculated and checked
    std::vector<unsigned char> minIntensities2 = {67, 27, 20, 65, 36, 
                                                9, 52, 82, 32, 12, 
                                                7, 51, 58, 34, 84, 
                                                34, 120, 79, 19, 25, 
                                                3, 84, 1, 11, 0 };

    // Generate a 5x5 image with the minimum intensity values
    Image expectedMIP2(5, 5, 1);
    for (int y = 0; y < expectedMIP2.getHeight(); ++y) {
        for (int x = 0; x < expectedMIP2.getWidth(); ++x) {
            expectedMIP2.setPixel(x, y, 0, minIntensities2[y * expectedMIP2.getWidth() + x]);
        }
    }

    // Check if the output image is correct
    assert(compareImages(mipImage2, expectedMIP2, tolerance));

    std::cout << "minimumIntensityProjection tests passed successfully!" << std::endl;

}

void ProjectionTests::test_averageIntensityProjection(const Volume& volume){

    // Get original volume
    const Volume& originalVolume = volume;

    // Get the size of the volume
    int width = originalVolume.getWidth();
    int height = originalVolume.getHeight();
    int numChannels = originalVolume.getChannels();

    // Test on entire volume
    Image aipImage = Projection::averageIntensityProjection(volume, -1, -1);

    // Check if the output image has the correct dimensions
    assert(aipImage.getWidth() == volume.getWidth());
    assert(aipImage.getHeight() == volume.getHeight());
    assert(aipImage.getChannels() == volume.getChannels());

    // Check if the average intensity values are correct
    // Known as the seed is set and manually calculated and checked
    std::vector<unsigned char> avgIntensities = {125, 121, 129, 131, 122,
                                                 118, 106, 165, 106, 112,
                                                 163, 129, 104, 115, 146,
                                                 123, 148, 143, 118, 158,
                                                 76, 108, 107, 126, 104};

    // Generate a 5x5 image with the average intensity values
    Image expectedAIP(5, 5, 1);
    for (int y = 0; y < expectedAIP.getHeight(); ++y) {
        for (int x = 0; x < expectedAIP.getWidth(); ++x) {
            expectedAIP.setPixel(x, y, 0, avgIntensities[y * expectedAIP.getWidth() + x]);
        }
    }

    // Check if the output image is correct
    int tolerance = 1;
    assert(compareImages(aipImage, expectedAIP, tolerance));

    // Test for a subset of the volume
    Image aipImage2 = Projection::averageIntensityProjection(volume, 4, 7);

    // Check if the output image has the correct dimensions
    assert(aipImage2.getWidth() == volume.getWidth());
    assert(aipImage2.getHeight() == volume.getHeight());
    assert(aipImage2.getChannels() == volume.getChannels());

    // Check if the maximum intensity values are correct
    // Known as the seed is set and manually calculated and checked
    std::vector<unsigned char> avgIntensities2 = {163, 62, 59, 176, 103, 
                                                73, 107, 160, 99, 68, 
                                                103, 159, 105, 152, 158, 
                                                101, 207, 146, 118, 135, 
                                                51, 142, 113, 124, 87 };

    // Generate a 5x5 image with the maximum intensity values
    Image expectedAIP2(5, 5, 1);
    for (int y = 0; y < expectedAIP2.getHeight(); ++y) {
        for (int x = 0; x < expectedAIP2.getWidth(); ++x) {
            expectedAIP2.setPixel(x, y, 0, avgIntensities2[y * expectedAIP2.getWidth() + x]);
        }
    }

    // Check if the output image is correct
    assert(compareImages(aipImage2, expectedAIP2, tolerance));

    std::cout << "averageIntensityProjection tests passed successfully!" << std::endl;
}

// Helper Function tests
void ProjectionTests::test_swap() {
    unsigned char a = 5, b = 10;
    Projection::swap(a, b);
    assert(a == 10 && b == 5);

    std::cout << "swap tests passed successfully!" << std::endl;
}

void ProjectionTests::test_partition() {
    unsigned char arr[] = {3, 7, 1, 5, 9, 2, 8, 4, 6};
    int partitionIndex = Projection::partition(arr, 0, 8);
    for (int i = 0; i < partitionIndex; ++i) {
        assert(arr[i] <= arr[partitionIndex]);
    }
    for (int i = partitionIndex + 1; i < 9; ++i) {
        assert(arr[i] > arr[partitionIndex]);
    }

    std::cout << "partition tests passed successfully!" << std::endl;
}

void ProjectionTests::test_quickSort() {
    unsigned char arr[] = {3, 7, 1, 5, 9, 2, 8, 4, 6};
    Projection::quickSort(arr, 0, 8);
    for (int i = 0; i < 8; ++i) {
        assert(arr[i] <= arr[i + 1]);
    }

    std::cout << "quickSort tests passed successfully!" << std::endl;
}

void ProjectionTests::test_medianIntensityProjection(const Volume& volume){
    // Get original volume
    const Volume& originalVolume = volume;

    // Get the size of the volume
    int width = originalVolume.getWidth();
    int height = originalVolume.getHeight();
    int numChannels = originalVolume.getChannels();

    // Test on entire volume
    Image aipImage = Projection::medianIntensityProjection_quickSort(volume, -1, -1);
    Image aipImage4 = Projection::medianIntensityProjection_histogram(volume, -1, -1);

    // Check if the output image has the correct dimensions
    assert(aipImage.getWidth() == volume.getWidth());
    assert(aipImage.getHeight() == volume.getHeight());
    assert(aipImage.getChannels() == volume.getChannels());
    assert(aipImage4.getWidth() == volume.getWidth());
    assert(aipImage4.getHeight() == volume.getHeight());
    assert(aipImage4.getChannels() == volume.getChannels());

    // Check if the average intensity values are correct
    // Known as the seed is set and manually calculated and checked
    std::vector<unsigned char> avgIntensities = {104, 95, 117, 157, 121,
                                                 126, 98, 160, 104, 45,
                                                 174, 141, 76, 97, 149,
                                                 118, 145, 147, 103, 160,
                                                 50, 97, 93, 120, 93 };

    // Generate a 5x5 image with the average intensity values
    Image expectedAIP(5, 5, 1);
    for (int y = 0; y < expectedAIP.getHeight(); ++y) {
        for (int x = 0; x < expectedAIP.getWidth(); ++x) {
            expectedAIP.setPixel(x, y, 0, avgIntensities[y * expectedAIP.getWidth() + x]);
        }
    }

    // Check if the output image is correct
    int tolerance = 1;
    assert(compareImages(aipImage, expectedAIP, tolerance));
    assert(compareImages(aipImage4, expectedAIP, tolerance));

    // Test on an even number of slices
    Image aipImage2 = Projection::medianIntensityProjection_quickSort(volume, 4, 8);
    Image aipImage3 = Projection::medianIntensityProjection_histogram(volume, 4, 8);

    // Check if the output image has the correct dimensions
    assert(aipImage2.getWidth() == volume.getWidth());
    assert(aipImage2.getHeight() == volume.getHeight());
    assert(aipImage2.getChannels() == volume.getChannels());
    assert(aipImage3.getWidth() == volume.getWidth());
    assert(aipImage3.getHeight() == volume.getHeight());
    assert(aipImage3.getChannels() == volume.getChannels());

    // Check if the average intensity values are correct
    // Known as the seed is set and manually calculated and checked
    std::vector<unsigned char> avgIntensities2 = {124, 62, 84, 186, 57, 
                                                25, 83, 169, 103, 31, 
                                                139, 114, 95, 105, 171, 
                                                109, 232, 148, 147, 139, 
                                                50, 111, 115, 172, 48 };

    // Generate a 5x5 image with the average intensity values
    Image expectedAIP2(5, 5, 1);
    for (int y = 0; y < expectedAIP2.getHeight(); ++y) {
        for (int x = 0; x < expectedAIP2.getWidth(); ++x) {
            expectedAIP2.setPixel(x, y, 0, avgIntensities2[y * expectedAIP2.getWidth() + x]);
        }
    }

    // Check if the output image is correct
    assert(compareImages(aipImage2, expectedAIP2, tolerance));
    assert(compareImages(aipImage3, expectedAIP2, tolerance));

    std::cout << "medianIntensityProjection tests passed successfully!" << std::endl;

}
