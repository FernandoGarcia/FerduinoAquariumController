#include <SdFat.h>

//const byte SelectSlave_SD = 4; // For ethernet shield
const byte SelectSlave_SD = 5;   // For Ferduino Mega 2560
const byte SelectSlave_RFM = 69;   // For Ferduino Mega 2560
const byte SelectSlave_ETH = 53;   // For Ferduino Mega 2560

SdFat SD;
SdFile file;


float temp;
float tempe;

void setup()
{
  int16_t n;
  char buf[8];

  pinMode(SelectSlave_RFM, OUTPUT);
  pinMode(SelectSlave_ETH, OUTPUT);
  digitalWrite(SelectSlave_RFM, HIGH);
  digitalWrite(SelectSlave_ETH, HIGH);
  
  Serial.begin(9600);

  SD.begin(SelectSlave_SD, SPI_HALF_SPEED);

  while(!Serial)
  {
    ; // wait for serial.
  }

  if(file.open("LOGTDIA.TXT", O_CREAT | O_APPEND | O_WRITE))
  {
    Serial.println("Writing...");
    Serial.println();

    for(temp = 27.5; temp > 22.0; temp -= 0.15)
    {
      file.print(temp);
      file.write((uint8_t*)"\0", 1);
      file.write((uint8_t*)"\r\n", 2);
    }

    for(tempe = 22.5; tempe < 28.0; tempe += 0.15)
    {
      file.print(tempe);
      file.write((uint8_t*)"\0", 1);
      file.write((uint8_t*)"\r\n", 2);
    }
    file.close();
    Serial.println("Done!");
    Serial.println();
  }
  else
  {
    Serial.println("Can't open.");
  }

  if(file.open("LOGTDIA.TXT", O_READ))
  {
    Serial.println("Reading...");
    Serial.println();
    delay(5000);
    while ((n = file.read(buf, sizeof(buf))) > 0)
    {
      Serial.println(buf);
    }
    file.close();
    Serial.println();
    Serial.print("Finished!");
  }
}
void loop()
{
}

