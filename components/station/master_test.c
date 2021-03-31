#define __HAS_DELAY_CIRCLES 0
#define F_CPU 1280000UL
#define __AVR_ATmega328P__
#include "i2cmaster.h"
#include <avr/io.h>
#include <util/delay.h>

#define SLA 0x05
#define LCD_A 0x27

int main(void)
{

    DDRB |= (1 << DDB0);
    _delay_ms(1000);

    send_start();
    int result = start_write_sr(SLA);
    send_byte(200);
    send_stop();

    // send_start();
    // start_read(SLA);
    // int data[3];
    // // int data_off[6] = {0, 0, 1, 1, 0, 0};
    // data[0] = read_ack();
    // data[1] = read_ack();
    // data[2] = read_nack();
    // send_stop();

    // send_start();
    // start_write(SLA);
    // send_byte(data[0]);
    // send_byte(data[1]);
    // send_byte(data[2]);
    // send_stop();

    if (result == 0)
    {

        PORTB |= (1 << PB0);
    }
}