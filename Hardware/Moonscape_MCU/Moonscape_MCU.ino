#include <SoftwareSerial.h>
SoftwareSerial s(D6, D5);
void setup()
{
  s.begin(57600);
  Serial.begin(57600);
}
void loop()
{
  int data = s.read();
  if (data != -1) {
    Serial.println(data);
  }
}
