#include "mxUnifiedIO.h"

mxUnifiedIO::mxUnifiedIO(void)
{
	_nConstr=1;
#if defined(MXUNIFIED_ATTINY) && (MXUNIFIED_ATTINY==13 || MXUNIFIED_ATTINY==85)
	_nNumPins=5;
#else
	_nNumPins=8;
#endif
	_dataOut=0;

	// Set default MCU pins
	// Can be redfined using mxUnifiedIO::specifyPins(uint8_t *arrPins)
	// The standard pin definition allows the following devices connected as example
	// ATmega328, PCD8544+Max7219 panel:
	//  P3;  D13 - led
	//  P2:  D3 - RST
	//  P4:  D4 - CE
	//  P5:  D5 - DC
	//  P6:  D6 - DIN
	//  P7:  D7 - CLK	
	
	//  P0:  D10 - CS  (SS)
	//  P1:  D11 - DIN (MOSI)
	//       D12 - not connected (MISO)
	//  P3:  D13 - CLK (SCK)
#ifdef ESP8266
	_aPins[0]=0;
	_aPins[1]=2;    // ESP12 LED on pin 2 is active low
	_aPins[2]=12;
	_aPins[3]=13;
	_aPins[4]=14;
	_aPins[5]=15;
	_aPins[6]=4;
	_aPins[7]=5;
#elif defined(MXUNIFIED_ATTINY)
	_aPins[0]=0;
	_aPins[1]=1;
	_aPins[2]=2;
	_aPins[3]=3;
	_aPins[4]=4;
	_aPins[5]=5;
	_aPins[6]=6;
	_aPins[7]=7;
#else
	_aPins[0]=10;
	_aPins[1]=11;
	_aPins[2]=12;
	_aPins[3]=13;
	_aPins[4]=4;
	_aPins[5]=5;
	_aPins[6]=6;
	_aPins[7]=7;
#endif
}

void mxUnifiedIO::specifyPins(uint8_t *arrPins)
{	// use these specific MCU pins to map to virtual expanded pins
	for(uint8_t n=0; n<_nNumPins; n++)
		_aPins[n]=arrPins[n];
}

void mxUnifiedIO::begin(uint8_t nPinSelection)		// uint8_t nPinSelection=MXUNIFIED_DEFAULT_PINS
{	// Overwrite in subclasses if desired!
	// Call without parameters assumes using the default pins.
	// For the base mxUnifiedIO class the default pins are tied directly to the MCU pins

	if(nPinSelection==MXUNIFIED_PINS_2TO9 || nPinSelection==MXUNIFIED_PINS_2TO9_13)
		for(uint8_t n=0; n<=7; n++)
			_aPins[n]=2+n;
	if(nPinSelection==MXUNIFIED_PINS_2TO9_13)
			_aPins[1]=13;
		
	for(uint8_t n=0; n<_nNumPins; n++)
		::pinMode(_aPins[n], OUTPUT);

#if(_MXUNIFIEDIO_DEBUG)
  Serial.print(F("mxUnifiedIO::begin("));
  //Serial.print(uI2C_address);
  Serial.print(F(") constr:"));
  Serial.print(_nConstr);
  Serial.print(F(", pins:"));
  Serial.print(_nNumPins);
  Serial.println(F("."));
#endif
}

uint8_t mxUnifiedIO::getNumPins(void)
{		// get the number of pins that are expanded
	return(_nNumPins);
}


void mxUnifiedIO::setBit(uint8_t nPin, uint8_t nValue)
{	// set the status of a pin (without actually writing it or ending the transmission yet)
	//uint8_t uDataOld=_dataOut;		// to return dirty flag when changed
	if(nValue) _dataOut |= ((uint32_t)1 << nPin);			// cast is needed to avoid shifting to negative 32bit values
	else _dataOut &= ~((uint32_t)1 << nPin);
	//return(_dataOut!=uDataOld);
}

void mxUnifiedIO::set8Bits(uint8_t nValue)
{	// set bits 0-7 to the specified value (leave upper bits unaltered
	//_dataOut=nValue;
	_dataOut&=0xFFFFFF00;
	_dataOut|=nValue;
}


uint8_t mxUnifiedIO::getBit(uint8_t nPin)
{
	return((_dataOut & (uint32_t)1<<nPin)?HIGH:LOW);
}

uint8_t mxUnifiedIO::get8Bits(void)
{
	return((uint8_t)_dataOut);
}
	
void mxUnifiedIO::send8Bits(bool fClosedTransmission)		// default: fClosedTransmission=true
{    // Overwrite in subclasses if desired!
	uint8_t uByte=(uint8_t)_dataOut;
#if(_MXUNIFIEDIO_DEBUG)
  Serial.print(F("mxUnifiedIO::send8Bits("));
  Serial.print(_dataOut);
  Serial.print(F(", 0x"));
  Serial.print(uByte, HEX);
  Serial.println(F(")"));
#endif

	for(uint8_t n=0; n<=7; n++)
	{
		::digitalWrite(_aPins[n], uByte&0x01);
		uByte>>=1;
	}
}

void mxUnifiedIO::sendBits(void)
{    // Overwrite in subclasses if desired!
	send8Bits();
}

void mxUnifiedIO::shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value)
{    // Overwrite in subclasses if desired!
}


void mxUnifiedIO::startTransmission(void)
{    // Overwrite in subclasses if desired!
}

void mxUnifiedIO::endTransmission(void)
{    // Overwrite in subclasses if desired!
}

void mxUnifiedIO::digitalWrite(uint8_t nPin, uint8_t nVal)
{ // Overwrite in subclasses if desired!
#if(_MXUNIFIEDIO_DEBUG)
  Serial.print(F("mxUnifiedIO::digitalWrite("));
  Serial.print(nPin);
  Serial.print(F(","));
  Serial.print(nVal);
  Serial.println(F(")"));
#endif

	if (nPin >= _nNumPins) return;
	setBit(nPin, nVal);
	::digitalWrite(_aPins[nPin], nVal);		// call the regular digitalWrite using the global scope resolution operator
	// TODO: use MCU-specific pin manipulation to provide faster switching
}	

void mxUnifiedIO::digitalWrite8(uint8_t nVal)
{
	set8Bits(nVal);
	send8Bits();
}

int mxUnifiedIO::digitalRead(uint8_t nPin)
{
	if (nPin >= _nNumPins) return LOW;

#if(_MXUNIFIEDIO_DEBUG)
  Serial.print(F("mxUnifiedIO::digitalRead("));
  Serial.print(nPin);
  Serial.print(F(","));
  Serial.print(getBit(nPin));
  Serial.println(F(")"));
#endif
	return(getBit(nPin));
}
	
void mxUnifiedIO::pinMode(uint8_t nPin, uint8_t nMode)
{    // Overwrite in subclasses if desired!
	if (nPin >= _nNumPins) return;
	::pinMode(_aPins[nPin], nMode);		// call the regular pinMode using the global scope resolution operator
}

