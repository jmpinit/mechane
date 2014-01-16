#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Serial.h"

#define forever for(;;)

#define CLK_NONE	1
#define CLK_8		2
#define CLK_64		3
#define CLK_256		4
#define CLK_1024	5

// constants

#define BAUD 4800

int main(void) {
	uart_init(F_CPU/16/BAUD-1);

	forever {
		while(uart_available()) {
			uart_tx_str("hello world");
			_delay_ms(3000);
		}
	}

	return 0;
}
