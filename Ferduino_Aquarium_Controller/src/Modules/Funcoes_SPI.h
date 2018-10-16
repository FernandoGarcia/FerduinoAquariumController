#pragma once // Do not change this line!
void selecionar_SPI(int dispositivo)
{
  switch (dispositivo)
  {
    case 0: // Utilizar cartão sd.
      // LOGLN(F("SD CARD selected."));
      digitalWrite(SelectSlave_ETH, HIGH);
      digitalWrite(ChipSelect_RFM, HIGH);
      digitalWrite(ChipSelect_SD, LOW);
      delay(10);
      break;

    case 1: // Utilizar ethercard
      // LOGLN(F("Ethernet selected."));
      digitalWrite(ChipSelect_SD, HIGH);
      digitalWrite(ChipSelect_RFM, HIGH);
      digitalWrite(SelectSlave_ETH, LOW);
      delay(10);
      break;

    case 2: // Utilizar RFM12B
      // LOGLN(F("RFM12B selected."));
      digitalWrite(SelectSlave_ETH, HIGH);
      digitalWrite(ChipSelect_SD, HIGH);
      digitalWrite(ChipSelect_RFM, LOW);
      delay(10);
      break;
  }
  return;
}
