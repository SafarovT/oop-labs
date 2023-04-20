set PROGRAM="%~1"

REM ��� ������� ��� ���������� ��������� ��������� ��� ��������
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

REM ���� � ����������� ���������, ��������� �����
%PROGRAM% AverageTest.txt "%TEMP%\AverageTestOutput.txt"
if ERRORLEVEL 1 goto err
fc "%TEMP%\AverageTestOutput.txt" AverageTestAnswer.txt
if ERRORLEVEL 1 goto err

REM ���� � �������� � ������� �� ������
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