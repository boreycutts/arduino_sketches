int PWM = 3;
int x = 0;
bool initialized = false;

void setup() 
{
  pinMode(PWM, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  analogWrite(PWM, voltageToAnalog(1.5));
  digitalWrite(5, LOW);

  if (!initialized)
  {
    analogWrite(PWM, voltageToAnalog(0));
    delay(2000);
    analogWrite(PWM, voltageToAnalog(3));
    delay(2000);
    initialized = true;
    
    Serial.println("Initialized");   
  }
  
  analogWrite(PWM, voltageToAnalog(1.5));

  delay(3000);

  droneOn();

  analogWrite(PWM, voltageToAnalog(3));

  delay(4000);

  droneOff();
}

void loop() 
{
  
}

int voltageToAnalog(int voltage)
{
  //If the voltage is in range of the micro's limit
  if(voltage <= 3 && voltage >= 0)
  {
    return voltage*160/3;
  }
  else
  {
    //return 1.5V
    return 80;
  }
}

void droneOn()
{
  digitalWrite(5, HIGH);
  delay(1000);
  digitalWrite(5, LOW);
  
  Serial.println("Drone On");
}

void droneOff()
{
  digitalWrite(5, HIGH);
  delay(5000);
  digitalWrite(5, LOW);

  Serial.println("Drone Off");
}

