@ECHO OFF

FOR %%f IN (input/*.txt) DO (

	@ECHO TEST %%~nf
	ConsoleApplication3.exe input/%%f
	
	FC /b output.txt output/%%f > nul
	IF ERRORLEVEL 1 ( 
	@ECHO NO
	) ELSE (
	@ECHO YES
	)

	IF EXIST input.txt DEL input.txt
	IF EXIST output.txt DEL output.txt
)

PAUSE
EXIT