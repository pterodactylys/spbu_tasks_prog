#!/bin/bash

cd /home/andrew/Документы/prog/gitrepo/kmms_prog_2024/251115_qt_example

g++ -o main main.cpp `pkg-config --cflags --libs Qt6Widgets`

./main