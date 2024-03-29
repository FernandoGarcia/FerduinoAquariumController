#pragma once               // Do not change this line!
#ifdef USE_ETHERNET_SHIELD // Do not change this line
  void requestAction(char *topic, byte *payload, unsigned int length)
#else  // Do not change this line
  void mqttData(void *response)
#endif // Do not change this line
{
  DynamicJsonDocument Json(MQTT_MAX_PACKET_SIZE);
  char pub_message[MQTT_MAX_PACKET_SIZE] = "";
  char _message_[50] = "";
  byte cont = 0;
  byte dia;
  #define COMMAND_SIZE 60
  char clientline[COMMAND_SIZE];
  char inData[COMMAND_SIZE];
  byte index = 0;
  char *str;
  char *p;
  bool terminador = false;
  float lunarCycle = moonPhase(t.year, t.mon, t.date); // get a value for the lunar cycle
  int16_t n;
  char buf[7];
  char PUB_TOPIC[50];

  strcpy(PUB_TOPIC, Username);
  strcat(PUB_TOPIC, "/");
  strcat(PUB_TOPIC, APIKEY);
  strcat(PUB_TOPIC, "/topic/response");

  LOG(F("\nResponse: ")); // Responde aos comandos
  LOGLN(PUB_TOPIC);
  LOG(F("\nNew request: "));

  #ifdef USE_ETHERNET_SHIELD // Do not change this line
    for (unsigned int i = 0; i < length; i++)
    {
      char c = (char)payload[i];
      LOG(c);

      if ((c != '\n') && (c != '\r'))
      {
        if (index < COMMAND_SIZE)
        {
          clientline[index] = c;
          index++;
        }
        continue;
      }
    }

    index = 0;

  #else  // Do not change this line
    ELClientResponse *res = (ELClientResponse *)response;
    String topic = res->popString();
    String message = res->popString();
    message.toCharArray(clientline, sizeof(clientline));

    LOG(F("\nMessage: "));
    LOGLN(message);
  #endif // Do not change this line

  LOGLN();

  for (unsigned int j = 0; j < strlen(clientline); j++)
  {
    if (clientline[j] != 'K')
    {
      inData[j] = clientline[j];
    }
    if (clientline[j] == 'K')
    {
      inData[j - 1] = '\0';
      p = inData;
      terminador = true;

      while ((str = strtok_r(p, ",", &p)) != NULL)
      {
        inParse[index] = str;
        index++;
      }
    }
  }

  if (terminador == true)
  {
    byte ID = atoi(inParse[0]);

    if (executarAgora == true)
    {
      executarAgora = false;
      executandoNuvem = false;
    }

    switch (ID)
    {
      case 0: // Home
        Json[F("theatsink")] = tempH;
        Json[F("twater")] = tempC;
        Json[F("tamb")] = tempA;
        Json[F("waterph")] = PHA;
        Json[F("reactorph")] = PHR;
        Json[F("orp")] = ORP;
        Json[F("dens")] = DEN;
        Json[F("wLedW")] = LedToPercent(wled_out);
        Json[F("bLedW")] = LedToPercent(bled_out);
        Json[F("rbLedW")] = LedToPercent(rbled_out);
        Json[F("redLedW")] = LedToPercent(rled_out);
        Json[F("uvLedW")] = LedToPercent(uvled_out);
        Json[F("running")] = millis() / 1000;
        Json[F("speed")] = LedToPercent(fanSpeed);
        Json[F("moonPhase")] = fase;
        Json[F("iluminated")] = lunarCycle * 100;
        Json[F("date")] = rtc.getDateStr(FORMAT_LONG, FORMAT_LITTLEENDIAN, '-');
        Json[F("time")] = rtc.getTimeStr();
        Json[F("update")] = lastUpdate;
        Json[F("outlet1")] = bitRead(status_parametros, 1); // Aquecedor
        Json[F("outlet2")] = bitRead(status_parametros, 0); // Chiller
        Json[F("outlet3")] = bitRead(status_parametros, 7); // Ozonizador
        Json[F("outlet4")] = bitRead(status_parametros, 5); // Reator de cálcio
        Json[F("outlet5")] = bitRead(Status, 2);            // Skimmer
        Json[F("outlet6")] = bitRead(Status, 3);            // Bomba 1
        Json[F("outlet7")] = bitRead(Status, 4);            // Bomba 2
        Json[F("outlet8")] = bitRead(Status, 5);            // Bomba 3
        Json[F("outlet9")] = bitRead(Status, 1);            // Reposição

        strcpy(_message_, "[");

        for (byte i = 0; i < 10; i++)
        {
          itoa(horaNuvem[i], buf, 10);
          strcat(_message_, buf);

          if (i < 9)
          {
            strcat(_message_, ",");
          }
        }

        strcat(_message_, "]");

        Json[F("horaNuvem")] = _message_;
        Json[F("haveraNuvem")] = haveraNuvem;
        Json[F("haveraRelampago")] = haveraRelampago;

        serializeJson(Json, pub_message);
        MQTT.publish(PUB_TOPIC, pub_message, false);
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

          Json[F("number")] = numberOfDevices;

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

          Json[F("p1")] = temperatura1;
          Json[F("p2")] = temperatura2;
          Json[F("p3")] = temperatura3;
          Json[F("ap1")] = sonda_associada_1;
          Json[F("ap2")] = sonda_associada_2;
          Json[F("ap3")] = sonda_associada_3;

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1)         // mode = 1 to save values
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
          sensors.requestTemperatures();                   // Chamada para todos os sensores.
          #ifdef USE_FAHRENHEIT
            tempC = (sensors.getTempF(sensor_agua));       // Lê a temperatura da água
            tempH = (sensors.getTempF(sensor_dissipador)); // Lê a temperatura do dissipador.
            tempA = (sensors.getTempF(sensor_ambiente));   // Lê a temperatura do ambiente.
          #else
            tempC = (sensors.getTempC(sensor_agua));       // Lê a temperatura da água
            tempH = (sensors.getTempC(sensor_dissipador)); // Lê a temperatura do dissipador.
            tempA = (sensors.getTempC(sensor_ambiente));   // Lê a temperatura do ambiente.
          #endif

          SaveDallasAddress();

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 2:                      // config date & time //Send (case, mode, date, month, year, hour, minute, second, day of week)
        if (atoi(inParse[1]) == 0) // To save time and date send inParse[1] = 1
        {
          Json[F("date")] = rtc.getDateStr(FORMAT_LONG, FORMAT_BIGENDIAN, '-');
          Json[F("time")] = rtc.getTimeStr();

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else
        {
          dia = rtc.validateDate(atoi(inParse[4]), atoi(inParse[3]), atoi(inParse[2]));
          dia = rtc.validateDateForMonth(atoi(inParse[4]), atoi(inParse[3]), atoi(inParse[2]));
          rtc.halt(true);
          rtc.setDate(dia, atoi(inParse[3]), atoi(inParse[2]));
          rtc.setTime(atoi(inParse[5]), atoi(inParse[6]), atoi(inParse[7]));
          rtc.halt(false);

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 3:
        if (atoi(inParse[1]) == 0) // Send (case, mode, values)
        {
          Json[F("hour")] = hora;
          Json[F("minute")] = minuto;
          Json[F("duration")] = duracaomaximatpa;
          Json[F("monday")] = semana_e[0];
          Json[F("tuesday")] = semana_e[1];
          Json[F("wednesday")] = semana_e[2];
          Json[F("thursday")] = semana_e[3];
          Json[F("friday")] = semana_e[4];
          Json[F("saturday")] = semana_e[5];
          Json[F("sunday")] = semana_e[6];
          Json[F("status")] = bitRead(tpa_status, 2);

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
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
          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        if (atoi(inParse[1]) == 2)
        {
          bitWrite(tpa_status, 2, atoi(inParse[2]));
          Salvar_erro_tpa_EEPROM();
          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;
      case 4:                      // individual led test - load first values
        if (atoi(inParse[1]) == 0) // Send (case, mode, wled, rled, rbled, rled, uvled)
        {
          Json[F("wLedW")] = wled_out;
          Json[F("bLedW")] = bled_out;
          Json[F("rbLedW")] = rbled_out;
          Json[F("uvLedW")] = uvled_out;
          Json[F("redLedW")] = rled_out;

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
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

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        else if (atoi(inParse[1]) == 2)
        {
          web_teste = false;
          teste_em_andamento = false;
          ler_predefinido_EEPROM();

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 5:
        //  Send{case, mode, color, first position}
        if (atoi(inParse[1]) == 0) // mode = 0 to read values
        {
          strcpy(pub_message, "{\"value0\":");

          for (byte i = 1 + atoi(inParse[3]); i < 9 + atoi(inParse[3]); i++)
          {
            itoa(cor[atoi(inParse[2])][i - 1], buf, 10);
            strcat(pub_message, buf);
            if (i < 8 + atoi(inParse[3]))
            {
              strcat(pub_message, ",\"value");
              itoa(i - atoi(inParse[3]), buf, 10);
              strcat(pub_message, buf);
              strcat(pub_message, "\":");
            }
          }
          strcat(pub_message, "}");
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // mode = 1 to save values temporarily
        {
          for (int i = atoi(inParse[3]); i < atoi(inParse[3]) + 8; i++)
          {
            cont++;
            cor[atoi(inParse[2])][i] = atoi(inParse[3 + cont]);
          }

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        else if (atoi(inParse[1]) == 2) // mode = 2 to save values to eeprom
        {
          SaveLEDToEEPROM();

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        else if (atoi(inParse[1]) == 3) // mode = 3 to discard values
        {
          ReadFromEEPROM();

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;
      case 6:                      // moonlight
        //  Send{case, mode, value}
        if (atoi(inParse[1]) == 0) // mode = 0 to read values
        {
          Json[F("min")] = MinI;
          Json[F("max")] = MaxI;

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // mode = 1 to save values
        {
          MinI = atoi(inParse[2]);
          MaxI = atoi(inParse[3]);
          Salvar_luz_noturna_EEPROM();

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }

        break;

      case 7:                      // fan led
        //  Send{case, mode, value}
        if (atoi(inParse[1]) == 0) // mode = 0 to read values
        {
          Json[F("minfan")] = HtempMin;
          Json[F("maxfan")] = HtempMax;

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // mode = 1 to save values
        {
          HtempMin = atof(inParse[2]);
          HtempMax = atof(inParse[3]);
          salvar_coolersEEPROM();

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 8: // reduce led power
        //  Send{case, mode, value}

        if (atoi(inParse[1]) == 0) // mode = 0 to read values
        {
          Json[F("templimit")] = tempHR;
          Json[F("potred")] = potR;

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // mode = 1 to save values
        {
          tempHR = atoi(inParse[2]);
          potR = atoi(inParse[3]);
          salvar_tempPotEEPROM();

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 9: // water temperature control
        //  Send{case, mode, value}

        if (atoi(inParse[1]) == 0) // mode = 0 to read values
        {
          Json[F("setTemp")] = setTempC;
          Json[F("offTemp")] = offTempC;
          Json[F("alarmTemp")] = alarmTempC;

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // mode = 1 to save values
        {
          setTempC = atof(inParse[2]);
          offTempC = atof(inParse[3]);
          alarmTempC = atof(inParse[4]);
          SaveTempToEEPROM();

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 10: // dosage manual
        // send (case, dosing pump selected, dose)
        dosadora_selecionada = atoi(inParse[1]);
        tempo_dosagem = map((atof(inParse[2]) * 2), 0, fator_calib_dosadora_e[dosadora_selecionada], 0, 60000UL);
        volume_dosado[dosadora_selecionada] += atof(inParse[2]);
        tempo_dosagem /= 2;
        web_dosage = true;
        Json[F("wait")] = String((tempo_dosagem / 1000) + 10);

        serializeJson(Json, pub_message);
        MQTT.publish(PUB_TOPIC, pub_message, false);

        millis_dosagem = millis();
        break;

      case 11:                     // Calibration

        if (atoi(inParse[1]) == 0) // send (case, mode, dosing pump selected)
        {
          dosadora_selecionada = atoi(inParse[2]);
          config_valores_calib_temp();
          Json[F("calib")] = fator_calib_dosadora[dosadora_selecionada];

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // send (case, mode, dosing pump selected) mode = 1 to dose
        {
          dosadora_selecionada = atoi(inParse[2]);
          Json[F("wait")] = 70;

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);

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

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 12:
        if (atoi(inParse[1]) == 0) // Send (case, mode, dosing pump selected)
        {
          config_valores_dosadoras_temp();
          config_valores_dosadoras_temp2();

          dosadora_selecionada = atoi(inParse[2]);

          Json[F("hStart")] = hora_inicial_dosagem_personalizada[dosadora_selecionada];
          Json[F("mStart")] = minuto_inicial_dosagem_personalizada[dosadora_selecionada];
          Json[F("hEnd")] = hora_final_dosagem_personalizada[dosadora_selecionada];
          Json[F("mEnd")] = minuto_final_dosagem_personalizada[dosadora_selecionada];
          Json[F("monday")] = segunda_dosagem_personalizada[dosadora_selecionada];
          Json[F("tuesday")] = terca_dosagem_personalizada[dosadora_selecionada];
          Json[F("wednesday")] = quarta_dosagem_personalizada[dosadora_selecionada];
          Json[F("thursday")] = quinta_dosagem_personalizada[dosadora_selecionada];
          Json[F("friday")] = sexta_dosagem_personalizada[dosadora_selecionada];
          Json[F("saturday")] = sabado_dosagem_personalizada[dosadora_selecionada];
          Json[F("sunday")] = domingo_dosagem_personalizada[dosadora_selecionada];
          Json[F("quantity")] = quantidade_dose_dosadora_personalizada[dosadora_selecionada];
          Json[F("dose")] = dose_dosadora_personalizada[dosadora_selecionada];
          Json[F("onoff")] = modo_personalizado_on[dosadora_selecionada];

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
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
          selecionar_SPI(SD_CARD);
          criar_arquivos();
          Salvar_dosadora_EEPROM();

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 13: // PH control
        //  Send{case, mode, value}

        if (atoi(inParse[1]) == 0) // mode = 0 to read values
        {
          Json[F("setPHA")] = setPHA;
          Json[F("offPHA")] = offPHA;
          Json[F("alarmPHA")] = alarmPHA;

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // mode = 1 to save values
        {
          setPHA = atof(inParse[2]);
          offPHA = atof(inParse[3]);
          alarmPHA = atof(inParse[4]);
          SavePHAToEEPROM();

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 14: // Calcium Reactor PH control
        //  Send{case, mode, value}

        if (atoi(inParse[1]) == 0) // mode = 0 to read values
        {
          Json[F("setPHR")] = setPHR;
          Json[F("offPHR")] = offPHR;
          Json[F("alarmPHR")] = alarmPHR;

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // mode = 1 to save values
        {
          setPHR = atof(inParse[2]);
          offPHR = atof(inParse[3]);
          alarmPHR = atof(inParse[4]);
          SavePHRToEEPROM();

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 15: // ORP control
        //  Send{case, mode, value}

        if (atoi(inParse[1]) == 0) // mode = 0 to read values
        {
          Json[F("setORP")] = setORP;
          Json[F("offORP")] = offORP;
          Json[F("alarmORP")] = alarmORP;

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // mode = 1 to save values
        {
          setORP = atoi(inParse[2]);
          offORP = atoi(inParse[3]);
          alarmORP = atoi(inParse[4]);
          SaveORPToEEPROM();

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 16: // Density control
        //  Send{case, mode, value}

        if (atoi(inParse[1]) == 0) // mode = 0 to read values
        {
          Json[F("setDEN")] = setDEN;
          Json[F("offDEN")] = offDEN;
          Json[F("alarmDEN")] = alarmDEN;

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // mode = 1 to save values
        {
          setDEN = atoi(inParse[2]);
          offDEN = atoi(inParse[3]);
          alarmDEN = atoi(inParse[4]);
          SaveDENToEEPROM();

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 17:
        strcpy(pub_message, "{\"filepump");
        itoa(atoi(inParse[2]), buf, 10);
        strcat(pub_message, buf);
        strcat(pub_message, "\":");
        selecionar_SPI(SD_CARD);

        if (file.open(arquivo[atoi(inParse[2])], O_READ))
        {
          strcat(pub_message, "\"");
          while ((n = file.read(buf, sizeof(buf))) > 0)
          {
            strcat(pub_message, buf);
            strcat(pub_message, ",");
          }
          strcat(pub_message, "0000\"}");
          file.close();
        }
        else
        {
          strcat(pub_message, "\"0000\"}");
        }

        selecionar_SPI(ETHER_CARD);
        MQTT.publish(PUB_TOPIC, pub_message, false);
        break;

      case 18:                     // Timers

        if (atoi(inParse[1]) == 0) // send (case, mode, timer selec.)
        {
          temporizador = atoi(inParse[2]);
          config_valores_timers_temp();

          Json[F("hStart")] = on_hora[temporizador];
          Json[F("mStart")] = on_minuto[temporizador];
          Json[F("hEnd")] = off_hora[temporizador];
          Json[F("mEnd")] = off_minuto[temporizador];
          Json[F("activated")] = temporizador_ativado[temporizador];

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
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

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 19:                     // preset mode
        if (atoi(inParse[1]) == 0) // send (case, mode, timer selec.)
        {
          Json[F("hStart")] = led_on_hora;
          Json[F("mStart")] = led_on_minuto;
          Json[F("hEnd")] = led_off_hora;
          Json[F("mEnd")] = led_off_minuto;
          Json[F("activated")] = pre_definido_ativado;
          Json[F("preset")] = predefinido;
          Json[F("wLedW")] = wled_out_temp;
          Json[F("bLedW")] = bled_out_temp;
          Json[F("rbLedW")] = rbled_out_temp;
          Json[F("uvLedW")] = uvled_out_temp;
          Json[F("redLedW")] = rled_out_temp;
          Json[F("PWM")] = pwm_pre_definido;
          Json[F("ramp")] = amanhecer_anoitecer;

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
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

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 20:                     // Automatic feeder
        if (atoi(inParse[1]) == 0) // send (case, mode)
        {
          Json[F("hStart")] = horario_alimentacao_e[0];
          Json[F("mStart")] = horario_alimentacao_e[1];
          Json[F("hEnd")] = horario_alimentacao_e[2];
          Json[F("mEnd")] = horario_alimentacao_e[3];
          Json[F("monday")] = dia_alimentacao_e[0];
          Json[F("tuesday")] = dia_alimentacao_e[1];
          Json[F("wednesday")] = dia_alimentacao_e[2];
          Json[F("thursday")] = dia_alimentacao_e[3];
          Json[F("friday")] = dia_alimentacao_e[4];
          Json[F("saturday")] = dia_alimentacao_e[5];
          Json[F("sunday")] = dia_alimentacao_e[6];
          Json[F("durationFeeding")] = duracao_alimentacao;
          Json[F("durationWaveOff")] = desligar_wavemaker;
          Json[F("doses")] = quantidade_alimentacao;
          Json[F("feederOnOff")] = bitRead(alimentacao_wavemaker_on_off, 0);
          Json[F("waveOnOff")] = bitRead(alimentacao_wavemaker_on_off, 1);

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
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
          selecionar_SPI(SD_CARD);
          criar_arquivos_alimentador();

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        else if (atoi(inParse[1]) == 2) // send (case, mode)
        {
          inicia_alimentacao();
          if (modo_alimentacao == true)
          {
            strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          }
          else
          {
            strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[1]))); // "{\"response\":\"stop\"}"
          }

          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 21:
        strcpy(pub_message, "{\"filefeeder\":");
        selecionar_SPI(SD_CARD);

        if (file.open("FEEDER.TXT", O_READ))
        {
          strcat(pub_message, "\"");
          while ((n = file.read(buf, sizeof(buf))) > 0)
          {
            strcat(pub_message, buf);
            strcat(pub_message, ",");
          }
          strcat(pub_message, "0000\"}");
          file.close();
        }
        else
        {
          strcat(pub_message, "\"0000\"}");
        }

        selecionar_SPI(ETHER_CARD);
        MQTT.publish(PUB_TOPIC, pub_message, false);
        break;

      case 22:
        if (atoi(inParse[1]) == 0) // send (case, mode)
        {
          Json[F("mode_selected")] = modo_selecionado;
          Json[F("PWM1")] = Pump1PWM_temp;
          Json[F("PWM2")] = Pump2PWM_temp;
          Json[F("period")] = periodo;
          Json[F("duration")] = duracao;

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
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

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
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

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        else if (atoi(inParse[1]) == 3)
        {
          ler_wave_EEPROM();

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 23:
        if (atoi(inParse[1]) == 0) // send (case, mode)
        {
          strcpy(pub_message, "{");
          for (byte i = 0; i < 9; i++)
          {
            strcat(pub_message, "\"mode");
            itoa(i + 1, buf, 10);
            strcat(pub_message, buf);
            strcat(pub_message, "\":");
            itoa(outlets[i], buf, 10);
            strcat(pub_message, buf);
            if (i < 8)
            {
              strcat(pub_message, ",");
            }
          }
          strcat(pub_message, "}");

          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1)
        {
          salvar_outlets_EEPROM();
          outlets_settings = false;

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        else if (atoi(inParse[1]) == 2)
        {
          outlets[atoi(inParse[2])] = atoi(inParse[3]);
          outlets_changed[atoi(inParse[2])] = true;
          outlets_millis = millis();
          outlets_settings = true;

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        else if (atoi(inParse[1]) == 3)
        {
          byte k = EEPROM.read(840);

          if (k != 66)
          {
            for (byte i = 0; i < 9; i++)
            {
              outlets[i] = 0;
            }
          }
          else
          {
            ler_outlets_EEPROM();
          }
          outlets_settings = false;

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 24:
        if (atoi(inParse[1]) == 0)
        {
          Json[F("White")] = desativarNuvemCanal[0];
          Json[F("Blue")] = desativarNuvemCanal[1];
          Json[F("RoyalBlue")] = desativarNuvemCanal[2];
          Json[F("Red")] = desativarNuvemCanal[3];
          Json[F("UV")] = desativarNuvemCanal[4];
          Json[F("Moon")] = desativarNuvemCanal[5];
          Json[F("every")] = nuvemCadaXdias;
          Json[F("cloud")] = probNuvemRelampago[0];
          Json[F("lightning")] = probNuvemRelampago[1];
          Json[F("quantMin")] = quantDuracaoMinMaxNuvem[0];
          Json[F("quantMax")] = quantDuracaoMinMaxNuvem[1];
          Json[F("durationMin")] = quantDuracaoMinMaxNuvem[2];
          Json[F("durationMax")] = quantDuracaoMinMaxNuvem[3];
          Json[F("WhiteR")] = desativarRelampagoCanal[0];
          Json[F("BlueR")] = desativarRelampagoCanal[1];
          Json[F("RoyalBlueR")] = desativarRelampagoCanal[2];
          Json[F("RedR")] = desativarRelampagoCanal[3];
          Json[F("UVR")] = desativarRelampagoCanal[4];
          Json[F("MoonR")] = desativarRelampagoCanal[5];
          Json[F("durationMinL")] = duracaoMinMaxRelampago[0];
          Json[F("durationMaxL")] = duracaoMinMaxRelampago[1];

          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1)
        {
          nuvemCadaXdias = atoi(inParse[2]);
          probNuvemRelampago[0] = atoi(inParse[3]);       // Probabilidade de nuvem
          desativarNuvemCanal[0] = atoi(inParse[4]);      // Ativar/desativar canal branco
          desativarNuvemCanal[1] = atoi(inParse[5]);      // Ativar/desativar canal azul
          desativarNuvemCanal[2] = atoi(inParse[6]);      // Ativar/desativar canal azul royal
          desativarNuvemCanal[3] = atoi(inParse[7]);      // Ativar/desativar canal vermelho
          desativarNuvemCanal[4] = atoi(inParse[8]);      // Ativar/desativar canal uv
          quantDuracaoMinMaxNuvem[0] = atoi(inParse[9]);  // Quantidade mínma de nuvens
          quantDuracaoMinMaxNuvem[1] = atoi(inParse[10]); // Quantidade máxima de nuvens
          quantDuracaoMinMaxNuvem[2] = atoi(inParse[11]); // Duração mínima da nuvem
          quantDuracaoMinMaxNuvem[3] = atoi(inParse[12]); // Duração máxima da nuvem
          probNuvemRelampago[1] = atoi(inParse[13]);      // Probabilidade de relâmpago
          desativarNuvemCanal[5] = atoi(inParse[14]);     // Ativar/desativar canal da luz noturna
          desativarRelampagoCanal[0] = atoi(inParse[15]); // Ativar/desativar relampago no canal branco
          desativarRelampagoCanal[1] = atoi(inParse[16]); // Ativar/desativar relampago no canal azul
          desativarRelampagoCanal[2] = atoi(inParse[17]); // Ativar/desativar relampago no canal azul royal
          desativarRelampagoCanal[3] = atoi(inParse[18]); // Ativar/desativar relampago no canal vermelho
          desativarRelampagoCanal[4] = atoi(inParse[19]); // Ativar/desativar relampago no canal uv
          desativarRelampagoCanal[5] = atoi(inParse[20]); // Ativar/desativar relampago no canal da luz noturna
          duracaoMinMaxRelampago[0] = atoi(inParse[21]);  // Duração mínima do relâmpago
          duracaoMinMaxRelampago[1] = atoi(inParse[22]);  // Duração máxima do relâmpago

          Salvar_clima_EEPROM();
          probabilidadeNuvem();                                               // Calcula a probabilidade de ocorrer nuvens.

          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        else if (atoi(inParse[1]) == 2)
        {
          executandoNuvem = true;
          inicioNuvem = true;
          executarAgora = true;
          millis_nuvem = millis();

          Json[F("wait")] = String(duracaoNuvem + duracaoRelampago);
          serializeJson(Json, pub_message);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        break;

      case 25:

        break;

      case 26:
        if (atoi(inParse[1]) == 0)
        {
          #ifdef TILT_HYDROMETER
            DEN = atof(inParse[2]);
          #else
            DEN_AUX = atof(inParse[2]);
          #endif
          temp_AUX = atof(inParse[3]);

          LOG(F("Density: "));
          LOGLN(DEN);
          LOG(F("Density aux: "));
          LOGLN(DEN_AUX);
          LOG(F("Temperature aux: "));
          LOGLN(temp_AUX);
          strcpy_P(buffer, (char *)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      default: // Break the loop if function called doesn't match.
        break;
    } // switch(ID)

    if (measureJson(Json) > 2)
    {
      LOG(F("\nJSON size: "));
      LOGLN(measureJson(Json));
      LOGLN(F("JSON:"));
      #ifdef DEBUG
        serializeJson(Json, Serial);
      #endif
      LOGLN();
    }
    if ((strlen(pub_message) > 0) && (measureJson(Json) <= 2))
    {
      LOG(F("\nMessage size: "));
      LOGLN(strlen(pub_message));
      LOGLN(F("Message:"));
      LOGLN(pub_message);
    }
    if ((strlen(buffer) > 0) && (strlen(pub_message) == 0) && (measureJson(Json) <= 2))
    {
      LOG(F("\nBuffer size: "));
      LOGLN(strlen(buffer));
      LOGLN(F("Buffer:"));
      LOGLN(buffer);
    }
    LOGLN();
  } // if (terminador == true)
}   // void

void enviar_dados()
{
  DynamicJsonDocument Json(MQTT_MAX_PACKET_SIZE);
  char pub_message[MQTT_MAX_PACKET_SIZE];
  char LOG_TOPIC[50];

  strcpy(LOG_TOPIC, "log/");
  strcat(LOG_TOPIC, Username);
  strcat(LOG_TOPIC, "/");
  strcat(LOG_TOPIC, APIKEY);

  LOG(F("\nLog: ")); // Envia dados
  LOGLN(LOG_TOPIC);

  #ifdef USE_ETHERNET_SHIELD // Do not change this line
    if (MQTT.connected())
  #else  // Do not change this line
    if (MQTT_connected == true)
  #endif // Do not change this line
  {
    Json[F("userName")] = Username;
    Json[F("minute")] = rtc.getTimeStamp();
    Json[F("A")] = tempC;                           // Temp. da água
    Json[F("B")] = tempH;                           // Temp. dissipador
    Json[F("C")] = tempA;                           // Temp. ambiente
    Json[F("D")] = PHA;                             // PH do aquário
    Json[F("E")] = PHR;                             // PH do reator de cálcio
    Json[F("F")] = DEN;                             // Densidade
    Json[F("G")] = ORP;                             // ORP
    Json[F("H")] = bitRead(status_parametros, 0);   // Status chiller, 0 = desligado e 1 = ligado
    Json[F("I")] = bitRead(status_parametros, 1);   // Status aquecedor, 0 = desligado e 1 = ligado
    Json[F("J")] = bitRead(status_parametros, 5);   // Status reator de cálcio, 0 = desligado e 1 = ligado
    Json[F("K")] = bitRead(status_parametros, 7);   // Status ozonizador, 0 = desligado e 1 = ligado
    Json[F("L")] = bitRead(Status, 1);              // Status reposição de água doce, 0 = desligado e 1 = ligado
    Json[F("M1")] = nivel_status1;                  // Status nível sensor 1, 0 = baixo e 1 = normal
    Json[F("M2")] = nivel_status2;                  // Status nível sensor 2, 0 = baixo e 1 = normal
    Json[F("M3")] = nivel_status3;                  // Status nível sensor 3, 0 = baixo e 1 = normal
    Json[F("M4")] = nivel_status4;                  // Status nível sensor 4, 0 = baixo e 1 = normal
    Json[F("M5")] = nivel_status5;                  // Status nível sensor 5, 0 = baixo e 1 = normal
    Json[F("M6")] = nivel_status6;                  // Status nível sensor 6, 0 = baixo e 1 = normal
    Json[F("N")] = bitRead(tpa_status, 0);          // Status TPA, 0 = desligado e 1 = ligado
    Json[F("O")] = bitRead(temporizador_status, 1); // Status timer 1, 0 = desligado e 1 = ligado
    Json[F("P")] = bitRead(temporizador_status, 2); // Status timer 2, 0 = desligado e 1 = ligado
    Json[F("Q")] = bitRead(temporizador_status, 3); // Status timer 3, 0 = desligado e 1 = ligado
    Json[F("R")] = bitRead(temporizador_status, 4); // Status timer 4, 0 = desligado e 1 = ligado
    Json[F("S")] = bitRead(temporizador_status, 5); // Status timer 5, 0 = desligado e 1 = ligado
    Json[F("T")] = bitRead(tpa_status, 2);          // Sinaliza falha na TPA
    Json[F("U1")] = volume_dosado[0];               // Volume dosado pela dosadora 1
    Json[F("U2")] = volume_dosado[1];               // Volume dosado pela dosadora 2
    Json[F("U3")] = volume_dosado[2];               // Volume dosado pela dosadora 3
    Json[F("U4")] = volume_dosado[3];               // Volume dosado pela dosadora 4
    Json[F("U5")] = volume_dosado[4];               // Volume dosado pela dosadora 5
    Json[F("U6")] = volume_dosado[5];               // Volume dosado pela dosadora 6
    Json[F("V1")] = bitRead(erro_dosagem, 0);       // Erro dosagem dosadora 1
    Json[F("V2")] = bitRead(erro_dosagem, 1);       // Erro dosagem dosadora 2
    Json[F("V3")] = bitRead(erro_dosagem, 2);       // Erro dosagem dosadora 3
    Json[F("V4")] = bitRead(erro_dosagem, 3);       // Erro dosagem dosadora 4
    Json[F("V5")] = bitRead(erro_dosagem, 4);       // Erro dosagem dosadora 5
    Json[F("V6")] = bitRead(erro_dosagem, 5);       // Erro dosagem dosadora 6

    serializeJson(Json, pub_message);
    MQTT.publish(LOG_TOPIC, pub_message, false);

    for (byte i = 0; i < 6; i++)
    {
      volume_dosado[i] = 0;
    }
    notconnected = 0;

    LOG(F("\nJSON size: "));
    LOGLN(measureJson(Json));
    LOGLN(F("JSON:"));
    #ifdef DEBUG
      serializeJson(Json, Serial);
    #endif
    LOGLN("");
  }
  else
  {
    LOGLN(F("\nNot connected!"));

    notconnected++;
    if ((notconnected >= (limite_falha - 2)) && (notconnected < limite_falha))
    {
      #ifdef USE_ETHERNET_SHIELD // Do not change this line!
        start_ethernet();
      #else  // Do not change this line!
        sincronizar();
      #endif // Do not change this line!

      #ifndef WATCHDOG
        notconnected = 0;
      #endif
    }

    #ifdef WATCHDOG
      if (notconnected == limite_falha)
      {
        LOG(F("\nResetting"));
        delay(9000);
      }
    #endif
  }
}

#ifdef USE_ETHERNET_SHIELD // Do not change this line
  void reconnect()
  {
    byte i = 0;
    char SUB_TOPIC[50];
    char CLIENT_ID[20];

    strcpy(SUB_TOPIC, Username);
    strcat(SUB_TOPIC, "/");
    strcat(SUB_TOPIC, APIKEY);
    strcat(SUB_TOPIC, "/topic/command");

    strcpy(CLIENT_ID, "ID: ");
    strcat(CLIENT_ID, Username);

    selecionar_SPI(ETHER_CARD); // Seleciona disposito SPI que será utilizado.

    while ((!MQTT.connected()) && (i < 3))
    {
      LOG(F("\nAttempting MQTT connection... "));
      if (MQTT.connect(CLIENT_ID, Username, APIKEY))
      {
        LOGLN(F("Connected!"));
        LOG(F("\nCommand: ")); // Recebe os commandos
        LOGLN(SUB_TOPIC);
        MQTT.subscribe(SUB_TOPIC);
      }
      else
      {
        int Status = MQTT.state();

        switch (Status)
        {
          case -4:
            LOGLN(F("Connection timeout"));
            break;

          case -3:
            LOGLN(F("Connection lost"));
            break;

          case -2:
            LOGLN(F("Connect failed"));
            break;

          case -1:
            LOGLN(F("Disconnected"));
            break;

          case 1:
            LOGLN(F("Bad protocol"));
            break;

          case 2:
            LOGLN(F("Bad client ID"));
            break;

          case 3:
            LOGLN(F("Unavailable"));
            break;

          case 4:
            LOGLN(F("Bad credentials"));
            break;

          case 5:
            LOGLN(F("Unauthorized"));
            break;
        }
      }
      i++;
      delay(200);
    }
  }
#endif // Do not change this line
