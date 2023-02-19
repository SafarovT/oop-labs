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

REM �������� �� ���������� ���������� �������� ������� � ���������� ����������� ��������
%PROGRAM% Matrix1.txt >> "%TEMP%\TestingResult1.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\TestingResult1.txt" Matrix1A.txt
del "%TEMP%\TestingResult1.txt
if ERRORLEVEL 1 goto err

REM �������� �� ����������� �������� ������������
%PROGRAM% MatrixWithZeroDeterminant.txt >> "%TEMP%\TestingResult2.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\TestingResult2.txt" ZeroDeterminantOutput.txt
del "%TEMP%\TestingResult2.txt
if ERRORLEVEL 1 goto err

REM �������� ������ c ����������� �������������� < 0.5 ����� �� 0
%PROGRAM% MatrixXY.txt >> "%TEMP%\TestingResult3.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\TestingResult3.txt" MatrixXYA.txt
del "%TEMP%\TestingResult3.txt
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1