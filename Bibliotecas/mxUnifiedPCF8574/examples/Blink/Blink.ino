#include <mxUnifiedPCF8574.h>

// The mxUnifiedPCF8574 constructor only requires the I2C address when using hardware SPI.
// On the Arduino Uno, Nano and Pro Mini, the hardware I2C pins are SDA=A4 and SCL=A5.
// On the ESP8266 the default pins for I2C are GPIO4 and GPIO5.
// On ESP8266 you can also use alternative I2C pins.
// The ESP-01 has only 4 pins available. If you dont use serial you can use 1 (TX) and 3 (RX) for I2C.
mxUnifiedPCF8574 unio = mxUnifiedPCF8574(0x27);     // use the PCF874 I2C output expander on address 0x27
//mxUnifiedPCF8574 unio = mxUnifiedPCF8574(0x27, 2, 0);     // on ESP8266 you can also use alternative I2C pins. Here SDA=2 and SCL=0

// Please note that the pins on the PCF8574 are intended to be used for data.
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
  Serial.println(F("mxUnifiedPCF8574 Blink"));

  unio.begin();            // start using the I/O expander
  //unio.begin(100000L);   // Optionally you can specify I2C speed
                           // For ESP default speed is 1MHz for ATmega it's 400KHz
}

void loop()
{
  Serial.print(F("."));
  unio.digitalWrite(3, HIGH);   // set expanded pin 3 high
  delay(250);
  unio.digitalWrite(3, LOW);   // set expanded pin 3 low
  delay(250);
}

