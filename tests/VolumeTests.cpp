//
// Created by Zhang, Xiaoye on 21/03/2024.
//

#include "VolumeTests.h"
#include "Volume.h"
#include <cassert>
#include <iostream>
#include <vector>

void VolumeTests::testVolumeCreationFromFolder() {
    // use a real folder path to test volume creation
    std::string folderPath = "../../tests/test_images";
    Volume volume(folderPath);

    assert(volume.getDepth() > 0);
    std::cout << "testVolumeCreationFromFolder passed." << std::endl;
}

void VolumeTests::testVolumeCreationFromFilenames() {
    // This test requires real image file paths.
    std::vector<std::string> filenames = {"../../tests/test_images/image_0.png", "../../tests/test_images/image_2.png"};
    Volume volume(filenames);

    assert(volume.getDepth() == filenames.size());
    std::cout << "testVolumeCreationFromFilenames passed." << std::endl;
}

void VolumeTests::testVolumeSliceAccess() {
    // use a real folder path to test volume creation
    std::string folderPath = "../../tests/test_images";
    Volume volume(folderPath);

    auto slice = volume.getSlice(0);
    assert(slice != nullptr);
    std::cout << "testVolumeSliceAccess passed." << std::endl;
}