#define  __HAS_DELAY_CYCLES 0
#define F_CPU 1280000UL
#include <avr/io.h>
#include <util/delay.h>
#define SLOT 0x05

int main(void) {
	DDRB |= (1 << DDB0);
	_delay_ms(5000);
	TWCR = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);
	while(!(TWCR & (1 << TWINT)));

	int SLA_W = (0x05 << 1)|0x00;
	TWDR = SLA_W;
	TWCR = (1 << TWINT)|(1 << TWEN);
	while(!(TWCR & (1 << TWINT)));

	TWDR = 0b00000001;
	TWCR = (1 << TWINT)|(1 << TWEN);
	while(!(TWCR & (1 << TWINT)));

	TWDR = 0b00000001;
	TWCR = (1 << TWINT)|(1 << TWEN);
	while(!(TWCR & (1 << TWINT)));

	TWDR = 0b00000001;
	TWCR = (1 << TWINT)|(1 << TWEN);
	while(!(TWCR & (1 << TWINT)));

	TWDR = 0b00000001;
	TWCR = (1 << TWINT)|(1 << TWEN);
	while(!(TWCR & (1 << TWINT)));

	TWDR = 0b00000001;
	TWCR = (1 << TWINT)|(1 << TWEN);
	while(!(TWCR & (1 << TWINT)));

	TWDR = 0b00000011;
	TWCR = (1 << TWINT)|(1 << TWEN);
	while(!(TWCR & (1 << TWINT)));

	TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTO);
	PORTB |= (1 << PB0);
}

