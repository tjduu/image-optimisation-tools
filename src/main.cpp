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

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "Image.h"
#include "Volume.h"
#include "Filter.h"
#include "Projection.h"

// Forward declarations for all menu display and processing functions
void displayMainMenu();
void display2DProcessingMenu();
void display3DProcessingMenu();
void displayColorCorrectionMenu();
void displayImageBlurMenu();
void displayEdgeDetectionMenu();
void display3DFilterMenu();
void displayProjectionMenu();

// Forward declarations for processing functions
void process2DImageProcessing(std::shared_ptr<Image>& imgPtr);
void process3DVolumeProcessing(std::shared_ptr<Volume>& volumePtr);
void processColorCorrection(std::shared_ptr<Image>& imgPtr);
void processImageBlur(std::shared_ptr<Image>& imgPtr);
void processEdgeDetection(std::shared_ptr<Image>& imgPtr);
void process3DFilters(std::shared_ptr<Volume>& volumePtr);
void processProjections(std::shared_ptr<Volume>& volumePtr);

namespace fs = std::filesystem;


//Part 1: Main and Menu Display Functions
int main() {
    // imgPtr is a smart pointer to Image
    std::shared_ptr<Image> imgPtr;
    // volumePtr is a smart pointer to Volume
    std::shared_ptr<Volume> volumePtr;
    // the image object to store the image
    Image img;
    // the path to the input image
    std::string inputPath;

    bool isRunning = true;

    int mainChoice;
    do {
        displayMainMenu();
        std::cin >> mainChoice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please enter a number.\n";
            continue;
        }
        switch (mainChoice) {
            case 1:{
                imgPtr.reset();
                volumePtr.reset();
                std::cout << "Enter image path: ";
                std::cin >> inputPath;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                try {
                    imgPtr = std::make_shared<Image>(inputPath);
                    std::cout << "Image loaded successfully.\n";
                } catch (const std::exception &e) {
                    std::cout << "Failed to load image: " << e.what() << std::endl;
                    break;
                }
                process2DImageProcessing(imgPtr);
                break;
            }
            case 2:{
                imgPtr.reset();
                volumePtr.reset();
                std::vector<std::string> filenames;
                std::cout << "Enter directory path for 3D volume: ";
                std::cin >> inputPath;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                try {
                    for (const auto& entry : fs::directory_iterator(inputPath)) {
                        if (entry.path().extension() == ".png") {
                            filenames.push_back(entry.path().string());
                        }
                    }

                    if (filenames.empty()) {
                        std::cerr << "No PNG files found in the specified directory." << std::endl;
                        break;
                    }

                    try {
                        volumePtr = std::make_shared<Volume>(filenames); // Create Volume object managed by smart pointer
                        process3DVolumeProcessing(volumePtr);
                    } catch (const std::exception& e) {
                        std::cout << "Failed to process volume: " << e.what() << std::endl;
                    }
                    std::cout << "Image loaded successfully.\n";
                } catch (const std::exception& e) {
                    std::cout << "Failed to load 3D volume: " << e.what() << std::endl;
                    break;
                }
                break;
            }
            case 3:{
                std::cout << "Exiting program.\n";
                isRunning = false;
                return 0;
            }
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (isRunning);

    return 0;
}

void displayMainMenu() {
    std::cout << "\nSelect an option:\n";
    std::cout << "1. 2D Image Processing\n";
    std::cout << "2. 3D Volume Processing\n";
    std::cout << "3. Quit\n";
    std::cout << "Enter choice: ";
}

// Part 2: 2D Image Processing Functions
void display2DProcessingMenu() {
    std::cout << "\n2D Image Processing Options:\n";
    std::cout << "1. Color Correction and Simple Per-pixel Modifiers\n";
    std::cout << "2. Image Blur\n";
    std::cout << "3. Edge Detection\n";
    std::cout << "4. Clear cache and Return to Main Menu\n";
    std::cout << "Enter choice: ";
}

// helper function to save the image
void saveImage(const std::shared_ptr<Image>& imgPtr) {
    std::string outputPath;
    std::cout << "Enter output path to save the image (with .png at the end): ";
    std::cin >> outputPath;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    try {
        imgPtr->save(outputPath);
        std::cout << "Image saved successfully to " << outputPath << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Failed to save the image: " << e.what() << std::endl;
    }
}

void processColorCorrection(std::shared_ptr<Image>& imgPtr) {
    if (!imgPtr) return; // Ensure the image pointer is not null.
    displayColorCorrectionMenu();
    int choice;
    std::cin >> choice;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string outputPath;

    // Ensure choice falls within implemented options
    if (choice < 1 || choice > 6) {
        std::cout << "Invalid choice. Please try again.\n";
        return;
    }

    // For returning to 2D processing menu
    if (choice == 6) {
        return;
    }

    switch (choice) {
        case 1: // Grayscale
            *imgPtr = Filter::grayScale(*imgPtr);
            break;
        case 2: { // Brightness
            int brightnessValue;
            bool autoBrightness;
            std::cout << "Enter brightness value (-255 to 255), or 0 for auto brightness: ";
            std::cin >> brightnessValue;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // Check if the brightness value is within the valid range
            if (brightnessValue < -255 || brightnessValue > 255) {
                std::cout << "Invalid brightness value. Please try again.\n";
                return;
            }
            autoBrightness = (brightnessValue == 0);
            *imgPtr = Filter::setBrightness(*imgPtr, brightnessValue, autoBrightness);
            break;
        }
        case 3: // Histogram Equalisation
            // ask if the image is rgb or not
            char rgb;
            std::cout << "Is the image RGB? (y/n): ";
            std::cin >> rgb;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (rgb == 'y' || rgb == 'Y') {
                // ask if user want to use hsv or not
                char hsv;
                std::cout << "Do you want to use HSV? (y/n), if choose no, use HSL: ";
                std::cin >> hsv;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (hsv == 'y' || hsv == 'Y') {
                    *imgPtr = Filter::histogramEqualization(*imgPtr, true); // Implement Histogram Equalization.
                }
                else if (hsv == 'n' || hsv == 'N'){
                    *imgPtr = Filter::histogramEqualization(*imgPtr, false); // Implement Histogram Equalization.
                }
                else {
                    std::cout << "Invalid choice. Please try again.\n";
                    return;
                }
            }
            else if (rgb == 'n' || rgb == 'N') {
                *imgPtr = Filter::histogramEqualization(*imgPtr, false); // Implement Histogram Equalization.
            }
            else {
                std::cout << "Invalid choice. Please try again.\n";
                return;
            }
            break;
        case 4: { // Thresholding
            double threshold;
            std::cout << "Enter threshold value (0-255): ";
            std::cin >> threshold;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // check if the threshold value is within the valid range
            if (threshold < 0 || threshold > 255) {
                std::cout << "Invalid threshold value. Please try again.\n";
                return;
            }
            //ask if the image is rgb or not
            char rgb_;
            std::cout << "Is the image RGB? (y/n): ";
            std::cin >> rgb_;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (rgb_ == 'y' || rgb_ == 'Y') {
                // ask if user want to use hsv or not
                char hsv;
                std::cout << "Do you want to use HSV? (y/n), if choose no, use HSL: ";
                std::cin >> hsv;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (hsv == 'y' || hsv == 'Y') {
                    *imgPtr = Filter::threshold(*imgPtr, threshold, true, true); // Implement Thresholding.
                }
                else if (hsv == 'n' || hsv == 'N'){
                    *imgPtr = Filter::threshold(*imgPtr, threshold, true, false); // Implement Thresholding.
                }
                else {
                    std::cout << "Invalid choice. Please try again.\n";
                    return;
                }
            }
            else if (rgb_ == 'n' || rgb_ == 'N') {
                *imgPtr = Filter::threshold(*imgPtr, threshold, false, false); // Implement Thresholding.
            }
            else {
                std::cout << "Invalid choice. Please try again.\n";
                return;
            }
            break;
        }
        case 5: { // Salt and Pepper Noise
            double noiseRatio;
            std::cout << "Enter noise ratio (0.0 to 1.0): ";
            std::cin >> noiseRatio;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // check if the noise ratio is within the valid range
            if (noiseRatio < 0.0 || noiseRatio > 1.0) {
                std::cout << "Invalid noise ratio. Please try again.\n";
                return;
            }
            *imgPtr = Filter::salt_and_pepper(*imgPtr, noiseRatio, true); // Implement Salt and Pepper Noise.
            break;
        }
        default:
            std::cout << "Invalid choice. Please try again.\n";
            return;
    }

    char saveNow;
    std::cout << "Do you want to save the changes? (y/n): ";
    std::cin >> saveNow;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (saveNow == 'y' || saveNow == 'Y') {
        saveImage(imgPtr);
    }
    else {
        std::cout << "Changes not saved to the local." << std::endl;
        return;
    }


}

void processImageBlur(std::shared_ptr<Image>& imgPtr) {
    displayImageBlurMenu();
    int choice;
    std::cin >> choice;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string outputPath;

    // Validate user choice before proceeding
    if (choice < 1 || choice > 4) {
        std::cout << "Invalid choice. Please try again.\n";
        return; // Exit the function if the choice is not valid
    }

    // If the choice is to return to the previous menu, just return from the function
    if (choice == 4) {
        return;
    }

    int kernelSize = 0;
    float sigma = 0.0f; // Only used for Gaussian Blur

    std::cout << "Enter kernel size (odd number): ";
    std::cin >> kernelSize;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (kernelSize % 2 == 0) {
        std::cout << "Kernel size must be an odd number. Please try again.\n";
        return; // Exit if the kernel size is not odd
    }
    // Ensure the kernel size is within the valid range
    if (kernelSize < 3 || kernelSize > 15) {
        std::cout << "Kernel size must be between 3 and 15. Please try again.\n";
        return;
    }

    // Process the specific blur based on the choice
    switch (choice) {
        case 1: // Median Blur
            *imgPtr = Filter::medianBlur(*imgPtr, kernelSize);
//            *imgPtr = Filter::histomedianBlur(*imgPtr, kernelSize);  // Implement Histogram Median Blur.
            break;
        case 2: // Box Blur
            *imgPtr = Filter::boxBlur(*imgPtr, kernelSize);
            break;
        case 3: // Gaussian Blur requires an additional input for sigma
            std::cout << "Enter sigma for Gaussian Blur: ";
            std::cin >> sigma;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // Ensure the sigma value is within the valid range
            if (sigma < 0.0f) {
                std::cout << "Sigma value must be non-negative. Please try again.\n";
                return;
            }
            *imgPtr = Filter::gaussianBlur(*imgPtr, kernelSize, sigma);
            break;
        default:
            std::cout << "Unexpected error occurred.\n";
            return;
    }

    char saveNow;
    std::cout << "Do you want to save the changes? (y/n): ";
    std::cin >> saveNow;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (saveNow == 'y' || saveNow == 'Y') {
        saveImage(imgPtr);
    }
    else {
        std::cout << "Changes not saved to the local." << std::endl;
        return;
    }
}

void processEdgeDetection(std::shared_ptr<Image>& imgPtr) {
    displayEdgeDetectionMenu();
    int choice;
    std::cin >> choice;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string outputPath;

    // Ensure the choice is within the valid range or to return to the previous menu
    if (choice < 1 || choice > 5) {
        std::cout << "Invalid choice. Please try again.\n";
        return; // Exit the function if the choice is not within the expected range
    }

    // If the user selects to return to the previous menu, simply exit this function
    if (choice == 5) {
        return;
    }

    // Ask for the input image path and attempt to load the image
    try {

        // Apply the selected edge detection algorithm
        switch (choice) {
            case 1:
                *imgPtr = Filter::applySobelOperator(*imgPtr);
                break;
            case 2:
                *imgPtr = Filter::applyPrewittOperator(*imgPtr);
                break;
            case 3:
                *imgPtr = Filter::applyScharrOperator(*imgPtr);
                break;
            case 4:
                *imgPtr = Filter::applyRobertsCrossOperator(*imgPtr);
                break;
            default:
                std::cout << "Unexpected error. Please try again.\n";
                return;
        }
        char saveNow;
        std::cout << "Do you want to save the changes? (y/n): ";
        std::cin >> saveNow;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (saveNow == 'y' || saveNow == 'Y') {
            saveImage(imgPtr);
        }
        else {
            std::cout << "Changes not saved to the local." << std::endl;
            return;
        }
    } catch (const std::exception& e) {
        std::cout << "An error occurred while processing the image: " << e.what() << std::endl;
    }
}

void process2DImageProcessing(std::shared_ptr<Image>& imgPtr) {
    bool isInMenu = true;
    int choice2D;
    do {
        display2DProcessingMenu();
        std::cin >> choice2D;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice2D) {
            case 1:
                processColorCorrection(imgPtr);
                break;
            case 2:
                processImageBlur(imgPtr);
                break;
            case 3:
                processEdgeDetection(imgPtr);
                break;
            case 4:
                isInMenu = false;
                return; // Return to main menu
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (isInMenu);
}

void displayColorCorrectionMenu() {
    std::cout << "\nColor Correction Options:\n";
    std::cout << "1. Grayscale\n";
    std::cout << "2. Brightness\n";
    std::cout << "3. Histogram Equalisation (Placeholder)\n";
    std::cout << "4. Thresholding (Placeholder)\n";
    std::cout << "5. Salt and Pepper Noise (Placeholder)\n";
    std::cout << "6. Return to 2D Image Processing Menu\n";
    std::cout << "Enter choice: ";
}

void displayImageBlurMenu() {
    std::cout << "\nImage Blur Options:\n";
    std::cout << "1. Apply Median Blur\n";
    std::cout << "2. Apply Box Blur\n";
    std::cout << "3. Apply Gaussian Blur\n";
    std::cout << "4. Return to Previous Menu\n";
    std::cout << "Enter choice: ";
}

// Display the edge detection menu
void displayEdgeDetectionMenu() {
    std::cout << "\nEdge Detection Options:\n";
    std::cout << "1. Apply Sobel Operator\n";
    std::cout << "2. Apply Prewitt Operator\n";
    std::cout << "3. Apply Scharr Operator\n";
    std::cout << "4. Apply Roberts Cross Operator\n";
    std::cout << "5. Return to Previous Menu\n";
    std::cout << "Enter choice: ";
}

// Part 4: 3D Volume Processing Functions
void display3DProcessingMenu() {
    std::cout << "\n3D Volume Processing Options:\n";
    std::cout << "1. Apply 3D Filters\n";
    std::cout << "2. Generate Projections, won't influence the Volume\n";
    std::cout << "3. Get Slice\n";
    std::cout << "4. Delete the cache and Return to Main Menu\n";
    std::cout << "Enter choice: ";
}

void display3DFilterMenu() {
    std::cout << "\n3D Filter Options:\n";
    std::cout << "1. 3D Gaussian Blur\n";
    std::cout << "2. 3D Median Filter\n";
    std::cout << "3. Return to 3D Volume Processing Menu\n";
    std::cout << "4. Save the volume now\n";
    std::cout << "Enter choice: ";
}

void display3DSliceMenu() {
    std::cout << "\nSlice Options:\n";
    std::cout << "1. Slice along X-Y plane\n";
    std::cout << "2. Slice along Y-Z plane\n";
    std::cout << "3. Slice along X-Z plane\n";
    std::cout << "4. Return to 3D Volume Processing Menu\n";
    std::cout << "Enter choice: ";
}

void process3DSlice(std::shared_ptr<Volume>& volumePtr) {
    bool isInMenu = true;
    int axis;
    do {
        display3DSliceMenu();
        std::cin >> axis;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (axis) {
            case 1:{
                // slice alone xy
                // ask for the depth of the slice
                int depth;
                std::cout << "Enter the depth of the slice (1 to " << volumePtr->getDepth() << "): ";
                std::cin >> depth;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (depth < 1 || depth > volumePtr->getDepth()) {
                    std::cout << "Invalid depth. Please try again.\n";
                    return;
                }
                try {
                    auto slice = volumePtr->getSlice(depth-1);
                    std::string outputPath;
                    std::cout << "Enter output path to save the slice (with .png at the end): ";
                    std::cin >> outputPath;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    slice->save(outputPath);
                    std::cout << "Slice saved successfully to " << outputPath << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Failed to get slice: " << e.what() << std::endl;
                    return;
                }
                break;
            }
            case 2:{
                // slice along yz
                // ask for the y location of the slice
                int y;
                std::cout << "Enter the x location of the slice (1 to " << volumePtr->getHeight() << "): ";
                std::cin >> y;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (y < 1 || y > volumePtr->getHeight()) {
                    std::cout << "Invalid y location. Please try again.\n";
                    return;
                }
                try {
                    auto slice = volumePtr->getSliceYZ(y-1);
                    std::string outputPath;
                    std::cout << "Enter output path to save the slice (with .png at the end): ";
                    std::cin >> outputPath;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    slice->save(outputPath);
                    std::cout << "Slice saved successfully to " << outputPath << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Failed to get slice: " << e.what() << std::endl;
                    return;
                }
                break;
            }
            case 3:{
                // slice along xz
                // ask for the x location of the slice
                int x;
                std::cout << "Enter the y location of the slice (1 to " << volumePtr->getWidth() << "): ";
                std::cin >> x;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (x < 1 || x > volumePtr->getWidth()) {
                    std::cout << "Invalid x location. Please try again.\n";
                    return;
                }
                try {
                    auto slice = volumePtr->getSliceXZ(x-1);
                    std::string outputPath;
                    std::cout << "Enter output path to save the slice (with .png at the end): ";
                    std::cin >> outputPath;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    slice->save(outputPath);
                    std::cout << "Slice saved successfully to " << outputPath << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Failed to get slice: " << e.what() << std::endl;
                    return;
                }
                break;
            }
            case 4:
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (isInMenu);
}


void process3DFilters(std::shared_ptr<Volume>& volumePtr) {
    display3DFilterMenu();
    int choice;
    std::cin >> choice;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string inputPath, outputPath;
    int kernelSize;
    float sigma;

    switch (choice) {
        case 1: { // 3D Gaussian Blur
            std::cout << "Enter kernel size (e.g., 3 for 3x3x3): ";
            std::cin >> kernelSize;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // check if the kernel size is within the valid range
            if (kernelSize < 3 || kernelSize > 15) {
                std::cout << "Kernel size must be between 3 and 15. Please try again.\n";
                return;
            }
            std::cout << "Enter sigma for the Gaussian filter: ";
            std::cin >> sigma;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // check if the sigma value is within the valid range
            if (sigma < 0.0f) {
                std::cout << "Sigma value must be non-negative. Please try again.\n";
                return;
            }
            Filter::apply3DGaussianBlur(*volumePtr, kernelSize, sigma);

            std::cout << "Do you want to save the filtered volume? (y/n): ";
            char saveChoice;
            std::cin >> saveChoice;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (saveChoice == 'y' || saveChoice == 'Y') {
                std::cout << "Enter the base output directory path (the path of the dictionary): ";
                std::cin >> outputPath;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                // Ensure outputPath ends with a slash to correctly form file paths
                if (outputPath.back() != '/' && outputPath.back() != '\\') {
                    outputPath += "/";
                }
                // ask what name to save the file as
                std::string outputFilename_;
                std::cout << "Enter the output filename (no need to add .png): ";
                std::cin >> outputFilename_;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                int depth = volumePtr->getDepth();
                for (int i = 0; i < depth; ++i) {
                    std::string outputFilename = outputPath + outputFilename_ + "_" + std::to_string(i+1) + ".png";
                    try {
                        volumePtr->getSlice(i)->save(outputFilename);
                        std::cout << "Saved slice " << i + 1 << " to " << outputFilename << std::endl;
                    } catch (const std::exception& e) {
                        std::cerr << "Failed to save slice " << i + 1 << ": " << e.what() << std::endl;
                        return;
                    }
                }
                std::cout << "Filtered volume saved to " << outputPath << std::endl;
            } else if (saveChoice == 'n' || saveChoice == 'N') {
                std::cout << "Filtered volume not saved." << std::endl;
            } else {
                std::cout << "Invalid choice. Please try again.\n";
                return;
            }

            break;
        }
        case 2: { // 3D Median Filter
            std::cout << "Enter kernel size (e.g., 3 for 3x3x3): ";
            std::cin >> kernelSize;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // check if the kernel size is within the valid range
            if (kernelSize < 3 || kernelSize > 15) {
                std::cout << "Kernel size must be between 3 and 15. Please try again.\n";
                return;
            }

            Filter::apply3DMedianFilter(*volumePtr, kernelSize);
//            Filter::apply3DMedianHistFilter(*volumePtr, kernelSize); // faster version

            std::cout << "Do you want to save the filtered volume? (y/n): ";
            char saveChoice;
            std::cin >> saveChoice;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (saveChoice == 'y' || saveChoice == 'Y') {
                std::cout << "Enter the base output directory path (the path of the dictionary): ";
                std::cin >> outputPath;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                // Ensure outputPath ends with a slash to correctly form file paths
                if (outputPath.back() != '/' && outputPath.back() != '\\') {
                    outputPath += "/";
                }
                // ask what name to save the file as
                std::string outputFilename_;
                std::cout << "Enter the output filename(no need to add .png): ";
                std::cin >> outputFilename_;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                int depth = volumePtr->getDepth();
                for (int i = 0; i < depth; ++i) {
                    std::string outputFilename = outputPath + outputFilename_ + "_" + std::to_string(i+1) + ".png";
                    try {
                        volumePtr->getSlice(i)->save(outputFilename);
                        std::cout << "Saved slice " << i + 1 << " to " << outputFilename << std::endl;
                    } catch (const std::exception& e) {
                        std::cerr << "Failed to save slice " << i + 1 << ": " << e.what() << std::endl;
                        return;
                    }
                }
                std::cout << "Filtered volume saved to " << outputPath << std::endl;
            } else if (saveChoice == 'n' || saveChoice == 'N') {
                std::cout << "Filtered volume not saved." << std::endl;
            } else {
                std::cout << "Invalid choice. Please try again.\n";
                return;
            }
            break;
        }
        case 3: // Return to 3D Volume Processing Menu
            return;
        case 4: {// Save the volume now
            std::cout << "Enter the base output directory path: ";
            std::cin >> outputPath;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // Ensure outputPath ends with a slash to correctly form file paths
            if (outputPath.back() != '/' && outputPath.back() != '\\') {
                outputPath += "/";
            }
            // ask what name to save the file as
            std::string outputFilename_;
            std::cout << "Enter the output filename(no need to add .png): ";
            std::cin >> outputFilename_;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            int depth = volumePtr->getDepth();
            for (int i = 0; i < depth; ++i) {
                std::string outputFilename = outputPath + outputFilename_ + "_" + std::to_string(i+1) + ".png";
                try {
                    volumePtr->getSlice(i)->save(outputFilename);
                    std::cout << "Saved slice " << i + 1 << " to " << outputFilename << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Failed to save slice " << i + 1 << ": " << e.what() << std::endl;
                    return;
                }
            }
            std::cout << "Volume saved to " << outputPath << std::endl;
            break;
        }
        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
}


void displayProjectionMenu() {
    std::cout << "\nProjection Options:\n";
    std::cout << "1. Maximum Intensity Projection\n";
    std::cout << "2. Minimum Intensity Projection\n";
    std::cout << "3. Average Intensity Projection\n";
    std::cout << "4. Median Intensity Projection\n";
    std::cout << "5. Return to 3D Volume Processing Menu\n";
    std::cout << "Enter choice: ";
}

void processProjections(std::shared_ptr<Volume>& volumePtr) {
    displayProjectionMenu();
    int choice;
    std::cin >> choice;
    std::string inputPath, outputPath;
    std::vector<std::string> filenames;

    if (choice < 1 || choice > 5) {
        std::cout << "Invalid choice. Please try again.\n";
        return; // Ensure choice is within the valid range
    }

    if (choice == 5) return; // Return to the previous menu
    Image projection;

    // Select z start and end values
    int z_start, z_end;
    // set default values for z_start and z_end
    z_start = -1;
    z_end = -1;
    // ask if user wants to select z_start and z_end
    std::cout << "Default projection from the top to the bottom." << std::endl;
    std::cout << "Do you want to select the start depth(z_start) and the end depth(z_end)? (y/n): ";
    char selectZ;
    std::cin >> selectZ;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (selectZ == 'y' || selectZ == 'Y') {
        std::cout << "Enter start z value (0-" << volumePtr->getDepth() - 1 << "): ";
        std::cin >> z_start;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter end z value (" << z_start << "-" << volumePtr->getDepth() - 1 << "): ";
        std::cin >> z_end;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Generate selected projection type
    switch (choice) {
        case 1:
            projection = Projection::maximumIntensityProjection(*volumePtr, z_start, z_end);
            break;
        case 2:
            projection = Projection::minimumIntensityProjection(*volumePtr, z_start, z_end);
            break;
        case 3:
            projection = Projection::averageIntensityProjection(*volumePtr, z_start, z_end);
            break;
        case 4:
            projection = Projection::medianIntensityProjection(*volumePtr, z_start, z_end);
            break;
        default:
            std::cerr << "An unexpected error occurred." << std::endl;
            return;
    }

    // ask if user wants to save the projection image
    char saveChoice;
    std::cout << "Do you want to save the projection image? (y/n): ";
    std::cin >> saveChoice;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (saveChoice == 'y' || saveChoice == 'Y') {
        std::cout << "Enter the output path for the projection image: ";
        std::cin >> outputPath;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        try {
            projection.save(outputPath);
            std::cout << "Projection image saved to " << outputPath << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Failed to save the projection image: " << e.what() << std::endl;
            return;
        }
    } else if (saveChoice == 'n' || saveChoice == 'N') {
        std::cout << "Projection image not saved." << std::endl;
    } else {
        std::cout << "Invalid choice. Please try again.\n";
        return;
    }
}
void process3DVolumeProcessing(std::shared_ptr<Volume>& volumePtr) {
    bool isInMenu = true;
    int choice3D;
    do {
        display3DProcessingMenu();
        std::cin >> choice3D;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice3D) {
            case 1:
                process3DFilters(volumePtr);
                break;
            case 2:
                processProjections(volumePtr);
                break;
            case 3:
                process3DSlice(volumePtr);
                break;
            case 4:
                isInMenu = false;
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (isInMenu);
}
