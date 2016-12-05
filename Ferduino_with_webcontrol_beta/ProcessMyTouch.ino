#ifdef USE_TFT
//-------------------------------------------Touch screen----------------------------
void processMyTouch()
{
  myTouch.read();
  int x, y;                  // Coordenadas do touch screen
#ifndef INVERT_TOUCH
  x = myTouch.getX();
  y = myTouch.getY();
#else
  x = 399 - myTouch.getX(); // Inverte as coordenadas X 
  y = 239 - myTouch.getY(); // Inverte as coordenadas Y 
#endif

  if (temperatura_alta == false) // Limpa mensagem de que a temperatura dos leds esteve alta.
  {
    temperatura_baixou = false;
  }
  if ((checkButtons(iniC[0], iniC[1], iniC[2], iniC[3]) == true) && (dispScreen != 0) && (LEDtestTick == false) && (horario_alterado == false)) // volta ao inicio
  {
    if ((dispScreen == 5) || (dispScreen == 28))
    {
      ReadFromEEPROM();
    }
    else if (dispScreen == 10)
    {
      ler_wave_EEPROM();
    }
    else if (dispScreen == 30)
    {
      stCurrentLen = 0;
      memcpy(stCurrent, limpar_senha, sizeof(limpar_senha));
    }
    else if (dispScreen == 22)
    {
      ler_predefinido_EEPROM();
    }
    periodo_selecionado = false;
    dispScreen = 0;
    clearScreen();
    mainScreen(true);

  }
  else
  {
    switch (dispScreen)
    {
      case 0:                       //Tela de inico

#ifdef SKIP_PASSWORD_SCREEN
        dispScreen = 1;
        clearScreen();
        menuScreen();
#else
        dispScreen = 30;
        clearScreen();
        solicitar_senha();
#endif
        break;
      case 1:     //------------------------------------Tela de menu-------------------------------------------------
        if (checkButtons(tanD[0], tanD[1], tanD[2], tanD[3]) == true)            // Seleciona o menu "Hora e data"
        {
          dispScreen = 2;
          clearScreen();
          setClock(true);
        }
        else if (checkButtons(tesT[0], tesT[1], tesT[2], tesT[3]) == true)        // Seleciona o menu "Configurar LED's"
        {
          dispScreen = 40;
          clearScreen();
          config_leds();
        }
        else if (checkButtons(temC[0], temC[1], temC[2], temC[3]) == true)        // Seleciona o menu "Controle de parâmetros"
        {
          dispScreen = 14;
          clearScreen();
          parametroScreen();
        }
        else if (checkButtons(graF[0], graF[1], graF[2], graF[3]) == true)        // Seleciona o menu "Gráficos"
        {
          dispScreen = 9;
          clearScreen();
          graficoScreen();
        }
        else if (checkButtons(ledW[0], ledW[1], ledW[2], ledW[3]) == true)        // Seleciona o menu "Timers"
        {
          dispScreen = 38;
          clearScreen();
          TimerScreen();
        }
        else if (checkButtons(tpaA[0], tpaA[1], tpaA[2], tpaA[3]) == true)          // Seleciona o menu "TPA automática"
        {
          dispScreen = 7;
          clearScreen();
          tpaScreen(true);
        }
        else if (checkButtons(dosA[0], dosA[1], dosA[2], dosA[3]) == true)          // Seleciona o menu "Dosadoras"
        {
          dispScreen = 8;
          clearScreen();
          menu_dosadoras();
        }
        else if (checkButtons(wavM[0], wavM[1], wavM[2], wavM[3]) == true)          // Seleciona o menu "Wavemaker"
        {
          dispScreen = 10;
          clearScreen();
          waveScreen(true);
        }
        else if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // Seleciona o "Menu 2"
        {
          dispScreen = 37;
          clearScreen();
          menuScreen_2();
        }
        break;

      case 2:    // -------------------------------------Tela configuracao data e hora---------------------
        if (checkButtons(houU[0], houU[1], houU[2], houU[3]) == true)
        {
          t_temp.hour = (t_temp.hour + 1) % 24;
          setClock();
        }
        else if (checkButtons(minU[0], minU[1], minU[2], minU[3]) == true)
        {
          t_temp.min = (t_temp.min + 1) % 60;
          setClock();
        }
        else if (checkButtons(segC[0], segC[1], segC[2], segC[3]) == true)
        {
          t_temp.sec = (t_temp.sec + 1) % 60;
          setClock();
        }
        else if (checkButtons(houD[0], houD[1], houD[2], houD[3]) == true)
        {
          t_temp.hour = (t_temp.hour + 23) % 24;
          setClock();
        }
        else if (checkButtons(minD[0], minD[1], minD[2], minD[3]) == true)
        {
          t_temp.min = (t_temp.min + 59) % 60;
          setClock();
        }
        else if (checkButtons(segB[0], segB[1], segB[2], segB[3]) == true)
        {
          t_temp.sec = (t_temp.sec + 59) % 60;
          setClock();
        }
        else if (checkButtons(dayU[0], dayU[1], dayU[2], dayU[3]) == true)
        {
          t_temp.date += 1;
          if (t_temp.date > 31)
          {
            t_temp.date = 1;
          }
          t_temp.date = validateDate(t_temp.date, t_temp.mon, t_temp.year);
          setClock();
        }
        else if (checkButtons(monU[0], monU[1], monU[2], monU[3]) == true)
        {
          t_temp.mon += 1;
          if (t_temp.mon > 12)
          {
            t_temp.mon = 1;
          }
          t_temp.date = validateDateForMonth(t_temp.date, t_temp.mon, t_temp.year);
          setClock();
        }
        else if (checkButtons(yeaU[0], yeaU[1], yeaU[2], yeaU[3]) == true)
        {
          t_temp.year += 1;
          t_temp.date = validateDateForMonth(t_temp.date, t_temp.mon, t_temp.year);
          setClock();
        }
        else if (checkButtons(dayD[0], dayD[1], dayD[2], dayD[3]) == true)
        {
          t_temp.date -= 1;
          if (t_temp.date < 1)
          {
            t_temp.date = 31;
          }
          t_temp.date = validateDate(t_temp.date, t_temp.mon, t_temp.year);
          setClock();
        }
        else if (checkButtons(monD[0], monD[1], monD[2], monD[3]) == true)
        {
          t_temp.mon -= 1;
          if (t_temp.mon < 1)
          {
            t_temp.mon = 12;
          }
          t_temp.date = validateDateForMonth(t_temp.date, t_temp.mon, t_temp.year);
          setClock();
        }
        else if (checkButtons(yeaD[0], yeaD[1], yeaD[2], yeaD[3]) == true)
        {
          t_temp.year -= 1;
          t_temp.date = validateDateForMonth(t_temp.date, t_temp.mon, t_temp.year);
          setClock();
        }
        else if (checkButtons(prOK[0], prOK[1], prOK[2], prOK[3]) == true)
        {
          rtc.halt(true);
          rtc.setTime(t_temp.hour, t_temp.min, t_temp.sec);
          rtc.setDate(t_temp.date, t_temp.mon, t_temp.year);
          t_temp.dow = calcDOW(t_temp.date, t_temp.mon, t_temp.year);
          rtc.setDOW(t_temp.dow);
          rtc.halt(false);
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        break;
      case 3:                    // -------------------Tela testar led------------------------------------------
        if (checkButtons(stsT[0], stsT[1], stsT[2], stsT[3]) == true)     //press start/stop test
        {
          if (LEDtestTick == true)
          {
            teste_em_andamento = false;
            LEDtestTick = false;
            testScreen(true);
          }
          else
          {
            teste_iniciado = true;
            LEDtestTick = true;
            drawFillRect(319, 1, 399, 239, 0, 0, 0);
            testScreen();
            teste_iniciado = false;
          }
        }
        else if (checkButtons(tenM[0], tenM[1], tenM[2], tenM[3]) == true)      //press -10s
        {
          min_cnt -= 10;
          if (min_cnt <= 0)
          {
            min_cnt = 0;
          }
        }
        else if (checkButtons(tenP[0], tenP[1], tenP[2], tenP[3]) == true)    //press +10s
        {
          min_cnt += 10;
          if (min_cnt > 1440)
          {
            min_cnt = 1440;
          }
        }
        else if ((checkButtons(menU[0], menU[1], menU[2], menU[3]) == true) && (LEDtestTick == false))           // volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if ((checkButtons(volT[0], volT[1], volT[2], volT[3]) == true) && (LEDtestTick == false))          // volta a tela configurar leds
        {
          dispScreen = 25;
          clearScreen();
          escolher_teste();
        }
        break;
      case 4:             //---------------------------------------Tela controle de temperatura----------------------------------
        if (checkButtons(prOK[0], prOK[1], prOK[2], prOK[3]) == true)       //Funcao salvar
        {
          setTempC = temp2beS;
          offTempC = temp2beO;
          alarmTempC = temp2beA;
          dispScreen = 14;
          SaveTempToEEPROM();
          clearScreen();
          parametroScreen();
        }
        else if (checkButtons(temM[0], temM[1], temM[2], temM[3]) == true)                      //press temp minus
        {
          temp2beS -= 0.1;
#ifdef USE_FAHRENHEIT
          if (temp2beS < 50)
          {
            temp2beS = 104;
          }
#else
          if (temp2beS < 10)
          {
            temp2beS = 40;
          }
#endif

          tempScreen();
        }
        else if (checkButtons(offM[0], offM[1], offM[2], offM[3]) == true)                       //press offset minus
        {
          temp2beO -= 0.1;
#ifdef USE_FAHRENHEIT
          if (temp2beO < 0.1)
          {
            temp2beO = 18.0;
          }
#else
          if (temp2beO < 0.1)
          {
            temp2beO = 9.9;
          }
#endif

          tempScreen();
        }
        else if (checkButtons(almM[0], almM[1], almM[2], almM[3]) == true)                        //press alarm minus
        {
          temp2beA -= 0.1;
#ifdef USE_FAHRENHEIT
          if (temp2beA < 0.1)
          {
            temp2beA = 18.0;
          }
#else
          if (temp2beA < 0.1)
          {
            temp2beA = 9.9;
          }
#endif
          tempScreen();
        }
        else if (checkButtons(temP[0], temP[1], temP[2], temP[3]) == true)                      //press temp plus
        {
          temp2beS += 0.1;

#ifdef USE_FAHRENHEIT
          if (temp2beS > 104)
          {
            temp2beS = 50;
          }
#else
          if (temp2beS > 40)
          {
            temp2beS = 10;
          }
#endif
          tempScreen();
        }
        else if (checkButtons(offP[0], offP[1], offP[2], offP[3]) == true)                           //press offset plus
        {
          temp2beO += 0.1;
#ifdef USE_FAHRENHEIT
          if (temp2beO > 18)
          {
            temp2beO = 0.1;
          }
#else
          if (temp2beO > 9.9)
          {
            temp2beO = 0.1;
          }
#endif
          tempScreen();
        }
        else if (checkButtons(almP[0], almP[1], almP[2], almP[3]) == true)                           //press alarm plus
        {
          temp2beA += 0.1;
#ifdef USE_FAHRENHEIT
          if (temp2beA > 18)
          {
            temp2beA = 0.1;
          }
#else
          if (temp2beA > 9.9)
          {
            temp2beA = 0.1;
          }
#endif
          tempScreen();
        }
        else if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu
        {
          dispScreen = 14;
          clearScreen();
          parametroScreen();
        }
        break;
      case 5:         // -------------------------------- Tela alterar valores led ------------------------------------------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
          ReadFromEEPROM();
        }
        else if (checkButtons(leWB[0], leWB[1], leWB[2], leWB[3]) == true)       // Mais cores
        {
          dispScreen = 28;
          clearScreen();
          escolher_canal();
        }
        else if (checkButtons(leST[0], leST[1], leST[2], leST[3]) == true)       // Alterar valores dos leds
        {
          dispScreen = 6;
          clearScreen();
          ledChangeScreen(true);
        }
        else if (checkButtons(savE[0], savE[1], savE[2], savE[3]) == true)      // Salva os valores na EEPROM
        {
          SaveLEDToEEPROM();
          dispScreen = 28;
          clearScreen();
          escolher_canal();
        }
        break;
      case 6:             //---------------------------------- Tela alterar potencia dos leds ---------------------
        if (checkButtons(salV[0], salV[1], salV[2], salV[3]) == true)       // Salvar tabela temporária
        {
          dispScreen = 5;
          clearScreen();
          ledSetScreen();
          periodo_selecionado = false;
        }
        else if ((y >= 15) && (y <= 40))                                // Seleção de período
        {
          if ((x >= 4) && (x <= 316))
          {
            periodo_selecionado = true;
            int oldLCT = LedChangTime;
            LedChangTime = map(x, 3, 320, 0, 12);

            if (oldLCT != LedChangTime)                        // Realçar período tocado
            {
              if (mensagem == true)
              {
                ledChangeScreen();
              }
              drawFillRect((oldLCT * 26) + 5, 21, (oldLCT * 26) + 29, 45, 0, 0, 0);
              setFont(SMALL, 0, 255, 255, 0, 0, 0);

              if (oldLCT == 11)
              {
                myGLCD.printNumI((oldLCT * 2), (oldLCT * 26) + 10, 22);
                myGLCD.print("0", (oldLCT * 26) + 14, 33);
              }
              else
              {
                myGLCD.printNumI((oldLCT * 2), (oldLCT * 26) + 10, 22);
                myGLCD.printNumI(((oldLCT * 2) + 2), (oldLCT * 26) + 10, 33);
              }

              drawFillRect((LedChangTime * 26) + 5, 21, (LedChangTime * 26) + 29, 45, 255, 0, 0);
              setFont(SMALL, 255, 255, 255, 255, 0, 0);

              if (LedChangTime == 11)
              {
                myGLCD.printNumI((LedChangTime * 2), (LedChangTime * 26) + 10, 22);
                myGLCD.print("0", (LedChangTime * 26) + 14, 33);
              }
              else
              {
                myGLCD.printNumI((LedChangTime * 2), (LedChangTime * 26) + 10, 22);
                myGLCD.printNumI(((LedChangTime * 2) + 2), (LedChangTime * 26) + 10, 33);
              }
              myGLCD.setColor(100, 100, 100);
              myGLCD.drawLine(4, 45, 316, 45);

              for (int i = 0; i < 8; i++)                          // Imprime valores do período.
              {
                int k = (LedChangTime * 8) + i;

                drawFillRect((i * 38) + 12, 200, (i * 38) + 36, 210, 0, 0, 0);
                setFont(SMALL, 255, 255, 255, 0, 0, 0);
                myGLCD.printNumI( cor[cor_selecionada][k], (i * 38) + 12, 200);
                y_tocado = map(cor[cor_selecionada][k], 255, 0, 80, 195);
                setor_selecionado = i;
                desenhar_barras_periodo ();
              }
            }
          }
        }
        else if ((y >= 80) && (y <= 195))
        {
          for (int i = 0; i < 8; i++) {
            if ((x >= (i * 38) + 5) && (x <= (i * 38) + 39))
            {
              int k = (LedChangTime * 8) + i;
              y_tocado = y;
              cor[cor_selecionada][k] = map(y_tocado, 195, 80, 0, 255);

              drawFillRect((i * 38) + 12, 200, (i * 38) + 36, 210, 0, 0, 0);
              setFont(SMALL, 255, 255, 255, 0, 0, 0);
              myGLCD.printNumI( cor[cor_selecionada][k], (i * 38) + 12, 200);
              setor_selecionado = i;
              desenhar_barras_periodo ();
            }
          }
        }
        else if ((y >= 50) && (y <= 75) && (periodo_selecionado == true))       // Botão +
        {
          for (int i = 0; i < 8; i++)
          {
            if ((x >= (i * 38) + 5) && (x <= (i * 38) + 39))
            {
              waitForIt((i * 38) + 5, 50, (i * 38) + 39, 75);
              int k = (LedChangTime * 8) + i;
              cor[cor_selecionada][k] += 1;
              delay(50);
              drawFillRect((i * 38) + 12, 200, (i * 38) + 36, 210, 0, 0, 0);
              setFont(SMALL, 255, 255, 255, 0, 0, 0);
              myGLCD.printNumI( cor[cor_selecionada][k], (i * 38) + 12, 200);
              y_tocado = map(cor[cor_selecionada][k], 255, 0, 80, 195);
              setor_selecionado = i;
              desenhar_barras_periodo ();
            }
          }
        }
        else if ((y >= 214) && (y <= 239)  && (periodo_selecionado == true)) // Botão -
        {
          for (int i = 0; i < 8; i++)
          {
            if ((x >= (i * 38) + 5) && (x <= (i * 38) + 39))
            {
              waitForIt((i * 38) + 5, 214, (i * 38) + 39, 239);
              int k = (LedChangTime * 8) + i;
              cor[cor_selecionada][k] -= 1;
              delay(50);

              drawFillRect((i * 38) + 12, 200, (i * 38) + 36, 210, 0, 0, 0);
              setFont(SMALL, 255, 255, 255, 0, 0, 0);
              myGLCD.printNumI( cor[cor_selecionada][k], (i * 38) + 12, 200);
              y_tocado = map(cor[cor_selecionada][k], 255, 0, 80, 195);
              setor_selecionado = i;
              desenhar_barras_periodo ();
            }
          }
        }
        else if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // Volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
          ReadFromEEPROM();
          periodo_selecionado = false;
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // volta a tela configurar leds
        {
          dispScreen = 5;
          clearScreen();
          ledSetScreen();
          ReadFromEEPROM();
          periodo_selecionado = false;
        }
        break;
      case 7: //--------------------------------------------- configurar tpa autom.-----------------------------------
        if (checkButtons(houU[0], houU[1], houU[2], houU[3]) == true)
        {
          temp2hora = (temp2hora + 1) % 24;
          tpaScreen();
        }
        else if (checkButtons(minUT[0], minUT[1], minUT[2], minUT[3]) == true)
        {
          temp2minuto = (temp2minuto + 1) % 60;
          tpaScreen();
        }
        else if (checkButtons(durC[0], durC[1], durC[2], durC[3]) == true)
        {
          temp2duracaomaximatpa = (temp2duracaomaximatpa + 1) % 60;
          if (temp2duracaomaximatpa == 0)
          {
            temp2duracaomaximatpa = 1;
          }
          tpaScreen();
        }
        else if (checkButtons(houD[0], houD[1], houD[2], houD[3]) == true)
        {
          temp2hora = (temp2hora + 23) % 24;
          tpaScreen();
        }
        else if (checkButtons(minDT[0], minDT[1], minDT[2], minDT[3]) == true)
        {
          temp2minuto = (temp2minuto + 59) % 60;
          tpaScreen();
        }
        else if (checkButtons(durB[0], durB[1], durB[2], durB[3]) == true)
        {
          temp2duracaomaximatpa = (temp2duracaomaximatpa + 59) % 60;
          if (temp2duracaomaximatpa == 0)
          {
            temp2duracaomaximatpa = 59;
          }
          tpaScreen();
        }
        else if (checkButtons(prOK[0], prOK[1], prOK[2], prOK[3]) == true)
        {
          hora = temp2hora;
          minuto = temp2minuto;
          duracaomaximatpa = temp2duracaomaximatpa;
          for (byte i = 0; i < 7; i++)
          {
            semana_e[i] = semana[i];
          }
          SalvartpaEEPROM();
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(segU[0], segU[1], segU[2], segU[3]) == true)
        {
          if (semana[0] == 1)
          {
            semana[0] = 0;
            tpaScreen();
          }
          else
          {
            semana[0] = 1;
            tpaScreen();
          }
        }
        else if (checkButtons(terC[0], terC[1], terC[2], terC[3]) == true)
        {
          if (semana[1] == 2)
          {
            semana[1] = 0;
            tpaScreen();
          }
          else {
            semana[1] = 2;
            tpaScreen();
          }
        }
        else if (checkButtons(quaR[0], quaR[1], quaR[2], quaR[3]) == true)
        {
          if (semana[2] == 3)
          {
            semana[2] = 0;
            tpaScreen();
          }
          else
          {
            semana[2] = 3;
            tpaScreen();
          }
        }
        else if (checkButtons(quiN[0] , quiN[1], quiN[2], quiN[3]) == true)
        {
          if (semana[3] == 4)
          {
            semana[3] = 0;
            tpaScreen();
          }
          else
          {
            semana[3] = 4;
            tpaScreen();
          }
        }
        else if (checkButtons(sexT[0], sexT[1], sexT[2], sexT[3]) == true)
        {
          if (semana[4] == 5)
          {
            semana[4] = 0;
            tpaScreen();
          }
          else
          {
            semana[4] = 5;
            tpaScreen();
          }
        }
        else if (checkButtons(sabA[0], sabA[1], sabA[2], sabA[3]) == true)
        {
          if (semana[5] == 6)
          {
            semana[5] = 0;
            tpaScreen();
          }
          else
          {
            semana[5] = 6;
            tpaScreen();
          }
        }
        else if (checkButtons(domI[0], domI[1], domI[2], domI[3]) == true)
        {
          if (semana[6] == 7)
          {
            semana[6] = 0;
            tpaScreen();
          }
          else
          {
            semana[6] = 7;
            tpaScreen();
          }
        }
        else if (checkButtons(proX[0], proX[1], proX[2], proX[3]) == true)
        {
          if (bitRead(tpa_status, 2) == true)
          {
            tpa_status = 0x0;
            Salvar_erro_tpa_EEPROM();
            tpaScreen();
          }
          else
          {
            bitWrite(tpa_status, 2, 1);
            Salvar_erro_tpa_EEPROM();
            tpaScreen();
          }
        }
        break;
      case 8: //--------------------------------------------- Escolher dosadora -----------------------------------
        if (checkButtons(manU[0], manU[1], manU[2], manU[3]) == true)
        {
          modo_manual = true;
          modo_personalizado = false;
          modo_calibrar = false;
          dispScreen = 21;
          clearScreen();
          selecionar_dosadora();
          setFont(SMALL, 255, 255, 255, 0, 0, 0);

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[164])));
          myGLCD.print(buffer, 15, 220); // "MODO MANUAL SELECIONADO"
        }
        else if (checkButtons(perS[0], perS[1], perS[2], perS[3]) == true)
        {
          modo_manual = false;
          modo_personalizado = true;
          modo_calibrar = false;
          dispScreen = 21;
          clearScreen();
          selecionar_dosadora();
          setFont(SMALL, 255, 255, 255, 0, 0, 0);

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[171])));
          myGLCD.print(buffer, 15, 220);
        }
        else if (checkButtons(orP[0], orP[1], orP[2], orP[3]) == true)
        {
          modo_manual = false;
          modo_personalizado = false;
          modo_calibrar = true;
          dispScreen = 21;
          clearScreen();
          selecionar_dosadora();
          setFont(SMALL, 255, 255, 255, 0, 0, 0);

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[172])));
          myGLCD.print(buffer, 15, 220);
        }
        else if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           /// volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
          modo_manual = false;
          modo_personalizado = false;
          modo_calibrar = false;
        }
        else if (checkButtons(reV[0], reV[1], reV[2], reV[3]) == true)           /// Rever config
        {
          dispScreen = 32;
          clearScreen();
          rever_configuracao_dosadoras();
        }
        break;
      case 9: //  -----------------------------------------Tela escolher graficos-----------------------------------------
        if (checkButtons(orP[0], orP[1], orP[2], orP[3]) == true)
        {
          dispScreen = 12;
          clearScreen();
          orpScreen();
        }
        else if (checkButtons(phR[0], phR[1], phR[2], phR[3]) == true)
        {
          dispScreen = 13;
          clearScreen();
          PHRScreen();
        }
        else if (checkButtons(tempG[0], tempG[1], tempG[2], tempG[3]) == true)
        {
          dispScreen = 13;
          clearScreen();
          tempgScreen();
        }
        else if (checkButtons(phA[0], phA[1], phA[2], phA[3]) == true)
        {
          dispScreen = 17;
          clearScreen();
          PHAScreen();
        }
        else if (checkButtons(denS[0], denS[1], denS[2], denS[3]) == true)
        {
          dispScreen = 19;
          clearScreen();
          densidadeScreen();
        }
        else if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           /// volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        break;
      case 10: //--------------------------------- Tela wavemaker ----------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu
        {
          ler_wave_EEPROM();
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(prOK[0], prOK[1], prOK[2], prOK[3]) == true)       //Funcao salvar
        {
          Salvar_wave_EEPROM();
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(boT1[0], boT1[1], boT1[2] , boT1[3]) == true) // Botao: 1
        {
          modo_selecionado = 1;
          waveScreen(true);
        }
        else if (checkButtons(boT2[0], boT2[1], boT2[2], boT2[3]) == true)  // Botao: 2
        {
          modo_selecionado = 2;
          waveScreen(true);
        }
        else if (checkButtons(boT3[0], boT3[1], boT3[2], boT3[3]) == true)  // Botao: 3
        {
          modo_selecionado = 3;
          waveScreen(true);
        }
        else if (checkButtons(boT4[0], boT4[1], boT4[2], boT4[3]) == true)  // Botao: 4
        {
          modo_selecionado = 4;
          waveScreen(true);
        }
        else if (checkButtons(boT5[0], boT5[1], boT5[2], boT5[3]) == true)  // Botao: M
        {
          modo_selecionado = 5;
          waveScreen(true);
        }
        if (modo_selecionado == 1)
        {
          if (checkButtons(peRB[0], peRB[1], peRB[2], peRB[3]) == true)  // Período -
          {
            periodo -= 100;
            if (periodo < 100)
            {
              periodo = 10000;
            }
            waveScreen();
          }
          else if (checkButtons(peRC[0], peRC[1], peRC[2], peRC[3]) == true)  // Período +
          {
            periodo += 100;
            if (periodo > 10000)
            {
              periodo = 100;
            }
            waveScreen();
          }
        }
        else if (modo_selecionado == 2)
        {
          if (checkButtons(peRB[0], peRB[1], peRB[2], peRB[3]) == true)  // Período -
          {
            periodo -= 100;
            if (periodo < 100)
            {
              periodo = 10000;
            }
            waveScreen();
          }
          else if (checkButtons(peRC[0], peRC[1], peRC[2], peRC[3]) == true)  // Período +
          {
            periodo += 100;
            if (periodo > 10000)
            {
              periodo = 100;
            }
            waveScreen();
          }
        }
        else if (modo_selecionado == 3)
        {
          if (checkButtons(peRB[0], peRB[1], peRB[2], peRB[3]) == true)  // Duração do intervalo -
          {
            duracao -= 500;
            if (duracao < 1000)
            {
              duracao = 9500;
            }
            waveScreen();
          }
          else if (checkButtons(peRC[0], peRC[1], peRC[2], peRC[3]) == true)  // Duração intervalo +
          {
            duracao += 500;
            if (duracao > 9500)
            {
              duracao = 1000;
            }
            waveScreen();
          }
        }
        else if (modo_selecionado == 4)
        {
          if (checkButtons(peRB[0], peRB[1], peRB[2], peRB[3]) == true)  // Duração do intervalo -
          {
            duracao -= 1000;
            if (duracao < 1000)
            {
              duracao = 5000;
            }
            waveScreen();
          }
          else if (checkButtons(peRC[0], peRC[1], peRC[2], peRC[3]) == true)  // intervalo +
          {
            duracao += 1000;
            if (duracao > 5000)
            {
              duracao = 1000;
            }
            waveScreen();
          }
        }
        else if (modo_selecionado == 5)
        {
          if (checkButtons(PoTEB1[0], PoTEB1[1], PoTEB1[2], PoTEB1[3]) == true)  // Potência bomba 1 -
          {
            Pump1PWM_temp -= 1;
            waveScreen();
          }
          else if (checkButtons(PoTEC1[0], PoTEC1[1], PoTEC1[2], PoTEC1[3]) == true)  // Potência bomba 1 +
          {
            Pump1PWM_temp += 1;
            waveScreen();
          }
          else if (checkButtons(PoTEB2[0], PoTEB2[1], PoTEB2[2], PoTEB2[3]) == true)  // Potência bomba 1 -
          {
            Pump2PWM_temp -= 1;
            waveScreen();
          }
          else if (checkButtons(PoTEC2[0], PoTEC2[1], PoTEC2[2], PoTEC2[3]) == true)  // Potência bomba 1 +
          {
            Pump2PWM_temp += 1;
            waveScreen();
          }
        }
        break;
      case 11:  //----------------------------- Tela grafico de temperatura ------------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           /// volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // volta a tela de graficos
        {
          dispScreen = 9;
          clearScreen();
          graficoScreen();
        }
        break;
      case 12:  //--------------------------- Tela grafico de orp---------------------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           /// volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // volta a tela de graficos
        {
          dispScreen = 9;
          clearScreen();
          graficoScreen();
        }
        break;
      case 13:   //-----------------Tela grafico de ph do aquario----------------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)         // volta a tela de graficos
        {
          dispScreen = 9;
          clearScreen();
          graficoScreen();
        }
        break;
      case 14:  //--------------------------------Tela escolher parametro para configurar-----------------------------------
        if (checkButtons(orP[0], orP[1], orP[2], orP[3]) == true)
        {
          dispScreen = 16;
          clearScreen();
          config_orp_Screen(true);
        }
        else if (checkButtons(phR[0], phR[1], phR[2], phR[3]) == true)
        {
          dispScreen = 15;
          clearScreen();
          config_phR_Screen(true);
        }
        else if (checkButtons(phA[0], phA[1], phA[2], phA[3]) == true)
        {
          dispScreen = 18;
          clearScreen();
          config_phA_Screen(true);
        }
        else if (checkButtons(tempG[0], tempG[1], tempG[2], tempG[3]) == true)
        {
          dispScreen = 4;
          clearScreen();
          tempScreen(true);
        }
        else if (checkButtons(caliB[0], caliB[1], caliB[2], caliB[3]) == true)
        {
          dispScreen = 0;
          clearScreen();
          mainScreen(true);
        }
        else if (checkButtons(denS[0], denS[1], denS[2], denS[3]) == true)
        {
          dispScreen = 20;
          clearScreen();
          config_dens_Screen(true);
        }
        else if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           /// volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        break;
      case 15:             //---------------------------------------Tela controle de PH do reator--------
        if (checkButtons(prOK[0], prOK[1], prOK[2], prOK[3]) == true)       //Funcao salvar
        {
          setPHR = PHR2beS;
          offPHR = PHR2beO;
          alarmPHR = PHR2beA;
          dispScreen = 14;
          SavePHRToEEPROM();
          clearScreen();
          parametroScreen();
        }
        else if (checkButtons(temM[0], temM[1], temM[2], temM[3]) == true)                      //press ph minus
        {
          PHR2beS -= 0.1;
          if (PHR2beS < 0.1)
          {
            PHR2beS = 9.9;
          }
          config_phR_Screen();
        }
        else if (checkButtons(offM[0], offM[1], offM[2], offM[3]) == true)                       //press offset minus
        {
          PHR2beO -= 0.1;
          if (PHR2beO < 0.1)
          {
            PHR2beO = 9.9;
          }
          config_phR_Screen();
        }
        else if (checkButtons(almM[0], almM[1], almM[2], almM[3]) == true)                        //press alarm minus
        {
          PHR2beA -= 0.1;
          if (PHR2beA < 0.1)
          {
            PHR2beA = 9.9;
          }
          config_phR_Screen();
        }
        else if (checkButtons(temP[0], temP[1], temP[2], temP[3]) == true)                      //press ph plus
        {
          PHR2beS += 0.1;
          if (PHR2beS > 9.9)
          {
            PHR2beS = 0.1;
          }
          config_phR_Screen();
        }
        else if (checkButtons(offP[0], offP[1], offP[2], offP[3]) == true)                           //press offset plus
        {
          PHR2beO += 0.1;
          if (PHR2beO > 9.9)
          {
            PHR2beO = 0.1;
          }
          config_phR_Screen();

        }
        else if (checkButtons(almP[0], almP[1], almP[2], almP[3]) == true)                           //press alarm plus
        {
          PHR2beA += 0.1;
          if (PHR2beA > 9.9)
          {
            PHR2beA = 0.1;
          }
          config_phR_Screen();
        }
        else if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu
        {
          dispScreen = 14;
          clearScreen();
          parametroScreen();
        }
        break;
      case 16:             //---------------------------------------Tela controle de ORP---------------------------------
        if (checkButtons(prOK[0], prOK[1], prOK[2], prOK[3]) == true)       //Funcao salvar
        {
          setORP = ORP2beS;
          offORP = ORP2beO;
          alarmORP = ORP2beA;
          dispScreen = 14;
          SaveORPToEEPROM();
          clearScreen();
          parametroScreen();
        }
        else if (checkButtons(temM[0], temM[1], temM[2], temM[3]) == true)                      //press orp minus
        {
          ORP2beS -= 10;
          if (ORP2beS < 100)
          {
            ORP2beS = 600;
          }
          config_orp_Screen();
        }
        else if (checkButtons(offM[0], offM[1], offM[2], offM[3]) == true)                       //press offset minus
        {
          ORP2beO -= 10;
          if (ORP2beO < 10)
          {
            ORP2beO = 200;
          }
          config_orp_Screen();
        }
        else if (checkButtons(almM[0], almM[1], almM[2], almM[3]) == true)                        //press alarm minus
        {
          ORP2beA -= 10;
          if (ORP2beA < 10)
          {
            ORP2beA = 200;
          }
          config_orp_Screen();
        }
        else if (checkButtons(temP[0], temP[1], temP[2], temP[3]) == true)                      //press orp plus
        {
          ORP2beS += 10;
          if (ORP2beS > 600)
          {
            ORP2beS = 100;
          }
          config_orp_Screen();
        }
        else if (checkButtons(offP[0], offP[1], offP[2], offP[3]) == true)                           //press offset plus
        {
          ORP2beO += 10;
          if (ORP2beO > 200)
          {
            ORP2beO = 10;
          }
          config_orp_Screen();
        }
        else if (checkButtons(almP[0], almP[1], almP[2], almP[3]) == true)                           //press alarm plus
        {
          ORP2beA += 10;
          if (ORP2beA > 200)
          {
            ORP2beA = 10;
          }
          config_orp_Screen();
        }
        else if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu
        {
          dispScreen = 14;
          clearScreen();
          parametroScreen();
        }
        break;
      case 17:   //---------------------Tela grafico de ph do reator de calcio-------------------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           /// volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // volta a tela de graficos
        {
          dispScreen = 9;
          clearScreen();
          graficoScreen();
        }
        break;

      case 18: //--------------------------Tela configuracao de ph do aquario-----------------------------------
        if (checkButtons(prOK[0], prOK[1], prOK[2], prOK[3]) == true)       //Funcao salvar
        {
          setPHA = PHA2beS;
          offPHA = PHA2beO;
          alarmPHA = PHA2beA;
          dispScreen = 14;
          SavePHAToEEPROM();
          clearScreen();
          parametroScreen();
        }
        else if (checkButtons(temM[0], temM[1], temM[2], temM[3]) == true)                      //press ph minus
        {
          PHA2beS -= 0.1;
          if (PHA2beS < 0.1)
          {
            PHA2beS = 0.1;
          }
          config_phA_Screen();
        }
        else if (checkButtons(offM[0], offM[1], offM[2], offM[3]) == true)                       //press offset minus
        {
          PHA2beO -= 0.1;
          if (PHA2beO < 0.0)
          {
            PHA2beO = 0.0;
          }
          config_phA_Screen();
        }
        else if (checkButtons(almM[0], almM[1], almM[2], almM[3]) == true)                        //press alarm minus
        {
          PHA2beA -= 0.1;
          if (PHA2beA < 0.0)
          {
            PHA2beA = 0.0;
          }
          config_phA_Screen();
        }
        else if (checkButtons(temP[0], temP[1], temP[2], temP[3]) == true)                      //press temp plus
        {
          PHA2beS += 0.1;
          if (PHA2beS > 9.9)
          {
            PHA2beS = 9.9;
          }
          config_phA_Screen();
        }
        else if (checkButtons(offP[0], offP[1], offP[2], offP[3]) == true)                           //press offset plus
        {
          PHA2beO += 0.1;
          if (PHA2beO > 9.9)
          {
            PHA2beO = 9.9;
          }
          config_phA_Screen();
        }
        else if (checkButtons(almP[0], almP[1], almP[2], almP[3]) == true)                           //press alarm plus
        {
          PHA2beA += 0.1;
          if (PHA2beA > 9.9)
          {
            PHA2beA = 9.9;
          }
          config_phA_Screen();
        }
        else if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu
        {
          dispScreen = 14;
          clearScreen();
          parametroScreen();
        }
        break;

      case 19://----------------------Tela grafico de densidade----------------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           /// volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // volta a tela de graficos
        {
          dispScreen = 9;
          clearScreen();
          graficoScreen();
        }
        break;

      case 20: //--------------------------Tela configuração densidade  -----------------------------------------------------
        if (checkButtons(prOK[0], prOK[1], prOK[2], prOK[3]) == true)       //Funcao salvar
        {
          setDEN = DEN2beS;
          offDEN = DEN2beO;
          alarmDEN = DEN2beA;
          dispScreen = 14;
          SaveDENToEEPROM();
          clearScreen();
          parametroScreen();
        }
        else if (checkButtons(temM[0], temM[1], temM[2], temM[3]) == true)                      //press densidade minus
        {
          DEN2beS -= 1;
          if (DEN2beS < 1000)
          {
            DEN2beS = 1000;
          }
          config_dens_Screen();
        }
        else if (checkButtons(offM[0], offM[1], offM[2], offM[3]) == true)                       //press offset minus
        {
          DEN2beO -= 1;
          if (DEN2beO < 1)
          {
            DEN2beO = 10;
          }
          config_dens_Screen();
        }
        else if (checkButtons(almM[0], almM[1], almM[2], almM[3]) == true)                        //press alarm minus
        {
          DEN2beA -= 1;
          if (DEN2beA < 1)
          {
            DEN2beA = 10;
          }
          config_dens_Screen();
        }
        else if (checkButtons(temP[0], temP[1], temP[2], temP[3]) == true)                      //press densidade plus
        {
          DEN2beS += 1;
          if (DEN2beS > 1050)
          {
            DEN2beS = 1000;
          }
          config_dens_Screen();
        }
        else if (checkButtons(offP[0], offP[1], offP[2], offP[3]) == true)                           //press offset plus
        {
          DEN2beO += 1;
          if (DEN2beO > 10)
          {
            DEN2beO = 1;
          }
          config_dens_Screen();
        }
        else if (checkButtons(almP[0], almP[1], almP[2], almP[3]) == true)                           //press alarm plus
        {
          DEN2beA += 1;
          if (DEN2beA > 10)
          {
            DEN2beA = 1;
          }
          config_dens_Screen();
        }
        else if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu
        {
          dispScreen = 14;
          clearScreen();
          parametroScreen();
        }
        break;
      case 21: // ------------------------------------------------ Escolher dosadora -----------------------------------

        if (checkButtons(dosa1[0], dosa1[1], dosa1[2], dosa1[3]) == true)
        {
          if (modo_manual == true)
          {
            dosadora_selecionada = 0;
            dispScreen = 27;
            clearScreen();
            config_dosagem_manual(true);
          }
          else if (modo_personalizado == true)
          {
            dosadora_selecionada = 0;
            dispScreen = 29;
            clearScreen();
            config_dosagem_personalizada(true);
          }

          else if (modo_calibrar == true)
          {
            dosadora_selecionada = 0;
            dispScreen = 26;
            clearScreen();
            calibrar_dosadoras(true);
          }
        }
        else if (checkButtons(dosa2[0], dosa2[1], dosa2[2], dosa2[3]) == true)
        {
          if (modo_manual == true)
          {
            dosadora_selecionada = 1;
            dispScreen = 27;
            clearScreen();
            config_dosagem_manual(true);
          }
          else if (modo_personalizado == true)
          {
            dosadora_selecionada = 1;
            dispScreen = 29;
            clearScreen();
            config_dosagem_personalizada(true);
          }
          else if (modo_calibrar == true)
          {
            dosadora_selecionada = 1;
            dispScreen = 26;
            clearScreen();
            calibrar_dosadoras(true);
          }
        }
        else if (checkButtons(dosa3[0], dosa3[1], dosa3[2], dosa3[3]) == true)
        {
          if (modo_manual == true)
          {
            dosadora_selecionada = 2;
            dispScreen = 27;
            clearScreen();
            config_dosagem_manual(true);
          }
          else if (modo_personalizado == true)
          {
            dosadora_selecionada = 2;
            dispScreen = 29;
            clearScreen();
            config_dosagem_personalizada(true);
          }
          else if (modo_calibrar == true)
          {
            dosadora_selecionada = 2;
            dispScreen = 26;
            clearScreen();
            calibrar_dosadoras(true);
          }
        }
        else if (checkButtons(dosa4[0], dosa4[1], dosa4[2], dosa4[3]) == true)
        {
          if (modo_manual == true)
          {
            dosadora_selecionada = 3;
            dispScreen = 27;
            clearScreen();
            config_dosagem_manual(true);
          }
          else if (modo_personalizado == true)
          {
            dosadora_selecionada = 3;
            dispScreen = 29;
            clearScreen();
            config_dosagem_personalizada(true);
          }

          else if (modo_calibrar == true)
          {
            dosadora_selecionada = 3;
            dispScreen = 26;
            clearScreen();
            calibrar_dosadoras(true);
          }
        }
        else if (checkButtons(dosa5[0], dosa5[1], dosa5[2], dosa5[3]) == true)
        {
          if (modo_manual == true)
          {
            dosadora_selecionada = 4;
            dispScreen = 27;
            clearScreen();
            config_dosagem_manual(true);
          }
          else if (modo_personalizado == true)
          {
            dosadora_selecionada = 4;
            dispScreen = 29;
            clearScreen();
            config_dosagem_personalizada(true);
          }
          else if (modo_calibrar == true)
          {
            dosadora_selecionada = 4;
            dispScreen = 26;
            clearScreen();
            calibrar_dosadoras(true);
          }
        }
        else if (checkButtons(dosa6[0], dosa6[1], dosa6[2], dosa6[3]) == true)
        {
          if (modo_manual == true)
          {
            dosadora_selecionada = 5;
            dispScreen = 27;
            clearScreen();
            config_dosagem_manual(true);
          }
          else if (modo_personalizado == true)
          {
            dosadora_selecionada = 5;
            dispScreen = 29;
            clearScreen();
            config_dosagem_personalizada(true);
          }
          else if (modo_calibrar == true)
          {
            dosadora_selecionada = 5;
            dispScreen = 26;
            clearScreen();
            calibrar_dosadoras(true);
          }
        }
        else if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // volta a tela de escolha da dosadora
        {
          dispScreen = 8;
          clearScreen();
          menu_dosadoras();
        }
        break;
      case 22:// ----------------------------------------- Teste individual dos leds -----------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
          ler_predefinido_EEPROM();
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // volta a tela escolher teste
        {
          dispScreen = 25;
          clearScreen();
          escolher_teste();
          ler_predefinido_EEPROM();
        }
        else if ((y >= 44) && (y <= 172)) //**************** Controle deslizante - início.
        {
          teste_em_andamento = true;
          if ((x >= 49) && (x <= 93))
          {
            y_tocado = y;
            desenhar_barras(cor_canal[0][0], cor_canal[0][1], cor_canal[0][2], 49, 44, 93, 172);
            wled_out_temp = map(y_tocado, 172, 44, 0, 255);

            if (wled_out_temp >= 100)
            {
              myGLCD.printNumI(wled_out_temp, 61, 186);
            }
            else if ((wled_out_temp >= 10) && (wled_out_temp < 100))
            {
              myGLCD.print("0", 61, 186);
              myGLCD.printNumI(wled_out_temp, 69, 186);
            }
            else if (wled_out_temp < 10)
            {
              myGLCD.print("00", 61, 186);
              myGLCD.printNumI(wled_out_temp, 77, 186);
            }
          }
          else if ((x >= 101) && (x <= 145)) //**************** Controle deslizante
          {
            y_tocado = y;
            desenhar_barras(cor_canal[1][0], cor_canal[1][1], cor_canal[1][2], 101, 44, 145, 172);
            bled_out_temp = map(y_tocado, 172, 44, 0, 255);

            if (bled_out_temp >= 100)
            {
              myGLCD.printNumI(bled_out_temp, 113, 186);
            }
            else if ((bled_out_temp >= 10) && (bled_out_temp < 100))
            {
              myGLCD.print("0", 113, 186);
              myGLCD.printNumI(bled_out_temp, 121, 186);
            }
            else if (bled_out_temp < 10)
            {
              myGLCD.print("00", 113, 186);
              myGLCD.printNumI(bled_out_temp, 129, 186);
            }
          }
          else if ((x >= 153) && (x <= 197)) //**************** Controle deslizante
          {
            y_tocado = y;
            desenhar_barras(cor_canal[2][0], cor_canal[2][1], cor_canal[2][2], 153, 44, 197, 172);
            rbled_out_temp = map(y_tocado, 172, 44, 0, 255);

            if (rbled_out_temp >= 100)
            {
              myGLCD.printNumI(rbled_out_temp, 165, 186);
            }
            else if ((rbled_out_temp >= 10) && (rbled_out_temp < 100))
            {
              myGLCD.print("0", 165, 186);
              myGLCD.printNumI(rbled_out_temp, 173, 186);
            }
            else if (rbled_out_temp < 10)
            {
              myGLCD.print("00", 165, 186);
              myGLCD.printNumI(rbled_out_temp, 181, 186);
            }
          }
          else if ((x >= 205) && (x <= 249)) //**************** Controle deslizante
          {
            y_tocado = y;
            desenhar_barras(cor_canal[3][0], cor_canal[3][1], cor_canal[3][2], 205, 44, 249, 172);
            rled_out_temp = map(y_tocado, 172, 44, 0, 255);

            if (rled_out_temp >= 100)
            {
              myGLCD.printNumI(rled_out_temp, 217, 186);
            }
            else if ((rled_out_temp >= 10) && (rled_out_temp < 100))
            {
              myGLCD.print("0", 217, 186);
              myGLCD.printNumI(rled_out_temp, 225, 186);
            }
            else if (rled_out_temp < 10)
            {
              myGLCD.print("00", 217, 186);
              myGLCD.printNumI(rled_out_temp, 233, 186);
            }
          }
          else if ((x >= 257) && (x <= 301)) //**************** Controle deslizante
          {
            y_tocado = y;
            desenhar_barras(cor_canal[4][0], cor_canal[4][1], cor_canal[4][2], 257, 44, 301, 172);
            uvled_out_temp = map(y_tocado, 172, 44, 0, 255);
            if (uvled_out_temp >= 100)
            {
              myGLCD.printNumI(uvled_out_temp, 269, 186);
            }
            else if ((uvled_out_temp >= 10) && (uvled_out_temp < 100))
            {
              myGLCD.print("0", 269, 186);
              myGLCD.printNumI(uvled_out_temp, 277, 186);
            }
            else if (uvled_out_temp < 10)
            {
              myGLCD.print("00", 269, 186);
              myGLCD.printNumI(uvled_out_temp, 285, 186);
            }
          }
        }//**************** Controle deslizante - fim.
        else if (checkButtons(49, 18, 93, 41) == true) // Botão mais
        {
          teste_em_andamento = true;
          wled_out_temp += 1;
          delay(50);
          y_tocado = map(wled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal[0][0], cor_canal[0][1], cor_canal[0][2], 49, 44, 93, 172);
          if (wled_out_temp >= 100)
          {
            myGLCD.printNumI(wled_out_temp, 61, 186);
          }
          else if ((wled_out_temp >= 10) && (wled_out_temp < 100))
          {
            myGLCD.print("0", 61, 186);
            myGLCD.printNumI(wled_out_temp, 69, 186);
          }
          else if (wled_out_temp < 10)
          {
            myGLCD.print("00", 61, 186);
            myGLCD.printNumI(wled_out_temp, 77, 186);
          }
        }
        else if (checkButtons(101, 18, 145, 41) == true) // Botão mais
        {
          teste_em_andamento = true;
          bled_out_temp += 1;
          delay(50);
          y_tocado = map(bled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal[1][0], cor_canal[1][1], cor_canal[1][2], 101, 44, 145, 172);

          if (bled_out_temp >= 100)
          {
            myGLCD.printNumI(bled_out_temp, 113, 186);
          }
          else if ((bled_out_temp >= 10) && (bled_out_temp < 100))
          {
            myGLCD.print("0", 113, 186);
            myGLCD.printNumI(bled_out_temp, 121, 186);
          }
          else if (bled_out_temp < 10)
          {
            myGLCD.print("00", 113, 186);
            myGLCD.printNumI(bled_out_temp, 129, 186);
          }
        }
        else if (checkButtons(153, 18, 197, 41) == true) // Botão mais
        {
          teste_em_andamento = true;
          rbled_out_temp += 1;
          delay(50);
          y_tocado = map(rbled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal[2][0], cor_canal[2][1], cor_canal[2][2], 153, 44, 197, 172);
          if (rbled_out_temp >= 100)
          {
            myGLCD.printNumI(rbled_out_temp, 165, 186);
          }
          else if ((rbled_out_temp >= 10) && (rbled_out_temp < 100))
          {
            myGLCD.print("0", 165, 186);
            myGLCD.printNumI(rbled_out_temp, 173, 186);
          }
          else if (rbled_out_temp < 10)
          {
            myGLCD.print("00", 165, 186);
            myGLCD.printNumI(rbled_out_temp, 181, 186);
          }
        }
        else if (checkButtons(205, 18, 249, 41) == true) // Botão mais
        {
          teste_em_andamento = true;
          rled_out_temp += 1;
          delay(50);
          y_tocado = map(rled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal[3][0], cor_canal[3][1], cor_canal[3][2], 205, 44, 249, 172);

          if (rled_out_temp >= 100)
          {
            myGLCD.printNumI(rled_out_temp, 217, 186);
          }
          else if ((rled_out_temp >= 10) && (rled_out_temp < 100))
          {
            myGLCD.print("0", 217, 186);
            myGLCD.printNumI(rled_out_temp, 225, 186);
          }
          else if (rled_out_temp < 10)
          {
            myGLCD.print("00", 217, 186);
            myGLCD.printNumI(rled_out_temp, 233, 186);
          }
        }
        else if (checkButtons(257, 18, 301, 41) == true) // Botão mais
        {
          teste_em_andamento = true;
          uvled_out_temp += 1;
          delay(50);
          y_tocado = map(uvled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal[4][0], cor_canal[4][1], cor_canal[4][2], 257, 44, 301, 172);
          if (uvled_out_temp >= 100)
          {
            myGLCD.printNumI(uvled_out_temp, 269, 186);
          }
          else if ((uvled_out_temp >= 10) && (uvled_out_temp < 100))
          {
            myGLCD.print("0", 269, 186);
            myGLCD.printNumI(uvled_out_temp, 277, 186);
          }
          else if (uvled_out_temp < 10)
          {
            myGLCD.print("00", 269, 186);
            myGLCD.printNumI(uvled_out_temp, 285, 186);
          }
        }
        else if (checkButtons(49, 201, 93, 224) == true) // Botão menos
        {
          teste_em_andamento = true;
          wled_out_temp -= 1;
          delay(50);
          y_tocado = map(wled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal[0][0], cor_canal[0][1], cor_canal[0][2], 49, 44, 93, 172);
          if (wled_out_temp >= 100)
          {
            myGLCD.printNumI(wled_out_temp, 61, 186);
          }
          else if ((wled_out_temp >= 10) && (wled_out_temp < 100))
          {
            myGLCD.print("0", 61, 186);
            myGLCD.printNumI(wled_out_temp, 69, 186);
          }
          else if (wled_out_temp < 10)
          {
            myGLCD.print("00", 61, 186);
            myGLCD.printNumI(wled_out_temp, 77, 186);
          }
        }
        else if (checkButtons(101, 201, 145, 224) == true) // Botão menos
        {
          teste_em_andamento = true;
          bled_out_temp -= 1;
          delay(50);
          y_tocado = map(bled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal[1][0], cor_canal[1][1], cor_canal[1][2], 101, 44, 145, 172);

          if (bled_out_temp >= 100)
          {
            myGLCD.printNumI(bled_out_temp, 113, 186);
          }
          else if ((bled_out_temp >= 10) && (bled_out_temp < 100))
          {
            myGLCD.print("0", 113, 186);
            myGLCD.printNumI(bled_out_temp, 121, 186);
          }
          else if (bled_out_temp < 10)
          {
            myGLCD.print("00", 113, 186);
            myGLCD.printNumI(bled_out_temp, 129, 186);
          }
        }
        else if (checkButtons(153, 201, 197, 224) == true) // Botão menos
        {
          teste_em_andamento = true;
          rbled_out_temp -= 1;
          delay(50);
          y_tocado = map(rbled_out_temp, 255, 0, 44, 172);

          desenhar_barras(cor_canal[2][0], cor_canal[2][1], cor_canal[2][2], 153, 44, 197, 172);
          if (rbled_out_temp >= 100)
          {
            myGLCD.printNumI(rbled_out_temp, 165, 186);
          }
          else if ((rbled_out_temp >= 10) && (rbled_out_temp < 100))
          {
            myGLCD.print("0", 165, 186);
            myGLCD.printNumI(rbled_out_temp, 173, 186);
          }
          else if (rbled_out_temp < 10)
          {
            myGLCD.print("00", 165, 186);
            myGLCD.printNumI(rbled_out_temp, 181, 186);
          }
        }
        else if (checkButtons(205, 201, 249, 224) == true) // Botão menos
        {
          teste_em_andamento = true;
          rled_out_temp -= 1;
          delay(50);
          y_tocado = map(rled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal[3][0], cor_canal[3][1], cor_canal[3][2], 205, 44, 249, 172);

          if (rled_out_temp >= 100)
          {
            myGLCD.printNumI(rled_out_temp, 217, 186);
          }
          else if ((rled_out_temp >= 10) && (rled_out_temp < 100))
          {
            myGLCD.print("0", 217, 186);
            myGLCD.printNumI(rled_out_temp, 225, 186);
          }
          else if (rled_out_temp < 10)
          {
            myGLCD.print("00", 217, 186);
            myGLCD.printNumI(rled_out_temp, 233, 186);
          }
        }
        else if (checkButtons(257, 201, 301, 224) == true) // Botão menos
        {
          teste_em_andamento = true;
          uvled_out_temp -= 1;
          delay(50);
          y_tocado = map(uvled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal[4][0], cor_canal[4][1], cor_canal[4][2], 257, 44, 301, 172);
          if (uvled_out_temp >= 100)
          {
            myGLCD.printNumI(uvled_out_temp, 269, 186);
          }
          else if ((uvled_out_temp >= 10) && (uvled_out_temp < 100))
          {
            myGLCD.print("0", 269, 186);
            myGLCD.printNumI(uvled_out_temp, 277, 186);
          }
          else if (uvled_out_temp < 10)
          {
            myGLCD.print("00", 269, 186);
            myGLCD.printNumI(uvled_out_temp, 285, 186);
          }
        }
        break;
      case 23:// -------------------------------- Rever configuração das dosadoras modo personalizado ------------------------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // volta ao menu de revisão das dosadoras
        {
          dispScreen = 34;
          clearScreen();
          rever_dosagem_personalizada();
        }
        break;
      case 24:// -------------------------------------- livre ------------------------------------------
        break;
      case 25:// ------------------------------------ Escolher teste dos leds --------------------------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu 1
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(testI[0], testI[1], testI[2], testI[3]) == true)           // Teste individual
        {
          dispScreen = 22;
          clearScreen();
          teste_individual_leds();
        }
        else if (checkButtons(testT[0], testT[1], testT[2], testT[3]) == true)           // Testar todos
        {
          dispScreen = 3;
          clearScreen();
          testScreen(true);
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // volta ao menu "Config. LED's"
        {
          dispScreen = 40;
          clearScreen();
          config_leds();
        }
        break;
      case 26: //------------------------------------ calibrar dosadoras -------------------------------------------
        if (checkButtons(almP[0], almP[1], almP[2], almP[3]) == true)            //fator calibracao mais.
        {
          fator_calib_dosadora[dosadora_selecionada] += 0.1;
          if (fator_calib_dosadora[dosadora_selecionada] > 99.9)
          {
            fator_calib_dosadora[dosadora_selecionada] = 0.0;
          }
          calibrar_dosadoras();
        }
        else if (checkButtons(almM[0], almM[1], almM[2], almM[3]) == true)            //fator calibracao menos.
        {
          fator_calib_dosadora[dosadora_selecionada] -= 0.1;
          if (fator_calib_dosadora[dosadora_selecionada] < 0.1)
          {
            fator_calib_dosadora[dosadora_selecionada] = 99.9;
          }
          calibrar_dosadoras();
        }
        else if (checkButtons(salV[0], salV[1], salV[2], salV[3]) == true)
        {
          config_valores_salvar_dosadoras();
          fator_calib_dosadora_e[0] = fator_calib_dosadora[0];
          fator_calib_dosadora_e[1] = fator_calib_dosadora[1];
          fator_calib_dosadora_e[2] = fator_calib_dosadora[2];
          fator_calib_dosadora_e[3] = fator_calib_dosadora[3];
          fator_calib_dosadora_e[4] = fator_calib_dosadora[4];
          fator_calib_dosadora_e[5] = fator_calib_dosadora[5];
          Salvar_calib_dosadora_EEPROM();

          dispScreen = 21;
          clearScreen();
          selecionar_dosadora();
          setFont(SMALL, 255, 255, 255, 0, 0, 0);

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[172])));
          myGLCD.print(buffer, 15, 220);

          modo_manual = false;
          modo_personalizado = false;
          modo_calibrar = true;
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // Volta a tela altera configuracao das dosadoras
        {
          dispScreen = 21;
          clearScreen();
          selecionar_dosadora();
          setFont(SMALL, 255, 255, 255, 0, 0, 0);

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[172])));
          myGLCD.print(buffer, 15, 220);

          modo_manual = false;
          modo_personalizado = false;
          modo_calibrar = true;
        }
        else if (checkButtons(iniciaR[0], iniciaR[1], iniciaR[2], iniciaR[3]) == true)
        {
          if (modo_calibrar == true)
          {
            strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[17])));
            printButton(buffer, iniciaR[0], iniciaR[1], iniciaR[2], iniciaR[3], false, 1);
#ifdef WATCHDOG
            wdt_disable();
#endif
            delay(10000);
            calibrar();
#ifdef WATCHDOG
            wdt_enable(WDTO_8S);
#endif
            strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[17])));
            printButton(buffer, iniciaR[0], iniciaR[1], iniciaR[2], iniciaR[3]);
          }
        }
        break;
      case 27:   // ----------------------------------------- Config dosagem manual --------------------------------------
        if (checkButtons(almP[0], almP[1], almP[2], almP[3]) == true)            //dose manual mais.
        {
          dose_dosadora_manual[dosadora_selecionada] += 0.5;
          if (dose_dosadora_manual[dosadora_selecionada] > 99.5)
          {
            dose_dosadora_manual[dosadora_selecionada] = 0.0;
          }
          config_dosagem_manual();
        }
        else if (checkButtons(almM[0], almM[1], almM[2], almM[3]) == true)            //dose manual menos.
        {
          dose_dosadora_manual[dosadora_selecionada] -= 0.5;
          if (dose_dosadora_manual[dosadora_selecionada] < 0.5)
          {
            dose_dosadora_manual[dosadora_selecionada] = 99.5;
          }
          config_dosagem_manual();
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // Volta a tela altera configuracao das dosadoras
        {
          dispScreen = 21;
          clearScreen();
          selecionar_dosadora();
          setFont(SMALL, 255, 255, 255, 0, 0, 0);

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[164])));
          myGLCD.print(buffer, 15, 220);

          modo_manual = true;
          modo_personalizado = false;
          modo_calibrar = false;
        }
        else if (checkButtons(iniciaR[0], iniciaR[1], iniciaR[2], iniciaR[3]) == true)
        {
          if (modo_manual == true)
          {
            strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[17])));
            printButton(buffer, iniciaR[0], iniciaR[1], iniciaR[2], iniciaR[3], false, 1);

            tempo_dosagem = map ((dose_dosadora_manual[dosadora_selecionada] * 2), 0, fator_calib_dosadora_e[dosadora_selecionada], 0, 60000);
            tempo_dosagem /= 2;
#ifdef WATCHDOG
            wdt_disable();
#endif
            delay(10000);
            dosagem_manual();
#ifdef WATCHDOG
            wdt_enable(WDTO_8S);
#endif
            volume_dosado[dosadora_selecionada] += dose_dosadora_manual[dosadora_selecionada];

            strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[17])));
            printButton(buffer, iniciaR[0], iniciaR[1], iniciaR[2], iniciaR[3]);
          }
        }
        break;
      case 28:  //--------------------------------Escolher canal LEDS-----------------------------------
        if (checkButtons(tempG[0], tempG[1], tempG[2], tempG[3]) == true)
        {
          cor_selecionada = 0;
          dispScreen = 5;
          clearScreen();
          ledSetScreen();
        }
        else if (checkButtons(phA[0], phA[1], phA[2], phA[3]) == true)
        {
          cor_selecionada = 1;
          dispScreen = 5;
          clearScreen();
          ledSetScreen();
        }
        else if (checkButtons(phR[0], phR[1], phR[2], phR[3]) == true)
        {
          cor_selecionada = 2;
          dispScreen = 5;
          clearScreen();
          ledSetScreen();
        }
        else if (checkButtons(orP[0], orP[1], orP[2], orP[3]) == true)
        {
          cor_selecionada = 3;
          dispScreen = 5;
          clearScreen();
          ledSetScreen();
        }
        else if (checkButtons(denS[0], denS[1], denS[2], denS[3]) == true)
        {
          cor_selecionada = 4;
          dispScreen = 5;
          clearScreen();
          ledSetScreen();
        }
        else if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           /// volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
          ReadFromEEPROM();
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // Volta a tela altera configuracao das dosadoras
        {
          dispScreen = 40;
          clearScreen();
          ReadFromEEPROM();
          config_leds();
        }
        break;
      case 29:   // ----------------------------------------- Config dosagem personalizada --------------------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // Volta a tela altera configuracao das dosadoras
        {
          dispScreen = 21;
          clearScreen();
          selecionar_dosadora();
          setFont(SMALL, 255, 255, 255, 0, 0, 0);

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[171])));
          myGLCD.print(buffer, 15, 220);

          modo_manual = false;
          modo_personalizado = true;
          modo_calibrar = false;
        }
        else if (checkButtons(proX[0], proX[1], proX[2], proX[3]) == true)
        {
          dispScreen = 31;
          clearScreen();
          config_dosagem_personalizada_2(true);
        }
        else if (checkButtons(houU[0], houU[1], houU[2], houU[3]) == true)
        {
          hora_inicial_dosagem_personalizada[dosadora_selecionada] = (hora_inicial_dosagem_personalizada[dosadora_selecionada] + 1) % 24;
          config_dosagem_personalizada();
        }
        else if (checkButtons(minUT[0], minUT[1], minUT[2], minUT[3]) == true)
        {
          minuto_inicial_dosagem_personalizada[dosadora_selecionada] = (minuto_inicial_dosagem_personalizada[dosadora_selecionada] + 1) % 60;
          config_dosagem_personalizada();
        }

        else if (checkButtons(houU[0] + 155, houU[1], houU[2] + 155, houU[3]) == true)
        {
          hora_final_dosagem_personalizada[dosadora_selecionada] = (hora_final_dosagem_personalizada[dosadora_selecionada] + 1) % 24;
          config_dosagem_personalizada();
        }
        else if (checkButtons(minUT[0] + 155, minUT[1], minUT[2] + 155, minUT[3]) == true)
        {
          minuto_final_dosagem_personalizada[dosadora_selecionada] = (minuto_final_dosagem_personalizada[dosadora_selecionada] + 1) % 60;
          config_dosagem_personalizada();
        }
        else if (checkButtons(houD[0], houD[1], houD[2], houD[3]) == true)
        {
          hora_inicial_dosagem_personalizada[dosadora_selecionada] = (hora_inicial_dosagem_personalizada[dosadora_selecionada] + 23) % 24;
          config_dosagem_personalizada();
        }
        else if (checkButtons(minDT[0], minDT[1], minDT[2], minDT[3]) == true)
        {
          minuto_inicial_dosagem_personalizada[dosadora_selecionada] = (minuto_inicial_dosagem_personalizada[dosadora_selecionada] + 59) % 60;
          config_dosagem_personalizada();
        }
        else if (checkButtons(houD[0] + 155, houD[1], houD[2] + 155, houD[3]) == true)
        {
          hora_final_dosagem_personalizada[dosadora_selecionada] = (hora_final_dosagem_personalizada[dosadora_selecionada] + 23) % 24;
          config_dosagem_personalizada();
        }
        else if (checkButtons(minDT[0] + 155, minDT[1], minDT[2] + 155, minDT[3]) == true)
        {
          minuto_final_dosagem_personalizada[dosadora_selecionada] = (minuto_final_dosagem_personalizada[dosadora_selecionada] + 59) % 60;
          config_dosagem_personalizada();
        }
        else if (checkButtons(segU[0], segU[1], segU[2], segU[3]) == true)
        {
          if (segunda_dosagem_personalizada[dosadora_selecionada] == 1)
          {
            segunda_dosagem_personalizada[dosadora_selecionada] = 0;
            config_dosagem_personalizada();
          }
          else
          {
            segunda_dosagem_personalizada[dosadora_selecionada] = 1;
            config_dosagem_personalizada();
          }
        }
        else if (checkButtons(terC[0], terC[1], terC[2], terC[3]) == true)
        {
          if (terca_dosagem_personalizada[dosadora_selecionada] == 2)
          {
            terca_dosagem_personalizada[dosadora_selecionada] = 0;
            config_dosagem_personalizada();
          }
          else
          {
            terca_dosagem_personalizada[dosadora_selecionada] = 2;
            config_dosagem_personalizada();
          }
        }
        else if (checkButtons(quaR[0], quaR[1], quaR[2], quaR[3]) == true)
        {
          if (quarta_dosagem_personalizada[dosadora_selecionada] == 3)
          {
            quarta_dosagem_personalizada[dosadora_selecionada] = 0;
            config_dosagem_personalizada();
          }
          else
          {
            quarta_dosagem_personalizada[dosadora_selecionada] = 3;
            config_dosagem_personalizada();
          }
        }
        else if (checkButtons(quiN[0], quiN[1], quiN[2], quiN[3]) == true)
        {
          if (quinta_dosagem_personalizada[dosadora_selecionada] == 4)
          {
            quinta_dosagem_personalizada[dosadora_selecionada] = 0;
            config_dosagem_personalizada();
          }
          else
          {
            quinta_dosagem_personalizada[dosadora_selecionada] = 4;
            config_dosagem_personalizada();
          }
        }
        if (checkButtons(sexT[0], sexT[1], sexT[2], sexT[3]) == true)
        {
          if (sexta_dosagem_personalizada[dosadora_selecionada] == 5)
          {
            sexta_dosagem_personalizada[dosadora_selecionada] = 0;
            config_dosagem_personalizada();
          }
          else
          {
            sexta_dosagem_personalizada[dosadora_selecionada] = 5;
            config_dosagem_personalizada();
          }
        }
        else if (checkButtons(sabA[0], sabA[1], sabA[2], sabA[3]) == true)
        {
          if (sabado_dosagem_personalizada[dosadora_selecionada] == 6)
          {
            sabado_dosagem_personalizada[dosadora_selecionada] = 0;
            config_dosagem_personalizada();
          }
          else
          {
            sabado_dosagem_personalizada[dosadora_selecionada] = 6;
            config_dosagem_personalizada();
          }
        }
        else if (checkButtons(domI[0], domI[1], domI[2], domI[3]) == true)
        {
          if (domingo_dosagem_personalizada[dosadora_selecionada] == 7)
          {
            domingo_dosagem_personalizada[dosadora_selecionada] = 0;
            config_dosagem_personalizada();
          }
          else
          {
            domingo_dosagem_personalizada[dosadora_selecionada] = 7;
            config_dosagem_personalizada();
          }
        }
        break;

      case 30:  // ----------------------------------------- Digitar a senha --------------------------------------------
#ifndef SKIP_PASSWORD_SCREEN
        if (checkButtons(boT1[0], boT1[1], boT1[2] , boT1[3]) == true) // Botao: 1
        {
          updateStr('1');
        }

        else if (checkButtons(boT2[0], boT2[1], boT2[2], boT2[3]) == true)  // Botao: 2
        {
          updateStr('2');
        }
        else if (checkButtons(boT3[0], boT3[1], boT3[2], boT3[3]) == true)  // Botao: 3
        {
          updateStr('3');
        }
        else if (checkButtons(boT4[0], boT4[1], boT4[2], boT4[3]) == true)  // Botao: 4
        {
          updateStr('4');
        }
        else if (checkButtons(boT5[0], boT5[1], boT5[2], boT5[3]) == true)  // Botao: 5
        {
          updateStr('5');
        }
        else if (checkButtons(boT6[0], boT6[1], boT6[2], boT6[3]) == true)  // Botao: 6
        {
          updateStr('6');
        }
        else if (checkButtons(boT7[0], boT7[1], boT7[2], boT7[3]) == true)  // Botao: 7
        {
          updateStr('7');
        }
        else if (checkButtons(boT8[0], boT8[1], boT8[2], boT8[3]) == true)  // Botao: 8
        {
          updateStr('8');
        }
        else if (checkButtons(boT9[0], boT9[1], boT9[2], boT9[3]) == true)  // Botao: 9
        {
          updateStr('9');
        }
        else if (checkButtons(boT0[0], boT0[1], boT0[2], boT0[3]) == true)  // Botao: 0
        {
          updateStr('0');
        }

        else if (checkButtons(boTL[0], boTL[1], boTL[2], boTL[3]) == true)  // Botao: limpar
        {
          for (int i = 0; i < 7; i++)
          {
            stCurrent[i] = '\0';
          }
          stCurrentLen = 0;

          drawFillRect(110, 210, 300, 225, 0, 0, 0);
        }
        else if (checkButtons(boTE[0], boTE[1], boTE[2], boTE[3]) == true)  // Botao: entrar
        {
          if ((stCurrent[0] == senha [0]) && (stCurrent[1] == senha [1]) && (stCurrent[2] == senha [2]) && (stCurrent[3] == senha [3]) && (stCurrent[4] == senha [4]) && (stCurrent[5] == senha [5]) && stCurrentLen <= 6)
          {
            stCurrentLen = 0;
            myGLCD.setFont(BigFont);
            myGLCD.setColor(0, 255, 0);
            myGLCD.setBackColor(0, 0, 0);

            strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[173])));
            myGLCD.print(buffer, 51, 192); // tabela_textos[173] = "SENHA CORRETA"

            delay(500);
            dispScreen = 1;
            clearScreen();
            menuScreen();
            memcpy(stCurrent, limpar_senha, sizeof(limpar_senha));
          }
          else if (stCurrentLen <= 6)
          {
#ifdef WATCHDOG
            wdt_reset();
#endif
            for (byte i = 0; i < 3; i++)
            {
              myGLCD.setFont(BigFont);
              myGLCD.setColor(255, 0, 0);
              myGLCD.setBackColor(0, 0, 0);
              strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[174])));
              myGLCD.print(buffer, 35, 192); // tabela_textos[174] = "SENHA INCORRETA!"

              delay(1000);

              drawFillRect(35, 192, 300, 207, 0, 0, 0);
              delay(500);
            }
            myGLCD.fillRect (110, 210, 300, 225); //Limpar senha impressa ***************
            stCurrentLen = 0;
            memcpy(stCurrent, limpar_senha, sizeof(limpar_senha));
          }
          else if (stCurrentLen > 6)
          {
#ifdef WATCHDOG
            wdt_reset();
#endif
            myGLCD.setFont(BigFont);
            myGLCD.setColor(255, 0, 0);
            myGLCD.setBackColor(0, 0, 0);

            strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[174])));
            myGLCD.print(buffer, 35, 192); // tabela_textos[174] = "SENHA INCORRETA!"

            delay(1000);

            drawFillRect(35, 192, 300, 207, 0, 0, 0);
            for (byte i = 0; i < 3; i++)
            {
              delay(500);
              myGLCD.setColor(255, 0, 0);
              strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[175])));
              myGLCD.print(buffer, 35, 192); // "MAXIMO 6 DIGITOS!"

              delay(1000);

              drawFillRect(35, 192, 300, 207, 0, 0, 0);
            }

            myGLCD.fillRect (110, 210, 300, 225); //Limpar senha impressa ***************
            stCurrentLen = 0;
            memcpy(stCurrent, limpar_senha, sizeof(limpar_senha));
          }
        }
#endif
        break;
      case 31:// ----------------------------------------- Dosagem personalizada --------------------------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(anT[0], anT[1], anT[2], anT[3]) == true) // Volta ao menu dosagem personalizada
        {
          dispScreen = 29;
          clearScreen();
          config_dosagem_personalizada(true);
        }
        else if (checkButtons(minUT[0], minUT[1], minUT[2], minUT[3]) == true) // Dose diaria mais
        {
          dose_dosadora_personalizada[dosadora_selecionada] += 0.5;
          if (dose_dosadora_personalizada[dosadora_selecionada] > 999.5)
          {
            dose_dosadora_personalizada[dosadora_selecionada] = 0.5;
          }
          else if (dose_dosadora_personalizada[dosadora_selecionada] <= 9.5)
          {
            drawFillRect(100, 45, 185, 67, 0, 0, 0);
          }

          config_dosagem_personalizada_2();
        }
        else if (checkButtons(minDT[0], minDT[1], minDT[2], minDT[3]) == true) // Dose diaria menos
        {
          dose_dosadora_personalizada[dosadora_selecionada] -= 0.5;
          if (dose_dosadora_personalizada[dosadora_selecionada] < 0.5)
          {
            dose_dosadora_personalizada[dosadora_selecionada] = 999.5;
          }
          else if (dose_dosadora_personalizada[dosadora_selecionada] <= 9.5)
          {
            drawFillRect(100, 45, 185, 67, 0, 0, 0);
          }
          config_dosagem_personalizada_2();
        }
        else  if (checkButtons(durC[0], durC[1], durC[2], durC[3]) == true)
        {
          quantidade_dose_dosadora_personalizada[dosadora_selecionada] += 1;
          if (quantidade_dose_dosadora_personalizada[dosadora_selecionada] > 24)
          {
            quantidade_dose_dosadora_personalizada[dosadora_selecionada] = 1;
          }
          config_dosagem_personalizada_2();
        }
        else if (checkButtons(durB[0], durB[1], durB[2], durB[3]) == true)
        {
          quantidade_dose_dosadora_personalizada[dosadora_selecionada] -= 1;
          if (quantidade_dose_dosadora_personalizada[dosadora_selecionada] < 1)
          {
            quantidade_dose_dosadora_personalizada[dosadora_selecionada] = 24;
          }
          config_dosagem_personalizada_2();
        }
        else  if (checkButtons(sexT[0], sexT[1], sexT[2], sexT[3]) == true) // Ativar ou desativar modo personalizado
        {
          if (modo_personalizado_on[dosadora_selecionada] == 0)
          {
            modo_personalizado_on[dosadora_selecionada] = 1;
            config_dosagem_personalizada_2();
          }
          else
          {
            modo_personalizado_on[dosadora_selecionada] = 0;
            config_dosagem_personalizada_2();
          }
        }
        else if (checkButtons(prOK[0], prOK[1], prOK[2], prOK[3]) == true)
        {
          if ((hora_final_dosagem_personalizada[dosadora_selecionada] == hora_inicial_dosagem_personalizada[dosadora_selecionada])
              && (minuto_final_dosagem_personalizada[dosadora_selecionada] < (minuto_inicial_dosagem_personalizada[dosadora_selecionada] + 10)))
          {
            myGLCD.setColor(255, 255, 0);
            myGLCD.fillRoundRect(15, 90, 319, 155);

            myGLCD.setColor(255, 0, 0);
            myGLCD.drawRoundRect(15, 90, 319, 155);

            setFont(SMALL, 255, 0, 0, 255, 255, 0);

            strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[176])));
            myGLCD.print(buffer, 20, 110); // "O INTERVALO ENTRE A INICIAL E A FINAL"

            strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[177])));
            myGLCD.print(buffer, 35, 130); // "DEVE SER DE NO MINIMO 10 MINUTOS!"
          }
          else if (hora_final_dosagem_personalizada[dosadora_selecionada] < hora_inicial_dosagem_personalizada[dosadora_selecionada])
          {
            myGLCD.setColor(255, 255, 0);
            myGLCD.fillRoundRect(15, 90, 319, 155);

            myGLCD.setColor(255, 0, 0);
            myGLCD.drawRoundRect(15, 90, 319, 155);

            setFont(SMALL, 255, 0, 0, 255, 255, 0);

            strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[178])));
            myGLCD.print(buffer, 50, 110);// "A HORA FINAL NAO PODE SER MENOR"

            strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[179])));
            myGLCD.print(buffer, 100, 130); // "QUE A INICIAL!"
          }
          else if (((hora_final_dosagem_personalizada[dosadora_selecionada] == hora_inicial_dosagem_personalizada[dosadora_selecionada])
                    && (minuto_final_dosagem_personalizada[dosadora_selecionada] >= (minuto_inicial_dosagem_personalizada[dosadora_selecionada] + 10)))
                   || (hora_final_dosagem_personalizada[dosadora_selecionada] > hora_inicial_dosagem_personalizada[dosadora_selecionada]))
          {
            config_valores_salvar_dosadoras();
            dispScreen = 21;
            clearScreen();
            selecionar_dosadora();
            setFont(SMALL, 255, 255, 255, 0, 0, 0);

            strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[171])));
            myGLCD.print(buffer, 15, 220); // tabela_textos[171] = "MODO PERSONALIZADO SELECIONADO"

            modo_manual = false;
            modo_personalizado = true;
            modo_calibrar = false;

            criar_arquivos();
            Salvar_dosadora_EEPROM();
          }
        }
        break;
      case 32: // -------------------------------- Rever configuração das dosadoras ------------------------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // volta ao menu das dosadoras
        {
          dispScreen = 8;
          clearScreen();
          menu_dosadoras();
        }
        else if (checkButtons(manU[0], manU[1], manU[2], manU[3]) == true)           // Rever configuração dosagem personalizada
        {
          dispScreen = 34;
          clearScreen();
          rever_dosagem_personalizada();
        }
        break;
      case 34:// -------------------------------- Rever configuração das dosadoras personalizado ------------------------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // volta ao menu de revisão das dosadoras
        {
          dispScreen = 32;
          clearScreen();
          rever_configuracao_dosadoras();
        }
        else if (checkButtons(salV[0], salV[1], salV[2], salV[3]) == true)           // Mais dosadoras
        {
          dispScreen = 23;
          clearScreen();
          rever_dosagem_personalizada();
        }
        break;

      case 35:// -------------------------------------- livre ------------------------------------------
        break;

      case 36: // -------------------------------- Luz noturna --------------------------------------------
        if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // volta a tela configurar leds
        {
          dispScreen = 40;
          clearScreen();
          config_leds();
        }
        else if (checkButtons(salV[0], salV[1], salV[2], salV[3]) == true)       //Funcao salvar
        {
          MaxI = tMaxI;
          MinI = tMinI;
          dispScreen = 40;
          Salvar_luz_noturna_EEPROM();
          clearScreen();
          config_leds();
        }
        else if (checkButtons(temM[0], temM[1], temM[2], temM[3]) == true)                      //press densidade minus
        {
          tMaxI -= 1;
          drawFillRect(128, 40, 180, 56, 0, 0, 0);
          luz_noturna();
        }
        else if (checkButtons(almM[0], almM[1], almM[2], almM[3]) == true)                        //press alarm minus
        {
          tMinI -= 1;
          drawFillRect(128, 140, 180, 156, 0, 0, 0);
          luz_noturna();
        }
        else if (checkButtons(temP[0], temP[1], temP[2], temP[3]) == true)                      //press densidade plus
        {
          tMaxI += 1;
          drawFillRect(128, 40, 180, 56, 0, 0, 0);
          luz_noturna();
        }
        else if (checkButtons(almP[0], almP[1], almP[2], almP[3]) == true)                           //press alarm plus
        {
          tMinI += 1;
          drawFillRect(128, 140, 180, 156, 0, 0, 0);
          luz_noturna();
        }
        else if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu 1
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        break;
      case 37: // -------------------------------- Menu 2 --------------------------------------------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // Volta ao menu 1
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(tanD[0], tanD[1], tanD[2], tanD[3]) == true)           // Sensores de temperatura
        {
          dispScreen = 41;
          clearScreen();
          procurar_sensores(true);
        }
        else if (checkButtons(tesT[0], tesT[1], tesT[2], tesT[3]) == true)           // Alimentador automático
        {
          dispScreen = 45;
          clearScreen();
          alimentadorScreen(true);
        }
        break;
      case 38: // -------------------------------- Timers --------------------------------------------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // Volta ao menu 1
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(7, 22, 56, 238) == true)           // Timer 1
        {
          temporizador = 0;
          dispScreen = 39;
          clearScreen();
          config_timer(true);
        }
        else if (checkButtons(71, 22, 120, 238) == true)           // Timer 2
        {
          temporizador = 1;
          dispScreen = 39;
          clearScreen();
          config_timer(true);
        }
        else if (checkButtons(135, 22, 184, 238) == true)           // Timer 3
        {
          temporizador = 2;
          dispScreen = 39;
          clearScreen();
          config_timer(true);
        }
        else if (checkButtons(199, 22, 248, 238) == true)           // Timer 4
        {
          temporizador = 3;
          dispScreen = 39;
          clearScreen();
          config_timer(true);
        }
        else if (checkButtons(263, 22, 312, 238) == true)           // Timer 5
        {
          temporizador = 4;
          dispScreen = 39;
          clearScreen();
          config_timer(true);
        }
        break;
      case 39:// -------------------------------- Configurar timers ------------------------------------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // Volta ao menu 2
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // Selecionar timer
        {
          dispScreen = 38;
          clearScreen();
          TimerScreen();
        }
        else if (checkButtons(salV[0], salV[1], salV[2], salV[3]) == true)
        {
          config_valores_salvar_timers();
          dispScreen = 38;
          clearScreen();
          TimerScreen();
          salvar_timers_EEPROM();
          bitWrite(temporizador_modificado, (temporizador + 1), 1);
        }
        else if (checkButtons(21, 45, 65, 88) == true)           // Hora ligar mais
        {
          on_hora[temporizador] += 1;
          if (on_hora[temporizador] > 23)
          {
            on_hora[temporizador] = 0;
          }
          config_timer();
        }
        else if (checkButtons(21, 135, 65, 178) == true)           // Hora ligar menos
        {
          on_hora[temporizador] -= 1;
          if (on_hora[temporizador] > 200) // 0 - 1 = 255 pois, byte varia de  0 a 255.
          {
            on_hora[temporizador] = 23;
          }
          config_timer();
        }

        else if (checkButtons(89, 45, 133, 88) == true)           // Minuto ligar mais
        {
          on_minuto[temporizador] += 1;
          if (on_minuto[temporizador] > 59)
          {
            on_minuto[temporizador] = 0;
          }
          config_timer();
        }
        else if (checkButtons(89, 135, 133, 178) == true)           // Minuto ligar menos
        {
          on_minuto[temporizador] -= 1;
          if (on_minuto[temporizador] > 200) // 0 - 1 = 255 pois, byte varia de  0 a 255.
          {
            on_minuto[temporizador] = 59;
          }
          config_timer();
        }
        else if (checkButtons(187, 45, 231, 88) == true)           // Hora desligar mais
        {
          off_hora[temporizador] += 1;
          if (off_hora[temporizador] > 23)
          {
            off_hora[temporizador] = 0;
          }
          config_timer();
        }
        else if (checkButtons(187, 135, 231, 178) == true)           // Hora desligar menos
        {
          off_hora[temporizador] -= 1;
          if (off_hora[temporizador] > 200) // 0 - 1 = 255 pois, byte varia de  0 a 255.
          {
            off_hora[temporizador] = 23;
          }
          config_timer();
        }

        else if (checkButtons(255, 45, 299, 88) == true)           // Minuto desligar mais
        {
          off_minuto[temporizador] += 1;
          if (off_minuto[temporizador] > 59)
          {
            off_minuto[temporizador] = 0;
          }
          config_timer();
        }
        else if (checkButtons(255, 135, 299, 178) == true)           // Minuto desligar menos
        {
          off_minuto[temporizador] -= 1;
          if (off_minuto[temporizador] > 200) // 0 - 1 = 255 pois, byte varia de  0 a 255.
          {
            off_minuto[temporizador] = 59;
          }
          config_timer();
        }
        else  if (checkButtons(domI[0] - 20, domI[1], domI[2] + 20, domI[3]) == true)       // Ativar / desativar timer
        {
          if (temporizador_ativado[temporizador] == 0)
          {
            temporizador_ativado[temporizador] = 1;
          }
          else
          {
            temporizador_ativado[temporizador] = 0;
          }
          config_timer();
        }
        break;
      case 40://---------------------------------------- Configurar leds ----------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // Volta ao menu 1
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(tanD[0], tanD[1], tanD[2], tanD[3]) == true)           // Testar leds
        {
          dispScreen = 25;
          clearScreen();
          escolher_teste();
        }
        else if (checkButtons(tesT[0], tesT[1], tesT[2], tesT[3]) == true)           // Alterar valores led
        {
          dispScreen = 28;
          clearScreen();
          escolher_canal();
        }
        else if (checkButtons(temC[0], temC[1], temC[2], temC[3]) == true)           // Luz Noturna
        {
          dispScreen = 36;
          clearScreen();
          luz_noturna(true);
        }
        else if (checkButtons(graF[0], graF[1], graF[2], graF[3]) == true)           // coolers
        {
          dispScreen = 42;
          clearScreen();
          configurar_coolers(true);
        }
        else if (checkButtons(ledW[0], ledW[1], ledW[2], ledW[3]) == true)           // Reduzir potência
        {
          dispScreen = 43;
          clearScreen();
          reduzir_potencia(true);
        }
        else if (checkButtons(tpaA[0], tpaA[1], tpaA[2], tpaA[3]) == true)           // Pre definido
        {
          dispScreen = 44;
          clearScreen();
          pre_definido(true);
        }
        break;
      case 41://---------------------------------------- Configurar sensores de temperatura ----------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // Volta ao menu 2
        {
          dispScreen = 37;
          clearScreen();
          menuScreen_2();
        }
        else if (checkButtons(busC[0], busC[1], busC[2], busC[3]) == true)           // Buscar sondas
        {
          clearScreen();
          procurar_sensores(true);
        }
        else if (checkButtons(sonD1[0], sonD1[1], sonD1[2], sonD1[3]) == true)           // Sonda 1
        {
          if (sonda_associada_1_temp == 1)
          {
            sonda_associada_1_temp = 2;
          }
          else if (sonda_associada_1_temp == 2)
          {
            sonda_associada_1_temp = 3;
          }
          else
          {
            sonda_associada_1_temp = 1;
          }
          procurar_sensores();
        }
        else if (checkButtons(sonD2[0], sonD2[1], sonD2[2], sonD2[3]) == true)           // Sonda 2
        {
          if (sonda_associada_2_temp == 1)
          {
            sonda_associada_2_temp = 2;
          }
          else if (sonda_associada_2_temp == 2)
          {
            sonda_associada_2_temp = 3;
          }
          else
          {
            sonda_associada_2_temp = 1;
          }
          procurar_sensores();
        }
        else if (checkButtons(sonD3[0], sonD3[1], sonD3[2], sonD3[3]) == true)           // Sonda 3
        {
          if (sonda_associada_3_temp == 1)
          {
            sonda_associada_3_temp = 2;
          }
          else if (sonda_associada_3_temp == 2)
          {
            sonda_associada_3_temp = 3;
          }
          else
          {
            sonda_associada_3_temp = 1;
          }
          procurar_sensores();
        }
        else if (checkButtons(prOK[0], prOK[1], prOK[2], prOK[3]) == true)           // Sonda 3
        {
          if ((sonda_associada_1_temp == sonda_associada_2_temp) || (sonda_associada_1_temp == sonda_associada_3_temp) || (sonda_associada_2_temp == sonda_associada_3_temp))
          {
            setFont(SMALL, 255, 0, 0, 0, 0, 0);
            strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[223]))); // "NAO ASSOCIE 2 OU 3"
            myGLCD.print(buffer, 10, 160);
            strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[224]))); // "SONDAS AO MESMO PARAMETRO"
            myGLCD.print(buffer, 10, 195);
          }
          else
          {
            sonda_associada_1 = sonda_associada_1_temp;
            sonda_associada_2 = sonda_associada_2_temp;
            sonda_associada_3 = sonda_associada_3_temp;

            for (byte i = 0; i < 8; i++)
            {
              if (sonda_associada_1_temp == 1)
              {
                sensor_agua[i] = sonda1[i];
              }
              else if (sonda_associada_1_temp == 2)
              {
                sensor_agua[i] = sonda2[i];
              }
              else
              {
                sensor_agua[i] = sonda3[i];
              }
              if (sonda_associada_2_temp == 1)
              {
                sensor_dissipador[i] = sonda1[i];
              }
              else if (sonda_associada_2_temp == 2)
              {
                sensor_dissipador[i] = sonda2[i];
              }
              else
              {
                sensor_dissipador[i] = sonda3[i];
              }

              if (sonda_associada_3_temp == 1)
              {
                sensor_ambiente[i] = sonda1[i];
              }
              else if (sonda_associada_3_temp == 2)
              {
                sensor_ambiente[i] = sonda2[i];
              }
              else
              {
                sensor_ambiente[i] = sonda3[i];
              }
            }
            contador_temp = 0;
            temperatura_agua_temp = 0;
            temperatura_dissipador_temp = 0;
            temperatura_ambiente_temp = 0;
            sensors.requestTemperatures();   // Chamada para todos os sensores.
#ifdef USE_FAHRENHEIT
            tempC = (sensors.getTempF(sensor_agua));       // Lê a temperatura da água
            tempH = (sensors.getTempF(sensor_dissipador)); // Lê a temperatura do dissipador.
            tempA = (sensors.getTempF(sensor_ambiente));   // Lê a temperatura do ambiente.
#else
            tempC = (sensors.getTempC(sensor_agua));  // Lê a temperatura da água
            tempH = (sensors.getTempC(sensor_dissipador)); // Lê a temperatura do dissipador.
            tempA = (sensors.getTempC(sensor_ambiente)); // Lê a temperatura do ambiente.
#endif
            SaveDallasAddress ();
            dispScreen = 37;
            clearScreen();
            menuScreen_2();
          }
        }
        break;
      case 42://---------------------------------------- Configurar coolers ----------------------------
        if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // volta a tela configurar leds
        {
          dispScreen = 40;
          clearScreen();
          config_leds();
        }
        else if (checkButtons(salV[0], salV[1], salV[2], salV[3]) == true)       //Função salvar
        {
          HtempMin = HtempMin_temp;
          HtempMax = HtempMax_temp;
          dispScreen = 40;
          salvar_coolersEEPROM();
          clearScreen();
          config_leds();
        }
        else if (checkButtons(temM[0], temM[1], temM[2], temM[3]) == true)                   // Temperatura para velocidade mínima -
        {
          HtempMin_temp -= 0.1;
#ifdef USE_FAHRENHEIT
          if (HtempMin_temp < 68)
          {
            HtempMin_temp = 95;
          }
#else
          if (HtempMin_temp < 20)
          {
            HtempMin_temp = 35;
          }
#endif

          drawFillRect(128, 40, 180, 56, 0, 0, 0);
          configurar_coolers();
        }
        else if (checkButtons(almM[0], almM[1], almM[2], almM[3]) == true)                       // Temperatura para velocidade máxima -
        {
          HtempMax_temp -= 0.1;
#ifdef USE_FAHRENHEIT
          if (HtempMax_temp < 96.8)
          {
            HtempMax_temp = 122.0;
          }
#else
          if (HtempMax_temp < 36)
          {
            HtempMax_temp = 50;
          }
#endif
          drawFillRect(128, 140, 180, 156, 0, 0, 0);
          configurar_coolers();
        }
        else if (checkButtons(temP[0], temP[1], temP[2], temP[3]) == true)                      // Temperatura para velocidade mínima +
        {
          HtempMin_temp += 0.1;
#ifdef USE_FAHRENHEIT
          if (HtempMin_temp > 95)
          {
            HtempMin_temp = 68;
          }
#else
          if (HtempMin_temp > 35)
          {
            HtempMin_temp = 20;
          }
#endif
          drawFillRect(128, 40, 180, 56, 0, 0, 0);
          configurar_coolers();
        }
        else if (checkButtons(almP[0], almP[1], almP[2], almP[3]) == true)                           // Temperatura para velocidade máxima +
        {
          HtempMax_temp += 0.1;
#ifdef USE_FAHRENHEIT
          if (HtempMax_temp > 122)
          {
            HtempMax_temp = 96.8;
          }
#else
          if (HtempMax_temp > 50)
          {
            HtempMax_temp = 36;
          }
#endif
          drawFillRect(128, 140, 180, 156, 0, 0, 0);
          configurar_coolers();
        }
        else if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu 1
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        break;
      case 43://---------------------------------------- Reduziir potência dos leds ----------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu 1
        {
          dispScreen = 1;
          clearScreen();
          menuScreen();
        }
        else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // volta a tela configurar leds
        {
          dispScreen = 40;
          clearScreen();
          config_leds();
        }
        else if (checkButtons(salV[0], salV[1], salV[2], salV[3]) == true)       //Função salvar
        {
          tempHR = tempHR_t;
          potR = potR_t;
          dispScreen = 40;
          salvar_tempPotEEPROM();
          clearScreen();
          config_leds();
        }
        else if (checkButtons(tempeC[0], tempeC[1], tempeC[2], tempeC[3]) == true)       //Temperatura +
        {
          tempHR_t += 1;
#ifdef USE_FAHRENHEIT
          if (tempHR_t > 210.2)
          {
            tempHR_t = 86;
          }
#else
          if (tempHR_t > 99)
          {
            tempHR_t = 30;
          }
#endif
          reduzir_potencia();
        }
        else if (checkButtons(tempeB[0], tempeB[1], tempeB[2], tempeB[3]) == true)       //Temperatura -
        {
          tempHR_t -= 1;
#ifdef USE_FAHRENHEIT
          if (tempHR_t < 86)
          {
            tempHR_t = 210.2;
          }
#else
          if (tempHR_t < 30)
          {
            tempHR_t = 99;
          }
#endif
          reduzir_potencia();
        }
        else if (checkButtons(potC[0], potC[1], potC[2], potC[3]) == true)       //Potência +
        {
          potR_t += 1;
          if (potR_t > 99)
          {
            potR_t = 1;
          }
          reduzir_potencia();
        }
        else if (checkButtons(potB[0], potB[1], potB[2], potB[3]) == true)    //Potência -
        {
          potR_t -= 1;
          if (potR_t < 1)
          {
            potR_t = 99;
          }
          reduzir_potencia();
        }
        break;
      case 44://---------------------------------------- Potência pré-definida para os leds ----------------------------
        if (horario_alterado == false)
        {
          if (checkButtons(205, 95, 315, 180) == true)
          {
            clearScreen();
            horario_alterado = true;
            pre_definido();
          }
          else if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu 1
          {
            dispScreen = 1;
            clearScreen();
            menuScreen();
            ler_predefinido_EEPROM();
          }
          else if (checkButtons(volT[0], volT[1], volT[2], volT[3]) == true)           // volta a tela configurar leds
          {
            dispScreen = 40;
            clearScreen();
            config_leds();
            ler_predefinido_EEPROM();
          }
          else if (checkButtons(salV[0], salV[1], salV[2], salV[3]) == true)           // volta a tela configurar leds
          {
            dispScreen = 40;
            clearScreen();
            config_leds();
            led_on_minuto = led_on_minuto_t;
            led_on_hora = led_on_hora_t;
            led_off_minuto = led_off_minuto_t;
            led_off_hora = led_off_hora_t;
            predefinido = predefinido_t;
            pre_definido_ativado = pre_definido_ativado_t;
            pwm_pre_definido = pwm_pre_definido_t;
            led_on_minuto = led_on_minuto_t;
            led_on_hora = led_on_hora_t;
            led_off_minuto = led_off_minuto_t;
            led_off_hora = led_off_hora_t;
            amanhecer_anoitecer = amanhecer_anoitecer_t;
            Salvar_predefinido_EEPROM();
            hora_modificada = true;
          }
          else if (checkButtons(210, 60, 310, 90) == true) // Ativar / desativar
          {
            if (pre_definido_ativado_t == 1)
            {
              pre_definido_ativado_t = 0;
            }
            else
            {
              pre_definido_ativado_t = 1;
            }
            pre_definido();
          }
          else if (checkButtons(210, 25, 310, 55) == true) // Controlar todos
          {
            if (predefinido_t == 1)
            {
              predefinido_t = 0;
            }
            else
            {
              predefinido_t = 1;
            }
            pre_definido();
          }
          else if (checkButtons(10, 25, 200, 55) == true) // Controlar individualmente 10, 25, 200, 55
          {
            if (predefinido_t == 1)
            {
              predefinido_t = 0;
            }
            else
            {
              predefinido_t = 1;
            }
            pre_definido();
          }
          if (pre_definido_ativado_t == 1) // Permite alterar valores somente se a função estiver ativada.
          {
            int m = 0;
            int n = 0;
            if (predefinido_t == 0) // Se predefinido igual a um. Controlar individualmente.
            {
              if ((x >= 135) && (x <= 165)) // individual pwm +
              {
                for (m = 0; m < 5; m++)
                {
                  n = m * 5;
                  if ((y >= 60 + (m * 30) + n) && (y <= 90 + (m * 30) + n))
                  {
                    waitForIt(135, (60 + (m * 30) + n), 165, (90 + (m * 30) + n));
                    if (m == 0)
                    {
                      wled_out_temp += 1;
                    }
                    else if (m == 1)
                    {
                      bled_out_temp += 1;
                    }
                    else if (m == 2)
                    {
                      rbled_out_temp += 1;
                    }
                    else if (m == 3)
                    {
                      rled_out_temp += 1;
                    }
                    else if (m == 4)
                    {
                      uvled_out_temp += 1;
                    }
                  }
                }
                pre_definido();
              }
              else if ((x >= 170) && (x <= 200)) // individual pwm -
              {
                for (int i = 0; i < 5; i++)
                {
                  for (m = 0; m < 5; m++)
                  {
                    n = m * 5;
                    if ((y >= 60 + (m * 30) + n) && (y <= 90 + (m * 30) + n))
                    {
                      waitForIt(170, (60 + (m * 30) + n), 200, (90 + (m * 30) + n));
                      if (m == 0)
                      {
                        wled_out_temp -= 1;
                      }
                      else if (m == 1)
                      {
                        bled_out_temp -= 1;
                      }
                      else if (m == 2)
                      {
                        rbled_out_temp -= 1;
                      }
                      else if (m == 3)
                      {
                        rled_out_temp -= 1;
                      }
                      else if (m == 4)
                      {
                        uvled_out_temp -= 1;
                      }
                    }
                  }
                }
                pre_definido();
              }
            }
            else // Se predefinido igual a zero. Controlar individualmente.
            {
              if (checkButtons(210, 200, 240, 230) == true) // PWM +
              {
                pwm_pre_definido_t += 1;
                pre_definido();
              }
              else if (checkButtons(280, 200, 310, 230) == true) // PWM -
              {
                pwm_pre_definido_t -= 1;
                pre_definido();
              }
            }
          }
        }
        else // Configurar hora
        {
          if (checkButtons(30, 45, 55, 70) == true)           // Hora ligar mais
          {
            led_on_hora_t += 1;
            if (led_on_hora_t > 23)
            {
              led_on_hora_t = 0;
            }
            pre_definido();
          }
          else if (checkButtons(30, 105, 55, 130) == true)           // Hora ligar menos
          {
            led_on_hora_t -= 1;
            if (led_on_hora_t > 200) // 0 - 1 = 255 pois, byte varia de  0 a 255.
            {
              led_on_hora_t = 23;
            }
            pre_definido();
          }

          else if (checkButtons(100, 45, 125, 70) == true)           // Minuto ligar mais
          {
            led_on_minuto_t += 1;
            if (led_on_minuto_t > 59)
            {
              led_on_minuto_t = 0;
            }
            pre_definido();
          }
          else if (checkButtons(100, 105, 125, 130) == true)           // Minuto ligar menos
          {
            led_on_minuto_t -= 1;
            if (led_on_minuto_t > 200) // 0 - 1 = 255 pois, byte varia de  0 a 255.
            {
              led_on_minuto_t = 59;
            }
            pre_definido();
          }
          else if (checkButtons(195, 45, 220, 70) == true)           // Hora desligar mais
          {
            led_off_hora_t += 1;
            if (led_off_hora_t > 23)
            {
              led_off_hora_t = 0;
            }
            pre_definido();
          }
          else if (checkButtons(195, 105, 220, 130) == true)           // Hora desligar menos
          {
            led_off_hora_t -= 1;
            if (led_off_hora_t > 200) // 0 - 1 = 255 pois, byte varia de  0 a 255.
            {
              led_off_hora_t = 23;
            }
            pre_definido();
          }
          else if (checkButtons(265, 45, 290, 70) == true)           // Minuto desligar mais
          {
            led_off_minuto_t += 1;
            if (led_off_minuto_t > 59)
            {
              led_off_minuto_t = 0;
            }
            pre_definido();
          }
          else if (checkButtons(265, 105, 290, 130) == true)           // Minuto desligar menos
          {
            led_off_minuto_t -= 1;
            if (led_off_minuto_t > 200) // 0 - 1 = 255 pois, byte varia de  0 a 255.
            {
              led_off_minuto_t = 59;
            }
            pre_definido();
          }
          else if (checkButtons(195, 175, 220, 200) == true)           // Amanhecer/anoitecer mais
          {
            amanhecer_anoitecer_t += 1;
            if (amanhecer_anoitecer_t > 240)
            {
              amanhecer_anoitecer_t = 60;
            }
            pre_definido();
          }
          else if (checkButtons(100, 175, 125, 200) == true)           // Amanhecer/anoitecer menos
          {
            amanhecer_anoitecer_t -= 1;
            if (amanhecer_anoitecer_t < 60)
            {
              amanhecer_anoitecer_t = 240;
            }
            pre_definido();
          }
          else if (checkButtons(iniC[0], iniC[1], iniC[2], iniC[3]) == true)           // PRONTO
          {
            if (((NumMins(led_off_hora_t, led_off_minuto_t) + amanhecer_anoitecer) > 1439) || ((NumMins(led_on_hora_t, led_on_minuto_t) + amanhecer_anoitecer) > 1439))
            {
              setFont(SMALL, 255, 0, 0, 0, 0, 0);
              strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[255])));
              myGLCD.print(buffer, 30, 210); // "ANOITECER + DURACAO OU AMANHECER + DURACAO"

              strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[256])));
              myGLCD.print(buffer, 70, 225); // "NAO PODEM ULTRAPASSAR AS 0 H!"
            }
            else
            {
              clearScreen();
              pre_definido(true);
            }
          }
        }
        break;
      case 45:   // ----------------------------------------- Config alimentador automático --------------------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu
        {
          dispScreen = 37;
          clearScreen();
          menuScreen_2();
        }
        else if (checkButtons(proX[0], proX[1], proX[2], proX[3]) == true)
        {
          dispScreen = 46;
          clearScreen();
          alimentadorScreen_2(true);
        }
        else if (checkButtons(anT[0], anT[1], anT[2], anT[3]) == true)
        {
          inicia_alimentacao();
          alimentadorScreen();
        }
        else if (checkButtons(houU[0], houU[1], houU[2], houU[3]) == true)
        {
          horario_alimentacao[0] = (horario_alimentacao[0] + 1) % 24;
          alimentadorScreen();
        }
        else if (checkButtons(minUT[0], minUT[1], minUT[2], minUT[3]) == true)
        {
          horario_alimentacao[1] = (horario_alimentacao[1] + 1) % 60;
          alimentadorScreen();
        }

        else if (checkButtons(houU[0] + 155, houU[1], houU[2] + 155, houU[3]) == true)
        {
          horario_alimentacao[2] = (horario_alimentacao[2] + 1) % 24;
          alimentadorScreen();
        }
        else if (checkButtons(minUT[0] + 155, minUT[1], minUT[2] + 155, minUT[3]) == true)
        {
          horario_alimentacao[3] = (horario_alimentacao[3] + 1) % 60;
          alimentadorScreen();
        }
        else if (checkButtons(houD[0], houD[1], houD[2], houD[3]) == true)
        {
          horario_alimentacao[0] = (horario_alimentacao[0] + 23) % 24;
          alimentadorScreen();
        }
        else if (checkButtons(minDT[0], minDT[1], minDT[2], minDT[3]) == true)
        {
          horario_alimentacao[1] = (horario_alimentacao[1] + 59) % 60;
          alimentadorScreen();
        }
        else if (checkButtons(houD[0] + 155, houD[1], houD[2] + 155, houD[3]) == true)
        {
          horario_alimentacao[2] = (horario_alimentacao[2] + 23) % 24;
          alimentadorScreen();
        }
        else if (checkButtons(minDT[0] + 155, minDT[1], minDT[2] + 155, minDT[3]) == true)
        {
          horario_alimentacao[3] = (horario_alimentacao[3] + 59) % 60;
          alimentadorScreen();
        }
        else if (checkButtons(segU[0], segU[1], segU[2], segU[3]) == true)
        {
          if (dia_alimentacao[0] == 1)
          {
            dia_alimentacao[0] = 0;
            alimentadorScreen();
          }
          else
          {
            dia_alimentacao[0] = 1;
            alimentadorScreen();
          }
        }
        else if (checkButtons(terC[0], terC[1], terC[2], terC[3]) == true)
        {
          if (dia_alimentacao[1] == 2)
          {
            dia_alimentacao[1] = 0;
            alimentadorScreen();
          }
          else
          {
            dia_alimentacao[1] = 2;
            alimentadorScreen();
          }
        }
        else if (checkButtons(quaR[0], quaR[1], quaR[2], quaR[3]) == true)
        {
          if (dia_alimentacao[2] == 3)
          {
            dia_alimentacao[2] = 0;
            alimentadorScreen();
          }
          else
          {
            dia_alimentacao[2] = 3;
            alimentadorScreen();
          }
        }
        else if (checkButtons(quiN[0] , quiN[1], quiN[2], quiN[3]) == true)
        {
          if (dia_alimentacao[3] == 4)
          {
            dia_alimentacao[3] = 0;
            alimentadorScreen();
          }
          else
          {
            dia_alimentacao[3] = 4;
            alimentadorScreen();
          }
        }
        else if (checkButtons(sexT[0], sexT[1], sexT[2], sexT[3]) == true)
        {
          if (dia_alimentacao[4] == 5)
          {
            dia_alimentacao[4] = 0;
            alimentadorScreen();
          }
          else
          {
            dia_alimentacao[4] = 5;
            alimentadorScreen();
          }
        }
        else if (checkButtons(sabA[0], sabA[1], sabA[2], sabA[3]) == true)
        {
          if (dia_alimentacao[5] == 6)
          {
            dia_alimentacao[5] = 0;
            alimentadorScreen();
          }
          else
          {
            dia_alimentacao[5] = 6;
            alimentadorScreen();
          }
        }
        else if (checkButtons(domI[0], domI[1], domI[2], domI[3]) == true)
        {
          if (dia_alimentacao[6] == 7)
          {
            dia_alimentacao[6] = 0;
            alimentadorScreen();
          }
          else
          {
            dia_alimentacao[6] = 7;
            alimentadorScreen();
          }
        }
        break;
      case 46:   // ----------------------------------------- Config alimentador automático --------------------------------------
        if (checkButtons(menU[0], menU[1], menU[2], menU[3]) == true)           // volta ao menu 2
        {
          dispScreen = 37;
          clearScreen();
          menuScreen_2();
        }
        else if (checkButtons(anT[0], anT[1], anT[2], anT[3]) == true)
        {
          dispScreen = 45;
          clearScreen();
          alimentadorScreen(true);
        }
        if (alimentacao_erro == false)
        {
          if (checkButtons(minUT[0], minUT[1], minUT[2], minUT[3]) == true)
          {
            duracao_alimentacao_temp += 1;
            if (duracao_alimentacao_temp > 99)
            {
              duracao_alimentacao_temp = 1;
            }
            alimentadorScreen_2();
          }
          else if (checkButtons(minDT[0], minDT[1], minDT[2], minDT[3]) == true)
          {
            duracao_alimentacao_temp -= 1;
            if (duracao_alimentacao_temp < 1)
            {
              duracao_alimentacao_temp = 99;
            }
            alimentadorScreen_2();
          }
          else  if (checkButtons(durC[0], durC[1], durC[2], durC[3]) == true)
          {
            quantidade_alimentacao_temp += 1;
            if (quantidade_alimentacao_temp > 24)
            {
              quantidade_alimentacao_temp = 1;
            }
            alimentadorScreen_2();
          }
          else if (checkButtons(durB[0], durB[1], durB[2], durB[3]) == true)
          {
            quantidade_alimentacao_temp -= 1;
            if (quantidade_alimentacao_temp < 1)
            {
              quantidade_alimentacao_temp = 24;
            }
            alimentadorScreen_2();
          }
          else if (checkButtons(minUA[0], minUA[1], minUA[2], minUA[3]) == true)
          {
            desligar_wavemaker_temp += 2;
            if (desligar_wavemaker_temp > 98)
            {
              desligar_wavemaker_temp = 2;
            }
            alimentadorScreen_2();
          }
          else if (checkButtons(minDA[0], minDA[1], minDA[2], minDA[3]) == true)
          {
            desligar_wavemaker_temp -= 2;
            if (desligar_wavemaker_temp < 2)
            {
              desligar_wavemaker_temp = 98;
            }
            alimentadorScreen_2();
          }
          else  if (checkButtons(alI[0], alI[1], alI[2], alI[3]) == true) // Ativar ou desativar alimentador
          {
            if (bitRead(alimentacao_wavemaker_on_off_temp, 0) == 0)
            {
              bitWrite(alimentacao_wavemaker_on_off_temp, 0, 1);
              alimentadorScreen_2();
            }
            else
            {
              bitWrite(alimentacao_wavemaker_on_off_temp, 0, 0);
              alimentadorScreen_2();
            }
          }
          else  if (checkButtons(waV[0], waV[1], waV[2], waV[3]) == true) // Ativar ou desativar wavemaker
          {
            if (bitRead(alimentacao_wavemaker_on_off_temp, 1) == 0)
            {
              bitWrite(alimentacao_wavemaker_on_off_temp, 1, 1);
              alimentadorScreen_2();
            }
            else
            {
              bitWrite(alimentacao_wavemaker_on_off_temp, 1, 0);
              alimentadorScreen_2();
            }
          }
          else if (checkButtons(prOK[0], prOK[1], prOK[2], prOK[3]) == true)
          {
            if ((horario_alimentacao[2] == horario_alimentacao[0])
                && (horario_alimentacao[3] < (horario_alimentacao[1] + 10)))
            {
              alimentacao_erro = true;

              myGLCD.setColor(255, 255, 0);
              myGLCD.fillRoundRect(15, 90, 319, 155);

              myGLCD.setColor(255, 0, 0);
              myGLCD.drawRoundRect(15, 90, 319, 155);

              setFont(SMALL, 255, 0, 0, 255, 255, 0);

              strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[176])));
              myGLCD.print(buffer, 20, 110); // "O INTERVALO ENTRE A INICIAL E A FINAL"

              strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[177])));
              myGLCD.print(buffer, 35, 130); // "DEVE SER DE NO MINIMO 10 MINUTOS!"
            }
            else if (horario_alimentacao[2] < horario_alimentacao[0])
            {
              alimentacao_erro = true;

              myGLCD.setColor(255, 255, 0);
              myGLCD.fillRoundRect(15, 90, 319, 155);

              myGLCD.setColor(255, 0, 0);
              myGLCD.drawRoundRect(15, 90, 319, 155);

              setFont(SMALL, 255, 0, 0, 255, 255, 0);

              strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[178])));
              myGLCD.print(buffer, 50, 110);// "A HORA FINAL NAO PODE SER MENOR"

              strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[179])));
              myGLCD.print(buffer, 100, 130); // "QUE A INICIAL!"
            }
            else if (((horario_alimentacao[2] == horario_alimentacao[0])
                      && (horario_alimentacao[3] >= (horario_alimentacao[1] + 10)))
                     || (horario_alimentacao[2] > horario_alimentacao[0]))
            {
              config_valores_salvar_dosadoras();
              dispScreen = 37;
              clearScreen();
              menuScreen_2();
              config_salvar_valores_alimentador();
              salvar_alimentador_EEPROM();
              criar_arquivos_alimentador();
            }
          }
        }
        break;
    }
  }
}
#endif
