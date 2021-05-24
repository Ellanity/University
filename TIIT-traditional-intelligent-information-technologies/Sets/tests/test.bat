@ECHO OFF

FOR %%f IN (input/*.txt) DO (

	TYPE input\%%f > input.txt
	sets.exe
	FC /B output.txt output/%%f > NUL
	IF ERRORLEVEL 1 (
	@ECHO NO
	) ELSE (
	@ECHO YES
	)
)

PAUSE
EXIT



