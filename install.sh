#!/bin/sh

git submodule init
git submodule sync --recursive
git submodule update
mkdir build
cd build
cmake ..
cd ..
cmake --build build/
sudo cmake --install build/ --config Release
