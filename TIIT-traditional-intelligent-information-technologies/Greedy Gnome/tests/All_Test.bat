@echo off
if %1. == . goto noparm
if exist %1.res del %1.res
echo Task: Жадный гном >%1.res
echo Program to test: %1 >>%1.res
echo ................ >>%1.res 
for %%i in (01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45) do call test.bat %%i %1
if exist gnome.in del gnome.in>Nul
if exist gnome.out del gnome.out>Nul
pause
exit
:noparm
@echo Usage: test_all filename
@echo filename must be without extension!
