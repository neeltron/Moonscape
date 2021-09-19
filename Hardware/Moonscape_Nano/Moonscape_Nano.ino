#define BAUDRATE 57600
#define DEBUGOUTPUT 0
#define powercontrol 10

byte generatedChecksum = 0;
byte checksum = 0;
int payloadLength = 0;
byte payloadData[64] = {0};
byte poorQuality = 0;
byte attention = 0;
byte meditation = 0;
long lastReceivedPacket = 0;
boolean bigPacket = false;
void setup()
{
  Serial.begin(BAUDRATE);
}
byte ReadOneByte()
{
  int ByteRead;
  while (!Serial.available());
  ByteRead = Serial.read();
#if DEBUGOUTPUT
  Serial.print((char)ByteRead);
#endif
  return ByteRead;
}
void loop()

{
  if (ReadOneByte() == 170)
  {
    if (ReadOneByte() == 170)
    {
      payloadLength = ReadOneByte();
      if (payloadLength > 169)
        return;
      generatedChecksum = 0;
      for (int i = 0; i < payloadLength; i++)
      {
        payloadData[i] = ReadOneByte();
        generatedChecksum += payloadData[i];
      }
      checksum = ReadOneByte();
      generatedChecksum = 255 - generatedChecksum;
      if (checksum == generatedChecksum)
      {
        poorQuality = 200;
        attention = payloadData[4];
        meditation = payloadData[5];
      #if !DEBUGOUTPUT
        if (bigPacket)
        {
          Serial.print(meditation, DEC);
          lastReceivedPacket = millis();
          Serial.print("\n");
        }
      #endif
        bigPacket = false;
      }
      else {
      } 
    } 
  }
}