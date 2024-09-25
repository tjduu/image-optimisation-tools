//
// Created by Zhang, Xiaoye on 22/03/2024.
//
#include "Volume.h"
#include "Projection.h"
#include "ProjectionTests.h"
#include "ImageTests.h"
#include "FilterTests.h"
#include "VolumeTests.h"
#include "SliceTests.h"
#include "SpeedTests.h"


int main(){
    std::cout << "Running tests..." << std::endl;

    // Image
    std::cout << "Image tests..." << std::endl;
    ImageTests::testImageCreationFromDimensions();
    ImageTests::testImageCopy();
    ImageTests::testPixelManipulation();
    ImageTests::testImageSave();
    std::cout << "Image tests passed." << std::endl;

    // Slice
    std::cout << "Slice tests..." << std::endl;
    SliceTests::testSliceCreation();
    SliceTests::testSlicePixelManipulation();
    SliceTests::testSliceSave();
    std::cout << "Slice tests passed." << std::endl;

    // Volume
    std::cout << "Volume tests..." << std::endl;
    VolumeTests::testVolumeCreationFromFolder();
    VolumeTests::testVolumeCreationFromFilenames();
    VolumeTests::testVolumeSliceAccess();
    std::cout << "Volume tests passed." << std::endl;

    // Projection
    std::cout << "Projection tests..." << std::endl;
    // Generate volume for testing and save them to a folder
    Volume volume = ProjectionTests::generateVolume();

    // Test projections and helper functions
    ProjectionTests::test_maximumIntensityProjection(volume);
    ProjectionTests::test_minimumIntensityProjection(volume);
    ProjectionTests::test_averageIntensityProjection(volume);
    ProjectionTests::test_medianIntensityProjection(volume);
    // Helper function tests
    ProjectionTests::test_swap();
    ProjectionTests::test_partition();
    ProjectionTests::test_quickSort();
    std::cout << "Projection tests passed." << std::endl;

    // Filter
    std::cout << "Filter tests..." << std::endl;
    FilterTests::testMedianBlur();
    FilterTests::testBoxBlur();
    FilterTests::testGaussianBlur();
    FilterTests::testGrayScale();
    FilterTests::testSetBrightness();
    FilterTests::test_setBrightness();
    FilterTests::test_setBrightness_auto();
    FilterTests::test_setBrightness_manual();
    FilterTests::testSaltAndPepper();
    FilterTests::test_salt_and_pepper();
    FilterTests::testThreshold();
    FilterTests::test_threshold();
    FilterTests::test_rgb_to_hsv();
    FilterTests::test_hsv_to_rgb();
    FilterTests::test_rgb_to_hsl();
    FilterTests::test_hsl_to_rgb();
    FilterTests::testHistogramEqualization();
    FilterTests::test_histogramEqualization();
    FilterTests::test_calculateHistogramEqualization();
    FilterTests::testApplySobelOperator();
    FilterTests::testApplyPrewittOperator();
    FilterTests::testApplyScharrOperator();
    FilterTests::testApplyRobertsCrossOperator();
    FilterTests::test3DGaussianBlur(volume);
    FilterTests::testCreate3DKernel(3, 1.0);
    FilterTests::testCreate3DKernel(5, 2.0);
    FilterTests::test3DMedianFilter();

    std::cout << "Filter tests passed." << std::endl;

    std::cout << "All tests passed." << std::endl;

    // Now run speed tests
    std::cout << "Running speed tests..." << std::endl;
    // Running speed tests for various image processing operations
    std::cout << "\nStarting speed tests for image processing operations..." << std::endl;
    SpeedTest::testGrayscaleSpeed();
    SpeedTest::testBrightnessSpeed();
    SpeedTest::testBrightnessSpeed(true); // With auto-adjust

    SpeedTest::testHistogramEqualSpeed(true); // Using HSV
    SpeedTest::testHistogramEqualSpeed(false); // Not using HSV

    SpeedTest::testThresholdingSpeed(false, false); // Apply to grayscale, not using HSV
    SpeedTest::testThresholdingSpeed(true, false); // Apply to RGB, not using HSV
    SpeedTest::testThresholdingSpeed(true, true); // Apply to RGB, using HSV

    SpeedTest::testSaltPepperSpeed(false); // Not applying to RGB
    SpeedTest::testSaltPepperSpeed(true); // Applying to RGB

    // Edge detection speed tests with various operators
    std::vector<std::pair<int, int>> imageSizes = {
            {640, 480}, // VGA
//            {800, 600}, // SVGA
            {1280, 720}, // HD
//            {1920, 1080}, // FHD
//            {3840, 2160} // 4K
    };

    std::cout << "\nRunning edge detection speed tests with various operators..." << std::endl;
    Filter filter; // Assuming Filter class has methods used in lambdas below

    // Replace the lambdas with the actual function calls if your setup differs
    SpeedTest::runEdgeDetectionSpeedTest("Sobel Operator", [&](Image& img) { filter.applySobelOperator(img); }, imageSizes);
    SpeedTest::runEdgeDetectionSpeedTest("Prewitt Operator", [&](Image& img) { filter.applyPrewittOperator(img); }, imageSizes);
    SpeedTest::runEdgeDetectionSpeedTest("Scharr Operator", [&](Image& img) { filter.applyScharrOperator(img); }, imageSizes);
    SpeedTest::runEdgeDetectionSpeedTest("Roberts Cross Operator", [&](Image& img) { filter.applyRobertsCrossOperator(img); }, imageSizes);

    std::cout << "\nEdge detection tests completed." << std::endl;

    // Running blur speed tests
    try {
        std::cout << "\nGaussian blur speed test result:" << std::endl;
        SpeedTest::testGaussianBlurSpeed();
    } catch (const std::exception& e) {
        std::cerr << "An exception occurred during the Gaussian blur speed test: " << e.what() << std::endl;
    }

    try {
        std::cout << "\nBox blur speed test result:" << std::endl;
        SpeedTest::testBoxBlurSpeed();
    } catch (const std::exception& e) {
        std::cerr << "An exception occurred during the Box blur speed test: " << e.what() << std::endl;
    }

    try {
        std::cout << "\nMedian blur speed test result:" << std::endl;
        SpeedTest::testMedianBlurSpeed();
    } catch (const std::exception& e) {
        std::cerr << "An exception occurred during the Median blur speed test: " << e.what() << std::endl;
    }


    return 0;
}