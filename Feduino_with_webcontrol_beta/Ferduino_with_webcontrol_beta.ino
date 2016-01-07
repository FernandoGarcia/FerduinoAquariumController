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

// Este programa é compatível com a IDE 1.0.6

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

// #define ENGLISH    // If this program is useful for you, make a donation to help with development. Paypal: fefegarcia_1@hotmail.com
// #define FRENCH     // Si ce programme est utile pour vous, faire un don pour aider au développement. Paypal: fefegarcia_1@hotmail.com
// #define GERMAN     // Wenn dieses Programm ist nützlich für Sie, eine Spende an mit Entwicklung zu helfen. Paypal: fefegarcia_1@hotmail.com
// #define ITALIAN    // Se questo programma è utile per voi, fare una donazione per aiutare con lo sviluppo. Paypal: fefegarcia_1@hotmail.com
#define PORTUGUESE   // Se este programa é útil para você, faça uma doação para ajudar no desenvolvimento. Paypal: fefegarcia_1@hotmail.com
// #define SPANISH    // Si este programa es útil para usted, hacer una donación para ayudar con el desarrollo. Paypal: fefegarcia_1@hotmail.com

//*************************************************************************************************
//*************** Bibliotecas utilizadas ***********************************************************
//*************************************************************************************************
#include <UTFT.h>    
#include <UTouch.h> 
#include <Wire.h>
#include <EEPROM.h>
#include <writeAnything.h>
#include <DS1307henning.h> // Comente esta linha para usar a versão em inglês.
//#include <DS1307.h>      // Descomente esta linha para usar a versão em inglês.
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <avr/pgmspace.h>
//#include <PCF8575.h>
//#include <JeeLib.h>
#include <Base64.h>
#include <SPI.h> 
#include <Ethernet.h>

//****************************************************************************************************
//****************** Variáveis de textos e fontes ****************************************************
//****************************************************************************************************
#define LARGE true
#define SMALL false
extern uint8_t RusFont1[];    // Declara que fontes vamos usar
extern uint8_t BigFont[];     // Declara que fontes vamos usar
char buffer[50];

//****************************************************************************************************
//****************** Define funções dos pinos digitais e analógicos **********************************
//****************************************************************************************************
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
const byte ozonizadorPin = 47;  // Pino que liga o ozonizador
const byte reatorPin = 48;      // Pino que liga o CO2 do reator.
const byte sensoresPin = 49;    // Pino que lê os sensores de temperatura
// Pinos 50, 51 e 52 reservados para comunicação SPI
// Pino 53 reservado para "select slave do ethernet shield.
const byte sensor1 = 54;   // A0;      // Pino analógico que verifica se há tensão na bóia da quarentena.
const byte sensor2 = 55;   // A1;      // Pino analógico que verifica se há tensão na bóia inferior do sump.
const byte sensor3 = 56;   // A2;      // Pino analógico que verifica se há tensão na bóia superior do sump.
const byte sensor4 = 57;   // A3;      // Pino analógico que verifica se há tensão na bóia inferior do reservatório.
const byte sensor5 = 58;   // A4;      // Pino analógico que verifica o nível do reef.
const byte sensor6 = 59;   // A5;      // Pino analógico que verifica o nível do fish only.
const byte bomba1Pin = 60; // A6;      // Bomba que tira água da quarentena.
const byte bomba2Pin = 61; // A7;      // Bomba que tira água do sump.
const byte bomba3Pin = 62; // A8;      // Bomba que coloca água no sump.
const byte dosadora1 = 63; // A9;      // Bomba dosadora 1
const byte dosadora2 = 64; // A10;     // Bomba dosadora 2
const byte dosadora3 = 65; // A11;     // Bomba dosadora 3
const byte dosadora4 = 66; // A12;     // Bomba dosadora 4
const byte dosadora5 = 67; // A13;     // Bomba dosadora 5
const byte dosadora6 = 68; // A14;     // Bomba dosadora 6
// Pino 69 (A15) reservado para SS do RFM12B

///**************** PCF8575 **********************************
const byte temporizador1 = 80;       // P0       // Pino que liga o timer 1.
const byte temporizador2 = 81;       // P1       // Pino que liga o timer 2.
const byte temporizador3 = 82;       // P2       // Pino que liga o timer 3.
const byte temporizador4 = 83;       // P3       // Pino que liga o timer 4.
const byte temporizador5 = 84;       // P4       // Pino que liga o timer 5.
const byte solenoide1Pin = 85;       // P5       // Liga a reposicao de água doce.

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
//        (SDA,SCL) Indica em quais pinos o RTC está conectado.
//DS1307 rtc(20, 21);     // Comente esta linha para usar o Ferduino Mega 2560
DS1307 rtc(18, 19);  // Descomente esta linha para usar o Ferduino Mega 2560
Time t_temp, t;

//*******************************************************************************************************
//********************** Variáveis das fuções do touch screen e tela inicial ****************************
//*******************************************************************************************************
UTFT        myGLCD(ITDB32WD, 38,39,40,41);   // "ITDB32WD" é o modelo do LCD
//UTouch      myTouch(6,5,4,3,2);              // Comente esta linha para usar o Ferduino Mega 2560
UTouch      myTouch(7,6,5,4,3);           // Descomente esta linha para usar o Ferduino Mega 2560

unsigned long previousMillis = 0;
String day, ano; 
byte whiteLed, blueLed, azulroyalLed, vermelhoLed, violetaLed;    // Valor anterior de PWM.
byte dispScreen = 0;

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
float HtempMin = 30.5;    // Declara a temperatura para iniciar o funcionamento das ventoinhas do dissipador 
float HtempMax = 40.5;    // Declara que as ventoinhas devem estar em sua velocidade máxima quando o dissipador estiver com 40°c
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
byte cor_canal1[] = {255, 255, 255};  // Branco 
byte cor_canal2[] = {9, 184, 255};    // Azul
byte cor_canal3[] = {58, 95, 205};    // Azul Royal 
byte cor_canal4[] = {255, 0, 0};      // Vermelho
byte cor_canal5[] = {224, 102, 255};  // Violeta

//*****************************************************************************************
//************************ Variáveis da fase lunar ****************************************
//*****************************************************************************************
String LP;
byte MaxI , tMaxI;  // Potência  máxima na Lua cheia.             
byte MinI, tMinI;   // Potência  mínima na Lua nova.
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
Sd2Card card;
SdFile file;
SdFile root;
SdVolume volume;
unsigned long log_SD_millis = 0;

//*****************************************************************************************
//*********************** Variável do controle de níveis **********************************
//*****************************************************************************************
boolean nivel_status = 0;             // Sinaliza nível baixo em um dos aquários

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
boolean Ethernet_Shield = true; // Altere para "false" caso não tenha um Ethernet Shield conectado ao Arduino.

const char *Username  = "fernandogarcia";   // Coloque aqui o nome de usuário cadastrado no joy-reef.com
const char *APIKEY = "ec0245b";           // Cole aqui a ApiKey gerada pelo joy-reef.com

const byte maxima_tentativa = 3;                // Número máximo de tentativas de autenticação.
const byte intervalo_tentativa = 15;   // Tempo  de espera (em minutos) para novas tentativas.

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Este MAC deve ser único na sua rede local.
byte ip[] = {192, 168, 0, 177};                     // Configure o IP conforme a sua rede local.
IPAddress dnsServer(8, 8, 8, 8);                    // Configure o IP conforme a sua rede local. Este é o DNS do Google, geralmente não é necessário mudar.
IPAddress gateway(192, 168, 0, 1);                  // Configure o "Gateway" conforme a sua rede local.
IPAddress subnet(255, 255, 255, 0);                 // Configure a máscara de rede conforme a sua rede local.
EthernetServer server(5000);                        // Coloque aqui o número da porta configurada no seu roteador para redirecionamento.
                                                    // O número da porta deverá ser obrigatóriamente um destes: 80, 5000, 6000, 7000, 8000, 8080 ou 9000.
unsigned long intervalo = 0;
char *inParse[25];
boolean web_teste = false;
byte tentativa = 0;
boolean web_dosage = false;
unsigned long millis_dosagem = 0;
unsigned long millis_enviar = 0;
boolean web_calibracao = false;
const char *token = ":";
char Auth1[50];
unsigned long teste_led_millis = 0; 
//*****************************************************************************************
//************************** Variáveis de controle do multiplexador ***********************
//*****************************************************************************************
#define STAMPS_V4X     // Comente esta linha para usar Stamps EZO
//#define STAMPS_EZO     // Descomente esta linha para usar Stamps EZO
boolean Stamps = false; // Altere para "false" caso não tenha ao menos um dos circuitos de PH, ORP e EC da Atlas Scientific.
unsigned long millis_antes = 0;
const byte ph1 = 0; // Y0
const byte ph2 = 1; // Y1
const byte orp = 2; // Y2
const byte ec = 3;  // Y3

//*****************************************************************************************
//************************** Variáveis da solicitação de senha ****************************
//*****************************************************************************************
char stCurrent[7]="";
char limpar_senha [7] = "";
byte stCurrentLen=0;
const char senha [7] = {'1','2','3','4','5','6','\0'}; // Insira sua senha aqui. O caracter '\0' não deve ser alterado.

//*****************************************************************************************
//************************** Variáveis dosadoras ******************************************
//*****************************************************************************************
boolean dosadoras = false; //Altere para "false" caso não tenha as dosadoras.
const char *arquivo[6] = {"HDP1.TXT","HDP2.TXT","HDP3.TXT","HDP4.TXT","HDP5.TXT","HDP6.TXT"};
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
/*
 boolean PCF8575TS_S = true; // Altere para "false" caso não tenha um PCF8575
 byte endereco_PCF8575TS = 0x20; // Endereço em hexadecimal = 0x20
PCF8575 PCF8575;*/ 

//*****************************************************************************************
//************************** Comunicação RF ***********************************************
//*****************************************************************************************
byte consumo = 0;
/*boolean RFM12B = false; // Altere para "false" caso não tenha um RFM12B
 #define myNodeID 30          // ID do emissor (intervalo 0-30) 
 #define network     210      // Grupo (pode ser no intervalo de 1-250).
 #define freq RF12_915MHZ     // Frequência de RF12B pode ser RF12_433MHZ, RF12_868MHZ ou RF12_915MHZ. Corresponde a frequência do módulo
 typedef struct { int power1, power2, power3, battery; } PayloadTX;      // Cria uma estrutura
 PayloadTX emontx;  
 const byte emonTx_NodeID = 10;            // ID do receptor*/

//*****************************************************************************************
//************************** Dispositivos SPI *********************************************
//*****************************************************************************************
const byte SD_CARD = 0; 
const byte ETHER_CARD = 1;
const byte RFM = 2;
//const byte ChipSelect_SD = 4; // Comente esta linha para usar o Ferduino Mega 2560
const byte ChipSelect_SD = 5;  // Descomente esta linha para usar o Ferduino Mega 2560           
const byte SelectSlave_ETH = 53;
const byte ChipSelect_RFM = 69; // A15

//*****************************************************************************************
//************************* Variáveis da temperatura ambiente *****************************
//*****************************************************************************************
float tempA = 0; // Temperatura ambiente
float temperatura_ambiente_temp = 0; // Temperatura temporária

//*****************************************************************************************
//************************* Variáveis das bombas de circulação ****************************
//*****************************************************************************************
byte modo_selecionado = 1; 
byte Pump1PWM_temp = 0;    
byte Pump2PWM_temp = 0;
int periodo = 10000;
int duracao = 5000; // Duração do ciclo em milisegundos para o modo 3.
unsigned long millis_antes_1 = 0;
byte conta = 0;
byte Pump1PWM = 0;    
byte Pump2PWM = 0;
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
byte *cor_canal[5] = {cor_canal1, cor_canal2, cor_canal3, cor_canal4, cor_canal5};

//*****************************************************************************************
//************************** Textos *******************************************************
//*****************************************************************************************
prog_char string0[] PROGMEM = "POST /ferduino/api/temp HTTP/1.1";
prog_char string1[] PROGMEM = "Host: www.joy-reef.com";
prog_char string2[] PROGMEM = "Authorization: Basic ";
prog_char string3[] PROGMEM = "Cache-Control: no-cache";
prog_char string4[] PROGMEM = "Content-Type: application/x-www-form-urlencoded";
prog_char string5[] PROGMEM = "Connection: Keep-Alive";
prog_char string6[] PROGMEM = "Content-Length: ";
prog_char string7[] PROGMEM = "{\"response\":\"ok\"}";
prog_char string8[] PROGMEM = "HTTP/1.1 200 OK";
prog_char string9[] PROGMEM = "Content-Type: application/json";
prog_char string10[] PROGMEM = "{\"response\":\"000\"}";
prog_char string11[] PROGMEM = "{\"response\":\"001\",\"interval\":\"";

char* tabela_strings[] PROGMEM = 
{
  string0, string1, string2, string3,
  string4, string5, string6, string7,
  string8, string9, string10, string11
};
