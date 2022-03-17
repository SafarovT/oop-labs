set PROGRAM="%~1"

REM При запуске без параметров ожидается ненулевой код возврата
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

REM Перемножение двух матриц
%PROGRAM% Matrix1.txt Matrix2.txt >> "%TEMP%\Matrix12A.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\Matrix12A" Matrix12A.txt
del "%TEMP%\Matrix12A.txt"
if ERRORLEVEL 1 goto err

REM Ввод некоректной матрицы с символами
%PROGRAM% MatrixWithLetters.txt Matrix2.txt
if NOT ERRORLEVEL 1 goto err

REM Ввод некоректной матрицы с недостаточным количеством значений
%PROGRAM% Matrix1.txt MatrixLessNumbers.txt
if NOT ERRORLEVEL 1 goto err


echo OK
exit 0

:err
echo Program testing failed
exit 1