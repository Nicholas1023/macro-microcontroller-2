REM SPDX-License-Identifier: CC0-1.0
REM Macro Microcontroller BASIC Example Program
REM Note: line numbers are automatically appended, hence there is no need to add them.

REM Example 1: Hello world!
PRINT "hello world!"
END

REM Example 2: Activate buzzer and motor
GPIO BELL
GPIO MOTOR
END

REM Example 3: Random floating-point number
PRINT RND
END

REM Example 4: Assigning variables
LET X = 5
LSVAR
END

REM Example 5: Reading input
INPUT Name
PRINT "Hello, "
PRINT Name
END