#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define forever for(;;)

// pins

#define PIN_1A		PC0
#define PIN_2A		PC2
#define PIN_EN		PC3

#define PIN_LED1	PD6
#define PIN_LED2	PD7

#define PIN_A		PB0
#define PIN_B		PB1

// constants

int main(void) {
	// setup pins
	DDRC |= (1 << PIN_EN) | (1 << PIN_1A) | (1 << PIN_2A);
	DDRD |= (1 << PIN_LED1) | (1 << PIN_LED2);

	forever {
		PORTD &= ~(1 << PIN_LED1);
		PORTD |= 1 << PIN_LED2;
		_delay_ms(500);
		PORTD &= ~(1 << PIN_LED2);
		PORTD |= 1 << PIN_LED1;
		_delay_ms(500);
	}

	return 0;
}
