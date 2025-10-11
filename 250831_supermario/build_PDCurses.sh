#!/bin/bash

mkdir -p build_PDCurses

cd build_PDCurses

cmake -DCMAKE_BUILD_TYPE=Release -G Ninja ../PDCurses-cmake
cmake --build .
 cd ..
