#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

#include "Motor.h"
#include "Led.h"

#define PIN_OFF(port,pin) (port) |= 1 << (pin);
#define PIN_ON(port,pin) (port) &= ~(1 << (pin));

#define MOTOR_DISABLE() PIN_OFF(PORTD, PIN_M_EN);
#define MOTOR_ENABLE() PIN_ON(PORTD, PIN_M_EN);

long pos;

ISR(TIMER1_COMPA_vect) {
	cli();

	PINC |= 1 << LED_GREEN;

	if(pos < target_pos) {
		motor_forward(128);
	} else {
		motor_backward(128);
	}
	
	sei();
}

void motor_forward(int speed) {
	MOTOR_ENABLE();

	TCCR0A &= ~(1 << COM0B0);
	TCCR0A &= ~(1 << COM0B1);
	TCCR0A |= (1 << COM0A0);
	TCCR0A |= (1 << COM0A1);

	OCR0A = speed;
}

void motor_backward(int speed) {
	MOTOR_ENABLE();
	
	TCCR0A &= ~(1 << COM0A0);
	TCCR0A &= ~(1 << COM0A1);
	TCCR0A |= (1 << COM0B0);
	TCCR0A |= (1 << COM0B1);

	OCR0B = speed;
}

uint8_t hist_portb;
ISR(PCINT0_vect) {
	cli();

	uint8_t changed;

	changed = PINB ^ hist_portb;
	hist_portb = PINB;

	if(changed & (1 << PB0)) { // pb0 changed
		if(PINB & (1 << PB0)) { // pb0 rising edge
			if(PINB & (1 << PB1)) { // pb1 high or low?
				pos--;
			} else {
				pos++;
			}
		}
	}

	sei();
}

void motor_init() {
	// pin change interrupt
	// for quadrature encoder
	PCICR = 1 << PCIE0;
	PCMSK0 = 1 << PCINT0;

	// heartbeat timer
	TCCR1B |= 2;
	TIMSK1 |= 1 << OCIE1A;
	OCR1A = 0xFFF;

	// motor control pins
	DDRD |= 1 << PIN_M_EN;
	DDRD |= (1 << PIN_M_1A) | (1 << PIN_M_2A);
	MOTOR_DISABLE();

	// pwm using timer0
	// phase correct, OCR0A top, no prescale
	TCCR0A = (1 << COM0A0) | (1 << COM0A1) | (1 << WGM00);
	TCCR0B = (1 << CS00);

	OCR0A = 255; // off
	OCR0B = 255; // off
}

void motor_stop() {
	PIN_OFF(PORTD, PIN_M_1A);
	PIN_OFF(PORTD, PIN_M_2A);
}

void motor_brake() {
	MOTOR_DISABLE();

	PIN_OFF(PORTD, PIN_M_1A);
	PIN_OFF(PORTD, PIN_M_2A);
}
