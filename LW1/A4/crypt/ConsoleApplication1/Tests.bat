set PROGRAM="%~1"

REM При запуске без достаточного количества параметров, ожидается ненулевой код возврата
%PROGRAM% crypt TextToCrypt.txt "%TEMP%\CryptedFile.txt"
if NOT ERRORLEVEL 1 goto err

REM Запуск с ключем вне диапазона, ожидается ненулевой код возврата
%PROGRAM% crypt TextToCrypt.txt "%TEMP%\CryptedFile.txt" 128
if NOT ERRORLEVEL 1 goto err

REM Запуск с ключем вне диапазона, ожидается ненулевой код возврата
%PROGRAM% crypt TextToCrypt.txt "%TEMP%\CryptedFile.txt" -128
if NOT ERRORLEVEL 1 goto err

REM Запуск с ключем заданным не в виде числа, ожидается ненулевой код возврата
%PROGRAM% crypt TextToCrypt.txt "%TEMP%\CryptedFile.txt" abcdefg
if NOT ERRORLEVEL 1 goto err

REM Запуск с неизвестным режимом работы, ожидается ненулевой код возврата
%PROGRAM% uncrypt TextToCrypt.txt "%TEMP%\CryptedFile.txt" abcdefg
if NOT ERRORLEVEL 1 goto err

REM Проверка шифрования и дешифрования файла со случайными символами
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