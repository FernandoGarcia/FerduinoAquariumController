#pragma once // Do not change this line!
void checktpa()
{
  if (outlets_changed[5] == true)
  {
    outlets_changed[5] = false;
    bitWrite(Status, 3, 0);
    PCF8575.digitalWrite(bomba1Pin, LOW);
  }

  if (outlets_changed[6] == true)
  {
    outlets_changed[6] = false;
    bitWrite(Status, 4, 0);
    PCF8575.digitalWrite(bomba2Pin, LOW);
  }

  if (outlets_changed[7] == true)
  {
    outlets_changed[7] = false;
    bitWrite(Status, 5, 0);
    PCF8575.digitalWrite(bomba3Pin, LOW);
  }

  if ((outlets[5] == 0) && (outlets[6] == 0) && (outlets[7] == 0))
  {
    tempo = (duracaomaximatpa * 60000UL);

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

    if ((analogRead(sensor1) < 400) && (analogRead(sensor2) > 400) && (analogRead(sensor3) < 400) && (tpa == 1)
        && (bitRead(tpa_status, 2) == false) && (analogRead(sensor4) > 400) && ((shiftedmillis - marcadoriniciotpa) < tempo))
    {
      bitWrite(Status, 3, 1);
      bitWrite(Status, 4, 0);
      bitWrite(Status, 5, 0);
      PCF8575.digitalWrite(bomba1Pin, HIGH);   // estagio 1
      PCF8575.digitalWrite(bomba2Pin, LOW);
      PCF8575.digitalWrite(bomba3Pin, LOW);

      tpa = 2;
      bitWrite(tpa_status, 1, 1);
      if ((4294967295ul - tempo) < millis()) // zera o cronometro para o proximo estagio
      {
        marcadoriniciotpa = millis() - (tempo * 2);
      }
      else
      {
        marcadoriniciotpa = millis();
      }
    }
    else if ((analogRead(sensor1) > 400) && (analogRead(sensor2) > 400) && (tpa == 2) && ((shiftedmillis - marcadoriniciotpa) < tempo))
    {
      bitWrite(Status, 3, 0);
      bitWrite(Status, 4, 1);
      bitWrite(Status, 5, 0);
      PCF8575.digitalWrite(bomba1Pin, LOW);   // estagio 2
      PCF8575.digitalWrite(bomba2Pin, HIGH);
      PCF8575.digitalWrite(bomba3Pin, LOW);

      tpa = 3;
      bitWrite(tpa_status, 1, 1);
      if ((4294967295ul - tempo) < millis()) // zera o cronometro para o proximo estagio
      {
        marcadoriniciotpa = millis() - (tempo * 2);
      }
      else
      {
        marcadoriniciotpa = millis();
      }
    }
    else if ((analogRead(sensor2) < 400) && (analogRead(sensor1) == 0) && (analogRead(sensor3) > 400) && (tpa == 3) && ((shiftedmillis - marcadoriniciotpa) < tempo))
    {
      bitWrite(Status, 3, 0);
      bitWrite(Status, 4, 0);
      bitWrite(Status, 5, 1);
      PCF8575.digitalWrite(bomba1Pin, LOW);   // estagio 3
      PCF8575.digitalWrite(bomba2Pin, LOW);
      PCF8575.digitalWrite(bomba3Pin, HIGH);

      tpa = 4;
      bitWrite(tpa_status, 1, 1);
      if ((4294967295ul - tempo) < millis()) // zera o cronometro para o proximo estagio
      {
        marcadoriniciotpa = millis() - (tempo * 2);
      }
      else
      {
        marcadoriniciotpa = millis();
      }
    }
    else if ((analogRead(sensor3) < 400) && (analogRead(sensor2) > 400) && (analogRead(sensor1) < 400) && (tpa == 4) && ((shiftedmillis - marcadoriniciotpa) < tempo))
    {
      bitWrite(Status, 3, 0);
      bitWrite(Status, 4, 0);
      bitWrite(Status, 5, 0);
      PCF8575.digitalWrite(bomba1Pin, LOW);   // estagio 0
      PCF8575.digitalWrite(bomba2Pin, LOW);
      PCF8575.digitalWrite(bomba3Pin, LOW);
      bitWrite(tpa_status, 1, 0);
    }
    else if (((shiftedmillis - marcadoriniciotpa) >= tempo) && (bitRead(tpa_status, 1) == true))
    {
      bitWrite(Status, 3, 0);
      bitWrite(Status, 4, 0);
      bitWrite(Status, 5, 0);
      PCF8575.digitalWrite(bomba1Pin, LOW);   // desliga as bombas todas e mete tpa=0 para não entrar no ciclo outra vez
      PCF8575.digitalWrite(bomba2Pin, LOW);
      PCF8575.digitalWrite(bomba3Pin, LOW);
      tpa = 0;
      bitWrite(tpa_status, 1, 0);
      bitWrite(tpa_status, 2, 1);
      Salvar_erro_tpa_EEPROM();
    }
  }


  if (outlets[5] == 1)
  {
    bitWrite(Status, 3, 1);
    PCF8575.digitalWrite(bomba1Pin, HIGH);
  }

  if (outlets[6] == 1)
  {
    bitWrite(Status, 4, 1);
    PCF8575.digitalWrite(bomba2Pin, HIGH);
  }

  if (outlets[7] == 1)
  {
    bitWrite(Status, 5, 1);
    PCF8575.digitalWrite(bomba3Pin, HIGH);
  }

  if (outlets[5] == 2)
  {
    bitWrite(Status, 3, 0);
    PCF8575.digitalWrite(bomba1Pin, LOW);
  }

  if (outlets[6] == 2)
  {
    bitWrite(Status, 4, 0);
    PCF8575.digitalWrite(bomba2Pin, LOW);
  }

  if (outlets[7] == 2)
  {
    bitWrite(Status, 5, 0);
    PCF8575.digitalWrite(bomba3Pin, LOW);
  }
}
