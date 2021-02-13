#define __HAS_DELAY_CIRCLES 0
#define F_CPU 1280000UL
#define __AVR_ATmega328P__
#include "i2cmaster.h"
#include <avr/io.h>
#include <util/delay.h>

#define SLA 0x05

int main(void) {

	DDRB |= (1 << DDB0);
	_delay_ms(1000);
    send_start();

    start_write(SLA);

    int data[6] = {1, 1, 1, 1, 1, 1};
    int data_off[6] = {1, 1, 0, 0, 0, 0};

    send_multiple_bytes(data_off);

    send_stop();

	PORTB |= (1 << PB0);
}