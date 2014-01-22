#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "rfm12.h"
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
	// LED init
	DDRB |= 1 << PB0;
	PORTB |= 1 << PB0;

	// uart init
	uart_init(F_CPU/16/BAUD-1);

	// radio init
	uint8_t teststring[] = "teststring\r\n";
	uint8_t packettype = 0xEE;
	rfm12_init();
	sei();

	/*uart_tx_str("i am receiver, hello!\r\n");
	forever {
		if(rfm12_rx_status() == STATUS_COMPLETE) {
			uart_tx_str("new packet:\r\n");

			uint8_t* bufcontents = rfm12_rx_buffer();

			// dump buffer contents to uart         
			for (int i = 0; i < rfm12_rx_len(); i++) {
				uart_tx(bufcontents[i]);
			}

			uart_tx_str("\r\n");

			// tell the implementation that the buffer
			// can be reused for the next data.
			rfm12_rx_clear();
		} else {
			uart_tx_str("status: ");

			switch(rfm12_rx_status()) {
				case STATUS_FREE:
					uart_tx_str("free.\r\n");
					break;
				case STATUS_OCCUPIED:
					uart_tx_str("occupied.\r\n");
					break;
				default:
					uart_tx('0'+rfm12_rx_status());
					uart_tx_str("\r\n");
			}
		}

		PORTB &= ~(1 << PB0);
		_delay_ms(50);
		PORTB |= 1 << PB0;
		_delay_ms(50);
	}*/

	uart_tx_str("i am sender, hello!\r\n");
	forever {
		uart_tx_str("sending...\r\n");
		rfm12_tx(sizeof(teststring), packettype, teststring);
		rfm12_tick();

		uart_tx_str("sent.\r\n");

		PORTB &= ~(1 << PB0);
		_delay_ms(500);
		PORTB |= 1 << PB0;
		_delay_ms(500);
	}

	return 0;
}
