#pragma once // Do not change this line!
// *************************************************************************************************
// *************** Bibliotecas utilizadas **********************************************************
// *************************************************************************************************
#ifdef USE_TFT // Do not change this line
 #include <UTFT.h>
 #include <URTouch.h>
#endif // Do not change this line
#include <Wire.h>
#include <EEPROM.h>
#include <writeAnything.h>
#include <rtc_ds.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SdFat.h>
#include <FreeStack.h>
#include <avr/pgmspace.h>
#include <PCF8575.h>

#if defined(RFM12B_LED_CONTROL) || defined(RFM12B_RELAY_CONTROL) // Do not change this line!
 #include <RFM12B.h>
#endif // Do not change this line!

#ifdef ETHERNET_SHIELD // Do not change this line!
 #ifndef USE_ESP8266   // Do not change this line!
  #include <SPI.h>
  #include <Ethernet.h>
  #include <PubSubClient.h>
 #else  // Do not change this line!
  #include <ELClient.h>
  #include <ELClientMqtt.h>
 #endif // Do not change this line!
 #include <ArduinoJson.h>
#endif  // Do not change this line!

#ifdef WATCHDOG // Do not change this line!
 #include <avr/wdt.h>
#endif // Do not change this line!
