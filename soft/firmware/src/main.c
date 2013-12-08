#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define forever for(;;)

// pins

#define PIN_M_1A		PC0
#define PIN_M_2A		PC1
#define PIN_M_EN		PC2

#define PIN_LED0		PD6
#define PIN_LED1		PD7

#define PIN_A			PB0
#define PIN_B			PB1

// constants

volatile uint8_t hist_portb = 0xFF;     // default is high because the pull-up

ISR(PCINT0_vect) {
	uint8_t changed;

	changed = PINB ^ hist_portb;
	hist_portb = PINB;

	if(changed & (1 << PB0)) {
		if(PINB & (1 << PB0)) { // pb0 rising edge
			if(PINB & (1 << PB1)) {
				// forward
				PORTD &= ~(1 << PIN_LED1);
				PORTD |= 1 << PIN_LED0;
			} else {
				// backward
				PORTD &= ~(1 << PIN_LED0);
				PORTD |= 1 << PIN_LED1;
			}
		}
	}
}

int main(void) {
	// setup pin change interrupts
	PCICR = 1 << PCIE0;
	PCMSK0 = 1 << PCINT0;

	// setup pins
	DDRC |= (1 << PIN_M_EN) | (1 << PIN_M_1A) | (1 << PIN_M_2A);
	DDRD |= (1 << PIN_LED0) | (1 << PIN_LED1);

	// motor enabled
	DDRC |= (1 << 2);
	PORTC |= (1 << 2);

	//PORTD |= (1 << PIN_LED0) | (1 << PIN_LED1);

	sei();

	forever {
		// forward
		PORTC &= ~(1 << PIN_M_2A);
		PORTC |= 1 << PIN_M_1A;
		_delay_ms(1000);
		
		// backward
		PORTC &= ~(1 << PIN_M_1A);
		PORTC |= 1 << PIN_M_2A;
		_delay_ms(1000);

		// stop
		PORTC &= ~(1 << PIN_M_1A);
		PORTC &= ~(1 << PIN_M_2A);
		_delay_ms(1000);
	}

	return 0;
}
