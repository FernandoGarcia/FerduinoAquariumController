void criar_arquivos()
{
  byte contador = 0;
  int minuto01 = 0;
  int minuto11 = 0;

  selecionar_SPI(SD_CARD); // Seleciona disposito SPI que será utilizado. 

  if(file.open(arquivo[dosadora_selecionada], O_WRITE))
  {
    file.remove();
  }
  if(modo_personalizado_on[dosadora_selecionada] == true)
  {  
    if(file.open(arquivo[dosadora_selecionada], O_CREAT | O_APPEND | O_WRITE))
    {   
      minuto01 = NumMins(hora_final_dosagem_personalizada[dosadora_selecionada], minuto_final_dosagem_personalizada[dosadora_selecionada])
        - NumMins(hora_inicial_dosagem_personalizada[dosadora_selecionada], minuto_inicial_dosagem_personalizada[dosadora_selecionada]); 
  
      minuto01 /= 1 + quantidade_dose_dosadora_personalizada[dosadora_selecionada];
  
      for(int i = 1; i <= quantidade_dose_dosadora_personalizada[dosadora_selecionada]; i++)
      { 
        contador += 1;  
        if(contador == 1)
        {
          minuto11 = NumMins(hora_inicial_dosagem_personalizada[dosadora_selecionada], minuto_inicial_dosagem_personalizada[dosadora_selecionada]) + minuto01;
        }
        if(contador > 1)
        {
          minuto11 += minuto01; 
        }
  
        if(minuto11 < 10)
        {
          file.print("000");  
          file.print(minuto11);
          file.write((uint8_t*)"\0", 1);
          writeCRLF(file);
        }
        else if(( minuto11 > 10) && (minuto11 < 100))
        {
          file.print("00");
          file.print(minuto11);
          file.write((uint8_t*)"\0", 1);
          writeCRLF(file);
        }
        else if(( minuto11 >= 100) && (minuto11 < 1000))
        {
          file.print("0");
          file.print(minuto11);
          file.write((uint8_t*)"\0", 1);
          writeCRLF(file);
        }
        else if(minuto11 >= 1000)
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
void check_dosagem_personalizada()
{
  int16_t n;
  char buf[7];
  int minuto01 = 0;
  int minuto11 = 0;

  for(byte i = 0; i < 6; i++)
  {
    if((NumMins(t.hour,t.min) >= NumMins(hora_inicial_dosagem_personalizada_e[i], minuto_inicial_dosagem_personalizada_e[i])) 
      && (NumMins(t.hour,t.min) <= NumMins(hora_final_dosagem_personalizada_e[i], minuto_final_dosagem_personalizada_e[i])))
    { 
      if(modo_personalizado_on_e[i] == true) 
      {
        if((segunda_dosagem_personalizada_e[i] == t.dow)|| (terca_dosagem_personalizada_e[i] == t.dow) || (quarta_dosagem_personalizada_e[i] == t.dow)
          || (quinta_dosagem_personalizada_e[i] == t.dow) || (sexta_dosagem_personalizada_e[i] == t.dow)
          || (sabado_dosagem_personalizada_e[i] == t.dow) || (domingo_dosagem_personalizada_e[i] == t.dow))
        {
          selecionar_SPI(SD_CARD);
          delay(50);

          if(file.open(arquivo[i], O_READ))
          {
            while ((n = file.read(buf, sizeof(buf))) > 0)
            {
              minuto01 = atoi(buf);
              if(minuto01 ==  NumMins(t.hour,t.min))
              {
                tempo_dosagem = map (((dose_dosadora_personalizada_e[i] / quantidade_dose_dosadora_personalizada_e[i])*2), 0, fator_calib_dosadora_e[i], 0, 60000);
                tempo_dosagem /= 2;                 
                digitalWrite(dosadora[i], HIGH);
                delay(tempo_dosagem);
                digitalWrite(dosadora[i], LOW);
                volume_dosado[i] += (dose_dosadora_personalizada_e[i] / quantidade_dose_dosadora_personalizada_e[i]);
                bitWrite(erro_dosagem, i, 0);
              }
            }
            file.close();
          }
          else
          {
            bitWrite(erro_dosagem, i, 1);
          }
        }
      }
    }
  }
}

void config_valores_dosadoras_temp()
{
  for(byte i = 0; i < 6; i++)
  {
    hora_inicial_dosagem_personalizada[i] = hora_inicial_dosagem_personalizada_e[i];
    minuto_inicial_dosagem_personalizada[i] = minuto_inicial_dosagem_personalizada_e[i];
    hora_final_dosagem_personalizada[i] = hora_final_dosagem_personalizada_e[i];
    minuto_final_dosagem_personalizada[i] = minuto_final_dosagem_personalizada_e[i];
    segunda_dosagem_personalizada[i] = segunda_dosagem_personalizada_e[i];
    terca_dosagem_personalizada[i] = terca_dosagem_personalizada_e[i];
    quarta_dosagem_personalizada[i] = quarta_dosagem_personalizada_e[i];
    quinta_dosagem_personalizada[i] = quinta_dosagem_personalizada_e[i];
    sexta_dosagem_personalizada[i] = sexta_dosagem_personalizada_e[i];
    sabado_dosagem_personalizada[i] = sabado_dosagem_personalizada_e[i];
    domingo_dosagem_personalizada[i] = domingo_dosagem_personalizada_e[i];
  }
}

void config_valores_dosadoras_temp2()
{
  for(byte i = 0; i < 6; i++)
  {
    dose_dosadora_personalizada[i] = dose_dosadora_personalizada_e[i];
    quantidade_dose_dosadora_personalizada[i] = quantidade_dose_dosadora_personalizada_e[i];
    modo_personalizado_on[i] = modo_personalizado_on_e[i];
    dose_dosadora_personalizada[i] = dose_dosadora_personalizada_e[i]; 
  }
}

void config_valores_calib_temp()
{
  for(byte i = 0; i < 6; i++)
  {
    fator_calib_dosadora[i] = fator_calib_dosadora_e[i];
  }
}

void config_valores_salvar_dosadoras()
{
  for(byte i = 0; i < 6; i++)
  {
    dose_dosadora_personalizada_e[i] = dose_dosadora_personalizada[i];
    quantidade_dose_dosadora_personalizada_e[i] = quantidade_dose_dosadora_personalizada[i];
    modo_personalizado_on_e[i] = modo_personalizado_on[i];
    hora_inicial_dosagem_personalizada_e[i] = hora_inicial_dosagem_personalizada[i];
    minuto_inicial_dosagem_personalizada_e[i] = minuto_inicial_dosagem_personalizada[i];
    hora_final_dosagem_personalizada_e[i] = hora_final_dosagem_personalizada[i];
    minuto_final_dosagem_personalizada_e[i] = minuto_final_dosagem_personalizada[i];
    segunda_dosagem_personalizada_e[i] = segunda_dosagem_personalizada[i];
    terca_dosagem_personalizada_e[i] = terca_dosagem_personalizada[i];
    quarta_dosagem_personalizada_e[i] = quarta_dosagem_personalizada[i];
    quinta_dosagem_personalizada_e[i] = quinta_dosagem_personalizada[i];
    sexta_dosagem_personalizada_e[i] = sexta_dosagem_personalizada[i];
    sabado_dosagem_personalizada_e[i] = sabado_dosagem_personalizada[i];
    domingo_dosagem_personalizada_e[i] = domingo_dosagem_personalizada[i];
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

