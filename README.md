# Ferduino Aquarium Controller ![Build status](https://github.com/FernandoGarcia/FerduinoAquariumController/actions/workflows/build.yml/badge.svg?event=push)

## About

This project is based on the [Arduino] platform.

This project started from the need to make partial water changes automatics in my 3 tanks.
After accomplishing what I wanted, the project has grown to the point it’s today.

The code was written based on version 2.1 of [Stilo].

All work was done thanks to the people who devote their time sharing their knowledge on forums.

Therefore, this is completely Open Source and always will be.

## Features

-   Temperature control for water;
-   PH control for calcium reactor;
-   PH monitor for tank;
-   ORP control;
-   Density monitor;
-   Auto top off;
-   Level monitor;
-   Partial water change automatic;
-   LED light control for 6 channels (5 day light + 1 moonlight);
-   Clouds and lightnings simulation;
-   Temperature control for LED;
-   Control for 5 timers;
-   Dosage control for up to 6 dosing pumps;
-   Control for DC pumps;
-   Graphs of parameters;
-   Web control, graphs, alerts by email and status in real time online;
-   Automatic feeder;
-   Graphic interface multilanguage.

## TFT touch screen interface

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=10&image_id=26">

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=10&image_id=28">

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=10&image_id=38">

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=10&image_id=27">

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=10&image_id=240">

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=10&image_id=451">

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=10&image_id=242">

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=10&image_id=241">

## Web interface

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=11&image_id=511">

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=11&image_id=512">

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=11&image_id=513">

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=11&image_id=514">

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=11&image_id=515">

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=11&image_id=516">

## Part list

[1 x Arduino mega 2560]

<img width="50%" src="http://arduino.cc/en/uploads/Main/ArduinoMega2560_R3_Fronte.jpg">

[1 x TFT touch screen with resolution 400 x 240]

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=11&image_id=749">

[1 X TFT shield]

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=11&image_id=616">

[1 x RTC DS3231 module without external EEPROM]

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=11&image_id=617">

[3 x Temperature sensor DS18B20]

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=11&image_id=524">

[1 x Relay board]

<img width="50%" src="https://ferduino.com/wp-content/uploads/2015/09/SSR-module-board-16-channels.jpg">

[Prototype shield] or [screw shield]

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=11&image_id=112">

<img width="50%" src="https://www.aqualed-light.com/wp-content/uploads/2018/09/Due_Mega_TFT_V4_001.jpg">

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=11&image_id=474">

1 x [Ethernet shield W5100],  [module] or [ESP8266]

<img width="50%" src="http://arduino.cc/en/uploads/Main/ArduinoEthernetShieldV3.jpg">

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=11&image_id=759">

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=11&image_id=489">

[6 x Float switch]

<img width="50%" src="https://ferduino.com/forum/gallery/image.php?album_id=11&image_id=53">

[6 x Dosing pump]

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=11&image_id=742">

[Circuits pH, ORP and EC]

<img src="https://ferduino.com/forum/gallery/image.php?album_id=11&image_id=54">

[1 x Multi circuit UART carrier board]

<img src="https://www.ferduino.com/forum/gallery/image.php?album_id=11&image_id=234">

[1 x PCF8575]

<img width="50%" src="https://www.ferduino.com/forum/gallery/image.php?album_id=11&image_id=685">

## Circuits

Please visit [this topic] to see circuits details.

## Assembly details

[TFT shield]

[Ethernet shield and module]

[Add WiFi with less than $5]

## Code installation

Please visit [this tutorial] to see how to install this code.

## Support

Please visit our [Forum] to get support.

## TODO

Energy monitor.

[stilo]: https://code.google.com/archive/p/stilo/downloads

[web control]: https://ferduino.com/webcontrol

[arduino]: http://arduino.cc

[forum]: https://ferduino.com/forum

[this topic]: https://ferduino.com/forum/viewtopic.php?f=24&t=40

[this tutorial]: https://ferduino.com/forum/viewtopic.php?f=8&t=34

[1 x arduino mega 2560]: http://www.ebay.com/sch/i.html?_odkw=arduino+mega+2560r3&LH_BIN=1&_osacat=0&_from=R40&_trksid=p2045573.m570.l1313.TR5.TRC2.A0.H0.Xarduino+mega+2560+r3&_nkw=arduino+mega+2560+r3&_sacat=0

[1 x tft touch screen with resolution 400 x 240]: https://goo.gl/Wtl9TL

[1 x tft shield]: https://www.elecfreaks.com/estore/lcd-tft01-arduino-mega-shield-v2-0-shd10.html

[1 x rtc ds3231 module without external eeprom]: https://goo.gl/weNRNj

[3 x temperature sensor ds18b20]: http://www.ebay.com/sch/i.html?_trksid=p2055845.m570.l1313.TR11.TRC1.A0.H0.Xds18b20&_nkw=ds18b20&_sacat=0&_from=R40

[1 x relay board]: https://ferduino.com/product/solid-state-relay-board-16-channels/

[prototype shield]: http://www.ebay.com/sch/i.html?_odkw=relay+board+arduino&LH_BIN=1&_sop=15&_osacat=0&_from=R40&_trksid=p2045573.m570.l1313.TR2.TRC1.A0.H0.Xprototype+shield+arduino+mega&_nkw=prototype+shield+arduino+mega&_sacat=0

[screw shield]: https://www.aqualed-light.com/en/produto/arduino-due-mega-screw-shield-with-tft-connector-and-rtc/

[ethernet shield w5100]: http://www.ebay.com/sch/i.html?_odkw=ethernet+shield+arduino&LH_BIN=1&_sop=15&_osacat=0&_from=R40&_trksid=p2045573.m570.l1313.TR2.TRC1.A0.H0.Xethernet+shield+arduino+mega+2560&_nkw=ethernet+shield+arduino+mega+2560&_sacat=0

[module]: http://www.ebay.com/sch/i.html?_odkw=ethernet+shield+module&LH_BIN=1&_sop=15&_osacat=0&_from=R40&_trksid=p2045573.m570.l1313.TR3.TRC2.A0.H0.Xethernet+module&_nkw=ethernet+module&_sacat=0

[esp8266]: https://goo.gl/wCq4uc

[6 x float switch]: http://www.ebay.com/sch/i.html?_trksid=p2055845.m570.l1311.R4.TR11.TRC1.A0.H0.Xfloat+sw&_nkw=float+switch+aquarium&_sacat=0&_from=R40

[6 x dosing pump]: http://www.ebay.com/sch/i.html?_odkw=dosing+pump&LH_BIN=1&_osacat=20754&_from=R40&_trksid=p2045573.m570.l1313.TR1.TRC0.A0.H0.Xdosing+pump+12v&_nkw=dosing+pump+12v&_sacat=20754

[circuits ph, orp and ec]: https://www.atlas-scientific.com/circuits.html?

[1 x multi circuit uart carrier board]: http://atlas-scientific.com/product_pages/components/multi_carrier.html?

[1 x pcf8575]: http://www.ebay.com/sch/i.html?_from=R40&_trksid=p2050601.m570.l1313.TR1.TRC0.A0.H0.Xpcf8575.TRS0&_nkw=pcf8575&_sacat=0

[tft shield]: https://www.ferduino.com/forum/viewtopic.php?f=24&t=488

[ethernet shield and module]: https://www.ferduino.com/forum/viewtopic.php?f=24&t=36

[add wifi with less than $5]: https://www.ferduino.com/forum/viewtopic.php?f=24&t=382
