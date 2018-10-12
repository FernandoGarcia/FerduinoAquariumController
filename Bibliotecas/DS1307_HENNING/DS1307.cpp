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
#if ARDUINO >= 100
 #include "Arduino.h"      // for delayMicroseconds, digitalPinToBitMask, etc
#else
 #include "WProgram.h"     // for delayMicroseconds
 #include "pins_arduino.h" // for digitalPinToBitMask, etc
#endif
#include "DS1307_HENNING.h"
#include "Translation.h"

#define REG_SEC   0
#define REG_MIN   1
#define REG_HOUR  2
#define REG_DOW   3
#define REG_DATE  4
#define REG_MON   5
#define REG_YEAR  6
#define REG_CON   7

/* Public */

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

DS1307_RAM::DS1307_RAM()
{
  for (int i = 0; i < 56; i++)
  {
    cell[i] = 0;
  }
}

DS1307::DS1307(uint8_t data_pin, uint8_t sclk_pin)
{
  _sda_pin = data_pin;
  _scl_pin = sclk_pin;

  pinMode(_scl_pin, OUTPUT);
}
Time DS1307::getTime()
{
  Time t;
  _burstRead();
  t.sec = _decode(_burstArray[0]);
  t.min = _decode(_burstArray[1]);
  t.hour  = _decodeH(_burstArray[2]);
  t.dow = _burstArray[3];
  t.date  = _decode(_burstArray[4]);
  t.mon = _decode(_burstArray[5]);
  t.year  = _decodeY(_burstArray[6]) + 2000;
  return t;
}

void DS1307::setTime(uint8_t hour, uint8_t min, uint8_t sec)
{
  if (((hour >= 0) && (hour < 24)) && ((min >= 0) && (min < 60)) && ((sec >= 0) && (sec < 60)))
  {
    _writeRegister(REG_HOUR, _encode(hour));
    _writeRegister(REG_MIN, _encode(min));
    _writeRegister(REG_SEC, _encode(sec));
  }
}

void DS1307::setDate(uint8_t date, uint8_t mon, uint16_t year)
{
  if (((date > 0) && (date <= 31)) && ((mon > 0) && (mon <= 12)) && ((year >= 2000) && (year < 3000)))
  {
    year -= 2000;
    _writeRegister(REG_YEAR, _encode(year));
    _writeRegister(REG_MON, _encode(mon));
    _writeRegister(REG_DATE, _encode(date));
  }
}

void DS1307::setDOW(uint8_t dow)
{
  if ((dow > 0) && (dow < 8))
  {
    _writeRegister(REG_DOW, dow);
  }
}

char *DS1307::getTimeStr(uint8_t format)
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

char *DS1307::getDateStr(uint8_t slformat, uint8_t eformat, char divider)
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

char *DS1307::getDOWStr(uint8_t format)
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

char *DS1307::getMonthStr(uint8_t format)
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

void DS1307::halt(bool enable)
{
  uint8_t _reg = _readRegister(REG_SEC);
  _reg &= ~(1 << 7);
  _reg |= (enable << 7);
  _writeRegister(REG_SEC, _reg);
}

void DS1307::setOutput(bool enable)
{
  uint8_t _reg = _readRegister(REG_CON);
  _reg &= ~(1 << 7);
  _reg |= (enable << 7);
  _writeRegister(REG_CON, _reg);
}


void DS1307::enableSQW(bool enable)
{
  uint8_t _reg = _readRegister(REG_CON);
  _reg &= ~(1 << 4);
  _reg |= (enable << 4);
  _writeRegister(REG_CON, _reg);
}

void DS1307::setSQWRate(int rate)
{
  uint8_t _reg = _readRegister(REG_CON);
  _reg &= ~(3);
  _reg |= (rate);
  _writeRegister(REG_CON, _reg);
}

/* Private */

void DS1307::_sendStart(byte addr)
{
  pinMode(_sda_pin, OUTPUT);
  digitalWrite(_sda_pin, HIGH);
  digitalWrite(_scl_pin, HIGH);
  digitalWrite(_sda_pin, LOW);
  digitalWrite(_scl_pin, LOW);
  shiftOut(_sda_pin, _scl_pin, MSBFIRST, addr);
}

void DS1307::_sendStop()
{
  pinMode(_sda_pin, OUTPUT);
  digitalWrite(_sda_pin, LOW);
  digitalWrite(_scl_pin, HIGH);
  digitalWrite(_sda_pin, HIGH);
  pinMode(_sda_pin, INPUT);
}

void DS1307::_sendNack()
{
  pinMode(_sda_pin, OUTPUT);
  digitalWrite(_scl_pin, LOW);
  digitalWrite(_sda_pin, HIGH);
  digitalWrite(_scl_pin, HIGH);
  digitalWrite(_scl_pin, LOW);
  pinMode(_sda_pin, INPUT);
}

void DS1307::_sendAck()
{
  pinMode(_sda_pin, OUTPUT);
  digitalWrite(_scl_pin, LOW);
  digitalWrite(_sda_pin, LOW);
  digitalWrite(_scl_pin, HIGH);
  digitalWrite(_scl_pin, LOW);
  pinMode(_sda_pin, INPUT);
}

void DS1307::_waitForAck()
{
  pinMode(_sda_pin, INPUT);
  digitalWrite(_scl_pin, HIGH);
  while (_sda_pin == LOW)
  {
  }
  digitalWrite(_scl_pin, LOW);
}

uint8_t DS1307::_readByte()
{
  pinMode(_sda_pin, INPUT);

  uint8_t value = 0;
  uint8_t currentBit = 0;

  for (int i = 0; i < 8; ++i)
  {
    digitalWrite(_scl_pin, HIGH);
    currentBit = digitalRead(_sda_pin);
    value |= (currentBit << (7 - i));
    delayMicroseconds(1);
    digitalWrite(_scl_pin, LOW);
  }
  return value;
}
void DS1307::_writeByte(uint8_t value)
{
  pinMode(_sda_pin, OUTPUT);
  shiftOut(_sda_pin, _scl_pin, MSBFIRST, value);
}

uint8_t DS1307::_readRegister(uint8_t reg)
{
  uint8_t readValue = 0;

  _sendStart(DS1307_ADDR_W);
  _waitForAck();
  _writeByte(reg);
  _waitForAck();
  _sendStop();
  _sendStart(DS1307_ADDR_R);
  _waitForAck();
  readValue = _readByte();
  _sendNack();
  _sendStop();
  return readValue;
}

void DS1307::_writeRegister(uint8_t reg, uint8_t value)
{
  _sendStart(DS1307_ADDR_W);
  _waitForAck();
  _writeByte(reg);
  _waitForAck();
  _writeByte(value);
  _waitForAck();
  _sendStop();
}

void DS1307::_burstRead()
{
  _sendStart(DS1307_ADDR_W);
  _waitForAck();
  _writeByte(0);
  _waitForAck();
  _sendStop();
  _sendStart(DS1307_ADDR_R);
  _waitForAck();

  for (int i = 0; i < 8; i++)
  {
    _burstArray[i] = _readByte();
    if (i < 7)
    {
      _sendAck();
    }
    else
    {
      _sendNack();
    }
  }
  _sendStop();
}

uint8_t DS1307::_decode(uint8_t value)
{
  uint8_t decoded = value & 127;
  decoded = (decoded & 15) + 10 * ((decoded & (15 << 4)) >> 4);
  return decoded;
}

uint8_t DS1307::_decodeH(uint8_t value)
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

uint8_t DS1307::_decodeY(uint8_t value)
{
  uint8_t decoded = (value & 15) + 10 * ((value & (15 << 4)) >> 4);
  return decoded;
}

uint8_t DS1307::_encode(uint8_t value)
{
  uint8_t encoded = ((value / 10) << 4) + (value % 10);
  return encoded;
}

void DS1307::writeBuffer(DS1307_RAM r)
{
  _sendStart(DS1307_ADDR_W);
  _waitForAck();
  _writeByte(8);
  _waitForAck();

  for (int i = 0; i < 56; i++)
  {
    _writeByte(r.cell[i]);
    _waitForAck();
  }

  _sendStop();
}

DS1307_RAM DS1307::readBuffer()
{
  DS1307_RAM r;

  _sendStart(DS1307_ADDR_W);
  _waitForAck();
  _writeByte(8);
  _waitForAck();
  _sendStop();
  _sendStart(DS1307_ADDR_R);
  _waitForAck();

  for (int i = 0; i < 56; i++)
  {
    r.cell[i] = _readByte();
    if (i < 55)
    {
      _sendAck();
    }
    else
    {
      _sendNack();
    }
  }
  _sendStop();

  return r;
}

void DS1307::poke(uint8_t addr, uint8_t value)
{
  if ((addr >= 0) && (addr <= 55))
  {
    addr += 8;
    _sendStart(DS1307_ADDR_W);
    _waitForAck();
    _writeByte(addr);
    _waitForAck();
    _writeByte(value);
    _waitForAck();
    _sendStop();
  }
}

uint8_t DS1307::peek(uint8_t addr)
{
  if ((addr >= 0) && (addr <= 55))
  {
    uint8_t readValue;

    addr += 8;
    _sendStart(DS1307_ADDR_W);
    _waitForAck();
    _writeByte(addr);
    _waitForAck();
    _sendStop();
    _sendStart(DS1307_ADDR_R);
    _waitForAck();
    readValue = _readByte();
    _sendNack();
    _sendStop();

    return readValue;
  }
  else
  {
    return 0;
  }
}

unsigned long DS1307::getTimeStamp()
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
