
#include <os/usart.h>
#include <os/bits.h>

#include <avr/pgmspace.h>


// Serial 0 / USB definitions
#define USART_BRRH UBRR0H
#define USART_BRRL UBRR0L

// Control and Status Registers A, B, C
#define USART_CSRA UCSR0A
#define USART_CSRB UCSR0B
#define USART_CSRC UCSR0C

// Data Register
#define USART_DR UDR0


namespace os {
namespace usart {
namespace {

pioreg_t _ubrrh = &USART_BRRH;
pioreg_t _ubrrl = &USART_BRRL;
pioreg_t _ucsra = &USART_CSRA;
pioreg_t _ucsrb = &USART_CSRB;
pioreg_t _ucsrc = &USART_CSRC;
pioreg_t _udr = &USART_DR;

}

void init(uint32_t rate) {
	uint32_t brr_val = F_CPU / (16*rate) - 1;

	// Set baud rate
	*_ubrrh = (byte_t)(brr_val >> 8);
	*_ubrrl = (byte_t)brr_val;

	// Sync mode
	os::clear_bit(*_ucsrc, UMSEL00);
	os::clear_bit(*_ucsrc, UMSEL01);
	// 8 data bits
	os::set_bit(*_ucsrc, UCSZ00);
	os::set_bit(*_ucsrc, UCSZ01);
	os::clear_bit(*_ucsrb, UCSZ02);
	// No parity bits
	os::clear_bit(*_ucsrc, UPM00);
	os::clear_bit(*_ucsrc, UPM01);
	// 2 stop bits
	os::set_bit(*_ucsrc, USBS0);
	// Enable Rx/Tx
	os::set_bit(*_ucsrb, RXEN0);
	os::set_bit(*_ucsrb, TXEN0);
}

void transmit(byte_t data) {
	// Wait for empty transmit buffer
	while (!os::get_bit(*_ucsra, UDRE0) && !os::get_bit(*_ucsra, TXC0)) { }
	// Write data
	*_udr = data;
}

void receive(byte_t& data) {
	while ( !(*_ucsra & (1<<RXC0)) ) {}
	// Get and return received data from buffer
	data = *_udr;
}

int transmit(os::flash_cstring_t* str) {
	PGM_P s = reinterpret_cast<PGM_P>(str);
	size_t n = 0;
	byte_t b = pgm_read_byte(s++);

	while (b) {
		transmit(b);
		++n;
		b = pgm_read_byte(s++);
	}
	return n;
}

int transmit(const byte_t* buf, uint16_t count) {
	if(!buf || !count) {
		return -1;
	}

	for(uint16_t i=0; i<count; ++i) {
		transmit(buf[i]);
	}

	return count;
}

int receive(byte_t* buf, uint16_t count) {
	if(!buf || !count) {
		return -1;
	}

	for(uint16_t i=0; i<count; ++i) {
		receive(buf[i]);
	}

	return count;
}

bool writer::write(const byte_t b) {
    os::usart::transmit(b);
    return true;
}

}
}

