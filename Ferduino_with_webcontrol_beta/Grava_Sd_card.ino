//Write CR LF to a file

void writeCRLF(SdFile& f) 
{
  f.write((uint8_t*)"\r\n", 2);
}

void logtempgraf() //Grava dados no SD CARD para gerar  grafico de temperatura.
{
  if(NumMins(t.hour,t.min) == 1)
  {
    EEPROM.write(688, t.date); 
  }

  selecionar_SPI(SD_CARD);

  if(file.open("LOGTDIA.TXT", O_CREAT | O_APPEND | O_WRITE))
  {
    if ((tempC<=1.0) || (tempC>99.9))
    {
      file.print("00.00");
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    else
    {
      file.print(tempC);
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    file.close();
  }

  if ((t.hour == 23) && (t.min > 58))
  {
    if(file.open("LOGTDIA.TXT", O_WRITE))
    {
      file.remove();
    }
  }
}

void logphagraf() //Grava dados no SD CARD para gerar  gráfico de PH do aquário.
{ 
  if(NumMins(t.hour,t.min) == 1)
  {
    EEPROM.write(689, t.date); 
  }

  selecionar_SPI(SD_CARD);

  if(file.open("LOGPDIA.TXT", O_CREAT | O_APPEND | O_WRITE))
  {
    if((PHA < 1.00) || (PHA > 9.99))
    {
      file.print("0.00");
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    else
    {   
      file.print(PHA);
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    file.close();
  }
  if ((t.hour == 23) && (t.min > 58))
  {
    if(file.open("LOGPDIA.TXT", O_WRITE))
    {
      file.remove();
    }
  } 
}

void logphrgraf() //Grava dados no SD CARD para gerar  gráfico de PH do reator de calcio.
{
  if(NumMins(t.hour,t.min) == 1)
  {
    EEPROM.write(690, t.date); 
  }

  selecionar_SPI(SD_CARD);

  if(file.open("LOGRDIA.TXT", O_CREAT | O_APPEND | O_WRITE))
  {
    if((PHR < 1.00) || (PHR > 9.99))
    {
      file.print("0.00");
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    else
    {
      file.print(PHR);
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    file.close();
  }

  if ((t.hour == 23) && (t.min > 58))
  {
    if(file.open("LOGRDIA.TXT", O_WRITE))
    {
      file.remove();
    }
  }
}

void logorpgraf() //Grava dados no SD CARD para gerar  grafico de ORP.
{
  if(NumMins(t.hour,t.min) == 1)
  {
    EEPROM.write(691, t.date); 
  }

  selecionar_SPI(SD_CARD);

  if(file.open("LOGODIA.TXT", O_CREAT | O_APPEND | O_WRITE))
  {   
    if ((ORP<=100) || (tempC>999))
    {
      file.print("000");
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    else
    {
      file.print(ORP);
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    file.close();
  }

  if ((t.hour == 23) && (t.min > 58))
  {
    if(file.open("LOGODIA.TXT", O_WRITE))
    {
      file.remove();
    }
  } 
}

void logdengraf() //Grava dados no SD CARD para gerar  grafico de PH do aquario.
{
  if(NumMins(t.hour,t.min) == 1)
  {
    EEPROM.write(692, t.date); 
  }

  selecionar_SPI(SD_CARD);

  if(file.open("LOGDDIA.TXT", O_CREAT | O_APPEND | O_WRITE))   
  {
    if( (DEN<1000) || (DEN>9999))
    {
      file.print("0000");
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    else
    {    

      file.print(DEN);
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    file.close();
  }

  if ((t.hour == 23) && (t.min > 58))
  {
    if(file.open("LOGDDIA.TXT", O_WRITE))
    {
      file.remove();
    }
  } 
}

void check_arquivo_temp_agua()
{
  int16_t n;
  char buf[8];
  int contador = 0;

  byte k = EEPROM.read(688);

  selecionar_SPI(SD_CARD);

  if(k != t.date)
  {
    if(file.open("LOGTDIA.TXT", O_WRITE))
    {
      file.remove();
    }
  }

  if(file.open("LOGTDIA.TXT", O_CREAT | O_READ | O_APPEND | O_WRITE))
  {
    while ((n = file.read(buf, sizeof(buf))) > 0)
    {
      if(strlen(buf) == 5)
      {
        contador++;
      }
    }
    if(contador < NumMins(t.hour, t.min))
    {
      for(int i = contador; i < NumMins(t.hour, t.min) - 1; i++)
      {
        file.print("00.00");
        file.write((uint8_t*)"\0", 1);
        writeCRLF(file);
      } 
    }
    file.close();
  }
}

void check_arquivo_ph_agua()
{
  int16_t n;
  char buf[7];
  int contador = 0;

  byte k = EEPROM.read(689);

  selecionar_SPI(SD_CARD);

  if(k != t.date)
  {
    if(file.open("LOGPDIA.TXT", O_WRITE))
    {
      file.remove();
    }
  }

  if(file.open("LOGPDIA.TXT", O_CREAT | O_READ | O_APPEND | O_WRITE))
  {
    while ((n = file.read(buf, sizeof(buf))) > 0)
    {
      if(strlen(buf) == 4)
      {
        contador++;
      }
    }
    if(contador < NumMins(t.hour, t.min))
    {
      for(int i = contador; i < NumMins(t.hour, t.min) - 1; i++)
      {
        file.print("0.00");
        file.write((uint8_t*)"\0", 1);
        writeCRLF(file);
      } 
    }
    file.close();
  }
}

void check_arquivo_ph_reator()
{
  int16_t n;
  char buf[7];
  int contador = 0;

  byte k = EEPROM.read(690);

  selecionar_SPI(SD_CARD);

  if(k != t.date)
  {
    if(file.open("LOGRDIA.TXT", O_WRITE))
    {
      file.remove();
    }
  }

  if(file.open("LOGRDIA.TXT", O_CREAT | O_READ | O_APPEND | O_WRITE))
  {
    while ((n = file.read(buf, sizeof(buf))) > 0)
    {
      if(strlen(buf) == 4)
      {
        contador++;
      }
    }
    if(contador < NumMins(t.hour, t.min))
    {
      for(int i = contador; i < NumMins(t.hour, t.min) - 1; i++)
      {
        file.print("0.00");
        file.write((uint8_t*)"\0", 1);
        writeCRLF(file);
      } 
    }
    file.close();
  }
}

void check_arquivo_orp()
{
  int16_t n;
  char buf[6];
  int contador = 0;

  byte k = EEPROM.read(691);

  selecionar_SPI(SD_CARD);

  if(k != t.date)
  {
    if(file.open("LOGODIA.TXT", O_WRITE))
    {
      file.remove();
    }
  }

  if(file.open("LOGODIA.TXT", O_CREAT | O_READ | O_APPEND | O_WRITE))
  {
    while ((n = file.read(buf, sizeof(buf))) > 0)
    {
      if(strlen(buf) == 3)
      {
        contador++;
      }
    }
    if(contador < NumMins(t.hour, t.min))
    {
      for(int i = contador; i < NumMins(t.hour, t.min) - 1; i++)
      {
        file.print("000");
        file.write((uint8_t*)"\0", 1);
        writeCRLF(file);
      } 
    }
    file.close();
  }
}

void check_arquivo_densidade()
{
  int16_t n;
  char buf[7];
  int contador = 0;

  byte k = EEPROM.read(692);

  selecionar_SPI(SD_CARD);

  if(k != t.date)
  {
    if(file.open("LOGDDIA.TXT", O_WRITE))
    {
      file.remove();
    }
  }

  if(file.open("LOGDDIA.TXT", O_CREAT | O_READ | O_APPEND | O_WRITE))
  {
    while ((n = file.read(buf, sizeof(buf))) > 0)
    {
      if(strlen(buf) == 4)
      {
        contador++;
      }
    }

    if(contador < NumMins(t.hour, t.min))
    {
      for(int i = contador; i < NumMins(t.hour, t.min) - 1; i++)
      {
        file.print("0000");
        file.write((uint8_t*)"\0", 1);
        writeCRLF(file);
      } 
    }
    file.close();
  }
}

