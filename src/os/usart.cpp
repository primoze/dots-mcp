
#include <os/usart.h>
#include <os/bits.h>

#include <avr/pgmspace.h>


// Serial 0 / USB definitions
// Baud Rate Register
#if defined(UBRRH) && defined(UBRRL)
#	define USART_BRRH UBRRH
#	define USART_BRRL UBRRL
#else
#	define USART_BRRH UBRR0H
#	define USART_BRRL UBRR0L
#endif // UBBRH && UBBRL

// Control and Status Registers A, B, C
#if defined(UCSRA)
#	define USART_CSRA UCSRA
#else
#	define USART_CSRA UCSR0A
#endif // UCSRA

#if defined(UCSRB)
#	define USART_CSRB UCSRB
#else
#	define USART_CSRB UCSR0B
#endif // UCSRB

#if defined(UCSRC)
#	define USART_CSRC UCSRC
#else
#	define USART_CSRC UCSR0C
#endif // UCSRC

// Data Register
#if defined(UDR)
#	define USART_DR UDR
#else
#	define USART_DR UDR0
#endif // UDR


namespace os {

namespace {
	ioreg_t _ubrrh = &USART_BRRH;
	ioreg_t _ubrrl = &USART_BRRL;
	ioreg_t _ucsra = &USART_CSRA;
	ioreg_t _ucsrb = &USART_CSRB;
	ioreg_t _ucsrc = &USART_CSRC;
	ioreg_t _udr = &USART_DR;
}

void USART_Init(uint32_t rate) {
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

void USART_Tx(byte_t data) {
	// Wait for empty transmit buffer
	while (!os::get_bit(*_ucsra, UDRE0) && !os::get_bit(*_ucsra, TXC0)) { }
	// Write data
	*_udr = data;
}

void USART_Rx(byte_t& data) {
	while ( !(*_ucsra & (1<<RXC0)) ) {}
	// Get and return received data from buffer
	data = *_udr;
}

int USART_Tx(os::flash_cstring_t str) {
	PGM_P s = reinterpret_cast<PGM_P>(str);
	size_t n = 0;
	byte_t b = pgm_read_byte(s++);

	while (b) {
		USART_Tx(b);
		++n;
		b = pgm_read_byte(s++);
	}
	return n;
}

int USART_Tx(const byte_t* buf, uint16_t count) {
	if(!buf || !count) {
		return -1;
	}

	for(uint16_t i=0; i<count; ++i) {
		USART_Tx(buf[i]);
	}

	return count;
}

int USART_Rx(byte_t* buf, uint16_t count) {
	if(!buf || !count) {
		return -1;
	}

	for(uint16_t i=0; i<count; ++i) {
		USART_Rx(buf[i]);
	}

	return count;
}

}
