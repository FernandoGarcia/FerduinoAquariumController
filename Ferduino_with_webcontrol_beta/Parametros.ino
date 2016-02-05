//---------------------------------------------------------------------------------------------
void checkTempC()
{
  contador_temp ++;

  sensors.requestTemperatures();                                          // Chamada para todos os sensores.
#ifdef USE_FAHRENHEIT
  temperatura_agua_temp += (sensors.getTempF(sensor_agua));               // Lê temperatura da água
  temperatura_dissipador_temp += (sensors.getTempF(sensor_dissipador));   // Lê temperatura do dissipador
  temperatura_ambiente_temp += (sensors.getTempF(sensor_ambiente));       // Lê temperatura do dissipador
#else
  temperatura_agua_temp += (sensors.getTempC(sensor_agua));               // Lê temperatura da água
  temperatura_dissipador_temp += (sensors.getTempC(sensor_dissipador));   // Lê temperatura do dissipador
  temperatura_ambiente_temp += (sensors.getTempC(sensor_ambiente));       // Lê temperatura do dissipador
#endif

  if (contador_temp == 12)
  {
    tempC = temperatura_agua_temp / 12;
    tempH = temperatura_dissipador_temp / 12;
    tempA = temperatura_ambiente_temp / 12;
    contador_temp = 0;
    temperatura_agua_temp = 0;
    temperatura_dissipador_temp = 0;
    temperatura_ambiente_temp = 0;
  }

  if (tempC < (setTempC + offTempC + alarmTempC) && tempC > (setTempC - offTempC - alarmTempC))
  {
    bitWrite(status_parametros, 2, 0);
  }

  if (alarmTempC > 0)                        // Aciona alarme
  {
    if ((tempC >= (setTempC + offTempC + alarmTempC)) || (tempC <= (setTempC - offTempC - alarmTempC)))
    {
      bitWrite(status_parametros, 2, 1);
    }
  }

  if (outlets_changed[0] == true)
  {
    outlets_changed[0] = false;
    bitWrite(status_parametros, 1, 0);
    digitalWrite(aquecedorPin, LOW);
  }

  if (outlets_changed[1] == true)
  {
    outlets_changed[1] = false;
    bitWrite(status_parametros, 0, 0);
    digitalWrite(chillerPin, LOW);
  }

  if ((outlets[0] == 0) && (outlets[1] == 0))
  {
    if ((tempC < (setTempC + offTempC)) && (tempC > (setTempC - offTempC)))          // Desliga aquecedor e chiller
    {
      bitWrite(status_parametros, 0, 0);
      bitWrite(status_parametros, 1, 0);
      digitalWrite(aquecedorPin, LOW);
      digitalWrite(chillerPin, LOW);
    }

    if (offTempC > 0)
    {
      if ((tempC > (setTempC + offTempC)))            // Liga o chiller
      {
        bitWrite(status_parametros, 0, 1);
        digitalWrite(chillerPin, HIGH);
      }
      if ((tempC < (setTempC - offTempC)))             // Liga o aquecedor
      {
        bitWrite(status_parametros, 1, 1);
        digitalWrite(aquecedorPin, HIGH);
      }
    }

#ifdef USE_FAHRENHEIT
    if ((tempC > 122) || (tempC < 50))
#else
    if ((tempC > 50) || (tempC < 10))
#endif
    {
      bitWrite(status_parametros, 0, 0);
      bitWrite(status_parametros, 1, 0);
      digitalWrite(aquecedorPin, LOW);
      digitalWrite(chillerPin, LOW);
    }

    if ((bitRead(status_parametros, 0) == true) &&  (bitRead(status_parametros, 1) == true)) // Evita aquecedor e chiller ligados ao mesmo tempo.
    {
      bitWrite(status_parametros, 0, 0);
      bitWrite(status_parametros, 1, 0);
      digitalWrite(aquecedorPin, LOW);
      digitalWrite(chillerPin, LOW);
    }
  }

  if (outlets[0] == 1)
  {
    bitWrite(status_parametros, 1, 1);
    digitalWrite(aquecedorPin, HIGH);
  }
  else if (outlets[0] == 2)
  {
    bitWrite(status_parametros, 1, 0);
    digitalWrite(aquecedorPin, LOW);
  }

  if (outlets[1] == 1)
  {
    bitWrite(status_parametros, 0, 1);
    digitalWrite(chillerPin, HIGH);
  }
  else if (outlets[1] == 2)
  {
    bitWrite(status_parametros, 0, 0);
    digitalWrite(chillerPin, LOW);
  }

  int tempval = int(tempH * 10);
  fanSpeed = map(tempval, (HtempMin * 10), (HtempMax * 10), 0, 255);       // Controle de velocidade das ventoinhas do dissipador

  if (fanSpeed < 0)
  {
    fanSpeed = 0;
  }
  if (fanSpeed > 255)
  {
    fanSpeed = 255;
  }
  analogWrite(fanPin, fanSpeed);

  if (tempH < HtempMin) // Desativa os coolers se a temperatura estiver abaixo da mínima definida.
  {
    digitalWrite(desativarFanPin, LOW);
  }
  else
  {
    digitalWrite(desativarFanPin, HIGH);
  }
}

void check_nivel() // Verifica o nível do reef e fish only.
{
  if ((analogRead(sensor5) > 400) || (analogRead(sensor6) > 400) || ((analogRead(sensor2) < 400) && (bitRead(tpa_status, 1) == false)))
  {
    nivel_status1 = true; // Sinaliza nivel baixo em um dos aquários ou sump
  }
  else
  {
    nivel_status1 = false; // Sinaliza nível normal dos aquários e sump
  }

  // Edit this part according to your requirements.

  /*if(analogRead(sensor1) < 400)
    {
    nivel_status1 = true; // Sinaliza nivel baixo sensor 1
    }
    else
    {
    nivel_status1 = false; // Sinaliza nível normal sensor 1
    }
    if(analogRead(sensor2) < 400)
    {
    nivel_status2 = true; // Sinaliza nivel baixo sensor 2
    }
    else
    {
    nivel_status2 = false; // Sinaliza nível normal sensor 2
    }
    if(analogRead(sensor3) < 400)
    {
    nivel_status3 = true; // Sinaliza nivel baixo sensor 3
    }
    else
    {
    nivel_status3 = false; // Sinaliza nível normal sensor 3
    }
    if(analogRead(sensor4) < 400)
    {
    nivel_status4 = true; // Sinaliza nivel baixo sensor 4
    }
    else
    {
    nivel_status4 = false; // Sinaliza nível normal sensor 4
    }
    if(analogRead(sensor5) < 400)
    {
    nivel_status5 = true; // Sinaliza nivel baixo sensor 5
    }
    else
    {
    nivel_status5 = false; // Sinaliza nível normal sensor 5
    }
    if(analogRead(sensor6) < 400)
    {
    nivel_status6 = true; // Sinaliza nivel baixo sensor 6
    }
    else
    {
    nivel_status6 = false; // Sinaliza nível normal sensor 6
    }*/
}

void check_PH_reator()
{
  if (PHR < (setPHR + offPHR + alarmPHR) && PHR > (setPHR - offPHR - alarmPHR))
  {
    bitWrite(status_parametros, 6, 0);
  }

  if (alarmPHR > 0)           // Liga o alarme
  {
    if ((PHR > (setPHR + offPHR + alarmPHR)) || (PHR <= (setPHR - offPHR - alarmPHR)))
    {
      bitWrite(status_parametros, 6, 1);
    }
  }

  if (outlets_changed[3] == true)
  {
    outlets_changed[3] = false;
    bitWrite(status_parametros, 5, 0);
#ifdef USE_PCF8575
    PCF8575.digitalWrite(reatorPin, LOW);  // Desliga co2 do reator de cálcio
#else
    digitalWrite(reatorPin, LOW);  // Desliga co2 do reator de cálcio
#endif
  }

  if (outlets[3] == 0)
  {
    if ((PHR < 4) || (PHR > 10))
    {
      bitWrite(status_parametros, 5, 0);
#ifdef USE_PCF8575
      PCF8575.digitalWrite(reatorPin, LOW);  // Desliga co2 do reator de cálcio
#else
      digitalWrite(reatorPin, LOW);  // Desliga co2 do reator de cálcio
#endif
    }
    else
    {
      if (PHR < setPHR)
      {
        bitWrite(status_parametros, 5, 0);
#ifdef USE_PCF8575
        PCF8575.digitalWrite(reatorPin, LOW);  // Desliga co2 do reator de cálcio
#else
        digitalWrite(reatorPin, LOW);  // Desliga co2 do reator de cálcio
#endif
      }
      if (offPHR > 0)
      {
        if (PHR > setPHR)
        {
          bitWrite(status_parametros, 5, 1);
#ifdef USE_PCF8575
          PCF8575.digitalWrite(reatorPin, HIGH); // Liga co2 do reator de cálcio
#else
          digitalWrite(reatorPin, HIGH); // Liga co2 do reator de cálcio
#endif
        }
      }
    }
  }
  else if (outlets[3] == 1)
  {
    bitWrite(status_parametros, 5, 1);
#ifdef USE_PCF8575
    PCF8575.digitalWrite(reatorPin, HIGH); // Liga co2 do reator de cálcio
#else
    digitalWrite(reatorPin, HIGH); // Liga co2 do reator de cálcio
#endif
  }
  else if (outlets[3] == 2)
  {
    bitWrite(status_parametros, 5, 0);
#ifdef USE_PCF8575
    PCF8575.digitalWrite(reatorPin, LOW); // Liga co2 do reator de cálcio
#else
    digitalWrite(reatorPin, LOW); // Liga co2 do reator de cálcio
#endif
  }
}

void check_PH_aquario()
{
  if (PHA < (setPHA + offPHA + alarmPHA) && PHA > (setPHA - offPHA - alarmPHA))
  {
    bitWrite(status_parametros, 3, 0);
  }
  if (alarmPHA > 0)           // Liga o alarme
  {
    if ((PHA >= (setPHA + offPHA + alarmPHA)) || (PHA <= (setPHA - offPHA - alarmPHA)))
    {
      bitWrite(status_parametros, 3, 1);
    }
  }
  if (outlets[3] == 0)
  {
    if (PHA < (setPHA - offPHA)) // Se PH do aquário menor que o desejado menos a variacao permitida.
    {
      bitWrite(status_parametros, 5, 0);
#ifdef USE_PCF8575
      PCF8575.digitalWrite(reatorPin, LOW);  // Desliga co2 do reator de cálcio
#else
      digitalWrite(reatorPin, LOW);  // Desliga co2 do reator de cálcio
#endif
    }
  }
}

void check_densidade()
{
  if (DEN < (setDEN + offDEN + alarmDEN) && DEN > (setDEN - offDEN - alarmDEN))
  {
    bitWrite(status_parametros, 4, 0);
  }
  if (alarmDEN > 0)           // Liga o alarme
  {
    if ((DEN >= (setDEN + offPHR + alarmDEN)) || (DEN <= (setDEN - offDEN - alarmDEN)))
    {
      bitWrite(status_parametros, 4, 1);
    }
  }
}

void check_ORP()
{
  if (ORP < (setORP + offORP + alarmORP) && ORP > (setORP - offORP - alarmORP))
  {
    bitWrite(status_parametros_1, 0, 0);
  }
  if (alarmORP > 0)            // Liga o alarme
  {
    if ((ORP >= (setORP + offORP + alarmORP)) || (ORP <= (setORP - offORP - alarmORP)))
    {
      bitWrite(status_parametros_1, 0, 1);
    }
  }

  if (outlets_changed[2] == true)
  {
    outlets_changed[2] = false;
    bitWrite(status_parametros, 7, 0);
#ifdef USE_PCF8575
    PCF8575.digitalWrite(ozonizadorPin, LOW); // Desliga ozonizador
#else
    digitalWrite(ozonizadorPin, LOW); // Desliga ozonizador
#endif
  }

  if (outlets[2] == 0)
  {
    if ((ORP < 100) || (ORP > 500))
    {
      bitWrite(status_parametros, 7, 0);
#ifdef USE_PCF8575
      PCF8575.digitalWrite(ozonizadorPin, LOW); // Desliga ozonizador
#else
      digitalWrite(ozonizadorPin, LOW); // Desliga ozonizador
#endif
    }
    else
    {
      if (ORP > setORP)
      {
        bitWrite(status_parametros, 7, 0);
#ifdef USE_PCF8575
        PCF8575.digitalWrite(ozonizadorPin, LOW);  // Desliga ozonizador
#else
        digitalWrite(ozonizadorPin, LOW);  // Desliga ozonizador
#endif
      }
      if (offORP > 0)
      {
        if (ORP < setORP)
        {
          bitWrite(status_parametros, 7, 1);
#ifdef USE_PCF8575
          PCF8575.digitalWrite(ozonizadorPin, HIGH); // Liga ozonizador
#else
          digitalWrite(ozonizadorPin, HIGH); // Liga ozonizador
#endif
        }
      }
    }
  }
  else if (outlets[2] == 1)
  {
    bitWrite(status_parametros, 7, 1);
#ifdef USE_PCF8575
    PCF8575.digitalWrite(ozonizadorPin, HIGH); // Liga ozonizador
#else
    digitalWrite(ozonizadorPin, HIGH); // Liga ozonizador
#endif
  }
  else if (outlets[2] == 2)
  {
    bitWrite(status_parametros, 7, 0);
#ifdef USE_PCF8575
    PCF8575.digitalWrite(ozonizadorPin, LOW); // Liga ozonizador
#else
    digitalWrite(ozonizadorPin, LOW); // Liga ozonizador
#endif
  }
}
void check_alarme()
{
  if ((bitRead(status_parametros, 2) == true) || (bitRead(status_parametros, 3) == true) || (bitRead(status_parametros, 4) == true) ||
      (bitRead(status_parametros, 6) == true) || (bitRead(status_parametros_1, 1) == true) || (bitRead(tpa_status, 2) == true))
  {
    digitalWrite (alarmPin, HIGH);
  }
  else
  {
    digitalWrite (alarmPin, LOW);
  }
}

void reposicao_agua_doce () // abre a solenoide 1 se o nível estiver baixo e se a tpa não estiver em andamento
//e se o chiller estiver desligado e se o nível do sump não estiver anormal e se não houve falha durante uma tpa.
{
  if (outlets_changed[8] == true)
  {
    outlets_changed[8] = false;
    bitWrite(Status, 1, 0);
#ifdef USE_PCF8575
    PCF8575.digitalWrite(solenoide1Pin, LOW);
#else
    digitalWrite(solenoide1Pin, LOW);
#endif
  }

  if (outlets[8] == 0)
  {
    if ((analogRead(sensor3) > 400) && (analogRead(sensor2) > 400) && (bitRead(tpa_status, 1) == false) && (bitRead(status_parametros, 0) == false) && (bitRead(tpa_status, 2) == false))
    {
#ifdef USE_PCF8575
      PCF8575.digitalWrite(solenoide1Pin, HIGH);
#else
      digitalWrite(solenoide1Pin, HIGH);
#endif
      bitWrite(Status, 1, 1); //sinaliza reposição em andamento
    }
    else
    {
#ifdef USE_PCF8575
      PCF8575.digitalWrite(solenoide1Pin, LOW);
#else
      digitalWrite(solenoide1Pin, LOW);
#endif
      bitWrite(Status, 1, 0);
    }
  }
  else if (outlets[8] == 1)
  {
    bitWrite(Status, 1, 1);
#ifdef USE_PCF8575
    PCF8575.digitalWrite(solenoide1Pin, HIGH);
#else
    digitalWrite(solenoide1Pin, HIGH);
#endif
  }
  else if (outlets[8] == 2)
  {
    bitWrite(Status, 1, 0);
#ifdef USE_PCF8575
    PCF8575.digitalWrite(solenoide1Pin, LOW);
#else
    digitalWrite(solenoide1Pin, LOW);
#endif
  }
}

#ifdef DISABLE_SKIMMER
void check_level_skimmer()
{
  if (outlets_changed[4] == true)
  {
    outlets_changed[4] = false;
#ifdef USE_PCF8575
    PCF8575.digitalWrite(skimmerPin, LOW);
#else
    digitalWrite(skimmerPin, LOW);
#endif
  }

  if (outlets[4] == 0)
  {
    if (analogRead(sensor3) < 400)
    {
#ifdef USE_PCF8575
      PCF8575.digitalWrite(skimmerPin, LOW);
#else
      digitalWrite(skimmerPin, LOW);
#endif
    }
    else
    {
#ifdef USE_PCF8575
      PCF8575.digitalWrite(skimmerPin, HIGH);
#else
      digitalWrite(skimmerPin, HIGH);
#endif
    }
  }
  else if (outlets[4] == 1)
  {
#ifdef USE_PCF8575
    PCF8575.digitalWrite(skimmerPin, HIGH);
#else
    digitalWrite(skimmerPin, HIGH);
#endif
  }
  else if (outlets[4] == 2)
  {
#ifdef USE_PCF8575
    PCF8575.digitalWrite(skimmerPin, LOW);
#else
    digitalWrite(skimmerPin, LOW);
#endif
  }
}
#endif
