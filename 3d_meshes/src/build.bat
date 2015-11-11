del out\rom.bin.bak
copy out\rom.bin out\rom.bin.bak
del out\rom.bin
%GDK_WIN%\bin\make -f %GDK_WIN%\makefile.gen
out\rom.bin
pause