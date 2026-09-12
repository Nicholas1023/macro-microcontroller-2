10 REM SPDX-License-Identifier: CC0-1.0
20 REM Macro Microcontroller BASIC Example Program
30 REM Note: line numbers are automatically appended in the interpreter.
40 REM Please remove the numbers before running the program!

50 REM Example 1: Hello world!
60 PRINT "hello world!"
70 END

80 REM Example 2: Activate buzzer and motor
90 GPIO BELL
100 GPIO MOTOR
110 END

120 REM Example 3: Random floating-point number
130 PRINT RND
140 END

150 REM Example 4: Assigning variables
160 LET X = 5
170 LSVAR
180 END

190 REM Example 5: Reading input
200 INPUT Name
210 PRINT "Hello, "
220 PRINT Name
230 END