void check_temporizadores()
{

  if ((temporizador_1_ativado == 1) && (bitRead(temporizador_modificado,1) == false))
  {  
    if(NumMins(off1_hora,off1_minuto) > NumMins(on1_hora,on1_minuto))
    {
      if((NumMins(t.hour,t.min) >= NumMins(on1_hora,on1_minuto)) && (NumMins(t.hour,t.min) <= NumMins(off1_hora,off1_minuto)))
      {
        digitalWrite(temporizador1, HIGH);
        bitWrite(temporizador_status,1,1);
      }
      if (NumMins(t.hour,t.min) > NumMins(off1_hora,off1_minuto))
      {
        digitalWrite(temporizador1, LOW);
        bitWrite(temporizador_status,1,0);
      }
    }
    if(NumMins(off1_hora,off1_minuto) < NumMins(on1_hora,on1_minuto))
    {                     
      if(NumMins(t.hour,t.min) >= NumMins(on1_hora,on1_minuto)) 
      {
        digitalWrite(temporizador1, HIGH);
        bitWrite(temporizador_status,1,1);
      }

      if (NumMins(t.hour,t.min) < NumMins(off1_hora,off1_minuto)) 
      {
        digitalWrite(temporizador1, HIGH);
        bitWrite(temporizador_status,1,1);
      }     
      if ((NumMins(t.hour,t.min) >= NumMins(off1_hora,off1_minuto)) && (NumMins(t.hour,t.min) < NumMins(on1_hora,on1_minuto)))
      {
        digitalWrite(temporizador1, LOW);
        bitWrite(temporizador_status,1,0);
      } 
    }
  }
  else
  {
    digitalWrite(temporizador1, LOW);
    bitWrite(temporizador_status,1,0);
    bitWrite(temporizador_modificado,1,0);
  }
  if ((temporizador_2_ativado == 1)  && (bitRead(temporizador_modificado,2) == false))
  {
    if(NumMins(off2_hora,off2_minuto) > NumMins(on2_hora,on2_minuto))
    {
      if((NumMins(t.hour,t.min) >= NumMins(on2_hora,on2_minuto)) && (NumMins(t.hour,t.min) <= NumMins(off2_hora,off2_minuto)))
      {
        digitalWrite(temporizador2, HIGH);
        bitWrite(temporizador_status,2,1);
      }
      if (NumMins(t.hour,t.min) > NumMins(off2_hora,off2_minuto))
      {
        digitalWrite(temporizador2, LOW);
        bitWrite(temporizador_status,2,0);
      }
    }
    if(NumMins(off2_hora,off2_minuto) < NumMins(on2_hora,on2_minuto))
    {                     
      if(NumMins(t.hour,t.min) >= NumMins(on2_hora,on2_minuto)) 
      {
        digitalWrite(temporizador2, HIGH);
        bitWrite(temporizador_status,2,1);
      }

      if (NumMins(t.hour,t.min) < NumMins(off2_hora,off2_minuto)) 
      {
        digitalWrite(temporizador2, HIGH);
        bitWrite(temporizador_status,2,1);
      }     
      if ((NumMins(t.hour,t.min) >= NumMins(off2_hora,off2_minuto)) && (NumMins(t.hour,t.min) < NumMins(on2_hora,on2_minuto)))
      {
        digitalWrite(temporizador2, LOW);
        bitWrite(temporizador_status,2,0);
      } 
    }
  }
  else
  {
    digitalWrite(temporizador2, LOW);
    bitWrite(temporizador_status,2,0);
    bitWrite(temporizador_modificado,2,0);
  }  
  if ((temporizador_3_ativado == 1) && (bitRead(temporizador_modificado,3) == false)) 
  {  
    if(NumMins(off3_hora,off3_minuto) > NumMins(on3_hora,on3_minuto))
    {
      if((NumMins(t.hour,t.min) >= NumMins(on3_hora,on3_minuto)) && (NumMins(t.hour,t.min) <= NumMins(off3_hora,off3_minuto)))
      {
        digitalWrite(temporizador3, HIGH);
        bitWrite(temporizador_status,3,1);
      }
      if (NumMins(t.hour,t.min) > NumMins(off3_hora,off3_minuto))
      {
        digitalWrite(temporizador3, LOW);
        bitWrite(temporizador_status,3,0);
      }
    }
    if(NumMins(off3_hora,off3_minuto) < NumMins(on3_hora,on3_minuto))
    {                     
      if(NumMins(t.hour,t.min) >= NumMins(on3_hora,on3_minuto)) 
      {
        digitalWrite(temporizador3, HIGH);
        bitWrite(temporizador_status,3,1);
      }

      if (NumMins(t.hour,t.min) < NumMins(off3_hora,off3_minuto)) 
      {
        digitalWrite(temporizador3, HIGH);
        bitWrite(temporizador_status,3,1);
      }     
      if ((NumMins(t.hour,t.min) >= NumMins(off3_hora,off3_minuto)) && (NumMins(t.hour,t.min) < NumMins(on3_hora,on3_minuto)))
      {
        digitalWrite(temporizador3, LOW);
        bitWrite(temporizador_status,3,0);
      } 
    }
  }
  else
  {
    digitalWrite(temporizador3, LOW);
    bitWrite(temporizador_status,3,0);
    bitWrite(temporizador_modificado,3,0);  
  } 
  if ((temporizador_4_ativado == 1) && (bitRead(temporizador_modificado,4) == false)) 
  {  
    if(NumMins(off4_hora,off4_minuto) > NumMins(on4_hora,on4_minuto))
    {
      if((NumMins(t.hour,t.min) >= NumMins(on4_hora,on4_minuto)) && (NumMins(t.hour,t.min) <= NumMins(off4_hora,off4_minuto)))
      {
        digitalWrite(temporizador4, HIGH);
        bitWrite(temporizador_status,4,1);
      }
      if (NumMins(t.hour,t.min) > NumMins(off4_hora,off4_minuto))
      {
        digitalWrite(temporizador4, LOW);
        bitWrite(temporizador_status,4,0);
      }
    }
    if(NumMins(off4_hora,off4_minuto) < NumMins(on4_hora,on4_minuto))
    {                     
      if(NumMins(t.hour,t.min) >= NumMins(on4_hora,on4_minuto)) 
      {
        digitalWrite(temporizador4, HIGH);
        bitWrite(temporizador_status,4,1);
      }

      if (NumMins(t.hour,t.min) < NumMins(off4_hora,off4_minuto)) 
      {
        digitalWrite(temporizador4, HIGH);
        bitWrite(temporizador_status,4,1);
      }     
      if ((NumMins(t.hour,t.min) >= NumMins(off4_hora,off4_minuto)) && (NumMins(t.hour,t.min) < NumMins(on4_hora,on4_minuto)))
      {
        digitalWrite(temporizador4, LOW);
        bitWrite(temporizador_status,4,0);
      } 
    }
  }
  else
  {
    digitalWrite(temporizador4, LOW);
    bitWrite(temporizador_status,4,0);
    bitWrite(temporizador_modificado,4,0);   
  }
  if ((temporizador_5_ativado == 1) && (bitRead(temporizador_modificado,5) == false))
  {  
    if(NumMins(off5_hora,off5_minuto) > NumMins(on5_hora,on5_minuto))
    {
      if((NumMins(t.hour,t.min) >= NumMins(on5_hora,on5_minuto)) && (NumMins(t.hour,t.min) <= NumMins(off5_hora,off5_minuto)))
      {
        digitalWrite(temporizador5, HIGH);
        bitWrite(temporizador_status,5,1);
      }
      if (NumMins(t.hour,t.min) > NumMins(off5_hora,off5_minuto))
      {
        digitalWrite(temporizador5, LOW);
        bitWrite(temporizador_status,5,0);
      }
    }
    if(NumMins(off5_hora,off5_minuto) < NumMins(on5_hora,on5_minuto))
    {                     
      if(NumMins(t.hour,t.min) >= NumMins(on5_hora,on5_minuto)) 
      {
        digitalWrite(temporizador5, HIGH);
        bitWrite(temporizador_status,5,1);
      }

      if (NumMins(t.hour,t.min) < NumMins(off5_hora,off5_minuto)) 
      {
        digitalWrite(temporizador5, HIGH);
        bitWrite(temporizador_status,5,1);
      }     
      if ((NumMins(t.hour,t.min) >= NumMins(off5_hora,off5_minuto)) && (NumMins(t.hour,t.min) < NumMins(on5_hora,on5_minuto)))
      {
        digitalWrite(temporizador5, LOW);
        bitWrite(temporizador_status,5,0);
      } 
    }
  }
  else
  {
    digitalWrite(temporizador5, LOW);
    bitWrite(temporizador_status,5,0);
    bitWrite(temporizador_modificado,5,0);
  }  
}

void config_valores_timers_temp()
{
  on_minuto[0] = on1_minuto;
  on_hora[0] = on1_hora;
  on_minuto[1] = on2_minuto;
  on_hora[1] = on2_hora;
  on_minuto[2] = on3_minuto;
  on_hora[2] = on3_hora;
  on_minuto[3] = on4_minuto;
  on_hora[3] = on4_hora;
  on_minuto[4] = on5_minuto;
  on_hora[4] = on5_hora ;
  off_minuto[0] = off1_minuto;
  off_hora[0] = off1_hora;
  off_minuto[1] = off2_minuto;
  off_hora[1] = off2_hora;
  off_minuto[2] = off3_minuto;
  off_hora[2] = off3_hora;
  off_minuto[3] = off4_minuto;
  off_hora[3] = off4_hora;
  off_minuto[4] = off5_minuto;
  off_hora[4] = off5_hora;
  temporizador_ativado[0] = temporizador_1_ativado;
  temporizador_ativado[1] = temporizador_2_ativado;
  temporizador_ativado[2] = temporizador_3_ativado;
  temporizador_ativado[3] = temporizador_4_ativado;
  temporizador_ativado[4] = temporizador_5_ativado;
}

void config_valore_salvat_timers()
{
  on1_minuto = on_minuto[0];
  on1_hora = on_hora[0];
  off1_minuto = off_minuto[0];
  off1_hora = off_hora[0];
  temporizador_1_ativado = temporizador_ativado[0];

  on2_minuto = on_minuto[1];
  on2_hora = on_hora[1];
  off2_minuto = off_minuto[1];
  off2_hora = off_hora[1];
  temporizador_2_ativado = temporizador_ativado[1];

  on3_minuto = on_minuto[2];
  on3_hora = on_hora[2];
  off3_minuto = off_minuto[2];
  off3_hora = off_hora[2];
  temporizador_3_ativado = temporizador_ativado[2];

  on4_minuto = on_minuto[3];
  on4_hora = on_hora[3];
  off4_minuto = off_minuto[3];
  off4_hora = off_hora[3];
  temporizador_4_ativado = temporizador_ativado[3];

  on5_minuto = on_minuto[4];
  on5_hora = on_hora[4];
  off5_minuto = off_minuto[4];
  off5_hora = off_hora[4];
  temporizador_5_ativado = temporizador_ativado[4]; 
}

