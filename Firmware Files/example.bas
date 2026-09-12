10 REM SPDX-License-Identifier: CC0-1.0
20 REM Macro Microcontroller BASIC Example Program
30 REM Note: line numbers are automatically appended in the interpreter. Please remove the numbers before running the program!

40 REM Example 1: Hello world!
50 PRINT "hello world!"
60 END

70 REM Example 2: Activate buzzer and motor
80 GPIO BELL
90 GPIO MOTOR
100 END

110 REM Example 3: Random floating-point number
120 PRINT RND
130 END

140 REM Example 4: Assigning variables
150 LET X = 5
160 LSVAR
170 END

180 REM Example 5: Reading input
190 INPUT Name
200 PRINT "Hello, "
210 PRINT Name
220 END