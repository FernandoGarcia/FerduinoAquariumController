/*
  DS1307.h - Arduino library support for the DS1307 I2C Real-Time Clock
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
#ifndef DS1307_h
#define DS1307_h

#if ARDUINO >= 100
#include "Arduino.h"       // for delayMicroseconds, digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif

// Uncomment only the line corresponding to your language.
// #define ENGLISH_L
// #define FRENCH_L
// #define GERMAN_L
// #define ITALIAN_L
#define PORTUGUESE_L
// #define SPANISH_L

#include "Week.h"

#define DS1307_ADDR_R	209
#define DS1307_ADDR_W	208

#define FORMAT_SHORT	1
#define FORMAT_LONG		2

#define FORMAT_LITTLEENDIAN	1
#define FORMAT_BIGENDIAN	2
#define FORMAT_MIDDLEENDIAN	3

#define SQW_RATE_1		0
#define SQW_RATE_4K		1
#define SQW_RATE_8K		2
#define SQW_RATE_32K	3

class Time
{
public:
	uint8_t		hour;
	uint8_t		min;
	uint8_t		sec;
	uint8_t		date;
	uint8_t		mon;
	uint16_t	year;
	uint8_t		dow;

		Time();
};

class DS1307_RAM
{
public:
	byte	cell[56];

		DS1307_RAM();
};

class DS1307
{
public:
		DS1307(uint8_t data_pin, uint8_t sclk_pin);
	Time	getTime();
	void	setTime(uint8_t hour, uint8_t min, uint8_t sec);
	void	setDate(uint8_t date, uint8_t mon, uint16_t year);
	void	setDOW(uint8_t dow);

	char	*getTimeStr(uint8_t format=FORMAT_LONG);
	char	*getDateStr(uint8_t slformat=FORMAT_LONG, uint8_t eformat=FORMAT_LITTLEENDIAN, char divider='.');
	char	*getDOWStr(uint8_t format=FORMAT_LONG);
	char	*getMonthStr(uint8_t format=FORMAT_LONG);

	void	halt(bool value);
	void	setOutput(bool enable);
	void	enableSQW(bool enable);
	void	setSQWRate(int rate);

	void		writeBuffer(DS1307_RAM r);
	DS1307_RAM	readBuffer();
	void		poke(uint8_t addr, uint8_t value);
	uint8_t		peek(uint8_t addr);
	unsigned long getTimeStamp();

private:
	uint8_t _scl_pin;
	uint8_t _sda_pin;
	uint8_t _burstArray[8];

	void	_sendStart(byte addr);
	void	_sendStop();
	void	_sendAck();
	void	_sendNack();
	void	_waitForAck();
	uint8_t	_readByte();
	void	_writeByte(uint8_t value);
	void	_burstRead();
	uint8_t	_readRegister(uint8_t reg);
	void 	_writeRegister(uint8_t reg, uint8_t value);
	uint8_t	_decode(uint8_t value);
	uint8_t	_decodeH(uint8_t value);
	uint8_t	_decodeY(uint8_t value);
	uint8_t	_encode(uint8_t vaule);
};
#endif
