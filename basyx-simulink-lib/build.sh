#!/bin/bash

rm -rf ./build/
cmake -B build -S .
cd build
make -j
echo "Executing app"
./app
