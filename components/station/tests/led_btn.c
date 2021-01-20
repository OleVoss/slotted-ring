#include <avr/io.h>

int main (void) {
	DDRB |= (1 << DDB0);
	PORTB |= (1 << PB1); // pull-up resistor
	
	while (1) {
		if (!(PINB & 0b00000010)) {
			PORTB |= (1 << PB0);
		} else {
			PORTB &= ~(1 << PB0);
		}
	}
}
