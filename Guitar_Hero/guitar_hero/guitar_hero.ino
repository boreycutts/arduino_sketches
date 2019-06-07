void setup() {
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  Serial.begin(9600);
}

bool green=false, red=false, yellow=false, blue=false, orange=false, fret_up=false, fret_down=false, start_=false, select=false, analog=false;
int whammy=0, thumb_x=0, thumb_y=0;

uint8_t buf[8] = { 
  0 };   /* Keyboard report buffer */
  
void loop() {
  green = !digitalRead(2);
  red = !digitalRead(3);
  yellow = !digitalRead(4);
  blue = !digitalRead(5);
  orange = !digitalRead(6);
  fret_up = !digitalRead(7);
  fret_down = !digitalRead(8);
  start_ = !digitalRead(9);
  select = !digitalRead(10);
  thumb_y = analogRead(A0);
  thumb_x = analogRead(A1);
  whammy = analogRead(A2);

  if(start_ && select && !analog)
  {
    while(!digitalRead(9) && !digitalRead(10))
    {
      Serial.print("analog = ");
      Serial.println(analog);
    }
    analog = true;
    delay(100);
  }
  else if(start_ && select && analog)
  {
    while(!digitalRead(9) && !digitalRead(10))
    {
      Serial.print("analog = ");
      Serial.println(analog);
    }
    analog = false;
    delay(100);
  }
  
  if(analog)
  {
    Serial.print(thumb_y);
    Serial.print(" ");
    Serial.print(thumb_x);
    Serial.print(" ");
    Serial.print(whammy);
    Serial.println(" ");
  }
  else
  {
    if(green)
    {
      Serial.print("Green ");
    }
    if(red)
    {
      Serial.print("Red ");
    }
    if(yellow)
    {
      Serial.print("Yellow ");
    }
    if(blue)
    {
      Serial.print("Blue ");
    }
    if(orange)
    {
      Serial.print("Orange ");
    }
    if(fret_up)
    {
      Serial.print("Fret_Up ");
    }
    if(fret_down)
    {
      Serial.print("Fret_Down ");
    }
    if(select)
    {
      Serial.print("Select ");
    }
    if(start_)
    {
      Serial.print("Start ");
    }
    Serial.println();
  }
}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);  // Release key  
  delay(500);
}
