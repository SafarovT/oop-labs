set PROGRAM="%~1"

REM ѕри запуске без параметров ожидаетс€ ненулевой код возврата
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

REM “ест с несколькими заливками, различных фигур
%PROGRAM% AverageTest.txt "%TEMP%\AverageTestOutput.txt"
if ERRORLEVEL 1 goto err
fc "%TEMP%\AverageTestOutput.txt" AverageTestAnswer.txt
if ERRORLEVEL 1 goto err

REM “ест с заливкой с выходом за контур
%PROGRAM% TestWithLeak.txt "%TEMP%\TestWithLeakOutput.txt"
if ERRORLEVEL 1 goto err
fc "%TEMP%\TestWithLeakOutput.txt" TestWithLeakAnswer.txt
if ERRORLEVEL 1 goto err

%PROGRAM% Test.txt "%TEMP%\!TestOutput.txt"
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1