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


#ifndef OWAROMA_CONTROL_H
#define OWAROMA_CONTROL_H

#include <stdbool.h>

typedef enum {
    OWAMOMA_SYS_STATE_INIT,       /* Init platform */
    OWAMOMA_SYS_STATE_GET_CMD,    /* Read commands from UART */
    OWAMOMA_SYS_STATE_PROC_CMD,   /* Process received commands */
    OWAMOMA_SYS_STATE_AUTO_CLOSE, /* Check if channel can be auto closed */
    OWAMOMA_SYS_STATE_EXIT,       /* Exit procesing commands */
    OWAMOMA_SYS_STATE_INVALID
} eOwAromaSysStates;

/* Initialize the platform */
extern void owaroma_platform_init(void);

/* Process the command received via UART */
extern void owaroma_proc_cmds(char c8Cmd);

/* Check for auto close of channels */
extern bool owaroma_check_auto_close(void);

#endif /* OWAROMA_CONTROL_H */
