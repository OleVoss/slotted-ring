#ifndef I2CMASTER_H
#define I2CMASTER_H

extern void enable_i2c();
extern void start_write(int adress);
extern void start_read(int adress); // is byte count needed?
extern void send_start();
extern void send_byte(int);
extern void send_multiple_bytes(int[]);
extern void send_stop();

#endif