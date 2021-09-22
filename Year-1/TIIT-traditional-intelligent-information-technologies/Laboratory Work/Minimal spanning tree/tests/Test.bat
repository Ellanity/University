@echo off
@echo TEST %2
@echo TEST %2 >> result.txt
copy %2.in input.txt >> result.txt
Timer %1 1000 16384 >> result.txt
fc %2.out output.txt /w >> result.txt
if exist input.txt del input.txt
if exist output.txt del output.txt