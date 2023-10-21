Firmata Server for Arduino 

To upload the HEX file, assuming the Arduino Nano is hosted at COM10, then from the same directory where CRE_Firmata.hex is located type:

"C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avrdude" -C"C:\Program Files (x86)\Arduino\hardware\tools\avr\etc\avrdude.conf" -v -pm328p -carduino -PCOM10 -b57600 -Uflash:w:cre_firmata.hex:i

Alternatively use the crpgm command:

crpgm 10

To program Change COM port to suite.

 
