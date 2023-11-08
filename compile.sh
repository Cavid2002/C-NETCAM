#!/bin/bash

cd src
./build.sh
cd ..

num=$#

if (( num == 0 )); then
    echo "No parameters provided!"
    exit 1
fi

file=$1

g++ $file.cpp -o ./bin/$file -I/usr/include/opencv4/ -L./src/ -lopencv_calib3d -lopencv_imgproc -lopencv_core -lopencv_ml -lopencv_features2d -lopencv_objdetect -lopencv_flann -lopencv_video -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lNETCAM