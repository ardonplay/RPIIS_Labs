@echo off
@echo Test %1
@echo Test %1 >>%2.res
if exist input.txt del input.txt>Nul
if exist output.txt del output.txt>Nul
copy %1.in input.txt >nul
Timer %2.exe 2000 131072 >>%2.res
FC output.txt %1.out /w >>%2.res