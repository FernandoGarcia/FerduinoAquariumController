#ifdef USE_TFT
//**********************************************************************************************
//*********************** Botões dos menus *****************************************************
//**********************************************************************************************
const byte temM[] = {
  90, 35, 115, 60
};           //temp. minus
const byte temP[] = {
  205, 35, 230, 60
};          //temp. plus
const byte offM[] = {
  90, 85, 115, 110
};          //offset minus
const byte offP[] = {
  205, 85, 230, 110
};         //offset plus
const byte almM[] = {
  90, 135, 115, 160
};         //alarm minus
const byte almP[] = {
  205, 135, 230, 160
};        //alarm plus
const int iniC[] = {
  325, 2, 390, 42
};           // inicio
const int menU[] = {
  325, 52, 390, 92
};       // Botao menu
const int prOK[] = {
  325, 200, 390, 238
};        //ok
const int salV[] = {
  325, 150, 390, 190
};        //salvar dosagem
const int deS[] = {
  325, 102, 390, 142
};
//const int xxxx[]= {325, 200, 390, 239};
const byte tanD[] = {
  10, 20, 150, 60
};        // Hora e data
const byte tesT[] = {
  10, 70, 150, 110
};       // Testar LED
const byte temC[] = {
  10, 120, 150, 160
};      // Controle de temperatura
const byte graF[] = {
  10, 170, 150, 210
};      // Graficos
const int ledW[] = {
  170, 20, 310, 60
};        // Timers

const int savE[] = {
  180, 203, 300, 235
};        //Save Eeprom
const byte leWB[] = {
  5, 203, 90, 235
};        //LED values show whites or blues
const byte leST[] = {
  100, 203, 170, 235
};       //LED values change

const int tpaA[] = {
  170, 70, 310, 110
};         //TPA automÃ¡tica
const int dosA[] = {
  170, 120, 310, 160
};        //Bomba dosadora
const int wavM[] = {
  170, 170, 310, 210
};        // Wavemaker
const int volT[] = {
  325, 200, 390, 238
};         //voltar
const int testT[] = {
  40, 34, 280, 74
};      //Testar todos os leds
const int testI[] = {
  40, 84, 280, 124
};    //Teste individual dos leds
//-----------botoes graficos e parametros--------------------
const byte tempG[] = {
  10, 20, 150, 60
};        //parametro/grafico de temperatura
const byte phA[] = {
  10, 70, 150, 110
};       //parametro/grafico de ph do aqua
const int phR[] = {
  10, 120, 150, 160
};      //parametro/grafico de ph do aqua
const byte orP[] = {
  10, 170, 150, 210
};      // parametro/grafico de orp
const int denS[] = {
  170, 20, 310, 60
};        //parametro/grafico de densidade
//const int []= {170, 70, 310, 110};
//const int []= {170, 120, 310, 160};

const byte manU[] = {
  10, 20, 150, 60
};        // Dosagem manual
const byte autO[] = {
  10, 70, 150, 110
};       //Dosagem automatica
const byte perS[] = {
  10, 70, 150, 110
};      //Dosagem personalizada
const byte reV[] = {
  10, 120, 150, 160
};     // rever cofig. dosagem personalizada
const int atiV[] = {
  170, 20, 310, 60
};    //Ativar/desativar dosadoras
//const int []= {170, 70, 310, 110};
//const int []= {170, 120, 310, 160};

const byte dosa1[] = {
  10, 20, 150, 60
};       //Bomba dosadora 1
const byte dosa2[] = {
  10, 70, 150, 110
};         //Bomba dosadora 2
const byte dosa3[] = {
  10, 120, 150, 160
};      // Bomba dosadora 3
const int dosa4[] = {
  170, 20, 310, 60
};       //Bomba dosadora 4
const int dosa5[] = {
  170, 70, 310, 110
};         //Bomba dosadora 5
const int dosa6[] = {
  170, 120, 310, 160
};      // Bomba dosadora 6
//----------------------------------------------------

const byte houU[] = {
  70, 18, 95, 43
};          //hour up
const byte minU[] = {
  160, 18, 185, 43
};        //min up
const byte minUT[] = {
  120, 18, 145, 43
};        //minutotpa mais
const byte minDT[] = {
  120, 69, 145, 92
};       //minutotpa menos
const byte houD[] = {
  70, 69, 95, 92
};         //hour down
const byte minD[] = {
  160, 69, 185, 92
};       //min down
const byte dayU[] = {
  70, 102, 95, 127
};       //day up
const byte monU[] = {
  160, 102, 185, 127
};     //month up
const int yeaU[] = {
  250, 102, 275, 127
};     //year up
const byte dayD[] = {
  70, 152, 95, 177
};       //day down
const byte monD[] = {
  160, 152, 185, 177
};     //month down
const int yeaD[] = {
  250, 152, 275, 177
};     //year down
const byte stsT[] = {
  90, 155, 220, 225
};     //start/stop
const byte tenM[] = {
  10, 170, 80, 210
};       //-10s
const int tenP[] = {
  230, 170, 300, 210
};     //+10s
const int segC[] = {
  250, 18, 275, 43
};        //segundo para cima
const int segB[] = {
  250, 69, 275, 92
};        //segundo para baixo
const int durC[] = {
  275, 18, 300, 43
};        //duracao tpa para cima
const int durB[] = {
  275, 69, 300, 92
};        //duracao tpa para baixo
const byte segU[] = {
  30, 99, 110, 139
};        //segunda
const byte terC[] = {
  120, 99, 200, 139
};       //terca
const int quaR[] = {
  210, 99, 290, 139
};       //quarta
const byte quiN[] = {
  30, 146, 110, 186
};       //quinta
const byte sexT[] = {
  120, 146, 200, 186
};      //sexta
const int sabA[] = {
  210, 146, 290, 186
};      //sabado
const byte domI[] = {
  120, 193, 200, 233
};      //domingo
const int caliB[] = {
  170, 170, 310, 210
};     //calibrar
const byte iniciaR[] = {
  120, 193, 200, 233
};   //Iniciar calibracao
const byte anT[] = {
  30, 193, 110, 233
};        //anterior
const int proX[] = {
  210, 193, 290, 233
};      //proximo
const int busC[] = {
  190, 30, 310, 70
};        //Buscar sondas
const int sonD1[] = {
  200, 128, 270, 158
};     //Sonda 1
const int sonD2[] = {
  250, 168, 320, 198
};     //Sonda 2
const int sonD3[] = {
  210, 208, 280, 238
};     //Sonda 3
const int tempeC[] = {
  265, 35, 290, 60
};      //Temperatura reduzir potência +
const int tempeB[] = {
  265, 70, 290, 95
};      //Temperatura reduzir potência -
const int potC[] = {
  265, 115, 290, 140
};      //Reduzir potência +
const int potB[] = {
  265, 150, 290, 175
};      //Reduzir potência -
const byte peRB[] = {
  45, 145, 70, 170
};
const byte peRC[] = {
  160, 145, 185, 170
};
const byte PoTEB1[] = {
  45, 115, 70, 140
};
const byte PoTEC1[] = {
  160, 115, 185, 140
};
const byte PoTEB2[] = {
  45, 185, 70, 210
};
const byte PoTEC2[] = {
  160, 185, 185, 210
};
const byte minUA[] = {
  120, 110, 145, 135
};   // Tempo alimentação mais
const byte minDA[] = {
  120, 160, 145, 185
};   // Tempo alimentação menos
const int alI[] = {
  200, 120, 280, 160
};      // Alimentador
const int waV[] = {
  200, 180, 280, 220
};      // Wavemaker

//----------------botoes solicitacao de senha-------------------------------------------------
const byte boT1[] = {
  10, 20, 62, 60
};          //Botao um
const byte boT2[] = {
  72, 20, 124, 60
};         //Botao dois
const byte boT3[] = {
  134, 20, 186, 60
};        //Botao tres
const byte boT4[] = {
  196, 20, 248, 60
};        //Botao quatro
const int boT5[] = {
  258, 20, 310, 60
};        //Botao cinco
const byte boT6[] = {
  10, 70, 62, 110
};          //Botao seis
const byte boT7[] = {
  72, 70, 124, 110
};        //Botao sete
const byte boT8[] = {
  134, 70, 186, 110
};       //Botao oito
const byte boT9[] = {
  196, 70, 248, 110
};       //Botao nove
const int boT0[] = {
  258, 70, 310, 110
};       //Botao zero
const byte boTL[] = {
  10, 120, 155, 160
};       //Botao limpar
const int boTE[] = {
  165, 120, 310, 160
};      //Botao entrar

//**********************************************************************************************
//***************************** funcoes ********************************************************
//**********************************************************************************************
void clearScreen()
{
  myGLCD.clrScr();
}

void printButton(const char* text, int x1, int y1, int x2, int y2, boolean setFont = false, byte cor = 0)
{
  int stl = strlen(text);
  int fx, fy;
  const byte color [3][3] = {{0, 0, 200}, {0, 150, 86}, {255, 0, 0}};

  myGLCD.setColor(color[cor][0], color[cor][1], color[cor][2]);
  myGLCD.fillRoundRect (x1, y1, x2, y2);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);

  myGLCD.setBackColor(color[cor][0], color[cor][1], color[cor][2]);
  if (setFont == true)
  {
    myGLCD.setFont(BigFont);
    fx = x1 + (((x2 - x1 + 1) - (stl * 16)) / 2);
    fy = y1 + (((y2 - y1 + 1) - 16) / 2);
    myGLCD.print(text, fx, fy);
  }
  else
  {
    myGLCD.setFont(RusFont1);
    fx = x1 + (((x2 - x1) - (stl * 8)) / 2);
    fy = y1 + (((y2 - y1 - 1) - 6) / 2);
    myGLCD.print(text, fx, fy);
  }
}

void printHeader(char* headline)
{
  setFont(SMALL, 255, 255, 0, 255, 255, 0);
  myGLCD.fillRect (1, 1, 319, 14);
  myGLCD.setColor(0, 0, 0);
  myGLCD.print(headline, 5, 4);
}

void setFont(boolean font, byte cr, byte cg, byte cb, byte br, byte bg, byte bb)
{
  myGLCD.setBackColor(br, bg, bb);    //font background black
  myGLCD.setColor(cr, cg, cb);      //font colour white
  if (font == LARGE)
    myGLCD.setFont(BigFont);     //font size LARGE
  else if (font == SMALL)
    myGLCD.setFont(RusFont1);
}

// Draw a red frame while a button is touched
void waitForIt(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
  {
    myTouch.read();
  }
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
}

//                   cor,       cor,   cor    locação x1, locação y1, locação x2, locação y2
void desenhar_barras(int sbR, int sbG, int sbB, int sbX1, int sbY1, int sbX2, int sbY2)
{
  drawFillRect(sbX1, y_tocado, sbX2, sbY2, sbR, sbG, sbB);
  drawFillRect(sbX1 + 1, y_tocado, sbX2 - 1, sbY1, 0, 0, 0);
  myGLCD.setColor(sbR, sbG, sbB);
  myGLCD.drawLine(sbX1, sbY1, sbX2, sbY1);
  myGLCD.drawLine(sbX1, sbY2, sbX2, sbY2);
}

void desenhar_barras_periodo ()
{
  myGLCD.setColor(cor_canal [cor_selecionada][0], cor_canal [cor_selecionada][1], cor_canal [cor_selecionada][2]);
  myGLCD.drawRect((setor_selecionado * 38) + 5, 80, (setor_selecionado * 38) + 39, 195);
  desenhar_barras(cor_canal [cor_selecionada][0], cor_canal [cor_selecionada][1], cor_canal [cor_selecionada][2], (setor_selecionado * 38) + 5, 80, (setor_selecionado * 38) + 39, 195);
}

boolean checkButtons(int x1, int y1, int x2, int y2)
{
  boolean match = false;
  int touch_x = myTouch.getX();
  int touch_y = myTouch.getY();

  if ((touch_x >= x1) && (touch_x <= x2) && (touch_y >= y1) && (touch_y <= y2))
  {
    match = true;
    waitForIt(x1, y1, x2, y2);
  }
  return match;
}

void drawFillRect(int x1, byte y1, int x2, byte y2, byte r, byte g, byte b)
{
  myGLCD.setColor(r, g, b);
  myGLCD.fillRect (x1, y1, x2, y2);
}
#endif

#ifdef USE_SCREENSAVER
void clockScreen()
{
  if (firstTime == true)
  {
    clearScreen();
  }
  myGLCD.setFont(SevenSegNumFontPlus);
  myGLCD.setColor(0, 174, 255);
  myGLCD.print(rtc.getTimeStr(FORMAT_LONG), CENTER, 100);

  myGLCD.setFont(BigFont);

  myGLCD.print(rtc.getDOWStr(FORMAT_SHORT), 99, 170);
  myGLCD.print(",", 150, 170);

  if (t.date < 10)
  {
    myGLCD.print("0", 169, 170);
    myGLCD.printNumI(t.date, 185, 170);
  }
  else
  {
    myGLCD.printNumI(t.date, 169, 170);
  }
  myGLCD.print("DE", 211, 170);
  myGLCD.print(rtc.getMonthStr(FORMAT_SHORT), 253, 170);
  firstTime = false;
}
#endif

int NumMins(uint8_t ScheduleHour, uint8_t ScheduleMinute)
{
  return (ScheduleHour * 60) + ScheduleMinute;
}

void myPinMode(int pin, boolean mode)
{
  if ((pin >= 0) && (pin <= MAX_PIN_NUMBER))
  {
    pinMode(pin, mode);
  }
  else
  {

  }
}

void myDigitalWrite(int pin, boolean level)
{
  if ((pin >= 0) && (pin <= MAX_PIN_NUMBER))
  {
    digitalWrite(pin, level);
  }
  else
  {

  }
}

void myAnalogWrite(int pin, byte pwm)
{
  if ((pin >= 0) && (pin <= MAX_PIN_NUMBER))
  {
    analogWrite(pin, pwm);
  }
  else
  {

  }
}

int myAnalogRead(int pin)
{
  int value = 6666;

  if ((pin >= 0) && (pin <= MAX_PIN_NUMBER))
  {
    value = analogRead(pin);
  }
  else
  {

  }
  return value;
}

