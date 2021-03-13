@Echo Off

for  %%f in (input/*.txt) do (

	TiitLabworkQuadtree.exe input/%%f
	
	fc /b output.txt output/%%f > nul
	if errorlevel 1 @echo No
	@echo Yes
)

pause
exit



