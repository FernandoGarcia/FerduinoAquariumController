#ifdef ETHERNET_SHIELD

void processRequest()
{
  char clientline[110];
  char line[110];
  char *requestString;
  char *RequestString;
  byte index = 0;
  client = server.available();
  uint8_t remoteIP[4];
  client.getRemoteIP(remoteIP);

  if (client)
  {
#ifdef DEBUG
    Serial.print(F("New client: "));
    Serial.print(remoteIP[0]);
    Serial.print(F("."));
    Serial.print(remoteIP[1]);
    Serial.print(F("."));
    Serial.print(remoteIP[2]);
    Serial.print(F("."));
    Serial.println(remoteIP[3]);
#endif

    if (((remoteIP[0] == ferduino[0]) && (remoteIP[1] == ferduino[1]) && (remoteIP[2] == ferduino[2]) && (remoteIP[3] == ferduino[3])) ||
        ((remoteIP[0] == ip[0]) && (remoteIP[1] == ip[1]) && (remoteIP[2] == ip[2])))
    {
      while (client.connected())
      {
        if (client.available())
        {
          char c = client.read();
          if (c != '\n' && c != '\r')
          {
            if (index < 110)
            {
              clientline[index] = c;
              line[index] = c;
              index++;
            }
            continue;
          }
          clientline[index] = 0;
          line[index] = 0;
#ifdef DEBUG
          Serial.println(clientline);
#endif

          if (strstr(clientline, "GET /"))
          {
            if (strstr(clientline, "?"))
            {
              //ignore any page request just look at the GET
              requestString = strstr(clientline, "=") + 1;
              (strstr(clientline, " HTTP"))[0] = 0;
              RequestString = strstr(line, "=") + 1;
              (strstr(line, " HTTP"))[0] = 0;
              readRequest(requestString, RequestString);
            }
          }
          break;
        }
      }
    }
    delay(2);
    client.flush();
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

  client = server.available();

  strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[8]))); // "HTTP/1.1 200 OK"
  client.println(buffer);

  strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[9]))); // "Content-Type: application/json"
  client.println(buffer);

  client.println();

  pass = strtok(Request, ",");

  base64_decode(pass, pass, strlen(pass));
  base64_decode(credencial, Auth1, strlen(Auth1));

  invalidPass = strcmp (pass, credencial);

  requestString = strstr(request, ",") + 1;

  if (invalidPass  == false)
  {
    for (unsigned int j = 0; j < strlen(requestString); j++)
    {
      if (request[j] != 'K')
      {
        inData[j] = requestString[j];
      }
      if (requestString[j] == 'K')
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
    if (tentativa <= maxima_tentativa)
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
    client.flush();
    client.stop();
  }
}

void requestAction(byte ID)
{
  byte cont = 0;
  byte dia;
  client = server.available();
  float lunarCycle = moonPhase(t.year, t.mon, t.date); //get a value for the lunar cycle
  int16_t n;
  char buf[7];

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
      client.print(millis() / 1000);
      client.print(F(",\"speed\":"));
      client.print(LedToPercent(fanSpeed));
      client.print(F(",\"moonPhase\":"));
      client.print(fase);
      client.print(F(",\"iluminated\":"));
      client.print(lunarCycle * 100);
      client.print(F(",\"date\":\""));
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
      client.print(F("\",\"update\":\""));
      client.print(lastUpdate);
      client.print(F("\"}"));
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

        for (byte k = 0; k < numberOfDevices; k++)
        {
          // Pesquisar endereços
          if (sensors.getAddress(tempDeviceAddress, k))
          {
            if (k == 0)
            {
#ifdef USE_FAHRENHEIT
              temperatura1 = sensors.getTempF(tempDeviceAddress);
#else
              temperatura1 = sensors.getTempC(tempDeviceAddress);
#endif

              for (byte i = 0; i < 8; i++)
              {
                sonda1[i] = tempDeviceAddress[i];
              }
            }
            if (k == 1)
            {
#ifdef USE_FAHRENHEIT
              temperatura2 = sensors.getTempF(tempDeviceAddress);
#else
              temperatura2 = sensors.getTempC(tempDeviceAddress);
#endif
              for (byte i = 0; i < 8; i++)
              {
                sonda2[i] = tempDeviceAddress[i];
              }
            }
            if (k == 2)
            {
#ifdef USE_FAHRENHEIT
              temperatura3 = sensors.getTempF(tempDeviceAddress);
#else
              temperatura3 = sensors.getTempC(tempDeviceAddress);
#endif
              for (byte i = 0; i < 8; i++)
              {
                sonda3[i] = tempDeviceAddress[i];
              }
            }
          }
        }
        client.print(F("{\"number\":"));
        client.print(numberOfDevices);

        if (numberOfDevices < 2)
        {
          if (sonda_associada_1 == 1)
          {
            sonda_associada_2 = 0;
            sonda_associada_3 = 0;
          }
          else if (sonda_associada_2 == 1)
          {
            sonda_associada_1 = 0;
            sonda_associada_3 = 0;
          }
          else if (sonda_associada_3 == 1)
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

        for (byte i = 0; i < 8; i++)
        {
          if (sonda_associada_1 == 1)
          {
            sensor_agua[i] = sonda1[i];
          }
          else if (sonda_associada_1 == 2)
          {
            sensor_agua[i] = sonda2[i];
          }
          else
          {
            sensor_agua[i] = sonda3[i];
          }
          if (sonda_associada_2 == 1)
          {
            sensor_dissipador[i] = sonda1[i];
          }
          else if (sonda_associada_2 == 2)
          {
            sensor_dissipador[i] = sonda2[i];
          }
          else
          {
            sensor_dissipador[i] = sonda3[i];
          }

          if (sonda_associada_3 == 1)
          {
            sensor_ambiente[i] = sonda1[i];
          }
          else if (sonda_associada_3 == 2)
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
        tempC = (sensors.getTempF(sensor_agua));  // Lê a temperatura da água
        tempH = (sensors.getTempF(sensor_dissipador)); // Lê a temperatura do dissipador.
        tempA = (sensors.getTempF(sensor_ambiente)); // Lê a temperatura do ambiente.
#else
        tempC = (sensors.getTempC(sensor_agua));  // Lê a temperatura da água
        tempH = (sensors.getTempC(sensor_dissipador)); // Lê a temperatura do dissipador.
        tempA = (sensors.getTempC(sensor_ambiente)); // Lê a temperatura do ambiente.
#endif

        SaveDallasAddress();

        strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
        client.println(buffer);
      }
      break;

    case 2: //config date & time //Send (case, mode, date, month, year, hour, minute, second, day of week)
      if (atoi(inParse[1]) == 0) // To save time and date send inParse[1] = 1
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
      if (atoi(inParse[1]) == 0) // Send (case, mode, values)
      {
        client.print(F("{\"hour\":"));
        client.print(hora);
        client.print(F(",\"minute\":"));
        client.print(minuto);
        client.print(F(",\"duration\":"));
        client.print(duracaomaximatpa);
        client.print(F(",\"monday\":"));
        client.print(semana_e[0]);
        client.print(F(",\"tuesday\":"));
        client.print(semana_e[1]);
        client.print(F(",\"wednesday\":"));
        client.print(semana_e[2]);
        client.print(F(",\"thursday\":"));
        client.print(semana_e[3]);
        client.print(F(",\"friday\":"));
        client.print(semana_e[4]);
        client.print(F(",\"saturday\":"));
        client.print(semana_e[5]);
        client.print(F(",\"sunday\":"));
        client.print(semana_e[6]);
        client.print(F(",\"status\":"));
        client.print(bitRead(tpa_status, 2));
        client.print(F("}"));
      }
      if (atoi(inParse[1]) == 1)
      {
        hora = atoi(inParse[2]);
        minuto = atoi(inParse[3]);
        duracaomaximatpa = atoi(inParse[4]);
        for (byte i = 0; i < 7; i++)
        {
          semana_e[i] = atoi(inParse[i + 5]);
        }
        SalvartpaEEPROM();
        strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
        client.println(buffer);
      }
      if (atoi(inParse[1]) == 2)
      {
        bitWrite(tpa_status, 2, atoi(inParse[2]));
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

        for (byte i = 1 + atoi(inParse[3]); i < 9 + atoi(inParse[3]); i++)
        {
          client.print(cor[atoi(inParse[2])][i - 1]);
          if (i < 8 + atoi(inParse[3]))
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
      tempo_dosagem = map ((atof(inParse[2]) * 2), 0, fator_calib_dosadora_e[dosadora_selecionada], 0, 60000);
      volume_dosado[dosadora_selecionada] += atof(inParse[2]);
      tempo_dosagem /= 2;
      web_dosage = true;
      client.print("{\"wait\":" + String((tempo_dosagem / 1000) + 10) + "}");
      millis_dosagem = millis();
      break;

    case 11:// Calibration

      if (atoi(inParse[1]) == 0) // send (case, mode, dosing pump selected)
      {
        dosadora_selecionada = atoi(inParse[2]);
        config_valores_calib_temp();
        client.print(F("{\"calib\":"));
        client.print(fator_calib_dosadora[dosadora_selecionada]);
        client.println(F("}"));
      }
      else if (atoi(inParse[1]) == 1) // send (case, mode, dosing pump selected) mode = 1 to dose
      {
        dosadora_selecionada = atoi(inParse[2]);
        client.print(F("{\"wait\":70}"));
        web_calibracao = true;
        millis_dosagem = millis();
      }
      else if (atoi(inParse[1]) == 2) // send (case, mode, dosing pump selected, factor of calibration) mode = 2 to save
      {
        dosadora_selecionada = atoi(inParse[2]);
        fator_calib_dosadora[dosadora_selecionada] = atof(inParse[3]);
        for (byte i = 0; i < 6; i++)
        {
          fator_calib_dosadora_e[i] = fator_calib_dosadora[i];
        }
        Salvar_calib_dosadora_EEPROM();

        strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
        client.println(buffer);
      }
      break;

    case 12:
      if (atoi(inParse[1]) == 0) // Send (case, mode, dosing pump selected)
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
      else if (atoi(inParse[1]) == 1) // Send (case, mode, dosing pump selected, values)
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
      for (byte i = 0; i < 6; i++)
      {
        if (i == 0)
        {
          client.print(F("{"));
        }
        client.print(F("\"filepump"));
        client.print(i);
        client.print(F("\":"));
        if (file.open(arquivo[i], O_READ))
        {
          client.print(F("\""));
          while ((n = file.read(buf, sizeof(buf))) > 0)
          {
            client.write(buf);
            client.print(F(","));
          }
          client.print(F("0000\""));
          if (i < 5)
          {
            client.print(F(","));
          }
          else
          {
            client.print(F("}"));
          }
          file.close();
        }
        else
        {
          client.print(F("\"0000\""));
          if (i < 5)
          {
            client.print(F(","));
          }
          else
          {
            client.print(F("}"));
          }
        }
      }
      break;

    case 18:// Timers

      if (atoi(inParse[1]) == 0) // send (case, mode, timer selec.)
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

      else if (atoi(inParse[1]) == 1) // send (case, mode, timer selected, values) mode = 1 to save
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
        bitWrite(temporizador_modificado, (temporizador + 1), 1);
        strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
        client.println(buffer);
      }
      break;

    case 19: // preset mode
      if (atoi(inParse[1]) == 0) // send (case, mode, timer selec.)
      {
        client.print(F("{\"hStart\":"));
        client.print(led_on_hora);
        client.print(F(",\"mStart\":"));
        client.print(led_on_minuto);
        client.print(F(",\"hEnd\":"));
        client.print(led_off_hora);
        client.print(F(",\"mEnd\":"));
        client.print(led_off_minuto);
        client.print(F(",\"activated\":"));
        client.print(pre_definido_ativado);
        client.print(F(",\"preset\":")); // 0 = individual control 1 = control all
        client.print(predefinido);
        client.print(F(",\"wLedW\":"));
        client.print(wled_out_temp);
        client.print(F(",\"bLedW\":"));
        client.print(bled_out_temp);
        client.print(F(",\"rbLedW\":"));
        client.print(rbled_out_temp);
        client.print(F(",\"uvLedW\":"));
        client.print(uvled_out_temp);
        client.print(F(",\"redLedW\":"));
        client.print(rled_out_temp);
        client.print(F(",\"PWM\":"));
        client.print(pwm_pre_definido);
        client.print(F(",\"ramp\":"));
        client.print(amanhecer_anoitecer);
        client.println(F("}"));
      }
      else
      {
        led_on_hora = atoi(inParse[2]);
        led_on_minuto = atoi(inParse[3]);
        led_off_hora = atoi(inParse[4]);
        led_off_minuto = atoi(inParse[5]);
        pre_definido_ativado = atoi(inParse[6]);
        predefinido = atoi(inParse[7]);
        wled_out_temp = atoi(inParse[8]);
        bled_out_temp = atoi(inParse[9]);
        rbled_out_temp = atoi(inParse[10]);
        uvled_out_temp = atoi(inParse[11]);
        rled_out_temp = atoi(inParse[12]);
        pwm_pre_definido = atoi(inParse[13]);
        amanhecer_anoitecer = atoi(inParse[14]);
        Salvar_predefinido_EEPROM();
        strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
        client.println(buffer);
      }
      break;

    case 20: // Automatic feeder
      if (atoi(inParse[1]) == 0) // send (case, mode)
      {
        client.print(F("{\"hStart\":"));
        client.print(horario_alimentacao_e[0]);
        client.print(F(",\"mStart\":"));
        client.print(horario_alimentacao_e[1]);
        client.print(F(",\"hEnd\":"));
        client.print(horario_alimentacao_e[2]);
        client.print(F(",\"mEnd\":"));
        client.print(horario_alimentacao_e[3]);
        client.print(F(",\"monday\":"));
        client.print(dia_alimentacao_e[0]);
        client.print(F(",\"tuesday\":"));
        client.print(dia_alimentacao_e[1]);
        client.print(F(",\"wednesday\":"));
        client.print(dia_alimentacao_e[2]);
        client.print(F(",\"thursday\":"));
        client.print(dia_alimentacao_e[3]);
        client.print(F(",\"friday\":"));
        client.print(dia_alimentacao_e[4]);
        client.print(F(",\"saturday\":"));
        client.print(dia_alimentacao_e[5]);
        client.print(F(",\"sunday\":"));
        client.print(dia_alimentacao_e[6]);
        client.print(F(",\"durationFeeding\":"));
        client.print(duracao_alimentacao);
        client.print(F(",\"durationWaveOff\":"));
        client.print(desligar_wavemaker);
        client.print(F(",\"doses\":"));
        client.print(quantidade_alimentacao);
        client.print(F(",\"feederOnOff\":"));
        client.print(bitRead(alimentacao_wavemaker_on_off, 0));
        client.print(F(",\"waveOnOff\":"));
        client.print(bitRead(alimentacao_wavemaker_on_off, 1));
        client.println(F("}"));
      }
      else if (atoi(inParse[1]) == 1) // send (case, mode, values)
      {
        for (byte i = 0; i < 4; i++)
        {
          horario_alimentacao_e[i] = atoi(inParse[i + 2]);
        }
        for (byte i = 0; i < 7; i++)
        {
          dia_alimentacao_e[i] = atoi(inParse[i + 6]);
        }
        duracao_alimentacao = atoi(inParse[13]);
        desligar_wavemaker = atoi(inParse[14]);
        quantidade_alimentacao = atoi(inParse[15]);
        bitWrite(alimentacao_wavemaker_on_off, 0, atoi(inParse[16]));
        bitWrite(alimentacao_wavemaker_on_off, 1, atoi(inParse[17]));
        salvar_alimentador_EEPROM();
        criar_arquivos_alimentador();
        strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
        client.println(buffer);
      }
      else if (atoi(inParse[1]) == 2) // send (case, mode)
      {
        inicia_alimentacao();
        if (modo_alimentacao == true)
        {
          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
        }
        else
        {
          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[12]))); // "{\"response\":\"stop\"}"
        }
        client.println(buffer);
      }
      break;

    case 21:
      client.print(F("{\"filefeeder\":"));

      if (file.open("FEEDER.TXT", O_READ))
      {
        client.print(F("\""));
        while ((n = file.read(buf, sizeof(buf))) > 0)
        {
          client.write(buf);
          client.print(F(","));
        }
        client.print(F("0000\""));
        client.print(F("}"));
        file.close();
      }
      else
      {
        client.print(F("\"0000\""));
        client.print(F("}"));
      }
      break;
    case 22:
      if (atoi(inParse[1]) == 0) // send (case, mode)
      {
        client.print(F("{\"mode_selected\":"));
        client.print(modo_selecionado);
        client.print(F(",\"PWM1\":"));
        client.print(Pump1PWM_temp);
        client.print(F(",\"PWM2\":"));
        client.print(Pump2PWM_temp);
        client.print(F(",\"period\":"));
        client.print(periodo);
        client.print(F(",\"duration\":"));
        client.print(duracao);
        client.println(F("}"));
      }
      else if (atoi(inParse[1]) == 1)
      {
        modo_selecionado = atoi(inParse[2]);

        if ((modo_selecionado == 1) || (modo_selecionado == 2))
        {
          periodo = atoi(inParse[3]);
        }
        else if ((modo_selecionado == 3) || (modo_selecionado == 4))
        {
          duracao = atoi(inParse[3]);
        }
        else if (modo_selecionado == 5)
        {
          Pump1PWM_temp = atoi(inParse[3]);
          Pump2PWM_temp = atoi(inParse[4]);
        }
        Salvar_wave_EEPROM();
        strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
        client.println(buffer);
      }
      else if (atoi(inParse[1]) == 2)
      {
        modo_selecionado = atoi(inParse[2]);

        if ((modo_selecionado == 1) || (modo_selecionado == 2))
        {
          periodo = atoi(inParse[3]);
        }
        else if ((modo_selecionado == 3) || (modo_selecionado == 4))
        {
          duracao = atoi(inParse[3]);
        }
        else if (modo_selecionado == 5)
        {
          Pump1PWM_temp = atoi(inParse[3]);
          Pump2PWM_temp = atoi(inParse[4]);
        }
        strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
        client.println(buffer);
      }
      else if (atoi(inParse[1]) == 3)
      {
        ler_wave_EEPROM();
        strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[7]))); // "{\"response\":\"ok\"}"
        client.println(buffer);
      }


      break;
  }
}

void enviar_dados()
{
  char dados[6];

#ifdef DEBUG
  Serial.println(F("Connecting..."));
#endif

  if (client.connect(ferduino, 80))
  {
    strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "POST /webcontrol/api/index.php HTTP/1.1"
    client.println(buffer);

    strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[1]))); // "Host: www.ferduino.com"
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

    client.println(strlen(Username) + sizeof(DEN) + sizeof(ORP) + 277);
    client.println();

    client.print(F("{\"userName\":\""));
    client.print(Username);
    client.print(F("\",\"minute\":\""));
    client.print(rtc.getTimeStamp());
    client.print(F("\",\"A\":")); // Temp. da água
    client.print(dtostrf(tempC, 5, 2, dados));
    client.print(F(",\"B\":")); // Temp. dissipador
    client.print(dtostrf(tempH, 5, 2, dados));
    client.print(F(",\"C\":")); // Temp. ambiente
    client.print(dtostrf(tempA, 5, 2, dados));
    client.print(F(",\"D\":")); // PH do aquário
    client.print(dtostrf(PHA, 4, 2, dados));
    client.print(F(",\"E\":")); // PH do reator de cálcio
    client.print(dtostrf(PHR, 4, 2, dados));
    client.print(F(",\"F\":")); // Densidade
    client.print(DEN);
    client.print(F(",\"G\":")); // ORP
    client.print(ORP);
    client.print(F(",\"H\":")); // Status chiller, 0 = desligado e 1 = ligado
    client.print(bitRead(status_parametros, 0));
    client.print(F(",\"I\":")); // Status aquecedor, 0 = desligado e 1 = ligado
    client.print(bitRead(status_parametros, 1));
    client.print(F(",\"J\":")); // Status reator de cálcio, 0 = desligado e 1 = ligado
    client.print(bitRead(status_parametros, 5));
    client.print(F(",\"K\":")); // Status ozonizador, 0 = desligado e 1 = ligado
    client.print(bitRead(status_parametros, 7));
    client.print(F(",\"L\":")); // Status reposição de água doce, 0 = desligado e 1 = ligado
    client.print(bitRead(Status, 1));
    client.print(F(",\"M1\":")); // Status niveis, 0 = baixo e 1 = normal
    client.print(nivel_status1);
    client.print(F(",\"M2\":")); // Status niveis, 0 = baixo e 1 = normal
    client.print(nivel_status2);
    client.print(F(",\"M3\":")); // Status niveis, 0 = baixo e 1 = normal
    client.print(nivel_status3);
    client.print(F(",\"M4\":")); // Status niveis, 0 = baixo e 1 = normal
    client.print(nivel_status4);
    client.print(F(",\"M5\":")); // Status niveis, 0 = baixo e 1 = normal
    client.print(nivel_status5);
    client.print(F(",\"M6\":")); // Status niveis, 0 = baixo e 1 = normal
    client.print(nivel_status6);
    client.print(F(",\"N\":")); // Status TPA, 0 = desligado e 1 = ligado
    client.print(bitRead(tpa_status, 0));
    client.print(F(",\"O\":"));
    client.print(bitRead(temporizador_status, 1)); // Status timer 1, 0 = desligado e 1 = ligado
    client.print(F(",\"P\":"));
    client.print(bitRead(temporizador_status, 2)); // Status timer 2, 0 = desligado e 1 = ligado
    client.print(F(",\"Q\":"));
    client.print(bitRead(temporizador_status, 3)); // Status timer 3, 0 = desligado e 1 = ligado
    client.print(F(",\"R\":"));
    client.print(bitRead(temporizador_status, 4)); // Status timer 4, 0 = desligado e 1 = ligado
    client.print(F(",\"S\":"));
    client.print(bitRead(temporizador_status, 5)); // Status timer 5, 0 = desligado e 1 = ligado
    client.print(F(",\"T\":")); // Sinaliza falha na TPA
    client.print(bitRead(tpa_status, 2));
    client.print(F(",\"U1\":")); // Volume dosado pela dosadora 1
    client.print(volume_dosado[0]);
    client.print(F(",\"U2\":")); // Volume dosado pela dosadora 2
    client.print(volume_dosado[1]);
    client.print(F(",\"U3\":")); // Volume dosado pela dosadora 3
    client.print(volume_dosado[2]);
    client.print(F(",\"U4\":")); // Volume dosado pela dosadora 4
    client.print(volume_dosado[3]);
    client.print(F(",\"U5\":")); // Volume dosado pela dosadora 5
    client.print(volume_dosado[4]);
    client.print(F(",\"U6\":")); // Volume dosado pela dosadora 6
    client.print(volume_dosado[5]);
    client.println(F("}"));

    delay(5);
    client.flush();
    client.stop();

    for (byte i = 0; i < 6; i++)
    {
      volume_dosado[i] = 0;
    }
    notconnected = 0;

#ifdef DEBUG
    Serial.println(F(">> Connected <<"));
#endif
  }
  else
  {
#ifdef DEBUG
    Serial.println(F("Can't connect!"));
#endif

    client.flush();
    client.stop();
#ifdef WATCHDOG
    notconnected++;
    if (notconnected == limite_falha)
    {
#ifdef DEBUG
      Serial.println();
      Serial.print(F("Resetting"));
#endif
      delay(9000);
      notconnected = 0;
    }
#endif
  }
}

#include <utility/w5100.h>
#include <utility/socket.h>

void checkSockStatus()
{
  for (byte i = 0; i < MAX_SOCK_NUM; i++)
  {
    uint8_t s = W5100.readSnSR(i);

    if ((s == 0x13))
    {
      close(i);
/*#ifdef DEBUG
      Serial.print(F("Socket:"));
      Serial.println(i);
#endif*/
    }
  }
}
#endif
