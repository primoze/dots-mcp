// System
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>


#include <dots-mcp/hal.h>


OS_INLINE
void panic() __attribute__((noreturn));

OS_C_ABI
int main(void) {

    os::hal::init();

    panic();
}

void panic() {
    DDRB |= _BV(5);
    bool state = true;
    while(true) {
        if(state) {
            PORTB |= _BV(5);
        } else {
            PORTB &= _BV(5) ^ 0xFF;
        }
        state = !state;
        _delay_ms(500);
    }
}
