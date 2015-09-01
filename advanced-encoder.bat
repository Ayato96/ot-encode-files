set DIERCOTRY_OTCLIENT=..\otClient\client
set RELEASE=updater.zip

set OT_DATA=data
set OTPKG_DATA=data
set OTPKG_MODULES=modules
set OTPKG_MODS=pokemon
set SPRITE_DAT=data\things\854



set DATA=data
set NEW_DATA="new data"

if exist %RELEASE% del %RELEASE%
if exist %DATA% rd /q /s %DATA%
if exist %NEW_DATA% rd /q /s %NEW_DATA%
if exist release rd /q /s release
mkdir %DATA%
mkdir "new data"
mkdir release
mkdir release\%OT_DATA%
mkdir release\%OT_DATA%\%SPRITE_DAT%

xcopy /E %DIERCOTRY_OTCLIENT% %DATA%
xcopy /E %DIERCOTRY_OTCLIENT% %NEW_DATA%

szyfruj.exe

move %NEW_DATA%\%OT_DATA%\%SPRITE_DAT%\Tibia.spr release\%OT_DATA%\%SPRITE_DAT%\Tibia.spr
move %NEW_DATA%\%OT_DATA%\%SPRITE_DAT%\Tibia.dat release\%OT_DATA%\%SPRITE_DAT%\Tibia.dat
copy %NEW_DATA%\%OT_DATA%\init.lua release\%OT_DATA%\init.lua
copy %NEW_DATA%\%OT_DATA%\version.lua release\%OT_DATA%\version.lua

winrar a -ep1 -r -afzip -ibck release\%OT_DATA%\%OTPKG_DATA%.otpkg %NEW_DATA%\%OT_DATA%\%OTPKG_DATA%\*
winrar a -ep1 -r -afzip -ibck release\%OT_DATA%\%OTPKG_MODULES%.otpkg %NEW_DATA%\%OT_DATA%\%OTPKG_MODULES%\*
winrar a -ep1 -r -afzip -ibck release\%OT_DATA%\%OTPKG_MODS%.otpkg %NEW_DATA%\%OT_DATA%\%OTPKG_MODS%\*

xcopy %NEW_DATA%\*.exe release\
xcopy %NEW_DATA%\*.dll release\

winrar a -ep1 -r -afzip -ibck %RELEASE% release\*

if exist %DATA% rd /q /s %DATA%
if exist %NEW_DATA% rd /q /s %NEW_DATA%

start %comspec% /c "mode 40,10&title Advanced-Encoder&color 1e&echo.&echo. Your client is ready.&echo.&echo. Press a key!&pause>NUL"