#include "cli_parser.h"

cli_parser::cli_parser() {
  this->available_options_map.add_options()((this->help_option_long + this->options_separator + 
    this->help_option).c_str(), this->help_option_description.c_str())(
    (this->output_directory_option_long + this->options_separator + this->output_directory_option).c_str(),
    boost::program_options::value<std::string>(), this->output_directory_option_description.c_str())(
    (this->input_directory_option_long + this->options_separator + this->input_directory_option).c_str(),
    boost::program_options::value<std::string>(), this->input_directory_option_description.c_str())(
    (this->input_file_option_long + this->options_separator + this->input_file_option).c_str(),
    boost::program_options::value<std::string>(), this->input_file_option_description.c_str());
}

cli_parser::~cli_parser() {}

void cli_parser::parse(int args_count, char** args_list) {
  boost::program_options::store(boost::program_options::parse_command_line(
    args_count, args_list, this->available_options_map), this->parsed_options_map);
  boost::program_options::notify(this->parsed_options_map);

  if(this->parsed_options_map.count(this->help_option_long)) {
    std::cout << this->available_options_map << std::endl;
    exit(EXIT_SUCCESS);
  }

  if(!(this->parsed_options_map.count(this->output_directory_option_long))) {
    std::cout << "Specify output path" << std::endl;
    std::cout << this->available_options_map << std::endl;
    exit(EXIT_SUCCESS);
  }

  if(!(this->parsed_options_map.count(this->input_directory_option_long) ||
    this->parsed_options_map.count(this->input_file_option_long))) {
    std::cout << "Specify path of the input files or single input file" << std::endl;
    std::cout << this->available_options_map << std::endl;
    exit(EXIT_SUCCESS);
  }
}

std::string cli_parser::getOutputDirectory() {
  std::string output_directory = this->parsed_options_map[this->output_directory_option_long].as<std::string>();
  if(!(boost::filesystem::exists(output_directory)))
    boost::filesystem::create_directory(output_directory);
  return output_directory;
}

std::vector<std::string> cli_parser::getInputFiles() {
  std::vector<std::string> result;
  if(this->parsed_options_map.count(this->input_directory_option_long)){
    boost::filesystem::path input_directory(this->parsed_options_map[
      this->input_directory_option_long].as<std::string>());
    boost::filesystem::directory_iterator end_iterator;
    for(boost::filesystem::directory_iterator files_iterator(input_directory);
      files_iterator != end_iterator; files_iterator++) {
        if(boost::filesystem::is_regular_file(files_iterator->path()))
          result.push_back(files_iterator->path().string());
      }
  } else {
    result.push_back(this->parsed_options_map[this->input_file_option_long].as<std::string>());
  }
  return result;
}