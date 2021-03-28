#include "i2cmaster.h"
#define __HAS_DELAY_CIRCLES 0
#define __AVR_ATmega328P__
#include <avr/io.h>
#include <util/delay.h>

void send_start()
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
}

void send_byte(int data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
}

void send_multiple_bytes(int data[])
{
    for (int i = 0; i < sizeof(data); i++)
    {
        send_byte(data[i]);
    }
}

void send_stop()
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void start_write(int adress)
{
    int SLA_W = (adress << 1) | 0x00;
    TWDR = SLA_W;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
}

int start_write_sr(int adress)
{
    int SLA_W = (adress << 1) | 0x00;
    TWDR = SLA_W;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;

    if ((TWSR & 0xf8) == 0x18)
    {
        return 1;
    }
    else if ((TWSR & 0xf8) == 0x20)
    {
        return 0;
    }
    return 2;
}

void start_read(int adress)
{
    int SLA_R = (adress << 1) | 0x01;
    TWDR = SLA_R;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
}

int read_ack()
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)))
        ;
    return TWDR;
}

int read_nack()
{
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
    return TWDR;
}