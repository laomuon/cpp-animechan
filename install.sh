#!/bin/sh

mkdir build
cd build
cmake ..
cd ..
cmake --build build/
sudo cmake --install build/ --config Release
