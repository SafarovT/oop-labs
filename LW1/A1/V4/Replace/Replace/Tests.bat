set PROGRAM="%~1"

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

%PROGRAM% fox.txt "%TEMP%\fox.txt" "" cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" fox.txt
if ERRORLEVEL 1 goto err

%PROGRAM% numbers.txt "%TEMP%\numbers.txt" 123 123123
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\numbers.txt" numbers_123_with_123123.txt
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