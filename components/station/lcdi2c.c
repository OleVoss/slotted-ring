#define __HAS_DELAY_CIRCLES 0
#define __AVR_ATmega328P__

#define SLA 0x27

#include "/home/voss/repos/slotted-ring/components/avr_lib/src/lcdpcf8574/lcdpcf8574.h"
// #include "/home/voss/repos/slotted-ring/components/avr_lib/src/i2chw/i2cmaster.h"
// #include "i2cmaster.h"
// #include <avr/io.h>
// #include <util/delay.h>
// #include <stdbool.h>

#define PCF_RS 0x01
#define PCF_RW 0x02
#define PCF_EN 0x04
#define PCF_BACKLIGHT 0x08

int main(void)
{
    // writeToWire(0x00, 0, false);
    // _delay_us(50000);

    // sendNibble(0x03, false);
    // _delay_us(4500);
    // sendNibble(0x03, false);
    // _delay_us(200);
    // sendNibble(0x03, false);
    // _delay_us(200);
    // sendNibble(0x02, false);

    // int functionFlags = 0;
    // functionFlags |= 0x08;
    // send(0x20 | functionFlags);

    // display();
    // clear();
    // leftToRight();

    // write("test");

    DDRB |= (1 << DDB0);
    lcd_init(LCD_DISP_ON_BLINK);
    lcd_home();
    lcd_puts("test string");
    PORTB |= (1 << PB0);
}

// void clear()
// {
//     send(0x01);
//     _delay_us(1600);
// }

// void display()
// {
//     int contrl = 0x04;
//     contrl |= 0x04;
//     send(0x08 | contrl);
// }

// void leftToRight()
// {
//     int mode = 0x02;
//     mode |= 0x02;
//     send(0x04 | mode);
// }

// void noBlink()
// {
//     send(0x08 | (0x04 & ~0x01));
// }

// void write(uint8_t ch)
// {
//     send(ch, true);
// }

// void send(int value, bool isData)
// {
//     sendNibble((value >> 4 & 0x0F), isData);
//     sendNibble((value & 0x0F), isData);
// }

// void sendNibble(int halfByte, bool isData)
// {
//     writeToWire(halfByte, isData, true);
//     _delay_us(1);
//     writeToWire(halfByte, isData, false);
//     _delay_us(37);
// }

// void writeToWire(int halfByte, bool isData, bool enable)
// {
//     int i2cData = halfByte << 4;
//     if (isData)
//     {
//         i2cData |= PCF_RS;
//     }
//     if (enable)
//     {
//         i2cData |= PCF_EN;
//     }
//     // if (_backlight > 0)
//     // {
//     i2cData |= PCF_BACKLIGHT;
//     // }

//     send_start();
//     start_write(SLA);
//     send_byte(i2cData);
//     send_stop;
// }