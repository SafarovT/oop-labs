set PROGRAM="%~1"

REM При запуске без параметров ожидается ненулевой код возврата
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% Matrix1.txt >> "%TEMP%\1TestResultWithMatrix1.txt"
if ERRORLEVEL 1 goto err
rem fc.exe "%TEMP%\Matrix12A" Matrix12A.txt
rem del "%TEMP%\Matrix12A.txt"
rem if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1