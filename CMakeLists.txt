#project name and minimum cmake version
cmake_minimum_required(VERSION 2.8.3)
project(lidar-to-depth-image-converter)

#c++ version
add_compile_options(-std=c++14)

#find OpenCV library
find_package(OpenCV REQUIRED)

#find Boost Library
find_package(Boost REQUIRED filesystem program_options)

#add the path of includes to includes search path
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

#build the source code
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} "${SOURCES}")
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${Boost_LIBRARIES})