//-----------------------main loop------------------------------
void loop()
{
  t = rtc.getTime(); // Atualiza as variáveis que usam o RTC.
  
  LED_levels_output(); // Atualiza a potência de saída dos leds

  checktpa(); // Verifica e executa a TPA automática.

  selecionar_SPI(SD_CARD); // Seleciona disposito SPI que será utilizado.

  logtempgraf(); // Grava temperatura no cartão SD.
  logphagraf(); // Grava o PH do aquário no cartão SD.
  logphrgraf(); // Grava o PH do reator de cálcio no cartão SD.
  logdengraf(); // Grava densidade no cartão SD.
  logorpgraf(); // Grava o ORP no cartão SD.

  if((Ethernet_Shield == true) && (bitRead(tpa_status,1) == false))
  {
    selecionar_SPI(ETHER_CARD); // Seleciona disposito SPI que será utilizado.
    processRequest();
  }
  if(millis() - intervalo > (intervalo_tentativa * 60000)) // Zera o número de tentativas de autenticação após o tempo definido.
  {
   tentativa = 0; 
  }
  
  if (myTouch.dataAvailable())  
  { 
    processMyTouch();  // Verifica se o LCD está sendo tocado e faz o processamento.
  }
  
  if(Stamps == true)
  {
    if((millis() - millis_antes) >= 120000) // Executa as funções a cada 2 minutos.
    {       
      parametros(); // Verifica os "stamps".
      millis_antes = millis(); 
    }
  }

  if((dosadoras == true) && (bitRead(tpa_status,1) == false)) // Verifica e executa as dosagens.
  {
    selecionar_SPI(SD_CARD); // Seleciona disposito SPI que será utilizado.
    check_dosagem_personalizada_1(); // Dosadora 1 - Dosagem personalizado
    check_dosagem_personalizada_2(); // Dosadora 2 - Dosagem personalizado
    check_dosagem_personalizada_3(); //Dosadora 3 - Dosagem personalizado
    check_dosagem_personalizada_4(); // Dosadora 4 - Dosagem personalizado
    check_dosagem_personalizada_5(); // Dosadora 5 - Dosagem personalizado
    check_dosagem_personalizada_6(); //Dosadora 6 - Dosagem personalizado
  }

  if((web_dosage == true) && ((millis() - millis_dosagem) > 10000))
  {
    dosagem_manual();
    web_dosage = false;
  }
  
  if((web_calibracao == true) && ((millis() - millis_dosagem) > 10000))
  {
    calibrar();
    web_calibracao = false;
  }
  
  if ((dispScreen != 22) && (web_teste == false))
  {
    teste_em_andamento = false;
  }
  if ((dispScreen == 3) && (LEDtestTick == true)) // Imprime valores se o teste de todos os leds em andamento.
  {
    testScreen();
  }
  /*  if(RFM12B == true)
   {
   selecionar_SPI(RFM); // Seleciona disposito SPI que será utilizado.
   if (rf12_recvDone())
   {  
   if (rf12_crc == 0 && (rf12_hdr & RF12_HDR_CTL) == 0)
   {
   int node_id = (rf12_hdr & 0x1F);		  //extract nodeID from payload
   if (node_id == emonTx_NodeID)  
   {             //check data is coming from node with the corrct ID
   emontx=*(PayloadTX*) rf12_data;            // Extract the data from the payload 
   }
   }
   }    
   }*/
  
  Wavemaker();
  
  if (dispScreen == 10) // Desenha os gráficos enquanto o menu estiver aberto.
  { 
    Grafico_WaveMaker();
  }
  
  if (millis() - previousMillis > 5000)    // Verifica as funções a cada 5 segundos.
  {  
    checkTempC(); // Verifica as temperaturas.
    reposicao_agua_doce(); // Verifica se há a necessidade reposição da água doce.
    check_nivel(); // Verifica se há algum problema com os níveis dos aquários.
    check_PH_reator(); // Verifica o PH do reatpr de cálcio.
    check_PH_aquario(); // Verifica o PH do aquário.
    check_densidade(); // Verifica a densidade.
    check_ORP(); // Verifica o ORP;
    check_alarme(); // Verifica os alarmes.
    check_temporizadores(); // Ativa ou desativa os timers.
    
    if(LEDtestTick == false) // Atualiza se o teste de todos os leds não estiver em andamento.
    {
    min_cnt = NumMins(t.hour,t.min); // Atualiza o intervalo para determinar a potência dos leds.
    }
    
    if (dispScreen == 0)
    {
      mainScreen();  // Atualiza tela inicial.  
    }
    if(suavizar <= 1)
    {
      suavizar += 0.1;
    }
    /*
     Serial.println("Dia da semana");  
     Serial.println(rtc.getDOWStr()); 
     
     Serial.println("Horario");
     Serial.println(rtc.getTimeStr(FORMAT_LONG));
     
     Serial.println(teste_em_andamento);*/

    Serial.print ("Free memory: ");
    Serial.println (FreeRam());
    /*     Serial.println("Sensor 1:");    
     Serial.println(valor1);
     
     Serial.println("Sensor 2:");
     Serial.println(valor2);
     
     Serial.println("Sensor 3:");
     Serial.println(valor3);
     
     Serial.println("Sensor 4:");
     Serial.println(valor4);
     
     Serial.println("Sensor 5:");    
     Serial.println(valor5);      
     
     Serial.println("Sensor 6:");
     Serial.println(valor6);
     */
  /*   Serial.print("marcadoriniciotpa: ");
     Serial.println(marcadoriniciotpa);
     
     Serial.print("shiftedmillis: ");
     Serial.println(shiftedmillis);
     
     Serial.print("Tempo: ");
     Serial.println(tempo);*/
     /*
     if (digitalRead(bomba1Pin)==HIGH)
     {
     Serial.println("Bomba1: ligada");
     }
     else
     {
     Serial.println("Bomba1: desligada");
     }
     if (digitalRead(bomba2Pin)==HIGH)
     {
     Serial.println("Bomba2: ligada");
     }
     else
     {
     Serial.println("Bomba2: desligada");
     }
     if (digitalRead(bomba3Pin)==HIGH)
     {
     Serial.println("Bomba3: ligada");
     }
     else
     {
     Serial.println("Bomba3: desligada");
     }*/
    previousMillis = millis();
  }
} //-------------------end of main loop





