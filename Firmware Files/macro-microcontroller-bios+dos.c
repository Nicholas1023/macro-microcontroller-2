// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2025-2026 Nicholas Lim <nicholas_lim@bbsshack.club>
// Macro Microcontroller BIOS + Macro Microcontroller DOS Version 0.0.1.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/sync.h"
#include "pico/bootrom.h"
#include "pico/unique_id.h"
#include "hardware/clocks.h"
#include "hardware/flash.h"

extern char __flash_binary_end;

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
bool lastSW1 = false;
bool lastSW2 = false;

char *variable[] = {"", ""};
char input[51];
char DOS_input[51];
char user_input[51];
char command[51];
int line_count = 0;

/* Change the following to true to add your own "OS", or false to boot to Macro
Microcontroller BASIC by default (No bootable media found). */
bool userconfig = true;

void interpreter();
void blink();
void gpio_control();
void DOS();

int main() {
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
    gpio_set_dir(IO1, GPIO_OUT);
    gpio_set_dir(IO2, GPIO_OUT);
    gpio_set_dir(IO3, GPIO_OUT);
    gpio_pull_up(SW1);
    gpio_pull_up(SW2);
    gpio_pull_up(SW3);
    sleep_ms(4000);
    printf(" _  _\n");
    printf("| \\/ | Macro Microcontroller BIOS Version 0.0.1.\n");
    printf("|_\\/_| Copyright (C) 2025-2026 Nicholas Lim.\n\n");
    printf("Device: Macro Microcontroller 2 (RP2040 @ %.0fMHz)\n", clock_get_hz(clk_sys)/1e+6);
    pico_unique_board_id_t id;
    pico_get_unique_board_id(&id);
    printf("Serial Number: ");
    for (int i = 0; i < PICO_UNIQUE_BOARD_ID_SIZE_BYTES; i++) {
        printf("%02X", id.id[i]);
    }
    volatile uint32_t stack_var;
    printf("\nRAM Free: %dK", ((uint32_t)&stack_var - (uint32_t)&end)/1024);
    int memTest = 1;
    if (memTest != 1) {
        gpio_put(BELL, 1);
        sleep_ms(100);
        gpio_put(BELL, 0);
        sleep_ms(100);
        gpio_put(BELL, 1);
        sleep_ms(100);
        gpio_put(BELL, 0);
        printf(" Error\nBIOS POST Failed. Restart your device to try again.\n");
        while (1) __wfi();
    }
    printf(" OK\nSerial Status: ");
    if (stdio_usb_connected()) {
        printf("Connected\n\n");
    } else {
        printf("Not connected\n\n");
    }
    gpio_put(BELL, 1);
    sleep_ms(100);
    gpio_put(BELL, 0);
    printf("Press SW1 to enter Macro Microcontroller BASIC.\nPress SW2 to enter BOOTSEL mode.\n\n");
    uint32_t startup = to_ms_since_boot(get_absolute_time());
    while (1) {
        bool currentSW1 = gpio_get(SW1);
        bool currentSW2 = gpio_get(SW2);
        uint32_t now = to_ms_since_boot(get_absolute_time());
        if (!currentSW1 && lastSW1 && now - startup <= 2000) {
            sleep_ms(40);
            if (gpio_get(SW1)) {
                interpreter();
            }
        } if (!currentSW2 && lastSW2 && now - startup <= 2000) {
            sleep_ms(40);
            if (gpio_get(SW2)) {
                printf("Entering BOOTSEL mode...\n");
                reset_usb_boot(0, 0);
            }
        } else if (now - startup > 1000) {
            break;
        }
        lastSW1 = currentSW1;
        lastSW2 = currentSW2;
    }
    printf("Booting system... ");
    sleep_ms(500);
    if (!userconfig) {
        gpio_put(BELL, 1);
        sleep_ms(500);
        gpio_put(BELL, 0);
        printf("No bootable media found.\n");
        interpreter();
    } else {
        printf("\n\n");
        DOS();
    }
    printf("Stopping all system processes... You may turn off your device now.");
    while (1) __wfi();
}

void DOS() {
    printf("Macro Microcontroller Disk Operating System Version 0.0.1.\nCopyright (C) 2026 Nicholas Lim.\n");
    while (true) {;
        printf("Drive A> ");
        memset(DOS_input, 0, 51);
        fgets(DOS_input, 51, stdin);
        printf("%s", DOS_input);
        char *DOS_statement = strtok(DOS_input, " ");
        if (DOS_statement == NULL) continue;
        if (strcasecmp(DOS_statement, "ECHO") == 0) {
            DOS_statement = strtok(NULL, "\n");
            if (DOS_statement == NULL) continue;
            printf("%s\n", DOS_statement);
        } else if (strcasecmp(DOS_statement, "HELP\n") == 0 || strcasecmp(DOS_statement, "HELP.PROG\n") == 0) {
            printf("Macro Microcontroller DOS Help Guide\nAvailable commands:\n- HELP: Launches the help guide.\n- ECHO: Echoes text.\n- LS: Show directory listing.\n- SYSTEM: Starts another Macro Microcontroller DOS console.\n- EXIT: Stops all processes for power off.\n");
        } else if (strcasecmp(DOS_statement, "LS\n") == 0) {
            uint32_t free_flash = (16 * 1024 * 1024) - (((uintptr_t)&__flash_binary_end) - XIP_BASE);
            printf("Storage: %uMB free\nDirectory listing of Drive A:\nName           Last modified\n─────────────────────────────────\nSYSTEM.PROG    08-15-2026 20:37\nHELP.PROG      08-16-2026 17:02\n─────────────────────────────────\n", free_flash / 1024 / 1024);
        } else if (strcasecmp(DOS_statement, "SYSTEM\n") == 0 || strcasecmp(DOS_statement, "SYSTEM.PROG\n") == 0) {
            DOS();
        } else if (strcasecmp(DOS_statement, "EXIT\n") == 0) {
            return;
        } else {
            printf("Command or file does not exist.\n");
        }
    }
}

void blink(int pin) {
    gpio_put(pin, 1);
    sleep_ms(1000);
    gpio_put(pin, 0);
}

void interpreter() {
    printf("Macro Microcontroller BASIC Version 0.0.3.\n");
    volatile uint32_t stack_var;
    printf("%d bytes of RAM free.\n", (uint32_t)&stack_var - (uint32_t)&end);
    printf("Ready.\n");
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
            if (strcasecmp(statement, "IO1") == 0) blink(IO1);
            else if (strcasecmp(statement, "IO2") == 0) blink(IO2);
            else if (strcasecmp(statement, "IO3") == 0) blink(IO3);
            else if (strcasecmp(statement, "LED1") == 0) blink(LED1);
            else if (strcasecmp(statement, "LED2") == 0) blink(LED2);
            else if (strcasecmp(statement, "LED3") == 0) blink(LED3);
            else if (strcasecmp(statement, "BELL") == 0) blink(BELL);
            else if (strcasecmp(statement, "MOTOR") == 0) blink(MOTOR);
            else printf("Error: Invalid GPIO pin number. Valid pins: IO1, IO2, IO3, LED1, LED2, LED3, BELL, MOTOR\n");

        } else if (strcasecmp(statement, "INPUT") == 0) {
            statement = strtok(NULL, "\n");
            if (statement == NULL) continue;
            printf("%s? ", statement);
            fgets(user_input, 51, stdin);
            printf("%s", user_input);
            char *value = strtok(user_input, "\n");
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
            printf("\n");
            return;
        
        } else if (strcasecmp(statement, "LSVAR\n") == 0) {
            if (variable[0] != "") {
                printf("Variable %s ", variable[0]);
                printf("with value %s\n", variable[1]);
            }
            
        } else if (strcasecmp(statement, "REM") != 0) {
            printf("Error: Invalid statement.\n");
        }
    }
}
