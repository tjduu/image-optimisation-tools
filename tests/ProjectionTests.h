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

#ifndef ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_PROJECTIONTESTS_H
#define ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_PROJECTIONTESTS_H
#include "Volume.h"
#include <iostream>
#include <cassert>

class ProjectionTests {
public:
    static void test_maximumIntensityProjection(const Volume& volume);
    static void test_minimumIntensityProjection(const Volume& volume);
    static void test_averageIntensityProjection(const Volume& volume);
    static void test_medianIntensityProjection(const Volume& volume);
    static bool compareImages(const Image& img1, const Image& img2, int tolerance);
    static Volume generateVolume();
    static void test_swap();
    static void test_partition();
    static void test_quickSort();
    static void selectionSort(std::vector<unsigned char>& arr);
    static Image generateRandomImage(int width, int height, int channels);
    // Additional method tests can be added here following the same pattern

private:

    };
#endif //ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_PROJECTIONTESTS_H
