#!/bin/bash

wget https://raw.githubusercontent.com/DrSmyrke/AVR-Libs/master/uart.h
wget https://raw.githubusercontent.com/DrSmyrke/AVR-Libs/master/myDevicesTypes.h
wget https://raw.githubusercontent.com/DrSmyrke/AVR-Libs/master/myProto.h
wget https://raw.githubusercontent.com/DrSmyrke/AVR-Libs/master/main.h

BUILD_NUM=$(git rev-list HEAD --count)
echo "#define BUILD_NUM $BUILD_NUM"> gitbuild.h

avr-gcc -mmcu=atmega8 -Os -o main.o main.c && avr-objcopy -O ihex main.o main.hex && rm main.o
avr-gcc -mmcu=atmega8 -Os -o main_TX.o main_TX.c && avr-objcopy -O ihex main_TX.o main_TX.hex && rm main_TX.o

rm {myProto.h,uart.h,myDevicesTypes.h,main.h,gitbuild.h}
