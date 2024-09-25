/**
 * @file Projection.h
 * @brief Declaration of the Projection class for generating projections from a 3D volume.
 *
 * The Projection class offers methods to generate various types of projections from a 3D volume, including Maximum Intensity Projection (MIP),
 * Minimum Intensity Projection (mIP), Average Intensity Projection (AIP), and Median Intensity Projection (MeIP). These projections
 * are useful for visualizing and analyzing volumetric data by collapsing it into a 2D image based on specific criteria.
 *
 * Group: Ziggurat
 *
 * Members:
 * - Xiaoye Zhang (GitHub: acse-xz4019)
 * - Melissa Sim (GitHub: acse-mys20)
 * - Wenhao Hong (GitHub: acse-wh623)
 * - Javonne Porter (GitHub: acse-jp2923)
 * - Tianju (Tim) Du (GitHub: edsml-td323)
 * - Wenxin Li (GitHub: edsml-wl123)
 *
 */

#ifndef ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_PROJECTION_H
#define ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_PROJECTION_H
#include "Image.h"
#include "Volume.h"

#include <algorithm>

/**
 * @class Projection
 * @brief Provides methods for generating 2D projections from 3D volumes.
 *
 * The class methods support generating projections by aggregating pixel data across the z-axis of the volume according to different criteria:
 * maximum, minimum, average, and median intensity values. This functionality allows for enhanced visualization and analysis of 3D volumetric data
 * in 2D form.
 *
 */
class Projection{
public:
    /**
     * @brief Generates a Maximum Intensity Projection (MIP) from a 3D volume.
     * 
     * This method generates a Maximum Intensity Projection (MIP) from a 3D volume.
     * The MIP is created by projecting the maximum intensity value along the z-axis for each pixel.
     * 
     * @param volume The 3D volume to generate the MIP from.
     * @param z_start The starting z-slice index for the MIP. If not specified, the MIP is generated from the first z-slice.
     * @param z_end The ending z-slice index for the MIP. If not specified, the MIP is generated to the last z-slice.
     * @return A image containing the Maximum Intensity Projection (MIP) of the 3D volume.
    */
    static Image maximumIntensityProjection(const Volume& volume, int z_start=-1, int z_end=-1);

    /**
     * @brief Generates a Minimum Intensity Projection (mIP) from a 3D volume.
     * 
     * This method generates a Minimum Intensity Projection (mIP) from a 3D volume.
     * The mIP is created by projecting the minimum intensity value along the z-axis for each pixel.
     * 
     * @param volume The 3D volume to generate the mIP from.
     * @param z_start The starting z-slice index for the mIP. If not specified, the mIP is generated from the first z-slice.
     * @param z_end The ending z-slice index for the mIP. If not specified, the mIP is generated to the last z-slice.
     * @return A image containing the Minimum Intensity Projection (mIP) of the 3D volume.
    */
    static Image minimumIntensityProjection(const Volume& volume, int z_start=-1, int z_end=-1);

    /**
     * @brief Generates an Average Intensity Projection (AIP) from a 3D volume.
     * 
     * This method generates an Average Intensity Projection (AIP) from a 3D volume.
     * The AIP is created by projecting the average intensity value along the z-axis for each pixel.
     * 
     * @param volume The 3D volume to generate the AIP from.
     * @param z_start The starting z-slice index for the AIP. If not specified, the AIP is generated from the first z-slice.
     * @param z_end The ending z-slice index for the AIP. If not specified, the AIP is generated to the last z-slice.
     * @return A image containing the Average Intensity Projection (AIP) of the 3D volume.
    */
    static Image averageIntensityProjection(const Volume& volume, int z_start=-1, int z_end=-1);

    /**
     * @brief Generates a Median Intensity Projection (MeIP) from a 3D volume.
     *  
     * This method generates a Median Intensity Projection (MeIP) from a 3D volume.
     * The MeIP is created by projecting the median intensity value along the z-axis for each pixel.
     * 
     * This function chooses between two methods to generate the MeIP based on depth of the volume:
     * - Histogram method: Uses a histogram to calculate the median intensity value. (for depths >= 500)
     * - Quick Sort method: Uses the Quick Sort algorithm to sort the intensity values. (for depths < 500)
     *  
     * @param volume The 3D volume to generate the MeIP from.
     * @param z_start The starting z-slice index for the MeIP. If not specified, the MeIP is generated from the first z-slice.
     * @param z_end The ending z-slice index for the MeIP. If not specified, the MeIP is generated to the last z-slice.
    */
    static Image medianIntensityProjection(const Volume& volume, int z_start=-1, int z_end=-1);

    /**
     * @brief Generates a Median Intensity Projection (MeIP) from a 3D volume.
     * 
     * This method generates a Median Intensity Projection (MeIP) from a 3D volume.
     * Using a histogram to get the median intensity value.
     * 
     * @param volume The 3D volume to generate the MeIP from.
     * @param z_start The starting z-slice index for the MeIP. If not specified, the MeIP is generated from the first z-slice.
     * @param z_end The ending z-slice index for the MeIP. If not specified, the MeIP is generated to the last z-slice.
     * @return A image containing the Median Intensity Projection (MeIP) of the 3D volume.
    */
    static Image medianIntensityProjection_histogram(const Volume& volume, int z_start=-1, int z_end=-1);

    /**
     * @brief Generates a Median Intensity Projection (MeIP) from a 3D volume.
     * 
     * This method generates a Median Intensity Projection (MeIP) from a 3D volume.
     * Using the Quick Sort algorithm to sort the intensity values of each pixel along the z-axis.
     * 
     * @param volume The 3D volume to generate the MeIP from.
     * @param z_start The starting z-slice index for the MeIP. If not specified, the MeIP is generated from the first z-slice.
     * @param z_end The ending z-slice index for the MeIP. If not specified, the MeIP is generated to the last z-slice.
     * @return A image containing the Median Intensity Projection (MeIP) of the 3D volume.
    */
    static Image medianIntensityProjection_quickSort(const Volume& volume, int z_start=-1, int z_end=-1);

    // Helper functions
    /**
     * @brief Swaps two unsigned char values.
     * 
     * This method swaps two unsigned char values.
     * 
     * @param a The first unsigned char value.
     * @param b The second unsigned char value.
    */
    static void swap(unsigned char& a, unsigned char& b);

    /**
     * @brief Partitions an array of unsigned char values.
     * 
     * This method partitions an array of unsigned char values.
     * Helper function for the Quick Sort algorithm.
     * 
     * @param arr The array of unsigned char values to partition.
     * @param low The starting index of the array.
     * @param high The ending index of the array.
     * @return The partition index.
    */
    static int partition(unsigned char* arr, int low, int high);

    /**
     * @brief Sorts an array of unsigned char values using the Quick Sort algorithm.
     * 
     * This method sorts an array of unsigned char values using the Quick Sort algorithm.
     * Helper function for the Median Intensity Projection (MeIP). To get the median value intensity
     * of each pixel.
     * 
     * @param arr The array of unsigned char values to sort.
     * @param low The starting index of the array.
     * @param high The ending index of the array.
     * @return The partition index.
    */
    static void quickSort(unsigned char* arr, int low, int high);
};
#endif //ADVANCED_PROGRAMMING_GROUP_ZIGGURAT_PROJECTION_H