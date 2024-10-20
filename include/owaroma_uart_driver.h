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


#ifndef OWAROMA_UART_DRIVER_H
#define OWAROMA_UART_DRIVER_H

#include <stdbool.h>

#define OWAROMA_PRINT_BUFFER_SIZE 100

// Initialize the UART
extern void owaroma_uart_init(void);

// UART IRQ Handler
extern void owaroma_uart_irq_handler(const char *pc8Data);

// Print a string to the UART
extern void owaroma_uart_print(const char *str);

extern bool owaroma_uart_read(char *pc8Data);
extern void owaroma_uart_write(const char *pc8Data);

#endif // OWAROMA_UART_DRIVER_H
