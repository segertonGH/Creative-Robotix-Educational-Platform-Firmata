@echo off

set command="C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avrdude" -C"C:\Program Files (x86)\Arduino\hardware\tools\avr\etc\avrdude.conf"

REM setlocal enableextensions enabledelayedexpansion
call :getargc argc %*

if %argc%==1 (
    echo programming arduino
    %command% -v -pm328p -carduino -PCOM%1 -b57600 -Uflash:w:cre_firmata.hex:i
	goto :eof
)

if %argc%==2 (
    echo programming %2 arduinos starting at COM%1
	REM TODO: BUG FIX? setlocal / endlocal has no effect, endcom only picked up after second run ?! 28092023 
	set /a endcom=%1+%2-1
    for /L %%n in (%1,1,%endcom%) do %command% -v -pm328p -carduino -PCOM%%n -b57600 -Uflash:w:cre_firmata.hex:i
	goto :eof
)

echo usage: crpgm [valid arduino nano COM port number ] i.e. crpgm 10 | [number of devices] i.e. crpgm 20 10 will program 10 devices starting from COM20

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