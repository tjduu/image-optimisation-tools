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

#include "SpeedTests.h"
#include "FilterTests.h"


long long SpeedTest::measureTimeMillis(const std::function<void()>& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func(); // Execute the function
    auto finish = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
}

// Implementation of testMedianBlur
void SpeedTest::testMedianBlurSpeed() {
    // Define a set of image sizes (width and height)
    std::vector<std::pair<int, int>> imageSizes = {
            {640, 480}, // VGA
//            {800, 600}, // SVGA
            {1280, 720}, // HD
//            {1920, 1080}, // FHD
//            {3840, 2160} // 4K
    };

    // Define a set of kernel sizes
    std::vector<int> kernelSizes = {3, 5, 7, 9, 11};

    // Create an instance of Filter
    Filter filter;

    // Iterate over each image size
    for (const auto& size : imageSizes) {
        int width = size.first;
        int height = size.second;

        // Create a test image of the given size with 3 channels (assuming RGB)
        Image testImage(width, height, 3);

        // Fill the test image with random data (pseudo-random for example purposes)
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int k = 0; k < 3; ++k) {
                    testImage.setPixel(x, y, k, rand() % 256);
                }
            }
        }

        // Iterate over each kernel size
        for (int kernel_size : kernelSizes) {
            // Start timing
            auto start = std::chrono::high_resolution_clock::now();

            // Apply the median blur
            Image resultImage = filter.medianBlur(testImage, kernel_size);

            // Stop timing
            auto end = std::chrono::high_resolution_clock::now();

            // Calculate the elapsed time in milliseconds
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

            // Output the results
            std::cout << "Image Size: " << width << "x" << height
                      << ", Kernel Size: " << kernel_size
                      << ", Time Taken: " << duration << " ms" << std::endl;
        }
    }
}

// Implementation of testBoxBlur
void SpeedTest::testBoxBlurSpeed() {
    // Define a set of image sizes (width and height)
    std::vector<std::pair<int, int>> imageSizes = {
            {640, 480}, // VGA
//            {800, 600}, // SVGA
            {1280, 720}, // HD
//            {1920, 1080}, // FHD
//            {3840, 2160} // 4K
    };

    // Define a set of kernel sizes
    std::vector<int> kernelSizes = {3, 5, 7, 9, 11};

    // Iterate over each image size
    for (const auto& size : imageSizes) {
        int width = size.first;
        int height = size.second;

        // Create a test image of the given size with 3 channels (assuming RGB)
        Image testImage(width, height, 3);

        // Fill the test image with random data (pseudo-random for example purposes)
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int k = 0; k < 3; ++k) {
                    testImage.setPixel(x, y, k, rand() % 256);
                }
            }
        }

        // Iterate over each kernel size
        for (int kernel_size : kernelSizes) {
            Filter filter; // Assuming a Filter class exists

            // Start timing
            auto start = std::chrono::high_resolution_clock::now();

            // Apply the box blur
            Image resultImage = filter.boxBlur(testImage, kernel_size);

            // Stop timing
            auto end = std::chrono::high_resolution_clock::now();

            // Calculate the elapsed time in milliseconds
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

            // Output the results
            std::cout << "Image Size: " << width << "x" << height
                      << ", Kernel Size: " << kernel_size
                      << ", Time Taken: " << duration << " ms" << std::endl;
        }
    }
}

// Implementation of testGaussianBlur
void SpeedTest::testGaussianBlurSpeed() {
    // Define a set of image sizes (width and height)
    std::vector<std::pair<int, int>> imageSizes = {
            {640, 480}, // VGA
//            {800, 600}, // SVGA
            {1280, 720}, // HD
//            {1920, 1080}, // FHD
//            {3840, 2160} // 4K
    };

    // Define a set of kernel sizes (must be odd numbers)
    std::vector<int> kernelSizes = {3, 5, 7, 9, 11};

    // Define a set of sigma values for the Gaussian function
    std::vector<float> sigmaValues = {1.0f};

    // Iterate over each image size
    for (const auto& size : imageSizes) {
        int width = size.first;
        int height = size.second;

        // Create a test image of the given size with 3 channels (assuming RGB)
        Image testImage(width, height, 3);

        // Fill the test image with random data (pseudo-random for example purposes)
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int k = 0; k < 3; ++k) {
                    testImage.setPixel(x, y, k, rand() % 256);
                }
            }
        }

        // Iterate over each kernel size
        for (int kernel_size : kernelSizes) {
            // Ensure the kernel size is odd
            if (kernel_size % 2 == 0) continue;

            // Iterate over each sigma value
            for (float sigma : sigmaValues) {
                Filter filter; // Assuming a Filter class exists

                // Start timing
                auto start = std::chrono::high_resolution_clock::now();

                // Apply the Gaussian blur
                Image resultImage;
                try {
                    resultImage = filter.gaussianBlur(testImage, kernel_size, sigma);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                    continue;
                }

                // Stop timing
                auto end = std::chrono::high_resolution_clock::now();

                // Calculate the elapsed time in milliseconds
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                // Output the results
                std::cout << "Image Size: " << width << "x" << height
                          << ", Kernel Size: " << kernel_size
                          << ", Time Taken: " << duration << " ms" << std::endl;
            }
        }
    }
}


void SpeedTest::testGrayscaleSpeed() {
    std::cout << "Test time spent for grayscale filter.\n";

    // Define a set of image sizes (width and height)
    std::vector<std::pair<int, int>> imageSizes = {
            {640, 480}, // VGA
//            {800, 600}, // SVGA
            {1280, 720}, // HD
//            {1920, 1080}, // FHD
//            {3840, 2160} // 4K
    };


    // Iterate over each image size
    for (const auto& size : imageSizes) {
        int width = size.first;
        int height = size.second;

        // Create a test image of the given size with 3 channels (assuming RGB)
        Image testImage(width, height, 3);

        // Fill the test image with random data (pseudo-random for example purposes)
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int k = 0; k < 3; ++k) {
                    testImage.setPixel(x, y, k, rand() % 256);
                }
            }
        }

        Filter filter; // Assuming a Filter class exists

        // Start timing
        auto start = std::chrono::high_resolution_clock::now();

        // Apply the box blur
        Image resultImage = filter.grayScale(testImage);

        // Stop timing
        auto end = std::chrono::high_resolution_clock::now();

        // Calculate the elapsed time in milliseconds
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // Output the results
        std::cout << "Image Size: " << width << "x" << height
                  << ", Time Taken: " << duration << " ms" << std::endl;
    }
}

void SpeedTest::testBrightnessSpeed(bool autobrightness) {
    if (autobrightness)
        std::cout << "Test time spent for brightness filter with autobrightness.\n";
    else
        std::cout << "Test time spent for brightness filter.\n";

    // Define a set of image sizes (width and height)
    std::vector<std::pair<int, int>> imageSizes = {
            {640, 480}, // VGA
//            {800, 600}, // SVGA
            {1280, 720}, // HD
//            {1920, 1080}, // FHD
//            {3840, 2160} // 4K
    };


    // Iterate over each image size
    for (const auto& size : imageSizes) {
        int width = size.first;
        int height = size.second;

        // Create a test image of the given size with 3 channels (assuming RGB)
        Image testImage(width, height, 3);

        // Fill the test image with random data (pseudo-random for example purposes)
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int k = 0; k < 3; ++k) {
                    testImage.setPixel(x, y, k, rand() % 256);
                }
            }
        }

        Filter filter; // Assuming a Filter class exists

        // Start timing
        auto start = std::chrono::high_resolution_clock::now();

        // Apply the box blur
        Image resultImage = filter.setBrightness(testImage, rand() % 513 - 256,autobrightness);

        // Stop timing
        auto end = std::chrono::high_resolution_clock::now();

        // Calculate the elapsed time in milliseconds
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // Output the results
        std::cout << "Image Size: " << width << "x" << height
                  << ", Time Taken: " << duration << " ms" << std::endl;
    }
}

void SpeedTest::testHistogramEqualSpeed(bool isHSV) {
    if (isHSV)
        std::cout << "Test time spent for histogram equalization filter on HSV images.\n";
    else
        std::cout << "Test time spent for histogram equalization filter.\n";
    // Define a set of image sizes (width and height)
    std::vector<std::pair<int, int>> imageSizes = {
            {640, 480}, // VGA
//            {800, 600}, // SVGA
            {1280, 720}, // HD
//            {1920, 1080}, // FHD
//            {3840, 2160} // 4K
    };


    // Iterate over each image size
    for (const auto& size : imageSizes) {
        int width = size.first;
        int height = size.second;

        // Create a test image of the given size with 3 channels (assuming RGB)
        Image testImage(width, height, 3);

        // Fill the test image with random data (pseudo-random for example purposes)
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int k = 0; k < 3; ++k) {
                    testImage.setPixel(x, y, k, rand() % 256);
                }
            }
        }

        Filter filter; // Assuming a Filter class exists

        // Start timing
        auto start = std::chrono::high_resolution_clock::now();

        // Apply the box blur
        Image resultImage = filter.histogramEqualization(testImage, isHSV);

        // Stop timing
        auto end = std::chrono::high_resolution_clock::now();

        // Calculate the elapsed time in milliseconds
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // Output the results
        std::cout << "Image Size: " << width << "x" << height
                  << ", Time Taken: " << duration << " ms" << std::endl;
    }
}

void SpeedTest::testThresholdingSpeed(bool isRGB, bool isHSV) {
    if (isRGB && isHSV)
        std::cout << "Test time spent for thresholding filter on HSV images.\n";
    else if (isRGB)
        std::cout << "Test time spent for thresholding filter on RGB images.\n";
    else
        std::cout << "Test time spent for thresholding filter on grayscale images.\n";

    // Define a set of image sizes (width and height)
    std::vector<std::pair<int, int>> imageSizes = {
            {640, 480}, // VGA
//            {800, 600}, // SVGA
            {1280, 720}, // HD
//            {1920, 1080}, // FHD
//            {3840, 2160} // 4K
    };


    // Iterate over each image size
    for (const auto& size : imageSizes) {
        int width = size.first;
        int height = size.second;

        int channel = 1;
        if (isRGB) channel = 3;
        Image testImage(width, height, channel);

        // Fill the test image with random data (pseudo-random for example purposes)
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int k = 0; k < channel; ++k) {
                    testImage.setPixel(x, y, k, rand() % 256);
                }
            }
        }

        Filter filter; // Assuming a Filter class exists

        // Start timing
        auto start = std::chrono::high_resolution_clock::now();

        // Apply the box blur
        Image resultImage = filter.threshold(testImage, rand()%513-256, true, isHSV);

        // Stop timing
        auto end = std::chrono::high_resolution_clock::now();

        // Calculate the elapsed time in milliseconds
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // Output the results
        std::cout << "Image Size: " << width << "x" << height
                  << ", Time Taken: " << duration << " ms" << std::endl;
    }
}

void SpeedTest::testSaltPepperSpeed(bool isRGB) {
    if (isRGB)
        std::cout << "Test time spent for salt and pepper filter on RGB images.\n";
    else
        std::cout << "Test time spent for salt and pepper filter on grayscale images.\n";
    // Define a set of image sizes (width and height)
    std::vector<std::pair<int, int>> imageSizes = {
            {640, 480}, // VGA
//            {800, 600}, // SVGA
            {1280, 720}, // HD
//            {1920, 1080}, // FHD
//            {3840, 2160} // 4K
    };


    // Iterate over each image size
    for (const auto& size : imageSizes) {
        int width = size.first;
        int height = size.second;

        int channel = 1;
        if (isRGB) channel = 3;
        Image testImage(width, height, channel);

        // Fill the test image with random data (pseudo-random for example purposes)
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int k = 0; k < channel; ++k) {
                    testImage.setPixel(x, y, k, rand() % 256);
                }
            }
        }

        Filter filter; // Assuming a Filter class exists

        // Start timing
        auto start = std::chrono::high_resolution_clock::now();

        // Apply the box blur
        Image resultImage = filter.salt_and_pepper(testImage, 0.5, isRGB);

        // Stop timing
        auto end = std::chrono::high_resolution_clock::now();

        // Calculate the elapsed time in milliseconds
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // Output the results
        std::cout << "Image Size: " << width << "x" << height
                  << ", Time Taken: " << duration << " ms" << std::endl;
    }
}

void SpeedTest::runEdgeDetectionSpeedTest(
        const std::string& methodName,
        const std::function<void(Image&)>& edgeDetectionFunc,
        const std::vector<std::pair<int, int>>& imageSizes
) {
    std::cout << "Testing " << methodName << "..." << std::endl;

    for (const auto& size : imageSizes) {
        Image img(size.first, size.second, 1); // Assuming 1 channel for simplicity, adjust if necessary
        std::cout << "\tImage size: " << size.first << "x" << size.second << " - ";
        long long timeTaken = SpeedTest::measureTimeMillis([&] { edgeDetectionFunc(img); });
        std::cout << "Time taken: " << timeTaken << " milliseconds" << std::endl;
    }
}