@echo off
set command="C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avrdude" -C"C:\Program Files (x86)\Arduino\hardware\tools\avr\etc\avrdude.conf"

setlocal enableextensions enabledelayedexpansion
call :getargc argc %*
if not %argc%==1 (
    echo usage: crpgm [valid arduino nano COM port] i.e. crpgm COM10
)

if %argc%==1 (
    echo programming arduino
    %command% -v -pm328p -carduino -P%1 -b57600 -Uflash:w:cre_firmata.hex:i
)

endlocal
goto :eof

:getargc
    set getargc_v0=%1
    set /a "%getargc_v0% = 0"
:getargc_l0
    if not x%2x==xx (
        shift
        set /a "%getargc_v0% = %getargc_v0% + 1"
        goto :getargc_l0
    )
    set getargc_v0=
    goto :eof