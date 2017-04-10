@echo off

IF NOT "%VisualStudioVersion%"=="14.0" ^
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64

set CompilerFlags= /FC /Zi /EHsc

mkdir build
pushd build
cl %CompilerFlags% ..\src\win32_rayK.cpp gdi32.lib user32.lib /I..\include /link /out:rayK.exe
popd

