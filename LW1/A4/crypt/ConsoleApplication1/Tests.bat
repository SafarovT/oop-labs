set PROGRAM="%~1"
rem set deleleFilesMacro = del "%TEMP%\CryptedFile.txt" del "%TEMP%\DecryptedFile.txt"

REM ��� ������� ��� ������������ ���������� ���������� ��������� ��������� ��� ��������
%PROGRAM% crypt TextToCrypt.txt "%TEMP%\CryptedFile.txt"
if NOT ERRORLEVEL 1 goto err

REM �������� ���������� � ������������ ����� �� ���������� ���������
%PROGRAM% crypt TextToCrypt.txt "%TEMP%\CryptedFile.txt" 120
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt "%TEMP%\CryptedFile.txt" "%TEMP%\DecryptedFile.txt" 120
if ERRORLEVEL 1 goto err
fc.exe TextToCrypt.txt "%TEMP%\DecryptedFile.txt"
if ERRORLEVEL 1 goto err

del "%TEMP%\CryptedFile.txt"
del "%TEMP%\DecryptedFile.txt"
echo OK
exit 0

:err
del "%TEMP%\CryptedFile.txt"
del "%TEMP%\DecryptedFile.txt"
echo Program testing failed
exit 1