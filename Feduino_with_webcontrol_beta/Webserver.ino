void processRequest()
{
  char clientline[110];
  char line[110];
  char *requestString;
  char *RequestString;
  byte index = 0;
  EthernetClient client = server.available();

  if (client) 
  {
    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
        if (c != '\n' && c != '\r') 
        {
          if(index < 110)
          {
            clientline[index] = c;
            line[index] = c;
            index++;
          }
          continue;
        }
        clientline[index] = 0;    
        line[index] = 0;
        Serial.println(clientline);

        if (strstr(clientline, "GET /"))
        {
          if(strstr(clientline,"?"))
          {
            //ignore any page request just look at the GET
            requestString = strstr(clientline,"=") + 1;
            (strstr(clientline, " HTTP"))[0] = 0;
            RequestString = strstr(line,"=") + 1;
            (strstr(line, " HTTP"))[0] = 0;
            readRequest(requestString, RequestString);
          }  
        }
        break;
      }
    }
    delay(2);
    client.stop();
  }
}

void readRequest(char *request, char *Request)
{
  char inData[50];
  char *requestString;
  byte count = 0;
  char *str;
  char *p;
  boolean invalidPass = true;
  char *pass;
  boolean terminador = false; 

  EthernetClient client = server.available();

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println();

  pass = strtok(Request, ",");
  base64_decode(pass, pass, strlen(pass)); 
  invalidPass = strcmp (pass, credencial);


  requestString = strstr(request,",") + 1;

  if (invalidPass  == false)
  {
    for(int j = 0; j < strlen(requestString); j++)
    { 
      if(request[j]!='K')
      {
        inData[j] = requestString[j];
      }
      if(requestString[j] == 'K')
      {
        inData[j] = '\0';  
        p = inData;
        terminador = true;

        while ((str = strtok_r(p, ",", &p)) != NULL)
        {  
          inParse[count] = str;
          count++;   
        }
      }
    }
  }
  if ((invalidPass  == false) && (tentativa < maxima_tentativa) && (terminador == true))
  {
    tentativa = 0;
    requestAction(atoi(inParse[0]));
  }
  else
  {
    tentativa++;
    if(tentativa <= maxima_tentativa)
    {
      intervalo = millis();
      client.print("{\"response\":\"000\"}"); 
    }
    else
    {
      client.print("{\"response\":\"001\",\"interval\":\"" + String((intervalo_tentativa * 60) - ((millis() - intervalo) / 1000)) +  "\"}");
    }
    delay(2);
    client.stop();
  }  
}

void requestAction(byte ID)
{
  byte cont = 0;
  byte dia;
  EthernetClient client = server.available();

  switch (ID)
  {
  case 0: // Home
    client.print("{\"theatsink\":"); 
    client.print(tempH);
    client.print(",\"twater\":"); 
    client.print(tempC);
    client.print(",\"tamb\":");  
    client.print(tempA);
    client.print(",\"waterph\":");  
    client.print(PHA);
    client.print(",\"reactorph\":");  
    client.print(PHR);
    client.print(",\"orp\":");  
    client.print(ORP);
    client.print(",\"dens\":");  
    client.print(DEN);
    client.print(",\"wLedW\":");  
    client.print(LedToPercent(wled_out));
    client.print(",\"bLedW\":"); 
    client.print(LedToPercent(bled_out));
    client.print(",\"rbLedW\":"); 
    client.print(LedToPercent(rbled_out));
    client.print(",\"redLedW\":"); 
    client.print(LedToPercent(rled_out));
    client.print(",\"uvLedW\":"); 
    client.print(LedToPercent(uvled_out));
    client.print("}");
    break; 

  case 1: // 

    break; 

  case 2: //config date & time //Send (case, mode, date, month, year, hour, minute, second, day of week)
    if(atoi(inParse[1]) == 0) // To save time and date send inParse[1] = 1
    {
      client.print("{\"date\":\"");
      client.print(t.year);
      client.print("-");   
      client.print(t.mon);  
      client.print("-");
      client.print(t.date);
      client.print("\",\"time\":\"");   
      client.print(t.hour);
      client.print(":");  
      client.print(t.min);
      client.print(":");
      client.print(t.sec);
      client.print("\"}");
    }
    else
    { 
      dia = validateDate(atoi(inParse[4]), atoi(inParse[3]), atoi(inParse[2]));
      dia = validateDateForMonth(atoi(inParse[4]), atoi(inParse[3]), atoi(inParse[2]));
      rtc.halt(true);
      rtc.setDate(dia, atoi(inParse[3]), atoi(inParse[2]));
      rtc.setTime(atoi(inParse[5]), atoi(inParse[6]), atoi(inParse[7])); 
      rtc.setDOW(calcDOW(atoi(inParse[4]), atoi(inParse[3]), atoi(inParse[2])));
      rtc.halt(false);
      client.print("{\"response\":\"ok\"}"); 
    }
    break;

  case 3:
    if (atoi(inParse[1]) == 4)
    {
      web_teste = false;
      teste_em_andamento = false;
      ler_predefinido_EEPROM();
      client.print("{\"response\":\"ok\"}"); 
    }
    break;

  case 4:    //individual led test - load first values
    if (atoi(inParse[1]) == 0) //Send (case, mode, wled, rled, rbled, rled, uvled) 
    {
      client.print("{\"wLedW\":");
      client.print(wled_out);
      client.print(",\"bLedW\":");
      client.print(bled_out);
      client.print(",\"rbLedW\":"); 
      client.print(rbled_out);
      client.print(",\"uvLedW\":"); 
      client.print(uvled_out);
      client.print(",\"redLedW\":"); 
      client.print(rled_out);
      client.print("}");      
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to change values
    {
      wled_out_temp = atoi(inParse[2]);
      bled_out_temp = atoi(inParse[3]); 
      rbled_out_temp = atoi(inParse[4]);
      rled_out_temp = atoi(inParse[5]);
      uvled_out_temp = atoi(inParse[6]);
      web_teste = true;
      teste_em_andamento = true;
      client.print("{\"response\":\"ok\"}");  
    } 
    break;

  case 5: 
    //  Send{case, mode, color, first position}
    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print("{\"value0\":");

      for(byte i = 1 + atoi(inParse[3]); i < 9 + atoi(inParse[3]); i++)
      {
        client.print(cor[atoi(inParse[2])][i - 1]);
        if(i < 8 + atoi(inParse[3]))
        {
          client.print(",\"value" + String(i - atoi(inParse[3])) + "\":");
        }
      }
      client.println("}");
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values temporarily
    {
      for (int i = atoi(inParse[3]); i < atoi(inParse[3]) + 8; i++)
      {
        cont++;
        cor[atoi(inParse[2])][i] = atoi(inParse[3 + cont]);
      }
      client.print("{\"response\":\"ok\"}");
    }
    else if (atoi(inParse[1]) == 2) // mode = 2 to save values to eeprom
    {
      SaveLEDToEEPROM();
      client.print("{\"response\":\"ok\"}");
    }
    else if (atoi(inParse[1]) == 3) // mode = 3 to discard values
    {
      ReadFromEEPROM();
      client.print("{\"response\":\"ok\"}");
    }
    break;
  case 6: //moonlight
    //  Send{case, mode, value}
    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print("{\"min\":");
      client.print(MinI);
      client.print(",\"max\":");  
      client.print(MaxI);
      client.println("}");
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values 
    {
      MinI = atoi(inParse[2]);
      MaxI = atoi(inParse[3]);  
      Salvar_luz_noturna_EEPROM(); 

      client.print("{\"response\":\"ok\"}");
    }  

    break; 

  case 7: //fan led
    //  Send{case, mode, value}
    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print("{\"minfan\":");
      client.print(HtempMin);
      client.print(",\"maxfan\":");  
      client.print(HtempMax);
      client.println("}");
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values 
    {
      HtempMin = atof(inParse[2]);
      HtempMax = atof(inParse[3]);  
      salvar_coolersEEPROM();

      client.print("{\"response\":\"ok\"}");
    }  
    break;  

  case 8: //reduce led power 
    //  Send{case, mode, value}

    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print("{\"templimit\":");
      client.print(tempHR);
      client.print(",\"potred\":");  
      client.print(potR);
      client.println("}");
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values 
    {
      tempHR = atoi(inParse[2]);
      potR = atoi(inParse[3]);  
      salvar_tempPotEEPROM();

      client.print("{\"response\":\"ok\"}");
    }  
    break;   

  case 9: //water temperature control 
    //  Send{case, mode, value}

    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print("{\"setTemp\":");
      client.print(setTempC);
      client.print(",\"offTemp\":");  
      client.print(offTempC);
      client.print(",\"alarmTemp\":");  
      client.print(alarmTempC);
      client.println("}");
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values 
    {
      setTempC = atof(inParse[2]);
      offTempC = atof(inParse[3]); 
      alarmTempC = atof(inParse[4]); 
      SaveTempToEEPROM();

      client.print("{\"response\":\"ok\"}");
    }  
    break;

  case 10:// dosage manual
    // send (case, dosing pump selected, dose)
    dosadora_selecionada = atoi(inParse[1]);
    tempo_dosagem = map ((atof(inParse[2])*2), 0, fator_calib_dosadora[dosadora_selecionada], 0, 60000);
    tempo_dosagem /= 2;
    web_dosage = true;
    client.print("{\"wait\":" + String((tempo_dosagem / 1000) + 10) + "}");
    millis_dosagem = millis();
    break; 

  case 11:// Calibration

    if(atoi(inParse[1]) == 0)// send (case, mode, dosing pump selected)
    {
      dosadora_selecionada = atoi(inParse[2]);
      config_valores_calib_temp();
      client.print("{\"calib\":");
      client.print(fator_calib_dosadora[dosadora_selecionada]);
      client.println("}");
    }
    else if(atoi(inParse[1]) == 1)// send (case, mode, dosing pump selected) mode = 1 to dose
    {
      dosadora_selecionada = atoi(inParse[2]);
      client.print("{\"wait\":70}");
      web_calibracao = true;
      millis_dosagem = millis();
    }
    else if(atoi(inParse[1]) == 2)// send (case, mode, dosing pump selected, factor of calibration) mode = 2 to save
    {
      dosadora_selecionada = atoi(inParse[2]);
      fator_calib_dosadora[dosadora_selecionada] = atof(inParse[3]);
      fator_calib_dosadora_1 = fator_calib_dosadora[0];
      fator_calib_dosadora_2 = fator_calib_dosadora[1];
      fator_calib_dosadora_3 = fator_calib_dosadora[2];
      fator_calib_dosadora_4 = fator_calib_dosadora[3];
      fator_calib_dosadora_5 = fator_calib_dosadora[4];
      fator_calib_dosadora_6 = fator_calib_dosadora[5];
      Salvar_calib_dosadora_EEPROM(); 

      client.print("{\"response\":\"ok\"}");
    }
    break;

  case 12:
    if(atoi(inParse[1]) == 0) // Send (case, mode, dosing pump selected)
    {
      config_valores_dosadoras_temp();
      config_valores_dosadoras_temp2();
      
      dosadora_selecionada = atoi(inParse[2]);
      client.print("{\"hStart\":");
      client.print(hora_inicial_dosagem_personalizada[dosadora_selecionada]);
      client.print(",\"mStart\":");  
      client.print(minuto_inicial_dosagem_personalizada[dosadora_selecionada]);
      client.print(",\"hEnd\":");  
      client.print(hora_final_dosagem_personalizada[dosadora_selecionada]);
      client.print(",\"mEnd\":");  
      client.print(minuto_final_dosagem_personalizada[dosadora_selecionada]);      
      client.print(",\"monday\":");  
      client.print(segunda_dosagem_personalizada[dosadora_selecionada]);
      client.print(",\"tuesday\":");  
      client.print(terca_dosagem_personalizada[dosadora_selecionada]);
      client.print(",\"wednesday\":");  
      client.print(quarta_dosagem_personalizada[dosadora_selecionada]);
      client.print(",\"thursday\":");  
      client.print(quinta_dosagem_personalizada[dosadora_selecionada]);
      client.print(",\"friday\":");  
      client.print(sexta_dosagem_personalizada[dosadora_selecionada]);
      client.print(",\"saturday\":");  
      client.print(sabado_dosagem_personalizada[dosadora_selecionada]);
      client.print(",\"sunday\":");  
      client.print(domingo_dosagem_personalizada[dosadora_selecionada]);
      client.print(",\"quantity\":");  
      client.print(quantidade_dose_dosadora_personalizada[dosadora_selecionada]); 
      client.print(",\"dose\":");  
      client.print(dose_dosadora_personalizada[dosadora_selecionada]);  
      client.print(",\"onoff\":");  
      client.print(modo_personalizado_on[dosadora_selecionada]);  
      client.println("}");
    }
    else if(atoi(inParse[1]) == 1) // Send (case, mode, dosing pump selected, values)
    {
      dosadora_selecionada = atoi(inParse[2]);
      hora_inicial_dosagem_personalizada[dosadora_selecionada] = atoi(inParse[3]);
      minuto_inicial_dosagem_personalizada[dosadora_selecionada] = atoi(inParse[4]);
      hora_final_dosagem_personalizada[dosadora_selecionada] = atoi(inParse[5]);  
      minuto_final_dosagem_personalizada[dosadora_selecionada] = atoi(inParse[6]);       
      segunda_dosagem_personalizada[dosadora_selecionada] = atoi(inParse[7]);  
      terca_dosagem_personalizada[dosadora_selecionada] = atoi(inParse[8]); 
      quarta_dosagem_personalizada[dosadora_selecionada] = atoi(inParse[9]);
      quinta_dosagem_personalizada[dosadora_selecionada] = atoi(inParse[10]); 
      sexta_dosagem_personalizada[dosadora_selecionada] = atoi(inParse[11]);  
      sabado_dosagem_personalizada[dosadora_selecionada] = atoi(inParse[12]);
      domingo_dosagem_personalizada[dosadora_selecionada] = atoi(inParse[13]);  
      quantidade_dose_dosadora_personalizada[dosadora_selecionada] = atoi(inParse[14]); 
      dose_dosadora_personalizada[dosadora_selecionada] = atof(inParse[15]);
      modo_personalizado_on[dosadora_selecionada] = atoi(inParse[16]); 
      config_valores_salvar_dosadoras(); 
      criar_arquivos();
      Salvar_dosadora_EEPROM(); 

      client.print("{\"response\":\"ok\"}");
    }
    break;

  case 13: //PH control 
    //  Send{case, mode, value}

    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print("{\"setPHA\":");
      client.print(setPHA);
      client.print(",\"offPHA\":");  
      client.print(offPHA);
      client.print(",\"alarmPHA\":");  
      client.print(alarmPHA);
      client.println("}");
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values 
    {
      setPHA = atof(inParse[2]);
      offPHA = atof(inParse[3]); 
      alarmPHA = atof(inParse[4]); 
      SavePHAToEEPROM();

      client.print("{\"response\":\"ok\"}");
    }  
    break; 

  case 14: // Calcium Reactor PH control 
    //  Send{case, mode, value}

    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print("{\"setPHR\":");
      client.print(setPHR);
      client.print(",\"offPHR\":");  
      client.print(offPHR);
      client.print(",\"alarmPHR\":");  
      client.print(alarmPHR);
      client.println("}");
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values 
    {
      setPHR = atof(inParse[2]);
      offPHR = atof(inParse[3]); 
      alarmPHR = atof(inParse[4]); 
      SavePHRToEEPROM();

      client.print("{\"response\":\"ok\"}");
    }  
    break; 

  case 15: // ORP control 
    //  Send{case, mode, value}

    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print("{\"setORP\":");
      client.print(setORP);
      client.print(",\"offORP\":");  
      client.print(offORP);
      client.print(",\"alarmORP\":");  
      client.print(alarmORP);
      client.println("}");
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values 
    {
      setORP = atoi(inParse[2]);
      offORP = atoi(inParse[3]); 
      alarmORP = atoi(inParse[4]); 
      SaveORPToEEPROM();

      client.print("{\"response\":\"ok\"}");
    }  
    break;

  case 16: // Density control 
    //  Send{case, mode, value}

    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print("{\"setDEN\":");
      client.print(setDEN);
      client.print(",\"offDEN\":");  
      client.print(offDEN);
      client.print(",\"alarmDEN\":");  
      client.print(alarmDEN);
      client.println("}");
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values 
    {
      setDEN = atoi(inParse[2]);
      offDEN = atoi(inParse[3]); 
      alarmDEN = atoi(inParse[4]); 
      SaveDENToEEPROM();

      client.print("{\"response\":\"ok\"}");
    }  
    break;

  case 17:// Send (case,parameter, last value received);
    if(atoi(inParse[1]) == 0)
    {
      check_arquivo_temp_agua(1, atoi(inParse[2]));
    }
    else if(atoi(inParse[1]) == 1)
    {
      check_arquivo_ph_agua(1, atoi(inParse[2]));
    }
    else if(atoi(inParse[1]) == 2)
    {
      check_arquivo_ph_reator(1, atoi(inParse[2])); 
    }
    else if(atoi(inParse[1]) == 3)
    {
      check_arquivo_orp(1, atoi(inParse[2])); 
    }
    else if(atoi(inParse[1]) == 4)
    {
      check_arquivo_densidade(1, atoi(inParse[2])); 
    }
    break;
  }
}


void dosagem_manual()
{
  digitalWrite(dosadora[dosadora_selecionada], HIGH);
  delay(tempo_dosagem);
  digitalWrite(dosadora[dosadora_selecionada], LOW);
}

void calibrar()
{
  digitalWrite(dosadora[dosadora_selecionada], HIGH);
  delay(60000);
  digitalWrite(dosadora[dosadora_selecionada], LOW);
}




