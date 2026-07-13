// SPDX-License-Identifier: MIT-0
// Macro Microcontroller 2 Custom Firmware Template
// This template assigns GPIO pins to built-in IO devices and set pin mode.
/*
MIT No Attribution

Copyright (C) 2026 Nicholas Lim.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/sync.h"

void userProgram();

// By default, IO pins are set to output mode.
int IOMode = 0;
// Uncomment the following line to set IO pins to input mode.
// int IOMode = 1;

// Assign GPIOs to switches.
const int SW1 = 0;
const int SW2 = 1;
const int SW3 = 2;

// Assign GPIOs to pins.
const int IO1 = 3;
const int IO2 = 4;
const int IO3 = 5;

// Assign GPIOs to LEDs.
const int LED1 = 6;
const int LED2 = 7;
const int LED3 = 8;

// Assign GPIOs to buzzer and motor.
const int BELL = 9;
const int MOTOR = 10;

void main() {
    // GPIO initialisation and mode setting.
    stdio_init_all();
    gpio_init(SW1);
    gpio_init(SW2);
    gpio_init(SW3);
    gpio_init(IO1);
    gpio_init(IO2);
    gpio_init(IO3);
    gpio_init(LED1);
    gpio_init(LED2);
    gpio_init(LED3);
    gpio_init(BELL);
    gpio_init(MOTOR);
    gpio_set_dir(SW1, GPIO_IN);
    gpio_set_dir(SW2, GPIO_IN);
    gpio_set_dir(SW3, GPIO_IN);
    gpio_set_dir(LED1, GPIO_OUT);
    gpio_set_dir(LED2, GPIO_OUT);
    gpio_set_dir(LED3, GPIO_OUT);
    gpio_set_dir(BELL, GPIO_OUT);
    gpio_set_dir(MOTOR, GPIO_OUT);
    if (IOMode == 0) {
        gpio_set_dir(IO1, GPIO_OUT);
        gpio_set_dir(IO2, GPIO_OUT);
        gpio_set_dir(IO3, GPIO_OUT);
    } else if (IOMode == 1) {
        gpio_set_dir(IO1, GPIO_IN);
        gpio_set_dir(IO2, GPIO_IN);
        gpio_set_dir(IO3, GPIO_IN);
    }
    userProgram();
    while (1) __wfi(); // Set MCU to sleep mode.
}

void userProgram() {
    // Write your code here!
}