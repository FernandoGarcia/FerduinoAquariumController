// DS1307_Serial_Hard (C)2010 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// A quick demo of how to use my DS1307-library to
// retrieve time- and date-data for you to manipulate.

// Modified by Fernando Garcia to support Wire library only.

#include <rtc_ds.h>

// Init the DS1307
RTC_DS rtc;

// Init a Time-data structure
Time t;

void setup()
{
  // Set the clock to run-mode
  rtc.halt(false);

  // Setup Serial connection
  Serial.begin(38400);

  if (rtc.isPresent())
  {
    Serial.println("RTC found");
  }
  else
  {
    Serial.println("RTC not found");
  }

  if (rtc.isRunning())
  {
    Serial.println("RTC is running");
  }
  else
  {
    Serial.println("RTC is not running");
  }

  // The following lines can be commented out to use the values already stored in the DS1307
  rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(3, 10, 2010);  // Set the date to October 3th, 2010
}

void loop()
{
  // Get data from the DS1307
  t = rtc.getTime();

  // Send date over serial connection
  Serial.print("Today is the ");
  Serial.print(t.date, DEC);
  Serial.print(". day of ");
  Serial.print(rtc.getMonthStr());
  Serial.print(" in the year ");
  Serial.print(t.year, DEC);
  Serial.println(".");

  // Send Day-of-Week and time
  Serial.print("It is the ");
  Serial.print(t.dow, DEC);
  Serial.print(". day of the week (counting sunday as the 1th), and it has passed ");
  Serial.print(t.hour, DEC);
  Serial.print(" hour(s), ");
  Serial.print(t.min, DEC);
  Serial.print(" minute(s) and ");
  Serial.print(t.sec, DEC);
  Serial.println(" second(s) since midnight.");

  // Send a divider for readability
  Serial.println("  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -");

  // Wait one second before repeating :)
  delay (1000);
}
