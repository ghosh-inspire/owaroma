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


#include "owaroma_control.h"
#include "owaroma_control_private.h"
#include "owaroma_uart_driver.h"
#include "owaroma_timer_driver.h"
#include "owaroma_gpio_driver.h"
#include <stdbool.h>
#include <stdio.h>

static char gu8PrintBuffer[OWAROMA_PRINT_BUFFER_SIZE];

static GpioChannel_t gsGpioChannelsMap[NUM_CHANNELS] = {
	{0, 0, false},
	{46, 0, false},
	{3, 0, false},
	{8, 0, false},
	{18, 0, false},
	{17, 0, false},
	{16, 0, false}
};

void owaroma_platform_init(void) {
    for (int i = 0; i < NUM_CHANNELS; i++) {
        gsGpioChannelsMap[i].bIsActive = false;
    }
    owaroma_timer_init();  // Initialize timer driver
    owaroma_uart_init();   // Initialize uart driver
    owaroma_gpio_init();   // Initialize gpio driver
}

void owaroma_disable_channel(unsigned int ui32Channel) {

    if (ui32Channel > NUM_CHANNELS) {
        owaroma_uart_print("Invalid channel\n");
        return;
    }

    if (gsGpioChannelsMap[ui32Channel].bIsActive) {
        owaroma_gpio_set_low(PUMP_GPIO);  // Stop Pump
        owaroma_gpio_set_low(gsGpioChannelsMap[ui32Channel].ui32GpioPin);  // Close valve
        gsGpioChannelsMap[ui32Channel].bIsActive = false;

        snprintf(gu8PrintBuffer, OWAROMA_PRINT_BUFFER_SIZE, "Channel %d disabled\n", ui32Channel);
        owaroma_uart_print(gu8PrintBuffer);
    } else {
        snprintf(gu8PrintBuffer, OWAROMA_PRINT_BUFFER_SIZE, "Channel %d already disabled\n", ui32Channel);
    }
}

void owaroma_enable_channel(int ui32Channel) {

    if (ui32Channel > NUM_CHANNELS) {
        owaroma_uart_print("Invalid channel\n");
        return;
    }

    // disable any active channel
    for (int i = 0; i < NUM_CHANNELS; i++) {
        if (gsGpioChannelsMap[i].bIsActive) {
            owaroma_disable_channel(i);
        }
    }

    owaroma_gpio_set_high(gsGpioChannelsMap[ui32Channel].ui32GpioPin);  // Open valve
    owaroma_gpio_set_high(PUMP_GPIO);  // Start pump
    gsGpioChannelsMap[ui32Channel].bIsActive = true;
    gsGpioChannelsMap[ui32Channel].u32StartTime = owaroma_timer_read();

    snprintf(gu8PrintBuffer, OWAROMA_PRINT_BUFFER_SIZE, "Channel %d enabled\n", ui32Channel);
    owaroma_uart_print(gu8PrintBuffer);
}

void owaroma_proc_cmds(char c8Cmd) {

    if ((c8Cmd == '0') || (c8Cmd == 'a')) {
        owaroma_uart_print("Keep Alive\n");
	return;
    }

    if (c8Cmd >= '1' && c8Cmd <= '6') {
        owaroma_enable_channel(c8Cmd - '0');
    } else if (c8Cmd >= 'b' && c8Cmd <= 'g') {
        owaroma_disable_channel(c8Cmd - 'a');  // Disable channels 'b' to 'g'
    } else {
        owaroma_uart_print("Unknown command\n");
    }
}

bool owaroma_check_auto_close(void) {

    bool bChannelsActive = false;
    unsigned long ui32CurrTime = owaroma_timer_read();

    for (int i = 0; i < NUM_CHANNELS; i++) {
        if (gsGpioChannelsMap[i].bIsActive) {
            if (ui32CurrTime - gsGpioChannelsMap[i].u32StartTime >= AUTO_CLOSE_DELAY) {
                owaroma_disable_channel(i);
            } else {
                bChannelsActive = true;
            }
        }
    }

    return !bChannelsActive;
}
