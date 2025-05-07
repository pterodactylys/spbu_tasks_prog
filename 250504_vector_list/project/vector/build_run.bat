@echo off
chcp 1251 > log
del log

set CPP_FILES="main.cpp src/vector.cpp src/vector.hpp"
set EXE=vector_main.exe
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

g++ "%CHARSET%" "%CPP_FILES%" -o %EXE%


%EXE%
