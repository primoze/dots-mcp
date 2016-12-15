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

#include <dots-core/cstring.h>
#include <dots-mcp/hal.h>

namespace os {
namespace hal {


os::hal::timer1_t timer1;

os::hal::usart0_t usart0;

os::hal::stdout_t stdout;


void init() {
    os::flash_cstring_t os = OS_MK_FSTR("dots-mcp v0.0.1\n");

    cli();
    usart0.init(9600);
//    timer1.init(1000);
    stdout.write(os);
    sei();
}


}
}

