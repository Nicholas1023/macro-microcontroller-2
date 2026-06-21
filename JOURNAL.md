### Devlogs from <a href="https://stardance.hackclub.com/projects/21502">https://stardance.hackclub.com/projects/21502</a>

## Finished the enclosure and organised the repository!
### 20 June 2026, 3h 1m 11s
Today, I have completed the 3D case for Macro Controller 2 and did some minor bug fixes for the BASIC Interpreter. I needed to reassign the GPIO pins from the first revision of the board.

Although the interpreter is currently still basic, it supports 4 BASIC statements and 4 custom statements for controls.

### What’s new in this devlog
- Text and key labels for enclosure with cover
- Organised repository
- New `KEY` statement for hardware GPIO control

<b><a href="Assets/firmware-demo.mp4">Firmware demonstration video</a></b>

<image src="Assets/macro-microcontroller-2.png">
<image src="Assets/enclosure-image.png">

## Halfway through my PCB's case!
### 19 June 2026, 2h 4m 14s

### What I've done in this devlog
For the first-half, I added silkscreen text to the PCB for the IO components (GPIO Pins, Keyboard switches, LEDs...). Next, I moved on to designing the enclosure. It took a while for me to get used to using a new app to design it.

### Modifications to the PCB
- Added screw mounting pads for easier mounting.
- LEDs moved closer to each other for space to add silkscreen designs.

### Problems I've faced
The screw holes were not appearing during the first few attempts, but it worked in the end when I placed it manually, instead of using the move function.

Creating the cutout for the USB connector took me about 15 mins as I needed to measure the length and clearance needed for a micro-USB plug and create another sketch before extruding it as a cutout.

### What I'll be working on next
Next, I'll be continuing with the enclosure design, adding a cover with a keyboard plate, and finally moving on to the BASIC interpreter firmware for it!

<image src="Assets/macro-microcontroller-2.png">
<image src="Assets/enclosure 2026-06-19.png">

## Finished routing my microcontroller board!
### 19 June 2026, 2h 1m 39s

Did most of the routing for the MCU and macropad segment today, but I might need to do some rewiring for the flash memory as the trace length for `SD0` and `SD2` are very different (5.57 & 13.2 mm).

### What has been added since the last devlog
- Added power LED
- Added pin headers for GPIO and power
- Added barrel jack in case if the DC motor drains too much power

### What I'll be doing next
Next, I'll be adding more silkscreen text, and maybe design an icon for my macropad + microcontroller board. I'll also be creating a custom enclosure for my device!

<image src="Assets/PCB 2026-06-19.png">

## Finished the schematics and a little of the BASIC Interpreter for my microcontroller board! 
### 18 June 2026, 2h 22m 57s

### What I did today
- Redid the old schematics by adding custom RP2040 circuit instead of a using a dev board.
- Added new GPIO devices such as DC motor and a buzzer. (for the BASIC interpreter)
- Started on `PRINT`, `LET` and `INPUT` for the interpreter.

### What I'll be doing next
Next, I will be focusing on the BASIC interpreter firmware, working on variable assignment and math operations and testing it on a real pico board! Also, I will be starting on the layout and BOM as I have completed the schematics!

<image src="Assets/schematics 2026-06-18.png">
