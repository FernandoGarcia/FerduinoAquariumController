#include <ELClient.h>
#include <ELClientMqtt.h>
#include <NeoSWSerial.h>

NeoSWSerial virtualPort (A8, A7);  // RX, TX

const char *Username  = "FernandoGarcia";
const char *APIKEY = "2e4e116a";

// Initialize a connection to esp-link using the normal hardware serial port both for
// SLIP and for debug messages.
ELClient ESP8266(&virtualPort);
ELClientMqtt MQTT(&ESP8266);

unsigned long last_millis;

boolean connected = false;

// Callback made from esp-link to notify of wifi status changes
// Here we just print something out for grins
void wifiCb(void* response)
{

  ELClientResponse *res = (ELClientResponse*)response;
  if (res->argc() == 1)
  {
    uint8_t status;
    res->popArg(&status, 1);

    if (status == STATION_GOT_IP)
    {
      Serial.println("WIFI connected!");
      Serial.println("");
    }
    else
    {
      Serial.println("Cant' connect to WIFI network!");
      connected = false;
    }
  }
}

// Callback when MQTT is connected
void mqttConnected(void* response)
{
  char SUB_TOPIC[50];
  char CLIENT_ID[20];

  Serial.println("MQTT connected!");

  strcpy(SUB_TOPIC, Username);
  strcat(SUB_TOPIC, "/");
  strcat(SUB_TOPIC, APIKEY);
  strcat(SUB_TOPIC, "/topic/command");

  strcpy(CLIENT_ID, "ID: ");
  strcat(CLIENT_ID, Username);

  Serial.print(F("Command: "));
  Serial.println(SUB_TOPIC);

  MQTT.subscribe(SUB_TOPIC);
  connected = true;
}

// Callback when MQTT is disconnected
void mqttDisconnected(void* response)
{
  Serial.println("MQTT disconnected");
  connected = false;
}

// Callback when an MQTT message arrives for one of our subscriptions
void mqttData(void* response)
{
  ELClientResponse *res = (ELClientResponse *)response;

  //Serial.print("Topic: ");
  String topic = res->popString();
  //Serial.println(topic);

  Serial.print("Message: ");
  String message = res->popString();
  Serial.println(message);
}

void resetCb()
{
  boolean ok = false;
  byte i = 0;

  Serial.println("Syncing or resyncing Arduino and ESP8266...");

  while ((ok == false) && (i < 10))
  {
    ok = ESP8266.Sync();
    if (!ok)
    {
      Serial.println("Sync failed!");
      i++;
    }
  }
  if (ok == true)
  {

    Serial.println("Synced!");

    MQTT.connectedCb.attach(mqttConnected);
    MQTT.disconnectedCb.attach(mqttDisconnected);
    MQTT.dataCb.attach(mqttData);
    MQTT.setup();
  }
}

void setup()
{
  Serial.begin(38400);
  virtualPort.begin(9600);

  while (!Serial)
  {
    ; // Nothing to do. :)
  }
  Serial.flush();
  Serial.println();
  Serial.println("Setup...");

  ESP8266.wifiCb.attach(wifiCb);
  resetCb();
}

void loop()
{
  ESP8266.Process();

  char PUB_TOPIC[50];

  if ((connected == true) && ((millis() - last_millis) > 5000))
  {
    strcpy(PUB_TOPIC, Username);
    strcat(PUB_TOPIC, "/");
    strcat(PUB_TOPIC, APIKEY);
    strcat(PUB_TOPIC, "/topic/response");

    Serial.print(F("Response: "));
    Serial.println(PUB_TOPIC);
    Serial.println("Publishing...");
    char buf[12];

    itoa(millis() / 1000, buf, 10);
    MQTT.publish(PUB_TOPIC, buf);
    Serial.println("Published!");
    last_millis = millis();
  }
}
