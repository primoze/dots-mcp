
#include <os/usart.h>
#include <os/bits.h>

#include <avr/pgmspace.h>




namespace os {
namespace usart {

#if defined (__AVR_ATmega328P__)

os::usart::usart0_t usart0;
os::usart::usart0_writer_t usart0_writer;

#endif // __AVT_ATmega328p__


}
}

