// SPDX-License-Identifier: MIT
/*
Macro Microcontroller BASIC, Version 0.0.2.
PCB files for Macro Microcontroller 2 are available at
https://github.com/Nicholas1023/macro-microcontroller-2.

MIT License

Copyright (C) 2025-2026 Nicholas Lim.

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/sync.h"

void interpretermain();
void gpiocontrol();
void keygpiocontrol();

const int SW1 = 0;
const int SW2 = 1;
const int SW3 = 2;

const int IO1 = 3;
const int IO2 = 4;
const int IO3 = 5;

const int LED1 = 6;
const int LED2 = 7;
const int LED3 = 8;

const int BELL = 9;
const int MOTOR = 10;

extern char end;
char *variable[] = {"", ""};
char input[51];
char userinput[51];
char command[51];
int line_count = 0;

void main() {
    stdio_init_all();
    sleep_ms(1500);
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
    gpio_set_dir(IO1, GPIO_OUT);
    gpio_set_dir(IO2, GPIO_OUT);
    gpio_set_dir(IO3, GPIO_OUT);
    gpio_set_dir(LED1, GPIO_OUT);
    gpio_set_dir(LED2, GPIO_OUT);
    gpio_set_dir(LED3, GPIO_OUT);
    gpio_set_dir(BELL, GPIO_OUT);
    gpio_set_dir(MOTOR, GPIO_OUT);
    const int testVariable = 1;
    if (testVariable == 1) {
        gpio_put(LED1, 1);
        gpio_put(LED2, 1);
        gpio_put(LED3, 1);
        gpio_put(BELL, 1);
        sleep_ms(100);
        gpio_put(LED1, 0);
        gpio_put(LED2, 0);
        gpio_put(LED3, 0);
        gpio_put(BELL, 0);
        printf("Macro Microcontroller BASIC Version 0.0.2.\nCopyright (C) 2025-2026 Nicholas Lim.\n");
        volatile uint32_t stack_var;
        printf("%d bytes of RAM free.\n", (uint32_t)&stack_var - (uint32_t)&end);
        printf("Ready.\n");
        interpretermain();
    } else {
        printf("Error detected in RAM. Retrying in 5 seconds...\n");
        gpio_put(LED1, 1);
        gpio_put(LED2, 1);
        gpio_put(LED3, 1);
        gpio_put(BELL, 1);
        sleep_ms(100);
        gpio_put(LED1, 0);
        gpio_put(LED2, 0);
        gpio_put(LED3, 0);
        gpio_put(BELL, 0);
        sleep_ms(100);
        gpio_put(LED1, 1);
        gpio_put(LED2, 1);
        gpio_put(LED3, 1);
        gpio_put(BELL, 1);
        sleep_ms(100);
        gpio_put(LED1, 0);
        gpio_put(LED2, 0);
        gpio_put(LED3, 0);
        gpio_put(BELL, 0);
        sleep_ms(5000);
        main();
    }
}

void interpretermain() {
    while (true) {
        line_count++;
        printf("%d0 ", line_count);
        memset(input, 0, 51);
        fgets(input, 51, stdin);
        printf("%s", input);
        char *statement = strtok(input, " ");
        if (statement == NULL) continue;
        if (strcasecmp(statement, "PRINT") == 0) {
            statement = strtok(NULL, "\n");
            if (statement == NULL) continue;
            if (strcasecmp(statement, variable[0]) == 0) {
                statement = variable[1];
                if (*statement == '"') {
                    statement++;
                    char *close = strrchr(statement, '"');
                    *close = '\0';
                }
                printf("%s\n", statement);
            } else if (*statement == '"') {
                statement++;
                char *close = strrchr(statement, '"');
                *close = '\0';
                printf("%s\n", statement);
            } else if (strcasecmp(statement, "BELL") == 0) {
                gpio_put(BELL, 1);
                sleep_ms(100);
                gpio_put(BELL, 0);
                printf("BELL\n");
            } else if (strcasecmp(statement, "RND") == 0) {
                printf("%f\n", (float)rand() / (float)RAND_MAX);
            }

        } else if (strcasecmp(statement, "GPIO") == 0) {
            statement = strtok(NULL, "\n");
            if (statement == NULL) continue;
            if (strcasecmp(statement, "IO1") == 0) gpiocontrol(IO1);
            else if (strcasecmp(statement, "IO2") == 0) gpiocontrol(IO2);
            else if (strcasecmp(statement, "IO3") == 0) gpiocontrol(IO3);
            else if (strcasecmp(statement, "LED1") == 0) gpiocontrol(LED1);
            else if (strcasecmp(statement, "LED2") == 0) gpiocontrol(LED2);
            else if (strcasecmp(statement, "LED3") == 0) gpiocontrol(LED3);
            else if (strcasecmp(statement, "BELL") == 0) gpiocontrol(BELL);
            else if (strcasecmp(statement, "MOTOR") == 0) gpiocontrol(MOTOR);
            else printf("Error: Invalid GPIO pin number. Valid pins: IO1, IO2, IO3, LED1, LED2, LED3, BELL, MOTOR\n");

        } else if (strcasecmp(statement, "INPUT") == 0) {
            statement = strtok(NULL, "\n");
            if (statement == NULL) continue;
            printf("%s? ", statement);
            fgets(userinput, 51, stdin);
            printf("%s", userinput);
            char *value = strtok(userinput, "\n");
            variable[0] = strdup(statement);
            variable[1] = value;

        } else if (strcasecmp(statement, "LET") == 0) {
            statement = strtok(NULL, " ");
            if (statement == NULL) continue;
            variable[0] = strdup(statement);
            statement = strtok(NULL, " ");
            statement = strtok(NULL, "\n");
            if (strcasecmp(statement, "RND") == 0) {
                char rndtext[8];
                sprintf(rndtext, "%.6f", (float)rand() / (float)RAND_MAX);
                variable[1] = rndtext;
            } else {
                variable[1] = strdup(statement);
            }

        } else if (strcasecmp(statement, "END\n") == 0) {
            variable[0] = "";
            variable[1] = "";
            line_count = 0;
            printf("Ready.\n");
        } else if (strcasecmp(statement, "EXIT\n") == 0) {
            variable[0] = "";
            variable[1] = "";
            line_count = 0;
            while (1) __wfi();

        } else if (strcasecmp(statement, "KEY\n") == 0) {
            while (1) keygpiocontrol();
        
        } else if (strcasecmp(statement, "LSVAR\n") == 0) {
            if (variable[0] != "") {
                printf("Variable %s ", variable[0]);
                printf("with value %s\n", variable[1]);
            }
            
        } else { printf("Error: Invalid statement.\n"); }
    }
}

void gpiocontrol(int pin) {
    gpio_put(pin, 1);
    sleep_ms(1000);
    gpio_put(pin, 0);
}

void keygpiocontrol() {
    if (gpio_get(SW1) == 1) {
        while (true) {
            gpio_put(IO1, 1);
            if (gpio_get(SW1) == 0) {
                gpio_put(IO1, 0);
                break;
            }
        }
    } else if (gpio_get(SW2) == 1) {
        while (true) {
            gpio_put(IO2, 1);
            if (gpio_get(SW2) == 0) {
                gpio_put(IO2, 0);
                break;
            }
        }
    } else if (gpio_get(SW3) == 1) {
        while (true) {
            gpio_put(IO3, 1);
            if (gpio_get(SW3) == 0) {
                gpio_put(IO3, 0);
                break;
            }
        }
    }
}