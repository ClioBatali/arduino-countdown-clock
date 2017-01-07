// 2016/2017 spartronics countdown clock using teensyduino arduino add-on
#include <Adafruit_NeoPixel.h>
#include <Timer.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define pin            17  // the physical pin on the arduino connected to signal -- only 17 will work with the teensy, since no others output 5V (only 3.3V)
#define numOfPixels    315   // total "pixels" in the strand

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numOfPixels, pin, NEO_GRB + NEO_KHZ800);

Timer t;
int pixArray[7][45];        // 7 rows, 45 columns (y,x)
int timeRemaining = 3931200;   // total time in seconds remaining from upload (3931200 = seconds from noon Jan 7th to midnight on Feb 21, 2017)
int potNum;

int nowSec; 
int nowMin;
int nowHrs; 
int nowDays;


void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  for (int i = 0; i < numOfPixels; i++) {
    int y = i / 45;
    int x = i % 45;
    if (y % 2 == 1) {
      x = 44 - x;
    }
    pixArray[y][x] = i;
  }

  t.every(1000, checkTime);
}

void loop() {
  if (potNum > analogRead(0) / 4 + 3 || potNum < analogRead(0) / 4 - 3) {
    potNum = analogRead(0) / 4; // reads value from potentiometer connected to pin 1, then divides by four (instead of 1023 as max value, it becomes 255)
    
  }

  Serial.println(analogRead(0) / 4);
  Serial.println(potNum);

  if (timeRemaining >= 0) {
    t.update();
  }
}

void draw(int num, int x) {
  if (num == 0 || num == 8 || num == 6) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(pixArray[0][x], pixels.Color(potNum, potNum, potNum)); // Potentiometer-determined-ly-bright white color
    pixels.setPixelColor(pixArray[1][x], pixels.Color(potNum, potNum, potNum)); // Left vertical line
    pixels.setPixelColor(pixArray[2][x], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[3][x], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[4][x], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[5][x], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[6][x], pixels.Color(potNum, potNum, potNum));

    pixels.setPixelColor(pixArray[0][x + 3], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[3][x + 3], pixels.Color(potNum, potNum, potNum)); // Part of right vertical line
    pixels.setPixelColor(pixArray[4][x + 3], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[5][x + 3], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[6][x + 3], pixels.Color(potNum, potNum, potNum));

    if (num == 8 || num == 0) {
      pixels.setPixelColor(pixArray[1][x + 3], pixels.Color(potNum, potNum, potNum)); // The rest of the right vertical line
      pixels.setPixelColor(pixArray[2][x + 3], pixels.Color(potNum, potNum, potNum));
    }

    pixels.setPixelColor(pixArray[0][x + 1], pixels.Color(potNum, potNum, potNum)); // Top and bottom
    pixels.setPixelColor(pixArray[0][x + 2], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[6][x + 1], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[6][x + 2], pixels.Color(potNum, potNum, potNum));

    if (num == 8 || num == 6) {
      pixels.setPixelColor(pixArray[3][x + 1], pixels.Color(potNum, potNum, potNum)); // Middle just for 8 and 6
      pixels.setPixelColor(pixArray[3][x + 2], pixels.Color(potNum, potNum, potNum));
    }

  } else if (num == 1 || num == 7 || num == 9 || num == 4 || num == 3) {
    pixels.setPixelColor(pixArray[0][x + 3], pixels.Color(potNum, potNum, potNum)); // Right vertical line
    pixels.setPixelColor(pixArray[1][x + 3], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[2][x + 3], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[3][x + 3], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[4][x + 3], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[5][x + 3], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[6][x + 3], pixels.Color(potNum, potNum, potNum));

    if (num == 7 || num == 9 || num == 3) {
      pixels.setPixelColor(pixArray[0][x], pixels.Color(potNum, potNum, potNum)); // Top just for 7, 3, and 9
      pixels.setPixelColor(pixArray[0][x + 1], pixels.Color(potNum, potNum, potNum));
      pixels.setPixelColor(pixArray[0][x + 2], pixels.Color(potNum, potNum, potNum));
      if (num == 9 || num == 3) {
        pixels.setPixelColor(pixArray[6][x], pixels.Color(potNum, potNum, potNum)); // Bottom just for 3 and 9
        pixels.setPixelColor(pixArray[6][x + 1], pixels.Color(potNum, potNum, potNum));
        pixels.setPixelColor(pixArray[6][x + 2], pixels.Color(potNum, potNum, potNum));
      }
    }

    if (num == 4 || num == 9 || num == 3) {
      pixels.setPixelColor(pixArray[3][x], pixels.Color(potNum, potNum, potNum)); // Middle for 4, 9, and 3
      pixels.setPixelColor(pixArray[3][x + 1], pixels.Color(potNum, potNum, potNum));
      pixels.setPixelColor(pixArray[3][x + 2], pixels.Color(potNum, potNum, potNum));
      if (num == 4 || num == 9) {
        pixels.setPixelColor(pixArray[0][x], pixels.Color(potNum, potNum, potNum)); // Left top side for 9 and 4
        pixels.setPixelColor(pixArray[1][x], pixels.Color(potNum, potNum, potNum));
        pixels.setPixelColor(pixArray[2][x], pixels.Color(potNum, potNum, potNum));
      }
    }
  } else if (num == 2 || num == 5) {
    pixels.setPixelColor(pixArray[0][x], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[0][x + 1], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[0][x + 2], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[0][x + 3], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[3][x], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[3][x + 1], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[3][x + 2], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[3][x + 3], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[6][x], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[6][x + 1], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[6][x + 2], pixels.Color(potNum, potNum, potNum));
    pixels.setPixelColor(pixArray[6][x + 3], pixels.Color(potNum, potNum, potNum));
    if (num == 2) {
      pixels.setPixelColor(pixArray[1][x + 3], pixels.Color(potNum, potNum, potNum)); // Right top side for 2
      pixels.setPixelColor(pixArray[2][x + 3], pixels.Color(potNum, potNum, potNum));
      pixels.setPixelColor(pixArray[4][x], pixels.Color(potNum, potNum, potNum)); // Left bottom side for 2
      pixels.setPixelColor(pixArray[5][x], pixels.Color(potNum, potNum, potNum));
    } else if (num == 5) {
      pixels.setPixelColor(pixArray[1][x], pixels.Color(potNum, potNum, potNum)); // Left top side for 5
      pixels.setPixelColor(pixArray[2][x], pixels.Color(potNum, potNum, potNum));
      pixels.setPixelColor(pixArray[4][x + 3], pixels.Color(potNum, potNum, potNum)); // Right bottom side for 5
      pixels.setPixelColor(pixArray[5][x + 3], pixels.Color(potNum, potNum, potNum));
    }
  } else {
  }

}

void checkTime() {
  nowSec = timeRemaining % 60;
  nowMin = (timeRemaining / 60) % 60;
  nowHrs = (timeRemaining / 3600) % 24;
  nowDays = (timeRemaining / 86400);
  
  /* Serial.print(nowDays);
    Serial.print(nowHrs);
    Serial.print(nowMin);
    Serial.println(nowSec);
  */

  pixels.clear();

  draw(nowDays / 10, 0);
  draw(nowDays % 10, 5);
  draw(nowHrs / 10, 12);
  draw(nowHrs % 10, 17);
  draw(nowMin / 10, 24);
  draw(nowMin % 10, 29);
  draw(nowSec / 10, 36);
  draw(nowSec % 10, 41);

  if (timeRemaining % 2 == 1) {
    drawColon(10);
    drawColon(22);
    drawColon(34);
  }

  pixels.show(); // This sends the updated pixel color to the hardware

  timeRemaining -= 1; // Updates counter for what "now" is. One second has elapsed

}

void drawColon(int x) {
  pixels.setPixelColor(pixArray[2][x], pixels.Color(potNum, potNum, potNum));
  pixels.setPixelColor(pixArray[4][x], pixels.Color(potNum, potNum, potNum));
}

