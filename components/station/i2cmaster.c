#include "i2cmaster.h"
#define __HAS_DELAY_CIRCLES 0
#define F_CPU 1280000UL
#define __AVR_ATmega328P__
#include <avr/io.h>
#include <util/delay.h>

void send_start() {
    TWCR = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
}

void send_byte(int data) {
    TWDR = data;
    TWCR = (1 << TWINT)|(1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
}

void send_multiple_bytes(int data[]) {
    for (int i=0; i<sizeof(data); i++) {
        send_byte(data[i]);
    }
}

void send_stop() {
	TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTO);
}

void start_write(int adress) {
    int SLA_W = (adress << 1)|0x00;
    TWDR = SLA_W;
    TWCR = (1 << TWINT)|(1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
}

void start_read(int adress) {
    int SLA_W = (adress << 1)|0x01;
    TWDR = SLA_W;
    TWCR = (1 << TWINT)|(1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
}