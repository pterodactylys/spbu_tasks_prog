@echo off
chcp 1251 > log
del log

set MAIN=oop_main.cpp
set EXE=temp_exe.exe
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

if exist %EXE% del %EXE%

g++ "%CHARSET%" %MAIN% -o %EXE%

%EXE%
