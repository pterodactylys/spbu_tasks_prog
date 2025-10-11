#!/bin/bash

MAIN=main_linux.cpp
EXE=example
CHARSET="-finput-charset=utf-8 -fexec-charset=UTF-8"
INCLUDE="-I./lib/PDCurses-cmake"
BINARY="-L./lib/build_PDCurses -lpdcurses"

if [ -f "$EXE" ]; then
    rm "$EXE"
fi

g++ -I./lib/PDCurses-cmake $MAIN -o $EXE -L./lib/build_PDCurses -lpdcurses

if [ -f "$EXE" ]; then
    ./"$EXE"
else
    exit 1
fi