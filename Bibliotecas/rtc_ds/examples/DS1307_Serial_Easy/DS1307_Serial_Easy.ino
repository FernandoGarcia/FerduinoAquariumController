// DS1307_Serial_Easy (C)2010 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// A quick demo of how to use my DS1307-library to
// quickly send time and date information over a serial link

// Modified by Fernando Garcia to support Wire library only.

#include <rtc_ds.h>

// Init the DS1307
RTC_DS rtc;

void setup()
{
  // Set the clock to run-mode
  rtc.halt(false);

  // Setup Serial connection
  Serial.begin(9600);

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
  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");

  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());

  // Wait one second before repeating :)
  delay(1000);
}
