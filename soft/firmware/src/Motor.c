#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "Motor.h"

#define PIN_OFF(port,pin) (port) |= 1 << (pin);
#define PIN_ON(port,pin) (port) &= ~(1 << (pin));

#define MOTOR_DISABLE() PIN_OFF(PORTD, PIN_M_EN);
#define MOTOR_ENABLE() PIN_ON(PORTD, PIN_M_EN);

// quadrature encoder interrupt
volatile uint8_t hist_portb = 0xFF;

ISR(PCINT0_vect) {
	uint8_t changed;

	changed = PINB ^ hist_portb;
	hist_portb = PINB;

	if(changed & (1 << PB0)) { // pb0 changed
		// count down ticks
		if(motor.mode == POSITION) {
			if(motor.ticks > 0) {
				motor.ticks--;
			} else {
				// stop!
				motor_brake();
			}
		}

		// calculate speed
		motor.inverse_speed = TCNT1 & 0x7FFF;
		TCNT1 = 0;

		if(PINB & (1 << PB0)) { // pb0 rising edge
			if(PINB & (1 << PB1)) // pb1 high or low?
				motor.dir = LEFT;
			else
				motor.dir = RIGHT;
		}
	}
}

void motor_init() {
	motor.mode = VELOCITY;
	motor.target_speed = 255;

	// pin change interrupt
	// for quadrature encoder
	PCICR = 1 << PCIE0;
	PCMSK0 = 1 << PCINT0;

	// motor control pins
	DDRD |= 1 << PIN_M_EN;
	DDRD |= (1 << PIN_M_1A) | (1 << PIN_M_2A);
	MOTOR_DISABLE();

	// pwm using timer0
	// phase correct, OCR0A top, no prescale
	TCCR0A = (1 << COM0A0) | (1 << COM0A1) | (1 << WGM00);
	TCCR0B = (1 << CS00);

	OCR0A = 255; // off
}

void motor_set_pos(int8_t dir, unsigned int speed) {
	motor.ticks = speed;
	motor_set_vel(dir, motor.target_speed);
}

void motor_set_vel(int8_t dir, unsigned int speed) {
	MOTOR_ENABLE();

	if(dir == LEFT) {
		TCCR0A &= ~(1 << COM0B0);
		TCCR0A &= ~(1 << COM0B1);
		TCCR0A |= (1 << COM0A0);
		TCCR0A |= (1 << COM0A1);
		OCR0A = speed;
	} else {
		TCCR0A &= ~(1 << COM0A0);
		TCCR0A &= ~(1 << COM0A1);
		TCCR0A |= (1 << COM0B0);
		TCCR0A |= (1 << COM0B1);
		OCR0B = speed;
	}
}

void motor_set_accel(int8_t dir, unsigned int speed) {
	PIN_OFF(PORTD, PIN_M_1A);
	PIN_ON(PORTD, PIN_M_2A);
}

void motor_stop() {
	PIN_OFF(PORTD, PIN_M_1A);
	PIN_OFF(PORTD, PIN_M_2A);
}

void motor_brake() {
	motor.ticks = 0;

	MOTOR_DISABLE();
	PIN_OFF(PORTD, PIN_M_1A);
	PIN_OFF(PORTD, PIN_M_2A);
}
