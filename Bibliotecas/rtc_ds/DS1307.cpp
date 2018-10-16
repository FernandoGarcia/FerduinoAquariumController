/*
   DS1307.cpp - Arduino library support for the DS1307 I2C Real-Time Clock
   Copyright (C)2010 Henning Karlsen. All right reserved

   You can find the latest version of the library at
   http://www.henningkarlsen.com/electronics

   This library has been made to easily interface and use the DS1307 RTC with
   the Arduino without needing the Wire library.

   If you make any modifications or improvements to the code, I would appreciate
   that you share the code with me so that I might include it in the next release.
   I can be contacted through http://www.henningkarlsen.com/electronics/contact.php

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

   Version:   1.0  - Oct   4 2010  - initial release

 */

 // Modified by Fernando Garcia to support Wire library only.

#if ARDUINO >= 100
 #include "Arduino.h"      // for delayMicroseconds, digitalPinToBitMask, etc
#else
 #include "WProgram.h"     // for delayMicroseconds
 #include "pins_arduino.h" // for digitalPinToBitMask, etc
#endif
#include "rtc_ds.h"
#include "Translation.h"
#include <Wire.h>

#define REG_SEC   0
#define REG_MIN   1
#define REG_HOUR  2
#define REG_DOW   3
#define REG_DATE  4
#define REG_MON   5
#define REG_YEAR  6
#define REG_CON   7

/* Public */

RTC_DS::RTC_DS()
{
  Wire.begin();
}

uint8_t RTC_DS::isPresent(void)
{
  Wire.begin();
  Wire.beginTransmission(DS_ADDR_W);
  Wire.write(0);

  if(Wire.endTransmission() == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }

}

uint8_t RTC_DS::isRunning(void)
{
  Wire.beginTransmission(DS_ADDR_W);
  Wire.write(0);
  Wire.endTransmission();

  Wire.requestFrom(DS_ADDR_W, 1);
  uint8_t ss = Wire.read();
  return !(ss >> 7);
}

Time::Time()
{
  this->year = 2010;
  this->mon  = 1;
  this->date = 1;
  this->hour = 0;
  this->min  = 0;
  this->sec  = 0;
  this->dow  = 5;
}

RTC_DS_RAM::RTC_DS_RAM()
{
  for (int i = 0; i < 56; i++)
  {
    cell[i] = 0;
  }
}


Time RTC_DS::getTime()
{
  Time t;

  Wire.beginTransmission(DS_ADDR_W);
  Wire.write(0);

  Wire.endTransmission();

  Wire.requestFrom(DS_ADDR_W, 8);

  for (int i = 0; i < 8; i++)
  {
    _burstArray[i] = Wire.read();
  }
  Wire.endTransmission();

  t.sec = _decode(_burstArray[0]);
  t.min = _decode(_burstArray[1]);
  t.hour  = _decodeH(_burstArray[2]);
  t.dow = _burstArray[3];
  t.date  = _decode(_burstArray[4]);
  t.mon = _decode(_burstArray[5]);
  t.year  = _decodeY(_burstArray[6]) + 2000;
  return t;
}

void RTC_DS::setTime(uint8_t hour, uint8_t min, uint8_t sec)
{
  if (((hour >= 0) && (hour < 24)) && ((min >= 0) && (min < 60)) && ((sec >= 0) && (sec < 60)))
  {
    Wire.beginTransmission(DS_ADDR_W);
    Wire.write(REG_HOUR);
    Wire.write(_encode(hour));
    Wire.endTransmission();

    Wire.beginTransmission(DS_ADDR_W);
    Wire.write(REG_MIN);
    Wire.write(_encode(min));
    Wire.endTransmission();

    Wire.beginTransmission(DS_ADDR_W);
    Wire.write(REG_SEC);
    Wire.write(_encode(sec));
    Wire.endTransmission();
  }
}

void RTC_DS::setDate(uint8_t date, uint8_t mon, uint16_t year)
{
  if (((date > 0) && (date <= 31)) && ((mon > 0) && (mon <= 12)) && ((year >= 2000) && (year < 3000)))
  {
    date = validateDate(date, mon, year);
    date = validateDateForMonth(date, mon, year);

    year -= 2000;
    Wire.beginTransmission(DS_ADDR_W);
    Wire.write(REG_YEAR);
    Wire.write(_encode(year));
    Wire.endTransmission();

    Wire.beginTransmission(DS_ADDR_W);
    Wire.write(REG_MON);
    Wire.write(_encode(mon));
    Wire.endTransmission();

    Wire.beginTransmission(DS_ADDR_W);
    Wire.write(REG_DATE);
    Wire.write(_encode(date));
    Wire.endTransmission();

    uint8_t dow = _calcDOW(date, mon, year);

    Wire.beginTransmission(DS_ADDR_W);
    Wire.write(REG_DOW);
    Wire.write(_encode(dow));
    Wire.endTransmission();
  }
}

char *RTC_DS::getTimeStr(uint8_t format)
{
  static char output[9];
  char buf[3];

  Time t;
  t = getTime();

  if (t.hour < 10)
  {
    strcpy(output, "0");
    itoa(t.hour, buf, 10);
    strcat(output, buf);
  }
  else
  {
    itoa(t.hour, buf, 10);
    strcpy(output, buf);
  }

  strcat(output, ":");

  if (t.min < 10)
  {
    strcat(output, "0");
  }

  itoa(t.min, buf, 10);
  strcat(output, buf);


  if (format == FORMAT_LONG)
  {
    strcat(output, ":");

    if (t.sec < 10)
    {
      strcat(output, "0");
    }

    itoa(t.sec, buf, 10);
    strcat(output, buf);
  }
  return output;
}

char *RTC_DS::getDateStr(uint8_t slformat, uint8_t eformat, char divider)
{
  static char output[11];
  char buf[5];
  char cc[2];

  cc[0] = divider;
  cc[1] = '\0';

  int yr;
  Time t;
  t = getTime();
  switch (eformat)
  {
    case FORMAT_LITTLEENDIAN:
      {
        if (t.date < 10)
        {
          strcpy(output, "0");
          itoa(t.date, buf, 10);
          strcat(output, buf);
        }
        else
        {
          itoa(t.date, buf, 10);
          strcpy(output, buf);
        }

        strcat(output, cc); // Append divider

        if (t.mon < 10)
        {
          strcat(output, "0");
        }

        itoa(t.mon, buf, 10);
        strcat(output, buf);

        strcat(output, cc);  // Append divider

        if (slformat == FORMAT_SHORT)
        {
          yr = t.year - 2000;
          if (yr < 10)
          {
            strcat(output, "0");
          }

          itoa(yr, buf, 10);
          strcat(output, buf);
        }
        else
        {
          itoa(t.year, buf, 10);
          strcat(output, buf);
        }
      }
      break;
    case FORMAT_BIGENDIAN:
      {
        if (slformat == FORMAT_SHORT)
        {
          yr = t.year - 2000;

          if (yr < 10)
          {
            strcpy(output, "0");
            itoa(yr, buf, 10);
            strcat(output, buf);
          }
          else
          {
            itoa(yr, buf, 10);
            strcpy(output, buf);
          }
        }
        else
        {
          itoa(t.year, buf, 10);
          strcpy(output, buf);
        }

        strcat(output, cc); // Append divider

        if (t.mon < 10)
        {
          strcat(output, "0");
        }

        itoa(t.mon, buf, 10);
        strcat(output, buf);

        strcat(output, cc);  // Append divider

        if (t.date < 10)
        {
          strcat(output, "0");
        }

        itoa(t.date, buf, 10);
        strcat(output, buf);
      }
      break;
    case FORMAT_MIDDLEENDIAN:
      {
        if (t.mon < 10)
        {
          strcpy(output, "0");
          itoa(t.mon, buf, 10);
          strcat(output, buf);
        }
        else
        {
          itoa(t.mon, buf, 10);
          strcpy(output, buf);
        }

        strcat(output, cc); // Append divider

        if (t.date < 10)
        {
          strcat(output, "0");
        }

        itoa(t.date, buf, 10);
        strcat(output, buf);

        strcat(output, cc); // Append divider

        if (slformat == FORMAT_SHORT)
        {
          yr = t.year - 2000;

          if (yr < 10)
          {
            strcat(output, "0");
          }

          itoa(yr, buf, 10);
          strcat(output, buf);
        }
        else
        {
          itoa(t.year, buf, 10);
          strcat(output, buf);
        }
      }
      break;
  }
  return output;
}

char *RTC_DS::getDOWStr(uint8_t format)
{
  static char buffer[15];
  Time t;
  t = getTime();

  if (format == FORMAT_SHORT)
  {
    strcpy_P(buffer, (PGM_P)pgm_read_word(&(dayOfWeekShortTable[t.dow])));
  }
  else
  {
    strcpy_P(buffer, (PGM_P)pgm_read_word(&(dayOfWeekTable[t.dow])));
  }
  return buffer;
}

char *RTC_DS::getMonthStr(uint8_t format)
{
  static char buffer[15];
  Time t;
  t = getTime();


  if (format == FORMAT_SHORT)
  {
    strcpy_P(buffer, (PGM_P)pgm_read_word(&(monthShortTable[t.mon])));
  }
  else
  {
    strcpy_P(buffer, (PGM_P)pgm_read_word(&(monthTable[t.mon])));
  }
  return buffer;
}

unsigned long RTC_DS::getTimeStamp()
{
  unsigned long time = 0;
  byte daysPerMonth[12] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  Time t;
  t = getTime();

  time = 365 * (t.year - 1970) * 86400UL;

  for(uint16_t i = 1970; i < t.year; i++)
  {
    if((i % 4) == 0)
    {
      time += 86400UL;
    }
  }

  for(uint8_t i = 0; i < t.mon - 1; i++)
  {
    time += daysPerMonth[i] * 86400UL;
  }
  if(t.mon > 2)
  {
    if(t.year % 4 == 0)
    {
      time += 29 * 86400UL;
    }
    else
    {
      time += 28 * 86400UL;
    }
  }
  time += (t.date - 1) * 86400UL;

  time += (t.hour * 3600UL);

  time += (t.min * 60UL);

  return time + t.sec;
}

void RTC_DS::halt(bool enable)
{
  Wire.beginTransmission(DS_ADDR_W);
  Wire.write(REG_SEC);

  Wire.requestFrom(DS_ADDR_W, 1);

  uint8_t _reg = Wire.read();
  Wire.endTransmission();

  _reg &= ~(1 << 7);
  _reg |= (enable << 7);

  Wire.beginTransmission(DS_ADDR_W);
  Wire.write(REG_SEC);
  Wire.write(_reg);
  Wire.endTransmission();
}

void RTC_DS::setOutput(bool enable)
{
  Wire.beginTransmission(DS_ADDR_W);
  Wire.write(REG_CON);

  Wire.requestFrom(DS_ADDR_W, 1);

  uint8_t _reg = Wire.read();
  Wire.endTransmission();

  _reg &= ~(1 << 7);
  _reg |= (enable << 7);

  Wire.beginTransmission(DS_ADDR_W);
  Wire.write(REG_CON);
  Wire.write(_reg);
  Wire.endTransmission();
}

void RTC_DS::enableSQW(bool enable)
{
  Wire.beginTransmission(DS_ADDR_W);
  Wire.write(REG_CON);

  Wire.requestFrom(DS_ADDR_W, 1);

  uint8_t _reg = Wire.read();
  Wire.endTransmission();

  _reg &= ~(1 << 4);
  _reg |= (enable << 4);

  Wire.beginTransmission(DS_ADDR_W);
  Wire.write(REG_CON);
  Wire.write(_reg);
  Wire.endTransmission();
}

void RTC_DS::setSQWRate(int rate)
{
  Wire.beginTransmission(DS_ADDR_W);
  Wire.write(REG_CON);

  Wire.requestFrom(DS_ADDR_W, 1);

  uint8_t _reg = Wire.read();
  Wire.endTransmission();

  _reg &= ~(3);
  _reg |= (rate);

  Wire.beginTransmission(DS_ADDR_W);
  Wire.write(REG_CON);
  Wire.write(_reg);
  Wire.endTransmission();
}

void RTC_DS::writeBuffer(RTC_DS_RAM r)
{
  Wire.beginTransmission(DS_ADDR_W);
  Wire.write(8);

  for (int i = 0; i < 30; i++)
  {
    Wire.write(r.cell[i]);
  }

  Wire.endTransmission();

  Wire.beginTransmission(DS_ADDR_W);
  Wire.write(38);

  for (int i = 30; i < 56; i++)
  {
    Wire.write(r.cell[i]);
  }

  Wire.endTransmission();
}

RTC_DS_RAM RTC_DS::readBuffer()
{
  RTC_DS_RAM r;

  Wire.beginTransmission(DS_ADDR_W);
  Wire.write(8);

  Wire.endTransmission();

  Wire.requestFrom(DS_ADDR_W, 32);

  for (int i = 0; i < 32; i++)
  {
    r.cell[i] = Wire.read();
  }
  Wire.endTransmission();

  Wire.beginTransmission(DS_ADDR_W);
  Wire.write(40);

  Wire.endTransmission();

  Wire.requestFrom(DS_ADDR_W, 32);

  for (int i = 32; i < 56; i++)
  {
    r.cell[i] = Wire.read();
  }
  Wire.endTransmission();

  return r;
}

uint8_t RTC_DS::poke(uint8_t addr, uint8_t value)
{
  if ((addr >= 0) && (addr <= 55))
  {
    addr += 8;

    Wire.beginTransmission(DS_ADDR_W);
    Wire.write(addr);
    Wire.write(value);

    if(Wire.endTransmission() == 0)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

uint8_t RTC_DS::peek(uint8_t addr)
{
  if ((addr >= 0) && (addr <= 55))
  {
    uint8_t readValue;

    addr += 8;

    Wire.beginTransmission(DS_ADDR_W);
    Wire.write(addr);

    Wire.requestFrom(DS_ADDR_W, 1);

    readValue = Wire.read();
    Wire.endTransmission();

    return readValue;
  }
  else
  {
    return 0;
  }
}

uint8_t RTC_DS::validateDateForMonth(byte d, byte m, word y)
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

uint8_t RTC_DS::validateDate(byte d, byte m, word y)
{
  byte mArr[12] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  byte od;

  if (m == 2)
  {
    if ((y % 4) == 0)
    {
      if (d == 30)
      {
        od = 1;
      }
      else if (d == 0)
      {
        od = 29;
      }
      else
      {
        od = d;
      }
    }
    else
    {
      if (d == 29)
      {
        od = 1;
      }
      else if (d == 0)
      {
        od = 28;
      }
      else
      {
        od = d;
      }
    }
  }
  else
  {
    if (d == 0)
    {
      od = mArr[m - 1];
    }
    else if (d == (mArr[m - 1] + 1))
    {
      od = 1;
    }
    else
    {
      od = d;
    }
  }

  return od;
}

/* Private */

uint8_t RTC_DS::_decode(uint8_t value)
{
  uint8_t decoded = value & 127;
  decoded = (decoded & 15) + 10 * ((decoded & (15 << 4)) >> 4);
  return decoded;
}

uint8_t RTC_DS::_decodeH(uint8_t value)
{
  if (value & 128)
  {
    value = (value & 15) + (12 * ((value & 32) >> 5));
  }
  else
  {
    value = (value & 15) + (10 * ((value & 48) >> 4));
  }
  return value;
}

uint8_t RTC_DS::_decodeY(uint8_t value)
{
  uint8_t decoded = (value & 15) + 10 * ((value & (15 << 4)) >> 4);
  return decoded;
}

uint8_t RTC_DS::_encode(uint8_t value)
{
  uint8_t encoded = ((value / 10) << 4) + (value % 10);
  return encoded;
}

uint8_t RTC_DS::_calcDOW(byte d, byte m, int y)
{
  int dow;
  byte mArr[12] = {6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

  dow = (y % 100);
  dow = dow * 1.25;
  dow += d;
  dow += mArr[m - 1];
  if (((y % 4) == 0) && (m < 3))
  {
    dow -= 1;
  }
  while (dow > 7)
  {
    dow -= 7;
  }
  if(dow < 7)
  {
    dow += 1;
  }
  else
  {
    dow = 1;
  }
  return dow;
}
