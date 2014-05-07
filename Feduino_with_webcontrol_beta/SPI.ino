void selecionar_SPI(int dispositivo)
{
  switch(dispositivo)
  {
  case 0: // Utilizar cartão sd.
    digitalWrite(ChipSelect_SD, LOW);
    digitalWrite(SelectSlave_ETH, HIGH);
    digitalWrite(ChipSelect_RFM, HIGH);
    break; 

  case 1: // Utilizar ethercard
    digitalWrite(SelectSlave_ETH, LOW);
    digitalWrite(ChipSelect_SD, HIGH);
    digitalWrite(ChipSelect_RFM, HIGH);
    break; 

  case 2: // Utilizar RFM12B
    digitalWrite(ChipSelect_RFM, LOW);
    digitalWrite(SelectSlave_ETH, HIGH);
    digitalWrite(ChipSelect_SD, HIGH);
    break; 
  }
  return;
}




