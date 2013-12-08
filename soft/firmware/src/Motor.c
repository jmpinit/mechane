#include <stdint.h>
#include <avr/io.h>

#include "Motor.h"

void motor_set_pos(int8_t dir, unsigned int speed) {
	motor.ticks = speed;
	motor_set_vel(dir, motor.target_speed);
}

void motor_set_vel(int8_t dir, unsigned int speed) {
	PORTC |= 1 << PIN_M_EN;
	PORTC &= ~(1 << PIN_M_1A);
	PORTC |= 1 << PIN_M_2A;
}

void motor_set_accel(int8_t dir, unsigned int speed) {
	PORTC &= ~(1 << PIN_M_1A);
	PORTC |= 1 << PIN_M_2A;
}

void motor_stop() {
	PORTC &= ~(1 << PIN_M_1A);
	PORTC &= ~(1 << PIN_M_2A);
}

void motor_brake() {
	PORTC &= ~(1 << PIN_M_EN);
	PORTC &= ~(1 << PIN_M_1A);
	PORTC &= ~(1 << PIN_M_2A);
}
