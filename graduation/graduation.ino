#include <Adafruit_NeoPixel.h>

#define PIN 5

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(36, PIN, NEO_RGB + NEO_KHZ400);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{
  squares();
}

void setPixelGrid(uint8_t x, uint8_t y, uint32_t c)
{
  int grid[6][6] = {{0,   1,    2,    3,    4,    5},
                  {11,  10,   9,    8,    7,    6},
                  {12,  13,   14,   15,   16,   17},
                  {23,  22,   21,   20,   19,   18},
                  {24,  25,   26,   27,   28,   29},
                  {35,  34,   33,   32,   31,   30}};
  strip.setPixelColor(grid[x][y], c);
}


void squares()
{
  int c0 = 0, c1 = 0, c2 = 0;
  bool b0 = true, b1 = false, b2 = false;

  while(b0 || b1 || b2)
  {
    if(b0)
    {
      c0++;
    }
    else
    {
      b0--;
    }
    if(b1)
    {
      if(c0 < 30)
      {
        c1--;
      }
      else
      {
        c1++;
      }
    }
    if(b2)
    {
      if(c1 < 30)
      {
        c2--;
      }
      else
      {
        c2++;
      }
    }
    
    if(c0 > 70)
    {
      b1 = true;
    }
    if(c1 > 70)
    {
      b2 = true;
    }
    
    setPixelGrid(2, 2, strip.Color(0, c0, 0));
    setPixelGrid(2, 3, strip.Color(0, c0, 0));
    setPixelGrid(3, 2, strip.Color(0, c0, 0));
    setPixelGrid(3, 3, strip.Color(0, c0, 0));

    setPixelGrid(1, 1, strip.Color(0, c1, 0));
    setPixelGrid(1, 2, strip.Color(0, c1, 0));
    setPixelGrid(1, 3, strip.Color(0, c1, 0));
    setPixelGrid(1, 4, strip.Color(0, c1, 0));
    setPixelGrid(2, 1, strip.Color(0, c1, 0));
    setPixelGrid(2, 4, strip.Color(0, c1, 0));
    setPixelGrid(3, 1, strip.Color(0, c1, 0));
    setPixelGrid(3, 4, strip.Color(0, c1, 0));
    setPixelGrid(4, 1, strip.Color(0, c1, 0));
    setPixelGrid(4, 2, strip.Color(0, c1, 0));
    setPixelGrid(4, 3, strip.Color(0, c1, 0));
    setPixelGrid(4, 4, strip.Color(0, c1, 0));

    setPixelGrid(0, 0, strip.Color(0, c2, 0));
    setPixelGrid(0, 1, strip.Color(0, c2, 0));
    setPixelGrid(0, 2, strip.Color(0, c2, 0));
    setPixelGrid(0, 3, strip.Color(0, c2, 0));
    setPixelGrid(0, 4, strip.Color(0, c2, 0));
    setPixelGrid(0, 5, strip.Color(0, c2, 0));
    setPixelGrid(1, 0, strip.Color(0, c2, 0));
    setPixelGrid(1, 5, strip.Color(0, c2, 0));
    setPixelGrid(2, 0, strip.Color(0, c2, 0));
    setPixelGrid(2, 5, strip.Color(0, c2, 0));
    setPixelGrid(3, 0, strip.Color(0, c2, 0));
    setPixelGrid(3, 5, strip.Color(0, c2, 0));
    setPixelGrid(4, 0, strip.Color(0, c2, 0));
    setPixelGrid(4, 5, strip.Color(0, c2, 0));
    setPixelGrid(5, 0, strip.Color(0, c2, 0));
    setPixelGrid(5, 1, strip.Color(0, c2, 0));
    setPixelGrid(5, 2, strip.Color(0, c2, 0));
    setPixelGrid(5, 3, strip.Color(0, c2, 0));
    setPixelGrid(5, 4, strip.Color(0, c2, 0));
    setPixelGrid(5, 5, strip.Color(0, c2, 0));

    strip.show();
    delay(10);
  }
}


void wave()
{
  for(uint8_t i = 0; i < 6; i++)
  {
    for(int c = 0; c < 100; c += 20)
    {
    for(uint8_t j = 0; j < 6; j++)
    {
      setPixelGrid(i, j, strip.Color(0, c, 0));
    }
    strip.show();
    delay(1);
    }
  }
  for(uint8_t i = 0; i < 6; i++)
  {
    for(int c = 100; c >= 0; c -= 20)
    {
    for(uint8_t j = 0; j < 6; j++)
    {
      setPixelGrid(i, j, strip.Color(0, c, 0));
    }
    strip.show();
    delay(1);
    }
  }
}

