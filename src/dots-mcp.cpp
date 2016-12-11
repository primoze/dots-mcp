// System
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <os/common.h>
#include <os/bits.h>
#include <os/usart.h>
#include <os/timer.h>
#include <os/cstring.h>
#include <os/stream.h>


os::io::stream<os::usart::usart0_writer_t> stream;


OS_C_ABI
int main(void) {

    using os::usart::usart0;
    using os::timer::timer1;

    os::flash_cstring_t os = OS_MK_FSTR("dots-mcp v0.0.1\n");

    cli();
    usart0.init(9600);
    timer1.init(500);
    stream.write(os);
    sei();


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
