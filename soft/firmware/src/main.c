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

// pins

#define PIN_LED0		PC4
#define PIN_LED1		PC5

#define PIN_A			PB0
#define PIN_B			PB1

volatile Motor motor;

ISR(TIMER1_COMPA_vect) {
	motor.inverse_speed = 0xFFFF;
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

char buffer[16];

int main(void) {
	uart_init(F_CPU/16/BAUD-1);
	motor_init();

	DDRC |= (1 << PIN_LED0) | (1 << PIN_LED1);

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
						case 'p': // set position mode
						case 'P':
							motor.mode = POSITION;
							break;
						case 'v': // set velocity mode
						case 'V':
							motor.mode = VELOCITY;
							break;
						case 's': // status
						case 'S':
							uart_tx_str("I am okay.\n\r");
							uart_tx_str("motor.mode: ");
							switch(motor.mode) {
								case POSITION:		uart_tx_str("position\n\r"); break;
								case VELOCITY:		uart_tx_str("velocity\n\r"); break;
								case ACCELERATION:	uart_tx_str("acceleration\n\r"); break;
							}
							break;
						case 'k': // kill (de-energize)
						case 'K':
							motor_stop();
							break;
						case 'b':
						case 'B': // brake
							motor_brake();
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
