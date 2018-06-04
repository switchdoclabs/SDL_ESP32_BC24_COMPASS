
// SDL_ESP32_BC24_COMPASS
// SwitchDoc Labs BC24 Pixel ESP32 Board plus LSM303 Compass and accelerometer
// June 2018
//
//

#define BC24COMPASSSOFTWAREVERSION "005"
#undef BC24DEBUG



#define BUTTONPIN 17

#define BLINKPIN 13


#include <Wire.h>

#include "M_LSM303.h"

LSM303 compass;

#include "utility.h"

#include "BigCircleFunctions.h"

/* Global variables */

float heading;

#define SPI_CS 10

void setup()
{
  char rtn = 0;
  Serial.begin(115200);  // Serial is used for debugging

  pinMode(BLINKPIN, OUTPUT);

  Serial.println();
  Serial.println();
  Serial.println("--------------------");
  Serial.println("BC24 Compass/Acceleromter Software");
  Serial.println("--------------------");
  Serial.print("Version: ");
  Serial.println(BC24COMPASSSOFTWAREVERSION);

  Serial.print("Compiled at:");
  Serial.print (__TIME__);
  Serial.print(" ");
  Serial.println(__DATE__);

  Serial.println("\r\npower on");
  Serial.begin(115200);
  Wire.begin();

  compass.init();
  compass.enableDefault();

  /*
    Calibration values; the default values of +/-32767 for each axis
    lead to an assumed magnetometer bias of 0. Use the Calibrate example
    program to determine appropriate values for your particular unit.
  */
  compass.m_min = (LSM303::vector<int16_t>) {
    -32767, -32767, -32767
  };
  compass.m_max = (LSM303::vector<int16_t>) {
    +32767, +32767, +32767
  };
  // Free heap on ESP32
  Serial.print("Free Heap Space on BC24:");
  Serial.println(ESP.getFreeHeap());

#ifdef BC24DEBUG
  Serial.print("CPU0 reset reason: ");
  print_reset_reason(rtc_get_reset_reason(0));

  Serial.print("CPU1 reset reason: ");
  print_reset_reason(rtc_get_reset_reason(1));
#endif

  // initalize our friend the BC24!
  //BC24inititialzeCircle();

  dumpSysInfo();
  getMaxMalloc(1 * 1024, 16 * 1024 * 1024);

  if (digitalLeds_initStrands(STRANDS, STRANDCNT)) {
    Serial.println("Init FAILURE: halting");
    while (true) {};
  }
  for (int i = 0; i < STRANDCNT; i++) {
    strand_t * pStrand = &STRANDS[i];
    Serial.print("Strand ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.print((uint32_t)(pStrand->pixels), HEX);
    Serial.println();
#if DEBUG_ESP32_DIGITAL_LED_LIB
    dumpDebugBuffer(-2, digitalLeds_debugBuffer);
#endif
    digitalLeds_resetPixels(pStrand);
#if DEBUG_ESP32_DIGITAL_LED_LIB
    dumpDebugBuffer(-1, digitalLeds_debugBuffer);
#endif
  }
  Serial.println("Init complete");


  Serial.print("RAM left: ");
  Serial.println(system_get_free_heap_size());

  blinkLED(2, 300);  // blink twice - OK!
  // set up BC24
  BC24BottomFiveBlink(Red, 1000);

}

long loopCount = 0;

void loop()
{



  compass.read();
  heading = compass.heading();

  // adjust for positioning
  heading = heading - 90.0;
  if (heading < 0)
    heading = heading + 360;

  if ((loopCount % 1000) == 0)
    printValues();

  loopCount++;


  // now do BC24
  displayCompassAndAccelerometer(heading, compass.a.x, compass.a.y, compass.a.z);

  delay(100);  // delay for serial readability
}

void printValues()
{
  char report[80];
  Serial.println("\r\n**************");
  Serial.print("heading=");
  Serial.println(heading);
  snprintf(report, sizeof(report), "A: %6d %6d %6d    M: %6d %6d %6d",
           compass.a.x, compass.a.y, compass.a.z,
           compass.m.x, compass.m.y, compass.m.z);
  Serial.println(report);

}
