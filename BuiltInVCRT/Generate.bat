call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
dumpbin /exports c:\windows\system32\msvcrt.dll > msvcrt.def
REM -- strip all fields except symbol name (4th col.), and add 'EXPORTS' at the start
pause
lib /def:msvcrt.def /out:msvcrt_x86.lib /machine:x86
lib /def:msvcrt.def /out:msvcrt_x64.lib /machine:x64