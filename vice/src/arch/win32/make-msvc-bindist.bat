@echo off
set VICEDIR=WinVICE-2.0
if not exist ..\..\..\data\x64.exe goto missingmsvc
if not exist ..\..\..\data\x128.exe goto missingmsvc
if not exist ..\..\..\data\xcbm2.exe goto missingmsvc
if not exist ..\..\..\data\xpet.exe goto missingmsvc
if not exist ..\..\..\data\xplus4.exe goto missingmsvc
if not exist ..\..\..\data\xvic.exe goto missingmsvc
if not exist ..\..\..\data\c1541.exe goto missingmsvc
if not exist ..\..\..\data\cartconv.exe goto missingmsvc
if not exist ..\..\..\data\petcat.exe goto missingmsvc
echo generating MSVC WIN32 binary port distribution
if exist %VICEDIR% goto removedir
mkdir %VICEDIR%
copy ..\..\..\data\x64.exe %VICEDIR%
copy ..\..\..\data\x128.exe %VICEDIR%
copy ..\..\..\data\xvic.exe %VICEDIR%
copy ..\..\..\data\xpet.exe %VICEDIR%
copy ..\..\..\data\xplus4.exe %VICEDIR%
copy ..\..\..\data\xcbm2.exe %VICEDIR%
copy ..\..\..\data\c1541.exe %VICEDIR%
copy ..\..\..\data\petcat.exe %VICEDIR%
copy ..\..\..\data\cartconv.exe %VICEDIR%
mkdir %VICEDIR%\C128
copy ..\..\..\data\C128\basic* %VICEDIR%\C128
copy ..\..\..\data\C128\*.vpl %VICEDIR%\C128
copy ..\..\..\data\C128\charg* %VICEDIR%\C128
copy ..\..\..\data\C128\*.vrs %VICEDIR%\C128
copy ..\..\..\data\C128\kernal* %VICEDIR%\C128
copy ..\..\..\data\C128\win_*.v* %VICEDIR%\C128
mkdir %VICEDIR%\C64
copy ..\..\..\data\C64\basic %VICEDIR%\C64
copy ..\..\..\data\C64\*.vpl %VICEDIR%\C64
copy ..\..\..\data\C64\c64mem.sym %VICEDIR%\C64
copy ..\..\..\data\C64\chargen %VICEDIR%\C64
copy ..\..\..\data\C64\*.vrs %VICEDIR%\C64
copy ..\..\..\data\C64\kernal %VICEDIR%\C64
copy ..\..\..\data\C64\win_*.v* %VICEDIR%\C64
mkdir %VICEDIR%\CBM-II
copy ..\..\..\data\CBM-II\*.vpl %VICEDIR%\CBM-II
copy ..\..\..\data\CBM-II\basic.* %VICEDIR%\CBM-II
copy ..\..\..\data\CBM-II\chargen.* %VICEDIR%\CBM-II
copy ..\..\..\data\CBM-II\kernal* %VICEDIR%\CBM-II
copy ..\..\..\data\CBM-II\*.vrs %VICEDIR%\CBM-II
copy ..\..\..\data\CBM-II\win_*.v* %VICEDIR%\CBM-II
mkdir %VICEDIR%\DRIVES
copy ..\..\..\data\DRIVES\d* %VICEDIR%\DRIVES
mkdir %VICEDIR%\PET
copy ..\..\..\data\PET\*.vpl %VICEDIR%\PET
copy ..\..\..\data\PET\basic* %VICEDIR%\PET
copy ..\..\..\data\PET\chargen* %VICEDIR%\PET
copy ..\..\..\data\PET\edit* %VICEDIR%\PET
copy ..\..\..\data\PET\kernal* %VICEDIR%\PET
copy ..\..\..\data\PET\*.vrs %VICEDIR%\PET
copy ..\..\..\data\PET\win_*.v* %VICEDIR%\PET
mkdir %VICEDIR%\PLUS4
copy ..\..\..\data\PLUS4\3plus1* %VICEDIR%\PLUS4
copy ..\..\..\data\PLUS4\basic %VICEDIR%\PLUS4
copy ..\..\..\data\PLUS4\*.vpl %VICEDIR%\PLUS4
copy ..\..\..\data\PLUS4\*.vrs %VICEDIR%\PLUS4
copy ..\..\..\data\PLUS4\kernal %VICEDIR%\PLUS4
copy ..\..\..\data\PLUS4\win_*.v* %VICEDIR%\PLUS4
mkdir %VICEDIR%\PRINTER
copy ..\..\..\data\PRINTER\cbm1526 %VICEDIR%\PRINTER
copy ..\..\..\data\PRINTER\mps* %VICEDIR%\PRINTER
copy ..\..\..\data\PRINTER\*.vpl %VICEDIR%\PRINTER
copy ..\..\..\data\PRINTER\nl10-cbm %VICEDIR%\PRINTER
mkdir %VICEDIR%\VIC20
copy ..\..\..\data\VIC20\basic %VICEDIR%\VIC20
copy ..\..\..\data\VIC20\chargen %VICEDIR%\VIC20
copy ..\..\..\data\VIC20\*.vpl %VICEDIR%\VIC20
copy ..\..\..\data\VIC20\*.vrs %VICEDIR%\VIC20
copy ..\..\..\data\VIC20\kernal %VICEDIR%\VIC20
copy ..\..\..\data\VIC20\win_*.v* %VICEDIR%\VIC20
mkdir %VICEDIR%\fonts
copy ..\..\..\data\fonts\*.fon %VICEDIR%\fonts
mkdir %VICEDIR%\html
copy ..\..\..\doc\html\*.html %VICEDIR%\html
mkdir %VICEDIR%\html\images
copy ..\..\..\doc\html\images\* %VICEDIR%\html\images
mkdir %VICEDIR%\html\plain
copy ..\..\..\doc\html\plain\* %VICEDIR%\html\plain
copy ..\..\..\FEEDBACK %VICEDIR%
copy ..\..\..\README %VICEDIR%
copy ..\..\..\doc\cartconv.txt %VICEDIR%
echo WIN32 port binary distribution directory generated as %VICEDIR%
goto end
:missingmsvc
echo executables are missing, please build the project first.
goto end
:removedir
echo %VICEDIR% already exists, please remove %VICEDIR% and run this batch file again.
:end
pause
