#include "bin_converter.h"

cv::Mat bin_converter::lidarToImage(std::string input_file_path, 
  std::string output_directory, int depth_image_horizontal_size)
{
  std::ifstream file_reader(input_file_path, 
    std::ios::binary | std::ios::ate | std::ios::in);
  int total_file_size = file_reader.tellg();
  int total_number_of_points = total_file_size / sizeof(float) 
    / constants::kitti_parameters_per_point;
  float lidar_points[total_number_of_points][constants::kitti_parameters_per_point];
  file_reader.seekg(0, std::ios::beg);
  file_reader.read((char *)lidar_points, total_file_size);
  file_reader.close();

  float depth_distance[total_number_of_points];
  for (int iterator = 0; iterator < total_number_of_points; iterator++)
  {
    depth_distance[iterator] = sqrt(pow(lidar_points[iterator][2], 2) +
      sqrt(pow(lidar_points[iterator][0], 2) + pow(lidar_points[iterator][1], 2)));
  }  
  float max_depth_distance = *(std::max_element(depth_distance,
    depth_distance + total_number_of_points));
  float min_depth_distance = *(std::min_element(depth_distance,
    depth_distance + total_number_of_points));

  cv::Mat depth_image = cv::Mat::zeros(64, depth_image_horizontal_size, CV_32FC1);
  cv::Mat depth_image_to_write = cv::Mat::zeros(64, depth_image_horizontal_size, CV_8UC1);

  int vertical_index = 0;
  int previous_horizontal_index = 0;
  for (int iterator = 0; iterator < total_number_of_points && 
    vertical_index < constants::kitti_lidar_number_of_beams; iterator++)
  {
    int horizontal_index = depth_image_horizontal_size * (atan2(lidar_points[iterator][1], 
      lidar_points[iterator][0]) + constants::pi) / (2 * constants::pi);

    depth_image.at<float>(vertical_index, horizontal_index, 0) = depth_distance[iterator];
    depth_image_to_write.at<unsigned char>(vertical_index, horizontal_index, 0) = constants::max_pixel_value
    * (depth_distance[iterator] - min_depth_distance) / (max_depth_distance - min_depth_distance);

    if(previous_horizontal_index > horizontal_index)
      vertical_index++;
    previous_horizontal_index = horizontal_index;
  }

  if(output_directory.find_last_of("/") != (output_directory.length() - 1))
    output_directory += "/";
  std::string image_name = input_file_path.substr(input_file_path.find_last_of("/") + 1, 
    input_file_path.find_last_of(".") - input_file_path.find_last_of("/") - 1);
  cv::imwrite(output_directory + image_name + constants::image_extension, depth_image_to_write);
  return depth_image;
}