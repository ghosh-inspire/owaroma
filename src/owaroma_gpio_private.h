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

#ifndef OWAROMA_GPIO_PRIVATE_H
#define OWAROMA_GPIO_PRIVATE_H

#define GPIO_BASE_ADDRESS 0x40000000

#define GPIO_SET_PIN(pin)   (GPIO_OUT_DATA_REG |= (pin))
#define GPIO_CLEAR_PIN(pin) (GPIO_OUT_DATA_REG &= ~(pin))

#define GPIO_READ_PIN(pin)  ((GPIO_IN_DATA_REG & (pin)) != 0)

#define GPIO_SET_DIR_OUTPUT(pin) (GPIO_CONFIG_DIRECTION |= (pin))
#define GPIO_SET_DIR_INPUT(pin)  (GPIO_CONFIG_DIRECTION &= ~(pin))

#endif // OWAROMA_GPIO_PRIVATE_H
