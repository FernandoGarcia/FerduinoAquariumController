#pragma once // Do not change this line!
void checkNuvemRelampago()
{
  if ((millis() - millis_nuvem) > (duracaoNuvem + duracaoRelampago) * 60000UL) // Finaliza nuvem e relâmpago
  {
    executandoNuvem = false;
    inicioNuvem = false;
    LOGLN(F("Lighting and cloud finished."));
  }

  if ((millis() - millis_nuvem) < (duracaoNuvem * 60000UL)) // Apenas nuvem
  {
    if (aguarde == false)
    {
      checkTempoRampa(); // Verifica se é tempo de aumentar ou diminuir o PWM
      checkNuvens();     // Executa o analogWrite para nuvens
    }
    else
    {
      aguardeIntervalo(); // Verifica se é o momento de esperar até a próxima nuvem
    }
  }
  else // Relâmpago e nuvem
  {
    if (aguarde == false)
    {
      checkTempoRampa(); // Verifica se é tempo de aumentar ou diminuir o PWM
      checkNuvens();     // Executa o analogWrite para nuvens
      checkRelampago();  // Executa o relâmpago
    }
    else
    {
      aguardeIntervalo(); // Verifica se é o momento de esperar até a próxima nuvem
    }
  }
}

void checkNuvens()
{
  for (byte i = 0; i < NUMERO_CANAIS; i++)
  {
    if (desativarNuvemCanal[i] == true)
    {
      if ((relampagoNoturno == true) && (i == EXTRA_CHANNEL_FOR_LIGHTNING))
      {
        // Não executa nuvem para o canal extra.
      }
      else
      {
        analogWrite(pinoLED[i], pwm_nuvem[i]);
      }
    }
  }
}

void checkRelampago()
{
  for (int i = 0; i < random(1, 5); i++)
  {
    for (byte i = 0; i < NUMERO_CANAIS; i++)
    {
      if (desativarRelampagoCanal[i] == true)
      {
        if (pontoBaixo[i] == true)
        {
          executeRelampago(i);
          temDelay = true;
        }
      }
      else
      {
        if ((relampagoNoturno == true) && (i == EXTRA_CHANNEL_FOR_LIGHTNING))
        {
          if (pontoBaixo[i] == true)
          {
            executeRelampago(i);
            temDelay = true;
          }
        }
      }
    }
    if (temDelay == true)
    {
      temDelay = false;
      delay(random(200, 500));
    }

    #ifdef WATCHDOG
      wdt_reset();
    #endif
  }
}

void executeRelampago(byte i)
{
  analogWrite(pinoLED[i], random(pwm_nuvem[i], 126)); // Pequena oscilação
  delay(random(25, 75));
  analogWrite(pinoLED[i], random(126, 175));          // Pequena oscilação
  delay(random(25, 50));
  analogWrite(pinoLED[i], 126);                       // Luz media
  delay(random(50, 100));
  analogWrite(pinoLED[i], 255);                       // Luz alta
  delay(random(100, 200));
  analogWrite(pinoLED[i], 126);                       // Luz media
  delay(random(50, 100));
  analogWrite(pinoLED[i], pwm_nuvem[i]);              // Luz normal

  #ifdef USE_EXTRA_CHANNEL_FOR_LIGHTNING_DURING_NIGHT

    if ((relampagoNoturno == true) && (i == EXTRA_CHANNEL_FOR_LIGHTNING))
    {
      delay(random(50, 100));
      analogWrite(pinoLED[i], valorAnterior);
    }

  #endif

}

void aguardeIntervalo()
{
  if ((millis() - LED_millis) > espere) // Escolhe um intervalo entre 4 e 7s até a próxima nuvem.
  {
    aguarde = false;
    espere = random(4000, 7000);
  }
}

void checkTempoRampa()
{
  if ((millis() - millisRampa) > TEMPO_RAMPA)
  {
    checkRampaNuvem();
    millisRampa = millis();
  }
}

void checkRampaNuvem()
{
  byte pwmAtualLED[NUMERO_CANAIS] = {wled_out, bled_out, rbled_out, rled_out, uvled_out, moonled_out};  // Branco, azul, azul royal, vermelho, violeta, luz noturna

  if (inicioNuvem == true)
  {
    LOGLN(F("Cloud in progress..."));
    inicioNuvem = false;
    for (byte i = 0; i < NUMERO_CANAIS; i++)
    {
      pwm_nuvem[i] = pwmAtualLED[i];
    }

    #ifdef USE_EXTRA_CHANNEL_FOR_LIGHTNING_DURING_NIGHT

      if (pwmAtualLED[EXTRA_CHANNEL_FOR_LIGHTNING] <= MIN_PWM_NUVEM)
      {
        valorAnterior = pwmAtualLED[EXTRA_CHANNEL_FOR_LIGHTNING];
        pwm_nuvem[EXTRA_CHANNEL_FOR_LIGHTNING] = moonled_out;
        relampagoNoturno = true;
      }
      else
      {
        relampagoNoturno = false;
      }
    #endif
  }

  #ifdef USE_EXTRA_CHANNEL_FOR_LIGHTNING_DURING_NIGHT
    if (relampagoNoturno == true)
    {
      pwmAtualLED[EXTRA_CHANNEL_FOR_LIGHTNING] = moonled_out;
    }
  #endif

  for (byte i = 0; i < NUMERO_CANAIS; i++)
  {
    if (pwmAtualLED[i] > MIN_PWM_NUVEM)
    {
      if (passo[i] == 0)
      {
        if (pwm_nuvem[i] >= int(pwmAtualLED[i] * 0.2))
        {
          pwm_nuvem[i]--;
        }
        if (pwm_nuvem[i] <= int(pwmAtualLED[i] * 0.2))
        {
          passo[i] = 1;
          pontoBaixo[i] = true;
        }
      }
      else
      {
        pontoBaixo[i] = false;
        if (pwm_nuvem[i] <= pwmAtualLED[i])
        {
          pwm_nuvem[i]++;
        }
        if (pwm_nuvem[i] >= pwmAtualLED[i])
        {
          passo[i] = 0;
          aguarde = true;
          LED_millis = millis();
        }
      }
    }
  } // for
}
void probabilidadeNuvem()
{
  int aleatorio = 0;

  aleatorio = random(0, 100);

  duracaoNuvem = random(quantDuracaoMinMaxNuvem[2], quantDuracaoMinMaxNuvem[3] + 1); // Quant. mín., quant. máx., duração min., duração máx.

  if(duracaoNuvem < 1)
  {
    duracaoNuvem = 1;
  }

  duracaoRelampago = random(duracaoMinMaxRelampago[0], duracaoMinMaxRelampago[1] + 1);

  if(duracaoRelampago < 1)
  {
    duracaoRelampago = 1;
  }

  if (aleatorio >= probNuvemRelampago[0]) // [0]= nuvem, [1] = relâmpago
  {
    haveraNuvem = false;
    LOGLN(F("\nThere won't be clouds today."));
  }
  else
  {
    haveraNuvem = true;
    LOGLN(F("\nThere will be clouds today."));
  }

  if ((t.date % nuvemCadaXdias) != 0)
  {
    haveraNuvem = false;
  }

  if (haveraNuvem == true)
  {
    quantNuvens = random(quantDuracaoMinMaxNuvem[0], quantDuracaoMinMaxNuvem[1] + 1); // Quant. mín., quant. máx., duração min., duração máx.

    int hora;
    int minuto;

    for (int i = 0; i < quantNuvens; i++)
    {
      horaNuvem[i] = random(1, 1440);
    }

    qsort(horaNuvem, 10, 2, sort_asc); // qsort(array, array size, size of each array element > int = 2 bytes)

    aleatorio = random(0, 100);


    if ((aleatorio >= probNuvemRelampago[1]) || (haveraNuvem == false)) // [0]= nuvem, [1] = relâmpago
    {
      haveraRelampago = false;
      LOGLN(F("There won't be lightning today."));
    }
    else
    {
      haveraRelampago = true;
      LOGLN(F("There will be lightning today."));
    }

    #ifdef DEBUG
      LOG(F("Cloud schedule ["));

      for (int i = 0; i < quantNuvens; i++)
      {
        minuto = horaNuvem[i] % 60;
        hora = (horaNuvem[i] - minuto) / 60;

        LOG(hora);
        LOG(F(":"));
        LOG(minuto);

        if(i < (quantNuvens - 1))
        {
          LOG(F(", "));
        }
      }

      LOGLN(F("]."));

      LOG(F("Cloud duration: "));
      LOG(duracaoNuvem);
      LOGLN(F(" minute(s)."));

      if(haveraRelampago == true)
      {
        LOG(F("Lightning duration: "));
        LOG(duracaoRelampago);
        LOGLN(F(" minute(s)."));
      }
    #endif
  }
  LOGLN();
}
