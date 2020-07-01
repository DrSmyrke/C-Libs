#!/bin/bash

rm {uart.h, myDevicesIDs.h, Atmega8T0.h, main.h}
curl https://raw.githubusercontent.com/DrSmyrke/AVR-Libs/master/uart.h > uart.h
curl https://raw.githubusercontent.com/DrSmyrke/AVR-Libs/master/myDevicesIDs.h > myDevicesIDs.h
curl https://raw.githubusercontent.com/DrSmyrke/AVR-Libs/master/Atmega8T0.h > Atmega8T0.h
curl https://raw.githubusercontent.com/DrSmyrke/AVR-Libs/master/main.h > main.h

avr-gcc -mmcu=atmega8 -Os -o main.o main.c && avr-objcopy -O ihex main.o main.hex && rm main.o
