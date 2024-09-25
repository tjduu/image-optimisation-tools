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

#ifndef ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_FILTERTESTS_H
#define ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_FILTERTESTS_H
#include "Filter.h"
#include "Slice.h"
#include <cassert>
#include <iostream>

class FilterTests {
public:
    static void testMedianBlur();
    static void testBoxBlur();
    static void testGaussianBlur();
    static void testGrayScale();
    static void testSetBrightness();
    static void test_setBrightness_manual();
    static void test_setBrightness_auto();
    static void test_setBrightness();
    static void testSaltAndPepper();
    static void test_salt_and_pepper();
    static void testThreshold();
    static void test_threshold();
    static void test_rgb_to_hsv();
    static void test_hsv_to_rgb();
    static void test_rgb_to_hsl();
    static void test_hsl_to_rgb();
    static void testHistogramEqualization();
    static void test_histogramEqualization();
    static void test_calculateHistogramEqualization();
    static void testApplySobelOperator();
    static void testApplyPrewittOperator();
    static void testApplyScharrOperator();
    static void testApplyRobertsCrossOperator();
    static void test3DGaussianBlur(Volume& volume);
    static void testCreate3DKernel(int kernelSize, float sigma);
    static void test3DMedianFilter();
    // Additional method tests can be added here following the same pattern
private:
    static double calculateSliceVariance(const std::shared_ptr<Slice>& slice);
    static double calculateSliceVariance(const std::shared_ptr<Image>& slice);
};

#endif //ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_FILTERTESTS_H
