void processRequest()
{
  char clientline[110];
  char line[110];
  char *requestString;
  char *RequestString;
  byte index = 0;
  EthernetClient client = server.available();
  uint8_t remoteIP[4];
  IPAddress joyreef(178, 255, 75, 60);
  client.getRemoteIP(remoteIP);

  if (client) 
  {  
    Serial.print(remoteIP[0]);
    Serial.print(".");
    Serial.print(remoteIP[1]);
    Serial.print(".");
    Serial.print(remoteIP[2]);
    Serial.print(".");
    Serial.println(remoteIP[3]);

    if(((remoteIP[0] == joyreef[0]) && (remoteIP[1] == joyreef[1]) && (remoteIP[2] == joyreef[2]) && (remoteIP[3] == joyreef[3])) ||
      ((remoteIP[0] == ip[0]) && (remoteIP[1] == ip[1]) && (remoteIP[2] == ip[2])))
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
  char credencial[50];

  EthernetClient client = server.available();

  strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[8]))); // "HTTP/1.1 200 OK"
  client.println(buffer);

  strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[9]))); // "Content-Type: application/json"
  client.println(buffer); 

  client.println();

  pass = strtok(Request, ",");

  base64_decode(pass, pass, strlen(pass)); 
  base64_decode(credencial, Auth1, strlen(Auth1));

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
      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[10]))); // "{\"response\":\"000\"}"
      client.print(buffer); 
    }
    else
    {
      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[11]))); // "{\"response\":\"001\",\"interval\":\""
      client.print(buffer + String((intervalo_tentativa * 60) - ((millis() - intervalo) / 1000)) +  "\"}");
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
  float lunarCycle = moonPhase(t.year, t.mon, t.date); //get a value for the lunar cycle

    switch (ID)
  {
  case 0: // Home
    client.print(F("{\"theatsink\":")); 
    client.print(tempH);
    client.print(F(",\"twater\":")); 
    client.print(tempC);
    client.print(F(",\"tamb\":"));  
    client.print(tempA);
    client.print(F(",\"waterph\":"));  
    client.print(PHA);
    client.print(F(",\"reactorph\":"));  
    client.print(PHR);
    client.print(F(",\"orp\":"));  
    client.print(ORP);
    client.print(F(",\"dens\":"));  
    client.print(DEN);
    client.print(F(",\"wLedW\":"));  
    client.print(LedToPercent(wled_out));
    client.print(F(",\"bLedW\":")); 
    client.print(LedToPercent(bled_out));
    client.print(F(",\"rbLedW\":")); 
    client.print(LedToPercent(rbled_out));
    client.print(F(",\"redLedW\":")); 
    client.print(LedToPercent(rled_out));
    client.print(F(",\"uvLedW\":")); 
    client.print(LedToPercent(uvled_out));
    client.print(F(",\"unix\":")); 
    client.print(rtc.getTimeStamp());
    client.print(F(",\"running\":")); 
    client.print(millis()/1000);
    client.print(F(",\"speed\":")); 
    client.print(LedToPercent(fanSpeed));
    client.print(F(",\"moonPhase\":")); 
    client.print(fase);
    client.print(F(",\"iluminated\":")); 
    client.print(lunarCycle *100);
    client.print(F("}"));
    break; 

  case 1:
    //  Send{case, mode, association}
    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      byte numberOfDevices = 0;
      float temperatura1 = 0;
      float temperatura2 = 0;
      float temperatura3 = 0;

      sensors.begin();
      numberOfDevices = sensors.getDeviceCount();

      for(byte k = 0; k < numberOfDevices; k++)
      {
        // Pesquisar endereços
        if(sensors.getAddress(tempDeviceAddress, k))
        {
          if (k == 0)
          { 
            temperatura1 = sensors.getTempC(tempDeviceAddress);
            for (byte i=0; i<8; i++) 
            {
              sonda1[i] = tempDeviceAddress[i];
            }
          }
          if (k == 1)
          { 
            temperatura2 = sensors.getTempC(tempDeviceAddress);
            for (byte i=0; i<8; i++) 
            {
              sonda2[i] = tempDeviceAddress[i];
            }
          }
          if (k == 2)
          { 
            temperatura3 = sensors.getTempC(tempDeviceAddress);
            for (byte i = 0; i < 8; i++) 
            {
              sonda3[i] = tempDeviceAddress[i];
            }
          }      
        }
      }
      client.print(F("{\"number\":"));
      client.print(numberOfDevices);

      if(numberOfDevices < 2)
      {
        if(sonda_associada_1 == 1)
        {
          sonda_associada_2 = 0;
          sonda_associada_3 = 0;
        }
        else if(sonda_associada_2 == 1)
        {
          sonda_associada_1 = 0;
          sonda_associada_3 = 0;
        }
        else if(sonda_associada_3 == 1)
        {
          sonda_associada_1 = 0;
          sonda_associada_2 = 0;
        }
      }
      client.print(F(",\"p1\":"));  
      client.print(temperatura1);
      client.print(F(",\"p2\":"));  
      client.print(temperatura2);
      client.print(F(",\"p3\":"));  
      client.print(temperatura3);
      client.print(F(",\"ap1\":"));
      client.print(sonda_associada_1);
      client.print(F(",\"ap2\":"));  
      client.print(sonda_associada_2);
      client.print(F(",\"ap3\":"));  
      client.print(sonda_associada_3);
      client.println(F("}"));
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values 
    {
      sonda_associada_1 = atoi(inParse[2]); // 0,3,2,K
      sonda_associada_2 = atoi(inParse[3]);
      sonda_associada_3 = atoi(inParse[4]);

      for(byte i = 0; i < 8; i++)
      {
        if(sonda_associada_1 == 1)
        { 
          sensor_agua[i] = sonda1[i];
        }
        else if(sonda_associada_1 == 2)
        { 
          sensor_agua[i] = sonda2[i];
        }
        else
        {
          sensor_agua[i] = sonda3[i];
        }
        if(sonda_associada_2 == 1)
        { 
          sensor_dissipador[i] = sonda1[i];
        }
        else if(sonda_associada_2 == 2)
        { 
          sensor_dissipador[i] = sonda2[i];
        }
        else
        {
          sensor_dissipador[i] = sonda3[i];
        }        

        if(sonda_associada_3 == 1)
        { 
          sensor_ambiente[i] = sonda1[i];
        }
        else if(sonda_associada_3 == 2)
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
      SaveDallasAddress();

      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer);
    }
    break;

  case 2: //config date & time //Send (case, mode, date, month, year, hour, minute, second, day of week)
    if(atoi(inParse[1]) == 0) // To save time and date send inParse[1] = 1
    {
      client.print(F("{\"date\":\""));
      client.print(t.year);
      client.print(F("-"));   
      client.print(t.mon);  
      client.print(F("-"));
      client.print(t.date);
      client.print(F("\",\"time\":\""));   
      client.print(t.hour);
      client.print(F(":"));  
      client.print(t.min);
      client.print(F(":"));
      client.print(t.sec);
      client.print(F("\"}"));
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

      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer); 
    }
    break;

  case 3:
    if(atoi(inParse[1]) == 0) // Send (case, mode, values)
    {
      client.print(F("{\"hour\":"));
      client.print(hora);
      client.print(F(",\"minute\":"));  
      client.print(minuto);
      client.print(F(",\"duration\":"));  
      client.print(duracaomaximatpa);      
      client.print(F(",\"monday\":"));  
      client.print(segunda);
      client.print(F(",\"tuesday\":"));  
      client.print(terca);
      client.print(F(",\"wednesday\":"));  
      client.print(quarta);
      client.print(F(",\"thursday\":"));  
      client.print(quinta);
      client.print(F(",\"friday\":"));  
      client.print(sexta);
      client.print(F(",\"saturday\":"));  
      client.print(sabado);
      client.print(F(",\"sunday\":"));  
      client.print(domingo);
      client.print(F(",\"status\":"));  
      client.print(bitRead(tpa_status,2));
      client.print(F("}")); 
    }
    if(atoi(inParse[1]) == 1)
    {
      hora = atoi(inParse[2]);
      minuto = atoi(inParse[3]); 
      duracaomaximatpa = atoi(inParse[4]);
      segunda = atoi(inParse[5]);
      terca = atoi(inParse[6]); 
      quarta = atoi(inParse[7]);
      quinta = atoi(inParse[8]);
      sexta = atoi(inParse[9]);
      sabado = atoi(inParse[10]);
      domingo = atoi(inParse[11]);
      SalvartpaEEPROM();
      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer); 
    }
    if(atoi(inParse[1]) == 2)
    {
      bitWrite(tpa_status,2,atoi(inParse[2])); 
      Salvar_erro_tpa_EEPROM();
      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer);
    }
    break;

  case 4:    //individual led test - load first values
    if (atoi(inParse[1]) == 0) //Send (case, mode, wled, rled, rbled, rled, uvled) 
    {
      client.print(F("{\"wLedW\":"));
      client.print(wled_out);
      client.print(F(",\"bLedW\":"));
      client.print(bled_out);
      client.print(F(",\"rbLedW\":")); 
      client.print(rbled_out);
      client.print(F(",\"uvLedW\":")); 
      client.print(uvled_out);
      client.print(F(",\"redLedW\":")); 
      client.print(rled_out);
      client.print(F("}"));      
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to change values
    {
      wled_out_temp = atoi(inParse[2]);
      bled_out_temp = atoi(inParse[3]); 
      rbled_out_temp = atoi(inParse[4]);
      rled_out_temp = atoi(inParse[5]);
      uvled_out_temp = atoi(inParse[6]);
      web_teste = true;
      teste_led_millis = millis();
      teste_em_andamento = true;

      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer); 
    }
    else if (atoi(inParse[1]) == 2)
    {
      web_teste = false;
      teste_em_andamento = false;
      ler_predefinido_EEPROM();

      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer);
    } 
    break;

  case 5: 
    //  Send{case, mode, color, first position}
    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print(F("{\"value0\":"));

      for(byte i = 1 + atoi(inParse[3]); i < 9 + atoi(inParse[3]); i++)
      {
        client.print(cor[atoi(inParse[2])][i - 1]);
        if(i < 8 + atoi(inParse[3]))
        {
          client.print(",\"value" + String(i - atoi(inParse[3])) + "\":");
        }
      }
      client.println(F("}"));
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values temporarily
    {
      for (int i = atoi(inParse[3]); i < atoi(inParse[3]) + 8; i++)
      {
        cont++;
        cor[atoi(inParse[2])][i] = atoi(inParse[3 + cont]);
      }
      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer);
    }
    else if (atoi(inParse[1]) == 2) // mode = 2 to save values to eeprom
    {
      SaveLEDToEEPROM();
      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer);
    }
    else if (atoi(inParse[1]) == 3) // mode = 3 to discard values
    {
      ReadFromEEPROM();
      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer);
    }
    break;
  case 6: //moonlight
    //  Send{case, mode, value}
    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print(F("{\"min\":"));
      client.print(MinI);
      client.print(F(",\"max\":"));  
      client.print(MaxI);
      client.println(F("}"));
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values 
    {
      MinI = atoi(inParse[2]);
      MaxI = atoi(inParse[3]);  
      Salvar_luz_noturna_EEPROM(); 

      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer);
    }  

    break; 

  case 7: //fan led
    //  Send{case, mode, value}
    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print(F("{\"minfan\":"));
      client.print(HtempMin);
      client.print(F(",\"maxfan\":"));  
      client.print(HtempMax);
      client.println(F("}"));
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values 
    {
      HtempMin = atof(inParse[2]);
      HtempMax = atof(inParse[3]);  
      salvar_coolersEEPROM();

      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer);
    }  
    break;  

  case 8: //reduce led power 
    //  Send{case, mode, value}

    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print(F("{\"templimit\":"));
      client.print(tempHR);
      client.print(F(",\"potred\":"));  
      client.print(potR);
      client.println(F("}"));
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values 
    {
      tempHR = atoi(inParse[2]);
      potR = atoi(inParse[3]);  
      salvar_tempPotEEPROM();

      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer);
    }  
    break;   

  case 9: //water temperature control 
    //  Send{case, mode, value}

    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print(F("{\"setTemp\":"));
      client.print(setTempC);
      client.print(F(",\"offTemp\":"));  
      client.print(offTempC);
      client.print(F(",\"alarmTemp\":"));  
      client.print(alarmTempC);
      client.println(F("}"));
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values 
    {
      setTempC = atof(inParse[2]);
      offTempC = atof(inParse[3]); 
      alarmTempC = atof(inParse[4]); 
      SaveTempToEEPROM();

      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer);
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
      client.print(F("{\"calib\":"));
      client.print(fator_calib_dosadora[dosadora_selecionada]);
      client.println(F("}"));
    }
    else if(atoi(inParse[1]) == 1)// send (case, mode, dosing pump selected) mode = 1 to dose
    {
      dosadora_selecionada = atoi(inParse[2]);
      client.print(F("{\"wait\":70}"));
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

      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer);
    }
    break;

  case 12:
    if(atoi(inParse[1]) == 0) // Send (case, mode, dosing pump selected)
    {
      config_valores_dosadoras_temp();
      config_valores_dosadoras_temp2();

      dosadora_selecionada = atoi(inParse[2]);
      client.print(F("{\"hStart\":"));
      client.print(hora_inicial_dosagem_personalizada[dosadora_selecionada]);
      client.print(F(",\"mStart\":"));  
      client.print(minuto_inicial_dosagem_personalizada[dosadora_selecionada]);
      client.print(F(",\"hEnd\":"));  
      client.print(hora_final_dosagem_personalizada[dosadora_selecionada]);
      client.print(F(",\"mEnd\":"));  
      client.print(minuto_final_dosagem_personalizada[dosadora_selecionada]);      
      client.print(F(",\"monday\":"));  
      client.print(segunda_dosagem_personalizada[dosadora_selecionada]);
      client.print(F(",\"tuesday\":"));  
      client.print(terca_dosagem_personalizada[dosadora_selecionada]);
      client.print(F(",\"wednesday\":"));  
      client.print(quarta_dosagem_personalizada[dosadora_selecionada]);
      client.print(F(",\"thursday\":"));  
      client.print(quinta_dosagem_personalizada[dosadora_selecionada]);
      client.print(F(",\"friday\":"));  
      client.print(sexta_dosagem_personalizada[dosadora_selecionada]);
      client.print(F(",\"saturday\":"));  
      client.print(sabado_dosagem_personalizada[dosadora_selecionada]);
      client.print(F(",\"sunday\":"));  
      client.print(domingo_dosagem_personalizada[dosadora_selecionada]);
      client.print(F(",\"quantity\":"));  
      client.print(quantidade_dose_dosadora_personalizada[dosadora_selecionada]); 
      client.print(F(",\"dose\":"));  
      client.print(dose_dosadora_personalizada[dosadora_selecionada]);  
      client.print(F(",\"onoff\":"));  
      client.print(modo_personalizado_on[dosadora_selecionada]);  
      client.println(F("}"));
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

      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer);
    }
    break;

  case 13: //PH control 
    //  Send{case, mode, value}

    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print(F("{\"setPHA\":"));
      client.print(setPHA);
      client.print(F(",\"offPHA\":"));  
      client.print(offPHA);
      client.print(F(",\"alarmPHA\":"));  
      client.print(alarmPHA);
      client.println(F("}"));
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values 
    {
      setPHA = atof(inParse[2]);
      offPHA = atof(inParse[3]); 
      alarmPHA = atof(inParse[4]); 
      SavePHAToEEPROM();

      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer);
    }  
    break; 

  case 14: // Calcium Reactor PH control 
    //  Send{case, mode, value}

    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print(F("{\"setPHR\":"));
      client.print(setPHR);
      client.print(F(",\"offPHR\":"));  
      client.print(offPHR);
      client.print(F(",\"alarmPHR\":"));  
      client.print(alarmPHR);
      client.println(F("}"));
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values 
    {
      setPHR = atof(inParse[2]);
      offPHR = atof(inParse[3]); 
      alarmPHR = atof(inParse[4]); 
      SavePHRToEEPROM();

      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer);
    }  
    break; 

  case 15: // ORP control 
    //  Send{case, mode, value}

    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print(F("{\"setORP\":"));
      client.print(setORP);
      client.print(F(",\"offORP\":"));  
      client.print(offORP);
      client.print(F(",\"alarmORP\":"));  
      client.print(alarmORP);
      client.println(F("}"));
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values 
    {
      setORP = atoi(inParse[2]);
      offORP = atoi(inParse[3]); 
      alarmORP = atoi(inParse[4]); 
      SaveORPToEEPROM();

      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer);
    }  
    break;

  case 16: // Density control 
    //  Send{case, mode, value}

    if (atoi(inParse[1]) == 0) // mode = 0 to read values
    {
      client.print(F("{\"setDEN\":"));
      client.print(setDEN);
      client.print(F(",\"offDEN\":"));  
      client.print(offDEN);
      client.print(F(",\"alarmDEN\":"));  
      client.print(alarmDEN);
      client.println(F("}"));
    }
    else if (atoi(inParse[1]) == 1) // mode = 1 to save values 
    {
      setDEN = atoi(inParse[2]);
      offDEN = atoi(inParse[3]); 
      alarmDEN = atoi(inParse[4]); 
      SaveDENToEEPROM();

      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer);
    }  
    break;

  case 17:
    break;

  case 18:// Timers

    if(atoi(inParse[1]) == 0)// send (case, mode, timer selec.)
    {
      temporizador = atoi(inParse[2]);
      config_valores_timers_temp();
      client.print(F("{\"hStart\":"));
      client.print(on_hora[temporizador]);
      client.print(F(",\"mStart\":"));  
      client.print(on_minuto[temporizador]);
      client.print(F(",\"hEnd\":"));  
      client.print(off_hora[temporizador]);
      client.print(F(",\"mEnd\":"));  
      client.print(off_minuto[temporizador]);
      client.print(F(",\"activated\":"));  
      client.print(temporizador_ativado[temporizador]);
      client.println(F("}"));
    }

    else if(atoi(inParse[1]) == 1)// send (case, mode, timer selected, values) mode = 1 to save
    {  
      web_timer = true;        
      temporizador = atoi(inParse[2]);
      on_hora[temporizador] = atoi(inParse[3]);
      on_minuto[temporizador] = atoi(inParse[4]);
      off_hora[temporizador] = atoi(inParse[5]);  
      off_minuto[temporizador] = atoi(inParse[6]); 
      temporizador_ativado[temporizador] = atoi(inParse[7]);
      config_valores_salvar_timers();   
      salvar_timers_EEPROM();
      bitWrite(temporizador_modificado,(temporizador + 1),1);
      strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
      client.println(buffer);     
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

void enviar_dados()
{
  char dados[6];
  EthernetClient client;
  IPAddress joyreef(178, 255, 75, 58);
  String UserName = Username;

  Serial.println("Connecting...");

  String PostData =
    "{\"userName\":\""+
    UserName+
    "\",\"minute\":\""+
    rtc.getTimeStamp()+
    "\",\"A\":"+ // Temp. da água
  dtostrf(tempC,5,2,dados)+
    ",\"B\":"+ // Temp. dissipador
  dtostrf(tempH,5,2,dados)+
    ",\"C\":"+ // Temp. ambiente
  dtostrf(tempA,5,2,dados)+
    ",\"D\":"+ // PH do aquário
  dtostrf(PHA,4,2,dados)+
    ",\"E\":"+ // PH do reator de cálcio
  dtostrf(PHR,4,2,dados)+
    ",\"F\":"+ // Densidade
  String(DEN)+
    ",\"G\":"+ // ORP
  String(ORP)+
    ",\"H\":"+ // Status chiller, 0 = desligado e 1 = ligado
  String(bitRead(status_parametros,0))+
    ",\"I\":"+ // Status aquecedor, 0 = desligado e 1 = ligado
  String(bitRead(status_parametros,1))+
    ",\"J\":"+ // Status reator de cálcio, 0 = desligado e 1 = ligado
  String(bitRead(status_parametros,5))+
    ",\"K\":"+ // Status ozonizador, 0 = desligado e 1 = ligado
  String(bitRead(status_parametros,7))+
    ",\"L\":"+ // Status reposição de água doce, 0 = desligado e 1 = ligado
  String(bitRead(Status,1))+
    ",\"M\":"+ // Status niveis, 0 = baixo e 1 = normal
  String(nivel_status)+
    ",\"N\":"+ // Status TPA, 0 = desligado e 1 = ligado
  String(bitRead(tpa_status,0))+
    ",\"O\":"+ 
    String(bitRead(temporizador_status,1))+ // Status timer 1, 0 = desligado e 1 = ligado
  ",\"P\":"+ 
    String(bitRead(temporizador_status,2))+ // Status timer 2, 0 = desligado e 1 = ligado
  ",\"Q\":"+
    String(bitRead(temporizador_status,3))+ // Status timer 3, 0 = desligado e 1 = ligado
  ",\"R\":"+ 
    String(bitRead(temporizador_status,4))+ // Status timer 4, 0 = desligado e 1 = ligado
  ",\"S\":"+ 
    String(bitRead(temporizador_status,5))+ // Status timer 5, 0 = desligado e 1 = ligado
  ",\"T\":"+ // Sinaliza falha na TPA
  String(bitRead(tpa_status,2))+ 
    "}";

  Serial.println (FreeRam());

  if (client.connect(joyreef, 80)) 
  {
    Serial.println(">> Connected <<");
    strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "POST /api/temp HTTP/1.1"
    client.println(buffer);

    strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[1]))); // "Host: www.joy-reef.eu"
    client.println(buffer);

    strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[2]))); // "Authorization: Basic "
    client.print(buffer);

    client.println(Auth1);

    strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[3]))); // "Cache-Control: no-cache"
    client.println(buffer);

    strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[4]))); // "Content-Type: application/x-www-form-urlencoded"
    client.println(buffer);

    strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[5]))); // "Connection: close"
    client.println(buffer);

    strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[6]))); // "Content-Length: "
    client.print(buffer);

    client.println(PostData.length());
    client.println();
    client.println(PostData); 

    Serial.println(PostData);

    delay(5);
    client.stop();

  }
  else
  {
    Serial.println("Can't connect!");
  }
}






















