#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Serial.h"
#include "Motor.h"

#define forever for(;;)

#define CLK_NONE	1
#define CLK_8		2
#define CLK_64		3
#define CLK_256		4
#define CLK_1024	5

// constants

#define BAUD 4800

#define NUM_SIZE 5

#define MOTOR_SLOWEST	0xFFF // the slowest speed cutoff

#define LEFT	1
#define RIGHT	-1

// pins

#define PIN_LED0		PD6
#define PIN_LED1		PD7

#define PIN_A			PB0
#define PIN_B			PB1

volatile uint8_t overflows = 0;
volatile uint8_t hist_portb = 0xFF;

volatile Motor motor;

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

ISR(TIMER1_COMPA_vect) {
	motor.inverse_speed = 0xFFFF;
	overflows++;
}

char buffer[16];
void delay_print(int itrs, int time) {
	for(int i=0; i < itrs; i++) {
		if(motor.dir == LEFT)
			sprintf(buffer, "-%u\n\r", motor.inverse_speed);
		else
			sprintf(buffer, "%u\n\r", motor.inverse_speed);

		uart_tx_str(buffer);
		for(int k=0; k<time; k++) _delay_ms(1);
	}
}

uint16_t decode(char* buffer, char* top) {
	uint16_t value = 0;
	static const uint16_t lookup[] = { 1, 10, 100, 1000, 10000 };

	uint8_t place = 0;
	while(top > buffer) {
		char c = *(--top);
		
		if(c >= '0' && c <= '9') {
			uint8_t digit = c - '0';
			value += digit*lookup[place++];
		}
	}

	return value;
}

typedef enum {
	LISTEN,
	READ,
	CMD,
	CONFUSED
} Mode;

int main(void) {
	motor.target_speed = 20;

	uart_init(F_CPU/16/BAUD-1);

	// setup pin change interrupts
	PCICR = 1 << PCIE0;
	PCMSK0 = 1 << PCINT0;

	// setup pins
	DDRC |= (1 << PIN_M_EN) | (1 << PIN_M_1A) | (1 << PIN_M_2A);
	DDRD |= (1 << PIN_LED0) | (1 << PIN_LED1);

	// motor enabled
	DDRC |= (1 << 2);
	PORTC |= (1 << 2);

	// setup 16 bit timer
	TCCR1B |= CLK_8;
	TIMSK1 |= 1 << OCIE1A; // interrupt on OCR1A compare match
	OCR1A = MOTOR_SLOWEST;

	sei();

	// control

	char digit_buffer[NUM_SIZE];
	char* digit = digit_buffer;

	Mode mode = LISTEN;

	forever {
		while(uart_available()) {
			char c = uart_read_buff();

			if(mode == CONFUSED) {
				// line end brings clarity
				if(c == '\n' || c == '\r') mode = LISTEN;
			} else {
				if(mode == CMD) {
					switch(c) {
						case 'p':
						case 'P':
							// TODO position query
							uart_tx_str("pos\n\r");
							break;
						case 's':
						case 'S':
							// TODO status message
							uart_tx_str("status\n\r");
							break;
						case 'k':
						case 'K':
							// TODO kill (de-energize)
							uart_tx_str("kill\n\r");
							break;
						case 'b':
						case 'B':
							// TODO brake
							uart_tx_str("brake\n\r");
							break;
					}

					mode = LISTEN;
				} else {
					if((c >= '0' && c <= '9') || c == '-') {
						// starting a number?
						if(mode == LISTEN) {
							mode = READ;
							digit = digit_buffer;
						}

						// save the digit
						if(digit >= digit_buffer + NUM_SIZE) {
							mode = CONFUSED; // too many digits
						} else {
							*(digit++) = c;
						}
					} else {
						if(c == '\n' || c == '\r') {
							if(mode == READ) { // use the parameter that was read in
								uint16_t num = decode(digit_buffer, digit);

								switch(motor.mode) {
									case POSITION:
										motor_set_pos(digit_buffer[0] == '-' ? LEFT : RIGHT, num);
										break;
									case VELOCITY:
										motor_set_vel(digit_buffer[0] == '-' ? LEFT : RIGHT, num);
										break;
									case ACCELERATION:
										motor_set_accel(digit_buffer[0] == '-' ? LEFT : RIGHT, num);
										break;
								}
							}

							mode = LISTEN;
						} else if(c == '\\') {
							if(mode != LISTEN) {
								mode = CONFUSED;
							} else {
								mode = CMD;
							}
						} else {
							mode = CONFUSED;
						}
					}
				}
			}
		}
	}

	return 0;
}
