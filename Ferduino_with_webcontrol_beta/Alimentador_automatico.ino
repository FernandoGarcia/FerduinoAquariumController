void alimentador_automatico()
{
  if ((modo_alimentacao == true) && (millis() >= alimentacao_millis))
  {
#ifdef USE_PCF8575
    PCF8575.digitalWrite(alimentadorPin, HIGH);
#else
    digitalWrite(alimentadorPin, HIGH);
#endif
  }
  else
  {
#ifdef USE_PCF8575
    PCF8575.digitalWrite(alimentadorPin, LOW);
#else
    digitalWrite(alimentadorPin, LOW);
#endif
  }
}

void check_alimentador()
{
  int16_t n;
  char buf[7];
  int minuto01 = 0;
  int minuto11 = 0;
  if ((NumMins(t.hour, t.min) >= NumMins(horario_alimentacao_e[0], horario_alimentacao_e[1])) && (NumMins(t.hour, t.min) <= NumMins(horario_alimentacao_e[2], horario_alimentacao_e[3])))
  {
    if ((bitRead(alimentacao_wavemaker_on_off, 0)  == true) && (modo_alimentacao == false))
    {
      if ((dia_alimentacao_e[0] == t.dow) || (dia_alimentacao_e[1] == t.dow) || (dia_alimentacao_e[2] == t.dow)
          || (dia_alimentacao_e[3] == t.dow) || (dia_alimentacao_e[4] == t.dow) || (dia_alimentacao_e[5] == t.dow)
          || (dia_alimentacao_e[6] == t.dow))
      {
        selecionar_SPI(SD_CARD);
        delay(50);

        if (file.open("FEEDER.TXT", O_READ))
        {
          while ((n = file.read(buf, sizeof(buf))) > 0)
          {
            minuto01 = atoi(buf);
            if (minuto01 ==  NumMins(t.hour, t.min))
            {
              modo_alimentacao = true;
              alimentacao_millis = millis();
            }
            if (bitRead(alimentacao_wavemaker_on_off, 1)  == true)
            {
              if (minuto01 - (desligar_wavemaker / 2) ==  NumMins(t.hour, t.min))
              {
                wavemaker_on_off = true;
                wavemaker_on_off_millis = millis();
              }
            }
          }
          file.close();
        }
      }
    }
  }
}

void criar_arquivos_alimentador()
{
  byte contador = 0;
  int minuto01 = 0;
  int minuto11 = 0;

  selecionar_SPI(SD_CARD); // Seleciona disposito SPI que será utilizado.

  if (file.open("FEEDER.TXT", O_WRITE))
  {
    file.remove();
  }
  if(bitRead(alimentacao_wavemaker_on_off, 0) == true)
  {
    if (file.open("FEEDER.TXT", O_CREAT | O_APPEND | O_WRITE))
    {
      minuto01 = NumMins(horario_alimentacao_e[2], horario_alimentacao_e[3]) - NumMins(horario_alimentacao_e[0], horario_alimentacao_e[1]);
  
      minuto01 /= 1 + quantidade_alimentacao;
  
      for (int i = 1; i <= quantidade_alimentacao; i++)
      {
        contador += 1;
        if (contador == 1)
        {
          minuto11 = NumMins(horario_alimentacao_e[0], horario_alimentacao_e[1]) + minuto01;
        }
        if (contador > 1)
        {
          minuto11 += minuto01;
        }
  
        if (minuto11 < 10)
        {
          file.print("000");
          file.print(minuto11);
          file.write((uint8_t*)"\0", 1);
          writeCRLF(file);
        }
        else if (( minuto11 > 10) && (minuto11 < 100))
        {
          file.print("00");
          file.print(minuto11);
          file.write((uint8_t*)"\0", 1);
          writeCRLF(file);
        }
        else if (( minuto11 >= 100) && (minuto11 < 1000))
        {
          file.print("0");
          file.print(minuto11);
          file.write((uint8_t*)"\0", 1);
          writeCRLF(file);
        }
        else if (minuto11 >= 1000)
        {
          file.print(minuto11);
          file.write((uint8_t*)"\0", 1);
          writeCRLF(file);
        }
      }
      file.close();
    }
  }
}

void config_valores_alimentador()
{
  for (byte i = 0; i < 4; i++)
  {
    horario_alimentacao[i] = horario_alimentacao_e[i];
  }
  for (byte i = 0; i < 7; i++)
  {
    dia_alimentacao[i] = dia_alimentacao_e[i];
  }
  duracao_alimentacao_temp = duracao_alimentacao;
  desligar_wavemaker_temp = desligar_wavemaker;
  quantidade_alimentacao_temp = quantidade_alimentacao;
  alimentacao_wavemaker_on_off_temp = alimentacao_wavemaker_on_off;
}

void config_salvar_valores_alimentador()
{
  for (byte i = 0; i < 4; i++)
  {
    horario_alimentacao_e[i] = horario_alimentacao[i];
  }
  for (byte i = 0; i < 7; i++)
  {
    dia_alimentacao_e[i] = dia_alimentacao[i];
  }
  duracao_alimentacao = duracao_alimentacao_temp;
  desligar_wavemaker = desligar_wavemaker_temp;
  quantidade_alimentacao = quantidade_alimentacao_temp;
  alimentacao_wavemaker_on_off = alimentacao_wavemaker_on_off_temp;
}

void inicia_alimentacao()
{
  if (modo_alimentacao == false)
  {
    if (bitRead(alimentacao_wavemaker_on_off, 1)  == true)
    {
      alimentacao_millis = millis() + ((desligar_wavemaker / 2) * 60000);
      modo_alimentacao = wavemaker_on_off = true;
      wavemaker_on_off_millis = millis();
    }
    else
    {
      modo_alimentacao = true;
      alimentacao_millis = millis();
    }
  }
  else
  {
    modo_alimentacao = wavemaker_on_off = false;
  }
}




