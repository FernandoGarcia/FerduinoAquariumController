#pragma once // Do not change this line!
#ifdef STAMPS_EZO
// ------------------------------------- Leitura dos stamps
  void check_parametro_ph_aquario()
  {
    bool done = false;
    byte holding;
    char sensorstring[15];

    do
    {
      Open_channel(ph1);
      delay(50);

      while (Serial1.available())
      {
        char c = Serial1.read();
      }

      Serial1.print("T,");
      #ifdef USE_FAHRENHEIT
        Serial1.print((tempC - 32) / 1.8);
      #else
        Serial1.print(tempC);
      #endif
      Serial1.print('\r');
      delay(1000);

      Serial1.print("R"); // Envia um comando.
      Serial1.print('\r');
      delay(1000);

      if (Serial1.available() > 3)
      {
        holding = Serial1.available();
        for (byte i = 1; i <= holding; i++)
        {
          sensorstring[i] = Serial1.read();
        }

        if (holding == 6)
        {
          PHA = ((sensorstring[1] - 48) * 100 + (sensorstring[3] - 48) * 10 + (sensorstring[4] - 48));
          PHA /= 100;
        }
        else
        {
          PHA = ((sensorstring[1] - 48) * 1000 + (sensorstring[2] - 48) * 100 + (sensorstring[4] - 48) * 10 + (sensorstring[5] - 48));
          PHA /= 100;
        }
        Serial1.flush();
        break;
      }
    }
    while (done == true);
  }

  void check_parametro_ph_reator()
  {
    bool done = false;
    byte holding;
    char sensorstring[15];

    do
    {
      Open_channel(ph2);
      delay(50);

      while (Serial1.available())
      {
        char c = Serial1.read();
      }

      Serial1.print("T,");
      #ifdef USE_FAHRENHEIT
        Serial1.print((tempC - 32) / 1.8);
      #else
        Serial1.print(tempC);
      #endif
      Serial1.print('\r');
      delay(1000);

      Serial1.print("R"); // Envia um comando.
      Serial1.print('\r');
      delay(1000);

      if (Serial1.available() > 3)
      {
        holding = Serial1.available();
        for (byte i = 1; i <= holding; i++)
        {
          sensorstring[i] = Serial1.read();
        }

        if (holding == 6)
        {
          PHR = ((sensorstring[1] - 48) * 100 + (sensorstring[3] - 48) * 10 + (sensorstring[4] - 48));
          PHR /= 100;
        }
        else
        {
          PHR = ((sensorstring[1] - 48) * 1000 + (sensorstring[2] - 48) * 100 + (sensorstring[4] - 48) * 10 + (sensorstring[5] - 48));
          PHR /= 100;
        }
        Serial1.flush();
        break;
      }
    }
    while (done == true);
  }

  void check_parametro_orp()
  {
    bool done = false;
    byte holding;
    char sensorstring[15];

    do
    {
      Open_channel(orp);
      delay(50);

      while (Serial1.available())
      {
        char c = Serial1.read();
      }

      Serial1.print("R"),
      Serial1.print('\r');
      delay(1000);

      if (Serial1.available() > 3)
      {
        holding = Serial1.available();
        for (byte i = 1; i <= holding; i++)
        {
          sensorstring[i] = Serial1.read();
        }
        if (holding == 5)
        {
          ORP = ((sensorstring[1] - 48) * 10 + (sensorstring[2] - 48));
        }
        else
        {
          ORP = ((sensorstring[1] - 48) * 100 + (sensorstring[2] - 48) * 10 + (sensorstring[3] - 48));
        }
        Serial1.flush();
        break;
      }
    }
    while (done == true);
  }

  void check_parametro_densidade()
  {
    bool done = false;
    byte holding;
    char sensorstring[15];

    do
    {
      Open_channel(ec);
      delay(50);

      while (Serial1.available())
      {
        char c = Serial1.read();
      }

      Serial1.print("T,");
      #ifdef USE_FAHRENHEIT
        Serial1.print((tempC - 32) / 1.8);
      #else
        Serial1.print(tempC);
      #endif
      Serial1.print('\r');
      delay(1000);

      Serial1.print("R"); // Envia um comando.
      Serial1.print('\r');
      delay(1000);

      if (Serial1.available() > 3)
      {
        holding = Serial1.available();
        for (byte i = 1; i <= holding; i++)
        {
          sensorstring[i] = Serial1.read();
        }

        if (holding == 6)
        {
          DEN = ((sensorstring[1] - 48) * 1000 + (sensorstring[3] - 48) * 100 + ((sensorstring[4] - 48) * 10) + (sensorstring[5] - 48));
        }

        Serial1.flush();
        break;
      }
    }
    while (done == true);
  }

  void iniciar_stamp_ph_aquario()
  {
    Open_channel(ph1);  // Open channel for tank pH
    delay(50);
    Serial1.print("R"); // To get a value
    Serial1.print('\r');
    delay(1000);

    Serial1.print("C,0"); // To stop continuous reading
    Serial1.print('\r');
    delay(1000);

    Serial1.print("L,0"); // To turn off the LEDs of debug
    Serial1.print('\r');
    delay(1000);

    Serial1.print("*OK,0"); // To disable response code
    Serial1.print('\r');
    delay(1000);
    check_parametro_ph_aquario();
  }

  void iniciar_stamp_ph_reator()
  {
    Open_channel(ph2);
    delay(50);
    Serial1.print("R"); // To get a value
    Serial1.print('\r');
    delay(1000);

    Serial1.print("C,0"); // To stop continuous reading
    Serial1.print('\r');
    delay(1000);

    Serial1.print("L,0"); // To turn off the LEDs of debug
    Serial1.print('\r');
    delay(1000);

    Serial1.print("*OK,0"); // To disable response code
    Serial1.print('\r');
    delay(1000);
    check_parametro_ph_reator();
  }

  void iniciar_stamp_orp()
  {
    Open_channel(orp);
    Serial1.print("R"); // To get a value
    Serial1.print('\r');
    delay(1000);

    Serial1.print("C,0"); // To stop continuous reading
    Serial1.print('\r');
    delay(1000);

    Serial1.print("L,0"); // To turn off the LEDs of debug
    Serial1.print('\r');
    delay(1000);

    Serial1.print("*OK,0"); // To disable response code
    Serial1.print('\r');
    delay(1000);
    check_parametro_orp();
  }

  void iniciar_stamp_densidade()
  {
    Open_channel(ec);   // To open channel for salinity
    delay(50);
    Serial1.print("R"); // To get a value
    Serial1.print('\r');
    delay(1000);

    Serial1.print("C,0"); // To stop continuous reading
    Serial1.print('\r');
    delay(1000);

    Serial1.print("L,0"); // To turn OFF the  LEDs of debug
    Serial1.print('\r');
    delay(1000);

    Serial1.print("*OK,0"); // To disable response code
    Serial1.print('\r');
    delay(1000);


    Serial1.print("O,EC"); // Disable EC reading.
    Serial1.print('\r');
    delay(1000);

    Serial1.print("O,TDS"); // Disable TDS reading.
    Serial1.print('\r');
    delay(1000);

    Serial1.print("O,S"); // Disable salinity reading
    Serial1.print('\r');
    delay(1000);

    Serial1.print("O,SG,1"); // Enable specific gravity reading
    Serial1.print('\r');
    delay(1000);

    check_parametro_densidade();
  }

  void Open_channel(short channel)
  {
    switch (channel)
    {
      case 0:
        // open channel Y0
        // S0=0
        // S1=0
        digitalWrite(multiplexadorS0Pin, LOW);
        digitalWrite(multiplexadorS1Pin, LOW);
        break;

      case 1:
        // open channel Y1
        // S0=1
        // S1=0
        digitalWrite(multiplexadorS0Pin, HIGH);
        digitalWrite(multiplexadorS1Pin, LOW);
        break;

      case 2:
        // open channel Y2
        // S0=0
        // S1=1
        digitalWrite(multiplexadorS0Pin, LOW);
        digitalWrite(multiplexadorS1Pin, HIGH);
        break;

      case 3:
        // open channel Y3
        // S0=1
        // S1=1
        digitalWrite(multiplexadorS0Pin, HIGH);
        digitalWrite(multiplexadorS1Pin, HIGH);
        break;
    }
    Serial1.print('\r');
    return;
  }
#endif
