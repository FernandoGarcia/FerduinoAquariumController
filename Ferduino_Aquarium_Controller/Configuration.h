#pragma once // Do not change this line!
// *************************************************************************************************
// *************** Selecionar idioma ***************************************************************
// *************************************************************************************************
// Descomente a linha correspondente ao seu idioma.
// Uncomment the line corresponding to your language.

// #define ENGLISH    // If this program is useful for you, make a donation to help with development. Paypal: fefegarcia_1@hotmail.com
// #define FRENCH     // Si ce programme est utile pour vous, faire un don pour aider au développement. Paypal: fefegarcia_1@hotmail.com
// #define GERMAN     // Wenn dieses Programm ist nützlich für Sie, eine Spende an mit Entwicklung zu helfen. Paypal: fefegarcia_1@hotmail.com
// #define ITALIAN    // Se questo programma vi è utile, fate una donazione per aiutare con il suo sviluppo. Paypal: fefegarcia_1@hotmail.com
#define PORTUGUESE   // Se este programa é útil para você, faça uma doação para ajudar no desenvolvimento. Paypal: fefegarcia_1@hotmail.com
// #define SPANISH    // Si este programa es útil para usted, hacer una donación para ayudar con el desarrollo. Paypal: fefegarcia_1@hotmail.com

// *************************************************************************************************
// **************************** ATIVAR OU DESATIVAR FUNÇÕES  ***************************************
// **************************** ENABLE OR DISABLE FUNCTIONS  ***************************************
// *************************************************************************************************
// Comment the line below to disable watchdog
// #define WATCHDOG // Reseta o controlador se a função "wdt_reset()" não for executada em até 8 segundos.
// Essa função minimiza problemas com o travamento do código mas, pode apresentar incompatibilidades com alguns bootloaders

// Comment the line below to disable ethernet functions
#define ETHERNET_SHIELD // Comente esta linha para desativar as funções do ethernet shield.

// Uncomment the line bellow to use an ESP8266 as WIFI module
// #define USE_ESP8266 // Descomente esta linha para usar um ESP8266 como módulo WIFI.

// Comment this two lines below if have not stamps
// Comente as duas linhas abaixo se não tiver stamps
#define STAMPS_V4X     // Comente esta linha para usar Stamps EZO
// #define STAMPS_EZO     // Descomente esta linha para usar Stamps EZO

// Comment the line below if you haven't a stamp for tank pH.
#define USE_STAMP_FOR_TANK_PH // Comente esta linha se você não tem um "stamp" para o pH do aquário.

// Comment the line below if you haven't a stamp for calcium reactor.
#define USE_STAMP_FOR_CALCIUM_REACTOR // Comente esta linha se você não tem um "stamp" para o reator de cálcio.

// Comment the line below if you haven't a stamp for ORP.
#define USE_STAMP_FOR_ORP // Comente esta linha se você não tem um "stamp" para a ORP.

// Comment the line below if you haven't a stamp for density.
// #define USE_STAMP_FOR_DENSITY // Comente esta linha se você não tem um "stamp" para a densidade.

// Uncomment the line bellow to use a digital tilt hydrometer (iSpindel) instead EC stamp and probe.
// Descomente a linha abaixo para usar o densímetro digital (iSpindel) em vez de stamp e sonda de condutividade.
#define TILT_HYDROMETER

// Comment this two lines below if have not RFM12B wireless transceiver
// #define RFM12B_LED_CONTROL   // Descomente esta linha para controlar os LEDs via RF
// #define RFM12B_RELAY_CONTROL // Descomente esta linha  para controlar os relês via RF

// Comente esta linha para desativar as mensagens no monitor serial ou para usar os pinos 0 e 1 (RX e TX) como OUTPUT
// Comment this line to disable the messages on serial monitor or to use pins 0 and 1 (RX e TX) as OUTPUT
#define DEBUG  // Comente esta linha para usar os pinos 0 e 1 para controle dos coolers e buzzer.

// Comment the line below to disable this function
// Comente a linha abaixo para desativar esta função
// #define DISABLE_SKIMMER // Desliga o skimmer caso o nível no compartimento esteja alto.
// Evita transbordamento do skimmer caso a bomba de retorno seja desligada

// Comment this line to enable password screen
// Comente esta linha para ativar a solicitação de senha.
// #define SKIP_PASSWORD_SCREEN // comente esta linha se deseja solicitar uma senha após o primeiro toque no TFT

// Comment this line to use static IP.
// Comente esta linha para usar IP estático
// #define USE_DHCP // Descomente esta linha para usar DHCP

// Uncomment the line below to use screensaver
// Descomente a linha abaixo para ativar o protetor de tela
// #define USE_SCREENSAVER

// Comment the line below to disable night mode for stream pumps
// Comente a linha abaixo para desativar o modo noturno para bombas de circulação.
#define NIGHT_MODE // Reduz a potência das bombas de circulação quando os LEDs estão desligados.

// Uncomment the line below to use temperature in Fahrenheit.
// #define USE_FAHRENHEIT // Descomente esta linha para usar temperatura em Fahrenheit

// Comment the line bellow if you don't want use a TFT. This function works only with IDE 1.6.7 or higher.
#define USE_TFT // Comente esta linha se você não quer usar um TFT. Estão função funciona apenas com a IDE 1.6.7 or higher.

// Change the TFT model below if needed. Normally it should work for all models with HX8352-A controller
// Altere o modelo do TFT abaixo se necessário. Nomalmente este dever funcionar para todos os modelos com controlador HX8352-A.
#define TFT_MODEL ITDB32WD

// Uncomment the line below if you are using a TFT shield.
// #define USE_TFT_SHIELD // Descomente esta linha se você estiver usando um "TFT shield".

// Select the suitable speed for your SD card. Don't leave two lines uncommented here.
// Selecione a velocidade adequada para seu cartão SD. Não deixe duas linhas descomentadas aqui.
// #define SD_CARD_SPEED SPI_FULL_SPEED    // Full speed
#define SD_CARD_SPEED SPI_HALF_SPEED      // Half speed
// #define SD_CARD_SPEED SPI_QUARTER_SPEED // Quarter speed

// Uncomment the line below if you have the  SD card on ethernet shield.
// #define USE_PIN_4_FOR_SD_CARD // Descomente esta linha se você tem o cartão SD conectado no "ethernet shield".

// Uncomment the line below if you have the  SD card on TFT
// Do not uncomment this line when using Ferduino Mega 2560
// #define USE_PIN_53_FOR_SD_CARD // Descomente esta linha se você tem o cartão SD conectado no TFT. Não descomente esta linha se estiver usando um Ferduino Mega 2560

// Uncomment the line bellow if your touch screen have coordinates mirrored. So don't need change in ProcessMyTouch: x = 399-myTouch.getX () and y = 239-myTouch.getY ().
// #define INVERT_TOUCH // Descomente essa linha se seu "touch screen" tem as coordenadas espelhadas. Assim não será necessário alterar em "ProcessMyTouch": x = 399-myTouch.getX () and y = 239-myTouch.getY ().

// Uncomment the line below to enable an extra channel for lightning during the night.
// #define USE_EXTRA_CHANNEL_FOR_LIGHTNING_DURING_NIGHT // Descomente esta linha para utilizar um canal extra para relâmpagos durante a noite.

// Select the extra channel to be used for lightning during the night. 0 = white, 1 = blue, 2 = royal blue, 3 = red, 4 = UV
#define EXTRA_CHANNEL_FOR_LIGHTNING 0 // Selecione o canal extra para ser usado para relâmpagos noturnos. 0 = branco, 1 = azul, 2 = azul royal, 3 = vermelho, 4 = ultra violeta

// Define the minimum PWM value to clouds and lightning. If the current PWM is smaller than this value the effect won't be done over the channel.
// When the PWM is smaller than this value the clouds and lightnigs are considered nocturnal. So the lightning will use the extra channel if moon PWM is higher than this value.
#define MIN_PWM_NUVEM 30 // Define o valor mínimo de PWM para nuvens e relâmpagos. Se o PWM atual for menor que este valor o efeito não será executado sobre o canal.
// Quando o PWM é menor que este valor as nuvens e relâmpagos são considereados noturnos. Então o relâmpago will usar o canal extra se o PWM lua for maior que este valor.

// *************************************************************************************************
// ************************* Inclusão de configurações *********************************************
// *************************************************************************************************
#include "src/Include/Library.h" // Do not change this line

// ****************************************************************************************************
// ****************** Define funções dos pinos digitais e analógicos **********************************
// ****************************************************************************************************
// Pinos 0 e 1 reservados para a porta serial 0.
const byte alarmPin = 0;          // Pino que aciona o alarme
const byte desativarFanPin = 1;   // Pino que desativa os coolers.
// Pino 2 reservado para INT do RFM12B.
// Pinos 3, 4, 5, 6 e 7 reservados para o touch.
// Pino 5 também é o chip select do cartão SD.
// Pin 7 is free in DIY controller. Used only in Ferduino M.
const byte ledPinUV = 8;            // Pino que liga os leds violeta
const byte ledPinBlue = 9;          // Pino que liga os leds azuis
const byte ledPinWhite = 10;        // Pino que liga os leds brancos
const byte ledPinRoyBlue = 11;      // Pino que liga os leds "royal blue"
const byte ledPinRed = 12;          // Pino que liga os leds vermelho
const byte fanPin = 13;             // Pino que controla a velocidade das ventoinhas do dissipador
// Pinos 14 e 15 reservados para a porta serial 3 que se comunica com os "Stamps"
const byte multiplexadorS0Pin = 16; // Pino S0 de controle dos stamps
const byte multiplexadorS1Pin = 17; // Pino S1 de controle dos stamps
// Pinos 18 e 19 reservados para o ESP8266.
// Pinos 20 e 21 reservados para comunicação I2C do PCF8575 e RTC.
// Pinos 22 à 41 reservados para o LCD.
const byte aquecedorPin = 42;   // Pino que liga o aquecedor
const byte chillerPin = 43;     // Pino que liga o chiller
const byte ledPinMoon = 44;     // Pino que liga os leds da luz noturna
const byte wavemaker1 = 45;     // Pino que controla o wavemaker 1
const byte wavemaker2 = 46;     // Pino que controla o wavemaker 2
// 47 and 48 are free
const byte sensoresPin = 49;    // Pino que lê os sensores de temperatura
// Pinos 50, 51 e 52 reservados para comunicação SPI
// Pino 53 reservado para "select slave do ethernet shield.
const byte sensor1 = 54;   // A0;      // Pino analógico que verifica se há tensão na bóia da quarentena.
const byte sensor2 = 55;   // A1;      // Pino analógico que verifica se há tensão na bóia inferior do sump.
const byte sensor3 = 56;   // A2;      // Pino analógico que verifica se há tensão na bóia superior do sump.
const byte sensor4 = 57;   // A3;      // Pino analógico que verifica se há tensão na bóia inferior do reservatório.
const byte sensor5 = 58;   // A4;      // Pino analógico que verifica o nível do reef.
const byte sensor6 = 59;   // A5;      // Pino analógico que verifica o nível do fish only.
// Pins 60 (A6), 61 (A7) and 62 (A8) are free
const byte dosadora1 = 63; // A9;      // Bomba dosadora 1
const byte dosadora2 = 64; // A10;     // Bomba dosadora 2
const byte dosadora3 = 65; // A11;     // Bomba dosadora 3
const byte dosadora4 = 66; // A12;     // Bomba dosadora 4
const byte dosadora5 = 67; // A13;     // Bomba dosadora 5
const byte dosadora6 = 68; // A14;     // Bomba dosadora 6
// Pino 69 (A15) reservado para SS do RFM12B

// ****************************************************************************************************
///************************************** PCF8575 ****************************************************
// ****************************************************************************************************
const byte ozonizadorPin = 0;     // P0       // Pino que liga o ozonizador
const byte reatorPin = 1;         // P1       // Pino que liga o CO2 do reator.
const byte bomba1Pin = 2;         // P2       // Bomba que tira água da quarentena.
const byte bomba2Pin = 3;         // P3       // Bomba que tira água do sump.
const byte bomba3Pin = 4;         // P4       // Bomba que coloca água no sump.
const byte temporizador1 = 5;     // P5       // Pino que liga o timer 1.
const byte temporizador2 = 6;     // P6       // Pino que liga o timer 2.
const byte temporizador3 = 7;     // P7       // Pino que liga o timer 3.
const byte temporizador4 = 8;     // P8       // Pino que liga o timer 4.
const byte temporizador5 = 9;     // P9       // Pino que liga o timer 5.
const byte solenoide1Pin = 10;    // P10      // Liga a reposição de água doce.
const byte alimentadorPin = 11;   // P11      // Pino que controla o alimentador automático.
const byte skimmerPin = 12;       // P12      // Pino que controla o skimmer

// *****************************************************************************************
// ************************** Senha para acessar os menus **********************************
// *****************************************************************************************
const char senha [7] = {'1', '2', '3', '4', '5', '6', '\0'}; // Insira sua senha aqui. O caracter '\0' não deve ser alterado.

// *****************************************************************************************
// ************************* Funções do ethernet shield ************************************
// *****************************************************************************************
#ifdef ETHERNET_SHIELD                                  // Do not change this line
  const char *Username  = "FernandoGarcia";             // Coloque aqui o nome de usuário cadastrado no ferduino.com/webcontrol
  const char *APIKEY = "2e4e116a";                      // Cole aqui a ApiKey gerada pelo ferduino.com/webcontrol

 #ifndef USE_ESP8266                                    // Do not change this line
    byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Este MAC deve ser único na sua rede local.
    byte ip[] = {192, 168, 0, 177};                     // Configure o IP conforme a sua rede local.
    IPAddress dnsServer(8, 8, 8, 8);                    // Configure o IP conforme a sua rede local. Este é o DNS do Google, geralmente não é necessário mudar.
    IPAddress gateway(192, 168, 0, 1);                  // Configure o "Gateway" conforme a sua rede local.
    IPAddress subnet(255, 255, 255, 0);                 // Configure a máscara de rede conforme a sua rede local.
 #endif  // Do not change this line
#endif // Do not change this line

// *****************************************************************************************
// *********************** Wireless transceiver (RFM12B) ***********************************
// *****************************************************************************************
#if defined(RFM12B_LED_CONTROL) || defined(RFM12B_RELAY_CONTROL) // Do not change this line
  #define MY_ID      99                                          // ID deste dispositivo
  #define NETWORK_ID   100                                       // Todos os dispositivos devem estar na mesma rede.
  #define TARGET_ID_LED   1                                      // 1 = ID do dispositivos que receberá a informação
  #define TARGET_ID_RELAY   2                                    // 2 = ID do dispositivos que receberá a informação
  #define KEY         "thisIsEncryptKey"                         // Esta senha deve ter exatamente 16 caracteres.
  #define FREQUENCY   RF12_915MHZ                                // Frequência de operação do rádio.
#endif // Do not change this line
