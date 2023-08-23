Firmata Server for Arduino 

To upload HEX file:

From the same directory CRE_Firmata.hex is located type:

"C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avrdude" -C"C:\Program Files (x86)\Arduino\hardware\tools\avr\etc\avrdude.conf" -v -pm328p -carduino -PCOM10 -b57600 -Uflash:w:cre_firmata.hex:i

Alternatively use the crpgm command:

crpgm COM4

Change COM port to suite 

 
