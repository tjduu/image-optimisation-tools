//
// Created by Zhang, Xiaoye on 22/03/2024.
//

#include "ImageTests.h"
#include "Image.h"
#include <cassert>
#include <iostream>

void ImageTests::testImageCreationFromDimensions() {
    Image img(10, 10, 3);
    assert(img.getWidth() == 10 && img.getHeight() == 10 && img.getChannels() == 3);
    std::cout << "testImageCreationFromDimensions passed." << std::endl;
}

void ImageTests::testImageCopy() {
    Image original(10, 10, 3);
    Image copy = original;
    assert(copy.getWidth() == original.getWidth() && copy.getHeight() == original.getHeight() && copy.getChannels() == original.getChannels());
    std::cout << "testImageCopy passed." << std::endl;
}

void ImageTests::testPixelManipulation() {
    Image img(10, 10, 1);
    img.setPixel(5, 5, 0, 255);
    assert(img.getPixel(5, 5, 0) == 255);
    std::cout << "testPixelManipulation passed." << std::endl;
}

void ImageTests::testImageSave() {
    Image img(10, 10, 1);
    img.setPixel(5, 5, 0, 255); // Modify an arbitrary pixel
    try {
        img.save("test_save.png");
        std::cout << "testImageSave passed." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "testImageSave failed: " << e.what() << std::endl;
    }
}


