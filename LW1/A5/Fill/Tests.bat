set PROGRAM="%~1"

REM При запуске без параметров ожидается ненулевой код возврата
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

del "%TEMP%\!TestOutput.txt

%PROGRAM% Test1.txt "%TEMP%\!TestOutput.txt"
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1