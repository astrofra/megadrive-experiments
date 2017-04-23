del dump_asm.txt
del out\* /s /f /q
del out\*.* /s /f /q
%GDK_WIN%\bin\make -f %GDK_WIN%\makefile_asm.gen > asm_src.txt
out\rom.bin
pause