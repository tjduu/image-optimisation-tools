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

#ifndef ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_SPEEDTESTS_H
#define ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_SPEEDTESTS_H
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <regex>
#include <map>
#include <chrono> // For timing tests

// External library headers (if used, e.g., for image loading/saving)
// #include "stb_image.h"
// #include "stb_image_write.h"

// Include project-specific headers
#include "Image.h"
#include "Volume.h"
#include "Filter.h"
#include "Projection.h"

// Test namespace or class declaration (if applicable)
// Placeholder for any test-specific declarations or utility functions
class SpeedTest {
public:
    static void testGrayscaleSpeed();
    static void testBrightnessSpeed(bool autoAdjust = false);
    static void testHistogramEqualSpeed(bool isHSV);
    static void testThresholdingSpeed(bool applyToRGB, bool isHSV);
    static void testSaltPepperSpeed(bool applyToRGB);
    static void runEdgeDetectionSpeedTest(
            const std::string& methodName,
            const std::function<void(Image&)>& edgeDetectionFunc,
            const std::vector<std::pair<int, int>>& imageSizes
            );
    static void testGaussianBlurSpeed();
    static void testBoxBlurSpeed();
    static void testMedianBlurSpeed();
    // Add additional test declarations as necessary
private:
    static long long measureTimeMillis(const std::function<void()>& func);
};

// Placeholder for any additional utility functions or classes used by the tests

#endif //ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_SPEEDTESTS_H
