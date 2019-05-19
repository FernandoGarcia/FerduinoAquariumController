#ifndef _MXUNIFIEDPCF8574_H
#define _MXUNIFIEDPCF8574_H

//#define _MXUNIFIEDIO_DEBUG 1

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
#endif
#include "mxUnifiedIO.h"
#include <Wire.h>

class mxUnifiedPCF8574 : public mxUnifiedIO
{
 public:
#if defined(ESP8266)
  mxUnifiedPCF8574(uint8_t uI2C_address, uint8_t nPinSDA = SDA, uint8_t nPinSCL = SCL);
#else
 	mxUnifiedPCF8574(uint8_t uI2C_address); // Constructor
#endif

#if(_MXUNIFIEDIO_DEBUG)
	void printDebug();
#endif

  // These are be overridden by this subclass to provide device-specific
  // optimized code.  Otherwise 'generic' versions are used.
#if defined(ESP8266)
  void begin(uint32_t i2c_speed=1000000L);
#else
  void begin(uint32_t i2c_speed=400000L);
#endif
  void send8Bits(bool fClosedTransmission=true);
  virtual void sendBits(void);
  void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value);
  void startTransmission(void);
  void endTransmission(void);
  
 	virtual void digitalWrite(uint8_t nPin, uint8_t nVal);

 	virtual void pinMode(uint8_t nPin, uint8_t nMode);
 	virtual int digitalRead(uint8_t nPin);
 	virtual uint32_t pulseIn(uint8_t nPin, uint8_t nLevel, uint32_t nTimeOut=500000);

 protected:
 	uint8_t _i2c_address;
	uint8_t receive8Bits();
	virtual void receiveBits();
	uint16_t _pinModes;			// store setup of pinmode one bit per pin 0=output, 1=input (being lazy use a 16 bit variable also used for PCF8575)
	uint16_t _dataIn;				// to store received data (TODO: storing is not really needed, can be optimized...)

 private:
 	uint8_t _i2c_error;
	uint32_t _i2c_speed;
 	uint8_t _i2c_sda;
 	uint8_t _i2c_scl;
};


class mxUnifiedPCF8575 : public mxUnifiedPCF8574
{
 public:
#if defined(ESP8266)
  mxUnifiedPCF8575(uint8_t uI2C_address, uint8_t nPinSDA = SDA, uint8_t nPinSCL = SCL) : mxUnifiedPCF8574(uI2C_address, nPinSDA, nPinSCL)
#else
 	mxUnifiedPCF8575(uint8_t uI2C_address) : mxUnifiedPCF8574(uI2C_address)
#endif
	{ // Constructor
		_nConstr++;		// Constructor counter only for debug purposes
		_nNumPins=16;
	};
	
  void send16Bits(bool fClosedTransmission=true);
  virtual void sendBits(void);

 protected:
	uint16_t receive16Bits();
	virtual void receiveBits();
};

#endif // _MXUNIFIEDPCF8574_H
