set PROGRAM="%~1"

REM ѕри запуске без параметров ожидаетс€ ненулевой код возврата
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

REM ¬вод некоректной матрицы с символами
%PROGRAM% MatrixWithLetters.txt
if NOT ERRORLEVEL 1 goto err

REM ¬вод некоректной матрицы с недостаточным количеством значений
%PROGRAM% MatrixLessNumbers.txt
if NOT ERRORLEVEL 1 goto err

del "%TEMP%\TestingResult1.txt
del "%TEMP%\TestingResult2.txt
del "%TEMP%\TestingResult3.txt

REM ѕроверка на корректное нахождение обратной матрицы с корректной изначальной матрицой
%PROGRAM% Matrix1.txt >> "%TEMP%\TestingResult1.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\TestingResult1.txt" Matrix1A.txt
if ERRORLEVEL 1 goto err

REM ѕроверка на определение нулевого определител€
%PROGRAM% MatrixWithZeroDeterminant.txt >> "%TEMP%\TestingResult2.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\TestingResult2.txt" ZeroDeterminantOutput.txt
if ERRORLEVEL 1 goto err

REM ѕроверка случа€, схожего со случаем работы с координатами в двумерном пространстве
rem %PROGRAM% MatrixXY.txt >> "%TEMP%\11TestingResult3.txt"
rem if ERRORLEVEL 1 goto err
rem fc.exe "%TEMP%\TestingResult3.txt" MatrixXYA.txt
rem if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1