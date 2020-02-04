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

// LED Stuff
#define PIN 11
#define LEDS 20
#define DELAY 15

// HSV Color Definitions
#define RED 16711680
#define ORANGE 16722432
#define YELLOW 16776960
#define GREEN 65280
#define CYAN 65322
#define BLUE 255
#define INDIGO 2752767
#define VIOLET 16711935

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

bool green=false, red=false, yellow=false, blue=false, orange=false, fret_up=false, fret_down=false, start_=false, select=false, star=false;
int whammy=0, thumb_x=0, thumb_y=0;
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
    updateButtonsPressed();
    if(buttonsPressed.length()) {
        buttonAnimation(buttonsPressed);
    } else {
        for(uint8_t i = 0; i < LEDS; i++) {
            strip.setPixelColor(i, 0, 0, 0);
        }
        strip.show();
    }
}

void buttonAnimation(const String buttonsPressedInit) {
    for(int i = 0; i < buttonsPressedInit.length(); i++) {
        updateButtonsPressed();
        if(buttonsPressed != buttonsPressedInit) {
            return;
        }

        for(int j = 0; j < LEDS/2; j++) {
            updateButtonsPressed();
            if(buttonsPressed != buttonsPressedInit) {
                return;
            }

            setPixelColorByCharacter(j, buttonsPressed[i]);
            strip.setPixelColor(LEDS/2 + j, 0, 0, 0);
            strip.show();
            delay(DELAY);
        }

        for(int j = 0; j < LEDS/2; j++) {
            updateButtonsPressed();
            if(buttonsPressed != buttonsPressedInit) {
                return;
            }

            setPixelColorByCharacter(LEDS/2 + j, buttonsPressed[i]);
            strip.setPixelColor(j, 0, 0, 0);
            strip.show();
            delay(DELAY);
        }
    }
}

void setPixelColorByCharacter(int index, char c) {
    switch(c) {
        case 'g':
            strip.setPixelColor(index, GREEN);
            break;
            
        case 'r':
            strip.setPixelColor(index, RED);
            break;

        case 'y':
            strip.setPixelColor(index, YELLOW);
            break;

        case 'b':
            strip.setPixelColor(index, BLUE);
            break;

        case 'o':
            strip.setPixelColor(index, ORANGE);
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

