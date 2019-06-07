#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(36, PIN, NEO_GRB + NEO_KHZ800);

int audio_pin = A0;
int audio_amplitude = 0;
int upper_threshold = 40;
int lower_threshold = 20;
int velocity = 5;
int color_count = 0;
int brightness = 0;

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  audio_amplitude = analogRead(audio_pin);
  if (audio_amplitude > upper_threshold)
  {
    if (brightness < 255)
    {
      brightness += velocity;
    }    
    else
    {
      brightness = 255;
    }

    colorSet();
  }
  else if (audio_amplitude < lower_threshold)
  {
    if (brightness > 0)
    {
      brightness -= velocity;
    }
    else
    {
      brightness = 0;
      color_count++;
      if (color_count > 6)
      {
        color_count = 0;
      }
    }
    
    colorSet();
  }
  strip.show();
}

void colorSet()
{
  /*if (color_count == 0)
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, strip.Color(0, 0, brightness));
    }    
  }
  else if (color_count == 1)
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, strip.Color(0, brightness, 0));
    } 
  }
  else if (color_count == 2)
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, strip.Color(0, brightness, brightness));
    } 
  }
  else if (color_count == 3)
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, strip.Color(brightness, 0, 0));
    } 
  }
  else if (color_count == 4)
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, strip.Color(brightness, 0, brightness));
    } 
  }
  else if (color_count == 5)
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, strip.Color(brightness, brightness, 0));
    } 
  }
  else
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, strip.Color(brightness, brightness, brightness));
    } 
  }*/
  for(uint16_t i = 0; i < strip.numPixels(); i++) 
  {
    color_count = rand() % 7;
    if (color_count == 0)
    {
      strip.setPixelColor(i, strip.Color(0, 0, brightness));
    }
    else if (color_count == 1)
    {
      strip.setPixelColor(i, strip.Color(0, brightness, 0));
    }
    else if (color_count == 2)
    {
      strip.setPixelColor(i, strip.Color(0, brightness, brightness));
    }
    else if (color_count == 3)
    {
      strip.setPixelColor(i, strip.Color(brightness, 0, 0));
    }
    else if (color_count == 4)
    {
      strip.setPixelColor(i, strip.Color(brightness, 0, brightness));
    }
    else if (color_count == 5)
    {
      strip.setPixelColor(i, strip.Color(brightness, brightness, 0));
    }
    else
    {
      strip.setPixelColor(i, strip.Color(brightness, brightness, brightness));
    }
  } 
}
