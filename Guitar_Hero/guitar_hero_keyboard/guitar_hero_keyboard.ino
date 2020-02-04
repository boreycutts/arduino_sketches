#include <Adafruit_NeoPixel.h>

// Keyboard Stuff
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
#define KEY_MOD_LSHIFT 0x02 // Keyboard Left Shift
#define KEY_BACKSPACE 0x2a // Keyboard DELETE (Backspace)

// Mode Stuff
#define MODES 2
#define MODE_CHANGE_TIMEOUT 300

// LED Stuff
#define PIN 11
#define LEDS 20
#define FADE_SPEED 8

// HSV Color Definitions
#define RED 0
#define ORANGE 5462
#define YELLOW 10923
#define GREEN 21845
#define CYAN 32768
#define BLUE 43691
#define INDIGO 49153
#define VIOLET 54613

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);

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

bool green=false, red=false, yellow=false, blue=false, orange=false, fret_up=false, fret_down=false, start_=false, select=false, star=false, cleared=false;
int whammy=0, thumb_x=0, thumb_y=0, modeChange=0, mode=0;
uint8_t i=2;
String buttonsPressed = "";

uint8_t buf[8] = { 
  0 };   /* Keyboard report buffer */
  
void loop() 
{
    /* TEST SPACE
    * swswswswsswsswswswswswsssssssssWaaabbcdee
    * 
    * 
    * 
    */

    if(mode == 0) {
        if(cleared) {
            for(uint8_t i = 0; i < LEDS; i++) {
                for(uint16_t brightness = 0; brightness < 255; brightness+=4) {
                    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(CYAN, 255, brightness)));
                    strip.show();
                }
            }
            delay(100);
            for(int16_t brightness = 254; brightness >= 0; brightness--) {
                for(uint8_t i = 0; i < LEDS; i++) {
                    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(CYAN, 255, brightness)));
                }
                strip.show();
                delay(4);
            }
            cleared = false;
        }
        updateButtonsPressed();
        if(buttonsPressed.length()) {
            buttonAnimation(buttonsPressed);
        } else {
            for(uint8_t i = 0; i < LEDS; i++) {
                strip.setPixelColor(i, 0, 0, 0);
            }
            strip.show();
        }
    } else if(mode == 1) {
        rainbow(mode);
    } else {
        if(!cleared) {
            for(uint8_t i = 0; i < LEDS; i++) {
                strip.setPixelColor(i, 0, 0, 0);
                strip.show();
                delay(50);
            }
            cleared = true;
        }
        updateButtonsPressed();
    }
}

void rainbow(const int modeInit) {
    for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
        updateButtonsPressed();
        if(mode != modeInit) {
            return;
        }
        
        for(int i = 0; i < LEDS; i++) {
            int pixelHue = firstPixelHue + (i * 65536L / LEDS);
            strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
        }
        strip.show();
        delay(10);
    }
}

void buttonAnimation(const String buttonsPressedInit) {
    uint8_t colorIndex1 = 0;
    uint8_t colorIndex2 = 1;
    while(true) {
        updateButtonsPressed();
        if(buttonsPressed != buttonsPressedInit) {
            return;
        }

        for(uint16_t brightness = 0; brightness < 255; brightness += FADE_SPEED) {
            updateButtonsPressed();
            if(buttonsPressed != buttonsPressedInit) {
                return;
            }
            
            for(uint8_t led = 0; led < LEDS/2; led++) {
                setPixelColorByCharacter(led, buttonsPressed[colorIndex1], brightness);
            }
            for(uint8_t led = LEDS/2; led < LEDS; led++) {
                if(buttonsPressedInit.length() > 1) {
                    setPixelColorByCharacter(led, buttonsPressed[colorIndex2], 255-brightness);
                } else {
                    setPixelColorByCharacter(led, buttonsPressed[0], 255-brightness);
                }
            }
            strip.show();
        }

        if(buttonsPressedInit.length() > 1) {
            if(colorIndex2 < buttonsPressedInit.length() - 1) {
                colorIndex2++;
            } else {
                colorIndex2 = 0;
            }
        }

        for(int16_t brightness = 255; brightness >= 0; brightness -= FADE_SPEED) {
            updateButtonsPressed();
            if(buttonsPressed != buttonsPressedInit) {
                return;
            }
        
            for(uint8_t led = 0; led < LEDS/2; led++) {
                setPixelColorByCharacter(led, buttonsPressed[colorIndex1], brightness);
            }
            for(uint8_t led = LEDS/2; led < LEDS; led++) {
                if(buttonsPressedInit.length() > 1) {
                    setPixelColorByCharacter(led, buttonsPressed[colorIndex2], 255-brightness);
                } else {
                    setPixelColorByCharacter(led, buttonsPressed[0], 255-brightness);
                }
            }
            strip.show();
        }

        if(colorIndex1 < buttonsPressedInit.length() - 1) {
            colorIndex1++;
        } else {
            colorIndex1 = 0;
        }
    }
}

void setPixelColorByCharacter(uint8_t index, char c, uint8_t brightness) {
    switch(c) {
        case 'g':
            strip.setPixelColor(index, strip.gamma32(strip.ColorHSV(GREEN, 255, brightness)));
            break;
            
        case 'r':
            strip.setPixelColor(index, strip.gamma32(strip.ColorHSV(RED, 255, brightness)));
            break;

        case 'y':
            strip.setPixelColor(index, strip.gamma32(strip.ColorHSV(YELLOW, 255, brightness)));
            break;

        case 'b':
            strip.setPixelColor(index, strip.gamma32(strip.ColorHSV(BLUE, 255, brightness)));
            break;

        case 'o':
            strip.setPixelColor(index, strip.gamma32(strip.ColorHSV(ORANGE, 255, brightness)));
            break;
    }
}

void updateButtonsPressed() {
    clearBuffers();
    getInputs();
    setBuffers();
    Serial.write(buf, 8);
}

void getInputs() {
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
}

void clearBuffers() {
    i = 2;
    buttonsPressed = "";

    for(uint8_t j = 0; j < 8; j++) {
        buf[j] = 0;
    }
}

void setBuffers() {
    if(green) {
        buf[i] = KEY_A;
        if(i < 8) {
            i++;
        }
        buttonsPressed += "g";
    }
    if(red) {
        buf[i] = KEY_B;
        if(i < 8) {
            i++;
        }
        buttonsPressed += "r";
    }
    if(yellow) {
        buf[i] = KEY_C;
        if(i < 8) {
            i++;
        }
        buttonsPressed += "y";
    }
    if(blue) {
        buf[i] = KEY_D;
        if(i < 8) {
            i++;
        }
        buttonsPressed += "b";
    }
    if(orange) {
        buf[i] = KEY_E;
        if(i < 8) {
            i++;
        }
        buttonsPressed += "o";
    }
    if(fret_up) {
        buf[i] = KEY_W;
        if(i < 8) {
            i++;
        }
    }
    if(fret_down) {
        buf[i] = KEY_S;
        if(i < 8) {
            i++;
        }
    }
    if(select) {
        buf[i] = KEY_ENTER;
        if(i < 8) {
            i++;
        }
    }
    if(start_) {
        buf[i] = KEY_BACKSPACE;
        if(i < 8) {
            i++;
        }
    }
    if(star) {
        buf[i] = KEY_F;
        if(i < 8) {
            i++;
        }
        modeChange++;
        if(modeChange > MODE_CHANGE_TIMEOUT) {
            modeChange = 0;
            if(mode < MODES) {
                mode++;
            } else { 
                mode = 0;
            }
        }
    } else {
        modeChange = 0;
    }
    if(whammy > 600) {
        buf[0] = KEY_MOD_LSHIFT;
    }
    if(thumb_x > 600) {
        buf[i] = KEY_RIGHT;
        if(i < 8) {
            i++;
        }
    }
    if(thumb_x < 400) {
        buf[i] = KEY_LEFT;
        if(i < 8) {
            i++;
        }
    }
    if(thumb_y > 600) {
        buf[i] = KEY_UP;
        if(i < 8) {
            i++;
        }
    }
    if(thumb_y < 400) {
        buf[i] = KEY_DOWN;
        if(i < 8) {
            i++;
        }
    }
}

