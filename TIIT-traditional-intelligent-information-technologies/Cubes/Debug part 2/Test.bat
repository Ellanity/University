@echo off
@echo TEST %2
@echo TEST %2 >> result.txt
copy %2 input.txt > nul
Timer %1 1000 65536 >> result.txt
Check %2 %2.a output.txt test.txt
Check %2 %2.a output.txt
type test.txt >> result.txt
if exist test.txt del test.txt
if exist input.txt del input.txt
if exist output.txt del output.txt
pause
