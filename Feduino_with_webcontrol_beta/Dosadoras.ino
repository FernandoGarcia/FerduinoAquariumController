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
void check_dosagem_personalizada()
{
  int16_t n;
  char buf[7];
  int minuto01 = 0;
  int minuto11 = 0;

  for(byte i = 0; i < 6; i++)
  {
    if(modo_personalizado_on_e[i] == true) 
    {
      if((segunda_dosagem_personalizada_e[i] == t.dow)|| (terca_dosagem_personalizada_e[i] == t.dow) || (quarta_dosagem_personalizada_e[i] == t.dow)
        || (quarta_dosagem_personalizada_e[i] == t.dow) || (quinta_dosagem_personalizada_e[i] == t.dow) || (sexta_dosagem_personalizada_e[i] == t.dow)
        || (sabado_dosagem_personalizada_e[i] == t.dow) || (domingo_dosagem_personalizada_e[i] == t.dow))
      {
        selecionar_SPI(SD_CARD);
        delay(50);

        if(file.open(&root, arquivo[i], O_READ))
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
            }
          }
        }
        file.close();
      }
    }
  }
}
/*
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
 */

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
