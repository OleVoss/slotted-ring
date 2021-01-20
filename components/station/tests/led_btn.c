#include <avr/io.h>

int main (void) {
	DDRB |= (1 << DDB0);
	PORTB |= (1 << DDB0);
}
