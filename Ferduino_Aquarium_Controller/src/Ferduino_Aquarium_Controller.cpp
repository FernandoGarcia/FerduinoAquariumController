// *************************************************************************************************
// ****************************** Variáveis ********************************************************
// *************************************************************************************************
#include "Ferduino_Aquarium_Controller.h"

// *************************************************************************************************
// ****************************** Protótipos de funções ********************************************
// *************************************************************************************************
double MyNormalize(double v);
void setFont(bool font, byte cr, byte cg, byte cb, byte br, byte bg, byte bb);
void drawFillRect(int x1, byte y1, int x2, byte y2, byte r, byte g, byte b);
void selecionar_SPI(int dispositivo);
void checkTempoRampa();
void checkNuvens();
void aguardeIntervalo();
void checkRelampago();
void executeRelampago(byte i);
void checkRampaNuvem();
int LedToPercent(int Led_out);
void config_valores_timers_temp();
void config_valores_salvar_timers();
int check(byte *pt1, byte *pt2, int lstep);
byte validateDate(byte d, byte m, word y);
byte calcDOW(byte d, byte m, int y);
byte validateDateForMonth(byte d, byte m, word y);
void updateStr(int val);
void Open_channel(short channel);
void start_ethernet();
void configPins();
void requestAction(char *topic, byte *payload, unsigned int length);
void mqttData(void *response);
static bool waitForAck(byte theNodeID);
int dosage_interval();
void sincronizar();

// *************************************************************************************************
// ****************************** Módulos **********************************************************
// *************************************************************************************************
#ifdef USE_TFT
  #if defined ENGLISH // Do not this lines
    #include "Language/English.h"
  #elif defined FRENCH
    #include "Language/French.h"
  #elif defined GERMAN
    #include "Language/German.h"
  #elif defined ITALIAN
    #include "Language/Italian.h"
  #elif defined PORTUGUESE
    #include "Language/Portuguese.h"
  #elif defined SPANISH
    #include "Language/Spanish.h"
  #endif
#endif

#include "Modules/Botoes_e_etc.h"
#include "Modules/Alimentador_automatico.h"
#include "Modules/Clima.h"
#include "Modules/Dosadoras.h"
#include "Modules/Fases_da_lua.h"
#include "Modules/Funcoes_EEPROM.h"

#if defined(RFM12B_LED_CONTROL) || defined(RFM12B_RELAY_CONTROL)
  #include "Modules/Funcoes_RFM12B.h"
#endif

#include "Modules/Funcoes_SPI.h"
#include "Modules/Grava_Sd_card.h"
#include "Modules/Leds.h"
#include "Modules/Parametros.h"

#ifdef USE_TFT
  #include "Modules/Menus.h"
  #include "Modules/Graficos.h"
  #include "Modules/Senha.h"
  #include "Modules/Inicio.h"
  #include "Modules/ProcessMyTouch.h"
#endif

#if defined(USE_ETHERNET_SHIELD) || defined(USE_ESP8266)
  #include "Modules/Webserver.h"
#endif

#ifdef USE_ESP8266
  #include "Modules/Funcoes_ESP8266.h"
#endif

#include "Modules/Stamps_EZO.h"
#include "Modules/Stamps_V4.h"
#include "Modules/Temporizadores.h"
#include "Modules/Troca_de_agua.h"
#include "Modules/Wavemaker.h"
#include "Modules/Setup.h"
#include "Modules/Loop.h"
