#ifndef BIN_CONVERTER
#define BIN_CONVERTER

#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

#include "constants.h"

class bin_converter
{
public:
  static cv::Mat lidarToImage(std::string input_file_path, std::string output_directory,
    int depth_image_horizontal_size);
};

#endif