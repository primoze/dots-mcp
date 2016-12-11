
#include <os/timer.h>


namespace os {
namespace timer {


#ifdef __AVR_ATmega328P__

os::timer::timer1_t timer1;

ISR(TIMER1_OVF_vect)
{
    timer1.tick();
}

#endif


}
}
