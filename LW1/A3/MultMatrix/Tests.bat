set PROGRAM="%~1"

REM ѕри запуске без параметров ожидаетс€ ненулевой код возврата
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

REM ѕеремножение двух матриц
%PROGRAM% Matrix1.txt Matrix2.txt >> "%TEMP%\Matrix12A.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\Matrix12A" Matrix12A.txt
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1