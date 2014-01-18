#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

#include "Motor.h"
#include "Led.h"

#define CLK_NONE	1
#define CLK_8		2
#define CLK_64		3
#define CLK_256		4
#define CLK_1024	5

#define PIN_OFF(port,pin) (port) |= 1 << (pin);
#define PIN_ON(port,pin) (port) &= ~(1 << (pin));

#define MOTOR_DISABLE() PIN_OFF(PORTD, PIN_M_EN);
#define MOTOR_ENABLE() PIN_ON(PORTD, PIN_M_EN);

uint16_t dt_i = 0;
uint32_t pos_i = 0;

// quadrature encoder interrupt
volatile uint8_t hist_portb = 0xFF;

volatile long overflows = 0;
ISR(TIMER1_COMPA_vect) {
	PINC |= 1 << LED_GREEN;

	/*switch(motor.mode) {
		case POSITION:
			motor.target_vel = pid_calc(&motor.pid, motor.pos, motor.target_pos);
			break;
		case VELOCITY:
			break;
	}*/

	//float correction = pid_calc(&motor.pid, motor.vel, motor.target_vel);
	/*float correction = fabs(motor.target_vel - motor.vel)/10.0;

	int16_t speed = 0xFFFF;
	if(OCR0A + correction < 0xFFFF)
		speed = OCR0A + correction;
	*/

	if(motor.target_vel < 0) {
		TCCR0A &= ~(1 << COM0B0);
		TCCR0A &= ~(1 << COM0B1);
		TCCR0A |= (1 << COM0A0);
		TCCR0A |= (1 << COM0A1);

		if(motor.target_vel - motor.vel < 0) {
			if(OCR0A < 255) OCR0A++;
		} else {
			if(OCR0A > 0) OCR0A--;
		}
	} else {
		TCCR0A &= ~(1 << COM0A0);
		TCCR0A &= ~(1 << COM0A1);
		TCCR0A |= (1 << COM0B0);
		TCCR0A |= (1 << COM0B1);

		if(motor.target_vel - motor.vel < 0) {
			if(OCR0B < 255) OCR0B++;
		} else {
			if(OCR0B > 0) OCR0B--;
		}
	}
	
	motor.vel = motor.pos - pos_i;
	pos_i = motor.pos;

	overflows++;
}

ISR(PCINT0_vect) {
	uint8_t changed;

	changed = PINB ^ hist_portb;
	hist_portb = PINB;

	if(changed & (1 << PB0)) { // pb0 changed
		// dx 
		if(PINB & (1 << PB0)) { // pb0 rising edge
			if(PINB & (1 << PB1)) { // pb1 high or low?
				motor.pos--;
			} else {
				motor.pos++;
			}
		}
		
		/*
		// dt 
		uint16_t dt_f = (TCNT1 & 0x7FFF);
		double dt = dt_f - dt_i;
		if(dt < 0) {
			// we did not go back in time
			dt += overflows * 0x7FFF;
			overflows = 0;
		}
		dt_i = dt_f;

		// velocity
		if(dt != 0) motor.vel = 0x7FFF * (motor.pos - pos_i) / dt;
		pos_i = motor.pos;
		*/
	}
}

float pid_calc(PidData* prefs, float current, float target) {
	float error = target - current;

	if(fabs(error) > prefs->epsilon)
		prefs->integral = prefs->integral + error*prefs->dt;
	float derivative = (error - prefs->pre_error)/prefs->dt;
	float output = prefs->Kp*error + prefs->Ki*prefs->integral + prefs->Kd*derivative;

	//Update error
	prefs->pre_error = error;

	return output;
}

void motor_init() {
	motor.mode = VELOCITY;
	motor.target_vel	= 0;

	motor.pid.epsilon	= 0.00;
	motor.pid.dt		= 0.1;
	motor.pid.Kp		= 3.0;
	motor.pid.Kd		= 0.1;
	motor.pid.Ki		= 0.014;

	// pin change interrupt
	// for quadrature encoder
	PCICR = 1 << PCIE0;
	PCMSK0 = 1 << PCINT0;

	// motor control pins
	DDRD |= 1 << PIN_M_EN;
	DDRD |= (1 << PIN_M_1A) | (1 << PIN_M_2A);
	MOTOR_DISABLE();

	// setup 16 bit timer
	TCCR1B |= CLK_8;
	TIMSK1 |= 1 << OCIE1A; // interrupt on OCR1A compare match
	OCR1A = 0xFFF;

	// pwm using timer0
	// phase correct, OCR0A top, no prescale
	TCCR0A = (1 << COM0A0) | (1 << COM0A1) | (1 << WGM00);
	TCCR0B = (1 << CS00);

	OCR0A = 255; // off
}

void motor_set_pos(uint32_t pos) {
	motor.mode = POSITION;
	motor.target_pos = pos;
}

void motor_set_vel(int32_t vel) {
	motor.mode = VELOCITY;
	motor.target_vel = vel;

	MOTOR_ENABLE();
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
	MOTOR_DISABLE();
	PIN_OFF(PORTD, PIN_M_1A);
	PIN_OFF(PORTD, PIN_M_2A);
}
