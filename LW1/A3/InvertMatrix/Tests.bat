set PROGRAM="%~1"

REM ��� ������� ��� ���������� ��������� ��������� ��� ��������
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

REM ���� ����������� ������� � ���������
%PROGRAM% MatrixWithLetters.txt
if NOT ERRORLEVEL 1 goto err

REM ���� ����������� ������� � ������������� ����������� ��������
%PROGRAM% MatrixLessNumbers.txt
if NOT ERRORLEVEL 1 goto err

del "%TEMP%\TestingResult1.txt
del "%TEMP%\TestingResult2.txt
del "%TEMP%\TestingResult3.txt

REM �������� �� ���������� ���������� �������� ������� � ���������� ����������� ��������
%PROGRAM% Matrix1.txt >> "%TEMP%\TestingResult1.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\TestingResult1.txt" Matrix1A.txt
if ERRORLEVEL 1 goto err

REM �������� �� ����������� �������� ������������
%PROGRAM% MatrixWithZeroDeterminant.txt >> "%TEMP%\TestingResult2.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\TestingResult2.txt" ZeroDeterminantOutput.txt
if ERRORLEVEL 1 goto err

REM �������� ������, ������� �� ������� ������ � ������������ � ��������� ������������
rem %PROGRAM% MatrixXY.txt >> "%TEMP%\11TestingResult3.txt"
rem if ERRORLEVEL 1 goto err
rem fc.exe "%TEMP%\TestingResult3.txt" MatrixXYA.txt
rem if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1