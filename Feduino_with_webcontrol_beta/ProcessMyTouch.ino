//-------------------------------------------Touch screen----------------------------
void processMyTouch()
{
  myTouch.read();
  int x, y;                  // Coordenadas do touch screen
  x=myTouch.getX();
  y=myTouch.getY();

  if(temperatura_alta == false) // Limpa mensagem de que a temperatura dos leds esteve alta.
  {
    temperatura_baixou = false;
  }
  if ((x>=iniC[0]) && (x<=iniC[2]) && (y>=iniC[1]) && (y<=iniC[3]) && (dispScreen!=0) && (LEDtestTick == false) && (horario_alterado == false))  // volta ao inicio
  {
    //waitForIt(iniC[0], iniC[1], iniC[2], iniC[3]);
    if((dispScreen == 5) || (dispScreen == 28)) 
    {
      ReadFromEEPROM();
    }
    else if(dispScreen == 10)
    {
      ler_wave_EEPROM();
    }
    else if(dispScreen == 30)
    {
      stCurrentLen=0;
      memcpy(stCurrent, limpar_senha, sizeof(limpar_senha));
    }
    else if(dispScreen == 22)
    {
      ler_predefinido_EEPROM(); 
    }
    periodo_selecionado = false;
    dispScreen=0;
    clearScreen();
    mainScreen(true);   

  } 
  else
  {
    switch (dispScreen) 
    {
    case 0:                       //Tela de inico
      dispScreen=30;
      clearScreen();
      solicitar_senha();
      break;
    case 1:     //------------------------------------Tela de menu-------------------------------------------------
      if ((x>=tanD[0]) && (x<=tanD[2]))               //first column
      {
        if ((y>=tanD[1]) && (y<=tanD[3]))             //press clock
        {
          //waitForIt(tanD[0], tanD[1], tanD[2], tanD[3]);
          dispScreen=2;
          clearScreen();
          setClock();
        }

        else if ((y>=tesT[1]) && (y<=tesT[3]))              // Menu configurar leds
        {
          //waitForIt(tesT[0], tesT[1], tesT[2], tesT[3]);
          dispScreen=40;
          clearScreen();
          config_leds();
        }  
        else if ((y>=temC[1]) && (y<=temC[3]))               //controle de parametros
        {
          //waitForIt(temC[0], temC[1], temC[2], temC[3]);
          dispScreen=14;
          clearScreen();
          parametroScreen();
        }
        else if ((y>=graF[1]) && (y<=graF[3]))           // seleciona a funcao grafico
        {
          //waitForIt(graF[0], graF[1], graF[2], graF[3]);
          dispScreen=9;
          clearScreen();
          graficoScreen();
        } 
      }
      else if ((x>=ledW[0]) && (x<=ledW[2]))                 //second column
      {
        if  ((y>=ledW[1]) && (y<=ledW[3]))           //Timers
        {
          //waitForIt(ledW[0], ledW[1], ledW[2], ledW[3]);
          dispScreen=38;
          clearScreen();
          TimerScreen();
        } 
        else if  ((y>=tpaA[1]) && (y<=tpaA[3]))           // seleciona a funcao "TPA automatica"
        {
          //waitForIt(tpaA[0], tpaA[1], tpaA[2], tpaA[3]);
          dispScreen=7;
          clearScreen();
          tpaScreen(true);
        }      
        else if  ((y>=dosA[1]) && (y<=dosA[3]))           // seleciona a funcao "Bomba dosadora"
        {
          //waitForIt(dosA[0], dosA[1], dosA[2], dosA[3]);
          dispScreen=8;
          clearScreen();
          menu_dosadoras();
        } 
        else if ((y>=wavM[1]) && (y<=wavM[3]))           // seleciona a funcao "wavemaker"
        {
          //waitForIt(wavM[0], wavM[1], wavM[2], wavM[3]);
          dispScreen=10;
          clearScreen();
          waveScreen(true);
        } 
      }
      else  if ((y>=menU[1]) && (y<=menU[3]) && (x>=menU[0]) && (x<=menU[2]))
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]); // Vai para o menu 2
        dispScreen=37;
        clearScreen();
        menuScreen_2();
      }
      break;

    case 2:    // -------------------------------------Tela configuracao data e hora---------------------

      if ((y>=houU[1]) && (y<=houU[3])) // Buttons: Time UP
      {
        if((x>=houU[0]) && (x<=houU[2]))
        {
          //waitForIt(houU[0], houU[1], houU[2], houU[3]);

          t_temp.hour = (t_temp.hour+1) %24;
          if (t_temp.hour<10)
          {
            myGLCD.printNumI(0, 70, 48);
            myGLCD.printNumI(t_temp.hour, 86, 48);
          }
          else
          {
            myGLCD.printNumI(t_temp.hour, 70, 48);
          }   
        }
        else if ((x>=minU[0]) && (x<=minU[2]))
        {
          //waitForIt(minU[0], minU[1], minU[2], minU[3]);
          t_temp.min = (t_temp.min +1) %60;
          if (t_temp.min<10)
          {
            myGLCD.printNumI(0, 160, 48);
            myGLCD.printNumI(t_temp.min, 176, 48);
          }
          else
          {
            myGLCD.printNumI(t_temp.min, 160, 48);
          }   
        }
        else if ((x>=segC[0]) && (x<=segC[2]))
        {
          //waitForIt(segC[0], segC[1], segC[2], segC[3]);
          t_temp.sec = (t_temp.sec +1) %60;
          if (t_temp.sec==60)
            t_temp.sec=0;
          if (t_temp.sec<10)
          {
            myGLCD.printNumI(0, 250, 48);
            myGLCD.printNumI(t_temp.sec, 266, 48);
          }
          else
          {
            myGLCD.printNumI(t_temp.sec, 250, 48);
          }     
        }
      }
      else if ((y>=houD[1]) && (y<=houD[3])) // Buttons: Time DOWN
      {
        if ((x>=houD[0]) && (x<=houD[2]))
        {
          //waitForIt(houD[0], houD[1], houD[2], houD[3]);
          t_temp.hour =(t_temp.hour + 23)% 24;
          if (t_temp.hour<10)
          {
            myGLCD.printNumI(0, 70, 48);
            myGLCD.printNumI(t_temp.hour, 86, 48);
          }
          else
          {
            myGLCD.printNumI(t_temp.hour, 70, 48);
          }            
        }
        else if ((x>=minD[0]) && (x<=minD[2]))
        {
          //waitForIt(minD[0], minD[1], minD[2], minD[3]);
          t_temp.min =(t_temp.min +59) %60;
          if (t_temp.min<10)
          {
            myGLCD.printNumI(0, 160, 48);
            myGLCD.printNumI(t_temp.min, 176, 48);
          }
          else
          {
            myGLCD.printNumI(t_temp.min, 160, 48);
          } 
        }
        else if ((x>=segB[0]) && (x<=segB[2]))
        {
          //waitForIt(segB[0], segB[1], segB[2], segB[3]); 
          t_temp.sec = (t_temp.sec +59) %60;
          if (t_temp.sec<10)
          {
            myGLCD.printNumI(0, 250, 48);
            myGLCD.printNumI(t_temp.sec, 266, 48);
          }
          else
          {
            myGLCD.printNumI(t_temp.sec, 250, 48);
          }
        }
      }

      if ((y>=dayU[1]) && (y<=dayU[3])) // Buttons: Date UP
      {
        if ((x>=dayU[0]) && (x<=dayU[2]))
        {
          //waitForIt(dayU[0], dayU[1], dayU[2], dayU[3]);
          t_temp.date+=1;
          t_temp.date=validateDate(t_temp.date, t_temp.mon, t_temp.year);
          if (t_temp.date<10)
          {
            myGLCD.printNumI(0, 70, 132);
            myGLCD.printNumI(t_temp.date, 86, 132);
          }
          else
          {
            myGLCD.printNumI(t_temp.date, 70, 132);
          }
        }
        else if ((x>=monU[0]) && (x<=monU[2]))
        {
          //waitForIt(monU[0], monU[1], monU[2], monU[3]);
          t_temp.mon =(t_temp.mon + 1) %13;
          if (t_temp.mon ==0)
          {
            t_temp.mon = 1;
          }
          if (t_temp.mon<10)
          {
            myGLCD.printNumI(0, 160, 132);
            myGLCD.printNumI(t_temp.mon, 176, 132);
          }
          else
          {
            myGLCD.printNumI(t_temp.mon, 160, 132);
          }

          t_temp.date=validateDateForMonth(t_temp.date, t_temp.mon, t_temp.year);
        }
        else if ((x>=yeaU[0]) && (x<=yeaU[2]))   
        {
          //waitForIt(yeaU[0], yeaU[1], yeaU[2], yeaU[3]);
          t_temp.year+=1;
          if (t_temp.year==2100)
            t_temp.year=2000;
          myGLCD.printNumI(t_temp.year, 230, 132);

          t_temp.date=validateDateForMonth(t_temp.date, t_temp.mon, t_temp.year);
        }
        t_temp.dow=calcDOW(t_temp.date, t_temp.mon, t_temp.year);
      }
      else if ((y>=dayD[1]) && (y<=dayD[3]))  // Buttons: Date DOWN
      {
        if ((x>=dayD[0]) && (x<=dayD[2]))
        {
          //waitForIt(dayD[0], dayD[1], dayD[2], dayD[3]);
          t_temp.date-=1;
          t_temp.date=validateDate(t_temp.date, t_temp.mon, t_temp.year);
          if (t_temp.date<10)
          {
            myGLCD.printNumI(0, 70, 132);
            myGLCD.printNumI(t_temp.date, 86, 132);
          }
          else
          {
            myGLCD.printNumI(t_temp.date, 70, 132);
          }
        }
        else if ((x>=monD[0]) && (x<=monD[2]))   
        {
          //waitForIt(monD[0], monD[1], monD[2], monD[3]);
          t_temp.mon =(t_temp.mon +12) %13;
          if (t_temp.mon ==0)
          {
            t_temp.mon = 12;
          }
          if (t_temp.mon<10)
          {
            myGLCD.printNumI(0, 160, 132);
            myGLCD.printNumI(t_temp.mon, 176, 132);
          }
          else
          {
            myGLCD.printNumI(t_temp.mon, 160, 132);
          }
          t_temp.date=validateDateForMonth(t_temp.date, t_temp.mon, t_temp.year);
        }

        else if ((x>=yeaD[0]) && (x<=yeaD[2]))
        {
          //waitForIt(yeaD[0], yeaD[1], yeaD[2], yeaD[3]);
          t_temp.year = (t_temp.year +2099) %2100;

          myGLCD.printNumI(t_temp.year, 230, 132);
          t_temp.date=validateDateForMonth(t_temp.date, t_temp.mon, t_temp.year);        
        }
        t_temp.dow=calcDOW(t_temp.date, t_temp.mon, t_temp.year);
      }
      else if ((y>=prOK[1]) && (y<=prOK[3]) && (x>=prOK[0]) && (x<=prOK[2]))
      {
        //waitForIt(prOK[0], prOK[1], prOK[2], prOK[3]); //funcao salvar
        rtc.halt(true);
        rtc.setTime(t_temp.hour, t_temp.min, t_temp.sec); 
        rtc.setDate(t_temp.date, t_temp.mon, t_temp.year);
        rtc.setDOW(t_temp.dow);
        rtc.halt(false);
        dispScreen=1;
        clearScreen();
        menuScreen();
      }
      else if ((y>=iniC[1]) && (y<=iniC[3]) && (x>=iniC[0]) && (x<=iniC[2]))
      {
        //waitForIt(iniC[0], iniC[1], iniC[2], iniC[3]); //volta ao inicio
        dispScreen=0;
        clearScreen();
        mainScreen(true);
      }
      else if ((y>=menU[1]) && (y<=menU[3]) && (x>=menU[0]) && (x<=menU[2]))
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]); //volta ao menu
        dispScreen=1;
        clearScreen();
        menuScreen();
      }     
      break;
    case 3:                    // -------------------Tela testar led------------------------------------------
      if ((x>=stsT[0]) && (x<=stsT[2]) && (y>=stsT[1]) && (y<=stsT[3]))     //press start/stop test
      {
        //waitForIt(stsT[0], stsT[1], stsT[2], stsT[3]); 

        if (LEDtestTick == true) 
        {
          teste_em_andamento = false;
          LEDtestTick = false;
          testScreen(true);
        }
        else {
          teste_iniciado = true;
          LEDtestTick = true; 
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect (319, 1, 399, 239);   //Limpar botões iniciar e menu.       
          testScreen();
          teste_iniciado = false; 
        }
      } 
      else
      {
        if ((x>=tenM[0]) && (x<=tenM[2]) && (y>=tenM[1]) && (y<=tenM[3]))      //press -10s
        {
          //waitForIt(tenM[0], tenM[1], tenM[2], tenM[3]);
          min_cnt -= 10;
          if (min_cnt <= 0)
          {
            min_cnt= 0; 
          }

        }
        else if ((x>=tenP[0]) && (x<=tenP[2]) && (y>=tenP[1]) && (y<=tenP[2]))    //press +10s
        {
          //waitForIt(tenP[0], tenP[1], tenP[2], tenP[3]);
          min_cnt += 10;
          if (min_cnt > 1440) 
          {
            min_cnt = 1440; 
          }
        }
        else if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]) && (LEDtestTick == false))           // volta ao menu
        {
          //waitForIt(menU[0], menU[1], menU[2], menU[3]);
          dispScreen=1;
          clearScreen();
          menuScreen(); 
        }
        else if ((x>=volT[0]) && (x<=volT[2]) && (y>=volT[1]) && (y<=volT[3])&& (LEDtestTick == false))           // volta a tela configurar leds
        {
          //waitForIt(volT[0], volT[1], volT[2], volT[3]);
          dispScreen=25;
          clearScreen();
          escolher_teste(); 
        }
      }    
      break;
    case 4:             //---------------------------------------Tela controle de temperatura----------------------------------
      if ((x>=prOK[0]) && (x<=prOK[2]) && (y>=prOK[1]) && (y<=prOK[3]))       //Funcao salvar
      {
        //waitForIt(prOK[0], prOK[1], prOK[2], prOK[3]);
        setTempC = temp2beS;
        offTempC = temp2beO;
        alarmTempC = temp2beA;
        dispScreen=14;
        SaveTempToEEPROM();
        clearScreen();
        parametroScreen();
      } 
      else if ((x>=temM[0]) && (x<=temM[2]))                         // Primeira coluna
      {
        if ((y>=temM[1]) && (y<=temM[3]))                      //press temp minus
        {
          //waitForIt(temM[0], temM[1], temM[2], temM[3]);
          temp2beS -= 0.1;
          if (temp2beS < 10)
          {
            temp2beS = 10; 
          }
          tempScreen();
        }
        else if ((y>=offM[1]) && (y<=offM[3]))                       //press offset minus
        {
          //waitForIt(offM[0], offM[1], offM[2], offM[3]);
          temp2beO -= 0.1;
          if (temp2beO <= 0.0) 
          {
            temp2beO = 0.0; 
          }
          tempScreen();
        }          
        else if ((y>=almM[1]) && (y<=almM[3]))                        //press alarm minus
        {
          //waitForIt(almM[0], almM[1], almM[2], almM[3]);
          temp2beA -= 0.1;
          if (temp2beA <= 0.0) 
          {
            temp2beA = 0.0;  
          }
          tempScreen();
        }
      }
      else if ((x>=temP[0]) && (x<=temP[2]))                             //Segunda coluna
      {
        if ((y>=temP[1]) && (y<=temP[3]))                      //press temp plus
        {
          //waitForIt(temP[0], temP[1], temP[2], temP[3]);
          temp2beS += 0.1;
          if (temp2beS >= 40) {
            temp2beS = 40; 
          }
          tempScreen();
        }
        else if ((y>=offP[1]) && (y<=offP[3]))                           //press offset plus
        {
          //waitForIt(offP[0], offP[1], offP[2], offP[3]);
          temp2beO += 0.1;
          if (temp2beO >= 10) {
            temp2beO = 9.9; 
          }
          tempScreen();
        }
        else if ((y>=almP[1]) && (y<=almP[3]))                           //press alarm plus
        {
          //waitForIt(almP[0], almP[1], almP[2], almP[3]);
          temp2beA += 0.1;
          if (temp2beA >= 10) {
            temp2beA = 9.9;  
          }
          tempScreen();
        }
      }
      else if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen=14;
        clearScreen();
        parametroScreen();
      } 
      break;
    case 5:         // -------------------------------- Tela alterar valores led ------------------------------------------------------------
      if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen=1;
        clearScreen();
        menuScreen();
        ReadFromEEPROM();
      }
      else if ((x>=leWB[0]) && (x<=leWB[2]) && (y>=leWB[1]) && (y<=leWB[3]))       // Mais cores
      {
        //waitForIt(leWB[0], leWB[1], leWB[2], leWB[3]);
        dispScreen=28;
        clearScreen();
        escolher_canal();
      } 
      else if ((x>=leST[0]) && (x<=leST[2]) && (y>=leST[1]) && (y<=leST[3]))       // Alterar valores dos leds
      {
        //waitForIt(leST[0], leST[1], leST[2], leST[3]);
        dispScreen=6;
        clearScreen();
        ledChangeScreen(true);
      }
      else if ((x>=savE[0]) && (x<=savE[2]) && (y>=savE[1]) && (y<=savE[3]))      // Salva os valores na EEPROM
      {
        //waitForIt(savE[0], savE[1], savE[2], savE[3]);
        SaveLEDToEEPROM();
        dispScreen=28;
        clearScreen();
        escolher_canal();
      }
      break;
    case 6:             //---------------------------------- Tela alterar potencia dos leds ---------------------
      if ((x>=salV[0]) && (x<=salV[2]) && (y>=salV[1]) && (y<=salV[3]))       // Salvar tabela temporária
      {
        //waitForIt(salV[0], salV[1], salV[2], salV[3]);
        dispScreen=5;
        clearScreen();
        ledSetScreen();
        periodo_selecionado = false;
      }
      else if ((y>=15) && (y<=40))                                    // Seleção de período
      {
        if ((x>=4) && (x<=316))
        {
          periodo_selecionado = true;
          int oldLCT = LedChangTime;
          LedChangTime = map(x, 3, 320, 0, 12);                

          if (oldLCT != LedChangTime)                        // Realçar período tocado
          {
            if(mensagem == true)
            {
              ledChangeScreen();
            }
            myGLCD.setColor(0, 0, 0);
            myGLCD.fillRect((oldLCT*26)+5, 21, (oldLCT*26)+29, 45);

            setFont(SMALL, 0, 255, 255, 0, 0, 0);

            if(oldLCT == 11)
            {
              myGLCD.printNumI((oldLCT*2), (oldLCT*26)+10, 22);
              myGLCD.print("0", (oldLCT*26)+14, 33);            
            }
            else
            {
              myGLCD.printNumI((oldLCT*2), (oldLCT*26)+10, 22);
              myGLCD.printNumI(((oldLCT*2)+2), (oldLCT*26)+10, 33);
            }
            myGLCD.setColor(255, 0, 0);
            myGLCD.fillRect((LedChangTime*26)+5, 21, (LedChangTime*26)+29, 45);

            setFont(SMALL, 255, 255, 255, 255, 0, 0);

            if(LedChangTime == 11)
            {
              myGLCD.printNumI((LedChangTime*2), (LedChangTime*26)+10, 22);
              myGLCD.print("0", (LedChangTime*26)+14, 33);
            }
            else
            {
              myGLCD.printNumI((LedChangTime*2), (LedChangTime*26)+10, 22);
              myGLCD.printNumI(((LedChangTime*2)+2), (LedChangTime*26)+10, 33);              
            }
            myGLCD.setColor(100, 100, 100);
            myGLCD.drawLine(4, 45, 316,45);

            for (int i = 0; i < 8; i++)                          // Imprime valores do período.
            {
              int k=(LedChangTime * 8) + i;
              myGLCD.setColor(0,0,0);
              myGLCD.fillRect((i * 38) + 12, 200, (i * 38) + 36, 210); 
              setFont(SMALL, 255, 255, 255, 0, 0, 0);
              myGLCD.printNumI( cor[cor_selecionada][k], (i * 38) + 12, 200);
              y_tocado = map(cor[cor_selecionada][k], 255, 0, 80, 195);
              setor_selecionado = i;
              desenhar_barras_periodo ();
            }
          }
        }
      }
      else if((y >= 80) && (y <= 195))
      {
        for (int i = 0; i < 8; i++) {                
          if ((x >= (i * 38) + 5) && (x <= (i * 38) + 39)) 
          {
            int k= (LedChangTime * 8) + i;
            y_tocado = y;
            cor[cor_selecionada][k] = map(y_tocado, 195, 80, 0, 255);
            myGLCD.setColor(0,0,0);
            myGLCD.fillRect((i * 38) + 12, 200, (i * 38) + 36, 210);
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
            //waitForIt((i*38)+5, 50, (i*38)+39, 75); 
            int k= (LedChangTime * 8) + i;
            cor[cor_selecionada][k] += 1;
            delay(50);
            myGLCD.setColor(0,0,0);
            myGLCD.fillRect((i * 38) + 12, 200, (i * 38) + 36, 210);
            setFont(SMALL, 255, 255, 255, 0, 0, 0);
            myGLCD.printNumI( cor[cor_selecionada][k], (i * 38) + 12, 200);
            y_tocado = map(cor[cor_selecionada][k], 255, 0, 80, 195);
            setor_selecionado = i;
            desenhar_barras_periodo ();
          }
        }
      }
      else if ((y>=214) && (y<=239)  && (periodo_selecionado == true))     // Botão -
      {
        for (int i = 0; i < 8; i++) 
        {                
          if ((x >= (i * 38) + 5) && (x <= (i * 38) + 39)) 
          {
            //waitForIt((i*38)+5, 214, (i*38)+39, 239);
            int k= (LedChangTime * 8) + i;
            cor[cor_selecionada][k] -= 1;
            delay(50);
            myGLCD.setColor(0,0,0);
            myGLCD.fillRect((i * 38) + 12, 200, (i * 38) + 36, 210);
            setFont(SMALL, 255, 255, 255, 0, 0, 0);
            myGLCD.printNumI( cor[cor_selecionada][k], (i * 38) + 12, 200);
            y_tocado = map(cor[cor_selecionada][k], 255, 0, 80, 195);
            setor_selecionado = i;
            desenhar_barras_periodo ();
          }
        }  
      }
      else if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           // Volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen=1;
        clearScreen();
        menuScreen();
        ReadFromEEPROM();
        periodo_selecionado = false; 
      }
      else if ((x>=volT[0]) && (x<=volT[2]) && (y>=volT[1]) && (y<=volT[3]))           // volta a tela configurar leds
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen=5;
        clearScreen();
        ledSetScreen();
        ReadFromEEPROM();
        periodo_selecionado = false;
      } 
      break;
    case 7: //--------------------------------------------- configurar tpa autom.-----------------------------------
      if ((y >= houU[1]) && (y <= houU[3])) // Buttons: Time UP
      {
        if ((x >= houU[0]) && (x <= houU[2])) 
        {
          //waitForIt(houU[0], houU[1], houU[2], houU[3]);
          temp2hora = (temp2hora + 1) % 24;
          tpaScreen();
        } 
        else if ((x >= minUT[0]) && (x <= minUT[2]))
        {
          //waitForIt(minUT[0], minUT[1], minUT[2], minUT[3]);
          temp2minuto = (temp2minuto + 1) % 60;
          tpaScreen();
        } 
        else if ((x >= durC[0]) && (x <= durC[2]))
        {
          //waitForIt(durC[0], durC[1], durC[2], durC[3]); 
          temp2duracaomaximatpa = (temp2duracaomaximatpa + 1) % 60;
          tpaScreen();
        }
      } 
      else if ((y >= houD[1]) && (y <= houD[3])) // Buttons: Time DOWN
      {
        if ((x >= houD[0]) && (x <= houD[2])) 
        {
          //waitForIt(houD[0], houD[1], houD[2], houD[3]);
          temp2hora = (temp2hora + 23) % 24;
          tpaScreen();
        } 
        else if ((x >= minDT[0]) && (x <= minDT[2])) 
        {
          //waitForIt(minDT[0], minDT[1], minDT[2], minDT[3]);
          temp2minuto = (temp2minuto + 59) % 60;
          tpaScreen();
        } 
        else if ((x >= durB[0]) && (x <= durB[2])) 
        {
          //waitForIt(durB[0], durB[1], durB[2], durB[3]);
          temp2duracaomaximatpa = (temp2duracaomaximatpa + 59) % 60;
          tpaScreen();          
        }
      }
      else if ((y >= prOK[1]) && (y <= prOK[3]) && (x >= prOK[0]) && (x <= prOK[2]))
      {
        //waitForIt(prOK[0], prOK[1], prOK[2], prOK[3]); //funcao salvar
        hora = temp2hora;
        minuto = temp2minuto;
        duracaomaximatpa = temp2duracaomaximatpa;
        segunda = temp2segunda;
        terca = temp2terca;
        quarta = temp2quarta;
        quinta = temp2quinta;
        sexta = temp2sexta;
        sabado = temp2sabado;
        domingo =temp2domingo;
        SalvartpaEEPROM();
        dispScreen = 1;
        clearScreen();
        menuScreen();
      }
      else if ((y >= menU[1]) && (y <= menU[3]) && (x >= menU[0]) && (x <= menU[2])) 
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]); //volta ao menu
        dispScreen = 1;
        clearScreen();
        menuScreen();
      }
      else if ((x >= segU[0]) && (x <= segU[2]) && (y >= segU[1]) && (y <= segU[3])) 
      {
        if (temp2segunda == 1) 
        {
          temp2segunda = 0;
          tpaScreen();
        } 
        else 
        {
          temp2segunda = 1;
          tpaScreen();
        }
      }
      else if ((x >= terC[0]) && (x <= terC[2]) && (y >= terC[1]) && (y <= terC[3])) 
      {
        if (temp2terca == 2) 
        {
          temp2terca = 0;
          tpaScreen();
        } 
        else {
          temp2terca = 2;
          tpaScreen();
        }
      }
      else if ((x >= quaR[0]) && (x <= quaR[2]) && (y >= quaR[1]) && (y <= quaR[3])) 
      {
        if (temp2quarta == 3) 
        {
          temp2quarta = 0;
          tpaScreen();
        } 
        else 
        {
          temp2quarta = 3;
          tpaScreen();
        }
      }
      else if ((x >= quiN[0]) && (x <= quiN[2]) && (y >= quiN[1]) && (y <= quiN[3])) 
      {

        if (temp2quinta == 4) 
        {
          temp2quinta = 0;
          tpaScreen();
        } 
        else 
        {
          temp2quinta = 4;
          tpaScreen();
        }
      }
      else if ((x >= sexT[0]) && (x <= sexT[2]) && (y >= sexT[1]) && (y <= sexT[3]))
      {
        if (temp2sexta == 5) 
        {
          temp2sexta = 0;
          tpaScreen();
        } 
        else 
        {
          temp2sexta = 5;
          tpaScreen();
        }
      }
      else if ((x >= sabA[0]) && (x <= sabA[2]) && (y >= sabA[1]) && (y <= sabA[3])) 
      {
        if (temp2sabado == 6) 
        {
          temp2sabado = 0;
          tpaScreen();
        } 
        else {
          temp2sabado = 6;
          tpaScreen();
        }
      }
      else if ((x >= domI[0]) && (x <= domI[2]) && (y >= domI[1]) && (y <= domI[3])) 
      {
        if (temp2domingo == 7) 
        {
          temp2domingo = 0;
          tpaScreen();
        } 
        else {
          temp2domingo = 7;
          tpaScreen();
        }
      }
      else if ((x >= proX[0]) && (x <= proX[2]) && (y >= proX[1]) && (y <= proX[3])) 
      {
        if (bitRead(tpa_status,2) == true)
        {
          tpa_status = 0x0;
          tpaScreen();
        }
        else
        {
          bitWrite(tpa_status,2,1);
          tpaScreen();
        }
      }

      break;
    case 8: //--------------------------------------------- Escolher dosadora -----------------------------------
      if ((x>=manU[0]) && (x<=manU[2]) && (y>=manU[1]) && (y<=manU[3]))
      {
        //waitForIt(manU[0], manU[1], manU[2], manU[3]);
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
      else if ((x>=perS[0]) && (x<=perS[2]) && (y>=perS[1]) && (y<=perS[3]))
      {
        //waitForIt(perS[0], perS[1], perS[2], perS[3]);
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
      else if ((x>=orP[0]) && (x<=orP[2]) && (y>=orP[1]) && (y<=orP[3]))
      {
        //waitForIt(orP[0], orP[1], orP[2], orP[3]);
        modo_manual = false;
        modo_personalizado = false;
        modo_calibrar = true;
        dispScreen=21;
        clearScreen();
        selecionar_dosadora();
        setFont(SMALL, 255, 255, 255, 0, 0, 0);

        strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[172])));
        myGLCD.print(buffer, 15, 220);      
      }    
      else if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           /// volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen=1;
        clearScreen();
        menuScreen();
        modo_manual = false;
        modo_personalizado = false;
        modo_calibrar = false; 
      }          
      else if ((x>=reV[0]) && (x<=reV[2]) && (y>=reV[1]) && (y<=reV[3]))           /// Rever config
      {
        //waitForIt(reV[0], reV[1], reV[2], reV[3]);
        dispScreen=32;
        clearScreen();
        rever_configuracao_dosadoras();
      }
      else if ((x>=atiV[0]) && (x<=atiV[2]) && (y>=atiV[1]) && (y<=atiV[3]))
      {
        //waitForIt(atiV[0], atiV[1], atiV[2], atiV[3]);
        dispScreen = 35;
        clearScreen();
        desativar_dosadoras(true);
      }
      break;

    case 9: //  -----------------------------------------Tela escolher graficos-----------------------------------------
      if ((x >= orP[0]) && (x <= orP[2]) && (y >= orP[1]) && (y <= orP[3]))           
      {
        //waitForIt(orP[0], orP[1], orP[2], orP[3]);
        dispScreen=12;
        clearScreen();
        orpScreen(); 
      } 
      else if ((x >= phR[0]) && (x <= phR[2]) && (y >= phR[1]) && (y <= phR[3]))           
      {
        //waitForIt(phR[0], phR[1], phR[2], phR[3]);
        dispScreen=13;
        clearScreen();
        PHRScreen(); 
      } 
      else if ((x >= tempG[0]) && (x <= tempG[2]) && (y >= tempG[1]) && (y <= tempG[3]))           
      {
        //waitForIt(tempG[0], tempG[1], tempG[2], tempG[3]);
        dispScreen=13;
        clearScreen();
        tempgScreen(); 
      }
      else if ((x >= phA[0]) && (x <= phA[2]) && (y >= phA[1]) && (y <= phA[3]))           
      {
        //waitForIt(phA[0], phA[1], phA[2], phA[3]);
        dispScreen=17;
        clearScreen();
        PHAScreen(); 
      } 
      else if ((x >= denS[0]) && (x <= denS[2]) && (y >= denS[1]) && (y <= denS[3]))           
      {
        //waitForIt(denS[0], denS[1], denS[2], denS[3]);
        dispScreen=19;
        clearScreen();
        densidadeScreen(); 
      }       

      else if ((x >= menU[0]) && (x <= menU[2]) && (y >= menU[1]) && (y <= menU[3]))           /// volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen=1;
        clearScreen();
        menuScreen(); 
      }          
      break;

    case 10: //--------------------------------- Tela wavemaker ----------------------------
      if ((x >= menU[0]) && (x <= menU[2]) && (y >= menU[1]) && (y <= menU[3]))           // volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        ler_wave_EEPROM();
        dispScreen = 1;
        clearScreen();
        menuScreen(); 
      }
      else if ((x>=prOK[0]) && (x<=prOK[2]) && (y>=prOK[1]) && (y<=prOK[3]))       //Funcao salvar
      {
        //waitForIt(prOK[0], prOK[1], prOK[2], prOK[3]);
        Salvar_wave_EEPROM(); 
        dispScreen = 1;
        clearScreen();
        menuScreen();
      }
      else if ((x>=boT1[0]) && (x<=boT1[2]) && (y>=boT1[1]) && (y<=boT1[3]))  // Botao: 1
      {
        //waitForIt(boT1[0], boT1[1], boT1[2] ,boT1[3]);
        modo_selecionado = 1;
        waveScreen(true);
      }
      else if ((x>=boT2[0]) && (x<=boT2[2]) && (y>=boT2[1]) && (y<=boT2[3]))  // Botao: 2
      {
        //waitForIt(boT2[0], boT2[1], boT2[2], boT2[3]);
        modo_selecionado = 2;
        waveScreen(true);
      }
      else if ((x>=boT3[0]) && (x<=boT3[2]) && (y>=boT3[1]) && (y<=boT3[3]))  // Botao: 3
      {
        //waitForIt(boT3[0], boT3[1], boT3[2], boT3[3]);
        modo_selecionado = 3;
        waveScreen(true);
      }
      else if ((x>=boT4[0]) && (x<=boT4[2]) && (y>=boT4[1]) && (y<=boT4[3]))  // Botao: 4
      {
        //waitForIt(boT4[0], boT4[1], boT4[2], boT4[3]);
        modo_selecionado = 4;
        waveScreen(true);
      }
      else if ((x>=boT5[0]) && (x<=boT5[2]) && (y>=boT5[1]) && (y<=boT5[3]))  // Botao: M
      {
        //waitForIt(boT5[0], boT5[1], boT5[2], boT5[3]);
        modo_selecionado = 5;
        waveScreen(true);
      }
      if(modo_selecionado == 1)
      {
        if ((x>=peRB[0]) && (x<=peRB[2]) && (y>=peRB[1]) && (y<=peRB[3]))  // Período -
        {
          //waitForIt(peRB[0], peRB[1], peRB[2], peRB[3]);
          periodo -= 100;
          if(periodo < 100)
          {
            periodo = 10000;
          } 
          waveScreen();
        }       
        else if ((x>=peRC[0]) && (x<=peRC[2]) && (y>=peRC[1]) && (y<=peRC[3]))  // Período +
        {
          //waitForIt(peRC[0], peRC[1], peRC[2], peRC[3]);
          periodo += 100;
          if(periodo > 10000)
          {
            periodo = 100;
          }
          waveScreen();
        }
      }
      else if(modo_selecionado == 2)
      {
        if ((x>=peRB[0]) && (x<=peRB[2]) && (y>=peRB[1]) && (y<=peRB[3]))  // Período -
        {
          //waitForIt(peRB[0], peRB[1], peRB[2], peRB[3]);
          periodo -= 100;
          if(periodo < 100)
          {
            periodo = 10000;
          }
          waveScreen();
        }       
        else if ((x>=peRC[0]) && (x<=peRC[2]) && (y>=peRC[1]) && (y<=peRC[3]))  // Período +
        {
          //waitForIt(peRC[0], peRC[1], peRC[2], peRC[3]);
          periodo += 100;
          if(periodo > 10000)
          {
            periodo = 100;
          }
          waveScreen();
        }        
      }
      else if(modo_selecionado == 3)
      {
        if ((x>=peRB[0]) && (x<=peRB[2]) && (y>=peRB[1]) && (y<=peRB[3]))  // Duração do intervalo -
        {
          //waitForIt(peRB[0], peRB[1], peRB[2], peRB[3]);
          duracao -= 500;
          if(duracao < 1000)
          {
            duracao = 9500;
          }
          waveScreen();
        }       
        else if ((x>=peRC[0]) && (x<=peRC[2]) && (y>=peRC[1]) && (y<=peRC[3]))  // Duração intervalo +
        {
          //waitForIt(peRC[0], peRC[1], peRC[2], peRC[3]);
          duracao += 500;
          if(duracao > 9500)
          {
            duracao = 1000;
          }
          waveScreen();
        }        
      }
      else if(modo_selecionado == 4)
      {
        if ((x>=peRB[0]) && (x<=peRB[2]) && (y>=peRB[1]) && (y<=peRB[3]))  // Duração do intervalo -
        {
          //waitForIt(peRB[0], peRB[1], peRB[2], peRB[3]);
          duracao -= 1000;
          if(duracao < 1000)
          {
            duracao = 5000;
          }
          waveScreen();
        }       
        else if ((x>=peRC[0]) && (x<=peRC[2]) && (y>=peRC[1]) && (y<=peRC[3]))  // intervalo +
        {
          //waitForIt(peRC[0], peRC[1], peRC[2], peRC[3]);
          duracao += 1000;
          if(duracao > 5000)
          {
            duracao = 1000;
          }
          waveScreen();
        }        
      }
      else if(modo_selecionado == 5)
      {
        if ((x>=PoTEB1[0]) && (x<=PoTEB1[2]) && (y>=PoTEB1[1]) && (y<=PoTEB1[3]))  // Potência bomba 1 -
        {
          //waitForIt(PoTEB1[0], PoTEB1[1], PoTEB1[2], PoTEB1[3]);
          Pump1PWM_temp -= 1;
          waveScreen();
        }       
        else if ((x>=PoTEC1[0]) && (x<=PoTEC1[2]) && (y>=PoTEC1[1]) && (y<=PoTEC1[3]))  // Potência bomba 1 +
        {
          //waitForIt(PoTEC1[0], PoTEC1[1], PoTEC1[2], PoTEC1[3]);
          Pump1PWM_temp += 1;
          waveScreen();
        }        
        else if ((x>=PoTEB2[0]) && (x<=PoTEB2[2]) && (y>=PoTEB2[1]) && (y<=PoTEB2[3]))  // Potência bomba 1 -
        {
          //waitForIt(PoTEB2[0], PoTEB2[1], PoTEB2[2], PoTEB2[3]);
          Pump2PWM_temp -= 1;
          waveScreen();
        }       
        else if ((x>=PoTEC2[0]) && (x<=PoTEC2[2]) && (y>=PoTEC2[1]) && (y<=PoTEC2[3]))  // Potência bomba 1 +
        {
          //waitForIt(PoTEC2[0], PoTEC2[1], PoTEC2[2], PoTEC2[3]);
          Pump2PWM_temp += 1;
          waveScreen();
        }
      }
      break;

    case 11:  //----------------------------- Tela grafico de temperatura ------------------------------
      if ((x >= menU[0]) && (x <= menU[2]) && (y >= menU[1]) && (y <= menU[3]))           /// volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen=1;
        clearScreen();
        menuScreen(); 
      }
      else if ((x >= volT[0]) && (x <= volT[2]) && (y >= volT[1]) && (y <= volT[3]))           // volta a tela de graficos
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen=9;
        clearScreen();
        graficoScreen(); 
      }           
      break;

    case 12:  //--------------------------- Tela grafico de orp---------------------------------------
      if ((x >= menU[0]) && (x <= menU[2]) && (y >= menU[1]) && (y <= menU[3]))           /// volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen=1;
        clearScreen();
        menuScreen(); 
      }
      else if ((x >= volT[0]) && (x <= volT[2]) && (y >= volT[1]) && (y <= volT[3]))           // volta a tela de graficos
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen=9;
        clearScreen();
        graficoScreen(); 
      }  
      break;           

    case 13:   //-----------------Tela grafico de ph do aquario----------------------------------
      if ((x >= menU[0]) && (x <= menU[2]) && (y >= menU[1]) && (y <= menU[3]))           // volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen=1;
        clearScreen();
        menuScreen(); 
      }
      else if ((x >= volT[0]) && (x <= volT[2]) && (y >= volT[1]) && (y <= volT[3]))         // volta a tela de graficos
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen=9;
        clearScreen();
        graficoScreen(); 
      } 
      break; 

    case 14:  //--------------------------------Tela escolher parametro para configurar-----------------------------------
      if ((x >= orP[0]) && (x <= orP[2]) && (y >= orP[1]) && (y <= orP[3]))           
      {
        //waitForIt(orP[0], orP[1], orP[2], orP[3]);
        dispScreen=16;
        clearScreen();
        config_orp_Screen(true); 
      } 
      else if ((x >= phR[0]) && (x <= phR[2]) && (y >= phR[1]) && (y <= phR[3]))           
      {
        //waitForIt(phR[0], phR[1], phR[2], phR[3]);
        dispScreen=15;
        clearScreen();
        config_phR_Screen(true); 
      }
      else if ((x >= phA[0]) && (x <= phA[2]) && (y>=phA[1]) && (y<=phA[3]))           
      {
        //waitForIt(phA[0], phA[1], phA[2], phA[3]);
        dispScreen=18;
        clearScreen();
        config_phA_Screen(true); 
      } 
      else if ((x >= tempG[0]) && (x <= tempG[2]) && (y >= tempG[1]) && (y <= tempG[3]))           
      {
        //waitForIt(tempG[0], tempG[1], tempG[2], tempG[3]);
        dispScreen=4;
        clearScreen();
        tempScreen(true); 
      }
      if ((x >= caliB[0]) && (x <= caliB[2]) && (y >= caliB[1]) && (y <= caliB[3]))           
      {
        //waitForIt(caliB[0], caliB[1], caliB[2], caliB[3]);
        dispScreen=0;
        clearScreen();
        mainScreen(true); 
      }
      else if ((x >= denS[0]) && (x <= denS[2]) && (y >= denS[1]) && (y <= denS[3]))           
      {
        //waitForIt(denS[0], denS[1], denS[2], denS[3]);
        dispScreen=20;
        clearScreen();
        config_dens_Screen(true); 
      }  
      else if ((x >= menU[0]) && (x <= menU[2]) && (y >= menU[1]) && (y <= menU[3]))           /// volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen=1;
        clearScreen();
        menuScreen(); 
      }          
      break;
    case 15:             //---------------------------------------Tela controle de PH do reator--------
      if ((x>=prOK[0]) && (x<=prOK[2]) && (y>=prOK[1]) && (y<=prOK[3]))       //Funcao salvar
      {
        //waitForIt(prOK[0], prOK[1], prOK[2], prOK[3]);
        setPHR = PHR2beS;
        offPHR = PHR2beO;
        alarmPHR = PHR2beA;
        dispScreen=14;
        SavePHRToEEPROM();
        clearScreen();
        parametroScreen();
      } 
      else
      {
        if ((x>=temM[0]) && (x<=temM[2]))                         // Primeira coluna
        {
          if ((y>=temM[1]) && (y<=temM[3]))                      //press ph minus
          {
            //waitForIt(temM[0], temM[1], temM[2], temM[3]);
            PHR2beS -= 0.1;
            if(PHR2beS < 0.1)
            {
              PHR2beS = 0.1;
            }         
            config_phR_Screen();
          }
          if ((y>=offM[1]) && (y<=offM[3]))                       //press offset minus
          {
            //waitForIt(offM[0], offM[1], offM[2], offM[3]);
            PHR2beO -= 0.1;
            if (PHR2beO <= 0.1) {
              PHR2beO = 0.0; 
            }
            config_phR_Screen();
          }          
          if ((y>=almM[1]) && (y<=almM[3]))                        //press alarm minus
          {
            //waitForIt(almM[0], almM[1], almM[2], almM[3]);
            PHR2beA -= 0.1;
            if (PHR2beA < 0.1) {
              PHR2beA = 0.0;  
            }
            config_phR_Screen();
          }
        }
        else if ((x>=temP[0]) && (x<=temP[2]))                             //Segunda coluna
        {
          if ((y>=temP[1]) && (y<=temP[3]))                      //press ph plus
          {
            //waitForIt(temP[0], temP[1], temP[2], temP[3]);
            PHR2beS += 0.1;
            if (PHR2beS > 9.9)
            {
              PHR2beS = 9.9;
            }
            config_phR_Screen();            
          }
          else if ((y>=offP[1]) && (y<=offP[3]))                           //press offset plus
          {
            //waitForIt(offP[0], offP[1], offP[2], offP[3]);
            PHR2beO += 0.1;
            if (PHR2beO > 9.9)
            {
              PHR2beO = 9.9;
            }
            config_phR_Screen();

          }
          else if ((y>=almP[1]) && (y<=almP[3]))                           //press alarm plus
          {
            //waitForIt(almP[0], almP[1], almP[2], almP[3]);
            PHR2beA += 0.1;
            if (PHR2beA > 9.9)
            {
              PHR2beA = 9.9;
            }
            config_phR_Screen();
          }
        }
        else if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu
        {
          //waitForIt(menU[0], menU[1], menU[2], menU[3]);
          dispScreen=14;
          clearScreen();
          parametroScreen(); 
        } 

      }
      break;
    case 16:             //---------------------------------------Tela controle de ORP---------------------------------
      if ((x>=prOK[0]) && (x<=prOK[2]) && (y>=prOK[1]) && (y<=prOK[3]))       //Funcao salvar
      {
        //waitForIt(prOK[0], prOK[1], prOK[2], prOK[3]);
        setORP = ORP2beS;
        offORP = ORP2beO;
        alarmORP = ORP2beA;
        dispScreen=14;
        SaveORPToEEPROM();
        clearScreen();
        parametroScreen();
      } 
      else
      {
        if ((x>=temM[0]) && (x<=temM[2]))                         // Primeira coluna
        {
          if ((y>=temM[1]) && (y<=temM[3]))                      //press orp minus
          {
            //waitForIt(temM[0], temM[1], temM[2], temM[3]);
            ORP2beS -= 10;
            if (ORP2beS < 100)
            {
              ORP2beS = 600;
            }
            config_orp_Screen();
          }
          else if ((y>=offM[1]) && (y<=offM[3]))                       //press offset minus
          {
            //waitForIt(offM[0], offM[1], offM[2], offM[3]);
            ORP2beO -= 10;
            if (ORP2beO < 10)
            {
              ORP2beO = 200;
            }
            config_orp_Screen();
          }          
          else if ((y>=almM[1]) && (y<=almM[3]))                        //press alarm minus
          {
            //waitForIt(almM[0], almM[1], almM[2], almM[3]);
            ORP2beA -= 10;
            if (ORP2beA < 10)
            {
              ORP2beA = 200;
            }
            config_orp_Screen();
          }
        }
        else if ((x>=temP[0]) && (x<=temP[2]))                             //Segunda coluna
        {
          if ((y>=temP[1]) && (y<=temP[3]))                      //press orp plus
          {
            //waitForIt(temP[0], temP[1], temP[2], temP[3]);
            ORP2beS += 10;
            if (ORP2beS > 600)
            {
              ORP2beS = 100;
            }
            config_orp_Screen();
          }
          else if ((y>=offP[1]) && (y<=offP[3]))                           //press offset plus
          {
            //waitForIt(offP[0], offP[1], offP[2], offP[3]);
            ORP2beO += 10;
            if (ORP2beO > 200)
            {
              ORP2beO = 10;
            }
            config_orp_Screen();
          }
          else if ((y>=almP[1]) && (y<=almP[3]))                           //press alarm plus
          {
            //waitForIt(almP[0], almP[1], almP[2], almP[3]);
            ORP2beA += 10;
            if (ORP2beA > 200)
            {
              ORP2beA = 10;
            }
            config_orp_Screen();
          }
        }
        else if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu
        {
          //waitForIt(menU[0], menU[1], menU[2], menU[3]);
          dispScreen=14;
          clearScreen();
          parametroScreen();
        } 

      }
      break;
    case 17:   //---------------------Tela grafico de ph do reator de calcio-------------------------------------
      if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           /// volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen=1;
        clearScreen();
        menuScreen(); 
      }
      else if ((x>=volT[0]) && (x<=volT[2]) && (y>=volT[1]) && (y<=volT[3]))           // volta a tela de graficos
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen=9;
        clearScreen();
        graficoScreen(); 
      }  
      break; 

    case 18: //--------------------------Tela configuracao de ph do aquario-----------------------------------
      if ((x>=prOK[0]) && (x<=prOK[2]) && (y>=prOK[1]) && (y<=prOK[3]))       //Funcao salvar
      {
        //waitForIt(prOK[0], prOK[1], prOK[2], prOK[3]);
        setPHA = PHA2beS;
        offPHA = PHA2beO;
        alarmPHA = PHA2beA;
        dispScreen=14;
        SavePHAToEEPROM();
        clearScreen();
        parametroScreen();
      } 
      else
      {
        if ((x>=temM[0]) && (x<=temM[2]))                         // Primeira coluna
        {
          if ((y>=temM[1]) && (y<=temM[3]))                      //press ph minus
          {
            //waitForIt(temM[0], temM[1], temM[2], temM[3]);
            PHA2beS -= 0.1;
            if (PHA2beS < 0.1)
            {
              PHA2beS = 0.1;
            }
            config_phA_Screen();
          }
          else if ((y>=offM[1]) && (y<=offM[3]))                       //press offset minus
          {
            //waitForIt(offM[0], offM[1], offM[2], offM[3]);
            PHA2beO -= 0.1;
            if (PHA2beO < 0.0) {
              PHA2beO = 0.0; 
            }
            config_phA_Screen();
          }          
          else if ((y>=almM[1]) && (y<=almM[3]))                        //press alarm minus
          {
            //waitForIt(almM[0], almM[1], almM[2], almM[3]);
            PHA2beA -= 0.1;
            if (PHA2beA < 0.0) {
              PHA2beA = 0.0;  
            }
            config_phA_Screen();
          }
        }
        else if ((x>=temP[0]) && (x<=temP[2]))                             //Segunda coluna
        {
          if ((y>=temP[1]) && (y<=temP[3]))                      //press temp plus
          {
            //waitForIt(temP[0], temP[1], temP[2], temP[3]);
            PHA2beS += 0.1;
            if (PHA2beS > 9.9)
            {
              PHA2beS = 9.9;
            }            
            config_phA_Screen();
          }
          else if ((y>=offP[1]) && (y<=offP[3]))                           //press offset plus
          {
            //waitForIt(offP[0], offP[1], offP[2], offP[3]);
            PHA2beO += 0.1;
            if (PHA2beO > 9.9)
            {
              PHA2beO = 9.9;
            }
            config_phA_Screen();
          }
          else if ((y>=almP[1]) && (y<=almP[3]))                           //press alarm plus
          {
            //waitForIt(almP[0], almP[1], almP[2], almP[3]);
            PHA2beA += 0.1;
            if (PHA2beA > 9.9)
            {
              PHA2beA = 9.9;
            }
            config_phA_Screen();
          }
        }
        else if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu
        {
          //waitForIt(menU[0], menU[1], menU[2], menU[3]);
          dispScreen=14;
          clearScreen();
          parametroScreen(); 
        } 
      }
      break;

    case 19://----------------------Tela grafico de densidade----------------------------------
      if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           /// volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen=1;
        clearScreen();
        menuScreen(); 
      }
      else if ((x>=volT[0]) && (x<=volT[2]) && (y>=volT[1]) && (y<=volT[3]))           // volta a tela de graficos
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen=9;
        clearScreen();
        graficoScreen(); 
      }  
      break;

    case 20: //--------------------------Tela configuração densidade  -----------------------------------------------------
      if ((x>=prOK[0]) && (x<=prOK[2]) && (y>=prOK[1]) && (y<=prOK[3]))       //Funcao salvar
      {
        //waitForIt(prOK[0], prOK[1], prOK[2], prOK[3]);
        setDEN = DEN2beS;
        offDEN = DEN2beO;
        alarmDEN = DEN2beA;
        dispScreen=14;
        SaveDENToEEPROM();
        clearScreen();
        parametroScreen();
      } 
      else
      {
        if ((x>=temM[0]) && (x<=temM[2]))                         // Primeira coluna
        {
          if ((y>=temM[1]) && (y<=temM[3]))                      //press densidade minus
          {
            //waitForIt(temM[0], temM[1], temM[2], temM[3]);
            DEN2beS -= 1;
            if (DEN2beS < 1000)
            {
              DEN2beS = 1000;
            }
            config_dens_Screen();
          }
          else if ((y>=offM[1]) && (y<=offM[3]))                       //press offset minus
          {
            //waitForIt(offM[0], offM[1], offM[2], offM[3]);
            DEN2beO -= 1;
            if (DEN2beO < 1)
            {
              DEN2beO = 10;
            }
            config_dens_Screen();
          }          
          else if ((y>=almM[1]) && (y<=almM[3]))                        //press alarm minus
          {
            //waitForIt(almM[0], almM[1], almM[2], almM[3]);
            DEN2beA -= 1;
            if (DEN2beA < 1)
            {
              DEN2beA = 10;
            }
            config_dens_Screen();
          }
        }
        else if ((x>=temP[0]) && (x<=temP[2]))                             //Segunda coluna
        {
          if ((y>=temP[1]) && (y<=temP[3]))                      //press densidade plus
          {
            //waitForIt(temP[0], temP[1], temP[2], temP[3]);
            DEN2beS += 1;
            if (DEN2beS > 1050)
            {
              DEN2beS = 1000;
            }
            config_dens_Screen();
          }
          else if ((y>=offP[1]) && (y<=offP[3]))                           //press offset plus
          {
            //waitForIt(offP[0], offP[1], offP[2], offP[3]);
            DEN2beO += 1;
            if (DEN2beO > 10)
            {
              DEN2beO = 1;
            }
            config_dens_Screen();
          }
          else if ((y>=almP[1]) && (y<=almP[3]))                           //press alarm plus
          {
            //waitForIt(almP[0], almP[1], almP[2], almP[3]);
            DEN2beA += 1;
            if (DEN2beA > 10)
            {
              DEN2beA = 1;
            }
            config_dens_Screen();
          }
        }
        else if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu
        {
          //waitForIt(menU[0], menU[1], menU[2], menU[3]);
          dispScreen=14;
          clearScreen();
          parametroScreen(); 
        } 
      }
      break;
    case 21: // ------------------------------------------------ Escolher dosadora -----------------------------------

      if ((x>=dosa1[0]) && (x<=dosa1[2]) && (y>=dosa1[1]) && (y<=dosa1[3]))         
      {
        //waitForIt(dosa1[0], dosa1[1], dosa1[2], dosa1[3]);
        if (modo_manual == true)
        {
          dosadora_selecionada = 0;
          dispScreen = 27;
          clearScreen();
          config_dosagem_manual(true);
        }     
        if (modo_personalizado == true)
        {
          dosadora_selecionada = 0;       
          dispScreen = 29;
          clearScreen();
          config_dosagem_personalizada(true);
        }

        if (modo_calibrar == true)
        {
          dosadora_selecionada = 0;
          dispScreen = 26;
          clearScreen();
          calibrar_dosadoras(true);
        }      
      }
      else if ((x>=dosa2[0]) && (x<=dosa2[2]) && (y>=dosa2[1]) && (y<=dosa2[3]))         
      {
        //waitForIt(dosa2[0], dosa2[1], dosa2[2], dosa2[3]);
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
      else if ((x>=dosa3[0]) && (x<=dosa3[2]) && (y>=dosa3[1]) && (y<=dosa3[3]))         
      {
        //waitForIt(dosa3[0], dosa3[1], dosa3[2], dosa3[3]);
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
      else if ((x>=dosa4[0]) && x<=dosa4[2] && (y>=dosa4[1]) && (y<=dosa4[3]))         
      {
        //waitForIt(dosa4[0], dosa4[1], dosa4[2], dosa4[3]);
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
      else if ((x>=dosa5[0]) && x<=dosa5[2] && (y>=dosa5[1]) && (y<=dosa5[3]))         
      {
        //waitForIt(dosa5[0], dosa5[1], dosa5[2], dosa5[3]);
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
      else if ((x>=dosa6[0]) && x<=dosa6[2] && (y>=dosa6[1]) && (y<=dosa6[3]))         
      {
        //waitForIt(dosa6[0], dosa6[1], dosa6[2], dosa6[3]);
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
      else if ((x>=menU[0]) && x<=menU[2] && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen = 1;
        clearScreen();
        menuScreen(); 
      }
      else if ((x>=volT[0]) && x<=volT[2] && (y>=volT[1]) && (y<=volT[3]))           // volta a tela de escolha da dosadora
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen = 8;
        clearScreen();
        menu_dosadoras();
      }
      break;
    case 22:// ----------------------------------------- Teste individual dos leds -----------------------
      if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen = 1;
        clearScreen();
        menuScreen(); 
        ler_predefinido_EEPROM();   
      }
      else if ((x>=volT[0]) && (x<=volT[2]) && (y>=volT[1]) && (y<=volT[3]))           // volta a tela escolher teste
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen=25;
        clearScreen();
        escolher_teste();
        ler_predefinido_EEPROM(); 
      }
      else if((y >= 44) && (y <= 172))//**************** Controle deslizante - início.
      {
        teste_em_andamento = true;
        if((x >= 49) && (x<=93))
        {
          y_tocado = y;
          desenhar_barras(cor_canal1[0], cor_canal1[1],cor_canal1[2], 49, 44, 93, 172);
          wled_out_temp = map(y_tocado, 172, 44, 0, 255);

          if(wled_out_temp >=100)
          {
            myGLCD.printNumI(wled_out_temp, 61, 186); 
          }
          else if((wled_out_temp >= 10) && (wled_out_temp < 100))
          {
            myGLCD.print("0", 61, 186);  
            myGLCD.printNumI(wled_out_temp, 69, 186); 
          } 
          else if(wled_out_temp < 10)
          {
            myGLCD.print("00", 61, 186);  
            myGLCD.printNumI(wled_out_temp, 77, 186); 
          }         
        }
        else if((x >= 101) && (x <= 145)) //**************** Controle deslizante
        {
          y_tocado = y;
          desenhar_barras(cor_canal2[0], cor_canal2[1],cor_canal2[2], 101, 44, 145, 172);
          bled_out_temp = map(y_tocado, 172, 44, 0, 255);

          if(bled_out_temp >= 100)
          {
            myGLCD.printNumI(bled_out_temp, 113, 186);
          }
          else if((bled_out_temp >= 10) && (bled_out_temp < 100))
          {
            myGLCD.print("0", 113, 186);
            myGLCD.printNumI(bled_out_temp, 121, 186);
          }
          else if(bled_out_temp < 10)
          {
            myGLCD.print("00", 113, 186);
            myGLCD.printNumI(bled_out_temp, 129, 186);
          }
        }
        else if((x >= 153) && (x <= 197)) //**************** Controle deslizante
        {
          y_tocado = y;
          desenhar_barras(cor_canal3[0], cor_canal3[1],cor_canal3[2], 153, 44, 197, 172);
          rbled_out_temp = map(y_tocado, 172, 44, 0, 255);

          if(rbled_out_temp >= 100)
          {
            myGLCD.printNumI(rbled_out_temp, 165, 186);
          }
          else if((rbled_out_temp >= 10) && (rbled_out_temp < 100))
          {
            myGLCD.print("0", 165, 186);
            myGLCD.printNumI(rbled_out_temp, 173, 186);
          }
          else if(rbled_out_temp < 10)
          {
            myGLCD.print("00", 165, 186);
            myGLCD.printNumI(rbled_out_temp, 181, 186);
          }
        }
        else if((x >= 205) && (x <= 249)) //**************** Controle deslizante
        {
          y_tocado = y;
          desenhar_barras(cor_canal4[0], cor_canal4[1],cor_canal4[2], 205, 44, 249, 172);
          rled_out_temp = map(y_tocado, 172, 44, 0, 255);

          if(rled_out_temp >= 100)
          {
            myGLCD.printNumI(rled_out_temp, 217, 186);
          }
          else if((rled_out_temp >= 10) && (rled_out_temp < 100))
          {
            myGLCD.print("0", 217, 186);
            myGLCD.printNumI(rled_out_temp, 225, 186);
          }          
          else if(rled_out_temp < 10)
          {
            myGLCD.print("00", 217, 186);
            myGLCD.printNumI(rled_out_temp, 233, 186);
          }          
        }       
        else if((x >= 257) && (x <= 301)) //**************** Controle deslizante
        {
          y_tocado = y;
          desenhar_barras(cor_canal5[0], cor_canal5[1],cor_canal5[2], 257, 44, 301, 172); 
          uvled_out_temp = map(y_tocado, 172, 44, 0, 255);
          if(uvled_out_temp >= 100)
          {
            myGLCD.printNumI(uvled_out_temp, 269, 186);
          }
          else if((uvled_out_temp >= 10) && (uvled_out_temp < 100))
          {
            myGLCD.print("0", 269, 186);
            myGLCD.printNumI(uvled_out_temp, 277, 186);
          }
          else if(uvled_out_temp < 10)
          {
            myGLCD.print("00", 269, 186);
            myGLCD.printNumI(uvled_out_temp, 285, 186);
          } 
        }
      }//**************** Controle deslizante - fim.

      else if((y >= 18) && (y <= 41))// Botão mais
      {
        teste_em_andamento = true;
        if((x >= 49) && (x<=93))
        {
          //waitForIt(49, 18, 93, 41);
          wled_out_temp += 1;
          delay(50);
          y_tocado = map(wled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal1[0], cor_canal1[1],cor_canal1[2], 49, 44, 93, 172);
          if(wled_out_temp >=100)
          {
            myGLCD.printNumI(wled_out_temp, 61, 186); 
          }
          else if((wled_out_temp >= 10) && (wled_out_temp < 100))
          {
            myGLCD.print("0", 61, 186);  
            myGLCD.printNumI(wled_out_temp, 69, 186); 
          } 
          else if(wled_out_temp < 10)
          {
            myGLCD.print("00", 61, 186);  
            myGLCD.printNumI(wled_out_temp, 77, 186); 
          }  
        }
        if((x >= 101) && (x <= 145)) // Botão mais
        {
          //waitForIt(101, 18, 145, 41);
          bled_out_temp += 1;
          delay(50);
          y_tocado = map(bled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal2[0], cor_canal2[1],cor_canal2[2], 101, 44, 145, 172);

          if(bled_out_temp >= 100)
          {
            myGLCD.printNumI(bled_out_temp, 113, 186);
          }
          else if((bled_out_temp >= 10) && (bled_out_temp < 100))
          {
            myGLCD.print("0", 113, 186);
            myGLCD.printNumI(bled_out_temp, 121, 186);
          }
          else if(bled_out_temp < 10)
          {
            myGLCD.print("00", 113, 186);
            myGLCD.printNumI(bled_out_temp, 129, 186);
          }
        }
        else if((x >= 153) && (x <= 197)) // Botão mais
        {
          //waitForIt(153, 18, 197, 41);
          rbled_out_temp += 1;
          delay(50);
          y_tocado = map(rbled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal3[0], cor_canal3[1],cor_canal3[2], 153, 44, 197, 172);
          if(rbled_out_temp >= 100)
          {
            myGLCD.printNumI(rbled_out_temp, 165, 186);
          }
          else if((rbled_out_temp >= 10) && (rbled_out_temp < 100))
          {
            myGLCD.print("0", 165, 186);
            myGLCD.printNumI(rbled_out_temp, 173, 186);
          }
          else if(rbled_out_temp < 10)
          {
            myGLCD.print("00", 165, 186);
            myGLCD.printNumI(rbled_out_temp, 181, 186);
          }
        }
        if((x >= 205) && (x <= 249)) // Botão mais
        {
          //waitForIt(205, 18, 249, 41);
          rled_out_temp += 1;
          delay(50);
          y_tocado = map(rled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal4[0], cor_canal4[1],cor_canal4[2], 205, 44, 249, 172);

          if(rled_out_temp >= 100)
          {
            myGLCD.printNumI(rled_out_temp, 217, 186);
          }
          else if((rled_out_temp >= 10) && (rled_out_temp < 100))
          {
            myGLCD.print("0", 217, 186);
            myGLCD.printNumI(rled_out_temp, 225, 186);
          }          
          else if(rled_out_temp < 10)
          {
            myGLCD.print("00", 217, 186);
            myGLCD.printNumI(rled_out_temp, 233, 186);
          }
        }       
        if((x >= 257) && (x <= 301)) // Botão mais
        {
          //waitForIt(257, 18, 301, 41);
          uvled_out_temp += 1;
          delay(50);
          y_tocado = map(uvled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal5[0], cor_canal5[1],cor_canal5[2], 257, 44, 301, 172);
          if(uvled_out_temp >= 100)
          {
            myGLCD.printNumI(uvled_out_temp, 269, 186);
          }
          else if((uvled_out_temp >= 10) && (uvled_out_temp < 100))
          {
            myGLCD.print("0", 269, 186);
            myGLCD.printNumI(uvled_out_temp, 277, 186);
          }
          else if(uvled_out_temp < 10)
          {
            myGLCD.print("00", 269, 186);
            myGLCD.printNumI(uvled_out_temp, 285, 186);
          }
        }
      }
      else if((y >= 201) && (y <= 224))
      {
        teste_em_andamento = true;

        if((x >= 49) && (x <= 93)) // Botão menos
        {
          //waitForIt(49, 201, 93, 224); 
          wled_out_temp -= 1;
          delay(50);
          y_tocado = map(wled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal1[0], cor_canal1[1],cor_canal1[2], 49, 44, 93, 172);
          if(wled_out_temp >=100)
          {
            myGLCD.printNumI(wled_out_temp, 61, 186); 
          }
          else if((wled_out_temp >= 10) && (wled_out_temp < 100))
          {
            myGLCD.print("0", 61, 186);  
            myGLCD.printNumI(wled_out_temp, 69, 186); 
          } 
          else if(wled_out_temp < 10)
          {
            myGLCD.print("00", 61, 186);  
            myGLCD.printNumI(wled_out_temp, 77, 186); 
          }
        }
        else if((x >= 101) && (x <= 145)) // Botão menos
        {
          //waitForIt(101, 201, 145, 224);
          bled_out_temp -= 1;
          delay(50);
          y_tocado = map(bled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal2[0], cor_canal2[1],cor_canal2[2], 101, 44, 145, 172);

          if(bled_out_temp >= 100)
          {
            myGLCD.printNumI(bled_out_temp, 113, 186);
          }
          else if((bled_out_temp >= 10) && (bled_out_temp < 100))
          {
            myGLCD.print("0", 113, 186);
            myGLCD.printNumI(bled_out_temp, 121, 186);
          }
          else if(bled_out_temp < 10)
          {
            myGLCD.print("00", 113, 186);
            myGLCD.printNumI(bled_out_temp, 129, 186);
          }
        }
        else if((x >= 153) && (x <= 197)) // Botão menos
        {
          //waitForIt(153, 201, 197, 224);
          rbled_out_temp -= 1;
          delay(50);
          y_tocado = map(rbled_out_temp, 255, 0, 44, 172);

          desenhar_barras(cor_canal3[0], cor_canal3[1],cor_canal3[2], 153, 44, 197, 172);
          if(rbled_out_temp >= 100)
          {
            myGLCD.printNumI(rbled_out_temp, 165, 186);
          }
          else if((rbled_out_temp >= 10) && (rbled_out_temp < 100))
          {
            myGLCD.print("0", 165, 186);
            myGLCD.printNumI(rbled_out_temp, 173, 186);
          }
          else if(rbled_out_temp < 10)
          {
            myGLCD.print("00", 165, 186);
            myGLCD.printNumI(rbled_out_temp, 181, 186);
          }
        }
        else if((x >= 205) && (x <= 249)) // Botão menos
        {
          //waitForIt(205, 201, 249, 224);
          rled_out_temp -= 1;
          delay(50);
          y_tocado = map(rled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal4[0], cor_canal4[1],cor_canal4[2], 205, 44, 249, 172);

          if(rled_out_temp >= 100)
          {
            myGLCD.printNumI(rled_out_temp, 217, 186);
          }
          else if((rled_out_temp >= 10) && (rled_out_temp < 100))
          {
            myGLCD.print("0", 217, 186);
            myGLCD.printNumI(rled_out_temp, 225, 186);
          }
          else if(rled_out_temp < 10)
          {
            myGLCD.print("00", 217, 186);
            myGLCD.printNumI(rled_out_temp, 233, 186);
          }
        }       
        else if((x >= 257) && (x <= 301)) // Botão menos
        {
          //waitForIt(257, 201, 301, 224);  
          uvled_out_temp -= 1;
          delay(50);
          y_tocado = map(uvled_out_temp, 255, 0, 44, 172);
          desenhar_barras(cor_canal5[0], cor_canal5[1],cor_canal5[2], 257, 44, 301, 172);
          if(uvled_out_temp >= 100)
          {
            myGLCD.printNumI(uvled_out_temp, 269, 186);
          }
          else if((uvled_out_temp >= 10) && (uvled_out_temp < 100))
          {
            myGLCD.print("0", 269, 186);
            myGLCD.printNumI(uvled_out_temp, 277, 186);
          }
          else if(uvled_out_temp < 10)
          {
            myGLCD.print("00", 269, 186);
            myGLCD.printNumI(uvled_out_temp, 285, 186);
          }
        }
      }
      break;
    case 23:// -------------------------------- Rever configuração das dosadoras modo personalizado ------------------------------------------
      if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen = 1;
        clearScreen();
        menuScreen(); 
      }
      else if ((x>=volT[0]) && (x<=volT[2]) && (y>=volT[1]) && (y<=volT[3]))           // volta ao menu de revisão das dosadoras
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen=34;
        clearScreen();
        rever_dosagem_personalizada();
      }
      break;
    case 24:// -------------------------------------- Desativar dosadoras ------------------------------------------
      if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen = 1;
        clearScreen();
        menuScreen();    
      }
      else if ((x>=volT[0]) && (x<=volT[2]) && (y>=volT[1]) && (y<=volT[3]))           // volta ao menu desativar dosadoras
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen = 35;
        clearScreen();
        desativar_dosadoras(true);
      }
      else if ((x >= 100) && (x <= 220) && (y >= 45) && (y <= 85))           //Ativar/desativar dosadora 4
      {
        //waitForIt(100, 45, 220, 85);

        if(bitRead(ativar_desativar,4) == true)
        {
          bitWrite(ativar_desativar,4 ,0);
          desativar_dosadoras_2();
        }
        else
        {
          desativar_dosadoras_2(true);
        }          
      }
      else if ((x >= 100) && (x <= 220) && (y >= 115) && (y <= 155))           //Ativar/desatiavr dosadora 5
      {
        //waitForIt(100, 115, 220, 155);

        if(bitRead(ativar_desativar,5) == true)
        {
          bitWrite(ativar_desativar,5 ,0);
          desativar_dosadoras_2();
        }
        else
        {
          desativar_dosadoras_2(true);
        }          
      }
      else if ((x >= 100) && (x <= 220) && (y >= 185) && (y <= 225))           //Ativar/desatiavr dosadora 6
      {
        //waitForIt(100, 185, 220, 225);

        if(bitRead(ativar_desativar,6) == true)
        {
          bitWrite(ativar_desativar,6 ,0);
          desativar_dosadoras_2();
        }
        else
        {
          desativar_dosadoras_2(true);
        }          
      }
      else if ((x>=salV[0]) && (x<=salV[2]) && (y>=salV[1]) && (y<=salV[3]))           //Salvar alterações
      {
        //waitForIt(salV[0], salV[1], salV[2], salV[3]);
        if(bitRead(ativar_desativar,4) == false)
        {
          modo_personalizado_on_4 = 0;
        }
        else if(bitRead(ativar_desativar,5) == false)
        {
          modo_personalizado_on_5 = 0;
        }
        else if(bitRead(ativar_desativar,6) == false)
        {
          modo_personalizado_on_6 = 0;
        }
        Salvar_dosadora_EEPROM(); 
        dispScreen = 8;
        clearScreen();
        menu_dosadoras();       
      }
      break;
    case 25:// ------------------------------------ Escolher teste dos leds --------------------------------------------
      if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu 1
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen = 1;
        clearScreen();
        menuScreen();    
      } 
      else if ((x>=testI[0]) && (x<=testI[2]) && (y>=testI[1]) && (y<=testI[3]))           // Teste individual
      {
        //waitForIt(testI[0], testI[1], testI[2], testI[3]);
        dispScreen = 22;
        clearScreen();
        teste_individual_leds(); 
      }   
      else if ((x>=testT[0]) && (x<=testT[2]) && (y>=testT[1]) && (y<=testT[3]))           // Testar todos
      {
        //waitForIt(testT[0], testT[1], testT[2], testT[3]);
        dispScreen = 3;
        clearScreen();
        testScreen(true); 
      }            
      else if ((x>=volT[0]) && (x<=volT[2]) && (y>=volT[1]) && (y<=volT[3]))           // volta ao menu desativar dosadoras
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen=40;
        clearScreen();
        config_leds();
      }
      break;
    case 26: //------------------------------------ calibrar dosadoras -------------------------------------------
      if ((x>=almP[0]) && x<=almP[2] && (y>=almP[1]) && (y<=almP[3]))            //fator calibracao mais.
      {
        //waitForIt(almP[0], almP[1], almP[2], almP[3]);
        fator_calib_dosadora[dosadora_selecionada] += 0.1;
        if (fator_calib_dosadora[dosadora_selecionada] > 99.9)
        {
          fator_calib_dosadora[dosadora_selecionada] = 0.0;
        }
        calibrar_dosadoras();
      }
      else if ((x>=almM[0]) && x<=almM[2] && (y>=almM[1]) && (y<=almM[3]))            //fator calibracao menos.
      {
        //waitForIt(almM[0], almM[1], almM[2], almM[3]);
        fator_calib_dosadora[dosadora_selecionada] -= 0.1;
        if (fator_calib_dosadora[dosadora_selecionada] < 0.1)
        {
          fator_calib_dosadora[dosadora_selecionada] = 99.9;
        }
        calibrar_dosadoras();
      }     
      else if ((x>=salV[0]) && x<=salV[2] && (y>=salV[1]) && (y<=salV[3]))
      {
        //waitForIt(salV[0], salV[1], salV[2], salV[3]); // Função salvar
        fator_calib_dosadora_1 = fator_calib_dosadora[0];
        fator_calib_dosadora_2 = fator_calib_dosadora[1];
        fator_calib_dosadora_3 = fator_calib_dosadora[2];
        fator_calib_dosadora_4 = fator_calib_dosadora[3];
        fator_calib_dosadora_5 = fator_calib_dosadora[4];
        fator_calib_dosadora_6 = fator_calib_dosadora[5];
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
      else if ((x>=volT[0]) && x<=volT[2] && (y>=volT[1]) && (y<=volT[3]))           // Volta a tela altera configuracao das dosadoras
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
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
      else if ((x>=iniciaR[0]) && (x<=iniciaR[2]) && (y>=iniciaR[1]) && (y<=iniciaR[3]))
      {
        //waitForIt(iniciaR[0], iniciaR[1], iniciaR[2], iniciaR[3]);
        if(modo_calibrar == true)
        {
          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[17])));
          printButton_verde(buffer, iniciaR[0], iniciaR[1], iniciaR[2], iniciaR[3]);

          delay(10000);
          digitalWrite(dosadora[dosadora_selecionada], HIGH);
          delay(60000);
          digitalWrite(dosadora[dosadora_selecionada], LOW);

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[17])));
          printButton(buffer, iniciaR[0], iniciaR[1], iniciaR[2], iniciaR[3]);
        }
      }      
      break;
    case 27:   // ----------------------------------------- Config dosagem manual --------------------------------------
      if ((x>=almP[0]) && (x<=almP[2]) && (y>=almP[1]) && (y<=almP[3]))            //dose manual mais.
      {
        //waitForIt(almP[0], almP[1], almP[2], almP[3]);
        dose_dosadora_manual[dosadora_selecionada] += 0.5;
        if (dose_dosadora_manual[dosadora_selecionada] > 99.5)
        {
          dose_dosadora_manual[dosadora_selecionada] = 0.0;
        }
        config_dosagem_manual();
      }
      else if ((x >= almM[0]) && (x <= almM[2]) && (y >= almM[1]) && (y <= almM[3]))            //dose manual menos.
      {
        //waitForIt(almM[0], almM[1], almM[2], almM[3]);
        dose_dosadora_manual[dosadora_selecionada] -= 0.5;
        if (dose_dosadora_manual[dosadora_selecionada] < 0.5)
        {
          dose_dosadora_manual[dosadora_selecionada] = 99.5;
        }
        config_dosagem_manual();
      }
      else if ((x>=volT[0]) && x<=volT[2] && (y>=volT[1]) && (y<=volT[3]))           // Volta a tela altera configuracao das dosadoras
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
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
      else if ((x>=iniciaR[0]) && x<=iniciaR[2] && (y>=iniciaR[1]) && (y<=iniciaR[3]))
      {
        //waitForIt(iniciaR[0], iniciaR[1], iniciaR[2], iniciaR[3]);
        if(modo_manual == true)
        {
          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[17])));
          printButton_verde(buffer, iniciaR[0], iniciaR[1], iniciaR[2], iniciaR[3]);

          tempo_dosagem = map ((dose_dosadora_manual[dosadora_selecionada]*2), 0, fator_calib_dosadora[dosadora_selecionada], 0, 60000);
          tempo_dosagem /= 2;                 
          delay(10000);
          digitalWrite(dosadora[dosadora_selecionada], HIGH);
          delay(tempo_dosagem);
          digitalWrite(dosadora[dosadora_selecionada], LOW);

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[17])));
          printButton(buffer, iniciaR[0], iniciaR[1], iniciaR[2], iniciaR[3]);
        }   
      }      
      break;

    case 28:  //--------------------------------Escolher canal LEDS-----------------------------------
      if ((x >= tempG[0]) && (x <= tempG[2]) && (y >= tempG[1]) && (y <= tempG[3]))           
      {
        //waitForIt(tempG[0], tempG[1], tempG[2], tempG[3]);
        cor_selecionada = 0;
        dispScreen=5;
        clearScreen(); 
        ledSetScreen();
      }
      else if ((x >= phA[0]) && (x <= phA[2]) && (y>=phA[1]) && (y<=phA[3]))           
      {
        //waitForIt(phA[0], phA[1], phA[2], phA[3]);
        cor_selecionada = 1;
        dispScreen=5;
        clearScreen(); 
        ledSetScreen();
      } 
      else if ((x >= phR[0]) && (x <= phR[2]) && (y >= phR[1]) && (y <= phR[3]))           
      {
        //waitForIt(phR[0], phR[1], phR[2], phR[3]);
        cor_selecionada = 2;
        dispScreen=5;
        clearScreen(); 
        ledSetScreen(); 
      }

      else if ((x >= orP[0]) && (x <= orP[2]) && (y >= orP[1]) && (y <= orP[3]))           
      {
        //waitForIt(orP[0], orP[1], orP[2], orP[3]);
        cor_selecionada = 3;
        dispScreen=5;
        clearScreen(); 
        ledSetScreen(); 
      } 
      else if ((x >= denS[0]) && (x <= denS[2]) && (y >= denS[1]) && (y <= denS[3]))           
      {
        //waitForIt(denS[0], denS[1], denS[2], denS[3]);
        cor_selecionada = 4;
        dispScreen=5;
        clearScreen(); 
        ledSetScreen(); 
      }  
      else if ((x >= menU[0]) && (x <= menU[2]) && (y >= menU[1]) && (y <= menU[3]))           /// volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen=1;
        clearScreen();
        menuScreen(); 
        ReadFromEEPROM();
      }          
      else if ((x>=volT[0]) && x<=volT[2] && (y>=volT[1]) && (y<=volT[3]))           // Volta a tela altera configuracao das dosadoras
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen = 40;
        clearScreen();
        ReadFromEEPROM();
        config_leds();
      }
      break;

    case 29:   // ----------------------------------------- Config dosagem personalizada --------------------------------------
      if ((x>=menU[0]) && x<=menU[2] && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen = 1;
        clearScreen();
        menuScreen(); 
      }
      else if ((x>=volT[0]) && x<=volT[2] && (y>=volT[1]) && (y<=volT[3]))           // Volta a tela altera configuracao das dosadoras
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
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
      else if ((y >= proX[1]) && (y <= proX[3]) && (x >= proX[0]) && (x <= proX[2])) 
      {
        //waitForIt(proX[0], proX[1], proX[2], proX[3]); //Próximo menu.
        dispScreen = 31;
        clearScreen();
        config_dosagem_personalizada_2(true);
      }

      else if ((y >= houU[1]) && (y <= houU[3])) // Buttons: Time UP
      {
        if ((x >= houU[0]) && (x <= houU[2])) 
        {
          //waitForIt(houU[0], houU[1], houU[2], houU[3]);
          hora_inicial_dosagem_personalizada[dosadora_selecionada] = (hora_inicial_dosagem_personalizada[dosadora_selecionada] + 1) % 24;
          config_dosagem_personalizada();
        } 
        else if ((x >= minUT[0]) && (x <= minUT[2])) 
        {
          //waitForIt(minUT[0], minUT[1], minUT[2], minUT[3]);
          minuto_inicial_dosagem_personalizada[dosadora_selecionada] = (minuto_inicial_dosagem_personalizada[dosadora_selecionada] + 1) % 60;
          config_dosagem_personalizada();
        } 

        else if ((x >= houU[0] + 155) && (x <= houU[2] + 155)) 
        {
          //waitForIt(houU[0] + 155, houU[1], houU[2] + 155, houU[3]);
          hora_final_dosagem_personalizada[dosadora_selecionada] = (hora_final_dosagem_personalizada[dosadora_selecionada] + 1) % 24;
          config_dosagem_personalizada();
        } 
        else if ((x >= minUT[0] + 155) && (x <= minUT[2] + 155)) 
        {
          //waitForIt(minUT[0] + 155, minUT[1], minUT[2] + 155, minUT[3]);
          minuto_final_dosagem_personalizada[dosadora_selecionada] = (minuto_final_dosagem_personalizada[dosadora_selecionada] + 1) % 60;
          config_dosagem_personalizada();
        }

      } 
      else if ((y >= houD[1]) && (y <= houD[3])) // Buttons: Time DOWN
      {
        if ((x >= houD[0]) && (x <= houD[2])) 
        {
          //waitForIt(houD[0], houD[1], houD[2], houD[3]);
          hora_inicial_dosagem_personalizada[dosadora_selecionada] = (hora_inicial_dosagem_personalizada[dosadora_selecionada] + 23) % 24;
          config_dosagem_personalizada();
        } 
        else if ((x >= minDT[0]) && (x <= minDT[2])) 
        {
          //waitForIt(minDT[0], minDT[1], minDT[2], minDT[3]);
          minuto_inicial_dosagem_personalizada[dosadora_selecionada] = (minuto_inicial_dosagem_personalizada[dosadora_selecionada] + 59) % 60;
          config_dosagem_personalizada();
        } 
        else if ((x >= houD[0] + 155) && (x <= houD[2] + 155)) 
        {
          //waitForIt(houD[0] + 155, houD[1], houD[2] + 155, houD[3]);
          hora_final_dosagem_personalizada[dosadora_selecionada] = (hora_final_dosagem_personalizada[dosadora_selecionada] + 23) % 24;
          config_dosagem_personalizada();
        } 
        else if ((x >= minDT[0] + 155) && (x <= minDT[2] + 155)) 
        {
          //waitForIt(minDT[0] + 155, minDT[1], minDT[2] + 155, minDT[3]);
          minuto_final_dosagem_personalizada[dosadora_selecionada] = (minuto_final_dosagem_personalizada[dosadora_selecionada] + 59) % 60;
          config_dosagem_personalizada();
        }
      }

      else if ((x >= segU[0]) && (x <= segU[2]) && (y >= segU[1]) && (y <= segU[3])) 
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
      else if ((x >= terC[0]) && (x <= terC[2]) && (y >= terC[1]) && (y <= terC[3])) 
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
      else if ((x >= quaR[0]) && (x <= quaR[2]) && (y >= quaR[1]) && (y <= quaR[3])) 
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
      else if ((x >= quiN[0]) && (x <= quiN[2]) && (y >= quiN[1]) && (y <= quiN[3])) 
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
      if ((x >= sexT[0]) && (x <= sexT[2]) && (y >= sexT[1]) && (y <= sexT[3])) 
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
      else if ((x >= sabA[0]) && (x <= sabA[2]) && (y >= sabA[1]) && (y <= sabA[3])) 
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
      else if ((x >= domI[0]) && (x <= domI[2]) && (y >= domI[1]) && (y <= domI[3])) 
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

      if ((x>=boT1[0]) && (x<=boT1[2]) && (y>=boT1[1]) && (y<=boT1[3]))  // Botao: 1
      {
        //waitForIt(boT1[0], boT1[1], boT1[2] ,boT1[3]);
        updateStr('1');
      }

      else if ((x>=boT2[0]) && (x<=boT2[2]) && (y>=boT2[1]) && (y<=boT2[3]))  // Botao: 2
      {
        //waitForIt(boT2[0], boT2[1], boT2[2], boT2[3]);
        updateStr('2');
      }
      else if ((x>=boT3[0]) && (x<=boT3[2]) && (y>=boT3[1]) && (y<=boT3[3]))  // Botao: 3
      {
        //waitForIt(boT3[0], boT3[1], boT3[2], boT3[3]);
        updateStr('3');
      }
      else if ((x>=boT4[0]) && (x<=boT4[2]) && (y>=boT4[1]) && (y<=boT4[3]))  // Botao: 4
      {
        //waitForIt(boT4[0], boT4[1], boT4[2], boT4[3]);
        updateStr('4');
      }
      else if ((x>=boT5[0]) && (x<=boT5[2]) && (y>=boT5[1]) && (y<=boT5[3]))  // Botao: 5
      {
        //waitForIt(boT5[0], boT5[1], boT5[2], boT5[3]);
        updateStr('5');
      }

      else if ((x>=boT6[0]) && (x<=boT6[2]) && (y>=boT6[1]) && (y<=boT6[3]))  // Botao: 6
      {
        //waitForIt(boT6[0], boT6[1], boT6[2], boT6[3]);
        updateStr('6');
      }
      else if ((x>=boT7[0]) && (x<=boT7[2]) && (y>=boT7[1]) && (y<=boT7[3]))  // Botao: 7
      {
        //waitForIt(boT7[0], boT7[1], boT7[2], boT7[3]);
        updateStr('7');
      }
      else if ((x>=boT8[0]) && (x<=boT8[2]) && (y>=boT8[1]) && (y<=boT8[3]))  // Botao: 8
      {
        //waitForIt(boT8[0], boT8[1], boT8[2], boT8[3]);
        updateStr('8');
      }
      else if ((x>=boT9[0]) && (x<=boT9[2]) && (y>=boT9[1]) && (y<=boT9[3]))  // Botao: 9
      {
        //waitForIt(boT9[0], boT9[1], boT9[2], boT9[3]);
        updateStr('9');
      }
      else if ((x>=boT0[0]) && (x<=boT0[2]) && (y>=boT0[1]) && (y<=boT0[3]))  // Botao: 0
      {
        //waitForIt(boT0[0], boT0[1], boT0[2], boT0[3]);
        updateStr('0');
      }

      else if ((x>=boTL[0]) && (x<=boTL[2]) && (y>=boTL[1]) && (y<=boTL[3]))  // Botao: limpar
      {
        //waitForIt(boTL[0], boTL[1], boTL[2], boTL[3]);
        for (int i=0; i < 7;i++) 
        {
          stCurrent[i] = '\0';
        }
        stCurrentLen=0;
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect (110, 210, 300, 225); //Limpar senha impressa ***************
      }
      else if ((x>=boTE[0]) && (x<=boTE[2]) && (y>=boTE[1]) && (y<=boTE[3]))  // Botao: entrar
      {
        //waitForIt(boTE[0], boTE[1], boTE[2], boTE[3]);
        if ((stCurrent[0] == senha [0]) && (stCurrent[1] == senha [1]) && (stCurrent[2] == senha [2]) && (stCurrent[3] == senha [3]) && (stCurrent[4] == senha [4]) && (stCurrent[5] == senha [5]) && stCurrentLen <=6)
        {
          stCurrentLen=0;
          myGLCD.setFont(BigFont);
          myGLCD.setColor(0, 255, 0);
          myGLCD.setBackColor(0, 0, 0);

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[173])));
          myGLCD.print(buffer, 51, 192); // tabela_textos[173] = "SENHA CORRETA"

          delay(500);
          dispScreen=1;
          clearScreen();
          menuScreen();
          memcpy(stCurrent, limpar_senha, sizeof(limpar_senha));
        }
        else if(stCurrentLen <=6)
        {
          for(byte i = 0; i < 3; i++)
          {
            myGLCD.setFont(BigFont);  
            myGLCD.setColor(255, 0, 0);
            strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[174])));
            myGLCD.print(buffer, 35, 192); // tabela_textos[174] = "SENHA INCORRETA!"

            delay(1000);
            myGLCD.setColor(0, 0, 0);
            myGLCD.fillRect (35, 192, 300, 207);
            delay(500);
          }
          myGLCD.fillRect (110, 210, 300, 225); //Limpar senha impressa ***************
          stCurrentLen=0;
          memcpy(stCurrent, limpar_senha, sizeof(limpar_senha));
        }
        else if(stCurrentLen > 6)
        {
          myGLCD.setFont(BigFont);
          myGLCD.setColor(255, 0, 0);
          myGLCD.setBackColor(0, 0, 0);

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[174]))); 
          myGLCD.print(buffer, 35, 192); // tabela_textos[174] = "SENHA INCORRETA!"

          delay(1000);
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect (35, 192, 300, 207);

          for(byte i = 0; i < 3; i++)
          {
            delay(500);  
            myGLCD.setColor(255, 0, 0);
            strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[175])));
            myGLCD.print(buffer, 35, 192); // "MAXIMO 6 DIGITOS!"

            delay(1000);
            myGLCD.setColor(0, 0, 0);
            myGLCD.fillRect (35, 192, 300, 207);
          }

          myGLCD.fillRect (110, 210, 300, 225); //Limpar senha impressa ***************
          stCurrentLen=0;
          memcpy(stCurrent, limpar_senha, sizeof(limpar_senha));
        }
      }
      break;
    case 31:// ----------------------------------------- Dosagem personalizada --------------------------------------------
      if ((x>=menU[0]) && x<=menU[2] && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen = 1;
        clearScreen();
        menuScreen(); 
      }
      else if ((y >= anT[1]) && (y <= anT[3]) && (x >= anT[0]) && (x <= anT[2])) // Volta ao menu dosagem personalizada
      {
        //waitForIt(anT[0], anT[1], anT[2], anT[3]);
        dispScreen = 29;
        clearScreen();
        config_dosagem_personalizada(true);
      }
      else if ((x >= minUT[0]) && (x <= minUT[2]) && (y >= minUT[1]) && (y <= minUT[3])) // Dose diaria mais
      {
        //waitForIt(minUT[0], minUT[1], minUT[2], minUT[3]);
        dose_dosadora_personalizada[dosadora_selecionada] += 0.5;
        if(dose_dosadora_personalizada[dosadora_selecionada] > 999.5)
        {
          dose_dosadora_personalizada[dosadora_selecionada] = 0.5;
        }
        else if(dose_dosadora_personalizada[dosadora_selecionada] <= 9.5)
        {
          myGLCD.setColor(0, 0, 0);                      
          myGLCD.fillRect(100, 45, 185, 67);
        }           

        config_dosagem_personalizada_2();
      }
      else if ((x >= minDT[0]) && (x <= minDT[2]) && (y >= minDT[1]) && (y <= minDT[3])) // Dose diaria menos
      {
        //waitForIt(minDT[0], minDT[1], minDT[2], minDT[3]);
        dose_dosadora_personalizada[dosadora_selecionada] -= 0.5;
        if(dose_dosadora_personalizada[dosadora_selecionada] <0.5)
        {
          dose_dosadora_personalizada[dosadora_selecionada] = 999.5;
        }
        else if(dose_dosadora_personalizada[dosadora_selecionada] <= 9.5)
        {
          myGLCD.setColor(0, 0, 0);                      
          myGLCD.fillRect(100, 45, 185, 67);
        }
        config_dosagem_personalizada_2();
      }
      else  if ((x >= durC[0]) && (x <= durC[2]) && (y >= durC[1]) && (y <= durC[3])) 
      {
        //waitForIt(durC[0], durC[1], durC[2], durC[3]); 
        quantidade_dose_dosadora_personalizada[dosadora_selecionada] += 1;
        if(quantidade_dose_dosadora_personalizada[dosadora_selecionada] > 24)
        {
          quantidade_dose_dosadora_personalizada[dosadora_selecionada] = 1;
        }
        config_dosagem_personalizada_2();
      }
      else if ((x >= durB[0]) && (x <= durB[2]) && (y >= durB[1]) && (y <= durB[3])) 
      {
        //waitForIt(durB[0], durB[1], durB[2], durB[3]);
        quantidade_dose_dosadora_personalizada[dosadora_selecionada] -= 1;
        if(quantidade_dose_dosadora_personalizada[dosadora_selecionada] < 1)
        {
          quantidade_dose_dosadora_personalizada[dosadora_selecionada] = 24;
        }
        config_dosagem_personalizada_2();        
      }
      else  if ((x >= sexT[0]) && (x<= sexT[2]) && (y >= sexT [1]) && (y <= sexT[3])) // Ativar ou desativar modo personalizado
      {
        //waitForIt(sexT[0], sexT[1], sexT[2], sexT[3]);
        if(modo_personalizado_on[dosadora_selecionada] == 0)
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
      else if ((y >= prOK[1]) && (y <= prOK[3]) && (x >= prOK[0]) && (x <= prOK[2])) 
      {
        //waitForIt(prOK[0], prOK[1], prOK[2], prOK[3]); //funcao salvar          
        if((hora_final_dosagem_personalizada[dosadora_selecionada] == hora_inicial_dosagem_personalizada[dosadora_selecionada]) 
          && (minuto_final_dosagem_personalizada[dosadora_selecionada] < (minuto_inicial_dosagem_personalizada[dosadora_selecionada]+10)))
        {
          setFont(SMALL, 255, 0, 0, 0, 0, 0);

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[176])));            
          myGLCD.print(buffer, 20, 110); // "O INTERVALO ENTRE A INICIAL E A FINAL"

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[177]))); 
          myGLCD.print(buffer, 35, 130);
        }
        else if(hora_final_dosagem_personalizada[dosadora_selecionada] < hora_inicial_dosagem_personalizada[dosadora_selecionada])
        {
          setFont(SMALL, 255, 0, 0, 0, 0, 0);

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[178]))); 
          myGLCD.print(buffer, 50, 110);

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_textos[179]))); 
          myGLCD.print(buffer, 100, 130);
        }
        else if((hora_final_dosagem_personalizada[dosadora_selecionada] == hora_inicial_dosagem_personalizada[dosadora_selecionada])
          && (minuto_final_dosagem_personalizada[dosadora_selecionada] >= (minuto_inicial_dosagem_personalizada[dosadora_selecionada] + 10))
          || (hora_final_dosagem_personalizada[dosadora_selecionada] > hora_inicial_dosagem_personalizada[dosadora_selecionada]))
        {
          config_valores_salvar_dosadoras();
          dispScreen =21;
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
      if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen = 1;
        clearScreen();
        menuScreen(); 
      }
      else if ((x>=volT[0]) && (x<=volT[2]) && (y>=volT[1]) && (y<=volT[3]))           // volta ao menu das dosadoras
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen=8;
        clearScreen();
        menu_dosadoras();
      }
      else if ((x>=manU[0]) && (x<=manU[2]) && (y>=manU[1]) && (y<=manU[3]))           // Rever configuração dosagem personalizada
      {
        //waitForIt(manU[0], manU[1], manU[2], manU[3]);
        dispScreen = 34;
        clearScreen();
        rever_dosagem_personalizada();
      }  
      break;     
    case 34:// -------------------------------- Rever configuração das dosadoras personalizado ------------------------------------------
      if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen = 1;
        clearScreen();
        menuScreen();    
      }
      else if ((x>=volT[0]) && (x<=volT[2]) && (y>=volT[1]) && (y<=volT[3]))           // volta ao menu de revisão das dosadoras
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen=32;
        clearScreen();
        rever_configuracao_dosadoras();
      }
      else if ((x>=salV[0]) && (x<=salV[2]) && (y>=salV[1]) && (y<=salV[3]))           // Mais dosadoras
      {
        //waitForIt(salV[0], salV[1], salV[2], salV[3]);
        dispScreen=23;
        clearScreen();
        rever_dosagem_personalizada_2();
      }
      break;
    case 35:// -------------------------------------- Desativar dosadoras ------------------------------------------
      if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen = 1;
        clearScreen();
        menuScreen();    
      }
      else if ((x>=volT[0]) && (x<=volT[2]) && (y>=volT[1]) && (y<=volT[3]))           // volta ao menu desativar dosadoras
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen = 8;
        clearScreen();
        menu_dosadoras();
      }
      else if ((x>=deS[0]) && (x<=deS[2]) && (y>=deS[1]) && (y<=deS[3]))           // volta ao menu desativar dosadoras
      {
        //waitForIt(deS[0], deS[1], deS[2], deS[3]);
        dispScreen = 24;
        clearScreen();
        desativar_dosadoras_2(true);
      }
      else if ((x >= 100) && (x <= 220) && (y >= 45) && (y <= 85))           //Ativar/desatiavr dosadora 1
      {
        //waitForIt(100, 45, 220, 85);

        if(bitRead(ativar_desativar,1) == true)
        {
          bitWrite(ativar_desativar,1, 0);
          desativar_dosadoras();
        }
        else
        {
          desativar_dosadoras(true);
        }          
      }
      else if ((x >= 100) && (x <= 220) && (y >= 115) && (y <= 155))           //Ativar/desatiavr dosadora 2
      {
        //waitForIt(100, 115, 220, 155);

        if(bitRead(ativar_desativar,2) == true)
        {
          bitWrite(ativar_desativar,2, 0);
          desativar_dosadoras();
        }
        else
        {
          desativar_dosadoras(true);
        }          
      }
      else if ((x >= 100) && (x <= 220) && (y >= 185) && (y <= 225))           //Ativar/desatiavr dosadora 3
      {
        //waitForIt(100, 185, 220, 225);

        if(bitRead(ativar_desativar,3) == true)
        {
          bitWrite(ativar_desativar,3, 0);
          desativar_dosadoras();
        }
        else
        {
          desativar_dosadoras(true);
        }          
      }
      else if ((x>=salV[0]) && (x<=salV[2]) && (y>=salV[1]) && (y<=salV[3]))           //Salvar alterações
      {
        //waitForIt(salV[0], salV[1], salV[2], salV[3]);
        if(bitRead(ativar_desativar,1) == false)
        {
          modo_personalizado_on_1= 0;
        }
        else if(bitRead(ativar_desativar,2) == false)
        {
          modo_personalizado_on_2= 0;
        }
        else if(bitRead(ativar_desativar,3) == false)
        {
          modo_personalizado_on_3= 0;
        }
        Salvar_dosadora_EEPROM(); 
        dispScreen = 8;
        clearScreen();
        menu_dosadoras();       
      }
      break;
    case 36: // -------------------------------- Luz noturna --------------------------------------------
      if ((x>=volT[0]) && x<=volT[2] && (y>=volT[1]) && (y<=volT[3]))           // volta a tela configurar leds
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen=40;
        clearScreen();
        config_leds(); 
      }
      else if ((x>=salV[0]) && (x<=salV[2]) && (y>=salV[1]) && (y<=salV[3]))       //Funcao salvar
      {
        //waitForIt(salV[0], salV[1], salV[2], salV[3]);
        MaxI = tMaxI;
        MinI = tMinI;
        dispScreen=40;
        Salvar_luz_noturna_EEPROM();
        clearScreen();
        config_leds();
      } 
      else if ((x>=temM[0]) && (x<=temM[2]))                         // Primeira coluna
      {
        if ((y>=temM[1]) && (y<=temM[3]))                      //press densidade minus
        {
          //waitForIt(temM[0], temM[1], temM[2], temM[3]);
          tMaxI -= 1;
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect (128, 40, 180, 56);//Limpar texto
          luz_noturna();
        }
        else if ((y>=almM[1]) && (y<=almM[3]))                        //press alarm minus
        {
          //waitForIt(almM[0], almM[1], almM[2], almM[3]);
          tMinI -= 1;
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect (128, 140, 180, 156);//Limpar texto
          luz_noturna();
        }
      }
      else if ((x>=temP[0]) && (x<=temP[2]))                             //Segunda coluna
      {
        if ((y>=temP[1]) && (y<=temP[3]))                      //press densidade plus
        {
          //waitForIt(temP[0], temP[1], temP[2], temP[3]);
          tMaxI += 1;
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect (128, 40, 180, 56); //Limpar texto
          luz_noturna();
        }
        else if ((y>=almP[1]) && (y<=almP[3]))                           //press alarm plus
        {
          //waitForIt(almP[0], almP[1], almP[2], almP[3]);
          tMinI += 1;
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect (128, 140, 180, 156);//Limpar texto
          luz_noturna();
        }
      }
      else if ((x>=menU[0]) && x<=menU[2] && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu 1
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen=1;
        clearScreen();
        menuScreen();
      } 
      break;
    case 37: // -------------------------------- Menu 2 -------------------------------------------------------------- 
      if ((x>=menU[0]) && (x<=menU[2]) && (y>=menU[1]) && (y<=menU[3]))           // Volta ao menu 1
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen=1;
        clearScreen();
        menuScreen();
      }
      else if ((x>=tanD[0]) && (x<=tanD[2]) && (y>=tanD[1]) && (y<=tanD[3]))           // Sensores de temperatura
      {
        //waitForIt(tanD[0], tanD[1], tanD[2], tanD[3]);
        dispScreen=41;
        clearScreen();
        procurar_sensores(true);
      }
      break;
    case 38: // -------------------------------- Timers -------------------------------------------------------------- 
      if ((x>=menU[0]) && x<=menU[2] && (y>=menU[1]) && (y<=menU[3]))           // Volta ao menu 1
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen=1;
        clearScreen();
        menuScreen();
      }
      else if ((x >= 7) && (x <= 56) && (y >= 22) && (y <= 238))           // Timer 1 
      {
        //waitForIt(7, 22, 56, 238);
        temporizador = 0;
        dispScreen=39;
        clearScreen();
        config_timer(true);
      }
      else if ((x >= 71) && (x <= 120) && (y >= 22) && (y <= 238))           // Timer 2 
      {
        //waitForIt(71, 22, 120, 238);
        temporizador = 1;
        dispScreen=39;
        clearScreen();
        config_timer(true);
      }
      else if ((x >= 135) && (x <= 184) && (y >= 22) && (y <= 238))           // Timer 3 
      {
        //waitForIt(135, 22, 184, 238);
        temporizador = 2;
        dispScreen=39;
        clearScreen();
        config_timer(true);
      }
      else if ((x >= 199) && (x <= 248) && (y >= 22) && (y <= 238))           // Timer 4 
      {
        //waitForIt(199, 22, 248, 238);
        temporizador = 3;
        dispScreen=39;
        clearScreen();
        config_timer(true);
      } 
      else if ((x >= 263) && (x <= 312) && (y >= 22) && (y <= 238))           // Timer 5 
      {
        //waitForIt(263, 22, 312, 238);
        temporizador = 4;
        dispScreen=39;
        clearScreen();
        config_timer(true);
      }       
      break;
    case 39:// -------------------------------- Configurar timers ------------------------------------------------------ 
      if ((x>=menU[0]) && x<=menU[2] && (y>=menU[1]) && (y<=menU[3]))           // Volta ao menu 2
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);   
        dispScreen=1;
        clearScreen();
        menuScreen();
      }
      else if ((x>=volT[0]) && x<=volT[2] && (y>=volT[1]) && (y<=volT[3]))           // Selecionar timer
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen=38;
        clearScreen();
        TimerScreen(); 
      } 
      else if ((x>=salV[0]) && x<=salV[2] && (y>=salV[1]) && (y<=salV[3]))
      {
        //waitForIt(salV[0], salV[1], salV[2], salV[3]); // Função salvar
        config_valore_salvat_timers();
        dispScreen=38;
        clearScreen();
        TimerScreen();
        salvar_timers_EEPROM();
        bitWrite(temporizador_modificado,(temporizador + 1),1);
      }
      else if ((x >= 21) && (x <= 65) && (y >= 45) && (y <= 88))           // Hora ligar mais 
      {
        //waitForIt(21, 45, 65, 88);
        on_hora[temporizador] += 1;
        if(on_hora[temporizador] > 23)
        {
          on_hora[temporizador] = 0;
        }
        config_timer();
      } 
      else if ((x >= 21) && (x <= 65) && (y >= 135) && (y <= 178))           // Hora ligar menos
      {
        //waitForIt(21, 135, 65, 178);
        on_hora[temporizador] -= 1;
        if(on_hora[temporizador] > 200) // 0 - 1 = 255 pois, byte varia de  0 a 255. 
        {
          on_hora[temporizador] = 23;
        }
        config_timer();
      } 

      else if ((x >= 89) && (x <= 133) && (y >= 45) && (y <= 88))           // Minuto ligar mais 
      {
        //waitForIt(89, 45, 133, 88);
        on_minuto[temporizador] += 1;
        if(on_minuto[temporizador] > 59)
        {
          on_minuto[temporizador] = 0;
        }
        config_timer();
      } 
      else if ((x >= 89) && (x <= 133) && (y >= 135) && (y <= 178))           // Minuto ligar menos
      {
        //waitForIt(89, 135, 133, 178);
        on_minuto[temporizador] -= 1;
        if(on_minuto[temporizador] > 200) // 0 - 1 = 255 pois, byte varia de  0 a 255. 
        {
          on_minuto[temporizador] = 59;
        }
        config_timer();
      }
      else if ((x >= 187) && (x <= 231) && (y >= 45) && (y <= 88))           // Hora desligar mais 
      {
        //waitForIt(187, 45, 231, 88);
        off_hora[temporizador] += 1;
        if(off_hora[temporizador] > 23)
        {
          off_hora[temporizador] = 0;
        }
        config_timer();
      } 
      else if ((x >= 187) && (x <= 231) && (y >= 135) && (y <= 178))           // Hora desligar menos
      {
        //waitForIt(187, 135, 231, 178);
        off_hora[temporizador] -= 1;
        if(off_hora[temporizador] > 200) // 0 - 1 = 255 pois, byte varia de  0 a 255. 
        {
          off_hora[temporizador] = 23;
        }
        config_timer();
      } 

      else if ((x >= 255) && (x <= 299) && (y >= 45) && (y <= 88))           // Minuto desligar mais 
      {
        //waitForIt(255, 45, 299, 88);
        off_minuto[temporizador] += 1;
        if(off_minuto[temporizador] > 59)
        {
          off_minuto[temporizador] = 0;
        }
        config_timer();
      } 
      else if ((x >= 255) && (x <= 299) && (y >= 135) && (y <= 178))           // Minuto desligar menos
      {
        //waitForIt(255, 135, 299, 178);
        off_minuto[temporizador] -= 1;
        if(off_minuto[temporizador] > 200) // 0 - 1 = 255 pois, byte varia de  0 a 255. 
        {
          off_minuto[temporizador] = 59;
        }
        config_timer();
      }
      else  if ((x>=domI[0]-20) && (x<=domI[2]+20) && (y>=domI[1]) && (y<=domI[3]))           // Ativar / desativar timer
      {
        //waitForIt(domI[0]-20, domI[1], domI[2]+20, domI[3]);
        if(temporizador_ativado[temporizador] == 0)
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
      if ((x>=menU[0]) && x<=menU[2] && (y>=menU[1]) && (y<=menU[3]))           // Volta ao menu 1
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);   
        dispScreen=1;
        clearScreen();
        menuScreen();
      }

      else if ((x>=tanD[0]) && x<=tanD[2] && (y>=tanD[1]) && (y<=tanD[3]))           // Testar leds
      {
        //waitForIt(tanD[0], tanD[1], tanD[2], tanD[3]);   
        dispScreen=25;
        clearScreen();
        escolher_teste();
      }
      else if ((x>=tesT[0]) && x<=tesT[2] && (y>=tesT[1]) && (y<=tesT[3]))           // Alterar valores led
      {
        //waitForIt(tesT[0], tesT[1], tesT[2], tesT[3]);   
        dispScreen=28;
        clearScreen();
        escolher_canal(); 
      }
      else if ((x>=temC[0]) && x<=temC[2] && (y>=temC[1]) && (y<=temC[3]))           // Luz Noturna
      {
        //waitForIt(temC[0], temC[1], temC[2], temC[3]);   
        dispScreen=36;
        clearScreen();
        luz_noturna(true);
      }    
      else if ((x>=graF[0]) && x<=graF[2] && (y>=graF[1]) && (y<=graF[3]))           // coolers
      {
        //waitForIt(graF[0], graF[1], graF[2], graF[3]);   
        dispScreen=42;
        clearScreen();
        configurar_coolers(true);
      } 
      else if ((x>=ledW[0]) && x<=ledW[2] && (y>=ledW[1]) && (y<=ledW[3]))           // Reduzir potência
      {
        //waitForIt(ledW[0], ledW[1], ledW[2], ledW[3]);   
        dispScreen=43;
        clearScreen();
        reduzir_potencia(true);
      }
      else if ((x >= tpaA[0]) && (x <= tpaA[2]) && (y >= tpaA[1]) && (y <= tpaA[3]))           // Pre definido
      {
        //waitForIt(tpaA[0], tpaA[1], tpaA[2], tpaA[3]);
        dispScreen = 44;
        clearScreen();
        pre_definido(true); 
      }
      break;
    case 41://---------------------------------------- Configurar leds ----------------------------
      if ((x>=menU[0]) && x<=menU[2] && (y>=menU[1]) && (y<=menU[3]))           // Volta ao menu 2
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);   
        dispScreen=37;
        clearScreen();
        menuScreen_2();
      }
      else if ((x>=busC[0]) && x<=busC[2] && (y>=busC[1]) && (y<=busC[3]))           // Buscar sondas
      {
        //waitForIt(busC[0], busC[1], busC[2], busC[3]);   
        clearScreen();
        procurar_sensores(true);
      }      

      else if ((x>=sonD1[0]) && x<=sonD1[2] && (y>=sonD1[1]) && (y<=sonD1[3]))           // Sonda 1
      {
        //waitForIt(sonD1[0], sonD1[1], sonD1[2], sonD1[3]);   
        if(sonda_associada_1_temp == 1)
        {
          sonda_associada_1_temp = 2;
        }
        else if(sonda_associada_1_temp == 2)
        {
          sonda_associada_1_temp = 3;
        }
        else
        {
          sonda_associada_1_temp = 1;
        }
        procurar_sensores();
      }      
      else if ((x>=sonD2[0]) && x<=sonD2[2] && (y>=sonD2[1]) && (y<=sonD2[3]))           // Sonda 2
      {
        //waitForIt(sonD2[0], sonD2[1], sonD2[2], sonD2[3]);   

        if(sonda_associada_2_temp == 1)
        {
          sonda_associada_2_temp = 2;
        }
        else if(sonda_associada_2_temp == 2)
        {
          sonda_associada_2_temp = 3;
        }

        else
        {
          sonda_associada_2_temp = 1;
        }
        procurar_sensores();
      }      
      else if ((x>=sonD3[0]) && x<=sonD3[2] && (y>=sonD3[1]) && (y<=sonD3[3]))           // Sonda 3
      {
        //waitForIt(sonD3[0], sonD3[1], sonD3[2], sonD3[3]);  

        if(sonda_associada_3_temp == 1)
        {
          sonda_associada_3_temp = 2;
        }
        else if(sonda_associada_3_temp == 2)
        {
          sonda_associada_3_temp = 3;
        }

        else
        {
          sonda_associada_3_temp = 1;
        }
        procurar_sensores();
      }      
      else if ((x>=prOK[0]) && x<=prOK[2] && (y>=prOK[1]) && (y<=prOK[3]))           // Sonda 3
      {
        //waitForIt(prOK[0], prOK[1], prOK[2], prOK[3]);   
        if((sonda_associada_1_temp == sonda_associada_2_temp) || (sonda_associada_1_temp == sonda_associada_3_temp) || (sonda_associada_2_temp == sonda_associada_3_temp))
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

          for(byte i = 0; i < 8; i++)
          {
            if(sonda_associada_1_temp == 1)
            { 
              sensor_agua[i] = sonda1[i];
            }
            else if(sonda_associada_1_temp == 2)
            { 
              sensor_agua[i] = sonda2[i];
            }
            else
            {
              sensor_agua[i] = sonda3[i];
            }
            if(sonda_associada_2_temp == 1)
            { 
              sensor_dissipador[i] = sonda1[i];
            }
            else if(sonda_associada_2_temp == 2)
            { 
              sensor_dissipador[i] = sonda2[i];
            }
            else
            {
              sensor_dissipador[i] = sonda3[i];
            }        

            if(sonda_associada_3_temp == 1)
            { 
              sensor_ambiente[i] = sonda1[i];
            }
            else if(sonda_associada_3_temp == 2)
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
          tempC = (sensors.getTempC(sensor_agua));  // Lê a temperatura da água
          tempH = (sensors.getTempC(sensor_dissipador)); // Lê a temperatura do dissipador.
          tempA = (sensors.getTempC(sensor_ambiente)); // Lê a temperatura do ambiente.
          SaveDallasAddress ();
          dispScreen=37;
          clearScreen();
          menuScreen_2(); 
        }
      }      
      break;
    case 42://---------------------------------------- Configurar coolers ----------------------------     
      if ((x>=volT[0]) && x<=volT[2] && (y>=volT[1]) && (y<=volT[3]))           // volta a tela configurar leds
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen=40;
        clearScreen();
        config_leds(); 
      }
      else if ((x>=salV[0]) && (x<=salV[2]) && (y>=salV[1]) && (y<=salV[3]))       //Função salvar
      {
        //waitForIt(salV[0], salV[1], salV[2], salV[3]);
        HtempMin = HtempMin_temp;
        HtempMax = HtempMax_temp;
        dispScreen=40;
        salvar_coolersEEPROM();
        clearScreen();
        config_leds();
      } 
      else if ((x>=temM[0]) && (x<=temM[2]))                         
      {
        if ((y>=temM[1]) && (y<=temM[3]))                   // Temperatura para velocidade mínima -   
        {
          //waitForIt(temM[0], temM[1], temM[2], temM[3]);
          HtempMin_temp -= 0.1;
          if (HtempMin_temp < 20)
          {
            HtempMin_temp = 35;
          }
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect (128, 40, 180, 56); // Limpar texto
          configurar_coolers();
        }
        else if ((y>=almM[1]) && (y<=almM[3]))                       // Temperatura para velocidade máxima -
        {
          //waitForIt(almM[0], almM[1], almM[2], almM[3]);
          HtempMax_temp -= 0.1;
          if (HtempMax_temp < 36)
          {
            HtempMax_temp = 50;
          }
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect (128, 140, 180, 156);// Limpar texto
          configurar_coolers();
        }
      }
      else if ((x>=temP[0]) && (x<=temP[2]))                          
      {
        if ((y>=temP[1]) && (y<=temP[3]))                      // Temperatura para velocidade mínima +
        {
          //waitForIt(temP[0], temP[1], temP[2], temP[3]);
          HtempMin_temp += 0.1;
          if (HtempMin_temp > 35)
          {
            HtempMin_temp = 20;
          }
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect (128, 40, 180, 56); //Limpar texto
          configurar_coolers();
        }
        else if ((y>=almP[1]) && (y<=almP[3]))                           // Temperatura para velocidade máxima +
        {
          //waitForIt(almP[0], almP[1], almP[2], almP[3]);
          HtempMax_temp += 0.1;
          if (HtempMax_temp > 50)
          {
            HtempMax_temp = 36;
          }
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect (128, 140, 180, 156);//Limpar texto
          configurar_coolers();
        }
      }
      else if ((x>=menU[0]) && x<=menU[2] && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu 1
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen=1;
        clearScreen();
        menuScreen();
      }
      break; 
    case 43://---------------------------------------- Reduziir potência dos leds ---------------------------- 
      if ((x>=menU[0]) && x<=menU[2] && (y>=menU[1]) && (y<=menU[3]))           // volta ao menu 1
      {
        //waitForIt(menU[0], menU[1], menU[2], menU[3]);
        dispScreen=1;
        clearScreen();
        menuScreen();
      }   
      else if ((x>=volT[0]) && x<=volT[2] && (y>=volT[1]) && (y<=volT[3]))           // volta a tela configurar leds
      {
        //waitForIt(volT[0], volT[1], volT[2], volT[3]);
        dispScreen=40;
        clearScreen();
        config_leds(); 
      }
      else if ((x>=salV[0]) && (x<=salV[2]) && (y>=salV[1]) && (y<=salV[3]))       //Função salvar
      {
        //waitForIt(salV[0], salV[1], salV[2], salV[3]);
        tempHR = tempHR_t;
        potR = potR_t;
        dispScreen=40;
        salvar_tempPotEEPROM();
        clearScreen();
        config_leds();
      }
      else if ((x>=tempeC[0]) && (x<=tempeC[2]) && (y>=tempeC[1]) && (y<=tempeC[3]))       //Temperatura +
      {
        //waitForIt(tempeC[0], tempeC[1], tempeC[2], tempeC[3]);
        tempHR_t += 1;
        if (tempHR_t > 99)
        {
          tempHR_t = 30;
        }        
        reduzir_potencia();
      }
      else if ((x>=tempeB[0]) && (x<=tempeB[2]) && (y>=tempeB[1]) && (y<=tempeB[3]))       //Temperatura -
      {
        //waitForIt(tempeB[0], tempeB[1], tempeB[2], tempeB[3]);
        tempHR_t -= 1;
        if (tempHR_t < 30)
        {
          tempHR_t = 99;
        }        
        reduzir_potencia();
      }        
      else if ((x>=potC[0]) && (x<=potC[2]) && (y>=potC[1]) && (y<=potC[3]))       //Potência +
      {
        //waitForIt(potC[0], potC[1], potC[2], potC[3]);
        potR_t += 1;
        if (potR_t > 99)
        {
          potR_t = 1;
        }        
        reduzir_potencia();
      }
      else if ((x>=potB[0]) && (x<=potB[2]) && (y>=potB[1]) && (y<=potB[3]))    //Potência -
      {
        //waitForIt(potB[0], potB[1], potB[2], potB[3]);
        potR_t -= 1;
        if (potR_t < 1) 
        {
          potR_t = 99;
        }        
        reduzir_potencia();
      }
      break; 
    case 44://---------------------------------------- Potência pré-definida para os leds ----------------------------
      if((x >= 205) && (x <= 315) && (y>= 95) && (y <= 180) && (horario_alterado == false))
      {
        myGLCD.setColor(255, 0, 0);
        myGLCD.drawRect(205, 95, 315, 180);
        myGLCD.drawRect(206, 96, 314, 179);
        delay(200);
        clearScreen();
        horario_alterado = true;
        pre_definido();
      }
      if(horario_alterado == false)
      {
        if ((x >= menU[0]) && (x <= menU[2]) && (y >= menU[1]) && (y <= menU[3]))           // volta ao menu 1
        {
          //waitForIt(menU[0], menU[1], menU[2], menU[3]);
          dispScreen=1;
          clearScreen();
          menuScreen();
          ler_predefinido_EEPROM();
        }   
        else if ((x >= volT[0]) && (x <= volT[2]) && (y >= volT[1]) && (y <= volT[3]))           // volta a tela configurar leds
        {
          //waitForIt(volT[0], volT[1], volT[2], volT[3]);
          dispScreen=40;
          clearScreen();
          config_leds();
          ler_predefinido_EEPROM(); 
        }
        else if ((x >= salV[0]) && (x <= salV[2]) && (y >= salV[1]) && (y <= salV[3]))           // volta a tela configurar leds
        {
          //waitForIt(salV[0], salV[1], salV[2], salV[3]);
          dispScreen=40;
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
        else if((x >= 210) && (x <= 310) && (y >= 60) && (y <= 90)) // Ativar / desativar
        { 
          if(pre_definido_ativado_t == 1)
          {
            pre_definido_ativado_t = 0; 
          }
          else
          {
            pre_definido_ativado_t = 1; 
          }
          pre_definido();
        }
        else if((x >= 210) && (x <= 310) && (y >= 25) && (y <= 55)) // Controlar todos
        { 
          if(predefinido_t == 1)
          {
            predefinido_t = 0; 
          }
          else
          {
            predefinido_t = 1; 
          }
          pre_definido();
        }      
        else if((x >= 10) && (x <= 200) && (y >= 25) && (y <= 55)) // Controlar individualmente 10, 25, 200, 55
        { 
          if(predefinido_t == 1)
          {
            predefinido_t = 0; 
          }
          else
          {
            predefinido_t = 1; 
          }
          pre_definido();
        }
        if(pre_definido_ativado_t == 1) // Permite alterar valores somente se a função estiver ativada.
        {
          int m = 0;
          int n = 0;
          if(predefinido_t == 0)// Se predefinido igual a um. Controlar individualmente.
          {

            if((x >= 135) && (x <= 165)) // individual pwm +
            {
              for(m = 0; m < 5; m++)
              {
                n = m * 5;
                if((y >= 60 + (m * 30) + n) && (y <= 90 + (m * 30) + n))
                {
                  if(m == 0)
                  {
                    wled_out_temp += 1;
                  } 
                  else if(m == 1)
                  {
                    bled_out_temp += 1;
                  }
                  else if(m == 2)
                  {
                    rbled_out_temp += 1;
                  }
                  else if(m == 3)
                  {
                    rled_out_temp += 1;
                  }
                  else if(m == 4)
                  {
                    uvled_out_temp += 1;
                  }
                }
              }
              pre_definido();
            }
            else if((x >= 170) && (x <= 200))// individual pwm -
            {
              for(int i = 0; i < 5; i++)
              {
                for(m = 0; m < 5; m++)
                {
                  n = m * 5;
                  if((y >= 60 + (m * 30) + n) && (y <= 90 + (m * 30) + n))
                  {
                    if(m == 0)
                    {
                      wled_out_temp -= 1;
                    } 
                    else if(m == 1)
                    {
                      bled_out_temp -= 1;
                    }
                    else if(m == 2)
                    {
                      rbled_out_temp -= 1;
                    }
                    else if(m == 3)
                    {
                      rled_out_temp -= 1;
                    }
                    else if(m == 4)
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
            if((x >= 210) && (x <= 240) && (y >= 200) && (y <= 230)) // PWM +
            {
              pwm_pre_definido_t += 1;
              pre_definido(); 
            }
            else if((x >= 280) && (x <= 310) && (y >= 200) && (y <= 230)) // PWM -
            {
              pwm_pre_definido_t -= 1;
              pre_definido();
            }
          }
        }
      }
      else // Configurar hora
      {
        if ((x >= 30) && (x <= 55) && (y >= 45) && (y <= 70))           // Hora ligar mais 
        {
          //waitForIt(30, 45, 55, 70);
          led_on_hora_t += 1;
          if(led_on_hora_t > 23)
          {
            led_on_hora_t = 0;
          }
          pre_definido();
        } 
        else if ((x >= 30) && (x <= 55) && (y >= 105) && (y <= 130))           // Hora ligar menos
        {
          //waitForIt(30, 105, 55, 130);
          led_on_hora_t -= 1;
          if(led_on_hora_t > 200) // 0 - 1 = 255 pois, byte varia de  0 a 255. 
          {
            led_on_hora_t = 23;
          }
          pre_definido();
        } 

        else if ((x >= 100) && (x <= 125) && (y >= 45) && (y <= 70))           // Minuto ligar mais 
        {
          //waitForIt(100, 45, 125, 70);
          led_on_minuto_t += 1;
          if(led_on_minuto_t > 59)
          {
            led_on_minuto_t = 0;
          }
          pre_definido();
        } 
        else if ((x >= 100) && (x <= 125) && (y >= 105) && (y <= 130))           // Minuto ligar menos
        {
          //waitForIt(100, 105, 125, 130);
          led_on_minuto_t -= 1;
          if(led_on_minuto_t > 200) // 0 - 1 = 255 pois, byte varia de  0 a 255. 
          {
            led_on_minuto_t = 59;
          }
          pre_definido();
        }
        else if ((x >= 195) && (x <= 220) && (y >= 45) && (y <= 70))           // Hora desligar mais 
        {
          //waitForIt(195, 45, 220, 70);
          led_off_hora_t += 1;
          if(led_off_hora_t > 23)
          {
            led_off_hora_t = 0;
          }
          pre_definido();
        } 
        else if ((x >= 195) && (x <= 220) && (y >= 105) && (y <= 130))           // Hora desligar menos
        {
          //waitForIt(195, 105, 220, 130);
          led_off_hora_t -= 1;
          if(led_off_hora_t > 200) // 0 - 1 = 255 pois, byte varia de  0 a 255. 
          {
            led_off_hora_t = 23;
          }
          pre_definido();
        } 

        else if ((x >= 265) && (x <= 290) && (y >= 45) && (y <= 70))           // Minuto desligar mais 
        {
          //waitForIt(265, 45, 290, 70);
          led_off_minuto_t += 1;
          if(led_off_minuto_t > 59)
          {
            led_off_minuto_t = 0;
          }
          pre_definido();
        } 
        else if ((x >= 265) && (x <= 290) && (y >= 105) && (y <= 130))           // Minuto desligar menos
        {
          //waitForIt(265, 105, 290, 130);
          led_off_minuto_t -= 1;
          if(led_off_minuto_t > 200) // 0 - 1 = 255 pois, byte varia de  0 a 255. 
          {
            led_off_minuto_t = 59;
          }
          pre_definido();
        }
        else if ((x >= 195) && (x <= 220) && (y >= 175) && (y <= 200))           // Amanhecer/anoitecer mais 
        {
          //waitForIt(265, 45, 290, 70);
          amanhecer_anoitecer_t += 1;
          if(amanhecer_anoitecer_t > 240)
          {
            amanhecer_anoitecer_t = 60;
          }
          pre_definido();
        } 
        else if ((x >= 100) && (x <= 125) && (y >= 175) && (y <= 200))           // Amanhecer/anoitecer menos
        {
          //waitForIt(265, 105, 290, 130);
          amanhecer_anoitecer_t -= 1;
          if(amanhecer_anoitecer_t < 60)
          {
            amanhecer_anoitecer_t = 240;
          }
          pre_definido();
        }
        else if ((x >= iniC[0]) && (x <= iniC[2]) && (y >= iniC[1]) && (y <= iniC[3]))           // PRONTO
        {
          //waitForIt(iniC[0], iniC[1], iniC[2], iniC[3]);
          if(((NumMins(led_off_hora_t,led_off_minuto_t) + amanhecer_anoitecer) > 1439) || ((NumMins(led_on_hora_t,led_on_minuto_t) + amanhecer_anoitecer) > 1439))
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
    }
  }
  delay(300);
}




