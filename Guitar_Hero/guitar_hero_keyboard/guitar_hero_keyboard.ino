#include <Adafruit_NeoPixel.h>

#define KEY_A 0x04 // Keyboard a and A
#define KEY_B 0x05 // Keyboard b and B
#define KEY_C 0x06 // Keyboard c and C
#define KEY_D 0x07 // Keyboard d and D
#define KEY_E 0x08 // Keyboard e and E
#define KEY_F 0x09 // Keyboard f and F
#define KEY_W 0x1a // Keyboard w and W
#define KEY_S 0x16 // Keyboard s and S
#define KEY_RIGHT 0x4f // Keyboard Right Arrow
#define KEY_LEFT 0x50 // Keyboard Left Arrow
#define KEY_DOWN 0x51 // Keyboard Down Arrow
#define KEY_UP 0x52 // Keyboard Up Arrow
#define KEY_ESC 0x29 // Keyboard ESCAPE
#define KEY_SPACE 0x2c // Keyboard Spacebar
#define KEY_ENTER 0x28 // Keyboard Return (ENTER)
#define KEY_MOD_LSHIFT 0x02
#define KEY_BACKSPACE 0x2a // Keyboard DELETE (Backspace)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(18, 11, NEO_RGB + NEO_KHZ400);

void setup() 
{
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);
  Serial.begin(9600);

  strip.begin();
  strip.show();
}

bool green=false, red=false, yellow=false, blue=false, orange=false, fret_up=false, fret_down=false, start_=false, select=false, star=false;
int whammy=0, thumb_x=0, thumb_y=0;
uint8_t i=2, c=0;
uint32_t color_green = strip.Color(255, 0, 0);
uint32_t color_red = strip.Color(0, 255, 0);
uint32_t color_yellow = strip.Color(150, 255, 0);
uint32_t color_blue = strip.Color(0, 0, 255);
uint32_t color_orange = strip.Color(65, 255, 0);
uint32_t colors_[5] = {0, 0, 0, 0, 0};

uint8_t buf[8] = { 
  0 };   /* Keyboard report buffer */
  
void loop() 
{
  green = !digitalRead(2);
  red = !digitalRead(3);
  yellow = !digitalRead(4);
  blue = !digitalRead(5);
  orange = !digitalRead(6);
  fret_up = !digitalRead(7);
  fret_down = !digitalRead(8);
  start_ = !digitalRead(9);
  select = !digitalRead(10);
  star = !digitalRead(12);
  thumb_y = analogRead(A0);
  thumb_x = analogRead(A1);
  whammy = analogRead(A2);

  /* TEST SPACE
   * swswswswsswsswswswswswsssssssssWaaabbcdee
   * 
   * wswssws
   * 
   * 
   */

  i = 2;
  c = 0;
  clearBuffer();
  for(int j = 0; j < 5; j++)
  {
    colors_[j] = 0;
  }
  
  if(green)
  {
    buf[i] = KEY_A;
    if(i < 7)
    {
      i++;
    }
    colors_[c] = color_green;
    c++;
  }
  if(red)
  {
    buf[i] = KEY_B;
    if(i < 7)
    {
      i++;
    }
    colors_[c] = color_red;
    c++;
  }
  if(yellow)
  {
    buf[i] = KEY_C;
    if(i < 7)
    {
      i++;
    }
    colors_[c] = color_yellow;
    c++;
  }
  if(blue)
  {
    buf[i] = KEY_D;
    if(i < 7)
    {
      i++;
    }
    colors_[c] = color_blue;
    c++;
  }
  if(orange)
  {
    buf[i] = KEY_E;
    if(i < 7)
    {
      i++;
    }
    colors_[c] = color_orange;
    c++;
  }
  if(fret_up)
  {
    buf[i] = KEY_W;
    if(i < 7)
    {
      i++;
    }
  }
  if(fret_down)
  {
    buf[i] = KEY_S;
    if(i < 7)
    {
      i++;
    }
  }
  if(select)
  {
    buf[i] = KEY_ENTER;
    if(i < 7)
    {
      i++;
    }
  }
  if(start_)
  {
    buf[i] = KEY_BACKSPACE;
    if(i < 7)
    {
      i++;
    }
  }
  if(star)
  {
    buf[i] = KEY_F;
    if(i < 7)
    {
      i++;
    }
  }
  if(whammy > 600)
  {
    buf[0] = KEY_MOD_LSHIFT;
  }
  if(thumb_x > 600)
  {
    buf[i] = KEY_RIGHT;
    if(i < 7)
    {
      i++;
    }
  }
  if(thumb_x < 400)
  {
    buf[i] = KEY_LEFT;
    if(i < 7)
    {
      i++;
    }
  }
  if(thumb_y > 600)
  {
    buf[i] = KEY_UP;
    if(i < 7)
    {
      i++;
    }
  }
  if(thumb_y < 400)
  {
    buf[i] = KEY_DOWN;
    if(i < 7)
    {
      i++;
    }
  }
  
  Serial.write(buf, 8);

  for(int j = 0; j < 18; j++)
  {
    if (c == 0)
    {
      for(int j = 0; j < 18; j++)
      {
        strip.setPixelColor(j, strip.Color(0, 0, 0));
      }
    }
    else if(c == 1)
    {
      strip.setPixelColor(j, colors_[0]);
    }
    else if(c == 2)
    {
      if(j < 9)
      {
        strip.setPixelColor(j, colors_[0]);
      }
      else
      {
        strip.setPixelColor(j, colors_[1]);
      }
    }
    else if(c == 3)
    {
      if(j < 6)
      {
        strip.setPixelColor(j, colors_[0]);
      }
      else if(j < 12)
      {
        strip.setPixelColor(j, colors_[1]);
      }
      else
      {
        strip.setPixelColor(j, colors_[2]);
      }
    }
    else if(c == 4)
    {
      if(j < 4)
      {
        strip.setPixelColor(j, colors_[0]);
      }
      else if(j < 8)
      {
        strip.setPixelColor(j, colors_[1]);
      }
      else if(j < 12)
      {
        strip.setPixelColor(j, colors_[2]);
      }
      else
      {
        strip.setPixelColor(j, colors_[3]);
      }
    }
    else
    {
      if(j < 3)
      {
        strip.setPixelColor(j, colors_[0]);
      }
      else if(j < 6)
      {
        strip.setPixelColor(j, colors_[1]);
      }
      else if(j < 9)
      {
        strip.setPixelColor(j, colors_[2]);
      }
      else if(j < 12)
      {
        strip.setPixelColor(j, colors_[3]);
      }
      else
      {
        strip.setPixelColor(j, colors_[4]);
      }
    }
  }
  strip.show();
}

void clearBuffer()
{
  buf[0] = 0;
  buf[1] = 0;
  buf[2] = 0;
  buf[3] = 0;
  buf[4] = 0;
  buf[5] = 0;
  buf[6] = 0;
  buf[7] = 0;
}

