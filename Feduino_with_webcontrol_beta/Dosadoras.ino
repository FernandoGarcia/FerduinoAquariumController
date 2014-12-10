void criar_arquivos()
{
  byte contador = 0;
  int minuto01 = 0;
  int minuto11 = 0;

  selecionar_SPI(SD_CARD); // Seleciona disposito SPI que será utilizado. 
  
  if(file.open(&root, arquivo[dosadora_selecionada], O_WRITE))
  {
    file.remove();
  }  
  if(file.open(&root, arquivo[dosadora_selecionada], O_CREAT | O_APPEND | O_WRITE))
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
void check_dosagem_personalizada_1()
{
  int16_t n;
  char buf[7];
  int minuto01 = 0;
  int minuto11 = 0;

  if(modo_personalizado_on_1 == true) 
  {
    if((segunda_dosagem_personalizada_1 == t.dow)|| (terca_dosagem_personalizada_1 == t.dow) || (quarta_dosagem_personalizada_1 == t.dow)
      || (quarta_dosagem_personalizada_1 == t.dow) || (quinta_dosagem_personalizada_1 == t.dow) || (sexta_dosagem_personalizada_1 == t.dow)
      || (sabado_dosagem_personalizada_1 == t.dow) || (domingo_dosagem_personalizada_1 == t.dow))
    {
      selecionar_SPI(SD_CARD);
      if(file.open(&root, "HDP1.TXT", O_READ))
      {
        while ((n = file.read(buf, sizeof(buf))) > 0)
        {
          minuto01 = atoi(buf);
          if(minuto01 ==  NumMins(t.hour,t.min))
          {
            tempo_dosagem = map (((dose_dosadora_1_personalizada/quantidade_dose_dosadora_1_personalizada)*2), 0, fator_calib_dosadora_1, 0, 60000);
            tempo_dosagem /= 2;                 
            digitalWrite(dosadora1, HIGH);
            delay(tempo_dosagem);
            digitalWrite(dosadora1, LOW);
          }
        }
      }
      file.close();
    }
  }
}

void check_dosagem_personalizada_2()
{
  int16_t n;
  char buf[7];
  int minuto01 = 0;
  int minuto11 = 0;

  if(modo_personalizado_on_2 == true)
  {
    if((segunda_dosagem_personalizada_2 == t.dow)|| (terca_dosagem_personalizada_2 == t.dow) || (quarta_dosagem_personalizada_2 == t.dow)
      || (quarta_dosagem_personalizada_2 == t.dow) || (quinta_dosagem_personalizada_2 == t.dow) || (sexta_dosagem_personalizada_2 == t.dow)
      || (sabado_dosagem_personalizada_2 == t.dow) || (domingo_dosagem_personalizada_2 == t.dow))
    {
      selecionar_SPI(SD_CARD);      
      if(file.open(&root, "HDP2.TXT", O_READ))
      {
        while ((n = file.read(buf, sizeof(buf))) > 0)
        {
          minuto01 = atoi(buf);
          if(minuto01 ==  NumMins(t.hour,t.min))
          {
            tempo_dosagem = map (((dose_dosadora_2_personalizada/quantidade_dose_dosadora_2_personalizada)*2), 0, fator_calib_dosadora_2, 0, 60000);
            tempo_dosagem /= 2;                 
            digitalWrite(dosadora2, HIGH);
            delay(tempo_dosagem);
            digitalWrite(dosadora2, LOW);
          }
        }
      }
      file.close();
    }
  }    
}
void check_dosagem_personalizada_3()
{
  int16_t n;
  char buf[7];
  int minuto01 = 0;
  int minuto11 = 0;

  if(modo_personalizado_on_3 == true)
  {
    if((segunda_dosagem_personalizada_3 == t.dow)|| (terca_dosagem_personalizada_3 == t.dow) || (quarta_dosagem_personalizada_3 == t.dow)
      || (quarta_dosagem_personalizada_3 == t.dow) || (quinta_dosagem_personalizada_3 == t.dow) || (sexta_dosagem_personalizada_3 == t.dow)
      || (sabado_dosagem_personalizada_3 == t.dow) || (domingo_dosagem_personalizada_3 == t.dow))
    {
      selecionar_SPI(SD_CARD);
      if(file.open(&root, "HDP3.TXT", O_READ))
      {
        while ((n = file.read(buf, sizeof(buf))) > 0)
        {
          minuto01 = atoi(buf);
          if(minuto01 ==  NumMins(t.hour,t.min))
          {
            tempo_dosagem = map (((dose_dosadora_3_personalizada/quantidade_dose_dosadora_3_personalizada)*2), 0, fator_calib_dosadora_3, 0, 60000);
            tempo_dosagem /= 2;                 
            digitalWrite(dosadora3, HIGH);
            delay(tempo_dosagem);
            digitalWrite(dosadora3, LOW);
          }
        }
      }
      file.close();
    }
  } 
}

void check_dosagem_personalizada_4()
{
  int16_t n;
  char buf[7];
  int minuto01 = 0;
  int minuto11 = 0;

  if(modo_personalizado_on_4 == true)
  {
    if((segunda_dosagem_personalizada_4 == t.dow)|| (terca_dosagem_personalizada_4 == t.dow) || (quarta_dosagem_personalizada_4 == t.dow)
      || (quarta_dosagem_personalizada_4 == t.dow) || (quinta_dosagem_personalizada_4 == t.dow) || (sexta_dosagem_personalizada_4 == t.dow)
      || (sabado_dosagem_personalizada_4 == t.dow) || (domingo_dosagem_personalizada_4 == t.dow))
    {
      selecionar_SPI(SD_CARD);
      if(file.open(&root, "HDP4.TXT", O_READ))
      {
        while ((n = file.read(buf, sizeof(buf))) > 0)
        {
          minuto01 = atoi(buf);
          if(minuto01 ==  NumMins(t.hour,t.min))
          {
            tempo_dosagem = map (((dose_dosadora_4_personalizada/quantidade_dose_dosadora_4_personalizada)*2), 0, fator_calib_dosadora_4, 0, 60000);
            tempo_dosagem /= 2;                 
            digitalWrite(dosadora4, HIGH);
            delay(tempo_dosagem);
            digitalWrite(dosadora4, LOW);
          }
        }
      }
      file.close();
    }
  }    
}

void check_dosagem_personalizada_5()
{
  int16_t n;
  char buf[7];
  int minuto01 = 0;
  int minuto11 = 0;

  if(modo_personalizado_on_5 == true)
  {
    if((segunda_dosagem_personalizada_5 == t.dow)|| (terca_dosagem_personalizada_5 == t.dow) || (quarta_dosagem_personalizada_5 == t.dow)
      || (quarta_dosagem_personalizada_5 == t.dow) || (quinta_dosagem_personalizada_5 == t.dow) || (sexta_dosagem_personalizada_5 == t.dow)
      || (sabado_dosagem_personalizada_5 == t.dow) || (domingo_dosagem_personalizada_5 == t.dow))
    {
      selecionar_SPI(SD_CARD);
      if(file.open(&root, "HDP5.TXT", O_READ))
      {
        while ((n = file.read(buf, sizeof(buf))) > 0)
        {
          minuto01 = atoi(buf);
          if(minuto01 ==  NumMins(t.hour,t.min))
          {
            tempo_dosagem = map (((dose_dosadora_5_personalizada/quantidade_dose_dosadora_5_personalizada)*2), 0, fator_calib_dosadora_5, 0, 60000);
            tempo_dosagem /= 2;                 
            digitalWrite(dosadora5, HIGH);
            delay(tempo_dosagem);
            digitalWrite(dosadora5, LOW);
          }
        }
      }
      file.close();
    }
  }    
}

void check_dosagem_personalizada_6()
{
  int16_t n;
  char buf[7];
  int minuto01 = 0;
  int minuto11 = 0;

  if(modo_personalizado_on_6 == true)
  {
    if((segunda_dosagem_personalizada_6 == t.dow)|| (terca_dosagem_personalizada_6 == t.dow) || (quarta_dosagem_personalizada_6 == t.dow)
      || (quarta_dosagem_personalizada_6 == t.dow) || (quinta_dosagem_personalizada_6 == t.dow) || (sexta_dosagem_personalizada_6 == t.dow)
      || (sabado_dosagem_personalizada_6 == t.dow) || (domingo_dosagem_personalizada_6 == t.dow))
    {
      selecionar_SPI(SD_CARD);
      if(file.open(&root, "HDP6.TXT", O_READ))
      {
        while ((n = file.read(buf, sizeof(buf))) > 0)
        {
          minuto01 = atoi(buf);
          if(minuto01 ==  NumMins(t.hour,t.min))
          {
            tempo_dosagem = map (((dose_dosadora_6_personalizada/quantidade_dose_dosadora_6_personalizada)*2), 0, fator_calib_dosadora_6, 0, 60000);
            tempo_dosagem /= 2;                 
            digitalWrite(dosadora6, HIGH);
            delay(tempo_dosagem);
            digitalWrite(dosadora6, LOW);
          }
        }
      }
      file.close();
    }
  }    
}

void config_valores_dosadoras_temp()
{
  hora_inicial_dosagem_personalizada[0] = hora_inicial_dosagem_personalizada_1;
  minuto_inicial_dosagem_personalizada[0] = minuto_inicial_dosagem_personalizada_1;
  hora_final_dosagem_personalizada[0] = hora_final_dosagem_personalizada_1;
  minuto_final_dosagem_personalizada[0] = minuto_final_dosagem_personalizada_1;
  segunda_dosagem_personalizada[0] = segunda_dosagem_personalizada_1;
  terca_dosagem_personalizada[0] = terca_dosagem_personalizada_1;
  quarta_dosagem_personalizada[0] = quarta_dosagem_personalizada_1;
  quinta_dosagem_personalizada[0] = quinta_dosagem_personalizada_1;
  sexta_dosagem_personalizada[0] = sexta_dosagem_personalizada_1;
  sabado_dosagem_personalizada[0] = sabado_dosagem_personalizada_1;
  domingo_dosagem_personalizada[0] = domingo_dosagem_personalizada_1;
  hora_inicial_dosagem_personalizada[1] = hora_inicial_dosagem_personalizada_2;
  minuto_inicial_dosagem_personalizada[1] = minuto_inicial_dosagem_personalizada_2;
  hora_final_dosagem_personalizada[1] = hora_final_dosagem_personalizada_2;
  minuto_final_dosagem_personalizada[1] = minuto_final_dosagem_personalizada_2;
  segunda_dosagem_personalizada[1] = segunda_dosagem_personalizada_2;
  terca_dosagem_personalizada[1] = terca_dosagem_personalizada_2;
  quarta_dosagem_personalizada[1] = quarta_dosagem_personalizada_2;
  quinta_dosagem_personalizada[1] = quinta_dosagem_personalizada_2;
  sexta_dosagem_personalizada[1] = sexta_dosagem_personalizada_2;
  sabado_dosagem_personalizada[1] = sabado_dosagem_personalizada_2;
  domingo_dosagem_personalizada[1] = domingo_dosagem_personalizada_2;
  hora_inicial_dosagem_personalizada[2] = hora_inicial_dosagem_personalizada_3;
  minuto_inicial_dosagem_personalizada[2] = minuto_inicial_dosagem_personalizada_3;
  hora_final_dosagem_personalizada[2] = hora_final_dosagem_personalizada_3;
  minuto_final_dosagem_personalizada[2] = minuto_final_dosagem_personalizada_3;
  segunda_dosagem_personalizada[2] = segunda_dosagem_personalizada_3;
  terca_dosagem_personalizada[2] = terca_dosagem_personalizada_3;
  quarta_dosagem_personalizada[2] = quarta_dosagem_personalizada_3;
  quinta_dosagem_personalizada[2] = quinta_dosagem_personalizada_3;
  sexta_dosagem_personalizada[2] = sexta_dosagem_personalizada_3;
  sabado_dosagem_personalizada[2] = sabado_dosagem_personalizada_3;
  domingo_dosagem_personalizada[2] = domingo_dosagem_personalizada_3;
  hora_inicial_dosagem_personalizada[3] = hora_inicial_dosagem_personalizada_4;
  minuto_inicial_dosagem_personalizada[3] = minuto_inicial_dosagem_personalizada_4;
  hora_final_dosagem_personalizada[3] = hora_final_dosagem_personalizada_4;
  minuto_final_dosagem_personalizada[3] = minuto_final_dosagem_personalizada_4;
  segunda_dosagem_personalizada[3] = segunda_dosagem_personalizada_4;
  terca_dosagem_personalizada[3] = terca_dosagem_personalizada_4;
  quarta_dosagem_personalizada[3] = quarta_dosagem_personalizada_4;
  quinta_dosagem_personalizada[3] = quinta_dosagem_personalizada_4;
  sexta_dosagem_personalizada[3] = sexta_dosagem_personalizada_4;
  sabado_dosagem_personalizada[3] = sabado_dosagem_personalizada_4;
  domingo_dosagem_personalizada[3] = domingo_dosagem_personalizada_4;
  hora_inicial_dosagem_personalizada[4] = hora_inicial_dosagem_personalizada_5;
  minuto_inicial_dosagem_personalizada[4] = minuto_inicial_dosagem_personalizada_5;
  hora_final_dosagem_personalizada[4] = hora_final_dosagem_personalizada_5;
  minuto_final_dosagem_personalizada[4] = minuto_final_dosagem_personalizada_5;
  segunda_dosagem_personalizada[4] = segunda_dosagem_personalizada_5;
  terca_dosagem_personalizada[4] = terca_dosagem_personalizada_5;
  quarta_dosagem_personalizada[4] = quarta_dosagem_personalizada_5;
  quinta_dosagem_personalizada[4] = quinta_dosagem_personalizada_5;
  sexta_dosagem_personalizada[4] = sexta_dosagem_personalizada_5;
  sabado_dosagem_personalizada[4] = sabado_dosagem_personalizada_5;
  domingo_dosagem_personalizada[4] = domingo_dosagem_personalizada_5;
  hora_inicial_dosagem_personalizada[5] = hora_inicial_dosagem_personalizada_6;
  minuto_inicial_dosagem_personalizada[5] = minuto_inicial_dosagem_personalizada_6;
  hora_final_dosagem_personalizada[5] = hora_final_dosagem_personalizada_6;
  minuto_final_dosagem_personalizada[5] = minuto_final_dosagem_personalizada_6;
  segunda_dosagem_personalizada[5] = segunda_dosagem_personalizada_6;
  terca_dosagem_personalizada[5] = terca_dosagem_personalizada_6;
  quarta_dosagem_personalizada[5] = quarta_dosagem_personalizada_6;
  quinta_dosagem_personalizada[5] = quinta_dosagem_personalizada_6;
  sexta_dosagem_personalizada[5] = sexta_dosagem_personalizada_6;
  sabado_dosagem_personalizada[5] = sabado_dosagem_personalizada_6;
  domingo_dosagem_personalizada[5] = domingo_dosagem_personalizada_6; 
}

void config_valores_dosadoras_temp2()
{
  dose_dosadora_personalizada[0] = dose_dosadora_1_personalizada;
  dose_dosadora_personalizada[1] = dose_dosadora_2_personalizada;
  dose_dosadora_personalizada[2] = dose_dosadora_3_personalizada;
  quantidade_dose_dosadora_personalizada[0] = quantidade_dose_dosadora_1_personalizada;
  quantidade_dose_dosadora_personalizada[1] = quantidade_dose_dosadora_2_personalizada;
  quantidade_dose_dosadora_personalizada[2] = quantidade_dose_dosadora_3_personalizada;
  modo_personalizado_on[0] = modo_personalizado_on_1;
  modo_personalizado_on[1] = modo_personalizado_on_2;
  modo_personalizado_on[2] = modo_personalizado_on_3;
  dose_dosadora_personalizada[3] = dose_dosadora_4_personalizada;
  dose_dosadora_personalizada[4] = dose_dosadora_5_personalizada;
  dose_dosadora_personalizada[5] = dose_dosadora_6_personalizada;
  quantidade_dose_dosadora_personalizada[3] = quantidade_dose_dosadora_4_personalizada;
  quantidade_dose_dosadora_personalizada[4] = quantidade_dose_dosadora_5_personalizada;
  quantidade_dose_dosadora_personalizada[5] = quantidade_dose_dosadora_6_personalizada;
  modo_personalizado_on[3] = modo_personalizado_on_4;
  modo_personalizado_on[4] = modo_personalizado_on_5;
  modo_personalizado_on[5] = modo_personalizado_on_6; 
}

void config_valores_calib_temp()
{
  fator_calib_dosadora[0] = fator_calib_dosadora_1;
  fator_calib_dosadora[1] = fator_calib_dosadora_2;
  fator_calib_dosadora[2] = fator_calib_dosadora_3;
  fator_calib_dosadora[3] = fator_calib_dosadora_4;
  fator_calib_dosadora[4] = fator_calib_dosadora_5;
  fator_calib_dosadora[5] = fator_calib_dosadora_6;
}

void config_valores_salvar_dosadoras()
{
  dose_dosadora_1_personalizada = dose_dosadora_personalizada[0];
  quantidade_dose_dosadora_1_personalizada = quantidade_dose_dosadora_personalizada[0];
  modo_personalizado_on_1 = modo_personalizado_on[0];
  hora_inicial_dosagem_personalizada_1 = hora_inicial_dosagem_personalizada[0];
  minuto_inicial_dosagem_personalizada_1 = minuto_inicial_dosagem_personalizada[0];
  hora_final_dosagem_personalizada_1 = hora_final_dosagem_personalizada[0];
  minuto_final_dosagem_personalizada_1 = minuto_final_dosagem_personalizada[0];
  segunda_dosagem_personalizada_1 = segunda_dosagem_personalizada[0];
  terca_dosagem_personalizada_1 = terca_dosagem_personalizada[0];
  quarta_dosagem_personalizada_1 = quarta_dosagem_personalizada[0];
  quinta_dosagem_personalizada_1 = quinta_dosagem_personalizada[0];
  sexta_dosagem_personalizada_1 = sexta_dosagem_personalizada[0];
  sabado_dosagem_personalizada_1 = sabado_dosagem_personalizada[0];
  domingo_dosagem_personalizada_1 = domingo_dosagem_personalizada[0];

  dose_dosadora_2_personalizada = dose_dosadora_personalizada[1];
  quantidade_dose_dosadora_2_personalizada = quantidade_dose_dosadora_personalizada[1];
  modo_personalizado_on_2 = modo_personalizado_on[1];
  hora_inicial_dosagem_personalizada_2 = hora_inicial_dosagem_personalizada[1];
  minuto_inicial_dosagem_personalizada_2 = minuto_inicial_dosagem_personalizada[1];
  hora_final_dosagem_personalizada_2 = hora_final_dosagem_personalizada[1];
  minuto_final_dosagem_personalizada_2 = minuto_final_dosagem_personalizada[1];
  segunda_dosagem_personalizada_2 = segunda_dosagem_personalizada[1];
  terca_dosagem_personalizada_2 = terca_dosagem_personalizada[1];
  quarta_dosagem_personalizada_2 = quarta_dosagem_personalizada[1];
  quinta_dosagem_personalizada_2 = quinta_dosagem_personalizada[1];
  sexta_dosagem_personalizada_2 = sexta_dosagem_personalizada[1];
  sabado_dosagem_personalizada_2 = sabado_dosagem_personalizada[1];
  domingo_dosagem_personalizada_2 = domingo_dosagem_personalizada[1];

  dose_dosadora_3_personalizada = dose_dosadora_personalizada[2];
  quantidade_dose_dosadora_3_personalizada = quantidade_dose_dosadora_personalizada[2];
  modo_personalizado_on_3 = modo_personalizado_on[2];
  hora_inicial_dosagem_personalizada_3 = hora_inicial_dosagem_personalizada[2];
  minuto_inicial_dosagem_personalizada_3 = minuto_inicial_dosagem_personalizada[2];
  hora_final_dosagem_personalizada_3 = hora_final_dosagem_personalizada[2];
  minuto_final_dosagem_personalizada_3 = minuto_final_dosagem_personalizada[2];
  segunda_dosagem_personalizada_3 = segunda_dosagem_personalizada[2];
  terca_dosagem_personalizada_3 = terca_dosagem_personalizada[2];
  quarta_dosagem_personalizada_3 = quarta_dosagem_personalizada[2];
  quinta_dosagem_personalizada_3 = quinta_dosagem_personalizada[2];
  sexta_dosagem_personalizada_3 = sexta_dosagem_personalizada[2];
  sabado_dosagem_personalizada_3 = sabado_dosagem_personalizada[2];
  domingo_dosagem_personalizada_3 = domingo_dosagem_personalizada[2];

  dose_dosadora_4_personalizada = dose_dosadora_personalizada[3];
  quantidade_dose_dosadora_4_personalizada = quantidade_dose_dosadora_personalizada[3];
  modo_personalizado_on_4 = modo_personalizado_on[3];
  hora_inicial_dosagem_personalizada_4 = hora_inicial_dosagem_personalizada[3];
  minuto_inicial_dosagem_personalizada_4 = minuto_inicial_dosagem_personalizada[3];
  hora_final_dosagem_personalizada_4 = hora_final_dosagem_personalizada[3];
  minuto_final_dosagem_personalizada_4 = minuto_final_dosagem_personalizada[3];
  segunda_dosagem_personalizada_4 = segunda_dosagem_personalizada[3];
  terca_dosagem_personalizada_4 = terca_dosagem_personalizada[3];
  quarta_dosagem_personalizada_4 = quarta_dosagem_personalizada[3];
  quinta_dosagem_personalizada_4 = quinta_dosagem_personalizada[3];
  sexta_dosagem_personalizada_4 = sexta_dosagem_personalizada[3];
  sabado_dosagem_personalizada_4 = sabado_dosagem_personalizada[3];
  domingo_dosagem_personalizada_4 = domingo_dosagem_personalizada[3];

  dose_dosadora_5_personalizada = dose_dosadora_personalizada[4];
  quantidade_dose_dosadora_5_personalizada = quantidade_dose_dosadora_personalizada[4];
  modo_personalizado_on_5 = modo_personalizado_on[4];
  hora_inicial_dosagem_personalizada_5 = hora_inicial_dosagem_personalizada[4];
  minuto_inicial_dosagem_personalizada_5 = minuto_inicial_dosagem_personalizada[4];
  hora_final_dosagem_personalizada_5 = hora_final_dosagem_personalizada[4];
  minuto_final_dosagem_personalizada_5 = minuto_final_dosagem_personalizada[4];
  segunda_dosagem_personalizada_5 = segunda_dosagem_personalizada[4];
  terca_dosagem_personalizada_5 = terca_dosagem_personalizada[4];
  quarta_dosagem_personalizada_5 = quarta_dosagem_personalizada[4];
  quinta_dosagem_personalizada_5 = quinta_dosagem_personalizada[4];
  sexta_dosagem_personalizada_5 = sexta_dosagem_personalizada[4];
  sabado_dosagem_personalizada_5 = sabado_dosagem_personalizada[4];
  domingo_dosagem_personalizada_5 = domingo_dosagem_personalizada[4];

  dose_dosadora_6_personalizada = dose_dosadora_personalizada[5];
  quantidade_dose_dosadora_6_personalizada = quantidade_dose_dosadora_personalizada[5];
  modo_personalizado_on_6 = modo_personalizado_on[5];
  hora_inicial_dosagem_personalizada_6 = hora_inicial_dosagem_personalizada[5];
  minuto_inicial_dosagem_personalizada_6 = minuto_inicial_dosagem_personalizada[5];
  hora_final_dosagem_personalizada_6 = hora_final_dosagem_personalizada[5];
  minuto_final_dosagem_personalizada_6 = minuto_final_dosagem_personalizada[5];
  segunda_dosagem_personalizada_6 = segunda_dosagem_personalizada[5];
  terca_dosagem_personalizada_6 = terca_dosagem_personalizada[5];
  quarta_dosagem_personalizada_6 = quarta_dosagem_personalizada[5];
  quinta_dosagem_personalizada_6 = quinta_dosagem_personalizada[5];
  sexta_dosagem_personalizada_6 = sexta_dosagem_personalizada[5];
  sabado_dosagem_personalizada_6 = sabado_dosagem_personalizada[5];
  domingo_dosagem_personalizada_6 = domingo_dosagem_personalizada[5];
}



