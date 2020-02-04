#include <Adafruit_NeoPixel.h>

#define PIN 3
#define LEDS 64
#define RED 0
#define ORANGE 5461
#define YELLOW 10923
#define GREEN 21845
#define CYAN 27306
#define BLUE 43690
#define INDIGO 49151
#define VIOLET 54613
#define ALEXA BLUE + 3000

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
    Serial.begin(9600);
    strip.begin();
    strip.show();
}

char data;
bool request_active;
bool request_playback_start;
bool request_playback_end;
bool request_record_start;
bool request_record_end;
bool request_process_start;
bool request_process_end;
bool reuqest_failed;
bool request_succeeded;

void loop() 
{
    request_active = false;
    request_playback_start = false;
    request_playback_end = false;
    request_record_start = false;
    request_record_end = false;
    request_process_start = false;
    request_process_end = false;
    
    if(!Serial.available())
    {
        Serial.println("IDLE");
        squareRainbow(10);
    }
    else
    {
        Serial.println("RECIEVED SERIAL DATA");
        request_active = true;
        while(request_active)
        {
            data = Serial.read();
            int test = data;
            switch(data)
            {
                case '1':
                    Serial.println(test);
                    request_playback_start = true;
                    clearStrip();
                    while(!Serial.available())
                    {
                        alexaPlayback(8);
                    }
                    break;

                case '2':
                    Serial.println(test);
                    request_playback_end = true;
                    request_active = false;
                    break;

                case '3':
                    Serial.println(test);
                    request_record_start = true;
                    alexaTrigger(25);
                    while(!Serial.available())
                    {
                        breath();
                    }
                    break;

                case '4':
                    Serial.println(test);
                    request_record_end = true;
                    break;

                case '5':
                    Serial.println(test);
                    request_process_start = true;
                    clearStrip();
                    while(!Serial.available())
                    {
                        alexaProcess(1);
                    }
                    break;

                case '6':
                    Serial.println(test);
                    request_process_end = true;
                    break;

                case -1:
                    break;

                default:
                    Serial.println(test);
                    request_active = false;
                    break;
            }
        }
    }
}

void setSquareColor(uint8_t square, uint32_t color)
{
    for(int i = 0 + 8*square; i < 8 + 8*square; i++)
    {
        strip.setPixelColor(i, color);
    }
}

void clearStrip()
{
    for(int square = 0; square < 8; square++)
    {
        if(Serial.available())
        {
            return;
        }
        setSquareColor(square, strip.gamma32(strip.ColorHSV(0, 0, 0)));
    }
    strip.show();
}

void alexaTrigger(int wait)
{
    const int SHELF[4][16] =    {\
                                    {15 ,14 ,13 ,12 ,11 ,10 ,9  ,8  ,7  ,6  ,5  ,4  ,3  ,2  ,1  ,0  }, {16 ,17 ,18 ,19 ,20 ,21 ,22 ,23 ,24 ,25 ,26 ,27 ,28 ,29 ,30 ,31},\
                                    {47 ,46 ,45 ,44 ,43 ,42 ,41 ,40 ,39 ,38 ,37 ,36 ,35 ,34 ,33 ,32 }, {48 ,49 ,50 ,51 ,52 ,53 ,54 ,55 ,56 ,57 ,58 ,59 ,60 ,61 ,62 ,63} \
                                };

    clearStrip();
    delay(400);
    for(int pixel = 0; pixel < 16; pixel++)
    {
        for(int i = 0; i < 4; i++)
        {
            strip.setPixelColor(SHELF[i][pixel], strip.gamma32(strip.ColorHSV(ALEXA, 255, 255)));
        }
        strip.show();
        delay(wait);
    }
}

void alexaPlayback(int wait)
{
    uint8_t square_0 = 0;
    uint8_t square_1 = 127;
    uint8_t square_2 = 25;
    uint8_t square_3 = 152;
    uint8_t square_4 = 50;
    uint8_t square_5 = 177;
    uint8_t square_6 = 75;
    uint8_t square_7 = 202;

    while(true)
    {
        if(Serial.available())
        {
            return;
        }

        setSquareColor(0, strip.gamma32(strip.ColorHSV(ALEXA, 255, cycleBrightness(square_0))));
        setSquareColor(1, strip.gamma32(strip.ColorHSV(ALEXA, 255, cycleBrightness(square_1))));
        setSquareColor(2, strip.gamma32(strip.ColorHSV(ALEXA, 255, cycleBrightness(square_2))));
        setSquareColor(3, strip.gamma32(strip.ColorHSV(ALEXA, 255, cycleBrightness(square_3))));
        setSquareColor(4, strip.gamma32(strip.ColorHSV(ALEXA, 255, cycleBrightness(square_4))));
        setSquareColor(5, strip.gamma32(strip.ColorHSV(ALEXA, 255, cycleBrightness(square_5))));
        setSquareColor(6, strip.gamma32(strip.ColorHSV(ALEXA, 255, cycleBrightness(square_6))));
        setSquareColor(7, strip.gamma32(strip.ColorHSV(ALEXA, 255, cycleBrightness(square_7))));

        strip.show();
        delay(wait);

        square_0++;
        square_1++;
        square_2++;
        square_3++;
        square_4++;
        square_5++;
        square_6++;
        square_7++;
    }
}

void alexaProcess(int wait)
{
    for(int square = 0; square < 8; square++)
    {
        if(Serial.available())
        {
            return;
        }
        for(int brightness = 0; brightness < 175; brightness += 4)
        {
            if(Serial.available())
            {
                return;
            }
            setSquareColor(square, strip.gamma32(strip.ColorHSV(0, 0, brightness)));
            strip.show();
            delay(wait);
        }
    }
    for(int square = 0; square < 8; square++)
    {
        if(Serial.available())
        {
            return;
        }
        for(int brightness = 175; brightness > 0; brightness -= 4)
        {
            if(Serial.available())
            {
                return;
            }
            setSquareColor(square, strip.gamma32(strip.ColorHSV(0, 0, brightness)));
            strip.show();
            delay(wait);
        }
    }
}

int cycleBrightness(int value)
{
    if(value < 128)
    {
        return 2*value;
    }
    else
    {
        return -2*value + 511;
    }
}

void breath()
{
    for(int brightness = 255; brightness > 0; brightness -= 1)
    {   
        if(Serial.available())
        {
            return;
        }
        for(int square = 0; square < 8; square++)
        {
            if(Serial.available())
            {
                return;
            }
            setSquareColor(square, strip.gamma32(strip.ColorHSV(ALEXA, 255, brightness)));
        }
        strip.show();
        delay(5);
    }
    for(int brightness = 0; brightness < 255; brightness += 1)
    {   
        if(Serial.available())
        {
            return;
        }
        for(int square = 0; square < 8; square++)
        {
            if(Serial.available())
            {
                return;
            }
            setSquareColor(square, strip.gamma32(strip.ColorHSV(ALEXA, 255, brightness)));
        }
        strip.show();
        delay(5);
    }
}

void squareRainbow(int wait)
{
    for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) 
    {
        if(Serial.available())
        {
            return;
        }
        for(int i=0; i<8; i++) 
        { 
            if(Serial.available())
            {
                return;
            }
            int pixelHue = firstPixelHue + (i * 65536L / 8);
            setSquareColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
        }
        strip.show();
        delay(wait);
    }
}

void randomRainbow(int wait)
{
    uint8_t square_0 = 0;
    uint8_t square_1 = 0;
    uint8_t square_2 = 0;
    uint8_t square_3 = 0;
    uint8_t square_4 = 0;
    uint8_t square_5 = 0;
    uint8_t square_6 = 0;
    uint8_t square_7 = 0;

    uint16_t color_0 = RED;
    uint16_t color_1 = GREEN+ORANGE;
    uint16_t color_2 = ORANGE;
    uint16_t color_3 = BLUE;
    uint16_t color_4 = YELLOW;
    uint16_t color_5 = INDIGO;
    uint16_t color_6 = GREEN;
    uint16_t color_7 = VIOLET;

    clearStrip();

    for(int i = 0; i < 128; i++)
    {
        if(Serial.available())
        {
            return;
        }
        setSquareColor(0, strip.gamma32(strip.ColorHSV(color_0, 255, cycleBrightness(square_0))));
        setSquareColor(1, strip.gamma32(strip.ColorHSV(color_1, 255, cycleBrightness(square_1))));
        setSquareColor(2, strip.gamma32(strip.ColorHSV(color_2, 255, cycleBrightness(square_2))));
        setSquareColor(3, strip.gamma32(strip.ColorHSV(color_3, 255, cycleBrightness(square_3))));
        setSquareColor(4, strip.gamma32(strip.ColorHSV(color_4, 255, cycleBrightness(square_4))));
        setSquareColor(5, strip.gamma32(strip.ColorHSV(color_5, 255, cycleBrightness(square_5))));
        setSquareColor(6, strip.gamma32(strip.ColorHSV(color_6, 255, cycleBrightness(square_6))));
        setSquareColor(7, strip.gamma32(strip.ColorHSV(color_7, 255, cycleBrightness(square_7))));
        
        square_1 += 1;
        square_3 += 1;
        square_5 += 1;
        square_7 += 1;

        strip.show();
        delay(10);
    }

    while(true)
    {
        if(Serial.available())
        {
            return;
        }
        setSquareColor(0, strip.gamma32(strip.ColorHSV(color_0, 255, cycleBrightness(square_0))));
        setSquareColor(1, strip.gamma32(strip.ColorHSV(color_1, 255, cycleBrightness(square_1))));
        setSquareColor(2, strip.gamma32(strip.ColorHSV(color_2, 255, cycleBrightness(square_2))));
        setSquareColor(3, strip.gamma32(strip.ColorHSV(color_3, 255, cycleBrightness(square_3))));
        setSquareColor(4, strip.gamma32(strip.ColorHSV(color_4, 255, cycleBrightness(square_4))));
        setSquareColor(5, strip.gamma32(strip.ColorHSV(color_5, 255, cycleBrightness(square_5))));
        setSquareColor(6, strip.gamma32(strip.ColorHSV(color_6, 255, cycleBrightness(square_6))));
        setSquareColor(7, strip.gamma32(strip.ColorHSV(color_7, 255, cycleBrightness(square_7))));

        color_0 += 128;
        color_1 += 188;
        color_2 += 128;
        color_3 += 188;
        color_4 += 128;
        color_5 += 188;
        color_6 += 128;
        color_7 += 188;
        
        square_0 += 1;
        square_1 += 1;
        square_2 += 1;
        square_3 += 1;
        square_4 += 1;
        square_5 += 1;
        square_6 += 1;
        square_7 += 1;

        strip.show();
        delay(wait);
    }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) 
{
    for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) 
    {
        for(int i=0; i<strip.numPixels(); i++) 
        { 
            int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
            strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
        }
        strip.show();
        delay(wait);
    }
}
