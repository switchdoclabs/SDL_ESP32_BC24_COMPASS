SDL_ESP32_BC24_COMPASS<BR>
BC24 With the LSM303 Compass / Accelerometer<BR>
SwitchDoc Labs June 2018 <BR>
For the BC24 24 Pixel plus ESP32 Dual Core Processor with Grove Connectors

Version 005:   Initial Release June 4, 2018<BR>

Features:

- Uses the RMT peripherial on the ESP32 - No real CPU load for the Pixels
- Tracks Magnetic North with a Red LED
- Tracks the tilting of the platform with the remaining 23 Pixels.  Varies according to pitch, yaw and yaw.

In order to install the Arduino IDE with support for the ESP32 on the BC24, please follow the tutorial here:

http://www.switchdoc.com/2018/07/tutorial-arduino-ide-esp32-bc24/

Select the Adafruit ESP32 Feather under Tools

If you get a "\SDL_ESP32_BC24DEMO\SDL_ESP32_BC24DEMO.ino:69:21: fatal error: TimeLib.h: No such file or directory"

Go to this link github.com/PaulStoffregen/Time and download the .zip file. Then, in the IDE, go to Sketch>Include Library and click on Add .ZIP Library... In your file download area, you should be able to find the Time-Master.zip. Click on it and Open. It will install the Time.h required for the compilation of the sketch. Try to compile. If you get a repeat error, ,then close the IDE and restart it. Then re-compiling should work.

Plug a USB Micro to USB connector into your computer (the one with the power supply will work) to establish the connection.

Kickstarter is at:<BR>
http://bit.ly/SDBC24LAUNCH

Video:<BR>
https://youtu.be/-znht_LWEV8

All Libraries included in main directory

<img class="aligncenter size-large wp-image-29202" src="http://www.switchdoc.com/wp-content/uploads/2018/06/IMG_6069-1024x1015.jpg" alt="" width="930" height="922" />



