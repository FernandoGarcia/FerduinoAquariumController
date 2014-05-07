//Write CR LF to a file

void writeCRLF(SdFile& f) 
{
  f.write((uint8_t*)"\r\n", 2);
}

void logtempgraf() //Grava dados no SD CARD para gerar  grafico de temperatura.
{
  char oldminuto1;
  oldminuto1 = time1;
  time1 = t.min;

  if(NumMins(t.hour,t.min) == 1)
  {
    EEPROM.write(688, t.date); 
  }

  if (oldminuto1!=time1)
  {
    file.open(&root, "LOGTDIA.TXT", O_CREAT | O_APPEND | O_WRITE);

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
  }
  file.close();

  if ((t.hour == 23) && (t.min > 58))
  {
    file.open(&root, "LOGTDIA.TXT", O_WRITE);
    file.remove();
  } 
}

void logphagraf() //Grava dados no SD CARD para gerar  gráfico de PH do aquário.
{ 
  char oldminuto2;
  oldminuto2 = time2;
  time2 = t.min;

  if(NumMins(t.hour,t.min) == 1)
  {
    EEPROM.write(689, t.date); 
  }

  if (oldminuto2!=time2)
  {
    if((PHA < 1.00) || (PHA > 9.99))
    {
      file.print("0.00");
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    else
    {
      file.open(&root, "LOGPDIA.TXT", O_CREAT | O_APPEND | O_WRITE);   
      file.print(PHA);
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
  }
  file.close();

  if ((t.hour == 23) && (t.min > 58))
  {
    file.open(&root, "LOGPDIA.TXT", O_WRITE);
    file.remove();
  } 
}

void logphrgraf() //Grava dados no SD CARD para gerar  gráfico de PH do reator de calcio.
{
  char oldminuto3;
  oldminuto3 = time3;
  time3 = t.min;
  if(NumMins(t.hour,t.min) == 1)
  {
    EEPROM.write(690, t.date); 
  }
  if (oldminuto3!=time3)
  {
    if((PHR < 1.00) || (PHR > 9.99))
    {
      file.print("0.00");
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    else
    {
      file.open(&root, "LOGRDIA.TXT", O_CREAT | O_APPEND | O_WRITE);   
      file.print(PHR);
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
  }
  file.close();

  if ((t.hour == 23) && (t.min > 58))
  {
    file.open(&root, "LOGRDIA.TXT", O_WRITE);
    file.remove();
  }
}

void logorpgraf() //Grava dados no SD CARD para gerar  grafico de ORP.
{
  char oldminuto4;
  oldminuto4 = time4;
  time4 = t.min;

  if(NumMins(t.hour,t.min) == 1)
  {
    EEPROM.write(691, t.date); 
  }

  if (oldminuto4!=time4)
  {
    if ((ORP<=100) || (tempC>999))
    {
      file.print("000");
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    else
    {
      file.open(&root, "LOGODIA.TXT", O_CREAT | O_APPEND | O_WRITE);   
      file.print(ORP);
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
  }
  file.close();

  if ((t.hour == 23) && (t.min > 58))
  {
    file.open(&root, "LOGODIA.TXT", O_WRITE);
    file.remove();
  } 
}

void logdengraf() //Grava dados no SD CARD para gerar  grafico de PH do aquario.
{
  char oldminuto5;
  oldminuto5 = time5;
  time5  = t.min;

  if(NumMins(t.hour,t.min) == 1)
  {
    EEPROM.write(692, t.date); 
  }

  if (oldminuto5!=time5)
  {
    if( (DEN<1000) || (DEN>9999))
    {
      file.print("0000");
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    else
    {    
      file.open(&root, "LOGDDIA.TXT", O_CREAT | O_APPEND | O_WRITE);   
      file.print(DEN);
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
  }
  file.close();

  if ((t.hour == 23) && (t.min > 58))
  {
    file.open(&root, "LOGDDIA.TXT", O_WRITE);
    file.remove();
  }  
}
void check_arquivo_temp_agua(boolean web = false, int num = 0)
{
  int16_t n;
  char buf[8];
  int contador = 0;
  EthernetClient client = server.available();
  byte k = EEPROM.read(688);

  if(web == false)
  {
    if(k != t.date)
    {
      file.open(&root, "LOGTDIA.TXT", O_READ);
      file.remove();
    }
  }

  file.open(&root, "LOGTDIA.TXT", O_CREAT | O_READ | O_APPEND | O_WRITE);
  while ((n = file.read(buf, sizeof(buf))) > 0)
  {
    if(strlen(buf) == 5)
    {
      contador++;
    }
    if(web == true)
    {     
      if(contador == (num + 1))
      {
        client.print("{\"v0\":");
      } 
      if((contador > num) && (contador < num + 15))
      {
        client.print(buf);
        client.print(",\"v" + String(contador - num) + "\":");
      }
      if(contador == (num + 15))
      {
        client.print(buf);  
      }
    }
  }
  if(web == true)
  {
    if((num + 15) > contador)
    {
      client.print("\"\""); 
    }
    client.print("}"); 
  }

  if(web == false)
  {
    if(contador < NumMins(t.hour, t.min))
    {
      for(int i = contador; i < NumMins(t.hour, t.min) - 1; i++)
      {
        file.print("00.00");
        file.write((uint8_t*)"\0", 1);
        writeCRLF(file);
      } 
    }
  }
  file.close();
}

void check_arquivo_ph_agua(boolean web = false, int num = 0)
{
  int16_t n;
  char buf[7];
  int contador = 0;
  EthernetClient client = server.available();
  byte k = EEPROM.read(689);

  if(web == false)
  {
    if(k != t.date)
    {
      file.open(&root, "LOGPDIA.TXT", O_READ);
      file.remove();
    }
  }

  file.open(&root, "LOGPDIA.TXT", O_CREAT | O_READ | O_APPEND | O_WRITE);
  while ((n = file.read(buf, sizeof(buf))) > 0)
  {
    if(strlen(buf) == 4)
    {
      contador++;
    }
    if(web == true)
    {     
      if(contador == (num + 1))
      {
        client.print("{\"v0\":");
      } 
      if((contador > num) && (contador < num + 15))
      {
        client.print(buf);
        client.print(",\"v" + String(contador - num) + "\":");
      }
      if(contador == (num + 15))
      {
        client.print(buf);  
      }
    }
  }
  if(web == true)
  {
    if((num + 15) > contador)
    {
      client.print("\"\""); 
    }
    client.print("}"); 
  }
  if(web == false)
  {
    if(contador < NumMins(t.hour, t.min))
    {
      for(int i = contador; i < NumMins(t.hour, t.min) - 1; i++)
      {
        file.print("0.00");
        file.write((uint8_t*)"\0", 1);
        writeCRLF(file);
      } 
    }
  }
  file.close();
}

void check_arquivo_ph_reator(boolean web = false, int num = 0)
{
  int16_t n;
  char buf[7];
  int contador = 0;
  EthernetClient client = server.available();
  byte k = EEPROM.read(690);

  if(web == false)
  {
    if(k != t.date)
    {
      file.open(&root, "LOGRDIA.TXT", O_READ);
      file.remove();
    }
  }

  file.open(&root, "LOGRDIA.TXT", O_CREAT | O_READ | O_APPEND | O_WRITE);
  while ((n = file.read(buf, sizeof(buf))) > 0)
  {
    if(strlen(buf) == 4)
    {
      contador++;
    }
    if(web == true)
    {     
      if(contador == (num + 1))
      {
        client.print("{\"v0\":");
      } 
      if((contador > num) && (contador < num + 15))
      {
        client.print(buf);
        client.print(",\"v" + String(contador - num) + "\":");
      }
      if(contador == (num + 15))
      {
        client.print(buf);  
      }
    }
  }
  if(web == true)
  {
    if((num + 15) > contador)
    {
      client.print("\"\""); 
    }
    client.print("}"); 
  }
  if(web == false)
  {
    if(contador < NumMins(t.hour, t.min))
    {
      for(int i = contador; i < NumMins(t.hour, t.min) - 1; i++)
      {
        file.print("0.00");
        file.write((uint8_t*)"\0", 1);
        writeCRLF(file);
      } 
    }
  }
  file.close();
}

void check_arquivo_orp(boolean web = false, int num = 0)
{
  int16_t n;
  char buf[6];
  int contador = 0;
  EthernetClient client = server.available();
  byte k = EEPROM.read(691);

  if(web == false)
  {
    if(k != t.date)
    {
      file.open(&root, "LOGODIA.TXT", O_READ);
      file.remove();
    }
  }

  file.open(&root, "LOGODIA.TXT", O_CREAT | O_READ | O_APPEND | O_WRITE);
  while ((n = file.read(buf, sizeof(buf))) > 0)
  {
    if(strlen(buf) == 3)
    {
      contador++;
    }
    if(web == true)
    {     
      if(contador == (num + 1))
      {
        client.print("{\"v0\":");
      } 
      if((contador > num) && (contador < num + 15))
      {
        client.print(buf);
        client.print(",\"v" + String(contador - num) + "\":");
      }
      if(contador == (num + 15))
      {
        client.print(buf);  
      }
    }
  }
  if(web == true)
  {
    if((num + 15) > contador)
    {
      client.print("\"\""); 
    }
    client.print("}"); 
  }
  if(web == false)
  {
    if(contador < NumMins(t.hour, t.min))
    {
      for(int i = contador; i < NumMins(t.hour, t.min) - 1; i++)
      {
        file.print("000");
        file.write((uint8_t*)"\0", 1);
        writeCRLF(file);
      } 
    }
  }
  file.close();
}

void check_arquivo_densidade(boolean web = false, int num = 0)
{
  int16_t n;
  char buf[7];
  int contador = 0;
  EthernetClient client = server.available();
  byte k = EEPROM.read(692);

  if(web == false)
  {
    if(k != t.date)
    {
      file.open(&root, "LOGDDIA.TXT", O_READ);
      file.remove();
    }
  }

  file.open(&root, "LOGDDIA.TXT", O_CREAT | O_READ | O_APPEND | O_WRITE);
  while ((n = file.read(buf, sizeof(buf))) > 0)
  {
    if(strlen(buf) == 4)
    {
      contador++;
    }
    if(web == true)
    {     
      if(contador == (num + 1))
      {
        client.print("{\"v0\":");
      } 
      if((contador > num) && (contador < num + 15))
      {
        client.print(buf);
        client.print(",\"v" + String(contador - num) + "\":");
      }
      if(contador == (num + 15))
      {
        client.print(buf);  
      }
    }
  }
  if(web == true)
  {
    if((num + 15) > contador)
    {
      client.print("\"\""); 
    }
    client.print("}"); 
  }
  if(web == false)
  {
    if(contador < NumMins(t.hour, t.min))
    {
      for(int i = contador; i < NumMins(t.hour, t.min) - 1; i++)
      {
        file.print("0000");
        file.write((uint8_t*)"\0", 1);
        writeCRLF(file);
      } 
    }
  }
  file.close();
}

