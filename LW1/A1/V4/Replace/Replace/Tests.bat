set PROGRAM="%~1"

rem ��� ������� ��� ���������� ��������� ��������� ��� ��������
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% fox.txt "%TEMP%\fox.txt" bird cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" fox.txt
if ERRORLEVEL 1 goto err

%PROGRAM% fox.txt "%TEMP%\fox.txt" dog cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" fox-replace-dog-with-cat.txt
if ERRORLEVEL 1 goto err

%PROGRAM% multi-line.txt "%TEMP%\multi-line.txt" 123 789
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\multi-line.txt" multi-line-replace-123-with-789.txt
if ERRORLEVEL 1 goto err

%PROGRAM% empty.txt "%TEMP%\empty.txt" 1 2
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\empty.txt" empty.txt
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1