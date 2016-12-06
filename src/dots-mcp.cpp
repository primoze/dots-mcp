// System
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <os/common.h>
#include <os/usart.h>
#include <os/cstring.h>


OS_C_ABI
int main(void) {

	cli();
	os::USART_Init(9600);
	sei();

	os::flash_cstring_t str = OS_FSTR("hellooooooo!!!!!!!");
	for(byte_t i=0; i<10; ++i) {
		os::USART_Tx(str);
	}

    // The LED is on Port B, Pin 5
    // Setup LED pin as an output
    DDRB |= _BV(5);

    // Loop forever
    while (1)
    {
        // Turn LED on for 500ms
        PORTB |= _BV(5);
        _delay_ms(500);

        // Turn LED off for 500ms
        PORTB &= _BV(5) ^ 0xFF;
        _delay_ms(500);
//    	os::USART_Tx(66);
    }
    return 0;
}

