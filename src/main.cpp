#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include "bin_converter.h"
#include "cli_parser.h"
#include "constants.h"

int main(int argc, char** argv) {
  cli_parser parser;
  parser.parse(argc, argv);
  std::string output_directory = parser.getOutputDirectory();
  std::vector<std::string> input_files = parser.getInputFiles();
  for(int files_iterator = 0; files_iterator < input_files.size(); files_iterator++) {
    bin_converter::lidarToImage(input_files[files_iterator], output_directory, constants::depth_image_width_default);
  }
}