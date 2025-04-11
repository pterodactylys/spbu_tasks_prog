@echo off
chcp 1251 > log
del log

set CPP_FILES="main.cpp src/long_number.cpp src/long_number.hpp"
set EXE=ln_main.exe
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

g++ "%CHARSET%" "%CPP_FILES%" -o %EXE%


%EXE%
