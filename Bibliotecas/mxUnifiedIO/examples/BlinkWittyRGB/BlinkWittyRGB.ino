/*
 * mxUnifiedIO BlinkWittyRGB
 * 
 * mxUnifiedIO is a set of libraries that implement unified I/O 
 * on various I/O expanders.
 * 
 * This example demonstrates the use of the mxUnifiedIO library
 * on the Witty Cloud ESP8266 module featuring an ESP-12F and RGB LED.
 * 
 * The base class library is only an abstraction of the hardware pins.
 * Normally it is used in conjunction with the child library for
 * the specific I/O expander.
 * 
 * For more information read the documentation.
 * https://github.com/maxint-rd/mxUnifiedIO
 */
#include <mxUnifiedIO.h>            // include the base library

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

// Witty Cloud ESP-12F (4MB) has following hardware:
//  - RGB-LED on pins GPIO15, GPIO12 and GPIO13 (GPIO15 pulled low via 10K to GND, resulting in less bright RED)
//  - LDR on pin ADC0
//  - BUTTON on GPIO4;
//  - ESP blue-LED on GPIO2, active low  (is also TX of second UART, according to some this pin should be high on boot)
// On base board:
//  - Flash button on GPIO0
//  - Reset button on RST
//  - CH340G usb-to-serial
//
// Pins still available:
//  - GPIO5 (can be used for I2C SLC, needs pull-up, 4.7K recommended)
//  - GPIO14 (can be used for I2C SDA, needs pull-up, 4.7K recommended) 
//  - GPIO16 (can be tied to RST to enable wake-up) 
// Note: default pins for I2C are GPIO4 (SDA) and GPIO5 (SCL)
//
 
void WittyRGB()
{
  static int nPin=2;
  unio.digitalWrite(nPin, LOW);   // set expanded pin low
  if(nPin==2) nPin=3;
  else if(nPin==3) nPin=5;
  else if(nPin==5) nPin=2;
  unio.digitalWrite(nPin, HIGH);   // set expanded pin high
}

void setup()
{
  Serial.begin(115200);
  delay(100);   // wait for serial to settle (needed to skip ESP8266 startup info)
  Serial.println(F("\n mxUnifiedIO Blink"));

  unio.begin();     // start using the output expander
  // unio.begin(0x27);     // start using the PCF874 I2C output expander on address 0x27

}

void loop()
{
  Serial.print(F("."));
  WittyRGB();
  unio.digitalWrite(1, !unio.digitalRead(1));   // invert expanded pin
  delay(250);
  unio.digitalWrite(1, !unio.digitalRead(1));   // invert expanded pin
  delay(250);
}

