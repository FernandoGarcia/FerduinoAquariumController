//**********************************************************************************************
//************************ Funcões EEPROM ******************************************************
//**********************************************************************************************
struct config_t                              // Temperatura
{
  int tempset;
  byte tempoff;
  byte tempalarm;
} 
tempSettings;

struct config_PHR                          // PH do reator
{
  byte PHRset;
  byte PHRoff;
  byte PHRalarm;
} 
PHRSettings;

struct config_PHA                         // PH do aquario
{
  byte PHAset;
  byte PHAoff;
  byte PHAalarm;
} 
PHASettings;

struct config_ORP                        // ORP
{
  int ORPset;
  byte ORPoff;
  byte ORPalarm;
} 
ORPSettings;

struct config_DEN                        // Densidade
{
  int DENset;
  byte DENoff;
  byte DENalarm;
} 
DENSettings;

struct config_tpa                       // TPA automatica
{
  byte temphora;
  byte tempminuto;
  byte tempduracaomaximatpa;
  byte tempsegunda;
  byte tempterca;
  byte tempquarta;
  byte tempquinta;
  byte tempsexta;
  byte tempsabado;
  byte tempdomingo;
} 
tpaconfig;

struct config_dos_calib
{
  int fator_calib_dosadora_1_temp;
  int fator_calib_dosadora_2_temp;
  int fator_calib_dosadora_3_temp;
  int fator_calib_dosadora_4_temp;
  int fator_calib_dosadora_5_temp;
  int fator_calib_dosadora_6_temp;
}
dosaCalib;

struct config_dos
{
  int dose_dosadora_1_personalizada_temp;
  int dose_dosadora_2_personalizada_temp;
  int dose_dosadora_3_personalizada_temp;
  int dose_dosadora_4_personalizada_temp;
  int dose_dosadora_5_personalizada_temp;
  int dose_dosadora_6_personalizada_temp;
  byte hora_inicial_dosagem_personalizada_1_temp; 
  byte minuto_inicial_dosagem_personalizada_1_temp;
  byte hora_final_dosagem_personalizada_1_temp; 
  byte minuto_final_dosagem_personalizada_1_temp; 
  byte segunda_dosagem_personalizada_1_temp; 
  byte terca_dosagem_personalizada_1_temp; 
  byte quarta_dosagem_personalizada_1_temp; 
  byte quinta_dosagem_personalizada_1_temp; 
  byte sexta_dosagem_personalizada_1_temp; 
  byte sabado_dosagem_personalizada_1_temp; 
  byte domingo_dosagem_personalizada_1_temp;
  byte hora_inicial_dosagem_personalizada_2_temp; 
  byte minuto_inicial_dosagem_personalizada_2_temp;
  byte hora_final_dosagem_personalizada_2_temp; 
  byte minuto_final_dosagem_personalizada_2_temp; 
  byte terca_dosagem_personalizada_2_temp; 
  byte quarta_dosagem_personalizada_2_temp; 
  byte quinta_dosagem_personalizada_2_temp; 
  byte sexta_dosagem_personalizada_2_temp; 
  byte sabado_dosagem_personalizada_2_temp; 
  byte domingo_dosagem_personalizada_2_temp;
  byte hora_inicial_dosagem_personalizada_3_temp; 
  byte minuto_inicial_dosagem_personalizada_3_temp;
  byte hora_final_dosagem_personalizada_3_temp; 
  byte minuto_final_dosagem_personalizada_3_temp;  
  byte terca_dosagem_personalizada_3_temp; 
  byte quarta_dosagem_personalizada_3_temp; 
  byte quinta_dosagem_personalizada_3_temp; 
  byte sexta_dosagem_personalizada_3_temp; 
  byte sabado_dosagem_personalizada_3_temp; 
  byte domingo_dosagem_personalizada_3_temp;
  byte quantidade_dose_dosadora_1_personalizada_temp;
  byte quantidade_dose_dosadora_2_personalizada_temp;
  byte quantidade_dose_dosadora_3_personalizada_temp;
  byte modo_personalizado_on_1_temp;
  byte hora_inicial_dosagem_personalizada_4_temp; 
  byte minuto_inicial_dosagem_personalizada_4_temp;
  byte hora_final_dosagem_personalizada_4_temp; 
  byte minuto_final_dosagem_personalizada_4_temp; 
  byte terca_dosagem_personalizada_4_temp; 
  byte quarta_dosagem_personalizada_4_temp; 
  byte quinta_dosagem_personalizada_4_temp; 
  byte sexta_dosagem_personalizada_4_temp; 
  byte sabado_dosagem_personalizada_4_temp; 
  byte domingo_dosagem_personalizada_4_temp;
  byte hora_inicial_dosagem_personalizada_5_temp; 
  byte minuto_inicial_dosagem_personalizada_5_temp;
  byte hora_final_dosagem_personalizada_5_temp; 
  byte minuto_final_dosagem_personalizada_5_temp; 
  byte terca_dosagem_personalizada_5_temp; 
  byte quarta_dosagem_personalizada_5_temp; 
  byte quinta_dosagem_personalizada_5_temp; 
  byte sexta_dosagem_personalizada_5_temp; 
  byte sabado_dosagem_personalizada_5_temp; 
  byte domingo_dosagem_personalizada_5_temp;
  byte hora_inicial_dosagem_personalizada_6_temp; 
  byte minuto_inicial_dosagem_personalizada_6_temp;
  byte hora_final_dosagem_personalizada_6_temp; 
  byte minuto_final_dosagem_personalizada_6_temp; 
  byte terca_dosagem_personalizada_6_temp; 
  byte quarta_dosagem_personalizada_6_temp; 
  byte quinta_dosagem_personalizada_6_temp; 
  byte sexta_dosagem_personalizada_6_temp; 
  byte sabado_dosagem_personalizada_6_temp; 
  byte domingo_dosagem_personalizada_6_temp;
  byte quantidade_dose_dosadora_4_personalizada_temp;
  byte quantidade_dose_dosadora_5_personalizada_temp;
  byte quantidade_dose_dosadora_6_personalizada_temp;
  byte segunda_dosagem_personalizada_2_temp;
  byte segunda_dosagem_personalizada_3_temp;
  byte segunda_dosagem_personalizada_4_temp;
  byte segunda_dosagem_personalizada_5_temp;
  byte segunda_dosagem_personalizada_6_temp;
  byte modo_personalizado_on_2_temp;
  byte modo_personalizado_on_3_temp;
  byte modo_personalizado_on_4_temp;
  byte modo_personalizado_on_5_temp;
  byte modo_personalizado_on_6_temp;
}
dosaconfig;

struct config_wave                        // Luz noturna
{
  byte modo_selecionado_temp; 
  byte Pump1PWM_temp2;    
  byte Pump2PWM_temp2;
  int periodo_temp;
  int duracao_temp;
} 
wave;

struct config_luz                        // Luz noturna
{
  byte MaxI_t;
  byte MinI_t;
} 
luznoturna;

struct config_timers
{
  byte on1_minuto_temp;
  byte on1_hora_temp;
  byte on2_minuto_temp;
  byte on2_hora_temp;
  byte on3_minuto_temp;
  byte on3_hora_temp;
  byte on4_minuto_temp;
  byte on4_hora_temp;
  byte on5_minuto_temp;
  byte on5_hora_temp;
  byte off1_minuto_temp;
  byte off1_hora_temp;
  byte off2_minuto_temp;
  byte off2_hora_temp;
  byte off3_minuto_temp;
  byte off3_hora_temp;
  byte off4_minuto_temp;
  byte off4_hora_temp;
  byte off5_minuto_temp;
  byte off5_hora_temp;
  byte temporizador_1_ativado_temp;
  byte temporizador_2_ativado_temp;
  byte temporizador_3_ativado_temp;
  byte temporizador_4_ativado_temp;
  byte temporizador_5_ativado_temp;
}
timers;

struct config_coolers                        // coolers
{
  int HtempMin_t;
  int HtempMax_t;
} 
coolers;

void SaveLEDToEEPROM()                  
{
  byte k = 222;
  EEPROM.write(796, k);         // Verifica se há valores para os LEDs na EEPROM
  for (int i=1; i<97; i++)  
  {
    EEPROM.write(i, wled[i-1]);
    EEPROM.write(i+96, bled[i-1]);
    EEPROM.write(i+(96*2), rbled[i-1]);
    EEPROM.write(i+(96*3), rled[i-1]);
    EEPROM.write(i+(96*4), uvled[i-1]);
  }
}

void SaveTempToEEPROM()
{
  byte k = 66;
  EEPROM.write(693, k);
  tempSettings.tempset = int(setTempC*10);
  tempSettings.tempoff = int(offTempC*10);
  tempSettings.tempalarm = int(alarmTempC*10);
  EEPROM_writeAnything(482, tempSettings);
}

void SalvartpaEEPROM()
{
  tpaconfig.temphora = int(hora);
  tpaconfig.tempminuto = int(minuto);
  tpaconfig.tempduracaomaximatpa = int(duracaomaximatpa);
  tpaconfig.tempsegunda = int(segunda);
  tpaconfig.tempterca = int(terca);
  tpaconfig.tempquarta = int(quarta);
  tpaconfig.tempquinta = int(quinta);
  tpaconfig.tempsexta = int(sexta);
  tpaconfig.tempsabado = int(sabado);
  tpaconfig.tempdomingo = int(domingo);
  EEPROM_writeAnything(488, tpaconfig);
}

void SavePHRToEEPROM()
{
  PHRSettings.PHRset = int(setPHR*10);
  PHRSettings.PHRoff = int(offPHR*10);
  PHRSettings.PHRalarm = int(alarmPHR*10);
  EEPROM_writeAnything(508, PHRSettings);
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
  PHASettings.PHAset = int(setPHA*10);
  PHASettings.PHAoff = int(offPHA*10);
  PHASettings.PHAalarm = int(alarmPHA*10);
  EEPROM_writeAnything(520, PHASettings);
}

void SaveDENToEEPROM()
{
  byte k = 66;
  EEPROM.write(707, k);
  DENSettings.DENset = int(setDEN-1000);
  DENSettings.DENoff = int(offDEN);
  DENSettings.DENalarm = int(alarmDEN);
  EEPROM_writeAnything(526, DENSettings);

}

void Salvar_calib_dosadora_EEPROM()
{
  byte k = 66;
  EEPROM.write(532, k); 
  dosaCalib.fator_calib_dosadora_1_temp = int (fator_calib_dosadora_1*10);
  dosaCalib.fator_calib_dosadora_2_temp = int (fator_calib_dosadora_2*10);
  dosaCalib.fator_calib_dosadora_3_temp = int (fator_calib_dosadora_3*10);
  dosaCalib.fator_calib_dosadora_4_temp = int (fator_calib_dosadora_4*10);
  dosaCalib.fator_calib_dosadora_5_temp = int (fator_calib_dosadora_5*10);
  dosaCalib.fator_calib_dosadora_6_temp = int (fator_calib_dosadora_6*10);
  EEPROM_writeAnything(533, dosaCalib);
}

void Salvar_dosadora_EEPROM()
{
  byte k = 66;
  EEPROM.write(706, k);
  dosaconfig.dose_dosadora_1_personalizada_temp = int(dose_dosadora_1_personalizada*10);
  dosaconfig.dose_dosadora_2_personalizada_temp = int(dose_dosadora_2_personalizada*10);
  dosaconfig.dose_dosadora_3_personalizada_temp = int(dose_dosadora_3_personalizada*10);
  dosaconfig.dose_dosadora_4_personalizada_temp = int(dose_dosadora_4_personalizada*10);
  dosaconfig.dose_dosadora_5_personalizada_temp = int(dose_dosadora_5_personalizada*10);
  dosaconfig.dose_dosadora_6_personalizada_temp = int(dose_dosadora_6_personalizada*10);
  dosaconfig.hora_inicial_dosagem_personalizada_1_temp = int(hora_inicial_dosagem_personalizada_1);
  dosaconfig.minuto_inicial_dosagem_personalizada_1_temp = int(minuto_inicial_dosagem_personalizada_1); 
  dosaconfig.hora_final_dosagem_personalizada_1_temp = int(hora_final_dosagem_personalizada_1);
  dosaconfig.minuto_final_dosagem_personalizada_1_temp = int(minuto_final_dosagem_personalizada_1);
  dosaconfig.segunda_dosagem_personalizada_1_temp = segunda_dosagem_personalizada_1;
  dosaconfig.terca_dosagem_personalizada_1_temp = int(terca_dosagem_personalizada_1);
  dosaconfig.quarta_dosagem_personalizada_1_temp = int(quarta_dosagem_personalizada_1);
  dosaconfig.quinta_dosagem_personalizada_1_temp = int(quinta_dosagem_personalizada_1);
  dosaconfig.sexta_dosagem_personalizada_1_temp = int(sexta_dosagem_personalizada_1);
  dosaconfig.sabado_dosagem_personalizada_1_temp = int(sabado_dosagem_personalizada_1);
  dosaconfig.domingo_dosagem_personalizada_1_temp = int(domingo_dosagem_personalizada_1);
  dosaconfig.hora_inicial_dosagem_personalizada_2_temp = int(hora_inicial_dosagem_personalizada_2);
  dosaconfig.minuto_inicial_dosagem_personalizada_2_temp = int(minuto_inicial_dosagem_personalizada_2); 
  dosaconfig.hora_final_dosagem_personalizada_2_temp = int(hora_final_dosagem_personalizada_2);
  dosaconfig.minuto_final_dosagem_personalizada_2_temp = int(minuto_final_dosagem_personalizada_2);
  dosaconfig.terca_dosagem_personalizada_2_temp = int(terca_dosagem_personalizada_2);
  dosaconfig.quarta_dosagem_personalizada_2_temp = int(quarta_dosagem_personalizada_2);
  dosaconfig.quinta_dosagem_personalizada_2_temp = int(quinta_dosagem_personalizada_2);
  dosaconfig.sexta_dosagem_personalizada_2_temp = int(sexta_dosagem_personalizada_2);
  dosaconfig.sabado_dosagem_personalizada_2_temp = int(sabado_dosagem_personalizada_2);
  dosaconfig.domingo_dosagem_personalizada_2_temp = int(domingo_dosagem_personalizada_2);
  dosaconfig.hora_inicial_dosagem_personalizada_3_temp = int(hora_inicial_dosagem_personalizada_3);
  dosaconfig.minuto_inicial_dosagem_personalizada_3_temp = int(minuto_inicial_dosagem_personalizada_3); 
  dosaconfig.hora_final_dosagem_personalizada_3_temp = int(hora_final_dosagem_personalizada_3);
  dosaconfig.minuto_final_dosagem_personalizada_3_temp = int(minuto_final_dosagem_personalizada_3);
  dosaconfig.terca_dosagem_personalizada_3_temp = int(terca_dosagem_personalizada_3);
  dosaconfig.quarta_dosagem_personalizada_3_temp = int(quarta_dosagem_personalizada_3);
  dosaconfig.quinta_dosagem_personalizada_3_temp = int(quinta_dosagem_personalizada_3);
  dosaconfig.sexta_dosagem_personalizada_3_temp = int(sexta_dosagem_personalizada_3);
  dosaconfig.sabado_dosagem_personalizada_3_temp = int(sabado_dosagem_personalizada_3);
  dosaconfig.domingo_dosagem_personalizada_3_temp = int(domingo_dosagem_personalizada_3);
  dosaconfig.quantidade_dose_dosadora_1_personalizada_temp = int(quantidade_dose_dosadora_1_personalizada);
  dosaconfig.quantidade_dose_dosadora_2_personalizada_temp = int(quantidade_dose_dosadora_2_personalizada);
  dosaconfig.quantidade_dose_dosadora_3_personalizada_temp = int(quantidade_dose_dosadora_3_personalizada);
  dosaconfig.modo_personalizado_on_1_temp = modo_personalizado_on_1;
  dosaconfig.hora_inicial_dosagem_personalizada_4_temp = int(hora_inicial_dosagem_personalizada_4);
  dosaconfig.minuto_inicial_dosagem_personalizada_4_temp = int(minuto_inicial_dosagem_personalizada_4); 
  dosaconfig.hora_final_dosagem_personalizada_4_temp = int(hora_final_dosagem_personalizada_4);
  dosaconfig.minuto_final_dosagem_personalizada_4_temp = int(minuto_final_dosagem_personalizada_4);
  dosaconfig.terca_dosagem_personalizada_4_temp = int(terca_dosagem_personalizada_4);
  dosaconfig.quarta_dosagem_personalizada_4_temp = int(quarta_dosagem_personalizada_4);
  dosaconfig.quinta_dosagem_personalizada_4_temp = int(quinta_dosagem_personalizada_4);
  dosaconfig.sexta_dosagem_personalizada_4_temp = int(sexta_dosagem_personalizada_4);
  dosaconfig.sabado_dosagem_personalizada_4_temp = int(sabado_dosagem_personalizada_4);
  dosaconfig.domingo_dosagem_personalizada_4_temp = int(domingo_dosagem_personalizada_4);
  dosaconfig.hora_inicial_dosagem_personalizada_5_temp = int(hora_inicial_dosagem_personalizada_5);
  dosaconfig.minuto_inicial_dosagem_personalizada_5_temp = int(minuto_inicial_dosagem_personalizada_5); 
  dosaconfig.hora_final_dosagem_personalizada_5_temp = int(hora_final_dosagem_personalizada_5);
  dosaconfig.minuto_final_dosagem_personalizada_5_temp = int(minuto_final_dosagem_personalizada_5);
  dosaconfig.terca_dosagem_personalizada_5_temp = int(terca_dosagem_personalizada_5);
  dosaconfig.quarta_dosagem_personalizada_5_temp = int(quarta_dosagem_personalizada_5);
  dosaconfig.quinta_dosagem_personalizada_5_temp = int(quinta_dosagem_personalizada_5);
  dosaconfig.sexta_dosagem_personalizada_5_temp = int(sexta_dosagem_personalizada_5);
  dosaconfig.sabado_dosagem_personalizada_5_temp = int(sabado_dosagem_personalizada_5);
  dosaconfig.domingo_dosagem_personalizada_5_temp = int(domingo_dosagem_personalizada_5);
  dosaconfig.hora_inicial_dosagem_personalizada_6_temp = int(hora_inicial_dosagem_personalizada_6);
  dosaconfig.minuto_inicial_dosagem_personalizada_6_temp = int(minuto_inicial_dosagem_personalizada_6); 
  dosaconfig.hora_final_dosagem_personalizada_6_temp = int(hora_final_dosagem_personalizada_6);
  dosaconfig.minuto_final_dosagem_personalizada_6_temp = int(minuto_final_dosagem_personalizada_6);
  dosaconfig.terca_dosagem_personalizada_6_temp = int(terca_dosagem_personalizada_6);
  dosaconfig.quarta_dosagem_personalizada_6_temp = int(quarta_dosagem_personalizada_6);
  dosaconfig.quinta_dosagem_personalizada_6_temp = int(quinta_dosagem_personalizada_6);
  dosaconfig.sexta_dosagem_personalizada_6_temp = int(sexta_dosagem_personalizada_6);
  dosaconfig.sabado_dosagem_personalizada_6_temp = int(sabado_dosagem_personalizada_6);
  dosaconfig.domingo_dosagem_personalizada_6_temp = int(domingo_dosagem_personalizada_6);
  dosaconfig.quantidade_dose_dosadora_4_personalizada_temp = int(quantidade_dose_dosadora_4_personalizada);
  dosaconfig.quantidade_dose_dosadora_5_personalizada_temp = int(quantidade_dose_dosadora_5_personalizada);
  dosaconfig.quantidade_dose_dosadora_6_personalizada_temp = int(quantidade_dose_dosadora_6_personalizada);
  dosaconfig.segunda_dosagem_personalizada_2_temp = segunda_dosagem_personalizada_2;
  dosaconfig.segunda_dosagem_personalizada_3_temp = segunda_dosagem_personalizada_3;
  dosaconfig.segunda_dosagem_personalizada_4_temp = segunda_dosagem_personalizada_4;
  dosaconfig.segunda_dosagem_personalizada_5_temp = segunda_dosagem_personalizada_5;
  dosaconfig.segunda_dosagem_personalizada_6_temp = segunda_dosagem_personalizada_6;
  dosaconfig.modo_personalizado_on_2_temp = modo_personalizado_on_2;
  dosaconfig.modo_personalizado_on_3_temp = modo_personalizado_on_3;
  dosaconfig.modo_personalizado_on_4_temp = modo_personalizado_on_4;
  dosaconfig.modo_personalizado_on_5_temp = modo_personalizado_on_5;
  dosaconfig.modo_personalizado_on_6_temp = modo_personalizado_on_6; 
  EEPROM_writeAnything(545, dosaconfig);
}
// Posições 635 até 687 estão livres
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
//Posições 709 a 710 disponíveis.

void Salvar_luz_noturna_EEPROM()
{
  luznoturna.MinI_t = int(MinI);
  luznoturna.MaxI_t = int(MaxI);
  EEPROM_writeAnything(712, luznoturna);
}
void salvar_timers_EEPROM()
{
  timers.on1_minuto_temp = int(on1_minuto); 
  timers.on1_hora_temp = int(on1_hora);
  timers.on2_minuto_temp = int(on2_minuto); 
  timers.on2_hora_temp = int(on2_hora);
  timers.on3_minuto_temp = int(on3_minuto); 
  timers.on3_hora_temp = int(on3_hora);
  timers.on4_minuto_temp = int(on4_minuto); 
  timers.on4_hora_temp = int(on4_hora);
  timers.on5_minuto_temp = int(on5_minuto); 
  timers.on5_hora_temp = int(on5_hora);
  timers.off1_minuto_temp = int(off1_minuto); 
  timers.off1_hora_temp = int(off1_hora);
  timers.off2_minuto_temp = int(off2_minuto); 
  timers.off2_hora_temp = int(off2_hora);
  timers.off3_minuto_temp = int(off3_minuto); 
  timers.off3_hora_temp = int(off3_hora);
  timers.off4_minuto_temp = int(off4_minuto); 
  timers.off4_hora_temp = int(off4_hora);
  timers.off5_minuto_temp = int(off5_minuto); 
  timers.off5_hora_temp = int(off5_hora);  
  timers.temporizador_1_ativado_temp = int(temporizador_1_ativado);
  timers.temporizador_2_ativado_temp = int(temporizador_2_ativado);
  timers.temporizador_3_ativado_temp = int(temporizador_3_ativado);
  timers.temporizador_4_ativado_temp = int(temporizador_4_ativado);
  timers.temporizador_5_ativado_temp = int(temporizador_5_ativado);
  EEPROM_writeAnything(716, timers);
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
  coolers.HtempMin_t = int(HtempMin*10);
  coolers.HtempMax_t = int(HtempMax*10);
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
//*******************************************************************************************************************
//***************************** LER EEPROM ************************************************************************** 
//*******************************************************************************************************************
void ReadFromEEPROM()
{
  byte k = EEPROM.read(796); // 796 ponteiro para os valores dos leds
  if (k == 222) 
  {
    for (int i=1; i<97; i++) 
    {
      wled[i-1] = EEPROM.read(i);
      bled[i-1] = EEPROM.read(i+96);
      rbled[i-1] = EEPROM.read(i+(96*2));
      rled[i-1] = EEPROM.read(i+(96*3));
      uvled[i-1] = EEPROM.read(i+(96*4));
    }  
  }
  k = EEPROM.read(693);
  if(k == 66)
  {
    EEPROM_readAnything(482, tempSettings);  
    setTempC = tempSettings.tempset;
    setTempC /=10;
    offTempC = tempSettings.tempoff;
    offTempC /=10;
    alarmTempC = tempSettings.tempalarm;
    alarmTempC /= 10;
  }
}

void lertpaEEPROM()
{
  EEPROM_readAnything(488, tpaconfig);  
  hora = tpaconfig.temphora;
  minuto = tpaconfig.tempminuto;
  duracaomaximatpa = tpaconfig.tempduracaomaximatpa;
  segunda = tpaconfig.tempsegunda;
  terca = tpaconfig.tempterca;
  quarta = tpaconfig.tempquarta;
  quinta = tpaconfig.tempquinta;
  sexta = tpaconfig.tempsexta;
  sabado = tpaconfig.tempsabado;
  domingo = tpaconfig.tempdomingo;
}

void lerPHREEPROM()
{
  EEPROM_readAnything(508, PHRSettings);  
  setPHR = PHRSettings.PHRset;
  setPHR /=10;
  offPHR = PHRSettings.PHRoff;
  offPHR /=10;
  alarmPHR = PHRSettings.PHRalarm;
  alarmPHR /= 10;
}

void lerORPEEPROM()
{
  byte k = EEPROM.read(705);
  if(k == 66)
  {
    EEPROM_readAnything(514, ORPSettings);  
    setORP = ORPSettings.ORPset;
    offORP = ORPSettings.ORPoff;
    alarmORP = ORPSettings.ORPalarm;
  }
}

void lerPHAEEPROM()
{
  EEPROM_readAnything(520, PHASettings);  
  setPHA = PHASettings.PHAset;
  setPHA /=10;
  offPHA = PHASettings.PHAoff;
  offPHA /=10;
  alarmPHA = PHASettings.PHAalarm;
  alarmPHA /= 10;
}

void lerDENEEPROM()
{
  byte k = EEPROM.read(707);
  if(k == 66)
  {
    EEPROM_readAnything(526, DENSettings);  
    setDEN = DENSettings.DENset;
    setDEN +=1000;
    offDEN = DENSettings.DENoff;
    alarmDEN = DENSettings.DENalarm;
  }
}

void ler_calib_dosadora_EEPROM()
{
  byte k;
  k = EEPROM.read(532);
  if(k == 66)
  {
    EEPROM_readAnything(533, dosaCalib);
    fator_calib_dosadora_1 = dosaCalib.fator_calib_dosadora_1_temp;
    fator_calib_dosadora_1 /=10;
    fator_calib_dosadora_2 = dosaCalib.fator_calib_dosadora_2_temp;
    fator_calib_dosadora_2 /=10;
    fator_calib_dosadora_3 = dosaCalib.fator_calib_dosadora_3_temp;
    fator_calib_dosadora_3 /=10;
    fator_calib_dosadora_4 = dosaCalib.fator_calib_dosadora_4_temp;
    fator_calib_dosadora_4 /=10;
    fator_calib_dosadora_5 = dosaCalib.fator_calib_dosadora_5_temp;
    fator_calib_dosadora_5 /=10;
    fator_calib_dosadora_6 = dosaCalib.fator_calib_dosadora_6_temp;
    fator_calib_dosadora_6 /=10;
  }
}
void ler_dosadora_EEPROM()
{
  EEPROM_readAnything(545,dosaconfig);

  byte k = EEPROM.read(706);

  if(k == 66)
  {
    dose_dosadora_1_personalizada = dosaconfig.dose_dosadora_1_personalizada_temp;
    dose_dosadora_1_personalizada /= 10;
    dose_dosadora_2_personalizada = dosaconfig.dose_dosadora_2_personalizada_temp;
    dose_dosadora_2_personalizada /= 10;
    dose_dosadora_3_personalizada = dosaconfig.dose_dosadora_3_personalizada_temp; 
    dose_dosadora_3_personalizada /= 10;
    dose_dosadora_4_personalizada = dosaconfig.dose_dosadora_4_personalizada_temp;
    dose_dosadora_4_personalizada /= 10;
    dose_dosadora_5_personalizada = dosaconfig.dose_dosadora_5_personalizada_temp;
    dose_dosadora_5_personalizada /= 10;
    dose_dosadora_6_personalizada = dosaconfig.dose_dosadora_6_personalizada_temp; 
    dose_dosadora_6_personalizada /= 10;
  }
  hora_inicial_dosagem_personalizada_1 = dosaconfig.hora_inicial_dosagem_personalizada_1_temp;
  minuto_inicial_dosagem_personalizada_1 = dosaconfig.minuto_inicial_dosagem_personalizada_1_temp;
  hora_final_dosagem_personalizada_1 = dosaconfig.hora_final_dosagem_personalizada_1_temp;  
  minuto_final_dosagem_personalizada_1 = dosaconfig.minuto_final_dosagem_personalizada_1_temp; 
  segunda_dosagem_personalizada_1 = dosaconfig.segunda_dosagem_personalizada_1_temp; 
  terca_dosagem_personalizada_1 = dosaconfig.terca_dosagem_personalizada_1_temp; 
  quarta_dosagem_personalizada_1 = dosaconfig.quarta_dosagem_personalizada_1_temp;
  quinta_dosagem_personalizada_1 = dosaconfig.quinta_dosagem_personalizada_1_temp;
  sexta_dosagem_personalizada_1  = dosaconfig.sexta_dosagem_personalizada_1_temp;
  sabado_dosagem_personalizada_1 = dosaconfig.sabado_dosagem_personalizada_1_temp;
  domingo_dosagem_personalizada_1 = dosaconfig.domingo_dosagem_personalizada_1_temp;
  hora_inicial_dosagem_personalizada_2 = dosaconfig.hora_inicial_dosagem_personalizada_2_temp;
  minuto_inicial_dosagem_personalizada_2 = dosaconfig.minuto_inicial_dosagem_personalizada_2_temp;
  hora_final_dosagem_personalizada_2 = dosaconfig.hora_final_dosagem_personalizada_2_temp;  
  minuto_final_dosagem_personalizada_2 = dosaconfig.minuto_final_dosagem_personalizada_2_temp; 
  terca_dosagem_personalizada_2 = dosaconfig.terca_dosagem_personalizada_2_temp; 
  quarta_dosagem_personalizada_2 = dosaconfig.quarta_dosagem_personalizada_2_temp;
  quinta_dosagem_personalizada_2 = dosaconfig.quinta_dosagem_personalizada_2_temp;
  sexta_dosagem_personalizada_2  = dosaconfig.sexta_dosagem_personalizada_2_temp;
  sabado_dosagem_personalizada_2 = dosaconfig.sabado_dosagem_personalizada_2_temp;
  domingo_dosagem_personalizada_2 = dosaconfig.domingo_dosagem_personalizada_2_temp;
  hora_inicial_dosagem_personalizada_3 = dosaconfig.hora_inicial_dosagem_personalizada_3_temp;
  minuto_inicial_dosagem_personalizada_3 = dosaconfig.minuto_inicial_dosagem_personalizada_3_temp;
  hora_final_dosagem_personalizada_3 = dosaconfig.hora_final_dosagem_personalizada_3_temp;  
  minuto_final_dosagem_personalizada_3 = dosaconfig.minuto_final_dosagem_personalizada_3_temp;  
  terca_dosagem_personalizada_3 = dosaconfig.terca_dosagem_personalizada_3_temp; 
  quarta_dosagem_personalizada_3 = dosaconfig.quarta_dosagem_personalizada_3_temp;
  quinta_dosagem_personalizada_3 = dosaconfig.quinta_dosagem_personalizada_3_temp;
  sexta_dosagem_personalizada_3  = dosaconfig.sexta_dosagem_personalizada_3_temp;
  sabado_dosagem_personalizada_3 = dosaconfig.sabado_dosagem_personalizada_3_temp;
  domingo_dosagem_personalizada_3 = dosaconfig.domingo_dosagem_personalizada_3_temp;
  quantidade_dose_dosadora_1_personalizada = dosaconfig.quantidade_dose_dosadora_1_personalizada_temp;
  quantidade_dose_dosadora_2_personalizada = dosaconfig.quantidade_dose_dosadora_2_personalizada_temp;
  quantidade_dose_dosadora_3_personalizada = dosaconfig.quantidade_dose_dosadora_3_personalizada_temp;
  modo_personalizado_on_1 = dosaconfig.modo_personalizado_on_1_temp;
  hora_inicial_dosagem_personalizada_4 = dosaconfig.hora_inicial_dosagem_personalizada_4_temp;
  minuto_inicial_dosagem_personalizada_4 = dosaconfig.minuto_inicial_dosagem_personalizada_4_temp;
  hora_final_dosagem_personalizada_4 = dosaconfig.hora_final_dosagem_personalizada_4_temp;  
  minuto_final_dosagem_personalizada_4 = dosaconfig.minuto_final_dosagem_personalizada_4_temp; 
  terca_dosagem_personalizada_4 = dosaconfig.terca_dosagem_personalizada_4_temp; 
  quarta_dosagem_personalizada_4 = dosaconfig.quarta_dosagem_personalizada_4_temp;
  quinta_dosagem_personalizada_4 = dosaconfig.quinta_dosagem_personalizada_4_temp;
  sexta_dosagem_personalizada_4  = dosaconfig.sexta_dosagem_personalizada_4_temp;
  sabado_dosagem_personalizada_4 = dosaconfig.sabado_dosagem_personalizada_4_temp;
  domingo_dosagem_personalizada_4 = dosaconfig.domingo_dosagem_personalizada_4_temp;
  hora_inicial_dosagem_personalizada_5 = dosaconfig.hora_inicial_dosagem_personalizada_5_temp;
  minuto_inicial_dosagem_personalizada_5 = dosaconfig.minuto_inicial_dosagem_personalizada_5_temp;
  hora_final_dosagem_personalizada_5 = dosaconfig.hora_final_dosagem_personalizada_5_temp;  
  minuto_final_dosagem_personalizada_5 = dosaconfig.minuto_final_dosagem_personalizada_5_temp; 
  terca_dosagem_personalizada_5 = dosaconfig.terca_dosagem_personalizada_5_temp; 
  quarta_dosagem_personalizada_5 = dosaconfig.quarta_dosagem_personalizada_5_temp;
  quinta_dosagem_personalizada_5 = dosaconfig.quinta_dosagem_personalizada_5_temp;
  sexta_dosagem_personalizada_5  = dosaconfig.sexta_dosagem_personalizada_5_temp;
  sabado_dosagem_personalizada_5 = dosaconfig.sabado_dosagem_personalizada_5_temp;
  domingo_dosagem_personalizada_5 = dosaconfig.domingo_dosagem_personalizada_5_temp;
  hora_inicial_dosagem_personalizada_6 = dosaconfig.hora_inicial_dosagem_personalizada_6_temp;
  minuto_inicial_dosagem_personalizada_6 = dosaconfig.minuto_inicial_dosagem_personalizada_6_temp;
  hora_final_dosagem_personalizada_6 = dosaconfig.hora_final_dosagem_personalizada_6_temp;  
  minuto_final_dosagem_personalizada_6 = dosaconfig.minuto_final_dosagem_personalizada_6_temp; 
  terca_dosagem_personalizada_6 = dosaconfig.terca_dosagem_personalizada_6_temp; 
  quarta_dosagem_personalizada_6 = dosaconfig.quarta_dosagem_personalizada_6_temp;
  quinta_dosagem_personalizada_6 = dosaconfig.quinta_dosagem_personalizada_6_temp;
  sexta_dosagem_personalizada_6  = dosaconfig.sexta_dosagem_personalizada_6_temp;
  sabado_dosagem_personalizada_6 = dosaconfig.sabado_dosagem_personalizada_6_temp;
  domingo_dosagem_personalizada_6 = dosaconfig.domingo_dosagem_personalizada_6_temp;
  quantidade_dose_dosadora_4_personalizada = dosaconfig.quantidade_dose_dosadora_4_personalizada_temp;
  quantidade_dose_dosadora_5_personalizada = dosaconfig.quantidade_dose_dosadora_5_personalizada_temp;
  quantidade_dose_dosadora_6_personalizada = dosaconfig.quantidade_dose_dosadora_6_personalizada_temp;
  segunda_dosagem_personalizada_2 = dosaconfig.segunda_dosagem_personalizada_2_temp;
  segunda_dosagem_personalizada_3 = dosaconfig.segunda_dosagem_personalizada_3_temp;
  segunda_dosagem_personalizada_4 = dosaconfig.segunda_dosagem_personalizada_4_temp;
  segunda_dosagem_personalizada_5 = dosaconfig.segunda_dosagem_personalizada_5_temp;
  segunda_dosagem_personalizada_6 = dosaconfig.segunda_dosagem_personalizada_6_temp;
  modo_personalizado_on_2 = dosaconfig.modo_personalizado_on_2_temp;
  modo_personalizado_on_3 = dosaconfig.modo_personalizado_on_3_temp;
  modo_personalizado_on_4 = dosaconfig.modo_personalizado_on_4_temp;
  modo_personalizado_on_5 = dosaconfig.modo_personalizado_on_5_temp;
  modo_personalizado_on_6 = dosaconfig.modo_personalizado_on_6_temp;
}

void ler_wave_EEPROM()
{
  byte k = EEPROM.read(694);

  if(k == 66)
  {
    EEPROM_readAnything(695, wave);
    modo_selecionado = wave.modo_selecionado_temp; 
    Pump1PWM_temp = wave.Pump1PWM_temp2;    
    Pump2PWM_temp = wave.Pump2PWM_temp2;
    periodo = (wave.periodo_temp * 100);
    duracao = (wave.duracao_temp * 100);
  } 
}

void ler_luz_noturna_EEPROM()
{
  EEPROM_readAnything(712, luznoturna);  
  MinI = luznoturna.MinI_t;
  MaxI = luznoturna.MaxI_t;
}
void ler_timers_EEPROM()
{
  EEPROM_readAnything(716, timers);
  on1_minuto = timers.on1_minuto_temp; 
  on1_hora = timers.on1_hora_temp;
  on2_minuto = timers.on2_minuto_temp; 
  on2_hora = timers.on2_hora_temp;
  on3_minuto = timers.on3_minuto_temp; 
  on3_hora = timers.on3_hora_temp;
  on4_minuto = timers.on4_minuto_temp; 
  on4_hora = timers.on4_hora_temp;
  on5_minuto = timers.on5_minuto_temp; 
  on5_hora = timers.on5_hora_temp;
  off1_minuto = timers.off1_minuto_temp; 
  off1_hora = timers.off1_hora_temp;
  off2_minuto = timers.off2_minuto_temp; 
  off2_hora = timers.off2_hora_temp;
  off3_minuto = timers.off3_minuto_temp; 
  off3_hora = timers.off3_hora_temp;
  off4_minuto = timers.off4_minuto_temp; 
  off4_hora = timers.off4_hora_temp;
  off5_minuto = timers.off5_minuto_temp; 
  off5_hora = timers.off5_hora_temp;
  temporizador_1_ativado = timers.temporizador_1_ativado_temp;
  temporizador_2_ativado = timers.temporizador_2_ativado_temp;
  temporizador_3_ativado = timers.temporizador_3_ativado_temp;
  temporizador_4_ativado = timers.temporizador_4_ativado_temp;
  temporizador_5_ativado = timers.temporizador_5_ativado_temp;
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
  if(k == 66)
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
  if(k == 66)
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
  if(k == 66)
  {
    tempHR = EEPROM.read(804);
    potR = EEPROM.read(806);
  }
}

void ler_predefinido_EEPROM()
{
  byte k = EEPROM.read(708);
  if(k == 66)
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



