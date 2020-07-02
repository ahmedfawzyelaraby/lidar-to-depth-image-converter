#ifndef CONSTANTS
#define CONSTANTS

#include <string>

namespace constants {
  static const int kitti_parameters_per_point = 4;
  static const int kitti_lidar_number_of_beams = 64;
  static const int depth_image_width_default = 1440;
  static const float kitti_lidar_vertical_resolution = 26.9;
  
  static const unsigned char max_pixel_value = 255;
  static const double complete_circle_degrees = 360.0;
  static const double half_circle_degrees = 180.0;
  static const double pi = 3.14159265;

  static const std::string image_extension = ".png";
}

#endif