/*
 * Copyright 2016 Primoz Erjavec
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef DOTS_MCP_HAL_H_
#define DOTS_MCP_HAL_H_


#include <dots-core/stream.h>
#include <dots-core/timer.h>
#include <dots-core/usart.h>

namespace os {
namespace hal {

void init();

#if defined (__AVR_ATmega328P__)

typedef os::timer::timer_16bit<0x80, 0x6f> timer1_t;
extern os::hal::timer1_t timer1;

typedef os::usart::usart<0xc0> usart0_t;
extern os::hal::usart0_t usart0;

typedef os::usart::writer<os::hal::usart0_t> usart0_writer_t;

typedef os::io::stream<os::hal::usart0_writer_t> stdout_t;
extern os::hal::stdout_t stdout;

#endif // __AVR_ATmega328P__


}
}



#endif // DOTS_MCP_HAL_H_
