byte validateDateForMonth(byte d, byte m, word y)
{
  byte mArr[12] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (m == 2)
  {
    if ((y % 4) == 0)
    {
      if (d > 29)
      {
        d = 29;
      }
    }
    else
    {
      if (d > 28)
      {
        d = 28;
      }
    }
  }
  else
  {
    if (d > mArr[m - 1])
    {
      d = mArr[m - 1];
    }
  }
  return d;
}

byte calcDOW(byte d, byte m, int y)
{
  int dow;
  byte mArr[12] = {6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

  dow = (y % 100);
  dow = dow * 1.25;
  dow += d;
  dow += mArr[m - 1];
  if (((y % 4) == 0) && (m < 3))
    dow -= 1;
  while (dow > 7)
    dow -= 7;

  return dow;
}

byte validateDate(byte d, byte m, word y)
{
  byte mArr[12] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  byte od;

  if (m == 2)
  {
    if ((y % 4) == 0)
    {
      if (d == 30)
        od = 1;
      else if (d == 0)
        od = 29;
      else
        od = d;
    }
    else
    {
      if (d == 29)
        od = 1;
      else if (d == 0)
        od = 28;
      else
        od = d;
    }
  }
  else
  {
    if (d == 0)
      od = mArr[m - 1];
    else if (d == (mArr[m - 1] + 1))
      od = 1;
    else
      od = d;
  }

  return od;
}
