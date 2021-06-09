/*
 #if defined() && defined()
 #error ""
 #endif
 */

#if defined(USE_ETHERNET_SHIELD) && defined(USE_ESP8266)
  #error "You can't enable ethernet shield and ESP8266 at same time."
#endif

#if defined(STAMPS_EZO) && defined(STAMPS_V4X)
  #error "You can't select two stamps model at same time."
#endif

#if defined(USE_PIN_4_FOR_SD_CARD) && defined(USE_PIN_53_FOR_SD_CARD)
  #error "You can't select pin 4 and 53 for SD card at same time."
#endif