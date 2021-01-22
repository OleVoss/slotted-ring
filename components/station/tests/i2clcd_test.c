#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "/home/voss/repos/slotted-ring/components/libs/src/lcdpcf8574/lcdpcf8574.h"
#include "/home/voss/repos/slotted-ring/components/libs/src/i2chw/i2cmaster.h"

int main(void) {
	i2c_init();

	lcd_init(LCD_DISP_ON);
	
	lcd_puts("Station Nr: 1");
}

