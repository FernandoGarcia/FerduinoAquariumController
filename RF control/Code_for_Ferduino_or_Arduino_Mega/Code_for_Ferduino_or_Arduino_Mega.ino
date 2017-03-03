
// Uncomment the line below if you have the  SD card on ethernet shield.
//#define USE_PIN_4_FOR_SD_CARD // Descomente esta linha se você tem o cartão SD conectado no "ethernet shield".

// Uncomment the line below if you have the  SD card on TFT
// Do not uncomment this line when using Ferduino Mega 2560
//#define USE_PIN_53_FOR_SD_CARD // Descomente esta linha se você tem o cartão SD conectado no TFT. Não descomente esta linha se estiver usando um Ferduino Mega 2560

#define DEBUG // Comente esta linha para usar os pinos 0 e 1 para controle dos coolers e buzzer.

#include <RFM12B.h>

RFM12B radio;
#define MY_ID      99                   // ID deste dispositivo
#define NETWORK_ID   100                // Todos os dispositivos devem estar na mesma rede.
#define TARGET_ID_LED   1               // 1 = ID do dispositivos que receberá a informação
#define FREQUENCY   RF12_915MHZ         // Frequência de operação do rádio.
#define KEY         "thisIsEncryptKey"  // Esta senha deve ter exatamente 16 caracteres.
#define ACK_TIME    200
const byte limite_sem_resposta = 4;     // Reseta o controlador após 4 envios sem resposta. Para desabilitar esta função altere o valor para 0 (ZERO).
unsigned long lastPeriod_millis = 0;
boolean requestACK_LED = false;         // true = Solicitar uma resposta do dispositivo que recebe a informação
byte nothing = 0;

// Values for test purpose
byte bled_out = 255;
byte wled_out = 255;
byte rbled_out = 255;
byte rled_out = 255;
byte uvled_out = 255;
byte moonled_out = 255;

boolean value;

typedef struct {
  int  nodeId;
  byte channel_white;
  byte channel_blue;
  byte channel_royalBlue;
  byte channel_red;
  byte channel_violet;
  byte channel_moon;
  byte channel_6;  // canal extra
  byte channel_7;  // canal extra
  byte channel_8;  // canal extra
  byte channel_9;  // canal extra
  byte channel_10; // canal extra
  byte channel_11; // canal extra
  byte channel_12; // canal extra
  byte channel_13; // canal extra
  byte channel_14; // canal extra
  byte channel_15; // canal extra
}
Payload_led;
Payload_led theData_led  = {MY_ID, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};

const byte SD_CARD = 0;
const byte ETHER_CARD = 1;
const byte RFM = 2;

#if defined USE_PIN_4_FOR_SD_CARD // Do not change this line
  const byte ChipSelect_SD = 4; // Para cartão SD conectado no "ethernet shield".
#elif defined USE_PIN_53_FOR_SD_CARD // Do not change this line
  const byte ChipSelect_SD = 53; // Para cartão SD conectado no TFT.
#else // Do not change this line
  const byte ChipSelect_SD = 5; // Para o Ferduino Mega 2560
#endif // Do not change this line

#ifdef USE_PIN_53_FOR_SD_CARD // Do not change this line
  const byte SelectSlave_ETH = 4;
#else // Do not change this line
  const byte SelectSlave_ETH = 53;
#endif // Do not change this line

const byte ChipSelect_RFM = 69; // A15

void RF_LED()
{
  theData_led.channel_white = wled_out * value;
  theData_led.channel_blue = bled_out * value;
  theData_led.channel_royalBlue = rbled_out * value;
  theData_led.channel_red = rled_out * value;
  theData_led.channel_violet = uvled_out * value;
  theData_led.channel_moon = moonled_out * value;

  value = !value;

#ifdef DEBUG
  Serial.print(F("Sending command to LED ("));
  Serial.print(sizeof(theData_led));
  Serial.print(F(" bytes)."));
#endif
  //requestACK_LED = !requestACK_LED; //request every other time

  radio.Send(TARGET_ID_LED, (const void*)(&theData_led), sizeof(theData_led), requestACK_LED);
  if (requestACK_LED)
  {
#ifdef DEBUG
    Serial.print(F(" - Waiting for ACK..."));
#endif
    if (waitForAck(TARGET_ID_LED))
    {
#ifdef DEBUG
      Serial.print(F("OK!"));
#endif
    }
    else
    {
#ifdef DEBUG
      Serial.print(F(" Nothing."));
#endif
      nothing++;

      if (nothing == limite_sem_resposta)
      {
#ifdef DEBUG
        Serial.println();
        Serial.print(F("Resetting"));
#endif
        delay(9000);
      }
    }
  }
#ifdef DEBUG
  Serial.println();
#endif
}

// wait a few milliseconds for proper ACK to me, return true if indeed received
static bool waitForAck(byte theNodeID)
{
  unsigned long now = millis();
  while (millis() - now <= ACK_TIME)
  {
    if (radio.ACKReceived(theNodeID))
    {
      return true;
    }
  }
  return false;
}

void selecionar_SPI(int dispositivo)
{
  switch (dispositivo)
  {
    case 0: // Utilizar cartão sd.
      digitalWrite(ChipSelect_SD, LOW);
      digitalWrite(SelectSlave_ETH, HIGH);
      digitalWrite(ChipSelect_RFM, HIGH);
      delay(10);
      break;

    case 1: // Utilizar ethercard
      digitalWrite(SelectSlave_ETH, LOW);
      digitalWrite(ChipSelect_SD, HIGH);
      digitalWrite(ChipSelect_RFM, HIGH);
      delay(10);
      break;

    case 2: // Utilizar RFM12B
      digitalWrite(ChipSelect_RFM, LOW);
      digitalWrite(SelectSlave_ETH, HIGH);
      digitalWrite(ChipSelect_SD, HIGH);
      delay(10);
      break;
  }
  return;
}

void setup()
{
#ifdef DEBUG //Do not change this line
  Serial.begin(38400); // Inicia a comunicação com a  porta serial 0 para obter mensagens de depuração.
  Serial.flush();
  Serial.println();
#endif

  pinMode(SelectSlave_ETH, OUTPUT);
  pinMode (ChipSelect_SD, OUTPUT);
  pinMode(ChipSelect_RFM, OUTPUT);

  selecionar_SPI(RFM);                      // Seleciona disposito SPI que será utilizado.
  radio.Initialize(MY_ID, FREQUENCY, NETWORK_ID);
  radio.Encrypt((byte*)KEY);

  char buff[50];
#ifdef DEBUG //Do not change this line
  sprintf(buff, "\nTransmitting at %d Mhz...", FREQUENCY == RF12_433MHZ ? 433 : FREQUENCY == RF12_868MHZ ? 868 : 915);
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

    selecionar_SPI(RFM); // Seleciona disposito SPI que será utilizado.
    RF_LED();
    lastPeriod_millis = millis();
  }

  if (radio.ReceiveComplete())
  {
    if (radio.CRCPass())
    {
      Serial.print('[');
      Serial.print(radio.GetSender(), DEC);
      Serial.print("] ");
      for (byte i = 0; i < *radio.DataLen; i++)
      {
        Serial.print((char)radio.Data[i]);
      }

      if (radio.ACKRequested())
      {
        radio.SendACK();
        Serial.print(" - ACK sent.");
      }
    }
  }
}
