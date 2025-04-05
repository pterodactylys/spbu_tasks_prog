@echo off
chcp 1251 > log
del log

set EXE=shell_sort.exe
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

g++ "%CHARSET%" main.cpp -o %EXE%

%EXE%
