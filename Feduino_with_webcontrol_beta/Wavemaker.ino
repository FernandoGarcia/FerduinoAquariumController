void Grafico_WaveMaker()
{  
  int Pump1PWM_t;
  int Pump2PWM_t;

  int bar = map(Pump1PWM, 0, 255, 225, 97);   

  if (bar < 97 )
  {
    bar = 97;
  }
  if (bar > 225)
  {
    bar = 225;
  }

  int bar2 = map(Pump2PWM, 0, 255, 225, 97);   

  if (bar2 < 97)
  {
    bar2 = 97;
  } 
  if (bar2 > 225)
  {
    bar2 = 225;
  }

  Pump1PWM_t = map(Pump1PWM, 0, 255, 0, 100);  
  Pump2PWM_t = map(Pump2PWM, 0, 255, 0, 100);

  myGLCD.setBackColor(0, 0, 0); 
  myGLCD.setColor(0, 0, 0);

  myGLCD.fillRect(251, bar - 1, 272, 91); 
  myGLCD.fillRect(280, bar2 - 1, 301, 91); 

  myGLCD.setColor(0, 0, 255);              

  myGLCD.fillRect(251, 225, 272, bar); 
  myGLCD.fillRect(280, 225, 301, bar2); 

  myGLCD.setFont(RusFont1);

  if(Pump1PWM_t < 10)
  {
    myGLCD.setColor(255, 255, 0);
    myGLCD.printNumI(Pump1PWM_t, 256, 80); 
    myGLCD.setColor(0, 0, 0);
    myGLCD.print("  ", 264, 80);
  }
  else if ((Pump1PWM_t >= 10) && (Pump1PWM_t <= 99))
  {
    myGLCD.setColor(255, 255, 0);
    myGLCD.printNumI(Pump1PWM_t, 256, 80); 
    myGLCD.setColor(0, 0, 0);
    myGLCD.print(" ", 272, 80);
  }
  else
  {
    myGLCD.setColor(255, 255, 0);
    myGLCD.printNumI(Pump1PWM_t, 256, 80);
  }

  if(Pump2PWM_t < 10)
  {
    myGLCD.setColor(255, 255, 0);
    myGLCD.printNumI(Pump2PWM_t, 285, 80);
    myGLCD.setColor(0, 0, 0);
    myGLCD.print("   ", 293, 80);
  }
  else if((Pump2PWM_t >= 10) && (Pump2PWM_t <= 99))
  {
    myGLCD.setColor(255, 255, 0);
    myGLCD.printNumI(Pump2PWM_t, 285, 80); 
    myGLCD.setColor(0, 0, 0);
    myGLCD.print(" ", 301, 80);
  }
  else
  {
    myGLCD.printNumI(Pump2PWM_t, 285, 80);  
  }
}

void Wavemaker()
{ 
  int value = 0;
  long times = millis();

  if(modo_selecionado == 1)
  {
    value = int(128 + 127 * sin(2  *  PI / periodo * times));
    Pump1PWM = 255 - value;
    Pump2PWM = value;
  }

  else if(modo_selecionado == 2)
  {
    value = int(128 + 127 * sin(2  *  PI / periodo * times));
    Pump1PWM = value;
    Pump2PWM = value;
  }

  else if(modo_selecionado == 3)
  {
    byte PWM1 [] = {128, 172, 205, 222, 225, 214, 187, 190, 203, 205, 198, 181, 173, 182, 185, 181, 171, 155, 159, 163, 163, 157, 146, 128, 210, 246, 254, 240, 207, 128}; // Opposite
    byte PWM2 [] = {128, 146, 157, 163, 163, 159, 155, 171, 181, 185, 182, 173, 181, 198, 205, 203, 190, 187, 214, 225, 222, 205, 172, 128, 210, 246, 254, 240, 207, 128};  // Same

    int millis1 = millis() - millis_antes_1;

    Pump1PWM = int(map(millis1, 0, duracao, PWM1 [conta], PWM1 [conta+1]));
    Pump2PWM = int(map(millis1, 0, duracao, PWM2 [conta], PWM2 [conta+1]));

    if ((millis() - millis_antes_1) >= duracao)
    {
      millis_antes_1 = millis();
      conta++;
    }

    if ( conta >= 29) // Opposite and same
    {
      conta = 0;
    }
  }

  else if(modo_selecionado == 4)
  {
    if ((millis() - millis_antes_1) >= duracao)
    {
      millis_antes_1 = millis();
      conta +=1;
      value = int(128 + 127 * sin(2 * PI / 400 * times));
      Pump1PWM = 255 - value;
      Pump2PWM = value;  

      if(conta < 61)
      {
        if (Pump1PWM < 128)
        {
          Pump1PWM += 128;
        }
        if (Pump2PWM < 128)
        {
          Pump2PWM += 128;
        }
      }
      else if(conta > 81)
      {
        if (Pump1PWM < 128)
        {
          Pump1PWM += 128;
        }
        if (Pump2PWM < 128)
        {
          Pump2PWM += 128;
        }
      }
      else if((conta >= 61) && (conta <= 81))
      {
        if (Pump1PWM < 128)
        {
          Pump1PWM += 50;
        }
        if (Pump2PWM < 128)
        {
          Pump2PWM += 50;
        }
      }
    }

    if (conta >= 142) // Opposite and same
    {
      conta = 0;
    }
  }
else if(modo_selecionado == 5)
{
 Pump1PWM = Pump1PWM_temp;
 Pump2PWM = Pump2PWM_temp;
}
  if(Pump1PWM > 255)
  {
    Pump1PWM = 255;
  }
  else if(Pump1PWM < 0)
  {
    Pump1PWM = 0;
  }
  else if(Pump2PWM > 255)
  {
    Pump2PWM = 255;
  } 
  else if(Pump2PWM < 0)
  {
    Pump2PWM = 0;
  }
  analogWrite(wavemaker1, Pump1PWM);
  analogWrite(wavemaker2, Pump2PWM);
}




