// System
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <os/common.h>
#include <os/bits.h>
#include <os/usart.h>
#include <os/cstring.h>
#include <os/stream.h>



os::io::stream<os::usart::writer> stream;

OS_C_ABI
int main(void) {

    auto os = OS_MK_FSTR("dots-mcp v0.0.1\n");

	cli();
	os::usart::init(9600);

	stream.write(os);

    panic();
}

void panic() {
    DDRB |= _BV(5);
    while(true) {
        PORTB |= _BV(5);
        _delay_ms(500);
        PORTB &= _BV(5) ^ 0xFF;
        _delay_ms(500);
    }
}
