#!/bin/sh


# rm -r external
# mkdir -p external

# git init

cd external

git submodule add --force https://github.com/opencv/opencv.git 
git submodule init && git submodule update


mkdir -p opencv
cd opencv
mkdir -p build/install
cd build
cmake .. -DWITH_FFMPEG=ON -DCMAKE_INSTALL_PREFIX=./install -Wno-dev && make -j4 && make install -Wno-dev