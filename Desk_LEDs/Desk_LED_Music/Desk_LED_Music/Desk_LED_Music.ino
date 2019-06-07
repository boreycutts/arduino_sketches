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
int threshold = 35 ;
int threshold_gap = 5;
int upper_threshold, lower_threshold;
int velocity = 5;
int color_count = 0;
float brightness = 0;
int R, G, B;
int count = 0;

bool led_even = true;
bool led_odd = false;

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  upper_threshold = threshold + threshold_gap;
  lower_threshold = threshold - threshold_gap;
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
      if (color_count > 13)
      {
        color_count = 0;
      }
    }
    color_count = 4;
    colorSet();
  }
  strip.show();
}



void colorSet()
{
  if (color_count == 0)
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
    
  }
  else if (color_count == 5)
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, strip.Color(brightness, brightness, 0));
    } 
  }
  else if (color_count == 6)
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, strip.Color(brightness, brightness, brightness));
    } 
  }

/////////////////////////////////////////////////////////////////////////////////////
  
  else if (color_count == 7)
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++) 
    {
      if(i % 2 == 0 && led_even)
      {
        strip.setPixelColor(i, strip.Color(0, 0, brightness));
      }
      else if (i % 2 == 1 && led_odd)
      {
        strip.setPixelColor(i, strip.Color(0, 0, brightness));
      }
      else
      {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
      count += 1;
      if (led_even && count > 1000)
      {
        led_odd = true;
        led_even = false;
        count = 0;
      }
      else if (led_odd && count > 1000)
      {
        led_odd = false;
        led_even = true;
        count = 0;
      }
    }    
  }
  else if (color_count == 8)
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++) 
    {
      if(i % 2 == 0 && led_even)
      {
        strip.setPixelColor(i, strip.Color(0, brightness, 0));
      }
      else if (i % 2 == 1 && led_odd)
      {
        strip.setPixelColor(i, strip.Color(0, brightness, 0));
      }
      else
      {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
      count += 1;
      if (led_even && count > 1000)
      {
        led_odd = true;
        led_even = false;
        count = 0;
      }
      else if (led_odd && count > 1000)
      {
        led_odd = false;
        led_even = true;
        count = 0;
      }
    } 
  }
  else if (color_count == 9)
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++) 
    {
      if(i % 2 == 0 && led_even)
      {
        strip.setPixelColor(i, strip.Color(0, brightness, brightness));
      }
      else if (i % 2 == 1 && led_odd)
      {
        strip.setPixelColor(i, strip.Color(0, brightness, brightness));
      }
      else
      {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
      count += 1;
      if (led_even && count > 1000)
      {
        led_odd = true;
        led_even = false;
        count = 0;
      }
      else if (led_odd && count > 1000)
      {
        led_odd = false;
        led_even = true;
        count = 0;
      }
    } 
  }
  else if (color_count == 10)
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++) 
    {
      if(i % 2 == 0 && led_even)
      {
        strip.setPixelColor(i, strip.Color(brightness, 0, 0));
      }
      else if (i % 2 == 1 && led_odd)
      {
        strip.setPixelColor(i, strip.Color(brightness, 0, 0));
      }
      else
      {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
      count += 1;
      if (led_even && count > 1000)
      {
        led_odd = true;
        led_even = false;
        count = 0;
      }
      else if (led_odd && count > 1000)
      {
        led_odd = false;
        led_even = true;
        count = 0;
      }
    } 
  }
  else if (color_count == 11)
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++) 
    {
      if(i % 2 == 0 && led_even)
      {
        strip.setPixelColor(i, strip.Color(brightness, 0, brightness));
      }
      else if (i % 2 == 1 && led_odd)
      {
        strip.setPixelColor(i, strip.Color(brightness, 0, brightness));
      }
      else
      {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
      count += 1;
      if (led_even && count > 1000)
      {
        led_odd = true;
        led_even = false;
        count = 0;
      }
      else if (led_odd && count > 1000)
      {
        led_odd = false;
        led_even = true;
        count = 0;
      }
    } 
  }
  else if (color_count == 12)
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++) 
    {
      if(i % 2 == 0 && led_even)
      {
        strip.setPixelColor(i, strip.Color(brightness, brightness, 0));
      }
      else if (i % 2 == 1 && led_odd)
      {
        strip.setPixelColor(i, strip.Color(brightness, brightness, 0));
      }
      else
      {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
      count += 1;
      if (led_even && count > 1000)
      {
        led_odd = true;
        led_even = false;
        count = 0;
      }
      else if (led_odd && count > 1000)
      {
        led_odd = false;
        led_even = true;
        count = 0;
      }
    } 
  }
  else
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++) 
    {
      if(i % 2 == 0 && led_even)
      {
        strip.setPixelColor(i, strip.Color(brightness, brightness, brightness));
      }
      else if (i % 2 == 1 && led_odd)
      {
        strip.setPixelColor(i, strip.Color(brightness, brightness, brightness));
      }
      else
      {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
      count += 1;
      if (led_even && count > 1000)
      {
        led_odd = true;
        led_even = false;
        count = 0;
      }
      else if (led_odd && count > 1000)
      {
        led_odd = false;
        led_even = true;
        count = 0;
      }
    } 
  }
}
