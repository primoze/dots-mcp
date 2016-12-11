
#ifndef OS_USART_H
#define OS_USART_H

#include <avr/interrupt.h>
#include <os/common.h>
#include <os/cstring.h>
#include <os/bits.h>


namespace os {
namespace usart {



// Writer for os::stream
template <class _usart>
class writer {
public:
    bool write(const byte_t b) {
        return usart.transmit(b);
    }
private:
    _usart usart;
};



template <ioaddr_t _base>
class usart {
public:

    usart() :
        ucsra(&_MMIO_BYTE(_base + UCSRA)),
        ucsrb(&_MMIO_BYTE(_base + UCSRB)),
        ucsrc(&_MMIO_BYTE(_base + UCSRC)),
        ubrrl(&_MMIO_BYTE(_base + UBRRL)),
        ubrrh(&_MMIO_BYTE(_base + UBRRH)),
        udr(&_MMIO_BYTE(_base + UDR))
    {
    }

    bool init(uint32_t rate) {

        uint32_t brr_val = F_CPU / (16*rate) - 1;

        // Set baud rate
        *ubrrh = (byte_t)(brr_val >> 8);
        *ubrrl = (byte_t)brr_val;

        // Disable Rx/Tx
        os::clear_bit(*ucsrb, RXEN0);
        os::clear_bit(*ucsrb, TXEN0);

        // Sync mode
        os::clear_bit(*ucsrc, UMSEL00);
        os::clear_bit(*ucsrc, UMSEL01);
        // 8 data bits
        os::set_bit(*ucsrc, UCSZ00);
        os::set_bit(*ucsrc, UCSZ01);
        os::clear_bit(*ucsrb, UCSZ02);
        // No parity bits
        os::clear_bit(*ucsrc, UPM00);
        os::clear_bit(*ucsrc, UPM01);
        // 2 stop bits
        os::set_bit(*ucsrc, USBS0);
        // Enable Rx/Tx
        os::set_bit(*ucsrb, RXEN0);
        os::set_bit(*ucsrb, TXEN0);
        return true;
    }

    bool transmit(const byte_t& b) {
        // Wait for empty transmit buffer
        while (!os::get_bit(*ucsra, UDRE0) && !os::get_bit(*ucsra, TXC0)) { }
        // Write data
        *udr = b;
        return true;
    }

    pioreg_t ucsra;
    pioreg_t ucsrb;
    pioreg_t ucsrc;
    pioreg_t ubrrl;
    pioreg_t ubrrh;
    pioreg_t udr;

private:
    static constexpr byte_t UCSRA = 0;
    static constexpr byte_t UCSRB = 1;
    static constexpr byte_t UCSRC = 2;
    static constexpr byte_t UBRRL = 4;
    static constexpr byte_t UBRRH = 5;
    static constexpr byte_t UDR = 6;

};

#if defined (__AVR_ATmega328P__)

typedef os::usart::usart<0xc0> usart0_t;
extern os::usart::usart0_t usart0;

typedef os::usart::writer<os::usart::usart0_t> usart0_writer_t;
extern os::usart::usart0_writer_t usart0_writer;

#endif // __AVR_ATmega328P__


}
}



#endif // OS_USART_H
