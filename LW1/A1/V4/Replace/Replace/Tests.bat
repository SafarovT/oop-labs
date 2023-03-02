set PROGRAM="%~1"

REM При запуске без параметров ожидается код ошибки
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

REM Стандартный тест
%PROGRAM% fox.txt "%TEMP%\fox.txt" dog cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" fox-replace-dog-with-cat.txt
if ERRORLEVEL 1 goto err

REM Тест где ничего не должно заменится
%PROGRAM% fox.txt "%TEMP%\fox.txt" bird cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" fox.txt
if ERRORLEVEL 1 goto err

REM Замена пустой строки на что-то, должно ничего не изменится
%PROGRAM% fox.txt "%TEMP%\fox.txt" "" cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" fox.txt
if ERRORLEVEL 1 goto err

REM Проверка на бесконечные циклы, а именно на замену, в замененной строке.
%PROGRAM% numbers.txt "%TEMP%\numbers.txt" 123 123123
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\numbers.txt" numbers_123_with_123123.txt
if ERRORLEVEL 1 goto err

REM Замена в пустом файле, файл должен остаться пустым
%PROGRAM% empty.txt "%TEMP%\empty.txt" 1 2
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\empty.txt" empty.txt
if ERRORLEVEL 1 goto err

del "%TEMP%\fox.txt"
del "%TEMP%\numbers.txt"
del "%TEMP%\empty.txt"
echo OK
exit 0

:err
del "%TEMP%\fox.txt"
del "%TEMP%\numbers.txt"
del "%TEMP%\empty.txt"
echo Program testing failed
exit 1