//*************************************************************************************************
//************************* Inclusão de configurações *********************************************
//*************************************************************************************************
#include "../Configuration.h" // Do not change this line

//*************************************************************************************************
//************************* Variáveis globais *****************************************************
//*************************************************************************************************
const char lastUpdate[] = "29/09/2018"; // Data da última modificação
#define MAX_PIN_NUMBER 69 // Numero de pinos disponíveis no Arduino Mega.

//****************************************************************************************************
//****************** Variáveis de textos e fontes ****************************************************
//****************************************************************************************************
#ifdef USE_TFT // Do not change this line
#define LARGE true
#define SMALL false
extern uint8_t RusFont1[];    // Declara que fontes vamos usar
extern uint8_t BigFont[];     // Declara que fontes vamos usar
#endif
char buffer[50];

#ifdef USE_SCREENSAVER //Do not change this line
extern uint8_t SevenSegNumFontPlus[];
#endif // Do not change this line


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
DS1307 rtc(20, 21);  // (SDA,SCL) Indica em quais pinos o RTC está conectado.
#endif // Do not change this line
Time t_temp, t;

//*******************************************************************************************************
//********************** Variáveis das fuções do touch screen e tela inicial ****************************
//*******************************************************************************************************
#ifdef USE_TFT // Do not change this line
UTFT        myGLCD(TFT_MODEL, 38, 39, 40, 41); // "ITDB32WD" é o modelo do LCD
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
float temp_AUX = 0;            // Variável que armazena temperatura enviado pelo hidrômetro.
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
int DEN_AUX = 0;             // Variável de densidade auxiliar para ser usar usada com o densímetro digital (iSpindel)
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
unsigned int duracaoNuvem = 0;
unsigned int duracaoRelampago = 0;
byte quantNuvens = 0;
int horaNuvem[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Em minutos.
boolean executandoNuvem = false;
boolean executarAgora = false;
unsigned long millis_nuvem = 0;
int lastMinute = 0;
unsigned int espere = 0;
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
const byte limite_falha = 30;                        // Reseta o controlador após 30 tentativas de upload para Ferduino. Utilize sempre um valor maior ou igual a 3.

#ifndef USE_ESP8266 //Do not change this line
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

//*************************************************************************************************
//****************************** Depuração ********************************************************
//*************************************************************************************************
#ifdef DEBUG
  #define LOG(...) Serial.print(__VA_ARGS__)
  #define LOGLN(...) Serial.println(__VA_ARGS__)
#else
  #define LOG(...)
  #define LOGLN(...)
#endif
