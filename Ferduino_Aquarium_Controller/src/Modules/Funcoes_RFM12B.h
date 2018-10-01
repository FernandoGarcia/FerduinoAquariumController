#ifdef RFM12B_LED_CONTROL
void RF_LED()
{
  theData_led.channel_white = wled_out;
  theData_led.channel_blue = bled_out;
  theData_led.channel_royalBlue = rbled_out;
  theData_led.channel_red = rled_out;
  theData_led.channel_violet = uvled_out;
  theData_led.channel_moon = moonled_out;

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
#endif

#ifdef RFM12B_RELAY_CONTROL
void RF_RELAY()
{
  int pins_status [16];

  for (byte i = 0; i < 16; i++)
  {
    //pins_status[i] = int(PCF8575.digitalRead(i));
#ifdef DEBUG
    Serial.println(PCF8575.digitalRead(i) ? "HIGH" : "LOW");
#endif
    pins_status[i] *= 255;
  }

  theData_relay.relay_0 = pins_status[0];
  theData_relay.relay_1 = pins_status[1];
  theData_relay.relay_2 = pins_status[2];
  theData_relay.relay_3 = pins_status[3];
  theData_relay.relay_4 = pins_status[4];
  theData_relay.relay_5 = pins_status[5];
  theData_relay.relay_6 = pins_status[6];
  theData_relay.relay_7 = pins_status[7];
  theData_relay.relay_8 = pins_status[8];
  theData_relay.relay_9 = pins_status[9];
  theData_relay.relay_10 = pins_status[10];
  theData_relay.relay_11 = pins_status[11];
  theData_relay.relay_12 = pins_status[12];
  theData_relay.relay_13 = pins_status[13];
  theData_relay.relay_14 = pins_status[14];
  theData_relay.relay_15 = pins_status[15];

#ifdef DEBUG
  Serial.print(F("Sending command to relay ("));
  Serial.print(sizeof(theData_relay));
  Serial.print(F(" bytes)."));
#endif
  //requestACK_RELAY = !requestACK_RELAY; //request every other time

  radio.Send(TARGET_ID_RELAY, (const void*)(&theData_relay), sizeof(theData_relay), requestACK_RELAY);
  if (requestACK_RELAY)
  {
#ifdef DEBUG
    Serial.print(F(" - Waiting for ACK..."));
#endif
    if (waitForAck(TARGET_ID_RELAY))
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
#endif

#if defined(RFM12B_LED_CONTROL) || defined(RFM12B_RELAY_CONTROL)
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
#endif
