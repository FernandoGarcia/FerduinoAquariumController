//------------------------setup------------------------------
void setup()
{
  Serial.begin(38400); //Inicia a comunicação com a  porta serial 0 para obter mensagens de depuração.
  Serial3.begin(38400); //Inicia a comunicação com a  porta serial 2 onde estão conectados os "stamps".
  pinMode(alarmPin, OUTPUT);               // Pino 0;
  pinMode(desativarFanPin, OUTPUT);        // Pino 1;
  pinMode (ChipSelect_RFM, OUTPUT);        // Pino 2;

  pinMode (ChipSelect_SD, OUTPUT);         // Pino 4;

  pinMode(ledPinUV, OUTPUT);               // Pino 8;
  pinMode(ledPinBlue, OUTPUT);             // Pino 9; 
  pinMode(ledPinWhite, OUTPUT);            // Pino 10;
  pinMode(ledPinRoyBlue, OUTPUT);          // Pino 11;
  pinMode(ledPinRed, OUTPUT);              // Pino 12;
  pinMode(fanPin, OUTPUT);                 // Pino 13;
  pinMode(multiplexadorS0Pin, OUTPUT);     // Pino 16;
  pinMode(multiplexadorS1Pin, OUTPUT);     // Pino 17;


  pinMode(aquecedorPin, OUTPUT);           // Pino 42;
  pinMode(chillerPin, OUTPUT);             // Pino 43;
  pinMode(ledPinMoon, OUTPUT);             // Pino 44;
  pinMode(wavemaker1, OUTPUT);             // Pino 45;
  pinMode(wavemaker2, OUTPUT);             // Pino 46;
  pinMode(ozonizadorPin, OUTPUT);          // Pino 47;
  pinMode(reatorPin, OUTPUT);              // Pino 48;

  pinMode (SelectSlave_ETH, OUTPUT);       // Pino 53;

  pinMode (sensor1, INPUT);                // Pino A0;
  pinMode (sensor2, INPUT);                // Pino A1;
  pinMode (sensor3, INPUT);                // Pino A2;
  pinMode (sensor4, INPUT);                // Pino A3;
  pinMode (sensor5, INPUT);                // Pino A4;
  pinMode (sensor6, INPUT);                // Pino A5;
  pinMode(bomba1Pin, OUTPUT);              // Pino A6;    
  pinMode(bomba2Pin, OUTPUT);              // Pino A7;  
  pinMode(bomba3Pin, OUTPUT);              // Pino A8; 
  pinMode (dosadora1, OUTPUT);             // Pino A9;
  pinMode (dosadora2, OUTPUT);             // Pino A10;
  pinMode (dosadora3, OUTPUT);             // Pino A11;
  pinMode (dosadora4, OUTPUT);             // Pino A12;
  pinMode (dosadora5, OUTPUT);             // Pino A13;
  pinMode (dosadora6, OUTPUT);             // Pino A14;

  //**************** PCF8575 ****************
  pinMode (temporizador1, OUTPUT);         // Pino 80;
  pinMode (temporizador2, OUTPUT);         // Pino 81;
  pinMode (temporizador3, OUTPUT);         // Pino 82;
  pinMode (temporizador4, OUTPUT);         // Pino 83;
  pinMode (temporizador5, OUTPUT);         // Pino 84;
  pinMode (solenoide1Pin, OUTPUT);         // Pino 85;




  myGLCD.InitLCD(LANDSCAPE); // Orientação da imagem no LCD.
  clearScreen(); // Limpa o LCD.

  myTouch.InitTouch(LANDSCAPE); // Orientação do "touch screen".
  myTouch.setPrecision(PREC_MEDIUM); // Define a precisão do "touch screen".
  ReadDallasAddress ();
  sensors.begin();     //Inicia as leituras das sondas de temperatura.
  sensors.setResolution(sensor_agua, 10); // Define a resolução em 10 bits.
  sensors.setResolution(sensor_dissipador, 10); // Define a resolução em 10 bits.
  sensors.requestTemperatures();   // Chamada para todos os sensores.
  tempC = (sensors.getTempC(sensor_agua));  // Lê a temperatura da água
  tempH = (sensors.getTempC(sensor_dissipador)); // Lê a temperatura do dissipador.
  tempA = (sensors.getTempC(sensor_ambiente)); // Lê a temperatura do ambiente.

  /*  if(PCF8575TS_S == true)
   {
   PCF8575.begin(endereco_PCF8575TS); // Inicia a comunicação com o PCF8575TS
   for(int i = 0; i < 16; i++)
   {
   PCF8575.pinMode(i, OUTPUT);
   delay(100);
   PCF8575.digitalWrite(i, LOW);
   }
   }*/

  rtc.halt(false); // Inicia o funcionamento do RTC.

  byte k =  EEPROM.read(0);

  if(k != 222) // Verifica se a EEPROM foi formatada por este programa
  { 
    setFont(LARGE, 255, 0, 0, 0, 0, 0);

    strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[225]))); // "FORMATANDO A EEPROM..."
    myGLCD.print(buffer, CENTER, 115);

    EEPROM.write(0, 222); // Indica que a EEPROM foi formatada por este programa  

    for (int i = 1; i < 4096; i++)
    {
      EEPROM.write(i, 0);
    }
  }

  k =  EEPROM.read(796); // Copia valores dos LEDs para a eeprom.
  
  if(k != 222)
  {
    SaveLEDToEEPROM();
  }

  //Lê a variáveis guardadas na EEPROM.

  ReadFromEEPROM();
  lertpaEEPROM();
  lerPHAEEPROM();
  lerPHREEPROM();
  lerORPEEPROM();
  lerDENEEPROM();
  ler_dosadora_EEPROM();
  ler_luz_noturna_EEPROM();
  ler_timers_EEPROM();
  ler_coolersEEPROM();
  ler_tempPotEEPROM();
  ler_wave_EEPROM();
  ler_calib_dosadora_EEPROM();
  ler_predefinido_EEPROM();

  selecionar_SPI(SD_CARD); // Seleciona disposito SPI que será utilizado.
  while(!card.init(SPI_FULL_SPEED, ChipSelect_SD)) // Inicia a comunicação com o cartão SD.
  {
    Serial.println("Please insert a SD card.");  
  }
  
  volume.init(&card);
  root.openRoot(&volume);

  t = rtc.getTime(); // Atualiza as variáveis que usam o RTC.  
  check_arquivo_temp_agua();
  check_arquivo_ph_agua();
  check_arquivo_ph_reator();
  check_arquivo_orp();
  check_arquivo_densidade();

  if(Stamps == true)
  {
    iniciar_stamps();
  }

  if(Ethernet_Shield == true)
  {
    selecionar_SPI(ETHER_CARD); // Seleciona disposito SPI que será utilizado.
    
    Ethernet.begin(mac, ip); // Comente esta linha para usar o W5100.
    //Ethernet.begin(mac, ip, SelectSlave_ETH); // Descomente esta linha para usar o W5100.
    
    server.begin();
    
    Serial.print("Ip Server: ");
    Serial.println(Ethernet.localIP());
  }
  
  /*  if(RFM12B == true)
   {
   selecionar_SPI(RFM); // Seleciona disposito SPI que será utilizado.
   rf12_initialize(myNodeID,freq,network);   //Initialize RFM12 with settings defined above  
   }*/
  clearScreen(); // Limpa o LCD.
  mainScreen(true); // Exibe a tela inicial no LCD.
}







