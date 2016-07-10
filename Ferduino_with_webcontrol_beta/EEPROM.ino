//**********************************************************************************************
//************************ Funcões EEPROM ******************************************************
//**********************************************************************************************
struct config_t                         // Temperatura
{
  int tempset;
  byte tempoff;
  byte tempalarm;
}
tempSettings;

struct config_ORP                        // ORP
{
  int ORPset;
  byte ORPoff;
  byte ORPalarm;
}
ORPSettings;

struct config_wave                       // Luz noturna
{
  byte modo_selecionado_temp;
  byte Pump1PWM_temp2;
  byte Pump2PWM_temp2;
  int periodo_temp;
  int duracao_temp;
}
wave;

struct config_coolers                    // Coolers
{
  int HtempMin_t;
  int HtempMax_t;
}
coolers;

struct config_dos_calib
{
  int calibracao;
}
dosaCalib[6];

struct config_dos
{
  int dose_personalizada;
}
dosaconfig[6];

void SaveLEDToEEPROM()
{
  byte k = 222;
  EEPROM.write(796, k);         // Salva ponteiro para os LEDs na EEPROM
  for (int i = 1; i < 97; i++)
  {
    EEPROM.write(i, wled[i - 1]);
    EEPROM.write(i + 96, bled[i - 1]);
    EEPROM.write(i + (96 * 2), rbled[i - 1]);
    EEPROM.write(i + (96 * 3), rled[i - 1]);
    EEPROM.write(i + (96 * 4), uvled[i - 1]);
  }
}

void SaveTempToEEPROM()
{
  byte k = 66;
  EEPROM.write(693, k);
  tempSettings.tempset = int(setTempC * 10);
  tempSettings.tempoff = int(offTempC * 10);
  tempSettings.tempalarm = int(alarmTempC * 10);
  EEPROM_writeAnything(482, tempSettings);
}

void SalvartpaEEPROM()
{
  EEPROM.write(488, hora);
  EEPROM.write(489, minuto);
  EEPROM.write(490, duracaomaximatpa);

  for (byte i = 0; i < 7; i++)
  {
    EEPROM.write((491 + i), semana_e[i]);
  }
}

void SavePHRToEEPROM()
{
  EEPROM.write(508, (setPHR * 10));
  EEPROM.write(509, (offPHR * 10));
  EEPROM.write(510, (alarmPHR * 10));
}

void SaveORPToEEPROM()
{
  byte k = 66;
  EEPROM.write(705, k);
  ORPSettings.ORPset = int(setORP);
  ORPSettings.ORPoff = int(offORP);
  ORPSettings.ORPalarm = int(alarmORP);
  EEPROM_writeAnything(514, ORPSettings);
}

void SavePHAToEEPROM()
{
  EEPROM.write(520, (setPHA * 10));
  EEPROM.write(521, (offPHA * 10));
  EEPROM.write(522, (alarmPHA * 10));
}

void SaveDENToEEPROM()
{
  byte k = 66;
  EEPROM.write(707, k);
  EEPROM.write(526, (setDEN - 1000));
  EEPROM.write(527, offDEN);
  EEPROM.write(528, alarmDEN);
}

void Salvar_calib_dosadora_EEPROM()
{
  byte k = 66;
  EEPROM.write(532, k);

  for (byte i = 0; i < 6; i++)
  {
    dosaCalib[i].calibracao = (fator_calib_dosadora_e[i] * 10);
  }
  EEPROM_writeAnything(533, dosaCalib);
}

void Salvar_dosadora_EEPROM()
{
  byte k = 66;
  EEPROM.write(706, k);

  for (byte i = 0; i < 6; i++)
  {
    dosaconfig[i].dose_personalizada = (dose_dosadora_personalizada_e[i] * 10);
    EEPROM.write((557 + i), hora_inicial_dosagem_personalizada_e[i]);
    EEPROM.write((583 + i), minuto_inicial_dosagem_personalizada_e[i]);
    EEPROM.write((589 + i), segunda_dosagem_personalizada_e[i]);
    EEPROM.write((595 + i), terca_dosagem_personalizada_e[i]);
    EEPROM.write((601 + i), quarta_dosagem_personalizada_e[i]);
    EEPROM.write((607 + i), quinta_dosagem_personalizada_e[i]);
    EEPROM.write((613 + i), sexta_dosagem_personalizada_e[i]);
    EEPROM.write((619 + i), sabado_dosagem_personalizada_e[i]);
    EEPROM.write((625 + i), domingo_dosagem_personalizada_e[i]);
    EEPROM.write((631 + i), quantidade_dose_dosadora_personalizada_e[i]);
    EEPROM.write((637 + i), modo_personalizado_on_e[i]);
    EEPROM.write((643 + i), hora_final_dosagem_personalizada_e[i]);
    EEPROM.write((649 + i), minuto_final_dosagem_personalizada_e[i]);
  }
  EEPROM_writeAnything(545, dosaconfig);
}
// 688 ponteiro para log de temperatura da água.
// 689 ponteiro para log de ph do aquário.
// 690 ponteiro para log de ph do reator de cálcio.
// 691 ponteiro para log de orp.
// 692 ponteiro para log de densidade.
// 693 ponteiro para a temperatura da água.

void Salvar_wave_EEPROM()
{
  byte k = 66;
  EEPROM.write(694, k);
  wave.modo_selecionado_temp = modo_selecionado;
  wave.Pump1PWM_temp2 = Pump1PWM_temp;
  wave.Pump2PWM_temp2 = Pump2PWM_temp;
  wave.periodo_temp = (periodo / 100);
  wave.duracao_temp = (duracao / 100);
  EEPROM_writeAnything(695, wave);
}
// 705 ponteiro para ORP
// 706 ponteiro para dosadora
// 707 ponteiro para densidade
// 708 ponteiro para led predefinido
// 709 Falha TPA.
// 710 ponteiro para alimentador

void Salvar_erro_tpa_EEPROM()
{
  EEPROM.write(709, bitRead(tpa_status, 2));
}

void Salvar_luz_noturna_EEPROM()
{
  byte k = 66;
  EEPROM.write(711, k);
  EEPROM.write(712, MinI);
  EEPROM.write(713, MaxI);
}
void salvar_timers_EEPROM()
{
  for (byte i = 0; i < 5; i++)
  {
    EEPROM.write((716 + i), on_minuto_e[i]);
    EEPROM.write((721 + i), on_hora_e[i]);
    EEPROM.write((726 + i), off_minuto_e[i]);
    EEPROM.write((731 + i), off_hora_e[i]);
    EEPROM.write((736 + i), temporizador_ativado_e[i]);
  }
}

void SaveDallasAddress ()
{

  for (byte i = 0; i < 8; i++)
  {
    EEPROM.write(766 + i, sensor_agua[i]);
    EEPROM.write(775 + i, sensor_dissipador[i]);
    EEPROM.write(784 + i, sensor_ambiente[i]);
  }
  EEPROM.write(792, 66);
  EEPROM.write(793, sonda_associada_1);
  EEPROM.write(794, sonda_associada_2);
  EEPROM.write(795, sonda_associada_3);
}

void salvar_coolersEEPROM()
{
  byte k = 66;

  EEPROM.write(797, k);
  coolers.HtempMin_t = int(HtempMin * 10);
  coolers.HtempMax_t = int(HtempMax * 10);
  EEPROM_writeAnything(798, coolers);
}

void salvar_tempPotEEPROM()
{
  byte k = 66;
  EEPROM.write(802, k);
  EEPROM.write(804, tempHR);
  EEPROM.write(806, potR);
}

void Salvar_predefinido_EEPROM()
{
  byte k = 66;
  EEPROM.write(708, k);
  EEPROM.write(808, predefinido);
  EEPROM.write(809, pre_definido_ativado);
  EEPROM.write(810, pwm_pre_definido);
  EEPROM.write(811, led_on_minuto);
  EEPROM.write(813, led_on_hora);
  EEPROM.write(815, led_off_minuto);
  EEPROM.write(817, led_off_hora);
  EEPROM.write(819, bled_out_temp);
  EEPROM.write(820, wled_out_temp);
  EEPROM.write(821, rbled_out_temp);
  EEPROM.write(822, rled_out_temp);
  EEPROM.write(823, uvled_out_temp);
  EEPROM.write(824, amanhecer_anoitecer);
}
void salvar_alimentador_EEPROM()
{
  byte k = 66;
  EEPROM.write(710, k);
  for (byte i = 0; i < 4; i++)
  {
    EEPROM.write((825 + i), horario_alimentacao_e[i]);
  }
  for (byte i = 0; i < 7; i++)
  {
    EEPROM.write((829 + i), dia_alimentacao_e[i]);
  }
  EEPROM.write(836, duracao_alimentacao);
  EEPROM.write(837, desligar_wavemaker);
  EEPROM.write(838, quantidade_alimentacao);
  EEPROM.write(839, alimentacao_wavemaker_on_off);
}

void salvar_outlets_EEPROM()
{
  byte k = 66;
  EEPROM.write(840, k);
  for (byte i = 0; i < 9; i++)
  {
    EEPROM.write(841 + i, outlets[i]);
  }
}
//*******************************************************************************************************************
//***************************** LER EEPROM **************************************************************************
//*******************************************************************************************************************
void ReadFromEEPROM()
{
  byte k = EEPROM.read(796); // 796 ponteiro para os valores dos leds
  if (k == 222)
  {
    for (int i = 1; i < 97; i++)
    {
      wled[i - 1] = EEPROM.read(i);
      bled[i - 1] = EEPROM.read(i + 96);
      rbled[i - 1] = EEPROM.read(i + (96 * 2));
      rled[i - 1] = EEPROM.read(i + (96 * 3));
      uvled[i - 1] = EEPROM.read(i + (96 * 4));
    }
  }
  k = EEPROM.read(693);
  if (k == 66)
  {
    EEPROM_readAnything(482, tempSettings);
    setTempC = tempSettings.tempset;
    setTempC /= 10;
    offTempC = tempSettings.tempoff;
    offTempC /= 10;
    alarmTempC = tempSettings.tempalarm;
    alarmTempC /= 10;
  }
}

void lertpaEEPROM()
{
  hora = EEPROM.read(488);
  minuto = EEPROM.read(489);
  duracaomaximatpa = EEPROM.read(490);
  for (byte i = 0; i < 7; i++)
  {
    semana_e[i] = EEPROM.read(491 + i);
  }
}

void lerPHREEPROM()
{
  setPHR = EEPROM.read(508);
  setPHR /= 10;
  offPHR = EEPROM.read(509);
  offPHR /= 10;
  alarmPHR = EEPROM.read(510);
  alarmPHR /= 10;
}

void lerORPEEPROM()
{
  byte k = EEPROM.read(705);
  if (k == 66)
  {
    EEPROM_readAnything(514, ORPSettings);
    setORP = ORPSettings.ORPset;
    offORP = ORPSettings.ORPoff;
    alarmORP = ORPSettings.ORPalarm;
  }
}

void lerPHAEEPROM()
{
  setPHA = EEPROM.read(520);
  setPHA /= 10;
  offPHA = EEPROM.read(521);
  offPHA /= 10;
  alarmPHA = EEPROM.read(522);
  alarmPHA /= 10;
}

void lerDENEEPROM()
{
  byte k = EEPROM.read(707);
  if (k == 66)
  {
    setDEN = EEPROM.read(526);
    setDEN += 1000;
    offDEN = EEPROM.read(527);
    alarmDEN = EEPROM.read(528);
  }
}

void ler_calib_dosadora_EEPROM()
{
  byte k;
  k = EEPROM.read(532);

  if (k == 66)
  {
    EEPROM_readAnything(533, dosaCalib);

    for (byte i = 0; i < 6; i++)
    {
      fator_calib_dosadora_e[i] = dosaCalib[i].calibracao;
      fator_calib_dosadora_e[i] /= 10;
    }
  }
}
void ler_dosadora_EEPROM()
{
  byte k = EEPROM.read(706);

  if (k == 66)
  {
    EEPROM_readAnything(545, dosaconfig);

    for (byte i = 0; i < 6; i++)
    {
      dose_dosadora_personalizada_e[i] = dosaconfig[i].dose_personalizada;
      dose_dosadora_personalizada_e[i] /= 10;
    }
  }
  for (byte i = 0; i < 6; i++)
  {
    hora_inicial_dosagem_personalizada_e[i] = EEPROM.read(557 + i);
    minuto_inicial_dosagem_personalizada_e[i] = EEPROM.read(583 + i);
    segunda_dosagem_personalizada_e[i] = EEPROM.read(589 + i);
    terca_dosagem_personalizada_e[i] = EEPROM.read(595 + i);
    quarta_dosagem_personalizada_e[i] = EEPROM.read(601 + i);
    quinta_dosagem_personalizada_e[i] = EEPROM.read(607 + i);
    sexta_dosagem_personalizada_e[i] = EEPROM.read(613 + i);
    sabado_dosagem_personalizada_e[i] = EEPROM.read(619 + i);
    domingo_dosagem_personalizada_e[i] = EEPROM.read(625 + i);
    quantidade_dose_dosadora_personalizada_e[i] = EEPROM.read(631 + i);
    modo_personalizado_on_e[i] = EEPROM.read(637 + i);
    hora_final_dosagem_personalizada_e[i] = EEPROM.read(643 + i);
    minuto_final_dosagem_personalizada_e[i] = EEPROM.read(649 + i);
  }
}

void ler_wave_EEPROM()
{
  byte k = EEPROM.read(694);

  if (k == 66)
  {
    EEPROM_readAnything(695, wave);
    modo_selecionado = wave.modo_selecionado_temp;
    Pump1PWM_temp = wave.Pump1PWM_temp2;
    Pump2PWM_temp = wave.Pump2PWM_temp2;
    periodo = (wave.periodo_temp * 100);
    duracao = (wave.duracao_temp * 100);
  }
}

void check_erro_tpa_EEPROM()
{
  bitWrite(tpa_status, 2, EEPROM.read(709));
}

void ler_luz_noturna_EEPROM()
{
  byte k = EEPROM.read(711);
  if (k == 66)
  {
    MinI = EEPROM.read(712);
    MaxI = EEPROM.read(713);
  }
}
void ler_timers_EEPROM()
{
  for (byte i = 0; i < 5; i++)
  {
    on_minuto_e[i] = EEPROM.read(716 + i);
    on_hora_e[i] = EEPROM.read(721 + i);
    off_minuto_e[i] = EEPROM.read(726 + i);
    off_hora_e[i] = EEPROM.read(731 + i);
    temporizador_ativado_e[i] = EEPROM.read(736 + i);
  }
}

void ReadDallasAddress()
{
  for (byte i = 0; i < 8; i++)
  {
    sensor_agua[i] = EEPROM.read(766 + i);    // sensor address
    sensor_dissipador[i] = EEPROM.read(775 + i);
    sensor_ambiente[i] = EEPROM.read(784 + i);
  }
  byte k = EEPROM.read(792);
  if (k == 66)
  {
    sonda_associada_1 = EEPROM.read(793);
    sonda_associada_2 = EEPROM.read(794);
    sonda_associada_3 = EEPROM.read(795);
  }
}
// 796 ponteiro para os valores dos leds
void ler_coolersEEPROM()
{
  byte k;

  k = EEPROM.read(797);
  if (k == 66)
  {
    EEPROM_readAnything(798, coolers);
    HtempMin = coolers.HtempMin_t;
    HtempMin /= 10;
    HtempMax = coolers.HtempMax_t;
    HtempMax /= 10;
  }
}

void ler_tempPotEEPROM()
{
  byte k = EEPROM.read(802);
  if (k == 66)
  {
    tempHR = EEPROM.read(804);
    potR = EEPROM.read(806);
  }
}

void ler_predefinido_EEPROM()
{
  byte k = EEPROM.read(708);
  if (k == 66)
  {
    predefinido = EEPROM.read(808);
    pre_definido_ativado = EEPROM.read(809);
    pwm_pre_definido = EEPROM.read(810);
    led_on_minuto = EEPROM.read(811);
    led_on_hora = EEPROM.read(813);
    led_off_minuto = EEPROM.read(815);
    led_off_hora = EEPROM.read(817);
    bled_out_temp = EEPROM.read(819);
    wled_out_temp = EEPROM.read(820);
    rbled_out_temp = EEPROM.read(821);
    rled_out_temp = EEPROM.read(822);
    uvled_out_temp = EEPROM.read(823);
    amanhecer_anoitecer = EEPROM.read(824);
  }
}

void ler_alimentador_EEPROM()
{
  byte k = EEPROM.read(710);

  if (k == 66)
  {
    for (byte i = 0; i < 4; i++)
    {
      horario_alimentacao_e[i] = EEPROM.read(825 + i);
    }
    for (byte i = 0; i < 7; i++)
    {
      dia_alimentacao_e[i] = EEPROM.read(829 + i);
    }
    duracao_alimentacao = EEPROM.read(836);
    desligar_wavemaker = EEPROM.read(837);
    quantidade_alimentacao = EEPROM.read(838);
    alimentacao_wavemaker_on_off = EEPROM.read(839);
  }
}

void ler_outlets_EEPROM()
{
  for (byte i = 0; i < 9; i++)
  {
    outlets[i] = EEPROM.read(841 + i);
  }
}

