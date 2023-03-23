#include "Adafruit_NeoPixel-master/Adafruit_NeoPixel.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 0
#define PIN1 1
// #define PIN2 2

// Parameter 1 = number of pixels in ring
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel ring = Adafruit_NeoPixel(21, PIN, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN1, NEO_GRB + NEO_KHZ800);
// Adafruit_NeoPixel meter = Adafruit_NeoPixel(3, PIN2, NEO_RGBW + NEO_KHZ800);

// 10 sec. frequency
unsigned long interval = 10000;   // the time we need to wait
unsigned long previousMillis = 0; // millis() returns an unsigned long.

// Assigned color for conduit flash
uint32_t color = 0x0099FF;

unsigned long patternInterval = 20;                              // time between steps in the pattern
unsigned long lastUpdate = 0;                                    // for millis() when last update occoured
unsigned long intervals[] = {20, 20, 20, 20, 20, 20, 20, 20, 2}; // speed for each pattern

void colorWipe(uint32_t c);
void pokeball();
void greatball();
void ultraball();
void theaterChaseRainbow();
void rainbowCycle();
uint32_t Wheel(byte WheelPos);

void updatePattern(int pat)
{ // call the pattern currently being created
  switch (pat)
  {
  case 0:
    colorWipe(ring.Color(0, 255, 0, 0)); // Red
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
    colorWipe(ring.Color(0, 255, 0, 0)); // Red
    break;
  case 5:
    ultraball();
    break;
  case 6:
    theaterChaseRainbow();
    break;
  case 7:
    colorWipe(ring.Color(0, 255, 0, 0)); // Red
    break;
  case 8:
    rainbowCycle();
    break;
  }
}

// Pokeball pattern for rings
void pokeball()
{
  ring.setPixelColor(0, 0, 0, 0, 255);
  ring.setPixelColor(1, 0, 0, 0, 255);
  ring.setPixelColor(2, 0, 0, 0, 255);
  ring.setPixelColor(3, 0, 0, 0, 255);
  ring.setPixelColor(4, 0, 255, 0, 0);
  ring.setPixelColor(5, 0, 255, 0, 0);
  ring.setPixelColor(6, 0, 255, 0, 0);
  ring.setPixelColor(7, 0, 0, 0, 255);
  ring.setPixelColor(8, 0, 0, 0, 255);
  ring.setPixelColor(9, 0, 0, 0, 255);
  ring.setPixelColor(10, 0, 0, 0, 255);
  ring.setPixelColor(11, 0, 0, 0, 255);
  ring.setPixelColor(12, 0, 0, 0, 255);
  ring.setPixelColor(13, 0, 255, 0, 0);
  ring.setPixelColor(14, 0, 255, 0, 0);
  ring.setPixelColor(15, 0, 255, 0, 0);
  ring.setPixelColor(16, 0, 255, 0, 0);
  ring.setPixelColor(17, 0, 255, 0, 0);
  ring.setPixelColor(18, 0, 255, 0, 0);
  ring.show();
}

// Greatball pattern for rings
void greatball()
{
  ring.setPixelColor(0, 0, 0, 0, 255);
  ring.setPixelColor(1, 0, 0, 0, 255);
  ring.setPixelColor(2, 0, 0, 0, 255);
  ring.setPixelColor(3, 0, 0, 0, 255);
  ring.setPixelColor(4, 0, 0, 255, 0);
  ring.setPixelColor(5, 0, 0, 255, 0);
  ring.setPixelColor(6, 0, 0, 255, 0);
  ring.setPixelColor(7, 0, 0, 0, 255);
  ring.setPixelColor(8, 0, 0, 0, 255);
  ring.setPixelColor(9, 0, 0, 0, 255);
  ring.setPixelColor(10, 0, 0, 0, 255);
  ring.setPixelColor(11, 0, 0, 0, 255);
  ring.setPixelColor(12, 0, 0, 0, 255);
  ring.setPixelColor(13, 0, 0, 255, 0);
  ring.setPixelColor(14, 0, 255, 0, 0);
  ring.setPixelColor(15, 0, 0, 255, 0);
  ring.setPixelColor(16, 0, 0, 255, 0);
  ring.setPixelColor(17, 0, 255, 0, 0);
  ring.setPixelColor(18, 0, 0, 155, 0);
  ring.show();
}

// Ultraball pattern for rings
void ultraball()
{
  ring.setPixelColor(0, 0, 0, 0, 255);
  ring.setPixelColor(1, 0, 0, 0, 255);
  ring.setPixelColor(2, 0, 0, 0, 255);
  ring.setPixelColor(3, 0, 0, 0, 255);
  ring.setPixelColor(4, 100, 255, 0, 0);
  ring.setPixelColor(5, 0, 0, 0, 0);
  ring.setPixelColor(6, 100, 255, 0, 0);
  ring.setPixelColor(7, 0, 0, 0, 255);
  ring.setPixelColor(8, 0, 0, 0, 255);
  ring.setPixelColor(9, 0, 0, 0, 255);
  ring.setPixelColor(10, 0, 0, 0, 255);
  ring.setPixelColor(11, 0, 0, 0, 255);
  ring.setPixelColor(12, 0, 0, 0, 255);
  ring.setPixelColor(13, 0, 0, 0, 0);
  ring.setPixelColor(14, 100, 255, 0, 0);
  ring.setPixelColor(15, 100, 255, 0, 0);
  ring.setPixelColor(16, 100, 255, 0, 0);
  ring.setPixelColor(17, 100, 255, 0, 0);
  ring.setPixelColor(18, 0, 0, 0, 0);
  ring.show();
}

// Randomly flicker all 8 conduit port lights one at a time.
// void conduit1() {
//     uint8_t  i;
//     i = random(128);
//     strip.setPixelColor(i, color);
//     strip.show();
//     strip.setPixelColor(i, 0);
// }

// Solid color conduit
void conduit2()
{
  strip.setPixelColor(0, color);
  strip.setPixelColor(1, color);
  strip.setPixelColor(2, color);
  strip.setPixelColor(3, color);
  strip.setPixelColor(4, color);
  strip.setPixelColor(5, color);
  strip.setPixelColor(6, color);
  strip.setPixelColor(7, color);
  strip.show();
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
void rainbowCycle()
{
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
void theaterChaseRainbow()
{
  static int j = 0, q = 0;
  static boolean on = true;
  if (on)
  {
    for (int i = 0; i < ring.numPixels(); i = i + 3)
    {
      ring.setPixelColor(i + q, Wheel((i + j) % 255)); // turn every third pixel on
    }
  }
  else
  {
    for (int i = 0; i < ring.numPixels(); i = i + 3)
    {
      ring.setPixelColor(i + q, 0); // turn every third pixel off
    }
  }
  on = !on;    // toggel pixelse on or off for next time
  ring.show(); // display
  q++;         // update the q variable
  if (q >= 3)
  { // if it overflows reset it and update the J variable
    q = 0;
    j++;
    if (j >= 256)
      j = 0;
  }
  lastUpdate = millis(); // time for next change to the display
}

// ColorWipe
//  modified from Adafruit example to make it a state machine
void colorWipe(uint32_t c)
{
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
void wipe()
{
  for (int i = 0; i < ring.numPixels(); i++)
  {
    ring.setPixelColor(i, ring.Color(0, 0, 0));
  }
}

uint32_t Wheel(byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85)
  {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170)
  {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void setup()
{
// This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined(__AVR_ATtiny85__)
  if (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  ring.begin();
  ring.setBrightness(50);
  ring.show(); // Initialize all pixels to 'off'
  strip.begin();
  strip.setBrightness(15);
  strip.show(); // Initialize all pixels to 'off'
  //  meter.begin();
  //  meter.setBrightness(75);
  //  meter.show(); // Initialize all pixels to 'off'
}

void loop()
{

  static int pattern = 0, lastReading;
  // conduit1();
  conduit2(); // sets led colors to purple
  // replace delay(1000)
  if ((millis() - previousMillis) >= interval)
  {
    previousMillis = millis();
    // every first second
    pattern++;
    if (pattern > 8)
      pattern = 0;                        // wrap around if too big
    patternInterval = intervals[pattern]; // set speed for this pattern
    wipe();                               // clear out the buffer
  }
  if ((millis() - lastUpdate) > patternInterval)
    updatePattern(pattern);
  //  power();
}
