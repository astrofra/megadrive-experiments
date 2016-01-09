del *.o /q
rd out /s /q

set GDK=../../../../../SGDK
set GDK_WIN=..\..\..\..\..\SGDK
..\..\..\..\..\SGDK\bin\make.exe -f ..\..\..\..\..\SGDK\makefile.gen

pause
if exist c:\gensKMod\rom.bin del c:\gensKMod\rom.bin
if exist out\rom.bin copy out\rom.bin c:\gensKMod\
if exist out\rom.bin c:
if exist out\rom.bin cd c:\gensKMod\
if exist rom.bin gens.exe rom.bin

pause
