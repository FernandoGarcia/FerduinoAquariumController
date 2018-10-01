void wifiCb(void* response)
{
  ELClientResponse *res = (ELClientResponse*)response;
  if (res->argc() == 1)
  {
    uint8_t status;
    res->popArg(&status, 1);

    if (status == STATION_GOT_IP)
    {
      LOGLN(F("WIFI connected!"));
    }
    else
    {
      MQTT_connected = false;
      LOGLN(F("Can't connect to WIFI network!"));
    }
  }
}

void mqttConnected(void* response)
{
  char SUB_TOPIC[50];
  strcpy(SUB_TOPIC, Username);
  strcat(SUB_TOPIC, "/");
  strcat(SUB_TOPIC, APIKEY);
  strcat(SUB_TOPIC, "/topic/command");

  LOGLN(F("MQTT connected!"));
  LOG(F("Command: ")); // Responde aos comandos
  LOGLN(SUB_TOPIC);

  MQTT.subscribe(SUB_TOPIC);
  MQTT_connected = true;
}

void mqttDisconnected(void* response)
{
  LOGLN(F("MQTT disconnected"));
  MQTT_connected = false;
}

void sincronizar()
{
  boolean ok = false;
  byte i = 0;

  LOGLN(F("Syncing Arduino and ESP8266..."));

  while ((ok == false) && (i < 10))
  {
    ok = ESP8266.Sync();
    if (!ok)
    {
      LOGLN(F("Sync failed!"));
      i++;
    }
  }
  if (ok == true)
  {
    LOGLN(F("Synced!"));
    MQTT.connectedCb.attach(mqttConnected);
    MQTT.disconnectedCb.attach(mqttDisconnected);
    MQTT.dataCb.attach(mqttData);
    MQTT.setup();
  }
  else
  {
    MQTT_connected = false;
  }
}
