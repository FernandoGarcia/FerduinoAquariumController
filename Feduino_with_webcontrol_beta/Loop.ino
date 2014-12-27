//-----------------------main loop------------------------------
void loop()
{
  t = rtc.getTime(); // Atualiza as variáveis que usam o RTC.

  LED_levels_output(); // Atualiza a potência de saída dos leds

  checktpa(); // Verifica e executa a TPA automática.

  if((millis() - log_SD_millis) > 60000) // Executa funções a cada 1 minuto.
  {
    selecionar_SPI(SD_CARD); // Seleciona disposito SPI que será utilizado.

    logtempgraf(); // Grava temperatura no cartão SD.
    logphagraf(); // Grava o PH do aquário no cartão SD.
    logphrgraf(); // Grava o PH do reator de cálcio no cartão SD.
    logdengraf(); // Grava densidade no cartão SD.
    logorpgraf(); // Grava o ORP no cartão SD.
    log_SD_millis = millis();
  }

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
      check_parametro_ph_reator(); // Verifica os "stamps".
      check_parametro_orp(); 
      //      check_parametro_densidade(); 
      check_parametro_ph_aquario();
      millis_antes = millis(); 
    }
  }

  if((dosadoras == true) && (bitRead(tpa_status,1) == false)) // Verifica e executa as dosagens.
  {
    if((millis() - dosadoras_millis) > 60000) // Verifica funções a cada 1 minuto.
    {
      selecionar_SPI(SD_CARD); // Seleciona disposito SPI que será utilizado.
      dosadoras_millis = millis();
      check_dosagem_personalizada(); // Dosadora 1 - Dosagem personalizado
    }
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

  if((millis() - millis_enviar) > 120000)
  {
    if((Ethernet_Shield == true) && (bitRead(tpa_status,1) == false))
    {
      selecionar_SPI(ETHER_CARD); // Seleciona disposito SPI que será utilizado.
      enviar_dados();
      millis_enviar = millis();
    }  
  }

  if ((dispScreen != 22) && (web_teste == false))
  {
    teste_em_andamento = false;
  }
  if(web_teste == true)
  {
    if((millis() - teste_led_millis) > 600000)
    {
      web_teste = false;
      teste_em_andamento = false;
      ler_predefinido_EEPROM();
    } 
  }

  if ((dispScreen == 3) && (LEDtestTick == true)) // Imprime valores se o teste de todos os leds em andamento.
  {
    testScreen();
  }

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
    /*  Serial.println();
     Serial.print("Day of week: ");  
     Serial.println(rtc.getDOWStr()); 
     
     Serial.print("Time: ");
     Serial.println(rtc.getTimeStr(FORMAT_LONG));*/

    Serial.print (F("Free memory: "));
    Serial.println (FreeRam());
    /*
    Serial.print("Sensor 1: ");    
     Serial.println(analogRead(A0));
     
     Serial.print("Sensor 2: ");
     Serial.println(analogRead(A1));
     
     Serial.print("Sensor 3: ");
     Serial.println(analogRead(A2));
     
     Serial.print("Sensor 4: ");
     Serial.println(analogRead(A3));
     
     Serial.print("Sensor 5: ");    
     Serial.println(analogRead(A4));      
     
     Serial.print("Sensor 6: ");
     Serial.println(analogRead(A5));
     
     Serial.print("marcadoriniciotpa: ");
     Serial.println(marcadoriniciotpa);
     
     Serial.print("shiftedmillis: ");
     Serial.println(shiftedmillis);
     
     Serial.print("Duration for stage: ");
     Serial.print(tempo/60000);
     Serial.println(" minutes");
     
     if (digitalRead(bomba1Pin)==HIGH)
     {
     Serial.println("Pump 1: ON");
     }
     else
     {
     Serial.println("Pump 1: OFF");
     }
     if (digitalRead(bomba2Pin)==HIGH)
     {
     Serial.println("Pump 2: ON");
     }
     else
     {
     Serial.println("Pump 2: OFF");
     }
     if (digitalRead(bomba3Pin)==HIGH)
     {
     Serial.println("Pump 3: ON");
     }
     else
     {
     Serial.println("Pump 3: OFF");
     }*/
    previousMillis = millis();
  }
} //-------------------end of main loop
