#!/bin/sh

mkdir build
cd build
cmake ..
cd ..
sudo cmake --build build/ --target install
