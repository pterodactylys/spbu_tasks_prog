#!/bin/bash

BUILD_TYPE="Unix Makefiles"
BUILD_SUFFIX="qt"

BUILD_FOLDER="build_${BUILD_SUFFIX}"
SOURCE_FOLDER="src"

if [ ! -d "$BUILD_FOLDER" ]; then
    mkdir "$BUILD_FOLDER"
fi

cd "$BUILD_FOLDER"

cmake -G "$BUILD_TYPE" -DUSE_QT=ON ../"$SOURCE_FOLDER"
cmake --build .

cd ..
