#!/bin/bash

# setup
set -e
lib_path=/home/ole/Repos/slotted-ring/components/avr_lib/src

# get filename
file=$(basename $1 .c)

# compile .c to .elf
avr-gcc -mmcu=atmega328p -Wall -Os -o $file.elf $file.c $lib_path/lcdpcf8574/lcdpcf8574.c $lib_path/i2chw/twimaster.c $lib_path/pcf8574/pcf8574.c

# copy elf sections
avr-objcopy -j .text -j .data -O ihex $file.elf $file.hex

# flash to atmega328p
avrdude -p m328p -c usbasp -e -U flash:w:$file.hex

# clean temorary files
rm $file.elf $file.hex
