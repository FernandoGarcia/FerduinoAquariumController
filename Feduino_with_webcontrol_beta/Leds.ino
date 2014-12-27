
int LedToPercent (int Led_out)        //returns LED output in %
{
  int result;

  if (Led_out==0) {
    result = 0; 
  }
  else {
    result = map(Led_out, 1, 255, 1, 100);  
  }

  return result; 
}
//---------------------------LED levels---------------------------
void LED_levels_output()
{
  int sector, sstep, t1, t2 ;
  float reduzir = 1.00;
  byte b_out, w_out, moon_out, rb_out, r_out, uv_out;

  if(tempH >= tempHR)
  {
    reduzir = (1 - (potR *.01));
    temperatura_alta = true;
    temperatura_baixou = false;
  } 
  if(temperatura_alta == true)
  {
    if(tempH <= (tempHR - 5)) // Se a temperatura estiver 5°C abaixo do especificado a potência volta ao valor normal.   
    {
      reduzir = 1.00;
      temperatura_alta = false;
      temperatura_baixou = true;
    }
    else
    {
      reduzir = (1 - (potR *.01));
      temperatura_baixou = false;    
    }
  }    

  if((teste_em_andamento == true) && (LEDtestTick == false))
  {
    bled_out = bled_out_temp;
    wled_out = wled_out_temp;
    rbled_out = rbled_out_temp;
    rled_out = rled_out_temp;
    uvled_out = uvled_out_temp;
  }
  else if((pre_definido_ativado == 1) && (LEDtestTick == false))
  {
    if (hora_modificada == false)
    {  
      if(NumMins(led_off_hora,led_off_minuto) > NumMins(led_on_hora,led_on_minuto))
      {
        if((NumMins(t.hour,t.min) >= (NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer)) && (NumMins(t.hour,t.min) <= (NumMins(led_off_hora,led_off_minuto + amanhecer_anoitecer))))
        {
          if(predefinido == 1) // Controla todos juntos
          {
            if((NumMins(t.hour,t.min) >= (NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer)) && (NumMins(t.hour,t.min) <= NumMins(led_on_hora,led_on_minuto)))
            { 
              bled_out = wled_out = rbled_out  = rled_out = uvled_out = map(NumMins(t.hour,t.min),(NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer), NumMins(led_on_hora,led_on_minuto), 0, pwm_pre_definido);
            }
            else if((NumMins(t.hour,t.min) >= NumMins(led_off_hora,led_off_minuto)) && (NumMins(t.hour,t.min) <= (NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer)))
            {
              bled_out = wled_out = rbled_out  = rled_out = uvled_out = map(NumMins(t.hour,t.min), NumMins(led_off_hora,led_off_minuto), (NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer), pwm_pre_definido, 0);
            }
            else
            {
              bled_out = wled_out = rbled_out  = rled_out = uvled_out = pwm_pre_definido;
            }    
          }
          else // Controla individualmente
          {
            if((NumMins(t.hour,t.min) >= (NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer)) && (NumMins(t.hour,t.min) <= NumMins(led_on_hora,led_on_minuto)))
            {
              bled_out = map(NumMins(t.hour,t.min),(NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer), NumMins(led_on_hora,led_on_minuto), 0, bled_out_temp);
              wled_out = map(NumMins(t.hour,t.min),(NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer), NumMins(led_on_hora,led_on_minuto), 0, wled_out_temp);
              rbled_out  = map(NumMins(t.hour,t.min),(NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer), NumMins(led_on_hora,led_on_minuto), 0, rbled_out_temp);
              rled_out = map(NumMins(t.hour,t.min),(NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer), NumMins(led_on_hora,led_on_minuto), 0, rled_out_temp);
              uvled_out = map(NumMins(t.hour,t.min),(NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer), NumMins(led_on_hora,led_on_minuto), 0, uvled_out_temp);
            }
            else if((NumMins(t.hour,t.min) >= NumMins(led_off_hora,led_off_minuto)) && (NumMins(t.hour,t.min) <= (NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer)))
            {
              bled_out = map(NumMins(t.hour,t.min), NumMins(led_off_hora,led_off_minuto), (NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer), bled_out_temp, 0);
              wled_out = map(NumMins(t.hour,t.min), NumMins(led_off_hora,led_off_minuto), (NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer), wled_out_temp, 0);
              rbled_out = map(NumMins(t.hour,t.min), NumMins(led_off_hora,led_off_minuto), (NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer), rbled_out_temp, 0);
              rled_out = map(NumMins(t.hour,t.min), NumMins(led_off_hora,led_off_minuto), (NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer), rled_out_temp, 0);
              uvled_out = map(NumMins(t.hour,t.min), NumMins(led_off_hora,led_off_minuto), (NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer), uvled_out_temp, 0);
            }
            else
            {
              bled_out = bled_out_temp;
              wled_out = wled_out_temp;
              rbled_out = rbled_out_temp;
              rled_out = rled_out_temp;
              uvled_out = uvled_out_temp;
            }
          }
        }
        else
        {
          bled_out = wled_out = rbled_out  = rled_out = uvled_out = 0;
        }
      }
      else if(NumMins(led_off_hora,led_off_minuto) < NumMins(led_on_hora,led_on_minuto)) 
      {                   
        if(predefinido == 1) // Controla todos juntos
        {
          if(NumMins(t.hour,t.min) >= (NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer)) 
          {   
            if((NumMins(t.hour,t.min) >= (NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer)) && (NumMins(t.hour,t.min) <= NumMins(led_on_hora,led_on_minuto)))
            { 
              bled_out = wled_out = rbled_out  = rled_out = uvled_out = map(NumMins(t.hour,t.min),(NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer), NumMins(led_on_hora,led_on_minuto), 0, pwm_pre_definido);
            }
            else 
            {
              bled_out = wled_out = rbled_out  = rled_out = uvled_out = pwm_pre_definido;  
            }
          }
          else if(NumMins(t.hour,t.min) <= (NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer))
          { 
            if((NumMins(t.hour,t.min) <= (NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer)) && (NumMins(t.hour,t.min) >= NumMins(led_off_hora,led_off_minuto)))
            {
              bled_out = wled_out = rbled_out  = rled_out = uvled_out = map(NumMins(t.hour,t.min),(NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer), NumMins(led_off_hora,led_off_minuto), 0, pwm_pre_definido);
            }
            else 
            {
              bled_out = wled_out = rbled_out  = rled_out = uvled_out = pwm_pre_definido;  
            }
          }
          else
          {
            bled_out = wled_out = rbled_out  = rled_out = uvled_out = 0;          
          }
        }
        else  // Controla individualmente
        {
          if(NumMins(t.hour,t.min) >= (NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer)) 
          {   
            if((NumMins(t.hour,t.min) >= (NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer)) && (NumMins(t.hour,t.min) <= NumMins(led_on_hora,led_on_minuto)))
            { 
              bled_out = map(NumMins(t.hour,t.min),(NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer), NumMins(led_on_hora,led_on_minuto), 0, bled_out_temp);
              wled_out = map(NumMins(t.hour,t.min),(NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer), NumMins(led_on_hora,led_on_minuto), 0, wled_out_temp);
              rbled_out  = map(NumMins(t.hour,t.min),(NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer), NumMins(led_on_hora,led_on_minuto), 0, rbled_out_temp);
              rled_out = map(NumMins(t.hour,t.min),(NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer), NumMins(led_on_hora,led_on_minuto), 0, rled_out_temp);
              uvled_out = map(NumMins(t.hour,t.min),(NumMins(led_on_hora,led_on_minuto) - amanhecer_anoitecer), NumMins(led_on_hora,led_on_minuto), 0, uvled_out_temp);
            }
            else 
            {
              bled_out = bled_out_temp;
              wled_out = wled_out_temp;
              rbled_out = rbled_out_temp;
              rled_out = rled_out_temp;
              uvled_out = uvled_out_temp;  
            }
          }
          else if(NumMins(t.hour,t.min) <= (NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer))
          { 
            if((NumMins(t.hour,t.min) <= (NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer)) && (NumMins(t.hour,t.min) >= NumMins(led_off_hora,led_off_minuto)))
            {
              bled_out = map(NumMins(t.hour,t.min),(NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer), NumMins(led_off_hora,led_off_minuto), 0, bled_out_temp);
              wled_out = map(NumMins(t.hour,t.min),(NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer), NumMins(led_off_hora,led_off_minuto), 0, wled_out_temp);
              rbled_out  = map(NumMins(t.hour,t.min),(NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer), NumMins(led_off_hora,led_off_minuto), 0, rbled_out_temp);
              rled_out = map(NumMins(t.hour,t.min),(NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer), NumMins(led_off_hora,led_off_minuto), 0, rled_out_temp);
              uvled_out = map(NumMins(t.hour,t.min),(NumMins(led_off_hora,led_off_minuto) + amanhecer_anoitecer), NumMins(led_off_hora,led_off_minuto), 0, uvled_out_temp);
            }
            else 
            {
              bled_out = bled_out_temp;
              wled_out = wled_out_temp;
              rbled_out = rbled_out_temp;
              rled_out = rled_out_temp;
              uvled_out = uvled_out_temp;  
            }
          }
          else
          {
            bled_out = wled_out = rbled_out  = rled_out = uvled_out = 0;          
          }
        }
      }
    }// se hora alterada == false
    else // Se hora alterada == true.
    {
      hora_modificada = false;
      bled_out = wled_out = rbled_out  = rled_out = uvled_out = 0;
    }
  }// predefinido ativado
  else
  {
    if (min_cnt > 1439) 
    {
      min_cnt = 0;
    }   // 24 hours of minutes 
    sector = min_cnt/15;              // divided by gives sector -- 15 minute
    sstep = min_cnt%15;               // remainder gives add on to sector value 

    t1 =sector;
    if (t1==95) 
    {
      t2=0;
    }
    else 
    {
      t2 = t1+1;
    }
    if (sstep==0) 
    {
      bled_out = (bled[t1]) * reduzir;
      wled_out = (wled[t1]) * reduzir;
      rbled_out = (rbled[t1]) * reduzir;
      rled_out = (rled[t1]) * reduzir;
      uvled_out = (uvled[t1]) * reduzir;    
    } 
    else 
    {
      bled_out = (check(&bled[t1], &bled[t2], sstep)) * reduzir;
      wled_out = (check(&wled[t1], &wled[t2], sstep)) * reduzir;
      rbled_out = (check(&rbled[t1], &rbled[t2], sstep)) * reduzir;
      rled_out = (check(&rled[t1], &rled[t2], sstep)) * reduzir;
      uvled_out = (check(&uvled[t1], &uvled[t2], sstep)) * reduzir;
    }
  }

  float lunarCycle = moonPhase(t.year, t.mon, t.date); //get a value for the lunar cycle
  moonled_out = ((MinI *(1 - lunarCycle)) + (MaxI * lunarCycle) + 0.5) * reduzir;

  if (MeanWell == true) 
  {
    b_out = bled_out;
    w_out = wled_out;
    rb_out = rbled_out;
    r_out = rled_out;
    uv_out = uvled_out;
    moon_out = moonled_out;
  } 
  else 
  {
    b_out = (255 - bled_out);
    w_out = (255 - wled_out);
    rb_out = (255 - rbled_out);
    r_out = (255 - rled_out);
    uv_out = (255 - uvled_out);
    moon_out = (255 - moonled_out);
  }
  if(suavizar < 1)
  {
    b_out = suavizar * b_out;
    w_out = suavizar * w_out;
    rb_out = suavizar * rb_out;
    r_out = suavizar * r_out;
    uv_out = suavizar * uv_out;
    moon_out = suavizar * moon_out;    
  }


  analogWrite(ledPinBlue, b_out);
  analogWrite(ledPinWhite, w_out);
  analogWrite(ledPinRoyBlue, rb_out);
  analogWrite(ledPinRed, r_out);
  analogWrite(ledPinUV, uv_out);
  analogWrite(ledPinMoon, moon_out);
}

int check( byte *pt1, byte *pt2, int lstep)
{
  int result;
  float fresult;

  if (*pt1==*pt2) {
    result = *pt1;
  }   // No change
  else if (*pt1<*pt2)                //Increasing brightness
  { 
    fresult = ((float(*pt2-*pt1)/15.0) * float(lstep))+float(*pt1);
    result = int(fresult);
  }
  //Decreasing brightness
  else {
    fresult = -((float(*pt1-*pt2)/15.0) * float(lstep))+float(*pt1);
    result = int(fresult);                     
  } 
  return result;
}
