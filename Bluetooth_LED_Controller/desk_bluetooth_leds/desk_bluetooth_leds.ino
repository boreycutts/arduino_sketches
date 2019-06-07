#include <Adafruit_NeoPixel.h>

#define PIN 6
#define COLOR 0
#define STATIC 1
#define DYNAMIC 2

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(51, PIN, NEO_GRB + NEO_KHZ800);

// GLOBAL VARIABLES 
byte serial_data[10];
uint32_t color;
bool color_fill = false;
bool rotate = true;
bool theater_chase = false;

volatile bool data_recieved = false;

void setup() {
  pinMode(2, INPUT);
  attachInterrupt(0, bt_isr, RISING);

  Serial.begin(9600);
  strip.begin();
  strip.show();
  Serial.setTimeout(10);
  color = strip.Color(255,0,0);
}

void loop() 
{
  Serial.readBytes(serial_data, 10);

  if(serial_data[0] != 0)
  {
    for(int i = 0; i < sizeof(serial_data); i++)
    {
      Serial.print(serial_data[i]);
      Serial.print(" ");
    }
    Serial.println("");
  }
  
  if(serial_data[0] == 1)
  {
    color = strip.Color(serial_data[1], serial_data[2], serial_data[3]);
    /*for(int i = 0; i < strip.numPixels(); i++)
    {
      if(data_recieved){break;}
      strip.setPixelColor(i, color);
      //strip.show();
      //delay(10);
    }
    strip.show();    */
    data_recieved = false;
  }
  else if(serial_data[0] == 2)
  {
    color_fill = serial_data[1];
    rotate = serial_data[3];
    theater_chase = serial_data[5];
    data_recieved = false;
  }

  if(!data_recieved)
  {
    if(color_fill)
    {
      colorFill(color, 20);
      colorFill(color, 20);
    }

    if(rotate)
    {
      pingPong(color, 20);
      pingPong(color, 20);
    }

    if(theater_chase)
    {
      theaterChase(color, 50);
    }

    if(!color_fill && !rotate && !theater_chase)
    {
      for(int i = 0; i < strip.numPixels(); i++)
      {
        if(data_recieved){break;}
        strip.setPixelColor(i, color);
        strip.show();
        delay(10);
      }
    }
  }

  memset(serial_data, 0, sizeof(serial_data));
}

void bt_isr()
{
  data_recieved = true;
  //Serial.println("INTERRUPT");
}

void rainbow(uint8_t wait) 
{
  uint16_t i, j;

  for(j=0; j<256; j++) 
  {
    if(data_recieved){break;}
    for(i=0; i<strip.numPixels(); i++) 
    {
      if(data_recieved){break;}
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    if(data_recieved){break;}
    for (int q=0; q < 3; q++) {
      if(data_recieved){break;}
      for (int i=0; i < strip.numPixels(); i=i+3) {
        if(data_recieved){break;}
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

void colorFill(uint32_t color, uint8_t wait)
{
  for(int i = 0; i < strip.numPixels(); i++)
  {
    if(data_recieved){break;}
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
  for(int i = 0; i < strip.numPixels(); i++)
  {
    if(data_recieved){break;}
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
    delay(wait);
  }
}

void pingPong(uint32_t color, uint8_t wait)
{
  int range = 15;
  for(int i = 0; i < strip.numPixels(); i++)
  {
    if(data_recieved){break;}
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
  for(int i = 0; i < strip.numPixels() - range; i++)
  {
    for(int j = 0; j < strip.numPixels(); j++)
    {
      if(data_recieved){break;}
      strip.setPixelColor(j, strip.Color(0, 0, 0));
    }
    if(data_recieved){break;}
    for(int j = 0; j < range; j++)
    {
      if(data_recieved){break;}
      strip.setPixelColor(i + j, color);
    }
    strip.show();
    delay(wait);
  }
  for(int i = strip.numPixels() - range; i >= 0; i--)
  {
    for(int j = 0; j < strip.numPixels(); j++)
    {
      if(data_recieved){break;}
      strip.setPixelColor(j, strip.Color(0, 0, 0));
    }
    if(data_recieved){break;}
    for(int j = 0; j < range; j++)
    {
      if(data_recieved){break;}
      strip.setPixelColor(i + j, color);
    }
    strip.show();
    delay(wait);
  }
}

void breathe(uint8_t wait)
{

}



// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) 
{
  if(WheelPos < 85) 
  {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) 
  {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else 
  {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

