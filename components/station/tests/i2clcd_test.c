#define __AVR_ATmega328P__
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "/home/voss/repos/slotted-ring/components/avr_lib/src/lcdpcf8574/lcdpcf8574.h"
#include "/home/voss/repos/slotted-ring/components/avr_lib/src/i2chw/i2cmaster.h"

#define SLA 0x27
int main(void)
{
	DDRB |= (1 << DDB0);
	_delay_ms(2000);

	send_start();
	int result = start_write_sr(SLA);
	send_stop();

	if (result == 1)
	{
		PORTB |= (1 << PB0);
	}
}
