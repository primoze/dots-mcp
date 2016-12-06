
#ifndef OS_USART_H
#define OS_USART_H

#include <avr/interrupt.h>
#include <os/common.h>
#include <os/cstring.h>

namespace os {

	void USART_Init(uint32_t rate);

	// Write a single byte.
	void USART_Tx(byte_t data);

	// Write buffer
	int USART_Tx(const byte_t* buf, uint16_t count);

	// Write flash string
	int USART_Tx(os::flash_cstring_t str);

	// Read a single byte.
	void USART_Rx(byte_t& data);

	// Read buffer
	int USART_Rx(byte_t* buf, uint16_t count);
}



#endif // OS_USART_H
