/*
 * mxUnifiedIO BlinkWittyRGB
 * 
 * mxUnifiedIO is a set of libraries that implement unified I/O 
 * on various I/O expanders.
 * 
 * This example demonstrates the use of the mxUnifiedIO library.
 * The base class library is only an abstraction of the hardware pins.
 * Normally it is used in conjunction with the child library for
 * the specific I/O expander.
 * 
 * For more information read the documentation.
 * https://github.com/maxint-rd/mxUnifiedIO
 */
#include <mxUnifiedIO.h>
mxUnifiedIO unio = mxUnifiedIO();   // create the object to access the expanded pins

/* This is the default hardware pin-mapping of the mxUnifiedIO base class:
#ifdef ESP8266
  _aPins[0]=0;
  _aPins[1]=2;    // ESP12 LED on pin 2 is active low
  _aPins[2]=12;
  _aPins[3]=13;
  _aPins[4]=14;
  _aPins[5]=15;
  _aPins[6]=4;
  _aPins[7]=5;
#else
  _aPins[0]=0;    // sometimes there is a LED on pin 0 (TX)
  _aPins[1]=11;
  _aPins[2]=12;
  _aPins[3]=13;   // most Arduino's have a LED on pin 13
  _aPins[4]=4;
  _aPins[5]=5;
  _aPins[6]=6;
  _aPins[7]=7;
#endif
 */
#define NUMPINS 8

void setup()
{
  Serial.begin(115200);
  Serial.println(F("mxUnifiedIO Blink8"));

  unio.begin();     // start using the mxUnifiedIO object
  for(int nPin=0; nPin<NUMPINS; nPin++)
    unio.digitalWrite(nPin, LOW);   // set expanded pin low
}

void loop()
{
  for(int nPin=0; nPin<NUMPINS; nPin++)
  {
    Serial.print(nPin);
    Serial.print(F(" "));
    unio.digitalWrite(nPin, HIGH);   // set expanded pin high
    delay(50);
    unio.digitalWrite(nPin, LOW);   // set expanded pin low
    delay(100);
  }
  Serial.println(F("."));
  delay(200);
}

