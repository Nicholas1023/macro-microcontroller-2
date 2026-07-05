REM "Macro Microcontroller BASIC Example Programs"
REM "Note: line numbers are automatically appended, hence there is no need to add line numbers."
REM "This example program (example.bas) is released into the public domain."

REM "Example 1: Hello world!"
PRINT "hello world!"
END

REM "Example 2: Turning on buzzer"
GPIO BELL
END

REM "Example 3: Random floating-point number"
PRINT RND
END

REM "Example 4: Assigning variables"
LET X = 5
LSVAR
END

REM "Example 5: Reading input"
INPUT Name
PRINT "Hello, "
PRINT Name
END