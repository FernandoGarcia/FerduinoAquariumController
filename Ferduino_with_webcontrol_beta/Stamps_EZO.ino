#ifdef STAMPS_EZO
//------------------------------------- Leitura dos stamps
void check_parametro_ph_aquario()
{
  boolean done = false;
  byte holding;
  char sensorstring[15];

  do{
    Open_channel(ph1);
    delay(50);

    while(Serial3.available())
    {
      char c = Serial3.read();
    }

    Serial3.print("T,");
    Serial3.print(tempC);
    Serial3.print('\r');
    delay(1000);

    Serial3.print("R"); // Envia um comando.
    Serial3.print('\r');
    delay(1000);

    if(Serial3.available() > 3)
    {
      holding = Serial3.available();
      for(byte i=1; i <= holding; i++)
      {
        sensorstring[i]= Serial3.read();
      }

      if(holding == 6)
      {
        PHA = ((sensorstring[1]-48)*100 + (sensorstring[3]-48)*10 + (sensorstring[4]-48));
        PHA /= 100;
      }
      else
      {
        PHA = ((sensorstring[1]-48)*1000 + (sensorstring[2]-48)*100 + (sensorstring[4]-48)*10 + (sensorstring[5]-48));
        PHA /= 100;
      }
      Serial3.flush();
      break;
    }
  }
  while (done == true);
}

void check_parametro_ph_reator()
{
  boolean done = false;
  byte holding;
  char sensorstring[15];

  do{
    Open_channel(ph2);
    delay(50);

    while(Serial3.available())
    {
      char c = Serial3.read();
    }

    Serial3.print("T,");
    Serial3.print(tempC);
    Serial3.print('\r');
    delay(1000);

    Serial3.print("R"); // Envia um comando.
    Serial3.print('\r');
    delay(1000);

    if(Serial3.available() > 3)
    {
      holding = Serial3.available();
      for(byte i=1; i <= holding; i++)
      {
        sensorstring[i]= Serial3.read();
      }

      if(holding == 6)
      {
        PHR = ((sensorstring[1]-48)*100 + (sensorstring[3]-48)*10 + (sensorstring[4]-48));
        PHR /= 100;
      }
      else
      {
        PHR = ((sensorstring[1]-48)*1000 + (sensorstring[2]-48)*100 + (sensorstring[4]-48)*10 + (sensorstring[5]-48));
        PHR /= 100;
      }
      Serial3.flush();
      break;
    }
  }
  while (done == true);
}

void check_parametro_orp()
{
  boolean done = false;
  byte holding;
  char sensorstring[15];

  do{
    Open_channel(orp);
    delay(50);
   
    while(Serial3.available())
    {
      char c = Serial3.read();
    }
   
    Serial3.print("R"),
    Serial3.print('\r');
    delay(1000);

    if(Serial3.available() > 3)
    {
      holding = Serial3.available();
      for(byte i = 1; i <= holding; i++)
      {
        sensorstring[i]= Serial3.read();
      }
      if(holding == 5)
      {
        ORP = ((sensorstring[1]-48)*10 + (sensorstring[2]-48));
      }
      else
      {
        ORP = ((sensorstring[1]-48)*100 + (sensorstring[2]-48)*10 + (sensorstring[3]-48));
      }
      Serial3.flush();     
      break;
    }
  }
  while (done == true);
}

void check_parametro_densidade()
{
  boolean done = false;
  byte holding;
  char sensorstring[15];

  do{
    Open_channel(ec);
    delay(50);

    while(Serial3.available())
    {
      char c = Serial3.read();
    }

    Serial3.print("T,");
    Serial3.print(tempC);
    Serial3.print('\r');
    delay(1000);

    Serial3.print("R"); // Envia um comando.
    Serial3.print('\r');
    delay(1000);

    if(Serial3.available() > 3)
    {
      holding = Serial3.available();
      for(byte i=1; i <= holding; i++)
      {
        sensorstring[i]= Serial3.read();
      }

      if(holding == 6)
      {
        DEN = ((sensorstring[1]-48)*1000 + (sensorstring[3]-48)*100 + ((sensorstring[4]-48)*10) + (sensorstring[5]-48));
      }

      Serial3.flush();
      break;
    }
  }
  while (done == true);
}

void iniciar_stamp_ph_aquario()
{
  Open_channel(ph1); // Open channel for tank pH
  delay(50);
  Serial3.print("R"); // To get a value
  Serial3.print('\r');
  delay(1000);

  Serial3.print("C,0"); // To stop continuous reading
  Serial3.print('\r');
  delay(1000);

  Serial3.print("L,0"); // To turn off the LEDs of debug
  Serial3.print('\r');
  delay(1000);

  Serial3.print("RESPONSE,0"); // To disable response code
  Serial3.print('\r');
  delay(1000);
  check_parametro_ph_aquario();
}

void iniciar_stamp_ph_reator()
{
  Open_channel(ph2);
  delay(50);
  Serial3.print("R"); // To get a value
  Serial3.print('\r');
  delay(1000);

  Serial3.print("C,0"); // To stop continuous reading
  Serial3.print('\r');
  delay(1000);

  Serial3.print("L,0"); // To turn off the LEDs of debug
  Serial3.print('\r');
  delay(1000);

  Serial3.print("RESPONSE,0"); // To disable response code
  Serial3.print('\r');
  delay(1000);
  check_parametro_ph_reator();
}

void iniciar_stamp_orp()
{
  Open_channel(orp);
  Serial3.print("R"); // To get a value
  Serial3.print('\r');
  delay(1000);

  Serial3.print("C,0"); // To stop continuous reading
  Serial3.print('\r');
  delay(1000);

  Serial3.print("L,0"); // To turn off the LEDs of debug
  Serial3.print('\r');
  delay(1000);

  Serial3.print("RESPONSE,0"); // To disable response code
  Serial3.print('\r');
  delay(1000);
  check_parametro_orp();
}

void iniciar_stamp_densidade()
{
  Open_channel(ec); // To open channel for salinity
  delay(50);
  Serial3.print("R"); // To get a value
  Serial3.print('\r');
  delay(1000);

  Serial3.print("C,0"); // To stop continuous reading
  Serial3.print('\r');
  delay(1000);

  Serial3.print("L,0"); // To turn OFF the  LEDs of debug
  Serial3.print('\r');
  delay(1000);

  Serial3.print("RESPONSE,0"); // To disable response code
  Serial3.print('\r');
  delay(1000);


  Serial3.print("O,EC"); // Disable EC reading.
  Serial3.print('\r');
  delay(1000);

  Serial3.print("O,TDS"); // Disable TDS reading.
  Serial3.print('\r');
  delay(1000);

  Serial3.print("O,S"); // Disable salinity reading
  Serial3.print('\r');
  delay(1000);
  check_parametro_densidade();
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
#endif
