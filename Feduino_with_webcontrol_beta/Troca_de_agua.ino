void checktpa()
{
  tempo = (duracaomaximatpa * 60000ul);

  if ((segunda==t.dow) || (terca==t.dow) || (quarta==t.dow) || (quinta==t.dow) || (sexta==t.dow) || (sabado==t.dow) || (domingo==t.dow))
  {
    if((hora==t.hour) && (minuto==t.min) && (tpa == 0))
    {
      tpa = 1;
      if ((4294967295ul - tempo) < millis())
      {
        marcadoriniciotpa= millis() - (tempo*2);
      }
      else
      {
        marcadoriniciotpa= millis();
      }
    }
  }

  if ((4294967295ul - tempo) < millis())
  {
    shiftedmillis= millis() - (tempo*2);
  }
  else
  {
    shiftedmillis= millis();
  }

  if ((analogRead(sensor1)<400) && (analogRead(sensor2)>400) && (analogRead(sensor3)<400) && tpa==1 && (analogRead(sensor4)>400) && ((shiftedmillis - marcadoriniciotpa) < tempo))
  {
    digitalWrite(bomba1Pin,HIGH); //estagio 1
    digitalWrite(bomba2Pin,LOW);
    digitalWrite(bomba3Pin,LOW);
    tpa=2;
    bitWrite(tpa_status,1,1);
    if ((4294967295ul - tempo) < millis()) //zera o cronometro para o proximo estagio
    {
      marcadoriniciotpa= millis() - (tempo*2);
    }
    else
    {
      marcadoriniciotpa= millis();
    }
  }
  else if ((analogRead(sensor1)>400) && (analogRead(sensor2)>400) && tpa==2 && ((shiftedmillis - marcadoriniciotpa) < tempo))
  {
    digitalWrite(bomba1Pin,LOW); //estagio 2
    digitalWrite(bomba2Pin,HIGH);
    digitalWrite(bomba3Pin,LOW);
    tpa=3;
    bitWrite(tpa_status,1,1);
    if ((4294967295ul - tempo) < millis()) //zera o cronometro para o proximo estagio
    {
      marcadoriniciotpa= millis() - (tempo*2);
    }
    else
    {
      marcadoriniciotpa= millis();
    }
  }
  else if ((analogRead(sensor2)<400) && (analogRead(sensor1)==0) && (analogRead(sensor3)>400) && tpa==3 && ((shiftedmillis - marcadoriniciotpa) < tempo))
  {
    digitalWrite(bomba1Pin,LOW); // estagio 3
    digitalWrite(bomba2Pin,LOW);
    digitalWrite(bomba3Pin,HIGH);
    tpa=4;
    bitWrite(tpa_status,1,1);
    if ((4294967295ul - tempo) < millis()) //zera o cronometro para o proximo estagio
    {
      marcadoriniciotpa= millis() - (tempo*2);
    }
    else
    {
      marcadoriniciotpa= millis();
    }
  }
  else if ((analogRead(sensor3)<400) && (analogRead(sensor2)>400) && (analogRead(sensor1)<400) && tpa==4 && ((shiftedmillis - marcadoriniciotpa) < tempo))
  {
    digitalWrite(bomba1Pin,LOW); // estagio 0
    digitalWrite(bomba2Pin,LOW);
    digitalWrite(bomba3Pin,LOW);
    bitWrite(tpa_status,1,0);
  }
  else if (((shiftedmillis - marcadoriniciotpa) >= tempo) && (bitRead(tpa_status,1)== true))
  {
    digitalWrite(bomba1Pin,LOW); //desliga as bombas todas e mete tpa=0 para não entrar no ciclo outra vez
    digitalWrite(bomba2Pin,LOW);
    digitalWrite(bomba3Pin,LOW);
    tpa=0;
    bitWrite(tpa_status,1,0);
    bitWrite(tpa_status,2,1);
  }
}

