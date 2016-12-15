#ifdef ETHERNET_SHIELD

#ifndef USE_ESP8266 // Do not change this line

void requestAction(char* topic, byte* payload, unsigned int length)
#else // Do not change this line
void mqttData(void* response)
#endif // Do not change this line
{
  StaticJsonBuffer<MQTT_MAX_PACKET_SIZE> jsonBuffer;
  JsonObject& Json = jsonBuffer.createObject();
  char pub_message[MQTT_MAX_PACKET_SIZE] = "";
  byte cont = 0;
  byte dia;
#define COMMAND_SIZE  50
  char clientline[COMMAND_SIZE];
  char inData[COMMAND_SIZE];
  byte index = 0;
  char *str;
  char *p;
  boolean terminador = false;
  float lunarCycle = moonPhase(t.year, t.mon, t.date); //get a value for the lunar cycle
  int16_t n;
  char buf[7];
  char PUB_TOPIC[50];

  strcpy(PUB_TOPIC, Username);
  strcat(PUB_TOPIC, "/");
  strcat(PUB_TOPIC, APIKEY);
  strcat(PUB_TOPIC, "/topic/response");

#ifdef DEBUG
  Serial.println();
  Serial.print(F("Response: ")); // Responde aos comandos
  Serial.println(PUB_TOPIC);
  Serial.print(F("New request: "));
#endif

#ifndef USE_ESP8266 // Do not change this line
  for (int i = 0; i < length; i++)
  {
    char c = (char)payload[i];
#ifdef DEBUG
    Serial.print(c);
#endif
    if (c != '\n' && c != '\r')
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

#else // Do not change this line
  ELClientResponse *res = (ELClientResponse *)response;
  String topic = res->popString();
#ifdef DEBUG
  //Serial.print(F("Topic: "));
  //Serial.println(topic);
#endif
  String message = res->popString();
  message.toCharArray(clientline, sizeof(clientline));
#ifdef DEBUG
  Serial.print(F("Message: "));
  Serial.println(message);
#endif
#endif // Do not change this line

#ifdef DEBUG
  Serial.println();
#endif

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
        Json[F("unix")] = rtc.getTimeStamp();
        Json[F("running")] = millis() / 1000;
        Json[F("speed")] = LedToPercent(fanSpeed);
        Json[F("moonPhase")] = fase;
        Json[F("iluminated")] = lunarCycle * 100;
        Json[F("date")] = String(t.year) + "-" + String (t.mon) + "-" + String (t.date);
        Json[F("time")] = String (t.hour) + ":" + String (t.min) + ":" + String (t.sec);
        Json[F("update")] = lastUpdate;

        Json.printTo(pub_message, Json.measureLength() + 1);
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

          Json.printTo(pub_message, Json.measureLength() + 1);
          MQTT.publish(PUB_TOPIC, pub_message, false);
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

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 2: //config date & time //Send (case, mode, date, month, year, hour, minute, second, day of week)
        if (atoi(inParse[1]) == 0) // To save time and date send inParse[1] = 1
        {
          Json[F("date")] = String(t.year) + "-" + String(t.mon) + "-" + String(t.date);
          Json[F("time")] = String(t.hour) + ":" + String(t.min) + ":" + String(t.sec);

          Json.printTo(pub_message, Json.measureLength() + 1);
          MQTT.publish(PUB_TOPIC, pub_message, false);
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

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
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

          Json.printTo(pub_message, Json.measureLength() + 1);
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
          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        if (atoi(inParse[1]) == 2)
        {
          bitWrite(tpa_status, 2, atoi(inParse[2]));
          Salvar_erro_tpa_EEPROM();
          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;
      case 4:    //individual led test - load first values
        if (atoi(inParse[1]) == 0) //Send (case, mode, wled, rled, rbled, rled, uvled)
        {
          Json[F("wLedW")] = wled_out;
          Json[F("bLedW")] = bled_out;
          Json[F("rbLedW")] = rbled_out;
          Json[F("uvLedW")] = uvled_out;
          Json[F("redLedW")] = rled_out;

          Json.printTo(pub_message, Json.measureLength() + 1);
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

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        else if (atoi(inParse[1]) == 2)
        {
          web_teste = false;
          teste_em_andamento = false;
          ler_predefinido_EEPROM();

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
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

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        else if (atoi(inParse[1]) == 2) // mode = 2 to save values to eeprom
        {
          SaveLEDToEEPROM();

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        else if (atoi(inParse[1]) == 3) // mode = 3 to discard values
        {
          ReadFromEEPROM();

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;
      case 6: //moonlight
        //  Send{case, mode, value}
        if (atoi(inParse[1]) == 0) // mode = 0 to read values
        {
          Json[F("min")] = MinI;
          Json[F("max")] = MaxI;

          Json.printTo(pub_message, Json.measureLength() + 1);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // mode = 1 to save values
        {
          MinI = atoi(inParse[2]);
          MaxI = atoi(inParse[3]);
          Salvar_luz_noturna_EEPROM();

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }

        break;

      case 7: //fan led
        //  Send{case, mode, value}
        if (atoi(inParse[1]) == 0) // mode = 0 to read values
        {
          Json[F("minfan")] = HtempMin;
          Json[F("maxfan")] = HtempMax;

          Json.printTo(pub_message, Json.measureLength() + 1);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // mode = 1 to save values
        {
          HtempMin = atof(inParse[2]);
          HtempMax = atof(inParse[3]);
          salvar_coolersEEPROM();

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 8: //reduce led power
        //  Send{case, mode, value}

        if (atoi(inParse[1]) == 0) // mode = 0 to read values
        {
          Json[F("templimit")] = tempHR;
          Json[F("potred")] = potR;

          Json.printTo(pub_message, Json.measureLength() + 1);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // mode = 1 to save values
        {
          tempHR = atoi(inParse[2]);
          potR = atoi(inParse[3]);
          salvar_tempPotEEPROM();

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 9: //water temperature control
        //  Send{case, mode, value}

        if (atoi(inParse[1]) == 0) // mode = 0 to read values
        {
          Json[F("setTemp")] = setTempC;
          Json[F("offTemp")] = offTempC;
          Json[F("alarmTemp")] = alarmTempC;

          Json.printTo(pub_message, Json.measureLength() + 1);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // mode = 1 to save values
        {
          setTempC = atof(inParse[2]);
          offTempC = atof(inParse[3]);
          alarmTempC = atof(inParse[4]);
          SaveTempToEEPROM();

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 10:// dosage manual
        // send (case, dosing pump selected, dose)
        dosadora_selecionada = atoi(inParse[1]);
        tempo_dosagem = map ((atof(inParse[2]) * 2), 0, fator_calib_dosadora_e[dosadora_selecionada], 0, 60000);
        volume_dosado[dosadora_selecionada] += atof(inParse[2]);
        tempo_dosagem /= 2;
        web_dosage = true;
        Json[F("wait")] = String((tempo_dosagem / 1000) + 10);

        Json.printTo(pub_message, Json.measureLength() + 1);
        MQTT.publish(PUB_TOPIC, pub_message, false);

        millis_dosagem = millis();
        break;

      case 11:// Calibration

        if (atoi(inParse[1]) == 0) // send (case, mode, dosing pump selected)
        {
          dosadora_selecionada = atoi(inParse[2]);
          config_valores_calib_temp();
          Json[F("calib")] = fator_calib_dosadora[dosadora_selecionada];

          Json.printTo(pub_message, Json.measureLength() + 1);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // send (case, mode, dosing pump selected) mode = 1 to dose
        {
          dosadora_selecionada = atoi(inParse[2]);
          Json[F("wait")] = 70;

          Json.printTo(pub_message, Json.measureLength() + 1);
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

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
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

          Json.printTo(pub_message, Json.measureLength() + 1);
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
          criar_arquivos();
          Salvar_dosadora_EEPROM();

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 13: //PH control
        //  Send{case, mode, value}

        if (atoi(inParse[1]) == 0) // mode = 0 to read values
        {
          Json[F("setPHA")] = setPHA;
          Json[F("offPHA")] = offPHA;
          Json[F("alarmPHA")] = alarmPHA;

          Json.printTo(pub_message, Json.measureLength() + 1);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // mode = 1 to save values
        {
          setPHA = atof(inParse[2]);
          offPHA = atof(inParse[3]);
          alarmPHA = atof(inParse[4]);
          SavePHAToEEPROM();

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
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

          Json.printTo(pub_message, Json.measureLength() + 1);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // mode = 1 to save values
        {
          setPHR = atof(inParse[2]);
          offPHR = atof(inParse[3]);
          alarmPHR = atof(inParse[4]);
          SavePHRToEEPROM();

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
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

          Json.printTo(pub_message, Json.measureLength() + 1);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // mode = 1 to save values
        {
          setORP = atoi(inParse[2]);
          offORP = atoi(inParse[3]);
          alarmORP = atoi(inParse[4]);
          SaveORPToEEPROM();

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
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

          Json.printTo(pub_message, Json.measureLength() + 1);
          MQTT.publish(PUB_TOPIC, pub_message, false);
        }
        else if (atoi(inParse[1]) == 1) // mode = 1 to save values
        {
          setDEN = atoi(inParse[2]);
          offDEN = atoi(inParse[3]);
          alarmDEN = atoi(inParse[4]);
          SaveDENToEEPROM();

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 17:
        strcpy(pub_message, "{\"filepump");
        itoa(atoi(inParse[2]), buf, 10);
        strcat(pub_message, buf);
        strcat(pub_message, "\":");
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
          strcat(pub_message, "0000}");
        }
        MQTT.publish(PUB_TOPIC, pub_message, false);
        break;

      case 18:// Timers

        if (atoi(inParse[1]) == 0) // send (case, mode, timer selec.)
        {
          temporizador = atoi(inParse[2]);
          config_valores_timers_temp();

          Json[F("hStart")] = on_hora[temporizador];
          Json[F("mStart")] = on_minuto[temporizador];
          Json[F("hEnd")] = off_hora[temporizador];
          Json[F("mEnd")] = off_minuto[temporizador];
          Json[F("activated")] = temporizador_ativado[temporizador];

          Json.printTo(pub_message, Json.measureLength() + 1);
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

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 19: // preset mode
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

          Json.printTo(pub_message, Json.measureLength() + 1);
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

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 20: // Automatic feeder
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

          Json.printTo(pub_message, Json.measureLength() + 1);
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
          criar_arquivos_alimentador();

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        else if (atoi(inParse[1]) == 2) // send (case, mode)
        {
          inicia_alimentacao();
          if (modo_alimentacao == true)
          {
            strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          }
          else
          {
            strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[1]))); // "{\"response\":\"stop\"}"
          }

          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;

      case 21:
        strcpy(pub_message, "{\"filefeeder\":");

        if (file.open("FEEDER.TXT", O_READ))
        {
          strcat(pub_message, "\"");
          while ((n = file.read(buf, sizeof(buf))) > 0)
          {
            strcat(pub_message, buf);
            strcat(pub_message, ",");
          }
          strcat(pub_message, "0000\"");
          strcat(pub_message, "}");
          file.close();
        }
        else
        {
          strcat(pub_message, "\"0000\"");
          strcat(pub_message, "}");
        }

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

          Json.printTo(pub_message, Json.measureLength() + 1);
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

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
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

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        else if (atoi(inParse[1]) == 3)
        {
          ler_wave_EEPROM();

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
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

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        else if (atoi(inParse[1]) == 2)
        {
          outlets[atoi(inParse[2])] = atoi(inParse[3]);
          outlets_changed[atoi(inParse[2])] = true;
          outlets_millis = millis();
          outlets_settings = true;

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
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

          strcpy_P(buffer, (char*)pgm_read_word_near(&(tabela_strings[0]))); // "{\"response\":\"ok\"}"
          MQTT.publish(PUB_TOPIC, buffer, false);
        }
        break;
    }// switch(ID)

#ifdef DEBUG
    if (Json.measureLength() > 2)
    {
      Serial.print(F("JSON size: "));
      Serial.println(Json.measureLength());
      Serial.println(F("JSON:"));
      Json.prettyPrintTo(Serial);
      Serial.println();
    }
    if ((strlen(pub_message) > 0) && (Json.measureLength() <= 2))
    {
      Serial.print(F("Message size: "));
      Serial.println(strlen(pub_message));
      Serial.println(F("Message:"));
      Serial.println(pub_message);
    }
    if ((strlen(buffer) > 0) && (strlen(pub_message) == 0) && (Json.measureLength() <= 2))
    {
      Serial.print(F("Buffer size: "));
      Serial.println(strlen(buffer));
      Serial.println(F("Buffer:"));
      Serial.println(buffer);
    }
    Serial.println();
#endif
  }// if (terminador == true)
} //void

void enviar_dados()
{
  StaticJsonBuffer<MQTT_MAX_PACKET_SIZE> jsonBuffer;
  JsonObject& Json = jsonBuffer.createObject();
  char pub_message[MQTT_MAX_PACKET_SIZE];
  char LOG_TOPIC[50];

  strcpy(LOG_TOPIC, "log/");
  strcat(LOG_TOPIC, Username);
  strcat(LOG_TOPIC, "/");
  strcat(LOG_TOPIC, APIKEY);

#ifdef DEBUG
  Serial.println();
  Serial.print(F("Log: ")); // Envia dados
  Serial.println(LOG_TOPIC);
  Serial.println(F("Connecting..."));
#endif

#ifndef USE_ESP8266 // Do not change this line
  if (!MQTT.connected())
  {
    reconnect();
  }

  if (MQTT.connected())
#else // Do not change this line

  sincronizar();

  if (MQTT_connected == true)
#endif // Do not change this line
  {
    Json[F("userName")] = Username;
    Json[F("minute")] = rtc.getTimeStamp();
    Json[F("A")] = tempC; // Temp. da água
    Json[F("B")] = tempH; // Temp. dissipador
    Json[F("C")] = tempA; // Temp. ambiente
    Json[F("D")] = PHA; // PH do aquário
    Json[F("E")] = PHR; // PH do reator de cálcio
    Json[F("F")] = DEN; // Densidade
    Json[F("G")] = ORP; // ORP
    Json[F("H")] = bitRead(status_parametros, 0); // Status chiller, 0 = desligado e 1 = ligado
    Json[F("I")] = bitRead(status_parametros, 1); // Status aquecedor, 0 = desligado e 1 = ligado
    Json[F("J")] = bitRead(status_parametros, 5); // Status reator de cálcio, 0 = desligado e 1 = ligado
    Json[F("K")] = bitRead(status_parametros, 7); // Status ozonizador, 0 = desligado e 1 = ligado
    Json[F("L")] = bitRead(Status, 1); // Status reposição de água doce, 0 = desligado e 1 = ligado
    Json[F("M1")] = nivel_status1; // Status nível sensor 1, 0 = baixo e 1 = normal
    Json[F("M2")] = nivel_status2; // Status nível sensor 2, 0 = baixo e 1 = normal
    Json[F("M3")] = nivel_status3; // Status nível sensor 3, 0 = baixo e 1 = normal
    Json[F("M4")] = nivel_status4; // Status nível sensor 4, 0 = baixo e 1 = normal
    Json[F("M5")] = nivel_status5; // Status nível sensor 5, 0 = baixo e 1 = normal
    Json[F("M6")] = nivel_status6; // Status nível sensor 6, 0 = baixo e 1 = normal
    Json[F("N")] = bitRead(tpa_status, 0); // Status TPA, 0 = desligado e 1 = ligado
    Json[F("O")] = bitRead(temporizador_status, 1); // Status timer 1, 0 = desligado e 1 = ligado
    Json[F("P")] = bitRead(temporizador_status, 2); // Status timer 2, 0 = desligado e 1 = ligado
    Json[F("Q")] = bitRead(temporizador_status, 3); // Status timer 3, 0 = desligado e 1 = ligado
    Json[F("R")] = bitRead(temporizador_status, 4); // Status timer 4, 0 = desligado e 1 = ligado
    Json[F("S")] = bitRead(temporizador_status, 5); // Status timer 5, 0 = desligado e 1 = ligado
    Json[F("T")] = bitRead(tpa_status, 2); // Sinaliza falha na TPA
    Json[F("U1")] = volume_dosado[0]; // Volume dosado pela dosadora 1
    Json[F("U2")] = volume_dosado[1]; // Volume dosado pela dosadora 2
    Json[F("U3")] = volume_dosado[2]; // Volume dosado pela dosadora 3
    Json[F("U4")] = volume_dosado[3]; // Volume dosado pela dosadora 4
    Json[F("U5")] = volume_dosado[4]; // Volume dosado pela dosadora 5
    Json[F("U6")] = volume_dosado[5]; // Volume dosado pela dosadora 6
    Json[F("V1")] = bitRead(erro_dosagem, 0); // Erro dosagem dosadora 1
    Json[F("V2")] = bitRead(erro_dosagem, 1); // Erro dosagem dosadora 2
    Json[F("V3")] = bitRead(erro_dosagem, 2); // Erro dosagem dosadora 3
    Json[F("V4")] = bitRead(erro_dosagem, 3); // Erro dosagem dosadora 4
    Json[F("V5")] = bitRead(erro_dosagem, 4); // Erro dosagem dosadora 5
    Json[F("V6")] = bitRead(erro_dosagem, 5); // Erro dosagem dosadora 6


    Json.printTo(pub_message, Json.measureLength() + 1);
    MQTT.publish(LOG_TOPIC, pub_message, false);

    for (byte i = 0; i < 6; i++)
    {
      volume_dosado[i] = 0;
    }
    notconnected = 0;

#ifdef DEBUG
    Serial.println(F(">> Connected <<"));
    Serial.print(F("JSON size: "));
    Serial.println(Json.measureLength());
    Serial.println(F("JSON:"));
    Json.prettyPrintTo(Serial);
    Serial.println("");
#endif
  }
  else
  {
#ifdef DEBUG
    Serial.println(F("Can't connect!"));
#endif

    notconnected++;
    if ((notconnected >= (limite_falha - 2)) && (notconnected < limite_falha))
    {
#ifndef USE_ESP8266 // Do not change this line!
      start_ethernet();
#else  // Do not change this line!
      sincronizar();
#endif  // Do not change this line!

#ifndef WATCHDOG
      notconnected = 0;
#endif
    }

#ifdef WATCHDOG
    if (notconnected == limite_falha)
    {
#ifdef DEBUG
      Serial.println();
      Serial.print(F("Resetting"));
#endif
      delay(9000);
    }
#endif
  }
}

#ifndef USE_ESP8266 //Do not change this line

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
#ifdef DEBUG
      Serial.print(F("Socket:"));
      Serial.println(i);
#endif
    }
  }
}

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

  while ((!MQTT.connected()) && (i < 5))
  {
#ifdef DEBUG
    Serial.println(F("Attempting MQTT connection..."));
#endif
    if (MQTT.connect(CLIENT_ID, Username, APIKEY))
    {
#ifdef DEBUG
      Serial.println(F("Connected!"));
      Serial.print(F("Command: ")); // Recebe os commandos
      Serial.println(SUB_TOPIC);
#endif
      MQTT.subscribe(SUB_TOPIC);
    }
    else
    {
#ifdef DEBUG
      int Status = MQTT.state();

      switch (Status)
      {
        case -4:
          Serial.println(F("Connection timeout"));
          break;

        case -3:
          Serial.println(F("Connection lost"));
          break;

        case -2:
          Serial.println(F("Connect failed"));
          break;

        case -1:
          Serial.println(F("Disconnected"));
          break;

        case 1:
          Serial.println(F("Bad protocol"));
          break;

        case 2:
          Serial.println(F("Bad client ID"));
          break;

        case 3:
          Serial.println(F("Unavailable"));
          break;

        case 4:
          Serial.println(F("Bad credentials"));
          break;

        case 5:
          Serial.println(F("Unauthorized"));
          break;
      }
#endif
    }
    i++;
    delay(200);
  }
}
#endif //Do not change this line

#endif //Do not change this line
