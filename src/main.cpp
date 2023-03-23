#include "Adafruit_NeoPixel-master/Adafruit_NeoPixel.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 5
#define PIN1 4
#define PIN2 2

// Parameter 1 = number of pixels in ring
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel ring = Adafruit_NeoPixel(21, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel conduitLeds = Adafruit_NeoPixel(8, PIN1, NEO_GRB + NEO_KHZ800);
// Adafruit_NeoPixel meter = Adafruit_NeoPixel(3, PIN2, NEO_RGBW + NEO_KHZ800);

// 10 sec. wait time between pattern changes
unsigned long interval = 5000;
// millis() returns an unsigned long.
unsigned long previousMillis = 0;

// Assigned color for conduit flash
uint32_t color = 0x0099FF;

// time between steps in the pattern
unsigned long patternInterval = 5;
// for millis() when last update occoured
unsigned long lastUpdate = 0;                                    
// speed for each pattern
unsigned long intervals[] = {10};

void colorWipe(uint32_t c);
void pokeball();
void greatball();
void ultraball();
void theaterChaseRainbow(uint8_t wait);
void rainbowCycle();
void wipe();

uint32_t Wheel(byte WheelPos);

void changePattern(int pat) {
 // selecting the next pattern
  switch (pat)
  {
  case 0:
    colorWipe(ring.Color(255, 0, 0, 0)); // Red
    break;
  case 1:
    pokeball();
    break;
  case 2:
    colorWipe(ring.Color(0, 255, 0, 0)); // Red
    break;
  case 3:
    greatball();
    break;
  case 4:
    colorWipe(ring.Color(0, 0, 255, 0)); // Red
    break;
  case 5:
    ultraball(); // hangs here
    break;
  case 6:
    rainbowCycle();
    break;
  case 7:
    colorWipe(ring.Color(0, 255, 0, 0)); // Red
    break;
  case 8:
    theaterChaseRainbow(50);
    break;
  }
}

// Pokeball pattern for rings
void pokeball() {
  int RGBWvalues[19][5]={
    {0, 0, 0, 0, 255},{1, 0, 0, 0, 255},{2, 0, 0, 0, 255},{3, 0, 0, 0, 255},
    {4, 0, 255, 0, 0},{5, 0, 255, 0, 0},{6, 0, 255, 0, 0},{7, 0, 0, 0, 255},
    {8, 0, 0, 0, 255},{9, 0, 0, 0, 255},{10, 0, 0, 0, 255},{11, 0, 0, 0, 255},
    {12, 0, 0, 0, 255},{13, 0, 255, 0, 0},{14, 0, 255, 0, 0},{15, 0, 255, 0, 0},
    {16, 0, 255, 0, 0},{17, 0, 255, 0, 0},{18, 0, 255, 0, 0}};
  
  for (int i = 0; i < (sizeof(RGBWvalues)/sizeof(RGBWvalues[0])); i++) {
    ring.setPixelColor(RGBWvalues[i][0],RGBWvalues[i][1],RGBWvalues[i][2],RGBWvalues[i][3],
    RGBWvalues[i][4]);
  }
  ring.show();
}

// Greatball pattern for rings
void greatball() {
  int RGBWvalues[19][5]={
    {0, 0, 0, 0, 255},{1, 0, 0, 0, 255},{2, 0, 0, 0, 255},{3, 0, 0, 0, 255},
    {4, 0, 0, 255, 0},{5, 0, 0, 255, 0},{6, 0, 0, 255, 0},{7, 0, 0, 0, 255},
    {8, 0, 0, 0, 255},{9, 0, 0, 0, 255},{10, 0, 0, 0, 255},{11, 0, 0, 0, 255},
    {12, 0, 0, 0, 255},{13, 0, 0, 255, 0},{14, 0, 255, 0, 0},{15, 0, 0, 255, 0},
    {16, 0, 0, 255, 0},{17, 0, 255, 0, 0},{18, 0, 0, 155, 0}};
  for (int i = 0; i < (sizeof(RGBWvalues)/sizeof(RGBWvalues[0])); i++) {
    ring.setPixelColor(RGBWvalues[i][0],RGBWvalues[i][1],RGBWvalues[i][2],RGBWvalues[i][3],
    RGBWvalues[i][4]);
  }
  ring.show();
}

// Ultraball pattern for rings
void ultraball() {
  int RGBWvalues[19][5]={
    {0, 0, 0, 0, 255},{1, 0, 0, 0, 255},{2, 0, 0, 0, 255},{3, 0, 0, 0, 255},
    {4, 100, 255, 0, 0},{5, 0, 0, 0, 0},{6, 100, 255, 0, 0},{7, 0, 0, 0, 255},
    {8, 0, 0, 0, 255},{9, 0, 0, 0, 255},{10, 0, 0, 0, 255},{11, 0, 0, 0, 255},
    {12, 0, 0, 0, 255},{13, 0, 0, 0, 0},{14, 100, 255, 0, 0},{15, 100, 255, 0, 0},
    {16, 100, 255, 0, 0},{17, 100, 255, 0, 0},{18, 0, 0, 0, 0}};
  for (int i = 0; i < (sizeof(RGBWvalues)/sizeof(RGBWvalues[0])); i++) {
    ring.setPixelColor(RGBWvalues[i][0],RGBWvalues[i][1],RGBWvalues[i][2],RGBWvalues[i][3],
    RGBWvalues[i][4]);
  }
  ring.show();
}

// Randomly flicker all 8 conduit port lights one at a time.
// void conduit1() {
//     uint8_t  i;
//     i = random(128);
//     conduitLeds.setPixelColor(i, color);
//     conduitLeds.show();
//     conduitLeds.setPixelColor(i, 0);
// }

// Solid color conduit
void conduit2() {
  for(int i = 0; i < 8; i++){
    conduitLeds.setPixelColor(i, color);
  }
  conduitLeds.show();
}

// Power meter
// void power() {
//   meter.setPixelColor(0, 0, 255, 0, 0);
//   meter.setPixelColor(1, 255, 0, 0, 0);
//   meter.setPixelColor(2, 255, 0, 0, 0);
//   meter.show();
// }

// RainbowCycle
//  modified from Adafruit example to make it a state machine
void rainbowCycle() {
  static uint16_t j = 0;
  for (int i = 0; i < ring.numPixels(); i++)
  {
    ring.setPixelColor(i, Wheel(((i * 256 / ring.numPixels()) + j) & 255));
  }
  ring.show();
  j++;
  if (j >= 256 * 5)
    j = 0;
  lastUpdate = millis(); // time for next change to the display
}

// TheaterChase
//  modified from Adafruit example to make it a state machine
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < ring.numPixels(); i=i+3) {
        ring.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      ring.show();

      delay(wait);

      for (uint16_t i=0; i < ring.numPixels(); i=i+3) {
        ring.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// ColorWipe
//  modified from Adafruit example to make it a state machine
void colorWipe(uint32_t c) {
  static int i = 0;
  ring.setPixelColor(i, c);
  ring.show();
  i++;
  if (i >= ring.numPixels())
  {
    i = 0;
  }
  lastUpdate = millis(); // time for next change to the display
}

// clear all LEDs
void wipe() {
  for (int i = 0; i < ring.numPixels(); i++)
  {
    ring.setPixelColor(i, ring.Color(0, 0, 0));
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85)
  {
    return conduitLeds.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170)
  {
    WheelPos -= 85;
    return conduitLeds.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return conduitLeds.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined(__AVR_ATtiny85__)
    if (F_CPU == 16000000)
      clock_prescale_set(clock_div_1);
  #endif

  //Serial.begin(115200);
  // End of trinket special code
  delay(3000);
  // Configure NeoPixel pin for output.
  ring.begin();
  // Adjust output brightness. Does not immediately affect what's currently
  // displayed on the LEDs. The next call to show() will refresh the LEDs
  // at this level.
  ring.setBrightness(50);
  // Initialize all pixels to 'off'
  ring.show(); 

  // Configure NeoPixel pin for output.
  conduitLeds.begin();
  // Adjust output brightness. Does not immediately affect what's currently
  // displayed on the LEDs. The next call to show() will refresh the LEDs
  // at this level.
  conduitLeds.setBrightness(255);
  // Initialize all pixels to 'off'
  conduitLeds.show();
    
  //  meter.begin();
  //  meter.setBrightness(75);
  //  meter.show(); // Initialize all pixels to 'off'
}

static int pattern = 0, lastReading;

void loop() {
  // conduit1();
  // sets conduit led color to 0x0099FF(purple~ish)
  conduit2();
 
  if ((millis() - previousMillis) >= interval) {
    previousMillis = millis();
    pattern++;
    
    // wrap around if too big
    if (pattern > 8) {
      pattern = 0;
    }

    // set speed for this pattern
    patternInterval = intervals[pattern];
    
    // clear out the buffer
    wipe();
  }
  
  if ((millis() - lastUpdate) > patternInterval)
    changePattern(pattern);
  //  power();
}
