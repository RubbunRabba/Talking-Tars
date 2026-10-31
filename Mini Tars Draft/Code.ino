// My exhibition project draft
// Most of the code is from claude, I have ran the code on my Arduino Nano and it 
// works fine, I just added the DFPlayer Mini code to play a sound when the eyes blink.
// The sound file should be named 0001.mp3 and placed in the root of the SD card in 
// the DFPlayer Mini. It was originally made for my science exhibition project and
// it carried out smoothly in the exhibition so you can trust it, the thing is that
// the volume of the speakers aren't that loud so I recomend cracking it a bit higher
// but not too much because it will distort the sound. I have set the volume to 20 
// but you can change it to your liking and your environment.
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

SoftwareSerial dfSerial(10, 11);   // Nano RX (from DF TX), Nano TX (to DF RX)
DFRobotDFPlayerMini player;

const int EYE_W = 36, EYE_H = 36, EYE_R = 10;
const int LEFT_X = 20, RIGHT_X = 72, EYE_Y = 14;

int offX = 0, offY = 0;
int targetX = 0, targetY = 0;
unsigned long nextBlink, nextLook;

void drawEyes(int ox, int oy, int h) {
  int y = EYE_Y + oy + (EYE_H - h) / 2;
  int r = min(EYE_R, h / 2);
  u8g2.firstPage();
  do {
    u8g2.drawRBox(LEFT_X + ox,  y, EYE_W, h, r);
    u8g2.drawRBox(RIGHT_X + ox, y, EYE_W, h, r);
  } while (u8g2.nextPage());
}

void blink() {
  for (int h = EYE_H; h >= 4; h -= 8) drawEyes(offX, offY, h);
  for (int h = 4; h <= EYE_H; h += 8)  drawEyes(offX, offY, h);
}

void setup() {
  u8g2.begin();
  u8g2.setBusClock(400000);
  randomSeed(analogRead(A0));

  // show the eyes right away while the DFPlayer boots
  drawEyes(0, 0, EYE_H);

  dfSerial.begin(9600);
  delay(1000);                                  // DFPlayer needs a moment after power-up
  if (player.begin(dfSerial, false, true)) {    // no ACK wait, reset module
    player.volume(20);                          // 0-30
    player.loop(1);                             // repeat 0001.mp3 forever
    // player.play(1);                          // use this instead to play it only once
  }
  // if begin() fails (bad wiring / no SD) the eyes keep running anyway

  nextBlink = millis() + 2000;
  nextLook  = millis() + 1000;
}

void loop() {
  unsigned long now = millis();

  if (now > nextLook) {
    targetX = random(-12, 13);
    targetY = random(-8, 9);
    nextLook = now + random(800, 3000);
  }

  if (offX < targetX) offX++; else if (offX > targetX) offX--;
  if (offY < targetY) offY++; else if (offY > targetY) offY--;

  if (now > nextBlink) {
    blink();
    nextBlink = now + random(2000, 6000);
  }

  drawEyes(offX, offY, EYE_H);
}