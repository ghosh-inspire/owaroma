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

#include "owaroma_uart_driver.h"
#include "owaroma_uart_private.h"
#include <stdio.h>

static unsigned char UART_DATA_WRITE_REGISTER = 0;

static uart_fifo_t owaroma_uart_fifo;

void owaroma_uart_init(void) {
    owaroma_uart_fifo.i32Head = 0;
    owaroma_uart_fifo.i32Tail = 0;
    owaroma_uart_fifo.i32Count = 0;
    owaroma_uart_print("UART initialized\n");
}

// Check if UART FIFO buffer is full
static bool owaroma_uart_is_full(void) {
    return owaroma_uart_fifo.i32Count == UART_FIFO_SIZE;
}

// Check if UART FIFO buffer is empty
static bool owaroma_uart_is_empty(void) {
    return owaroma_uart_fifo.i32Count == 0;
}

void owaroma_uart_write(const char *pc8Data) {
    while (*pc8Data) {
        if (!owaroma_uart_is_full()) {
            owaroma_uart_fifo.u8Buffer[owaroma_uart_fifo.i32Tail] = *pc8Data;
            owaroma_uart_fifo.i32Tail = (owaroma_uart_fifo.i32Tail + 1) % UART_FIFO_SIZE;
            owaroma_uart_fifo.i32Count++;
        }
        pc8Data++;
    }
}

bool owaroma_uart_read(char *pc8Data) {
    if (!owaroma_uart_is_empty()) {
        *pc8Data = owaroma_uart_fifo.u8Buffer[owaroma_uart_fifo.i32Head];
        owaroma_uart_fifo.i32Head = (owaroma_uart_fifo.i32Head + 1) % UART_FIFO_SIZE;
        owaroma_uart_fifo.i32Count--;
        return true;
    }
    return false;  // No data available
}

// Example UART IRQ handler
void owaroma_uart_irq_handler(const char *pc8Data) {
    owaroma_uart_write(pc8Data);
}

void owaroma_uart_print(const char *pStr) {

    // Send string to UART
    while (*pStr) {
        UART_DATA_WRITE_REGISTER = *pStr;
	putchar(UART_DATA_WRITE_REGISTER);
	pStr++;
    }
    putchar('\0');
}
