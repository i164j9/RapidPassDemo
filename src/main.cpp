#include "Adafruit_NeoPixel-master/Adafruit_NeoPixel.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

/* the case for this code:
https://www.thingiverse.com/thing:3695499

https://www.adafruit.com/product/2853 - NeoPixel ring - 12 smd5050 RGBW leds
https://www.adafruit.com/product/2860 - neoPixel jewel - 7 smd5050 RGBW leds
https://www.adafruit.com/product/1938 - diffused 5mm tht leds
https://www.adafruit.com/product/1769 - connector
https://www.adafruit.com/product/1304 - usb lipo charger
https://www.adafruit.com/product/1903 - boost converter
https://www.adafruit.com/product/1578 - 3.7v lipo
https://www.adafruit.com/product/1501 - trinket 5v
*/

// true if you want the conduit solid
// false if you want them to flash
#define solidConduit true

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__)
  //this will compile for Arduino UNO, Pro and older boards
  #define RING_PIN 6
  #define CONDUIT_PIN 7
  #define METER_PIN 8
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  //this will compile for Arduino Mega
  #define RING_PIN 8
  #define CONDUIT_PIN 9
  #define METER_PIN 10
#elif defined ESP32
  // for the ESP-WROVER 32
  // Output for ESP32. Pins 6-11 are connected to SPI flash.
  #define RING_PIN 18
  #define CONDUIT_PIN 19
  #define METER_PIN 23
#elif defined __AVR_ATtiny85__
// adafruit trinket
  #define RING_PIN 0
  #define CONDUIT_PIN 1
  #define METER_PIN 2
#endif

#define NUM_CONDUIT_LEDS  8
#define NUM_RING_LEDS 21
#define NUM_METER_LEDS  3

// Parameter 1 = number of pixels in ring
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUM_RING_LEDS, RING_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel conduitLeds = Adafruit_NeoPixel(NUM_CONDUIT_LEDS, CONDUIT_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel meter = Adafruit_NeoPixel(NUM_METER_LEDS, METER_PIN, NEO_GRB + NEO_KHZ800);

// 10 sec. wait time between pattern changes
unsigned long interval = 10000;

// millis() returns an unsigned long.
unsigned long previousMillis = 0;

// Assigned color for conduit flash
uint32_t color = 0x0099FF;

// delay for colorWipe
uint8_t dly = 5;

// time between steps in the pattern
unsigned long patternInterval = 5;

// for millis() when last update occoured
unsigned long lastUpdate = 0;                                    

// speed for each pattern
unsigned long intervals[5] = {20};

void colorWipe(uint32_t c, uint8_t wait);
void pokeball();
void greatball();
void ultraball();
void theaterChaseRainbow(uint8_t);
void rainbowCycle(uint8_t);
void wipe();

uint32_t Wheel(byte);

void changePattern(int pat) {
 // select the next pattern
  switch (pat)
  {
  case 0:
    colorWipe(ring.Color(0, 255, 0, 0),dly); // Red
    break;
  case 1:
    pokeball();
    break;
  case 2:
    colorWipe(ring.Color(0, 255, 0, 0),dly); // Red
    break;
  case 3:
    greatball();
    break;
  case 4:
    colorWipe(ring.Color(0, 255, 0, 0),dly); // Red
    break;
  case 5:
    ultraball();
    break;
  case 6:
    rainbowCycle(1);
    break;
  case 7:
    colorWipe(ring.Color(0, 255, 0, 0),dly); // Red
    break;
  case 8:
    theaterChaseRainbow(60);
    break;
  }
}


// Pokeball pattern for rings
void pokeball() {
  static int RGBWvalues[19][5]={
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
  static int RGBWvalues[19][5]={
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
  static int RGBWvalues[19][5]={
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


//Randomly flicker all 8 conduit port lights one at a time.
void conduitFlicker() {
    uint8_t  i;
    i = random(128);
    conduitLeds.setPixelColor(i, color);
    conduitLeds.show();
    conduitLeds.setPixelColor(i, 0);
}


// Solid color conduit
void conduitSolid() {
  for(int i = 0; i < 8; i++){
    conduitLeds.setPixelColor(i, color);
  }
  conduitLeds.show();
}


// Power meter
void power() {
  meter.setPixelColor(0, 0, 255, 0, 0);
  meter.setPixelColor(1, 255, 0, 0, 0);
  meter.setPixelColor(2, 255, 0, 0, 0);
  meter.show();
}


// RainbowCycle
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  // 5 cycles of all colors on wheel
  for(j=0; j<256*5; j++) { 
    for(i=0; i< ring.numPixels(); i++) {
      ring.setPixelColor(i, Wheel(((i * 256 / ring.numPixels()) + j) & 255));
    }
    ring.show();
    delay(wait);
  }
}


// TheaterChase
//  modified from Adafruit example to make it a state machine
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < ring.numPixels(); i+=3) {
        ring.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      ring.show();
      delay(wait);
      for (uint16_t i=0; i < ring.numPixels(); i+=3) {
        ring.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


// ColorWipe
// c - color, wait - delay in ms
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<ring.numPixels(); i++) {
    ring.setPixelColor(i, c);
    ring.show();
    delay(wait);
  }
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
    
   meter.begin();
   meter.setBrightness(75);
   meter.show(); // Initialize all pixels to 'off'
}

static int pattern = 0, lastReading;

void loop() {
  #if solidConduit == true
  // sets conduit led color to 0x0099FF(purple~ish)
    conduitSolid();
  #else
    conduitFlicker();
  #endif
  if ((millis() - previousMillis) >= interval) {
    previousMillis = millis();
    pattern++;
    
    // wrap around if too big
    if (pattern > 8) {
      pattern = 0;
    }

    // set speed for this pattern
    patternInterval = intervals[pattern];
    
    // reset leds to black/off
    wipe();
  }
  
  if ((millis() - lastUpdate) > patternInterval)
    changePattern(pattern);
    //power();
}
