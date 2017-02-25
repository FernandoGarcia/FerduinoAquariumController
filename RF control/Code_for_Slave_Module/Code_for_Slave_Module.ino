#include <RFM12B.h>

#define DEBUG

#define MY_ID      1 // ID of this slave module
#define NETWORKID   100 // All devices should be in this network
#define FREQUENCY   RF12_915MHZ // Match this with the version of your RFM12B! (others: RF69_433MHZ, RF69_868MHZ)
#define KEY         "thisIsEncryptKey" // Has to be same 16 characters/bytes on all nodes, not more not less!
#define CS_FOR_FLASH_MEMORY_ON_MODULE 5 // ChipSelect of flash memory on board

// PWM pins on ATmega328
const byte ledPinUV = 3;         // Pin for UV LED
const byte ledPinBlue = 5;       // Pin for blue LED
const byte ledPinWhite = 6;      // Pin for white LED
const byte ledPinRoyBlue = 9;    // Pin for royal blue LED
const byte ledPinRed = 10;       // Pin for red LED
const byte ledPinMoon = 11;      // Pin moonlight

#define LED         13 // LED for debug
#define SERIAL_BAUD 115200
#define ACK_TIME    30  // # of ms to wait for an ack

unsigned long lastPeriod_millis = 0;

RFM12B radio;

typedef struct {
  int  nodeId;
  byte channel_white;
  byte channel_blue;
  byte channel_royalBlue;
  byte channel_red;
  byte channel_violet;
  byte channel_moon;
  byte channel_6;   // Extra channel
  byte channel_7;   // Extra channel
  byte channel_8;   // Extra channel
  byte channel_9;   // Extra channel
  byte channel_10;  // Extra channel
  byte channel_11;  // Extra channel
  byte channel_12;  // Extra channel
  byte channel_13;  // Extra channel
  byte channel_14;  // Extra channel
  byte channel_15;  // Extra channel
}
Payload;
Payload theData;

void setup()
{
#ifdef DEBUG
  Serial.begin(SERIAL_BAUD);
#endif

  pinMode(LED, OUTPUT); // pin 13

  pinMode(ledPinUV, OUTPUT);               // Pin 3;
  pinMode(ledPinBlue, OUTPUT);             // Pin 5;
  pinMode(ledPinWhite, OUTPUT);            // Pin 6;
  pinMode(ledPinRoyBlue, OUTPUT);          // Pin 9;
  pinMode(ledPinRed, OUTPUT);              // Pin 10;
  pinMode(ledPinMoon, OUTPUT);             // Pin 10;

  pinMode(CS_FOR_FLASH_MEMORY_ON_MODULE, OUTPUT);
  digitalWrite(CS_FOR_FLASH_MEMORY_ON_MODULE, HIGH);


  radio.Initialize(MY_ID, FREQUENCY, NETWORKID);
  radio.Encrypt((byte*)KEY);

#ifdef DEBUG
  char buff[50];
  sprintf(buff, "\nListening at %d Mhz...", FREQUENCY == RF12_433MHZ ? 433 : FREQUENCY == RF12_868MHZ ? 868 : 915);
  Serial.println(buff);
#endif
}

void loop()
{
  if ((millis() - lastPeriod_millis) > 5000)
  {
#ifdef DEBUG //Do not change this line
    Serial.print("Running: ");
    Serial.println(millis() / 1000);
#endif
    lastPeriod_millis = millis();
  }

  if (radio.ReceiveComplete())
  {
    if (radio.CRCPass())
    {
#ifdef DEBUG
      Serial.print('[');
      Serial.print(radio.GetSender(), DEC);
      Serial.print("] ");
#endif
      if (*radio.DataLen != sizeof(Payload))
      {
#ifdef DEBUG
        Serial.print("Invalid payload received, not matching Payload struct!");
#endif
      }
      else
      {
        theData = *(Payload*)radio.Data; //assume radio.DATA actually contains our struct and not something else
        analogWrite(ledPinUV, theData.channel_violet);
        analogWrite(ledPinBlue, theData.channel_blue);
        analogWrite(ledPinWhite, theData.channel_white);
        analogWrite(ledPinRoyBlue, theData.channel_royalBlue);
        analogWrite(ledPinRed, theData.channel_red);
        analogWrite(ledPinMoon, theData.channel_moon);
#ifdef DEBUG
        Serial.print(" Master ID = ");
        Serial.print(theData.nodeId);
        Serial.print(" UV = ");
        Serial.print(theData.channel_violet);
        Serial.print(" Blue = ");
        Serial.print(theData.channel_blue);
        Serial.print(" White = ");
        Serial.print(theData.channel_white);
        Serial.print(" Royal blue = ");
        Serial.print(theData.channel_royalBlue);
        Serial.print(" Red = ");
        Serial.print(theData.channel_red);
        Serial.print(" Moon = ");
        Serial.print(theData.channel_moon);
#endif
        Blink(LED, 5);
      }

      if (radio.ACKRequested())
      {
        byte theNodeID = radio.GetSender();
        radio.SendACK();
        //when a node requests an ACK, respond to the ACK and also send a packet requesting an ACK
        //This way both TX/RX NODE functions are tested on 1 end at the GATEWAY

#ifdef DEBUG
        Serial.print(" - ACK sent. Sending packet to node ");
        Serial.print(theNodeID);
#endif
        delay(10);
        radio.Send(theNodeID, "ACK TEST", 8, true);

#ifdef DEBUG
        Serial.print(" - waiting for ACK...");
#endif

        if (waitForAck(theNodeID))
        {
#ifdef DEBUG
          Serial.print("ok!");
#endif
        }
        else
        {
#ifdef DEBUG
          Serial.print("nothing...");
#endif
        }
      }
#ifdef DEBUG
      Serial.println();
#endif
    }
  }
}

void Blink(byte PIN, int DELAY_MS)
{
  digitalWrite(PIN, HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN, LOW);
}

// wait a few milliseconds for proper ACK to me, return true if indeed received
static bool waitForAck(byte theNodeID)
{
  long now = millis();

  while (millis() - now <= ACK_TIME)
  {
    if (radio.ACKReceived(theNodeID))
    {
      return true;
    }
  }
  return false;
}

