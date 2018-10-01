void checktpa()
{
  if (outlets_changed[5] == true)
  {
    outlets_changed[5] = false;
#ifdef USE_PCF8575
    PCF8575.digitalWrite(bomba1Pin, LOW);
#else
    myDigitalWrite(bomba1Pin, LOW);
#endif
  }

  if (outlets_changed[6] == true)
  {
    outlets_changed[6] = false;
#ifdef USE_PCF8575
    PCF8575.digitalWrite(bomba2Pin, LOW);
#else
    myDigitalWrite(bomba2Pin, LOW);
#endif
  }

  if (outlets_changed[7] == true)
  {
    outlets_changed[7] = false;
#ifdef USE_PCF8575
    PCF8575.digitalWrite(bomba3Pin, LOW);
#else
    myDigitalWrite(bomba3Pin, LOW);
#endif
  }

  if ((outlets[5] == 0) && (outlets[6] == 0) && (outlets[7] == 0))
  {
    tempo = (duracaomaximatpa * 60000ul);

    if ((semana[0] == t.dow) || (semana[1] == t.dow) || (semana[2] == t.dow) || (semana[3] == t.dow) || (semana[4] == t.dow) || (semana[5] == t.dow) || (semana[6] == t.dow))
    {
      if ((hora == t.hour) && (minuto == t.min) && (tpa == 0))
      {
        tpa = 1;
        if ((4294967295ul - tempo) < millis())
        {
          marcadoriniciotpa = millis() - (tempo * 2);
        }
        else
        {
          marcadoriniciotpa = millis();
        }
      }
    }

    if ((4294967295ul - tempo) < millis())
    {
      shiftedmillis = millis() - (tempo * 2);
    }
    else
    {
      shiftedmillis = millis();
    }

    if ((myAnalogRead(sensor1) < 400) && (myAnalogRead(sensor2) > 400) && (myAnalogRead(sensor3) < 400) && (tpa == 1)
        && (bitRead(tpa_status, 2) == false) && (myAnalogRead(sensor4) > 400) && ((shiftedmillis - marcadoriniciotpa) < tempo))
    {
#ifdef USE_PCF8575
      PCF8575.digitalWrite(bomba1Pin, HIGH); //estagio 1
      PCF8575.digitalWrite(bomba2Pin, LOW);
      PCF8575.digitalWrite(bomba3Pin, LOW);
#else
      myDigitalWrite(bomba1Pin, HIGH); //estagio 1
      myDigitalWrite(bomba2Pin, LOW);
      myDigitalWrite(bomba3Pin, LOW);
#endif

      tpa = 2;
      bitWrite(tpa_status, 1, 1);
      if ((4294967295ul - tempo) < millis()) //zera o cronometro para o proximo estagio
      {
        marcadoriniciotpa = millis() - (tempo * 2);
      }
      else
      {
        marcadoriniciotpa = millis();
      }
    }
    else if ((myAnalogRead(sensor1) > 400) && (myAnalogRead(sensor2) > 400) && (tpa == 2) && ((shiftedmillis - marcadoriniciotpa) < tempo))
    {
#ifdef USE_PCF8575
      PCF8575.digitalWrite(bomba1Pin, LOW); //estagio 2
      PCF8575.digitalWrite(bomba2Pin, HIGH);
      PCF8575.digitalWrite(bomba3Pin, LOW);
#else
      myDigitalWrite(bomba1Pin, LOW); //estagio 2
      myDigitalWrite(bomba2Pin, HIGH);
      myDigitalWrite(bomba3Pin, LOW);
#endif

      tpa = 3;
      bitWrite(tpa_status, 1, 1);
      if ((4294967295ul - tempo) < millis()) //zera o cronometro para o proximo estagio
      {
        marcadoriniciotpa = millis() - (tempo * 2);
      }
      else
      {
        marcadoriniciotpa = millis();
      }
    }
    else if ((myAnalogRead(sensor2) < 400) && (myAnalogRead(sensor1) == 0) && (myAnalogRead(sensor3) > 400) && (tpa == 3) && ((shiftedmillis - marcadoriniciotpa) < tempo))
    {
#ifdef USE_PCF8575
      PCF8575.digitalWrite(bomba1Pin, LOW); // estagio 3
      PCF8575.digitalWrite(bomba2Pin, LOW);
      PCF8575.digitalWrite(bomba3Pin, HIGH);
#else
      myDigitalWrite(bomba1Pin, LOW); // estagio 3
      myDigitalWrite(bomba2Pin, LOW);
      myDigitalWrite(bomba3Pin, HIGH);
#endif

      tpa = 4;
      bitWrite(tpa_status, 1, 1);
      if ((4294967295ul - tempo) < millis()) //zera o cronometro para o proximo estagio
      {
        marcadoriniciotpa = millis() - (tempo * 2);
      }
      else
      {
        marcadoriniciotpa = millis();
      }
    }
    else if ((myAnalogRead(sensor3) < 400) && (myAnalogRead(sensor2) > 400) && (myAnalogRead(sensor1) < 400) && (tpa == 4) && ((shiftedmillis - marcadoriniciotpa) < tempo))
    {
#ifdef USE_PCF8575
      PCF8575.digitalWrite(bomba1Pin, LOW); // estagio 0
      PCF8575.digitalWrite(bomba2Pin, LOW);
      PCF8575.digitalWrite(bomba3Pin, LOW);
#else
      myDigitalWrite(bomba1Pin, LOW); // estagio 0
      myDigitalWrite(bomba2Pin, LOW);
      myDigitalWrite(bomba3Pin, LOW);
#endif
      bitWrite(tpa_status, 1, 0);
    }
    else if (((shiftedmillis - marcadoriniciotpa) >= tempo) && (bitRead(tpa_status, 1) == true))
    {
#ifdef USE_PCF8575
      PCF8575.digitalWrite(bomba1Pin, LOW); //desliga as bombas todas e mete tpa=0 para não entrar no ciclo outra vez
      PCF8575.digitalWrite(bomba2Pin, LOW);
      PCF8575.digitalWrite(bomba3Pin, LOW);
#else
      myDigitalWrite(bomba1Pin, LOW); //desliga as bombas todas e mete tpa=0 para não entrar no ciclo outra vez
      myDigitalWrite(bomba2Pin, LOW);
      myDigitalWrite(bomba3Pin, LOW);
#endif
      tpa = 0;
      bitWrite(tpa_status, 1, 0);
      bitWrite(tpa_status, 2, 1);
      Salvar_erro_tpa_EEPROM();
    }
  }


  if (outlets[5] == 1)
  {
#ifdef USE_PCF8575
    PCF8575.digitalWrite(bomba1Pin, HIGH);
#else
    myDigitalWrite(bomba1Pin, HIGH);
#endif
  }

  if (outlets[6] == 1)
  {
#ifdef USE_PCF8575
    PCF8575.digitalWrite(bomba2Pin, HIGH);
#else
    myDigitalWrite(bomba2Pin, HIGH);
#endif
  }

  if (outlets[7] == 1)
  {
#ifdef USE_PCF8575
    PCF8575.digitalWrite(bomba3Pin, HIGH);
#else
    myDigitalWrite(bomba3Pin, HIGH);
#endif
  }

  if (outlets[5] == 2)
  {
#ifdef USE_PCF8575
    PCF8575.digitalWrite(bomba1Pin, LOW);
#else
    myDigitalWrite(bomba1Pin, LOW);
#endif
  }

  if (outlets[6] == 2)
  {
#ifdef USE_PCF8575
    PCF8575.digitalWrite(bomba2Pin, LOW);
#else
    myDigitalWrite(bomba2Pin, LOW);
#endif
  }

  if (outlets[7] == 2)
  {
#ifdef USE_PCF8575
    PCF8575.digitalWrite(bomba3Pin, LOW);
#else
    myDigitalWrite(bomba3Pin, LOW);
#endif
  }
}

