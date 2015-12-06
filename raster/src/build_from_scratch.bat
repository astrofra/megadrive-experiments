del out\* /s /f /q
del out\*.* /s /f /q
%GDK_WIN%\bin\make -f %GDK_WIN%\makefile.gen
out\rom.bin
pause