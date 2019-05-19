# mxUnifiedPCF8574 / mxUnifiedPCF8575
mxUnifiedIO child library for Arduino. Use device specific drivers with PCF8574/PCF8575 I2C I/O expanders using a unified API.

This library (Arduino IDE version 1.6 and higher) is a child library of the [mxUnifiedIO](https://github.com/maxint-rd/mxUnifiedIO) library. It provides a unified API to drive PCF8574, PCF8574A and PCF8575 I2C I/O expanders via the dedicated I2C SDA/SCL or (on ESP826) using selected pins. 

By using this library, setting a pin of the shift-register is as easy as calling Arduino's digitalWrite().
The library implements shiftOut() to allow device specific drivers using the expanded pins of the I/O expander to be used as easy as those on the MCU.

# Connections and Pinout
- This library supports both the 8-bit PCF8574/PCF8574A and the 16-bit PCF8575 I2C I/O expanders. See [documentation](./documentation) for manufacturer datasheets. See below for pinout of LCD backpack module featuring the PCF8574.
- The mxUnifiedPCF8574 and mxUnifiedPCF8575 constructors only require the I2C address when using hardware SPI.
- On the Arduino Uno, Nano and Pro Mini, the hardware I2C pins are SDA=A4 and SCL=A5.
- On the ESP8266 the default pins for I2C are GPIO4 and GPIO5.
- On ESP8266 you can also use alternative I2C pins.
- The ESP-01 has only 4 pins available. If you dont use serial you can use 1 (TX) and 3 (RX) for I2C.
```C++
mxUnifiedPCF8574 unio = mxUnifiedPCF8574(0x27);     // use the PCF874 I2C 8-bit output expander on address 0x27
//mxUnifiedPCF8574 unio = mxUnifiedPCF8574(0x27, 2, 0);     // on ESP8266 you can also use alternative I2C pins. Here SDA=2 and SCL=0
//mxUnifiedPCF8575 unio = mxUnifiedPCF8575(0x20);     // use the PCF875 I2C 16-bit output expander on address 0x20
```

Please note that the pins on the PCF8574 and PCF8575 are intended to be used for data. They cannot deliver much current. When connecting LEDs to the pins, they may not light up very brightly.

The LCD backpack module features a PCF8574 chip. To drive the  LCD backlight LEDs with sufficient current, it uses a transistor. See the pinout of the module below:

```
PCF8574 I2C LCD driver backpack module pinout

     +---------------------+
-SCL-+   ::: +---+         |
-SCA-+   +-+ |PCF| ''': LED+-
-VCC-+   |*| |   |  ..- jmp+-
-GND-+   +-+ +---+         |
     +---------------------+
        1234567890123456
        ||||||||||||||||

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
```

# Troubleshooting tips
- Install both this library as the required parent library (download from https://github.com/maxint-rd/mxUnifiedIO)
- Use an I2C scanner sketch to see if the I2C device is properly connected and responding (see link below).
- Check if all data-pins between MCU, interface modules and devices are properly connected, according the pins as defined in your sketch.
- Use a multimeter to check pin voltages. Note: most PCF8574/PCF8575 modules are both 3.3V and 5V complient. However, some modules may need specific voltages. You may want to use a level-shifter to convert voltages.

# For reference
- Arduino I2C scanner sketches:
    * https://playground.arduino.cc/Main/I2cScanner
- Rob Tillaarts PCF8574 library:
    * https://github.com/RobTillaart/Arduino/tree/master/libraries/PCF8574
    * https://playground.arduino.cc/Main/PCF8574Class

# Features & limitations
- The current version of this library supports ESP8266 and Atmel ATmega328 and ATmega168 (tested Pro Mini's running at 8MHz/3v3). Other Atmel processors may work too, but they've not been tested yet. For some MCUs the library will require modification. Please let me know if you've successfully used this library with other MCUs.
- The PCF8574 and PCF8575 have certain input posibilities which are supported by this library. The library provides no specific support for the interrupt pin INT of the PCF8574/8575 chip.
- Using pinMode(pin, OUTPUT) a pin can be set to output mode. digitalWrite() and shiftOut() are used to set the output pins.
- Using pinMode(pin, INPUT) a pin can be set to input mode. digitalRead() can be used to query the current status of an input pin. pulseIn() can be used to measure the time (in microseconds) a pin changed to a specfic level.
- Using digitalRead() on an input pin will briefly set the pin HIGH prior to reading the current state. When digitalRead() is used for an output pin it returns the last state that was set.
- For faster digitalRead() and higher accuracy of pulseIn() you can set the input pin HIGH first.
- Input pins support dual mode. In dual mode the pin can be used as both input and output pin, eg. for a toggle led with a button. Such toggle led should be connected between VCC and pin, whereas the button is connected between GND and pin. digitalWrite() can be used to set the pin LOW and it is only briefly set high when reading the input state.
- Using shiftOut() requires startTransaction() and endTransaction().
- Using digitalWrite() to change one expanded pin requires sending multiple bits to the I/O expander using the serial I2C protocol (both addressing information plus the data byte - even two bytes when using the PCF8575). Therefor the maximum speed that can be achieved is much lower than using direct MCU pins.
- Best speeds can be obtained by by using a fast MCU. The ESP8266 has a higher clock-speed than an ATmega328.
- shiftOUt() can be used as software SPI on expanded pins, where you can choose which pin to use for MOSI and SCK. Please note that shifting one byte out requires 16 changes of the clock pin (even four bytes when using the PCF8575), so this is much slower than using direct MCU pins. However, the Nokia LCD examples show that the results can still be quite usable. See https://github.com/maxint-rd/mxUnifiedPCD8544_Nokia_5110_LCD for more info and the specific examples.

# Disclaimer
- All code on this GitHub account, including this library is provided to you on an as-is basis without guarantees and with all liability dismissed. It may be used at your own risk. Unfortunately I have no means to provide support.

