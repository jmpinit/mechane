#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Led.h"
#include "Serial.h"
#include "Motor.h"

#define forever for(;;)

// constants

#define NUM_SIZE 5 // len of number params in digits

Motor motor;

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
	// led init
	DDRC |= (1 << LED_GREEN) | (1 << LED_RED);
	PORTC |= 1 << LED_RED;

	uart_init(50); // 19200 baud
	motor_init();

	sei();

	// control

	char digit_buffer[NUM_SIZE];
	char* digit = digit_buffer;

	Mode mode = LISTEN;

	forever {
		/*sprintf(buffer, "vel=%d\r\n", (int)motor.vel);
		uart_tx_str(buffer);*/
		/*for(int i=0; i<motor.pos; i++)
			uart_tx('*');
		uart_tx_str("\r\n");*/
		int v = motor.vel;
		int tv = motor.target_vel;
		if(v < 0) v = - v;
		if(tv < 0) tv = -tv;
		for(int i=0; i<v || i<tv && i<64; i++) {
			if(i < tv && i < v) {
				uart_tx('*');
			} else if(i < v) {
				uart_tx('+');
			} else if(i < tv) {
				uart_tx('x');
			}
		}
		uart_tx_str("\r\n");

		while(uart_available()) {
			char c = uart_read_buff();
			//uart_tx(c);

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
						case 'i':
						case 'I':
							sprintf(buffer, "pos=%u\r\n", motor.pos);
							uart_tx_str(buffer);
							sprintf(buffer, "vel=%d\r\n", motor.vel);
							uart_tx_str(buffer);
							sprintf(buffer, "target pos=%u\r\n", motor.target_pos);
							uart_tx_str(buffer);
							sprintf(buffer, "target vel=%d\r\n", motor.target_vel);
							uart_tx_str(buffer);
							break;
					}

					mode = LISTEN;
				} else {
					if((c >= '0' && c <= '9') || c == '+' || c == '-' || c == 'p' || c == 'd' || c == 'i') {
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

								switch(digit_buffer[0]) {
									case '+':
									case '-':
										switch(motor.mode) {
											case POSITION:
												motor_set_pos((digit_buffer[0] == '-' ? -1 : 1) * num);
												break;
											case VELOCITY:
												motor_set_vel((digit_buffer[0] == '-' ? -1 : 1) * num);
												break;
										}
										break;
									// PID set
									case 'p':
										motor.pid.Kp = num;
										break;
									case 'd':
										motor.pid.Kd = num;
										break;
									case 'i':
										motor.pid.Ki = num;
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
