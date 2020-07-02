# KITTI LiDAR to Depth Image Converter
This repository contains C++ based code implementation that converts the lidar frames of KITTI dataset into a 2D depth image. The idea behind this code was inspired from the [**Fast Range Image-based Segmentation of Sparse 3D Laser Scans for Online Operation**](https://ieeexplore.ieee.org/document/7759050) paper.
## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. **Please be noted that this code is tested on Ubuntu OS only**.
### Prerequisites
- Aptitude Dependencies
```bash
$ sudo apt update
$ sudo apt -y install git curl wget cmake build-essential lsb-core unzip
```
- Boost
```bash
$ wget https://sourceforge.net/projects/boost/files/boost/1.62.0/boost_1_62_0.tar.gz
$ tar -xzvf boost_1_62_0.tar.gz
$ cd boost_1_62_0
$ mkdir build
$ ./bootstrap.sh --with-libraries=filesystem --with-libraries=program_options
$ sudo ./b2 install -j$(nproc)
```
- OpenCV
```bash
$ wget https://github.com/opencv/opencv/archive/3.4.8.zip
$ unzip 3.4.8.zip
$ cd opencv-3.4.8
$ mkdir build
$ cd build
$ cmake ..
$ make -j
$ sudo make install
```
### Installation
You can skip this step and use the already built executable in github actions.
```bash
$ git clone https://github.com/ahmedfawzyelaraby/ros-images-extractor.git
$ cd ros-images-extractor
$ mkdir build
$ cd build
$ cmake ..
$ make -j
```
### Usage
```bash
$ ./ros-bag-image-extractor -h # this command will get you the instructions you need to run the code.
```
