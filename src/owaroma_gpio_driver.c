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

#include "owaroma_gpio_driver.h"
#include "owaroma_gpio_private.h"
#include "owaroma_uart_driver.h"

#include <stdio.h>

// simulated gpio registers
static unsigned long GPIO_OUT_DATA_REG;
static unsigned long GPIO_IN_DATA_REG;
static unsigned long GPIO_CONFIG_DIRECTION;

static char gu8PrintBuffer[OWAROMA_PRINT_BUFFER_SIZE];

void owaroma_gpio_init(void) {

    GPIO_OUT_DATA_REG = 0;
    GPIO_IN_DATA_REG = 0;
    GPIO_CONFIG_DIRECTION = 0;

    owaroma_uart_print("GPIO initialized\n");
}

// Function to write to a GPIO pin, set/clear
static void owaroma_gpio_write(int pin, bool value) {

    if (pin < 0 || pin >= 64) {
        snprintf(gu8PrintBuffer, OWAROMA_PRINT_BUFFER_SIZE, "Invalid GPIO pin: %d\n", pin);
        owaroma_uart_print(gu8PrintBuffer);
        return;
    }
    if (value) {
	GPIO_SET_PIN(1U << pin);  // Set the GPIO pin
    } else {
	GPIO_CLEAR_PIN(1U << pin);  // Clear the GPIO pin
    }
    snprintf(gu8PrintBuffer, OWAROMA_PRINT_BUFFER_SIZE, "GPIO %d %s\n", pin, value ? "set HIGH" : "set LOW");
    owaroma_uart_print(gu8PrintBuffer);
}

// Function to read the state of a GPIO pin
static bool owaroma_gpio_read(int pin) {

    if (pin < 0 || pin >= 64) {
        snprintf(gu8PrintBuffer, OWAROMA_PRINT_BUFFER_SIZE, "Invalid GPIO pin: %d\n", pin);
        owaroma_uart_print(gu8PrintBuffer);
        return false;
    }
    return GPIO_READ_PIN(1U << pin);  // Return true if the pin is set, false otherwise
}

// Function to configure a GPIO pin as output
void owaroma_gpio_config_out(int pin) {

    GPIO_SET_DIR_OUTPUT(1U << pin);  // Set the pin as output
    snprintf(gu8PrintBuffer, OWAROMA_PRINT_BUFFER_SIZE, "GPIO %d configured as OUTPUT\n", pin);
    owaroma_uart_print(gu8PrintBuffer);
}

// Function to configure a GPIO pin as input
void owaroma_gpio_config_in(int pin) {

    GPIO_SET_DIR_INPUT(1U << pin);  // Set the pin as input
    snprintf(gu8PrintBuffer, OWAROMA_PRINT_BUFFER_SIZE, "GPIO %d configured as INPUT\n", pin);
    owaroma_uart_print(gu8PrintBuffer);
}

// Function to set a GPIO pin high
void owaroma_gpio_set_high(int pin) {

    owaroma_gpio_write(pin, true);  // Write high (true) to the GPIO pin
}

// Function to set a GPIO pin low
void owaroma_gpio_set_low(int pin) {

    owaroma_gpio_write(pin, false);  // Write low (false) to the GPIO pin
}
