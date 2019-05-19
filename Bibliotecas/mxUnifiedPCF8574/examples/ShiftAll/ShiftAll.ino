/*
 * mxUnifiedPCF8574
 * 
 * The mxUnifiedPCF8574 library supports both the PCF8574 8-bit I/O expander, as well as the similar PCF8575 16-bit I/O expander.
 * The PCF8574 is the same as the PCF8574A, except for the address range. 
 */
#include <mxUnifiedPCF8574.h>

//mxUnifiedPCF8575 unio = mxUnifiedPCF8575(0x20);     // use the PCF875 I2C output expander on address 0x20
mxUnifiedPCF8575 unio = mxUnifiedPCF8575(0x20, 2, 0);     // on ESP8266 you can also use software I2C, e.g. SDA=2, SDA=0. the ESP-01 has only 4 pins available. If you don't use serial, you can use 1 (TX) and 3 (RX)
//mxUnifiedPCF8574 unio = mxUnifiedPCF8574(0x27);     // use the PCF874 I2C output expander on address 0x27
//mxUnifiedPCF8574 unio = mxUnifiedPCF8574(0x27, 2, 0);     // on ESP8266 you can also use software I2C. the ESP-01 has only 4 pins available. If you don't use serial, you can use 1 (TX) and 3 (RX)

// Please note that the pins on the PCF8574/PCF8575 are intended to be used for data.
// They cannot deliver much current. When connecting LEDs to the pins, they
// may not light up very brightly.

// The LCD backpack module has for that specific reason a transistor to drive
// the LCD backlight LEDs. See the pinout of the module below

/*
PCF8574 I2C LCD driver
========================

Pin to chip interface
---------------------

     +---------------------+
-SCL-+   ::: +---+         |
-SCA-+   +-+ |PCF| ''': LED+-
-VCC-+   |*| |   |  ..- jmp+-
-GND-+   +-+ +---+         |
     +---------------------+
        1234567890123456
        ||||||||||||||||


Pinout
------

Pin Description
 1  GND
 2  VCC
 3  Contrast (adjustable VCC->Pot->Pin3)
 4  P0
 5  P1
 6  P2
 7  not connected
 8  not connected
 9  not connected
10  not connected
11  P4
12  P5
13  P6
14  P7
15  VCC (for LED)
16  P3 (connected via LED jumper to J3Y (=S8050) transistor, sink)
*/


void setup()
{
  Serial.begin(115200);
  Serial.print(F("mxUnified PCF8574/PCF8575 Blink "));
  Serial.print(unio.getNumPins());
  Serial.println(F(" pins"));

  unio.begin();            // start using the I/O expander
  //unio.begin(100000L);   // Optionally you can specify I2C speed
                           // For ESP default speed is 1MHz for ATmega it's 400KHz

  for(int nPin=0; nPin<unio.getNumPins(); nPin++)
    unio.digitalWrite(nPin, LOW);   // set expanded pin low
}

void loop()
{
  for(int nPin=0; nPin<unio.getNumPins(); nPin++)
  {
    Serial.print(nPin);
    Serial.print(F(" "));
    unio.digitalWrite(nPin, HIGH);   // set expanded pin high

    unio.startTransmission();
    unio.shiftOut(nPin, (nPin<unio.getNumPins()-1) ? nPin+1 : 0, MSBFIRST, 0xAA);   // shift some value out
    unio.endTransmission();
    delay(1);
    unio.startTransmission();
    unio.shiftOut(nPin, (nPin<unio.getNumPins()-1) ? nPin+1 : 0, MSBFIRST, 0x55);   // shift some value out
    unio.endTransmission();
    
    delay(50);
    unio.digitalWrite(nPin, LOW);   // set expanded pin low
    //delay(100);
  }
  Serial.println(F("."));
  delay(500);
}

