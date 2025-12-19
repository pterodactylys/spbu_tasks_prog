#!/bin/bash

BUILD_TYPE=Ninja
BUILD_SUFFIX=ninja

BUILD_FOLDER=build_${BUILD_SUFFIX}
SOURCE_FOLDER=.
IMG_FOLDER=img

mkdir -p ${BUILD_FOLDER}

cd ${BUILD_FOLDER}

cmake -G ${BUILD_TYPE} ../${SOURCE_FOLDER}
cmake --build .

mkdir -p ${IMG_FOLDER}
cp ../${IMG_FOLDER}/grustnii-smail.png ${IMG_FOLDER}/

cd ..
