
g++ -c NET.cpp -o NET.o
g++ -c CAMERA.cpp -o CAMERA.o -I/usr/include/opencv4/
ar -rcs libNETCAM.a NET.o CAMERA.o 
rm CAMERA.o NET.o