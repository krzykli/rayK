@echo off

IF NOT "%VisualStudioVersion%"=="14.0" ^
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64

set CompilerFlags= /GS /GL /analyze- /W4 /Gy /Zc:wchar_t /Zi /Gm- /O2 /Zc:inline /fp:precise /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /errorReport:prompt /WX- /Zc:forScope /Gd /Oy- /Oi /MD /EHsc

mkdir build
pushd build
cl %CompilerFlags% ..\src\main.cpp /I..\include /link /out:rayK.exe
popd

