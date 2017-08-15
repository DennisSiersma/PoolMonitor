This is still very much a work in progress. Weather info based in part on great work by Daniel Eichorn's WeatherStation and further adaptation by Bodmer.

This copy has been adapted to be compatible with a ESP8266 feather Huzzah by Adafruit with a 2.4" TFT FeatherWing display interface. Adaptation as a Pool Monitor includes support for PH and ORP sensors by Atlas Scientific on a WhiteboxLab Tentacle shield and AS EZO 'stamps'.

Pool temperature is measured thru a OneWire DS18B20 and communication interface is build using the great Blynk functionality. 

This ReadMe file is not complete yet so some helpful information is missing, so bear this in mind if you want to try this sketch as it will need some Arduino project experience to get working!  edits to the settings.h file will be needed to set your location and to add the Weather Underground API key. You can get this API key by setting up a free account on the Weather Underground website.

The ESP8266 support core for the Arduino IDE must be loaded via the Boards Manager. Set the upload baud rate to a high value, the CPU clock rate to 160MHz and the SPIFFS size to 3Mbytes in the IDE. The large SPIFFS size is needed to hold the image and weather icon files that will be automatically downloaded from the internet.


#The following support ibraries are needed:

esp8266-weather-station via Library Manager or from this link:

https://github.com/squix78/esp8266-weather-station

JPEGDecoder via Library Manager or from this link:

https://github.com/Bodmer/JPEGDecoder

json-streaming-parser via Library Manager or from this link:

https://github.com/squix78/json-streaming-parser

TFT_ILI9341_ESP from this link:

https://github.com/Bodmer/TFT_ILI9341_ESP

WiFiManager via Library Manager or from this link:

https://github.com/tzapu/WiFiManager

Blynk via Library Manager or from this link:
https://github.com/blynkkk/blynk-library