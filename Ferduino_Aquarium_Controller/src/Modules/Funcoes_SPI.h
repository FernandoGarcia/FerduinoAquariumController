void selecionar_SPI(int dispositivo)
{
  switch (dispositivo)
  {
  case 0:   // Utilizar cartão sd.
    //LOGLN(F("SD CARD selected."));
    myDigitalWrite(ChipSelect_SD, LOW);
    myDigitalWrite(SelectSlave_ETH, HIGH);
    myDigitalWrite(ChipSelect_RFM, HIGH);
    delay(10);
    break;

  case 1:   // Utilizar ethercard
  //LOGLN(F("Ethernet selected."));
    myDigitalWrite(SelectSlave_ETH, LOW);
    myDigitalWrite(ChipSelect_SD, HIGH);
    myDigitalWrite(ChipSelect_RFM, HIGH);
    delay(10);
    break;

  case 2:   // Utilizar RFM12B
    //LOGLN(F("RFM12B selected."));
    myDigitalWrite(ChipSelect_RFM, LOW);
    myDigitalWrite(SelectSlave_ETH, HIGH);
    myDigitalWrite(ChipSelect_SD, HIGH);
    delay(10);
    break;
  }
  return;
}
