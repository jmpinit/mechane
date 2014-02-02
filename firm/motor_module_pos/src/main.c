#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Led.h"
#include "Serial.h"
#include "Motor.h"
#include "rfm12.h"

#define forever for(;;)

// constants
long target_pos;

int main(void) {
	// led init
	DDRC |= (1 << LED_GREEN) | (1 << LED_RED);
	PORTC |= 1 << LED_GREEN;

	uart_init(27); // 19200 baud
	motor_init();
	rfm12_init();

	sei();

	target_pos = 1024;

	// control

	forever {
		/*for(int i=0; i < 255; i += 16) {
			motor_forward(i);
			_delay_ms(500);

			motor_brake();
			_delay_ms(500);
			
			motor_backward(i);
			_delay_ms(500);
			
			motor_brake();
			_delay_ms(500);
		}*/

		while(uart_available()) {
			motor_brake();
		}
	}

	return 0;
}
