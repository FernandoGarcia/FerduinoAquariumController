#ifdef ETHERNET_SHIELD // Do not change this line

#ifdef USE_ESP8266 // Do not change this line

void wifiCb(void* response)
{
  ELClientResponse *res = (ELClientResponse*)response;
  if (res->argc() == 1)
  {
    uint8_t status;
    res->popArg(&status, 1);

    if (status == STATION_GOT_IP)
    {
      Serial.println(F("WIFI connected!"));
    }
    else
    {
      MQTT_connected = false;
#ifdef DEBUG
      Serial.println(F("Can't connect to WIFI network!"));
#endif
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

#ifdef DEBUG
  Serial.println(F("MQTT connected!"));
  Serial.print(F("Command: ")); // Responde aos comandos
  Serial.println(SUB_TOPIC);
#endif
  MQTT.subscribe(SUB_TOPIC);
  MQTT_connected = true;
}

void mqttDisconnected(void* response)
{
#ifdef DEBUG
  Serial.println(F("MQTT disconnected"));
#endif
  MQTT_connected = false;
}

void sincronizar()
{
  boolean ok = false;
  byte i = 0;

#ifdef DEBUG
  Serial.println(F("Syncing Arduino and ESP8266..."));
#endif

  while ((ok == false) && (i < 10))
  {
    ok = ESP8266.Sync();
    if (!ok)
    {
#ifdef DEBUG
      Serial.println(F("Sync failed!"));
#endif
      i++;
    }
  }
  if (ok == true)
  {
#ifdef DEBUG
    Serial.println(F("Synced!"));
#endif
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
#endif // Do not change this line

#endif // Do not change this line
