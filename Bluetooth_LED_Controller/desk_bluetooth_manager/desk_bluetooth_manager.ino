// GLOBAL VARIABLES 
byte serial_data[10];

void setup() 
{
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(10);
}

void loop() 
{
  Serial.readBytes(serial_data, 10);
  
  if(serial_data[0] != 0)
  {
    digitalWrite(2, HIGH);
    delay(100);
    Serial.write(serial_data,sizeof(serial_data));
    digitalWrite(2, LOW);
  }
  memset(serial_data, 0, sizeof(serial_data));
}
