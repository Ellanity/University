@echo off
@echo Test %1
@echo Test %1 >>%2.res
if exist gnome.in del gnome.in>Nul
if exist gnome.out del gnome.out>Nul
copy %1 gnome.in >nul
Timer %2.exe 2000 65536 >>%2.res
if exist gnome.out (
goto next
) else (@echo No output file! >>%2.res
)
goto end
:next
Check.exe %1 gnome.out %1.a >>%2.res
:end