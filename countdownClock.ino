// 2016/2017 spartronics countdown clock using teensyduino arduino addon 
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define pin            17  // the physical pin on the arduino connected to signal -- only 17 will work with the teensy, since no others output 5V (only 3.3V)

#define numOfPixels    15   // total "pixels" in the strand

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numOfPixels, pin, NEO_GRB + NEO_KHZ800);

int timeRemaining = 3931200;   // total time in seconds remaining from upload (3931200 = seconds from noon Jan 7th to midnight on Feb 21, 2017)

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  int nowSec = timeRemaining % 60;
  int nowMin = (timeRemaining / 60) % 60;
  int nowHrs = (timeRemaining / 3600) % 24;
  int nowDays = (timeRemaining / 86400);
   
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one. This loop checks all LEDs
  for(int i=0;i<numOfPixels;i++){

    if((i+1)==(count)){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(150,150,150)); // Moderately bright white color

      pixels.show(); // This sends the updated pixel color to the hardware
    }
  }
  delay(1000); // Delay for one second (in milliseconds)
  count-=1; // Updates counter for what "now" is. One second has elapsed
}
