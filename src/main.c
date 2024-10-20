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
#include "owaroma_uart_driver.h"
#include <unistd.h>
#include <stdio.h>

int main(void) {

    eOwAromaSysStates eOwAromaState = OWAMOMA_SYS_STATE_INIT;
    char command = '\0';

    while (eOwAromaState != OWAMOMA_SYS_STATE_EXIT) {

        switch (eOwAromaState) {

            case OWAMOMA_SYS_STATE_INIT:

                /* platform init */
                owaroma_platform_init();
                owaroma_uart_print("Platform Init Done, ready to receive commands\n");

                owaroma_uart_irq_handler("12349e6");  /* Dummy commands for testing */
                eOwAromaState = OWAMOMA_SYS_STATE_GET_CMD;
            break;

            case OWAMOMA_SYS_STATE_GET_CMD:

	        bool bCmdRead = owaroma_uart_read(&command);

		if (bCmdRead) {
                    eOwAromaState = OWAMOMA_SYS_STATE_PROC_CMD;
		} else {
                    eOwAromaState = OWAMOMA_SYS_STATE_AUTO_CLOSE;
		}
            break;

            case OWAMOMA_SYS_STATE_PROC_CMD:

                /* process commands */
                owaroma_proc_cmds(command);
                command = '\0';

                eOwAromaState = OWAMOMA_SYS_STATE_AUTO_CLOSE;
            break;

            case OWAMOMA_SYS_STATE_AUTO_CLOSE:

	        owaroma_check_auto_close();

                owaroma_uart_irq_handler("0");  /* Dummy commands for testing */

		eOwAromaState = OWAMOMA_SYS_STATE_GET_CMD; /* This is just for test application to cleanly exit */
            break;

            default:
                    owaroma_uart_print("Invalid command, ignoring..\n");
                    eOwAromaState = OWAMOMA_SYS_STATE_GET_CMD;
            break;
	}
    }

    return 0;
}
