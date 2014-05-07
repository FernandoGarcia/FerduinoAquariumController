//------------------------------------- Leitura dos stamps
void parametros()
{
  int i;
  do{
    Open_channel(ph1);
    Serial3.print(tempC); //Para se obter um valor compensado pode-se enviar um valor de temperatura da água.
    Serial3.print('\r');
    delay(500);

    if(Serial3.available() > 3) 
    {
      holding = Serial3.available();
      for(i=1; i <= holding; i++)
      {
        sensorstring[i]= Serial3.read();
      }

      if(holding ==5)
      {
        PHT = ((sensorstring[1]-48)*100 + (sensorstring[3]-48)*10 + (sensorstring[4]-48));
        PHA = PHT/100;
      }
      else
      {
        PHT = ((sensorstring[1]-48)*1000 + (sensorstring[2]-48)*100 + (sensorstring[4]-48)*10 + (sensorstring[5]-48));
        PHA = PHT/100;
      }  
      PHT=0;
      Serial3.flush();
      break;
    }
  } 
  while (done==1);
  done=0;

  do{
    Open_channel(ph2);
    Serial3.print(tempC); //Para se obter um valor compensado pode-se enviar um valor de temperatura da água.
    Serial3.print('\r');
    delay(500);

    if(Serial3.available() > 3) 
    {
      holding = Serial3.available();
      for(i=1; i <= holding; i++)
      {
        sensorstring[i]= Serial3.read();
      }
      if(holding ==5)
      {
        PHT = ((sensorstring[1]-48)*100 + (sensorstring[3]-48)*10 + (sensorstring[4]-48));
        PHR = PHT/100;
      }
      else
      {
        PHT = ((sensorstring[1]-48)*1000 + (sensorstring[2]-48)*100 + (sensorstring[4]-48)*10 + (sensorstring[5]-48));
        PHR = PHT/100;
      }  
      PHT=0;
      Serial3.flush();
      break;
    }

  } 
  while (done==1);
  done=0;

  do{
    Open_channel(orp);
    Serial3.print("r"),
    Serial3.print('\r');
    delay(500);

    if(Serial3.available() > 3) 
    {
      holding = Serial3.available();
      for(i=1; i <= holding; i++)
      {
        sensorstring[i]= Serial3.read();
      }

      ORPT = ((sensorstring[1]-48)*100 + (sensorstring[2]-48)*10 + (sensorstring[3]-48));
      ORP = ORPT; 
      ORPT=0;
      Serial3.flush();      
      break;
    }
  } 
  while (done==1);
  done=0;
/*
  do{
    Open_channel(ec);
    Serial3.print(tempC); //Para se obter um valor compensado pode-se enviar um valor de temperatura da água.
    Serial3.print('\r');
    delay(500);
    if(Serial3.available() > 3) 
    {
      Serial.print("Densidade:");
      holding = Serial3.available();
      for(i=1; i <= 15; i++)
      {
        sensorstring[i]= Serial3.read();
        Serial.print(sensorstring[i]);
      }
      Serial.println();
      Serial3.flush();
      break;
    }  
  } 
  while (done==1);
  done=0;
*/
}

void iniciar_stamps()
{
    Open_channel(ph1); 
  delay(50);
  Serial3.print("e"); // Envia um comando para que o "stamp" pare de enviar as leituras.
  Serial3.print('\r');
  delay(1000);
  Serial3.flush();
  Serial3.print("L0"); // Envia um comando para que o "stamp" apague o led de depuração.
  Serial3.print('\r');
  delay(1000);
  Open_channel(ph2);
  delay(50);
  Serial3.print("e"); // Envia um comando para que o "stamp" pare de enviar as leituras.
  Serial3.print('\r');
  delay(1000);
  Serial3.flush();
  Serial3.print("L0"); // Envia um comando para que o "stamp" apague o led de depuração.
  Serial3.print('\r');
  delay(1000);
  Open_channel(orp);
  delay(50);
  Serial3.print("e"); // Envia um comando para que o "stamp" pare de enviar as leituras.
  Serial3.print('\r');
  delay(1000);
  Serial3.flush();
  Serial3.print("L0"); // Envia um comando para que o "stamp" apague o led de depuração.
  Serial3.print('\r');
  delay(1000);    
  Open_channel(ec);
  delay(50);
  Serial3.print("e"); // Envia um comando para que o "stamp" pare de enviar as leituras.
  Serial3.print('\r');
  delay(1000);
  Serial3.flush();
  Serial3.print("L0"); // Envia um comando para que o "stamp" apague o led de depuração.
  Serial3.print('\r');
  delay(1000);
  parametros(); // Verifica os "stamps".
}

void Open_channel(short channel)
{
  switch (channel) 
  {
  case 0:
    //open channel Y0
    //S0=0
    //S1=0
    digitalWrite(multiplexadorS0Pin, LOW);
    digitalWrite(multiplexadorS1Pin, LOW);
    break;

  case 1:
    //open channel Y1
    //S0=1
    //S1=0
    digitalWrite(multiplexadorS0Pin, HIGH);
    digitalWrite(multiplexadorS1Pin, LOW);
    break;

  case 2:
    //open channel Y2
    //S0=0
    //S1=1
    digitalWrite(multiplexadorS0Pin, LOW);
    digitalWrite(multiplexadorS1Pin, HIGH);
    break;

  case 3:
    //open channel Y3
    //S0=1
    //S1=1
    digitalWrite(multiplexadorS0Pin, HIGH);
    digitalWrite(multiplexadorS1Pin, HIGH);
    break;
  }
  Serial3.print('\r');
  return;
}
