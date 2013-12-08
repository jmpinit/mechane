#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define forever for(;;)

#define CLK_NONE	1
#define CLK_8		2
#define CLK_64		3
#define CLK_256		4
#define CLK_1024	5

// constants

#define BAUD 4800

#define MOTOR_SLOWEST	0xFFF // the slowest speed cutoff

#define LEFT	1
#define RIGHT	-1

// pins

#define PIN_M_1A		PC0
#define PIN_M_2A		PC1
#define PIN_M_EN		PC2

#define PIN_LED0		PD6
#define PIN_LED1		PD7

#define PIN_A			PB0
#define PIN_B			PB1

// motor info
typedef struct {
	int8_t dir;
	uint16_t inverse_speed;
} Motor;

volatile Motor motor;

volatile uint8_t overflows = 0;
volatile uint8_t hist_portb = 0xFF;

ISR(PCINT0_vect) {
	uint8_t changed;

	changed = PINB ^ hist_portb;
	hist_portb = PINB;

	if(changed & (1 << PB0)) { // pb0 changed
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

void uart_tx(char c);

ISR(TIMER1_COMPA_vect) {
	motor.inverse_speed = 0xFFFF;
	overflows++;
}

void uart_init(unsigned int ubrr) {
	// set tx output
	PORTD |= 1 << PD1;

	// set baud rate
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	// enable rx and tx
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	// set frame format: 8data, 2stop bit
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void uart_tx(char c) {
	// wait for empty tx buffer
	while(!(UCSR0A & (1<<UDRE0))) asm volatile ("NOP");

	// put char in buffer
	UDR0 = c;
}

void uart_tx_str(char* str) {
	char c;
	while((c = *(str++))) uart_tx(c);
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

int main(void) {
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

	forever {
		// forward
		PORTC &= ~(1 << PIN_M_2A);
		PORTC |= 1 << PIN_M_1A;
		delay_print(100, 10);
		
		// backward
		PORTC &= ~(1 << PIN_M_1A);
		PORTC |= 1 << PIN_M_2A;
		delay_print(100, 10);

		// stop
		PORTC &= ~(1 << PIN_M_1A);
		PORTC &= ~(1 << PIN_M_2A);
		delay_print(100, 10);
	}

	return 0;
}
