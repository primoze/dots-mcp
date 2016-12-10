
#ifndef OS_USART_H
#define OS_USART_H

#include <avr/interrupt.h>
#include <os/common.h>
#include <os/cstring.h>
#include <os/bits.h>


namespace os {
namespace usart {

void init(uint32_t rate);

// Write a single byte.
void transmit(byte_t data);

// Write buffer
int transmit(const byte_t* buf, uint16_t count);

// Write flash string
int transmit(os::flash_cstring_t str);

// Read a single byte.
void receive(byte_t& data);

// Read buffer
int receive(byte_t* buf, uint16_t count);

// Writer for os::stream
class writer {
public:
    bool write(const byte_t b);
};

}
}



#endif // OS_USART_H
