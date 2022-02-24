set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% -1 > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 256 > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 255 > %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt 255.txt
if ERRORLEVEL 1 goto err

%PROGRAM% 25 > %TEMP%\out.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out.txt 25.txt
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1