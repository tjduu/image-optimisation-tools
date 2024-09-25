# Advanced Programming Group Ziggurat Image Processing Tool

This project is an advanced set of image processing tools, offering a series of powerful functionalities for handling both 2D and 3D images. Users can perform various operations on images through a user-friendly interface, as detailed in the basic usage section. This project aims to provide a user-friendly image processing platform for research, education, or personal enthusiasts.

## Getting Started

### Prerequisites

This project requires the following environment:

- A C++ compilation environment that supports the C++17 standard (GCC, Clang, or MSVC recommended)
- CMake version 3.27 or higher
- stb_image and stb_image_write libraries, which are included in the project

### Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/ese-msc-2023/advanced-programming-group-ziggurat.git
   cd advanced_programming_group_ziggurat
   ```

2. **Build the Project**

   Create a build directory in the project root and initialize CMake configuration:

   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. **Compile the Project**

   Build the project using CMake:

   ```bash
   cmake --build .
   ```

   Or use Make (if on a Unix-like system):

   ```bash
   make
   ```

4. **Run the Program**

   After compilation, the executable file will be located in the `build` directory:

   ```bash
   ./advanced_programming_group_ziggurat
   ```

   Additionally, a `tests` folder will be generated under `build`, containing test executables:

   ```bash
   cd tests
   ./runTests
   ```

## Usage

Here is a concise user manual intended to guide users on how to operate the "Ziggurat" image and volume processing tool.

### Before You Begin
- Ensure your system has installed all necessary libraries and dependencies to run this project code.
- This tool supports a range of processes for 2D images and 3D volume data, including color correction, blurring, and edge detection.
- The input path for the 2D image or 3D volume data directory should be valid and accessible.

### Starting the Program

After successfully compiling the Ziggurat Image Processing Tool, you can start the program by executing the generated binary. Upon launch, the main menu provides you with three primary options:

1. **2D Image Processing**: Choose this option to perform operations on 2D images.
2. **3D Volume Processing**: Select this for manipulating 3D volume data.
3. **Quit**: Exit the application.

#### Navigating the Menus

Interaction with the tool is primarily through the console. When prompted, enter the number corresponding to your choice and press Enter.

### 2D Image Processing

After selecting the 2D Image Processing option, you will be prompted to enter the path to your image file. Following the image path input, you will access the 2D processing submenu, where you can choose among several operations, including:

- **Color Correction**: Adjust the image's color properties, such as converting to grayscale or adjusting brightness.
- **Image Blur**: Apply different blurring effects to the image.
- **Edge Detection**: Detect edges within the image using various algorithms.

Each operation may require additional inputs (e.g., brightness level, kernel size). Follow the on-screen prompts to input these values.

### 3D Volume Processing

Choosing the 3D Volume Processing option prompts you to enter the directory path containing your 3D volume data. The tool expects this directory to contain `.png` files representing slices of the volume. In the 3D processing submenu, you can:

- **Apply 3D Filters**: Select from available filters to apply to the entire volume.
- **Generate Projections**: Create 2D projections from the 3D volume based on different criteria.
- **Get Slice**: Extract specific slices from the volume for closer examination.

Like with 2D image processing, you may need to provide additional information depending on the chosen operation.

### Saving Your Work

After completing any processing operation, you will be prompted to save your changes. You must specify the output path for the saved file, including the `.png` extension for images. If you choose not to save, your changes will not be retained.

### Error Handling

Should you enter an invalid choice or encounter an error during file loading or saving, the program will display an error message and may prompt you to try again.

### Exiting the Program

You can exit the program at any time by choosing the Quit option from the main menu or by using your console's standard methods to terminate the application (e.g., Ctrl+C).

Thank you for using the Ziggurat Image Processing Tool. We hope this guide helps you make the most of our software for your image processing needs.

By following the steps and instructions above, users should be able to effectively utilize the "Ziggurat" project code for image and volume data processing.

## Technology Stack

- C++
- CMake
- stb_image/stb_image_write

## Version Control

This project uses Git for version control.

## Team Members

This project was developed by the Ziggurat team, with members and their GitHub usernames listed below:

- Tianju (Tim) Du - [@edsml-td323](https://github.com/edsml-td323)
- Melissa Sim - [@acse-mys20](https://github.com/acse-mys20)
- Xiaoye Zhang - [@acse-xz4019](https://github.com/acse-xz4019)
- Wenhao Hong - [@acse-wh623](https://github.com/acse-wh623)
- Javonne Porter - [@acse-jp2923](https://github.com/acse-jp2923)
- Wenxin Li - [@edsml-wl123](https://github.com/edsml-wl123)

We appreciate the contributions of each team member, whose efforts have made this project a reality.

## Structure of the folder

```
.
├── AdvProgGroupAssignment2024.pdf
├── CMakeLists.txt
├── Doxyfile
├── GroupProject-ReportTemplate.docx
├── GroupProject-Zigguart-Report.pdf
├── Images
│   ├── dimorphos.png
│   ├── gracehopper.png
│   ├── stinkbug.png
│   ├── tienshan.png
│   ├── vh_anatomy.png
│   ├── vh_anatomy_sp15.png
│   └── vh_ct.png
├── LICENSE
├── Output
│   ├── 1-grayscale
│   │   ├── gracehopper.png
│   │   └── tienshan.png
│   ├── 2-brightness
│   │   ├── gracehopper_minus100.png
│   │   ├── gracehopper_plus100.png
│   │   ├── stinkbug_minus50.png
│   │   └── stinkbug_plus50.png
│   ├── 3-histogram
│   │   ├── vh_anatomy_HSL.png
│   │   ├── vh_anatomy_HSV.png
│   │   └── vh_ct.png
│   ├── 4-threshold
│   │   ├── stinkbug_80.png
│   │   ├── tienshan_HSL_127.png
│   │   ├── tienshan_HSV_127.png
│   │   └── vh_ct_80.png
│   ├── 5-saltandpepper
│   │   ├── gracehopper_10.png
│   │   ├── gracehopper_25.png
│   │   ├── stinkbug_10.png
│   │   └── stinkbug_40.png
│   ├── 6-blur
│   │   ├── box
│   │   │   ├── stinkbug_3x3.png
│   │   │   ├── stinkbug_5x5.png
│   │   │   ├── tienshan_3x3.png
│   │   │   ├── tienshan_5x5.png
│   │   │   ├── vh_anatomy_sp15_3x3.png
│   │   │   └── vh_anatomy_sp15_5x5.png
│   │   ├── gaussian
│   │   │   ├── stinkbug_3x3.png
│   │   │   ├── stinkbug_5x5.png
│   │   │   ├── tienshan_3x3.png
│   │   │   ├── tienshan_5x5.png
│   │   │   ├── vh_anatomy_sp15_3x3.png
│   │   │   └── vh_anatomy_sp15_5x5.png
│   │   └── median
│   │       ├── stinkbug_3x3.png
│   │       ├── stinkbug_5x5.png
│   │       ├── tienshan_3x3.png
│   │       ├── tienshan_5x5.png
│   │       ├── vh_anatomy_sp15_3x3.png
│   │       └── vh_anatomy_sp15_5x5.png
│   ├── 7-edgedetection
│   │   ├── prewitt
│   │   │   ├── dimorphos.png
│   │   │   ├── gracehopper.png
│   │   │   ├── stinkbug.png
│   │   │   ├── tienshan.png
│   │   │   └── vh_anatomy.png
│   │   ├── robertscross
│   │   │   ├── dimorphos.png
│   │   │   ├── gracehopper.png
│   │   │   ├── stinkbug.png
│   │   │   ├── tienshan.png
│   │   │   └── vh_anatomy.png
│   │   ├── scharr
│   │   │   ├── dimorphos.png
│   │   │   ├── gracehopper.png
│   │   │   ├── stinkbug.png
│   │   │   ├── tienshan.png
│   │   │   └── vh_anatomy.png
│   │   └── sobel
│   │       ├── dimorphos.png
│   │       ├── gracehopper.png
│   │       ├── stinkbug.png
│   │       ├── tienshan.png
│   │       └── vh_anatomy.png
│   ├── 8-confuciusornis
│   │   ├── aip-gaussian_3x3x3.png
│   │   ├── aip-gaussian_5x5x5.png
│   │   ├── aip-median_3x3x3.png
│   │   ├── aip-median_5x5x5.png
│   │   ├── aip-nofilter.png
│   │   ├── mip-gaussian-3x3x3.png
│   │   ├── mip-gaussian-5x5x5.png
│   │   ├── mip-median-3x3x3.png
│   │   ├── mip-median-5x5x5.png
│   │   ├── mip-nofilter.png
│   │   ├── slice_xz_y420.png
│   │   ├── slice_yz_x400.png
│   │   ├── thinslab_10_70_nofilter_aip.png
│   │   └── thinslab_10_70_nofilter_mip.png
│   ├── 9-fracture
│   │   ├── minip-gaussian_3x3x3.png
│   │   ├── minip-gaussian_5x5x5.png
│   │   ├── minip-median_3x3x3.png
│   │   ├── minip-median_5x5x5.png
│   │   ├── minip-nofilter.png
│   │   ├── mip-gaussian-3x3x3.png
│   │   ├── mip-gaussian-5x5x5.png
│   │   ├── mip-median-3x3x3.png
│   │   ├── mip-median-5x5x5.png
│   │   ├── mip-nofilter.png
│   │   ├── slice_xz_y138.png
│   │   ├── slice_yz_x275.png
│   │   ├── thinslab_276_476_nofilter_aip.png
│   │   └── thinslab_276_476_nofilter_mip.png
│   └── README.md
├── README.md
├── References.md
├── Scans
│   └── README.md
├── docs
│   └── html
│       ├── Filter_8cpp.html
│       ├── Filter_8cpp__incl.map
│       ├── Filter_8cpp__incl.md5
│       ├── Filter_8cpp__incl.png
│       ├── Filter_8cpp_source.html
│       ├── Image_8cpp.html
│       ├── Image_8cpp.js
│       ├── Image_8cpp__incl.map
│       ├── Image_8cpp__incl.md5
│       ├── Image_8cpp__incl.png
│       ├── Image_8cpp_source.html
│       ├── Projection_8cpp.html
│       ├── Projection_8cpp__incl.map
│       ├── Projection_8cpp__incl.md5
│       ├── Projection_8cpp__incl.png
│       ├── Projection_8cpp_source.html
│       ├── Slice_8cpp.html
│       ├── Slice_8cpp__incl.map
│       ├── Slice_8cpp__incl.md5
│       ├── Slice_8cpp__incl.png
│       ├── Slice_8cpp_source.html
│       ├── Volume_8cpp.html
│       ├── Volume_8cpp.js
│       ├── Volume_8cpp__incl.map
│       ├── Volume_8cpp__incl.md5
│       ├── Volume_8cpp__incl.png
│       ├── Volume_8cpp_a236da76f72861ea5da08f8b3f19dda3a_icgraph.map
│       ├── Volume_8cpp_a236da76f72861ea5da08f8b3f19dda3a_icgraph.md5
│       ├── Volume_8cpp_a236da76f72861ea5da08f8b3f19dda3a_icgraph.png
│       ├── Volume_8cpp_a931100806e4dc14dd0f1c25cb05e6d74_cgraph.map
│       ├── Volume_8cpp_a931100806e4dc14dd0f1c25cb05e6d74_cgraph.md5
│       ├── Volume_8cpp_a931100806e4dc14dd0f1c25cb05e6d74_cgraph.png
│       ├── Volume_8cpp_source.html
│       ├── bc_s.png
│       ├── bc_sd.png
│       ├── clipboard.js
│       ├── closed.png
│       ├── cookie.js
│       ├── dir_68267d1309a1af8e8297ef4c3efbcdba.html
│       ├── dir_68267d1309a1af8e8297ef4c3efbcdba.js
│       ├── doc.svg
│       ├── docd.svg
│       ├── doxygen.css
│       ├── doxygen.svg
│       ├── doxygen_crawl.html
│       ├── dynsections.js
│       ├── files.html
│       ├── files_dup.js
│       ├── folderclosed.svg
│       ├── folderclosedd.svg
│       ├── folderopen.svg
│       ├── folderopend.svg
│       ├── globals.html
│       ├── globals_defs.html
│       ├── globals_func.html
│       ├── graph_legend.html
│       ├── graph_legend.md5
│       ├── graph_legend.png
│       ├── index.html
│       ├── jquery.js
│       ├── main_8cpp.html
│       ├── main_8cpp.js
│       ├── main_8cpp__incl.map
│       ├── main_8cpp__incl.md5
│       ├── main_8cpp__incl.png
│       ├── main_8cpp_a1037d85dbfd2be3f05de3d4aebcf88c6_icgraph.map
│       ├── main_8cpp_a1037d85dbfd2be3f05de3d4aebcf88c6_icgraph.md5
│       ├── main_8cpp_a1037d85dbfd2be3f05de3d4aebcf88c6_icgraph.png
│       ├── main_8cpp_a12769675b9a59861b6adb0ab6d794d35_icgraph.map
│       ├── main_8cpp_a12769675b9a59861b6adb0ab6d794d35_icgraph.md5
│       ├── main_8cpp_a12769675b9a59861b6adb0ab6d794d35_icgraph.png
│       ├── main_8cpp_a2bb21b25ad4fb7b50327673cb0b89232_cgraph.map
│       ├── main_8cpp_a2bb21b25ad4fb7b50327673cb0b89232_cgraph.md5
│       ├── main_8cpp_a2bb21b25ad4fb7b50327673cb0b89232_cgraph.png
│       ├── main_8cpp_a2bb21b25ad4fb7b50327673cb0b89232_icgraph.map
│       ├── main_8cpp_a2bb21b25ad4fb7b50327673cb0b89232_icgraph.md5
│       ├── main_8cpp_a2bb21b25ad4fb7b50327673cb0b89232_icgraph.png
│       ├── main_8cpp_a3f59019099538e8aa23e72a544461c26_icgraph.map
│       ├── main_8cpp_a3f59019099538e8aa23e72a544461c26_icgraph.md5
│       ├── main_8cpp_a3f59019099538e8aa23e72a544461c26_icgraph.png
│       ├── main_8cpp_a45a9819c2302c376dbf21c50052ae0ec_cgraph.map
│       ├── main_8cpp_a45a9819c2302c376dbf21c50052ae0ec_cgraph.md5
│       ├── main_8cpp_a45a9819c2302c376dbf21c50052ae0ec_cgraph.png
│       ├── main_8cpp_a45a9819c2302c376dbf21c50052ae0ec_icgraph.map
│       ├── main_8cpp_a45a9819c2302c376dbf21c50052ae0ec_icgraph.md5
│       ├── main_8cpp_a45a9819c2302c376dbf21c50052ae0ec_icgraph.png
│       ├── main_8cpp_a4fe328e14db2e322932aec03caf0cba0_cgraph.map
│       ├── main_8cpp_a4fe328e14db2e322932aec03caf0cba0_cgraph.md5
│       ├── main_8cpp_a4fe328e14db2e322932aec03caf0cba0_cgraph.png
│       ├── main_8cpp_a4fe328e14db2e322932aec03caf0cba0_icgraph.map
│       ├── main_8cpp_a4fe328e14db2e322932aec03caf0cba0_icgraph.md5
│       ├── main_8cpp_a4fe328e14db2e322932aec03caf0cba0_icgraph.png
│       ├── main_8cpp_a54e0d21fe46990a6e13e13af155535e8_icgraph.map
│       ├── main_8cpp_a54e0d21fe46990a6e13e13af155535e8_icgraph.md5
│       ├── main_8cpp_a54e0d21fe46990a6e13e13af155535e8_icgraph.png
│       ├── main_8cpp_a6e32f80d0cb47c24bbcebeed3e6b0b79_cgraph.map
│       ├── main_8cpp_a6e32f80d0cb47c24bbcebeed3e6b0b79_cgraph.md5
│       ├── main_8cpp_a6e32f80d0cb47c24bbcebeed3e6b0b79_cgraph.png
│       ├── main_8cpp_a6e32f80d0cb47c24bbcebeed3e6b0b79_icgraph.map
│       ├── main_8cpp_a6e32f80d0cb47c24bbcebeed3e6b0b79_icgraph.md5
│       ├── main_8cpp_a6e32f80d0cb47c24bbcebeed3e6b0b79_icgraph.png
│       ├── main_8cpp_a7a3226a72874a6e9dff534869ccaf811_cgraph.map
│       ├── main_8cpp_a7a3226a72874a6e9dff534869ccaf811_cgraph.md5
│       ├── main_8cpp_a7a3226a72874a6e9dff534869ccaf811_cgraph.png
│       ├── main_8cpp_a7a3226a72874a6e9dff534869ccaf811_icgraph.map
│       ├── main_8cpp_a7a3226a72874a6e9dff534869ccaf811_icgraph.md5
│       ├── main_8cpp_a7a3226a72874a6e9dff534869ccaf811_icgraph.png
│       ├── main_8cpp_a7d53df4fb63141b2b44bab0d2f65b9ec_icgraph.map
│       ├── main_8cpp_a7d53df4fb63141b2b44bab0d2f65b9ec_icgraph.md5
│       ├── main_8cpp_a7d53df4fb63141b2b44bab0d2f65b9ec_icgraph.png
│       ├── main_8cpp_a80d752db517acaf02fc489a7a124cf8d_icgraph.map
│       ├── main_8cpp_a80d752db517acaf02fc489a7a124cf8d_icgraph.md5
│       ├── main_8cpp_a80d752db517acaf02fc489a7a124cf8d_icgraph.png
│       ├── main_8cpp_a8f2071efda55973b46f716a2f0b94994_icgraph.map
│       ├── main_8cpp_a8f2071efda55973b46f716a2f0b94994_icgraph.md5
│       ├── main_8cpp_a8f2071efda55973b46f716a2f0b94994_icgraph.png
│       ├── main_8cpp_a9b4a43bab40fe7d971e6f0f7ff1f8186_cgraph.map
│       ├── main_8cpp_a9b4a43bab40fe7d971e6f0f7ff1f8186_cgraph.md5
│       ├── main_8cpp_a9b4a43bab40fe7d971e6f0f7ff1f8186_cgraph.png
│       ├── main_8cpp_a9b4a43bab40fe7d971e6f0f7ff1f8186_icgraph.map
│       ├── main_8cpp_a9b4a43bab40fe7d971e6f0f7ff1f8186_icgraph.md5
│       ├── main_8cpp_a9b4a43bab40fe7d971e6f0f7ff1f8186_icgraph.png
│       ├── main_8cpp_aa77a727dcfe7b7bd55497442fa614d0f_cgraph.map
│       ├── main_8cpp_aa77a727dcfe7b7bd55497442fa614d0f_cgraph.md5
│       ├── main_8cpp_aa77a727dcfe7b7bd55497442fa614d0f_cgraph.png
│       ├── main_8cpp_aa77a727dcfe7b7bd55497442fa614d0f_icgraph.map
│       ├── main_8cpp_aa77a727dcfe7b7bd55497442fa614d0f_icgraph.md5
│       ├── main_8cpp_aa77a727dcfe7b7bd55497442fa614d0f_icgraph.png
│       ├── main_8cpp_abc8231150c0b2319fa16d80c965312d0_cgraph.map
│       ├── main_8cpp_abc8231150c0b2319fa16d80c965312d0_cgraph.md5
│       ├── main_8cpp_abc8231150c0b2319fa16d80c965312d0_cgraph.png
│       ├── main_8cpp_abc8231150c0b2319fa16d80c965312d0_icgraph.map
│       ├── main_8cpp_abc8231150c0b2319fa16d80c965312d0_icgraph.md5
│       ├── main_8cpp_abc8231150c0b2319fa16d80c965312d0_icgraph.png
│       ├── main_8cpp_acb234e861d609a01a27fcefe230538bc_icgraph.map
│       ├── main_8cpp_acb234e861d609a01a27fcefe230538bc_icgraph.md5
│       ├── main_8cpp_acb234e861d609a01a27fcefe230538bc_icgraph.png
│       ├── main_8cpp_ae15cf3bf488be52b3b854f6a9f2e4a34_icgraph.map
│       ├── main_8cpp_ae15cf3bf488be52b3b854f6a9f2e4a34_icgraph.md5
│       ├── main_8cpp_ae15cf3bf488be52b3b854f6a9f2e4a34_icgraph.png
│       ├── main_8cpp_ae66f6b31b5ad750f1fe042a706a4e3d4_cgraph.map
│       ├── main_8cpp_ae66f6b31b5ad750f1fe042a706a4e3d4_cgraph.md5
│       ├── main_8cpp_ae66f6b31b5ad750f1fe042a706a4e3d4_cgraph.png
│       ├── main_8cpp_aed514c284993caa02f7f3cb5e50cfd33_icgraph.map
│       ├── main_8cpp_aed514c284993caa02f7f3cb5e50cfd33_icgraph.md5
│       ├── main_8cpp_aed514c284993caa02f7f3cb5e50cfd33_icgraph.png
│       ├── main_8cpp_source.html
│       ├── menu.js
│       ├── menudata.js
│       ├── minus.svg
│       ├── minusd.svg
│       ├── nav_f.png
│       ├── nav_fd.png
│       ├── nav_g.png
│       ├── nav_h.png
│       ├── nav_hd.png
│       ├── navtree.css
│       ├── navtree.js
│       ├── navtreedata.js
│       ├── navtreeindex0.js
│       ├── open.png
│       ├── plus.svg
│       ├── plusd.svg
│       ├── resize.js
│       ├── search
│       │   ├── all_0.js
│       │   ├── all_1.js
│       │   ├── all_2.js
│       │   ├── all_3.js
│       │   ├── all_4.js
│       │   ├── all_5.js
│       │   ├── all_6.js
│       │   ├── all_7.js
│       │   ├── all_8.js
│       │   ├── close.svg
│       │   ├── defines_0.js
│       │   ├── files_0.js
│       │   ├── files_1.js
│       │   ├── files_2.js
│       │   ├── files_3.js
│       │   ├── files_4.js
│       │   ├── files_5.js
│       │   ├── functions_0.js
│       │   ├── functions_1.js
│       │   ├── functions_2.js
│       │   ├── functions_3.js
│       │   ├── functions_4.js
│       │   ├── functions_5.js
│       │   ├── mag.svg
│       │   ├── mag_d.svg
│       │   ├── mag_sel.svg
│       │   ├── mag_seld.svg
│       │   ├── search.css
│       │   ├── search.js
│       │   └── searchdata.js
│       ├── splitbar.png
│       ├── splitbard.png
│       ├── sync_off.png
│       ├── sync_on.png
│       ├── tab_a.png
│       ├── tab_ad.png
│       ├── tab_b.png
│       ├── tab_bd.png
│       ├── tab_h.png
│       ├── tab_hd.png
│       ├── tab_s.png
│       ├── tab_sd.png
│       └── tabs.css
├── include
│   └── myproject
│       ├── Filter.h
│       ├── Image.h
│       ├── Projection.h
│       ├── Slice.h
│       ├── Volume.h
│       ├── stb_image.h
│       └── stb_image_write.h
├── src
│   ├── Filter.cpp
│   ├── Image.cpp
│   ├── Projection.cpp
│   ├── Slice.cpp
│   ├── Volume.cpp
│   └── main.cpp
└── tests
    ├── CMakeLists.txt
    ├── FilterTests.cpp
    ├── FilterTests.h
    ├── ImageTests.cpp
    ├── ImageTests.h
    ├── ProjectionTests.cpp
    ├── ProjectionTests.h
    ├── SliceTests.cpp
    ├── SliceTests.h
    ├── SpeedTests.cpp
    ├── SpeedTests.h
    ├── VolumeTests.cpp
    ├── VolumeTests.h
    ├── test_images
    │   ├── image_0.png
    │   ├── image_1.png
    │   ├── image_2.png
    │   ├── image_3.png
    │   ├── image_4.png
    │   ├── image_5.png
    │   ├── image_6.png
    │   ├── image_7.png
    │   ├── image_8.png
    │   ├── image_9.png
    │   └── projection_test
    │       ├── image_0.png
    │       ├── image_1.png
    │       ├── image_2.png
    │       ├── image_3.png
    │       ├── image_4.png
    │       ├── image_5.png
    │       ├── image_6.png
    │       ├── image_7.png
    │       ├── image_8.png
    │       └── image_9.png
    └── test_main.cpp
```

## Acknowledgements

Our project has referenced code from OpenAI's ChatGPT during its development. We are extremely grateful for OpenAI's innovative work in the field of artificial intelligence, which has provided valuable resources and insights for our project development.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
