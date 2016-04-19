//-----------------------main loop------------------------------
void loop()
{
  t = rtc.getTime(); // Atualiza as variáveis que usam o RTC.

  LED_levels_output(); // Atualiza a potência de saída dos leds

  checktpa(); // Verifica e executa a TPA automática.

  if ((millis() - log_SD_millis) > 60000) // Executa funções a cada 1 minuto.
  {
    selecionar_SPI(SD_CARD); // Seleciona disposito SPI que será utilizado.

    logtempgraf(); // Grava temperatura no cartão SD.
    logphagraf(); // Grava o PH do aquário no cartão SD.
    logphrgraf(); // Grava o PH do reator de cálcio no cartão SD.
    logdengraf(); // Grava densidade no cartão SD.
    logorpgraf(); // Grava o ORP no cartão SD.
    log_SD_millis = millis();
  }

  if ((dosadoras == true) && (bitRead(tpa_status, 1) == false)) // Verifica e executa as dosagens.
  {
    if ((modo_alimentacao == false) || ((millis() < alimentacao_millis) && (modo_alimentacao == true)))
    {
      if ((millis() - dosadoras_millis) > 60000) // Verifica funções a cada 1 minuto.
      {
#ifdef WATCHDOG
        wdt_disable();
#endif
        selecionar_SPI(SD_CARD); // Seleciona disposito SPI que será utilizado.
        dosadoras_millis = millis();
        check_dosagem_personalizada(); // Dosagem personalizada
#ifdef WATCHDOG
        wdt_enable(WDTO_8S);
#endif
      }
    }
  }

#ifdef ETHERNET_SHIELD
  if ((millis() - close_millis) > 1000)
  {
    selecionar_SPI(ETHER_CARD); // Seleciona disposito SPI que será utilizado.
    checkSockStatus();
    close_millis = millis();
  }

  if (bitRead(tpa_status, 1) == false)
  {
    selecionar_SPI(ETHER_CARD); // Seleciona disposito SPI que será utilizado.
    processRequest();
  }

  if ((millis() - millis_enviar) > 120000)
  {
    if (bitRead(tpa_status, 1) == false)
    {
      selecionar_SPI(ETHER_CARD); // Seleciona disposito SPI que será utilizado.
      enviar_dados();
      millis_enviar = millis();
    }
  }

  if (millis() - intervalo > (intervalo_tentativa * 60000)) // Zera o número de tentativas de autenticação após o tempo definido.
  {
    tentativa = 0;
  }

  if (outlets_settings == true)
  {
    if ((millis() - outlets_millis) > 300000) // Lê os valores da EEPROM se as configurações não forem salvas em até 5 minutos
    {
      for (byte i = 0; i < 9; i++)
      {
        outlets_changed[i] = true;
      }
      ler_outlets_EEPROM();
      outlets_settings = false;
    }
  }
#endif

#ifdef USE_TFT
  if (myTouch.dataAvailable())
  {
#ifdef USE_SCREENSAVER
    if (((millis() - previousMillis_2) > (interval * 1000UL)) && (dispScreen == 0))
    {
      clearScreen();
      mainScreen(true);
    }
    else
    {
      processMyTouch();
    }
    previousMillis_2 = millis();
#else
    processMyTouch();  // Verifica se o LCD está sendo tocado e faz o processamento.
#endif
  }
#endif

#ifdef WATCHDOG
  wdt_reset();
#endif

#if defined(STAMPS_EZO) || defined(STAMPS_V4X)
  if ((millis() - millis_antes) >= 120000) // Executa as funções a cada 2 minutos.
  {
    check_parametro_ph_reator(); // Verifica os "stamps".
    check_parametro_orp();
    //      check_parametro_densidade();
    check_parametro_ph_aquario();
    millis_antes = millis();
  }
#endif

#ifdef ETHERNET_SHIELD
  if ((web_dosage == true) && ((millis() - millis_dosagem) > 10000))
  {
#ifdef WATCHDOG
    wdt_disable();
#endif
    dosagem_manual();
    web_dosage = false;
#ifdef WATCHDOG
    wdt_enable(WDTO_8S);
#endif
  }

  if ((web_calibracao == true) && ((millis() - millis_dosagem) > 10000))
  {
#ifdef WATCHDOG
    wdt_disable();
#endif
    calibrar();
    web_calibracao = false;
#ifdef WATCHDOG
    wdt_enable(WDTO_8S);
#endif
  }
#endif

#if defined(RFM12B_LED_CONTROL) || defined(RFM12B_RELAY_CONTROL)
  if ((millis() - lastPeriod_millis) > 5000)
  {
    if (millis() > 20000)
    {
      selecionar_SPI(RFM); // Seleciona disposito SPI que será utilizado.
#ifdef RFM12B_LED_CONTROL
      RF_LED();
#endif
#ifdef RFM12B_RELAY_CONTROL
      RF_RELAY();
#endif
    }
    lastPeriod_millis = millis();
  }
#endif

  if ((dispScreen != 22) && (web_teste == false))
  {
    teste_em_andamento = false;
  }

#ifdef ETHERNET_SHIELD
  if (web_teste == true)
  {
    if ((millis() - teste_led_millis) > 600000)
    {
      web_teste = false;
      teste_em_andamento = false;
      ler_predefinido_EEPROM();
    }
  }
#endif

#ifdef USE_TFT
  if ((dispScreen == 3) && (LEDtestTick == true)) // Imprime valores se o teste de todos os leds em andamento.
  {
    testScreen();
  }
#endif

  Wavemaker();

#ifdef USE_TFT
  if (dispScreen == 10) // Desenha os gráficos enquanto o menu estiver aberto.
  {
    if ((modo_alimentacao == false) || (wavemaker_on_off == false))
    {
      Grafico_WaveMaker();
    }
  }
#endif

  if (modo_alimentacao == true) // Função que desliga alimentador automático.
  {
    if (millis() >= alimentacao_millis)
    {
      if ((millis() - alimentacao_millis) > (duracao_alimentacao * 1000L))
      {
        modo_alimentacao = false;
        if (dispScreen == 45)
        {
          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[17])));
          printButton(buffer, anT[0], anT[1], anT[2], anT[3]); // tabela_textos[17] = "INICIAR"
        }
      }
    }
  }

  if (wavemaker_on_off == true) // Função que liga o wavemaker após o período de alimentação.
  {
    if ((millis() - wavemaker_on_off_millis) > (desligar_wavemaker * 60000))
    {
      wavemaker_on_off = false;
    }
  }

  if ((millis() - check_alimentador_millis) > 60000)
  {
    check_alimentador(); // Verifica agendamendo do alimentador.
    check_alimentador_millis = millis();
  }

  alimentador_automatico(); // Liga ou desliga o alimentador automático.

  if (millis() - previousMillis > 5000)    // Verifica as funções a cada 5 segundos.
  {
    checkTempC();           // Verifica as temperaturas.
    reposicao_agua_doce();  // Verifica se há a necessidade reposição da água doce.
    check_nivel();          // Verifica se há algum problema com os níveis dos aquários.
    check_PH_reator();      // Verifica o PH do reatpr de cálcio.
    check_PH_aquario();     // Verifica o PH do aquário.
    check_densidade();      // Verifica a densidade.
    check_ORP();            // Verifica o ORP;
    check_alarme();         // Verifica os alarmes.
    check_temporizadores(); // Ativa ou desativa os timers.

#ifdef DISABLE_SKIMMER
    check_level_skimmer();  // desativa o skimmer para evitar transbordamento.
#endif

    if (LEDtestTick == false)          // Atualiza se o teste de todos os leds não estiver em andamento.
    {
      min_cnt = NumMins(t.hour, t.min); // Atualiza o intervalo para determinar a potência dos leds.
    }

#ifdef USE_TFT
    if (dispScreen == 0)
    {
#ifdef USE_SCREENSAVER
      if ((millis() - previousMillis_2) > (interval * 1000UL))
      {
        clockScreen();  // atualiza o protetor de tela
      }
      else
      {
        mainScreen();  // Atualiza tela inicial.
        firstTime = true;
      }
#else
      mainScreen();  // Atualiza tela inicial.
#endif
    }
#endif

    if (suavizar <= 1)
    {
      suavizar += 0.1;
    }
#ifdef DEBUG
    /*  Serial.println();
      Serial.print("Day of week: ");
      Serial.println(rtc.getDOWStr());

      Serial.print("Time: ");
      Serial.println(rtc.getTimeStr(FORMAT_LONG));*/

    Serial.print(F("Free memory: "));
    Serial.println(FreeRam());
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
#endif
    previousMillis = millis();
  }

} //-------------------end of main loop











