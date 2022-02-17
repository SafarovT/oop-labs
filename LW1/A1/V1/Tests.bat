set PROGRAM="%~1"

rem проверяем копирование пустого файла (копируем его во временную папку текущего пользователя)
%PROGRAM% Empty.txt %TEMP%\Empty.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\Empty.txt Empty.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при невозможности записи в выходной файл (в исполняемый файл программы)
%PROGRAM% multiline.txt %PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1