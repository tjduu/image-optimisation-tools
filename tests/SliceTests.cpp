//
// Created by Zhang, Xiaoye on 21/03/2024.
//

#include "SliceTests.h"
#include "Slice.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <filesystem>
#include <string>
namespace fs = std::filesystem;

void SliceTests::testSliceCreation() {
    int width = 10, height = 10, channels = 3;
    auto data = std::make_unique<unsigned char[]>(width * height * channels);
    Slice slice(width, height, channels, std::move(data));

    assert(slice.getWidth() == width);
    assert(slice.getHeight() == height);
    assert(slice.getChannels() == channels);
    std::cout << "testSliceCreation passed." << std::endl;
}

void SliceTests::testSlicePixelManipulation() {
    int width = 2, height = 2, channels = 1;
    auto data = std::make_unique<unsigned char[]>(width * height * channels);
    Slice slice(width, height, channels, std::move(data));

    unsigned char value = 128;
    slice.setPixel(0, 0, 0, value);
    assert(slice.getPixel(0, 0, 0) == value);
    std::cout << "testSlicePixelManipulation passed." << std::endl;
}

void SliceTests::testSliceSave() {
    int width = 10, height = 10, channels = 3;
    auto rawData = new unsigned char[width * height * channels];
    std::fill(rawData, rawData + width * height * channels, 0); // 初始化数据为0

    // 使用原始指针创建unique_ptr
    std::unique_ptr<unsigned char[]> data(rawData);
    Slice slice(width, height, channels, std::move(data));

    std::string filename = "../../tests/slice_test.png";
    bool saveResult = slice.save(filename);

    // 使用filesystem检查文件是否存在
    bool fileExists = std::filesystem::exists(filename);

    // 清理：删除测试文件
    if (fileExists) {
        std::filesystem::remove(filename);
    }

    if (!saveResult || !fileExists) {
        std::cerr << "testSliceSave failed." << std::endl;
    } else {
        std::cout << "testSliceSave passed." << std::endl;
    }
}