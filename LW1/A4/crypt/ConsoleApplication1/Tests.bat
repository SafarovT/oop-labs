set PROGRAM="%~1"

del "%TEMP%\!Answer.txt"
%PROGRAM% crypt TextToCrypt.txt "%TEMP%\!Answer.txt" 120
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1