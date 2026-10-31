# Talking-Tars
A simple model of "Tars" that talks and has eyes that move

Read Me:
This project is a simple robot that speaks and has eyes
The materials required are:
Arduino (preferably the regular Nano)
0.96 oled display (SSD1306 I2C OLED)
speaker module
DFPlayer module
Micro SD card (preferably below 32gb, its okay if more you just have to format it in a lower capacity)
Maybe a good power supply (I used a 2s li ion charger board + a buck converter set to 5v)
The needed libraries are U8g2 and DFRobotDFPlayerMini
The sound should be saved either in .mp3 or .wav, and the card should be formatted in FAT32, I used a text to speech converesion from Eleven Labs, I attatched the .mp3 file too. The speech is based on the theme given to me by my school so it is about India.
There might be some problems in the first boots, just reset the whole thing and it will work just fine
Adding a resistor to the RX pins might be helpful 

## Wiring by Claude

| Part | Pin | Arduino Nano |
|---|---|---|
| OLED (0.96" I2C) | VCC | 5V (or 3.3V, depends on your module) |
| OLED | GND | GND |
| OLED | SDA | A4 |
| OLED | SCL | A5 |
| DFPlayer Mini | VCC | 5V |
| DFPlayer Mini | GND | GND |
| DFPlayer Mini | TX | D10 |
| DFPlayer Mini | RX | D11, through a 1k resistor |
| DFPlayer Mini | SPK_1, SPK_2 | Speaker (8 ohm, 0.5W) |
