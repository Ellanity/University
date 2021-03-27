@echo off
if exist result.txt del result.txt
for %%i in (01, 02, 03, 04, 05, 06, 07, 08, 09, 10, 11) do call test.bat %1 %%i
pause