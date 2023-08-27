Set CurrentPath=%~dp0
Set QtDir="S:\Qt\Qt5.9.9_src\5.9.9\msvc2015\bin"
cd /d %QtDir%

:: setup vcpath
set VCPath=S:\Program Files (x86)\Microsoft Visual Studio 14.0\VC
call "%VCPath%\vcvarsall.bat"

:: setup qt env
call qtenv2.bat

:: deploy
windeployqt.exe %CurrentPath%debug\EasyCmd.exe

pause > nul