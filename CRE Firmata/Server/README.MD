Firmata Server for Arduino 

To upload HEX file, 

avrdude -C../etc/avrdude.conf -v -pm328p -carduino -PCOM4 -b57600 -Uflash:w:CRE_Firmata.hex":i

Change COM port to suit
