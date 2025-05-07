@echo off
chcp 1251 > log
del log

set CPP_FILES="main.cpp src/doubly_linked_list.cpp src/doubly_linked_list.hpp"
set EXE=list_main.exe
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

g++ "%CHARSET%" "%CPP_FILES%" -o %EXE%


%EXE%
