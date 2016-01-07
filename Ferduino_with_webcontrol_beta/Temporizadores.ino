void check_temporizadores()
{
  for(byte i = 0; i < 5; i++)
  {
    if ((temporizador_ativado_e[i] == 1) && (bitRead(temporizador_modificado,1) == false))
    {  
      if(NumMins(off_hora_e[i], off_minuto_e[i]) > NumMins(on_hora_e[i], on_minuto_e[i]))
      {
        if((NumMins(t.hour,t.min) >= NumMins(on_hora_e[i], on_minuto_e[i])) && (NumMins(t.hour,t.min) < NumMins(off_hora_e[i], off_minuto_e[i])))
        {
          digitalWrite(temporizador_e[i], HIGH);
          bitWrite(temporizador_status, (i + 1), 1);
        }
        else
        {
          digitalWrite(temporizador_e[i], LOW);
          bitWrite(temporizador_status, (i + 1), 0);
        }
      }
      else if(NumMins(off_hora_e[i], off_minuto_e[i]) < NumMins(on_hora_e[i], on_minuto_e[i]))
      {                     
        if(NumMins(t.hour,t.min) >= NumMins(on_hora_e[i], on_minuto_e[i]) || (NumMins(t.hour,t.min) < NumMins(off_hora_e[i], off_minuto_e[i]))) 
        {
          digitalWrite(temporizador_e[i], HIGH);
          bitWrite(temporizador_status, (i + 1), 1);
        }    
        else
        {
          digitalWrite(temporizador_e[i], LOW);
          bitWrite(temporizador_status, (i + 1), 0);
        } 
      }
    }
    else
    {
      digitalWrite(temporizador_e[i], LOW);
      bitWrite(temporizador_status, (i + 1), 0);
      bitWrite(temporizador_modificado, (i + 1), 0);
    }
  }
}

void config_valores_timers_temp()
{
  for(byte i = 0; i < 5; i++)
  {
    on_minuto[i] = on_minuto_e[i];
    on_hora[i] = on_hora_e[i];
    off_minuto[i] = off_minuto_e[i];
    off_hora[i] = off_hora_e[i];
    temporizador_ativado[i] = temporizador_ativado_e[i];
  }
}

void config_valores_salvar_timers()
{
  for(byte i = 0; i < 5; i++)
  {
    on_minuto_e[i] = on_minuto[i];
    on_hora_e[i] = on_hora[i];
    off_minuto_e[i] = off_minuto[i];
    off_hora_e[i] = off_hora[i];
    temporizador_ativado_e[i] = temporizador_ativado[i];
  }
}
