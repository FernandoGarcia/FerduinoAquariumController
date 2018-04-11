///*****************************************************************************************************************************************************
//......................................................................................................................................................
//...............           .           ...           .....         . .....     ..... .   ...     ...     .....     .....           ....................
//..............                                       ...             . .       ....      .       .         .       ...     ...     . .................
//.............  2@B@B@B@B@.  @B@B@B@B@B,  N@B@B@@@BN:  . iB@B@B@@@B5:     .@@@i .... vB@@   .@B@i   N@B@B:   . OB@;  .  :qB@@@B@BM7   .................
//.............  ZB@BXqGZ8Z  .B@BMX00GGM.  BB@BXNZB@B@q   r@@@N00MB@B@B:   ,B@Br ...  L@B@   .B@B7   @B@B@B:    B@B7    8@B@M1JUO@B@B: .................
//.............  S@BO         @B@.         G@Bk    j@B@.  iB@B     ,@B@B.  .@B@:  ... vB@B   .@B@i   O@@YB@B.   M@@i   B@B@.      BB@B  ................
//.............  XB@O         @@B:         8B@F    J@@B   i@B@       @B@G  .B@Bi ...  7@B@   .B@Bi   MB@ rB@B   G@@i  r@B@,       .@B@v  ...............
//.............  F@B@q8OMB5   @B@B@B@@@,   Z@BBJ2UMB@B:   iB@@  . .  P@B@  .@B@i  ... vB@B   .@B@i   M@@, E@@B  GB@i  qB@B  .....  B@BN  ...............
//.............. kB@B@@@B@M   B@@8XZGOO.   8B@B@B@B@v     i@B@   .   qB@B  .B@B: ...  r@B@   .B@B;   MB@:  MB@G S@Bi  q@B@   ...   @B@k  ...............
//.............  S@BM         @B@,         Z@Bq  :@@@5    iB@B       B@BZ  .@B@:      7B@B   .@B@i   O@Bi   @B@7uB@i  uB@@.   .   ,@@B7 ................
//.............  kB@M      .  B@B:         8B@N   :@B@Y   i@@@      O@B@.   B@@0      M@BM   .B@B;   MB@i    @@@B@@i  .@B@G       B@B@   ...............
//.............  q@@@   ....  @B@Nju1UFk.  M@BM    1@B@:  rB@B2u1X@B@B@:    r@@B@Jrr2B@B@.   .@B@r   B@Br    ,@B@B@r   i@B@BS777NB@@@   ................
//.............. NB@B  ..... .B@B@B@B@@@:  MB@O  .  B@B@  i@B@B@B@B@q;   ..  ,P@B@B@B@Bu   . ,@@B7   @@@;  .  i@B@Bi     1B@B@B@B@O7   .................
//.............   ..  .......   . ... ..    ..  ...  ...   ..   .       ....    .:::,     ... ...     ..  ...   . .  ..     ,:::.     ..................
//..............     .........           .     .....     .           ....... .         . ....     ..     .....     .......         .....................
//................................... ................. ......... ............... . ........... ................. ........... . . ......................
//******************************************************************************************************************************************************
//***********************              Desenvolvido por Fernando Garcia         ************************************************************************
//******************************************************************************************************************************************************
//******* Dúvidas, sugestões e elogios: info@ferduino.com **********************************************************************************************
//******************************************************************************************************************************************************

// Este programa é compatível com a IDE 1.8.1

// As funções para controle via web foram implementadas graças à preciosa ajuda do Simone Grimaldi e Danilo Castellano.

//---------------------------------------------------------

// Este programa foi desenvolvido com base na versão Stilo 2.1
// Disponível nesta página http://code.google.com/p/stilo/

//-----------------------------------------------------------
// Este programa é software livre; Você pode redistribuí-lo e/ou
// modificá-lo sob os termos da GNU General Public License
// como publicada pela Free Software Foundation versão 3
// da licença, ou (por sua opção) qualquer versão posterior.
// Este programa é distribuído na esperança que seja útil,
// mas sem qualquer garantia; sem mesmo a garantia implícita de
// comercialização ou propósito particular. Consulte o
// GNU General Public License para mais detalhes.

//*************************************************************************************************
//*************** Selecionar idioma ***************************************************************
//*************************************************************************************************

// Descomente a linha correspondente ao seu idioma.
// Uncomment the line corresponding to your language.

//#define ENGLISH    // If this program is useful for you, make a donation to help with development. Paypal: fefegarcia_1@hotmail.com
//#define FRENCH     // Si ce programme est utile pour vous, faire un don pour aider au développement. Paypal: fefegarcia_1@hotmail.com
//#define GERMAN     // Wenn dieses Programm ist nützlich für Sie, eine Spende an mit Entwicklung zu helfen. Paypal: fefegarcia_1@hotmail.com
//#define ITALIAN    // Se questo programma vi è utile, fate una donazione per aiutare con il suo sviluppo. Paypal: fefegarcia_1@hotmail.com
#define PORTUGUESE   // Se este programa é útil para você, faça uma doação para ajudar no desenvolvimento. Paypal: fefegarcia_1@hotmail.com
//#define SPANISH    // Si este programa es útil para usted, hacer una donación para ayudar con el desarrollo. Paypal: fefegarcia_1@hotmail.com

//*************************************************************************************************
//**************************** ATIVAR OU DESATIVAR FUNÇÕES  ***************************************
//**************************** ENABLE OR DISABLE FUNCTIONS ****************************************
//*************************************************************************************************
// Comment the line below to disable watchdog
//#define WATCHDOG // Reseta o controlador se a função "wdt_reset()" não for executada em até 8 segundos.
// Essa função minimiza problemas com o travamento do código mas, pode apresentar incompatibilidades com alguns bootloaders

// Comment the line below to disable ethernet functions
#define ETHERNET_SHIELD // Comente esta linha para desativar as funções do ethernet shield.

// Uncomment the line bellow to use an ESP8266 as WIFI module
//#define USE_ESP8266 // Descomente esta linha para usar um ESP8266 como módulo WIFI.

// Comment this two lines below if have not stamps
// Comente as duas linhas abaixo se não tiver stamps
#define STAMPS_V4X     // Comente esta linha para usar Stamps EZO
//#define STAMPS_EZO     // Descomente esta linha para usar Stamps EZO

// Comment the line below if you haven't a stamp for tank pH.
#define USE_STAMP_FOR_TANK_PH // Comente esta linha se você não tem um "stamp" para o pH do aquário.

// Comment the line below if you haven't a stamp for calcium reactor.
#define USE_STAMP_FOR_CALCIUM_REACTOR // Comente esta linha se você não tem um "stamp" para o reator de cálcio.

// Comment the line below if you haven't a stamp for ORP.
#define USE_STAMP_FOR_ORP // Comente esta linha se você não tem um "stamp" para a ORP.

// Comment the line below if you haven't a stamp for density.
//#define USE_STAMP_FOR_DENSITY // Comente esta linha se você não tem um "stamp" para a densidade.

// Comment this two lines below if have not RFM12B wireless transceiver
//#define RFM12B_LED_CONTROL   // Descomente esta linha para controlar os LEDs via RF
//#define RFM12B_RELAY_CONTROL // Descomente esta linha  para controlar os relês via RF


// Comment the line below if have not a PCF8575
#define USE_PCF8575 // Descomente essa linha para usar um PCF8575

// Comente esta linha para desativar as mensagens no monitor serial ou para usar os pinos 0 e 1 (RX e TX) como OUTPUT
// Comment this line to disable the messages on serial monitor or to use pins 0 and 1 (RX e TX) as OUTPUT
#define DEBUG  // Comente esta linha para usar os pinos 0 e 1 para controle dos coolers e buzzer.

// Comment the line below to disable this function
// Comente a linha abaixo para desativar esta função
//#define DISABLE_SKIMMER // Desliga o skimmer caso o nível no compartimento esteja alto.
// Evita transbordamento do skimmer caso a bomba de retorno seja desligada

// Comment this line to enable password screen
// Comente esta linha para ativar a solicitação de senha.
//#define SKIP_PASSWORD_SCREEN // comente esta linha se deseja solicitar uma senha após o primeiro toque no TFT

// Comment this line to use static IP.
// Comente esta linha para usar IP estático
//#define USE_DHCP // Descomente esta linha para usar DHCP

// Uncomment the line below to use screensaver
// Descomente a linha abaixo para ativar o protetor de tela
//#define USE_SCREENSAVER

// Comment the line below to disable night mode for stream pumps
// Comente a linha abaixo para desativar o modo noturno para bombas de circulação.
#define NIGHT_MODE // Reduz a potência das bombas de circulação quando os LEDs estão desligados.

// Uncomment the line below to use temperature in Fahrenheit.
//#define USE_FAHRENHEIT // Descomente esta linha para usar temperatura em Fahrenheit

// Comment the line bellow if you don't want use a TFT. This function works only with IDE 1.6.7 or higher.
#define USE_TFT // Comente esta linha se você não quer usar um TFT. Estão função funciona apenas com a IDE 1.6.7 or higher.

// Uncomment the line below to use pins 18 and 19 for RTC and comment to use pins 20 and 21 for RTC.
#define USE_PINS_18_AND_19_FOR_RTC // Descomente esta linha para usar os pinos 18 e 19 para o RTC e comente para usar os pinos 20 e 21 para o RTC.

// Uncomment the line below if you are using a TFT shield.
//#define USE_TFT_SHIELD // Descomente esta linha se você estiver usando um "TFT shield".

// Uncomment the line below if you have the  SD card on ethernet shield.
//#define USE_PIN_4_FOR_SD_CARD // Descomente esta linha se você tem o cartão SD conectado no "ethernet shield".

// Uncomment the line below if you have the  SD card on TFT
// Do not uncomment this line when using Ferduino Mega 2560
//#define USE_PIN_53_FOR_SD_CARD // Descomente esta linha se você tem o cartão SD conectado no TFT. Não descomente esta linha se estiver usando um Ferduino Mega 2560

// Uncomment the line bellow if your touch screen have coordinates mirrored. So don't need change in ProcessMyTouch: x = 399-myTouch.getX () and y = 239-myTouch.getY ().
//#define INVERT_TOUCH // Descomente essa linha se seu "touch screen" tem as coordenadas espelhadas. Assim não será necessário alterar em "ProcessMyTouch": x = 399-myTouch.getX () and y = 239-myTouch.getY ().

// Uncomment the line below to enable an extra channel for lightning during the night.
//#define USE_EXTRA_CHANNEL_FOR_LIGHTNING_DURING_NIGHT // Descomente esta linha para utilizar um canal extra para relâmpagos durante a noite.

// Select the extra channel to be used for lightning during the night. 0 = white, 1 = blue, 2 = royal blue, 3 = red, 4 = UV
#define EXTRA_CHANNEL_FOR_LIGHTNING 0 // Selecione o canal extra para ser usado para relâmpagos noturnos. 0 = branco, 1 = azul, 2 = azul royal, 3 = vermelho, 4 = ultra violeta

// Define the minimum PWM value to clouds and lightning. If the current PWM is smaller than this value the effect won't be done over the channel.
// When the PWM is smaller than this value the clouds and lightnigs are considered nocturnal. So the lightning will use the extra channel if moon PWM is higher than this value.
#define MIN_PWM_NUVEM 30 // Define o valor mínimo de PWM para nuvens e relâmpagos. Se o PWM atual for menor que este valor o efeito não será executado sobre o canal. 
// Quando o PWM é menor que este valor as nuvens e relâmpagos são considereados noturnos. Então o relâmpago will usar o canal extra se o PWM lua for maior que este valor.

//*************************************************************************************************
//*************** Bibliotecas utilizadas **********************************************************
//*************************************************************************************************
#ifdef USE_TFT // Do not change this line
#include <UTFT.h>
#include <URTouch.h>
#endif // Do not change this line
#include <Wire.h>
#include <EEPROM.h>
#include <writeAnything.h>
#include <DS1307_HENNING.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <avr/pgmspace.h>

#ifdef USE_PCF8575 // Do not change this line!
#include <PCF8575.h>
#endif // Do not change this line!

#if defined(RFM12B_LED_CONTROL) || defined(RFM12B_RELAY_CONTROL) // Do not change this line!
#include <RFM12B.h>
#endif // Do not change this line!

#ifdef ETHERNET_SHIELD // Do not change this line!
#ifndef USE_ESP8266 // Do not change this line!
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#else // Do not change this line!
#include <ELClient.h>
#include <ELClientMqtt.h>
#include <NeoSWSerial.h>
#endif // Do not change this line!
#include <ArduinoJson.h>
#endif // Do not change this line!

#ifdef WATCHDOG // Do not change this line!
#include <avr/wdt.h>
#endif // Do not change this line!

//*************************************************************************************************
//************************* Atualizações **********************************************************
//*************************************************************************************************
const char lastUpdate[] = "11/04/2018"; // Data da última modificação

//****************************************************************************************************
//****************** Variáveis de textos e fontes ****************************************************
//****************************************************************************************************
#ifdef USE_TFT //Do not change this line
#define LARGE true
#define SMALL false
extern uint8_t RusFont1[];    // Declara que fontes vamos usar
extern uint8_t BigFont[];     // Declara que fontes vamos usar
#endif
char buffer[50];

#ifdef USE_SCREENSAVER //Do not change this line
extern uint8_t SevenSegNumFontPlus[];
#endif //Do not change this line

//****************************************************************************************************
//****************** Define funções dos pinos digitais e analógicos **********************************
//****************************************************************************************************
#define MAX_PIN_NUMBER 69 // Numero de pinos disponíveis no Arduino Mega.
// Pinos 0 e 1 reservados para a porta serial 0.
const byte alarmPin = 0;          // Pino que aciona o alarme
const byte desativarFanPin = 1;   // Pino que desativa os coolers.
// Pino 2 reservado para INT do RFM12B.
// Pinos 3, 4, 5, 6 e 7 reservados para o touch.
// Pino 5 também é o chip select do cartão SD.
const byte ledPinUV = 8;         // Pino que liga os leds violeta
const byte ledPinBlue = 9;       // Pino que liga os leds azuis
const byte ledPinWhite = 10;     // Pino que liga os leds brancos
const byte ledPinRoyBlue = 11;   // Pino que liga os leds "royal blue"
const byte ledPinRed = 12;       // Pino que liga os leds vermelho
const byte fanPin = 13;          // Pino que controla a velocidade das ventoinhas do dissipador
// Pinos 14 e 15 reservados para a porta serial 3 que se comunica com os "Stamps"
const byte multiplexadorS0Pin = 16; // Pino S0 de controle dos stamps
const byte multiplexadorS1Pin = 17; // Pino S1 de controle dos stamps
// Pinos 18 e 19 reservados para o RTC.
// Pinos 20 e 21 reservados para comunicação I2C do PCF8575.
// Pinos 22 à 41 reservados para o LCD.
const byte aquecedorPin = 42;   // Pino que liga o aquecedor
const byte chillerPin = 43;     // Pino que liga o chiller
const byte ledPinMoon = 44;     // Pino que liga os leds da luz noturna
const byte wavemaker1 = 45;     // Pino que controla o wavemaker 1
const byte wavemaker2 = 46;     // Pino que controla o wavemaker 2

//***************************************************************************************************
//***************************************************************************************************
// Os 2 pinos abaixo serão controlados pelo PCF8575 caso esteja usando um.
// Observe que estes pinos também estão declarados na seção PCF8575.
// Caso esteja usando um PCF8575 os pinos 47 e 48 estarão livres para ser usados em outras funções

// The 2 pins below will be controlled for PCF8575 if you have an installed.
// Notice that this pins also are declared in PCF8575 section.
// when using a PCF8575 the pins 47 and 48 will be free to be used in others functions.
//***************************************************************************************************
#ifndef USE_PCF8575 // Do not change this line!
const byte ozonizadorPin = 47;  // Pino que liga o ozonizador
const byte reatorPin = 48;      // Pino que liga o CO2 do reator.
#endif // Do not change this line!
//***************************************************************************************************
//***************************************************************************************************

const byte sensoresPin = 49;    // Pino que lê os sensores de temperatura
// Pinos 50, 51 e 52 reservados para comunicação SPI
// Pino 53 reservado para "select slave do ethernet shield.
const byte sensor1 = 54;   // A0;      // Pino analógico que verifica se há tensão na bóia da quarentena.
const byte sensor2 = 55;   // A1;      // Pino analógico que verifica se há tensão na bóia inferior do sump.
const byte sensor3 = 56;   // A2;      // Pino analógico que verifica se há tensão na bóia superior do sump.
const byte sensor4 = 57;   // A3;      // Pino analógico que verifica se há tensão na bóia inferior do reservatório.
const byte sensor5 = 58;   // A4;      // Pino analógico que verifica o nível do reef.
const byte sensor6 = 59;   // A5;      // Pino analógico que verifica o nível do fish only.

//***************************************************************************************************
//***************************************************************************************************
// Os 3 pinos abaixo serão controlados pelo PCF8575 caso esteja usando um.
// Observe que estes pinos também estão declarados na seção PCF8575.
// Caso esteja usando um PCF8575 os pinos 60, 61 e 62 estarão livres para ser usados em outras funções

// The 3 pins below will be controlled for PCF8575 if you have an installed.
// Notice that this pins also are declared in PCF8575 section.
// when using a PCF8575 the pins 60, 61 and 62 will be free to be used in others functions.
//***************************************************************************************************
#ifndef USE_PCF8575 // Do not change this line!
const byte bomba1Pin = 60; // A6       // Bomba que tira água da quarentena.
#ifndef USE_ESP8266 // Do not change this line!
const byte bomba2Pin = 61; // A7       // Bomba que tira água do sump.
const byte bomba3Pin = 62; // A8       // Bomba que coloca água no sump.
#else // Do not change this line!
// When using an ESP8266 as WiFi module is needed move this pins to any free pins.
// Quando usar um ESP8266 como módulo WiFi é necessário mudar estes pinos para outros livres.
const byte bomba2Pin = 88; // Move to free pin.
const byte bomba3Pin = 89; // Move to free pin.
#endif // Do not change this line!
#endif // Do not change this line!

//***************************************************************************************************
//***************************************************************************************************
const byte dosadora1 = 63; // A9;      // Bomba dosadora 1
const byte dosadora2 = 64; // A10;     // Bomba dosadora 2
const byte dosadora3 = 65; // A11;     // Bomba dosadora 3
const byte dosadora4 = 66; // A12;     // Bomba dosadora 4
const byte dosadora5 = 67; // A13;     // Bomba dosadora 5
const byte dosadora6 = 68; // A14;     // Bomba dosadora 6
// Pino 69 (A15) reservado para SS do RFM12B

//***************************************************************************************************
//***************************************************************************************************
// Os 7 pinos abaixo serão controlados pelo PCF8575 caso esteja usando um.
// Observe que estes pinos também estão declarados na seção PCF8575.

// The 7 pins below will be controlled for PCF8575 if you have an installed.
// Notice that this pins also are declared in PCF8575 section.
//***************************************************************************************************
#ifndef USE_PCF8575 // Do not change this line!
const byte temporizador1 = 80;           // Pino que liga o timer 1.
const byte temporizador2 = 81;           // Pino que liga o timer 2.
const byte temporizador3 = 82;           // Pino que liga o timer 3.
const byte temporizador4 = 83;           // Pino que liga o timer 4.
const byte temporizador5 = 84;           // Pino que liga o timer 5.
const byte solenoide1Pin = 85;           // Liga a reposição de água doce.
const byte alimentadorPin = 86;          // Pino que controla o alimentador automático.
const byte skimmerPin = 87;              // Pino que controla o skimmer
#endif // Do not change this line!

//****************************************************************************************************
///************************************** PCF8575 ****************************************************
//****************************************************************************************************
// Do not change this part if you have not a PCF8575 installed.
// Não altere esta parte se você não tem um PCF8575 instalado.
#ifdef USE_PCF8575 // Do not change this line!
const byte ozonizadorPin = 0;       // P0       // Pino que liga o ozonizador
const byte reatorPin = 1;           // P1       // Pino que liga o CO2 do reator.
const byte bomba1Pin = 2;           // P2       // Bomba que tira água da quarentena.
const byte bomba2Pin = 3;           // P3       // Bomba que tira água do sump.
const byte bomba3Pin = 4;           // P4       // Bomba que coloca água no sump.
const byte temporizador1 = 5;       // P5       // Pino que liga o timer 1.
const byte temporizador2 = 6;       // P6       // Pino que liga o timer 2.
const byte temporizador3 = 7;       // P7       // Pino que liga o timer 3.
const byte temporizador4 = 8;       // P8       // Pino que liga o timer 4.
const byte temporizador5 = 9;       // P9       // Pino que liga o timer 5.
const byte solenoide1Pin = 10;      // P10      // Liga a reposição de água doce.
const byte alimentadorPin = 11;     // P11      // Pino que controla o alimentador automático.
const byte skimmerPin = 12;         // P12      // Pino que controla o skimmer
#endif // Do not change this line!
//****************************************************************************************************
//***************** Variáveis dos sensores de temperatura ********************************************
//****************************************************************************************************
OneWire OneWireBus(sensoresPin);        // Sensores de temperatura
DallasTemperature sensors(&OneWireBus); // Passa a nossa referência OneWire para sensores de temperatura.
DeviceAddress sensor_agua;              // Atribui os endereços dos sensores de temperatura.
DeviceAddress sensor_dissipador;        // Atribui os endereços dos sensores de temperatura.
DeviceAddress sensor_ambiente;          // Atribui os endereços dos sensores de temperatura.
byte sonda_associada_1 = 1;
byte sonda_associada_2 = 2;
byte sonda_associada_3 = 3;

//****************************************************************************************************
//***************** Variáveis temporárias dos sensores de temperatura ********************************
//****************************************************************************************************
DeviceAddress tempDeviceAddress; // Endereço temporário da sonda.
DeviceAddress sonda1; // Endereço temporário da sonda1.
DeviceAddress sonda2; // Endereço temporário da sonda2.
DeviceAddress sonda3; // Endereço temporário da sonda3.
byte sonda_associada_1_temp = 0;
byte sonda_associada_2_temp = 0;
byte sonda_associada_3_temp = 0;

//*******************************************************************************************************
//********************** Funções do RTC ********************************************************************
//*******************************************************************************************************
#ifdef USE_PINS_18_AND_19_FOR_RTC // Do not change this line
DS1307 rtc(18, 19);     // (SDA,SCL) Indica em quais pinos o RTC está conectado.
#else // Do not change this line
DS1307 rtc(20, 21);  /// (SDA,SCL) Indica em quais pinos o RTC está conectado.
#endif // Do not change this line
Time t_temp, t;

//*******************************************************************************************************
//********************** Variáveis das fuções do touch screen e tela inicial ****************************
//*******************************************************************************************************
#ifdef USE_TFT // Do not change this line
UTFT        myGLCD(ITDB32WD, 38, 39, 40, 41); // "ITDB32WD" é o modelo do LCD
#ifdef USE_TFT_SHIELD // Do not change this line
URTouch      myTouch(6, 5, 4, 3, 2);          // Pinos usados pelo "touch" no TFT shield
#else // Do not change this line
URTouch      myTouch(7, 6, 5, 4, 3);       // Pinos usados pelo "touch" no Ferduino Mega 2560
#endif // Do not change this line

unsigned int ano = 0;
byte dia = 0;
byte whiteLed, blueLed, azulroyalLed, vermelhoLed, violetaLed;    // Valor anterior de PWM.
#endif //Do not change this line

byte dispScreen = 0;
unsigned long previousMillis = 0;

#ifdef USE_SCREENSAVER //Do not change this line
unsigned long previousMillis_2 = 0;
int interval = 60; // In seconds
boolean firstTime = true;
#endif //Do not change this line
//*****************************************************************************************
//*********************** Parâmetros ******************************************************
//*****************************************************************************************
byte status_parametros = 0x0;
//bit 0;   // Sinaliza que o chiller está ligado / desligado
//bit 1;   // Sinaliza que o aquecedor está ligado / desligado
//bit 2;   // Sinaliza que o alarme de temperatura está ativo
//bit 3;   // Sinaliza que o PH do aquário esta fora do especificado
//bit 4;   // Sinaliza que a densidade esta fora do especificado
//bit 5;   // Sinaliza que CO2 esta ligado / desligado
//bit 6;   // Sinaliza que o PH do reator de cálcio esta fora do especificado
//bit 7;   // Sinaliza que o ozonizador esta ligado / desligado
byte status_parametros_1 = 0x0;
//bit 0    // Sinaliza que a ORP esta fora do especificado

byte outlets[9];
//outlets[0] = Aquecedor > 0 = auto, 1 = on, 2 = off
//outlets[1] = Chiller > 0 = auto, 1 = on, 2 = off
//outlets[2] = Ozonizador > 0 = auto, 1 = on, 2 = off
//outlets[3] = Reator de cálcio > 0 = auto, 1 = on, 2 = off
//outlets[4] = Skimmer > 0 = auto, 1 = on, 2 = off
//outlets[5] = Bomba 1 (TPA) > 0 = auto, 1 = on, 2 = off
//outlets[6] = Bomba 2 (TPA) > 0 = auto, 1 = on, 2 = off
//outlets[7] = Bomba 3 (TPA) > 0 = auto, 1 = on, 2 = off
//outlets[8] = Reposição (ATO) > 0 = auto, 1 = on, 2 = off
byte outlets_changed[9];
boolean outlets_settings = false;
unsigned long outlets_millis = 0;
//*****************************************************************************************
//*********************** Variáveis do controle de temperatura da água ********************
//*****************************************************************************************
float tempC = 0;               // Temperatura da água
float setTempC = 25.5;         // Temperatura desejada
float offTempC = 0.5;          // Variação permitida da temperatura
float alarmTempC = 1;          // Variacao para acionar o alarme de temperatura da água
byte contador_temp = 0;
float temperatura_agua_temp = 0; // Temperatura temporária

//*****************************************************************************************
//************************ Variáveis temporárias de controle de temperatura da água *******
//*****************************************************************************************
float temp2beS;
float temp2beO;
float temp2beA;

//*****************************************************************************************
//************************ Variáveis do controle do PH do aquário *************************
//*****************************************************************************************
float PHA = 0;              // PH do aquário
float setPHA = 0;           // PH desejado do aquário
float offPHA = 0;           // Variaçãoo permitida do PH do aquário
float alarmPHA = 0;         // Variação para acionar o alarme de ph do aquário

//*****************************************************************************************
//************************ Variáveis temporárias de controle do PH do aquário *************
//*****************************************************************************************
float PHA2beS;
float PHA2beO;
float PHA2beA;

//*****************************************************************************************
//************************ Variáveis de controle de densidade *****************************
//*****************************************************************************************
int DEN = 0;                 // Densidade
int setDEN = 1025;           // Densidade desejada
byte offDEN = 2;             // Variação permitida da densidade
byte alarmDEN = 1;           // Variação para acionar o alarme de densidade

//*****************************************************************************************
//************************ Variáveis de controle do PH do reator de cálcio ****************
//*****************************************************************************************
float PHR = 0;              // Valores PH reator
float setPHR = 0;           // PH do reator desejado
float offPHR = 0;           // Variacao permitida do PH do reator
float alarmPHR = 0;         // Variacao para acionar o alarme do PH do reator de calcio

//*****************************************************************************************
//************************ Variáveis temporárias de controle do PH do reator de cálcio ****
//*****************************************************************************************
float PHR2beS;
float PHR2beO;
float PHR2beA;

//*****************************************************************************************
//************************ Variáveis de controle da  ORP **********************************
//*****************************************************************************************
int ORP = 0;                // Valores ORP
int setORP = 420;           // ORP desejada
byte offORP = 10;           // Variação permitida da ORP
byte alarmORP = 10;         // Variacão para acionar o alarme da ORP

//*****************************************************************************************
//************************ Variáveis temporárias de controle da ORP ***********************
//*****************************************************************************************
int ORP2beS;
byte ORP2beO;
byte ORP2beA;

//*****************************************************************************************
//************************ Variáveis temporárias de controle da densidade *****************
//*****************************************************************************************
int DEN2beS;
byte DEN2beO;
byte DEN2beA;

//*****************************************************************************************
//************************ Variáveis de controle de velocidade dos coolers ****************
//*****************************************************************************************
#ifdef USE_FAHRENHEIT //Do not change this line
float HtempMin = 86.9;
float HtempMax = 104.9;
#else //Do not change this line
float HtempMin = 30.5;    // Declara a temperatura para iniciar o funcionamento das ventoinhas do dissipador
float HtempMax = 40.5;    // Declara que as ventoinhas devem estar em sua velocidade máxima quando o dissipador estiver com 40°c
#endif //Do not change this line
int fanSpeed = 0;         // PWM dos coolers

//*****************************************************************************************
//************** Variáveis temperárias de controle de velocidade dos coolers **************
//*****************************************************************************************
float HtempMin_temp = 0;    // Declara a temperatura para iniciar o funcionamento das ventoinhas do dissipador
float HtempMax_temp = 0;    // Declara que as ventoinhas devem estar em sua velocidade máxima quando o dissipador estiver com 40°c

//*****************************************************************************************
//*********************** Variáveis de controle da temperatura do dissipador **************
//*****************************************************************************************
float tempH = 0;    // Temperatura do dissipador
byte tempHR = 60;   // Temperatura para reduzir potência dos leds
byte potR = 30;     // Porcentagem a ser reduzida.

//*****************************************************************************************
//*********** Variáveis temporárias de controle da temperatura do dissipador **************
//*****************************************************************************************
float temperatura_dissipador_temp = 0; // Temperatura temporária
byte tempHR_t = 0;                     // Temperatura temporária para reduzir potência dos leds
byte potR_t = 0;                       // Porcentagem temporária a ser reduzida.
boolean temperatura_alta = false;      // Sinaliza que a temperatura dos leds está alta.
boolean temperatura_baixou = false;    // Sinaliza que a temperatura dos leds esteve alta.

//*****************************************************************************************
//************************ Variáveis de controle da iluminação ****************************
//*****************************************************************************************
int LedChangTime = 0;             // Página de alteração do leds, tempo e valores.
boolean MeanWell = true;          // Se estiver usando drivers cuja potência máxima seja obtida aplicando zero volt e a mínima seja 5 volts altere de "true" para "false".
boolean LEDtestTick = false;      // Acelerar o tempo durante o teste dos leds.
int min_cnt ;
byte bled_out;
byte wled_out;
byte rbled_out;
byte rled_out;
byte uvled_out;
byte bled_out_temp;
byte wled_out_temp;
byte rbled_out_temp;
byte rled_out_temp;
byte uvled_out_temp;
byte moonled_out;
boolean periodo_selecionado = false;
byte y_tocado;
boolean teste_em_andamento = false;
byte cor_selecionada = 0;
// bit 1 = led branco
// bit 2 = led azul
// bit 3 = led azul royal
// bit 4 = led vermelho
// bit 5 = led violeta
byte setor_selecionado = 0;
boolean mensagem = true;
float suavizar = 0.0; // LEDS iniciam suavemente e chega ao valor especificado em 50 segundos.
byte predefinido = 0;
byte pre_definido_ativado = 0;
byte pwm_pre_definido = 0;
byte led_on_minuto;
byte led_on_hora;
byte led_off_minuto;
byte led_off_hora;
boolean horario_alterado = false;
boolean hora_modificada = false;
byte amanhecer_anoitecer = 60;
boolean teste_iniciado = false;

#define NUMERO_CANAIS 6
#define TEMPO_RAMPA 50
byte pinoLED[NUMERO_CANAIS] = {ledPinWhite, ledPinBlue, ledPinRoyBlue, ledPinRed, ledPinUV, ledPinMoon}; // Branco, azul, azul royal, vermelho, violeta, luz noturna
boolean desativarNuvemCanal[NUMERO_CANAIS] = {false, false, false, false, false, false};
byte probNuvemRelampago[2] = {100, 99}; // [0]= nuvem, [1] = relâmpago
byte nuvemCadaXdias = 1;
byte quantDuracaoMinMaxNuvem[4] = {1, 10, 2, 9}; // Quant. mín., quant. máx., duração min., duração máx.
boolean haveraNuvem = false;
boolean haveraRelampago = false;
byte duracaoNuvem = 0;
byte duracaoRelampago = 0;
byte quantNuvens = 0;
int horaNuvem[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Em minutos.
boolean executandoNuvem = false;
boolean executarAgora = false;
unsigned long millis_nuvem = 0;
int lastMinute = 0;
int espere = 0;
unsigned long millisRampa = 0;
boolean pontoBaixo[NUMERO_CANAIS] = {false, false, false, false, false, false};
boolean aguarde = false;
boolean inicioNuvem = false;
byte pwm_nuvem[NUMERO_CANAIS] = {0, 0, 0, 0, 0, 0};
byte passo[NUMERO_CANAIS] = {0, 0, 0, 0, 0, 0};
unsigned long LED_millis = 0;
boolean relampagoNoturno = false;
boolean temDelay = false;
byte valorAnterior = 0;
boolean desativarRelampagoCanal[NUMERO_CANAIS] = {true, true, true, true, true, true};
byte duracaoMinMaxRelampago[2] = {1, 5}; // Duração min., duração máx.

//*****************************************************************************************
//**************** Variáveis temporárias de controle da iluminação ************************
//*****************************************************************************************
byte predefinido_t = 0;
byte pre_definido_ativado_t = 0;
byte pwm_pre_definido_t = 0;
byte led_on_minuto_t;
byte led_on_hora_t;
byte led_off_minuto_t;
byte led_off_hora_t;
byte amanhecer_anoitecer_t = 0;

//*****************************************************************************************
//************************* LED design ****************************************************
//*****************************************************************************************
const byte cor_canal[5][3] = {
  {255, 255, 255},
  {9, 184, 255},
  {58, 95, 205},
  {255, 0, 0},
  {224, 102, 255}
};
/*
  byte cor_canal1[] = {255, 255, 255};  // Branco
  byte cor_canal2[] = {9, 184, 255};    // Azul
  byte cor_canal3[] = {58, 95, 205};    // Azul Royal
  byte cor_canal4[] = {255, 0, 0};      // Vermelho
  byte cor_canal5[] = {224, 102, 255};  // Violeta
*/

//*****************************************************************************************
//************************ Variáveis da fase lunar ****************************************
//*****************************************************************************************
String LP;
byte MaxI = 255; // Potência  máxima na Lua cheia.
byte tMaxI;
byte MinI = 0;   // Potência  mínima na Lua nova.
byte tMinI;
byte fase = 0;

//*****************************************************************************************
//********* Variáveis da TPA (Troca Parcial de Água) automática ***************************
//*****************************************************************************************
byte hora = 0;
byte minuto = 0;
byte duracaomaximatpa = 0;
byte semana_e[7]; // Index 0 = segunda-feira, 1 = terça-feira, 2 = quarta-feira, 3 = quinta-feira, 4 = sexta-feira, 5 = sábado, 6 = domingo.
byte tpa = 0;                             // Controla os estágios da TPA automática
byte tpa_status = 0x0; // 0 = false e 1 = true
// bit 1 = Sinaliza TPA automática em andamento
// bit 2 = Sinaliza falha durante a TPA automática
unsigned long tempo = 0;                 // Duração de cada estágio da TPA automática
unsigned long marcadoriniciotpa = 0;   // Evita que uma tpa inicie próximo do millis zerar
unsigned long shiftedmillis = 0;       // Evita que uma tpa inicie próximo do millis zerar

//*****************************************************************************************
//********** Variáveis temporárias da TPA (Troca Parcial de Água) automática **************
//*****************************************************************************************
byte temp2hora;
byte temp2minuto;
byte temp2duracaomaximatpa;
byte semana[7];

//****************************************************************************************
//*********************** Variáveis de controle das funções que utilizam o cartao SD *****
//****************************************************************************************
SdFat SD;
SdFile file;
unsigned long log_SD_millis = 0;
void writeCRLF(SdFile& f);

//*****************************************************************************************
//*********************** Variável do controle de níveis **********************************
//*****************************************************************************************
boolean nivel_status1 = 0;             // Sinaliza nível baixo sensor 1
boolean nivel_status2 = 0;             // Sinaliza nível baixo sensor 2
boolean nivel_status3 = 0;             // Sinaliza nível baixo sensor 3
boolean nivel_status4 = 0;             // Sinaliza nível baixo sensor 4
boolean nivel_status5 = 0;             // Sinaliza nível baixo sensor 5
boolean nivel_status6 = 0;             // Sinaliza nível baixo sensor 6

//*****************************************************************************************
//************************ Variável de controle da reposição de água doce *****************
//*****************************************************************************************
byte Status = 0x0;
// bit 1 // Sinaliza reposição ligada / desligada
// bit 2
// bit 3

//*****************************************************************************************
//************************* Funções do ethernet shield ************************************
//*****************************************************************************************
#ifdef ETHERNET_SHIELD //Do not change this line
const char *Username  = "FernandoGarcia";           // Coloque aqui o nome de usuário cadastrado no ferduino.com/webcontrol
const char *APIKEY = "2e4e116a";                     // Cole aqui a ApiKey gerada pelo ferduino.com/webcontrol
const byte limite_falha = 30;                        // Reseta o controlador após 30 tentativas de upload para Ferduino. Utilize sempre um valor maior ou igual a 3.

#ifndef USE_ESP8266 //Do not change this line  
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Este MAC deve ser único na sua rede local.
byte ip[] = {192, 168, 0, 177};                     // Configure o IP conforme a sua rede local.
IPAddress dnsServer(8, 8, 8, 8);                    // Configure o IP conforme a sua rede local. Este é o DNS do Google, geralmente não é necessário mudar.
IPAddress gateway(192, 168, 0, 1);                  // Configure o "Gateway" conforme a sua rede local.
IPAddress subnet(255, 255, 255, 0);                 // Configure a máscara de rede conforme a sua rede local.

EthernetClient client;
PubSubClient MQTT(client);
#else //Do not change this line
NeoSWSerial virtualPort (A8, A7);  // RX, TX
ELClient ESP8266(&virtualPort);
ELClientMqtt MQTT(&ESP8266);
boolean MQTT_connected = false;
#define MQTT_MAX_PACKET_SIZE 550
#endif //Do not change this line

char *inParse[20];
unsigned long millis_mqtt = 0;
boolean web_dosage = false;
unsigned long millis_dosagem = 0;
unsigned long millis_enviar = 0;
boolean web_calibracao = false;
unsigned long teste_led_millis = 0;
unsigned long close_millis = 0;
byte notconnected = 0;
#endif //Do not change this line

boolean web_teste = false;
//*****************************************************************************************
//************************** Variáveis de controle do multiplexador ***********************
//*****************************************************************************************
#if defined(STAMPS_EZO) || defined(STAMPS_V4X) //Do not change this line
unsigned long millis_antes = 0;
const byte ph1 = 0; // Y0
const byte ph2 = 1; // Y1
const byte orp = 2; // Y2
const byte ec = 3;  // Y3
#endif //Do not change this line

//*****************************************************************************************
//************************** Variáveis da solicitação de senha ****************************
//*****************************************************************************************
char stCurrent[7] = "";
char limpar_senha [7] = "";
byte stCurrentLen = 0;
const char senha [7] = {'1', '2', '3', '4', '5', '6', '\0'}; // Insira sua senha aqui. O caracter '\0' não deve ser alterado.

//*****************************************************************************************
//************************** Variáveis dosadoras ******************************************
//*****************************************************************************************
boolean dosadoras = true; //Altere para "false" caso não tenha as dosadoras.
const char *arquivo[6] = {"HDP1.TXT", "HDP2.TXT", "HDP3.TXT", "HDP4.TXT", "HDP5.TXT", "HDP6.TXT"};
unsigned long tempo_dosagem = 0;
unsigned long dosadoras_millis = 0;
boolean modo_manual = false;
boolean modo_personalizado = false;
boolean modo_calibrar = false;
byte dosadora_selecionada = 0; // 0 = false, 1 = true
byte dosadora[6] = {dosadora1, dosadora2, dosadora3, dosadora4, dosadora5, dosadora6}; // Index 0 = dosadora 1 , 1 = dosadora 2, 2 = dosadora 3, 3 = dosadora 4, 4 = dosadora 5, 5 = dosadora 6
byte ativar_desativar = 0x0;     // 0 = false, 1 = true
byte hora_inicial_dosagem_personalizada_e[6];
byte minuto_inicial_dosagem_personalizada_e[6];
byte hora_final_dosagem_personalizada_e[6];
byte minuto_final_dosagem_personalizada_e[6];
byte segunda_dosagem_personalizada_e[6];
byte terca_dosagem_personalizada_e[6];
byte quarta_dosagem_personalizada_e[6];
byte quinta_dosagem_personalizada_e[6];
byte sexta_dosagem_personalizada_e[6];
byte sabado_dosagem_personalizada_e[6];
byte domingo_dosagem_personalizada_e[6];
float dose_dosadora_personalizada_e[6] = {101, 102, 103, 104, 105, 106};
byte quantidade_dose_dosadora_personalizada_e[6];
byte modo_personalizado_on_e[6];
float dose_dosadora_manual_e[6] = {20, 20, 20, 20, 20, 20};
float fator_calib_dosadora_e[6] = {35.1, 35.2, 35.3, 35.4, 35.5, 35.6};
byte erro_dosagem;

//*****************************************************************************************
//************************** Variáveis temporárias das dosadoras **************************
//*****************************************************************************************
byte hora_inicial_dosagem_personalizada[6];
byte minuto_inicial_dosagem_personalizada[6];
byte hora_final_dosagem_personalizada[6];
byte minuto_final_dosagem_personalizada[6];
byte segunda_dosagem_personalizada[6];
byte terca_dosagem_personalizada[6];
byte quarta_dosagem_personalizada[6];
byte quinta_dosagem_personalizada[6];
byte sexta_dosagem_personalizada[6];
byte sabado_dosagem_personalizada[6];
byte domingo_dosagem_personalizada[6];
float dose_dosadora_personalizada[6];
byte quantidade_dose_dosadora_personalizada[6];
byte modo_personalizado_on[6];
float dose_dosadora_manual[6];
float volume_dosado[6];
float fator_calib_dosadora[6];

//*****************************************************************************************
//************************** Variáveis dos timers *****************************************
//*****************************************************************************************
byte temporizador = 0;
byte temporizador_e[5] = {temporizador1, temporizador2, temporizador3, temporizador4, temporizador5};  // Index 0 = timer 1 , 1 = timer 2, 2 = timer 3, 3 = timer 4, 4 = timer 5

boolean web_timer = false;
byte temporizador_status = 0x0; // 1 = true e 0 = false
//bit 1 = temporizador 1
//bit 2 = temporizador 2
//bit 3 = temporizador 3
//bit 4 = temporizador 4
//bit 5 = temporizador 5
byte temporizador_modificado = 0x0;
//bit 1 = temporizador 1
//bit 2 = temporizador 2
//bit 3 = temporizador 3
//bit 4 = temporizador 4
//bit 5 = temporizador 5

byte on_hora_e[5]; // Index 0 = timer 1 , 1 = timer 2, 2 = timer 3, 3 = timer 4, 4 = timer 5
byte on_minuto_e[5];
byte off_hora_e[5];
byte off_minuto_e[5];
byte temporizador_ativado_e[5];

//*****************************************************************************************
//******************** Variáveis temporárias dos timers ***********************************
//*****************************************************************************************
byte on_hora[5];
byte on_minuto[5];
byte off_hora[5];
byte off_minuto[5];
byte temporizador_ativado[5];

//*****************************************************************************************
//************************** Variáveis do PCF8575 *****************************************
//*****************************************************************************************
#ifdef USE_PCF8575 //Do not change this line
byte endereco_PCF8575TS = 0x20; // Endereço em hexadecimal = 0x20
PCF8575 PCF8575;
#endif //Do not change this line

//*****************************************************************************************
//*********************** Wireless transceiver (RFM12B) ***********************************
//*****************************************************************************************
#if defined(RFM12B_LED_CONTROL) || defined(RFM12B_RELAY_CONTROL) //Do not change this line
RFM12B radio;
#define MY_ID      99                   // ID deste dispositivo
#define NETWORK_ID   100                // Todos os dispositivos devem estar na mesma rede.
#define TARGET_ID_LED   1               // 1 = ID do dispositivos que receberá a informação
#define TARGET_ID_RELAY   2             // 2 = ID do dispositivos que receberá a informação
#define FREQUENCY   RF12_915MHZ         // Frequência de operação do rádio.
#define KEY         "thisIsEncryptKey"  // Esta senha deve ter exatamente 16 caracteres.
#define ACK_TIME    200
const byte limite_sem_resposta = 4;     // Reseta o controlador após 4 envios sem resposta. Para desabilitar esta função altere o valor para 0 (ZERO).
unsigned long lastPeriod_millis = 0;
boolean requestACK_LED = false;         // true = Solicitar uma resposta do dispositivo que recebe a informação
boolean requestACK_RELAY = false;       // true = Solicitar uma resposta do dispositivo que recebe a informação
byte nothing = 0;
#endif //Do not change this line

#ifdef RFM12B_LED_CONTROL //Do not change this line
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
#endif //Do not change this line

#ifdef RFM12B_RELAY_CONTROL //Do not change this line
typedef struct {
  int  nodeId;
  byte relay_0;
  byte relay_1;
  byte relay_2;
  byte relay_3;
  byte relay_4;
  byte relay_5;
  byte relay_6;
  byte relay_7;
  byte relay_8;
  byte relay_9;
  byte relay_10;
  byte relay_11;
  byte relay_12;
  byte relay_13;
  byte relay_14;
  byte relay_15;
}
Payload_relay;
Payload_relay theData_relay  = {MY_ID, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif //Do not change this line

//*****************************************************************************************
//************************** Dispositivos SPI *********************************************
//*****************************************************************************************
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

//*****************************************************************************************
//************************* Variáveis da temperatura ambiente *****************************
//*****************************************************************************************
float tempA = 0; // Temperatura ambiente
float temperatura_ambiente_temp = 0; // Temperatura temporária

//*****************************************************************************************
//************************* Variáveis das bombas de circulação ****************************
//*****************************************************************************************
#ifdef NIGHT_MODE //Do not change this line
const float POWER_PUMP1 = 0.5; // 50%
const float POWER_PUMP2 = 0.5; // 50%
#endif //Do not change this line
byte modo_selecionado = 1;
byte Pump1PWM_temp = 0;
byte Pump2PWM_temp = 0;
int periodo = 10000;
unsigned int duracao = 5000; // Duração do ciclo em milisegundos para o modo 3.
unsigned long millis_antes_1 = 0;
byte conta = 0;
byte Pump1PWM = 0;
byte Pump2PWM = 0;

//*****************************************************************************************
//*********************** Variáveis de controle do alimentador automático *****************
//*****************************************************************************************
byte horario_alimentacao_e[4]; // horario_e[0] = hora para iniciar, horario_e[1] = minuto para iniciar, horario_e[2] = hora para terminar, horario_e[3] = minuto para terminar
byte dia_alimentacao_e[7];
byte duracao_alimentacao = 1; // Duração em segundos
byte desligar_wavemaker = 2; // Tempo em minutos
byte quantidade_alimentacao = 1;
byte alimentacao_wavemaker_on_off = 0; // bit 0 = alimentação automática ativada  ou desativada bit 1 = desligar wavemaker ativado / desativado
boolean modo_alimentacao = false;
boolean wavemaker_on_off = false;
unsigned long alimentacao_millis = 0;
unsigned long wavemaker_on_off_millis = 0;
unsigned long check_alimentador_millis = 0;
boolean alimentacao_erro = false;

//*****************************************************************************************
//********************* Variáveis temporárias do alimentador automático *******************
//*****************************************************************************************
byte horario_alimentacao[4];
byte dia_alimentacao[7];
byte duracao_alimentacao_temp = 0;
byte desligar_wavemaker_temp = 0;
byte quantidade_alimentacao_temp = 0;
byte alimentacao_wavemaker_on_off_temp = 0;

//*****************************************************************************************
//************************** Variáveis de controle da potência dos leds *******************
//*****************************************************************************************
byte wled[96] = {                         //Potência de saída dos leds brancos 255 = 100% da potência
  0, 0, 0, 0, 0, 0, 0, 0,       // 0 e 2
  0, 0, 0, 0, 0, 0, 0, 0,       // 2 e 4
  0, 0, 0, 0, 12, 21, 30, 39,       // 4 e 6
  48, 57, 66, 75, 84, 93, 102, 111,     // 6 e 8
  120, 129, 138, 147, 156, 165, 174, 183, // 8 e 10
  192, 201, 210, 219, 228, 237, 246, 255, // 10 e 12
  255, 246, 237, 228, 219, 210, 201, 192, // 12 e 14
  183, 174, 165, 156, 147, 138, 129, 120,  // 14 e 16
  111, 102, 93, 84, 75, 66, 57, 48,       // 16 e 18
  39, 30, 21, 12, 0, 0, 0, 0,         // 18 a 20
  0, 0, 0, 0, 0, 0, 0, 0,         // 20 e 22
  0, 0, 0, 0, 0, 0, 0, 0          // 22 a 0
};

byte bled[96] = {                       // Potência de saída dos leds azuis 255 = 100% da potência
  0, 0, 0, 0, 0, 0, 0, 0,       // 0 e 2
  0, 0, 0, 0, 0, 0, 0, 0,       // 2 e 4
  0, 0, 0, 0, 12, 21, 30, 39,       // 4 e 6
  48, 57, 66, 75, 84, 93, 102, 111,     // 6 e 8
  120, 129, 138, 147, 156, 165, 174, 183, // 8 e 10
  192, 201, 210, 219, 228, 237, 246, 255, // 10 e 12
  255, 246, 237, 228, 219, 210, 201, 192, // 12 e 14
  183, 174, 165, 156, 147, 138, 129, 120,  // 14 e 16
  111, 102, 93, 84, 75, 66, 57, 48,       // 16 e 18
  39, 30, 21, 12, 0, 0, 0, 0,         // 18 a 20
  0, 0, 0, 0, 0, 0, 0, 0,         // 20 e 22
  0, 0, 0, 0, 0, 0, 0, 0          // 22 a 0
};

byte rbled[96] = {                         //Potência de saída dos leds brancos 255 = 100% da potência
  0, 0, 0, 0, 0, 0, 0, 0,       // 0 e 2
  0, 0, 0, 0, 0, 0, 0, 0,       // 2 e 4
  0, 0, 0, 0, 12, 21, 30, 39,       // 4 e 6
  48, 57, 66, 75, 84, 93, 102, 111,     // 6 e 8
  120, 129, 138, 147, 156, 165, 174, 183, // 8 e 10
  192, 201, 210, 219, 228, 237, 246, 255, // 10 e 12
  255, 246, 237, 228, 219, 210, 201, 192, // 12 e 14
  183, 174, 165, 156, 147, 138, 129, 120,  // 14 e 16
  111, 102, 93, 84, 75, 66, 57, 48,       // 16 e 18
  39, 30, 21, 12, 0, 0, 0, 0,         // 18 a 20
  0, 0, 0, 0, 0, 0, 0, 0,         // 20 e 22
  0, 0, 0, 0, 0, 0, 0, 0          // 22 a 0
};
byte rled[96] = {                         //Potência de saída dos leds brancos 255 = 100% da potência
  0, 0, 0, 0, 0, 0, 0, 0,       // 0 e 2
  0, 0, 0, 0, 0, 0, 0, 0,       // 2 e 4
  0, 0, 0, 0, 12, 21, 30, 39,       // 4 e 6
  48, 57, 66, 75, 84, 93, 102, 111,     // 6 e 8
  120, 129, 138, 147, 156, 165, 174, 183, // 8 e 10
  192, 201, 210, 219, 228, 237, 246, 255, // 10 e 12
  255, 246, 237, 228, 219, 210, 201, 192, // 12 e 14
  183, 174, 165, 156, 147, 138, 129, 120,  // 14 e 16
  111, 102, 93, 84, 75, 66, 57, 48,       // 16 e 18
  39, 30, 21, 12, 0, 0, 0, 0,         // 18 a 20
  0, 0, 0, 0, 0, 0, 0, 0,         // 20 e 22
  0, 0, 0, 0, 0, 0, 0, 0          // 22 a 0
};
byte uvled[96] = {                         //Potência de saída dos leds brancos 255 = 100% da potência
  0, 0, 0, 0, 0, 0, 0, 0,       // 0 e 2
  0, 0, 0, 0, 0, 0, 0, 0,       // 2 e 4
  0, 0, 0, 0, 12, 21, 30, 39,       // 4 e 6
  48, 57, 66, 75, 84, 93, 102, 111,     // 6 e 8
  120, 129, 138, 147, 156, 165, 174, 183, // 8 e 10
  192, 201, 210, 219, 228, 237, 246, 255, // 10 e 12
  255, 246, 237, 228, 219, 210, 201, 192, // 12 e 14
  183, 174, 165, 156, 147, 138, 129, 120,  // 14 e 16
  111, 102, 93, 84, 75, 66, 57, 48,       // 16 e 18
  39, 30, 21, 12, 0, 0, 0, 0,         // 18 a 20
  0, 0, 0, 0, 0, 0, 0, 0,         // 20 e 22
  0, 0, 0, 0, 0, 0, 0, 0          // 22 a 0
};

byte *cor[5] = {wled, bled, rbled, rled, uvled};

//*****************************************************************************************
//************************** Textos *******************************************************
//*****************************************************************************************
#ifdef ETHERNET_SHIELD //Do not change this line
const char string0[] PROGMEM = "{\"response\":\"ok\"}";
const char string1[] PROGMEM = "{\"response\":\"stop\"}";

const char* const tabela_strings[] PROGMEM =
{
  string0, string1
};
#endif //Do not change this line
