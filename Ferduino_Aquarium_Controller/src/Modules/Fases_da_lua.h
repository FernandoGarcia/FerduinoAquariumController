//**********************************************************************************************
//********************** Funcoes fase da lua* **************************************************
//**********************************************************************************************
float moonPhase(int moonYear, int moonMonth, int moonDay)
{
  float LC = 29.53059;  // 1 ciclo lunar = 29.53059 dias.
  double AG; 
  float phase;
  double IP; 
  long YY, MM, K1, K2, K3, JulianDay; 
  YY = moonYear - floor((12 - moonMonth) / 10); 
  MM = moonMonth + 9;
  if (MM >= 12)
  { 
    MM = MM - 12; 
  }
  K1 = floor(365.25 * (YY + 4712));
  K2 = floor(30.6 * MM + 0.5);
  K3 = floor(floor((YY / 100) + 49) * 0.75) - 38;
  JulianDay = K1 + K2 + moonDay + 59;
  if (JulianDay > 2299160)
  { 
    JulianDay = JulianDay - K3; 
  }
  IP = MyNormalize((JulianDay - 2451550.1) / LC);
  AG = IP*LC;
  phase = 0; 

  //Determine the Moon Illumination %
  if ((AG >= 0) && (AG <= LC/2))            //FROM New Moon 0% TO Full Moon 100%
  { 
    phase = (2*AG)/LC; 
  }
  if ((AG > LC/2) && (AG <= LC))            //FROM Full Moon 100% TO New Moon 0%
  { 
    phase = 2*(LC-AG)/LC; 
  }
  //Determine the Lunar Phase
  if ((AG >= 0) && (AG <= 5.54))         // 0 a 35%        
  { 
#ifdef USE_TFT
    LP = tabela_textos_fase[1];  // "LUA NOVA"
#endif    
    fase = 1;
  }
  if ((AG > 5.17) && (AG <= 14.32))       //35 a 97%  
  { 
#ifdef USE_TFT    
    LP = tabela_textos_fase[2];  // "LUA CRESCENTE"
#endif    
    fase = 2;
  }
  if ((AG > 14.32) && (AG <= 15.21))      // 97 a 100 e de 100 a 97%     
  { 
#ifdef USE_TFT    
    LP = tabela_textos_fase[3]; // "LUA CHEIA"
#endif    
    fase = 3;
  }    
  if ((AG > 15.21) && (AG <= 24.36))     //97 a 35%    
  { 
#ifdef USE_TFT    
    LP = tabela_textos_fase[4]; // "LUA MINGUANTE"
#endif    
    fase = 4;
  }
  if ((AG >= 24.36) && (AG <= LC))       //35 a 0%
  { 
#ifdef USE_TFT    
    LP = tabela_textos_fase[1];  // "LUA NOVA"
#endif    
    fase = 1;
  }

  return phase; 
}

/******* Normalization Function *******/
double MyNormalize(double v) 
{ 
  v = v - floor(v);
  if (v < 0)
    v = v + 1;
  return v;
}
