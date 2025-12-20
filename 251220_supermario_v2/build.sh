#!/bin/bash

BUILD_TYPE="Unix Makefiles"
BUILD_SUFFIX="make"

BUILD_FOLDER="build_${BUILD_SUFFIX}"
SOURCE_FOLDER="src"

if [ ! -d "$BUILD_FOLDER" ]; then
    mkdir "$BUILD_FOLDER"
fi

cd "$BUILD_FOLDER"

cmake -G "$BUILD_TYPE" ../"$SOURCE_FOLDER"
cmake --build .

cd ..
