/*
MIT License

Copyright (c) 2024 OW AROMA Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "owaroma_timer_driver.h"
#include "owaroma_uart_driver.h"
#include <unistd.h>

// simulated timer register
static unsigned long TIME_CNT_REGISTER = 0;

void owaroma_timer_init(void) {

    TIME_CNT_REGISTER = 0;

    owaroma_uart_print("TIMER initialized\n");
}

// timer irq handler
void owaroma_timer_irq_handler() {

    sleep(1); // called every one sec
    TIME_CNT_REGISTER += 1;
}

unsigned long owaroma_timer_read(void) {

    owaroma_timer_irq_handler(); // simulate timer handler called every 1 sec

    return TIME_CNT_REGISTER;
}
