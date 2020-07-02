#!/bin/bash

mkdir build
cd $(pwd)/build
cmake ..
make -j
