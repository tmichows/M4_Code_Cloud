/*
 * Project myProject
 * Author: Your Name
 * Date:
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

#include "neopixel.h"

#define PIXEL_PIN SPI1
#define PIXEL_COUNT 12
#define PIXEL_TYPE WS2812

Adafruit_NeoPixel ring(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int setNPColor(String colorName);

// setup() runs once, when the device is first turned on
void setup()
{
  // Put initialization like pinMode and begin functions here
  ring.begin();

  Particle.function("colorName", setNPColor);
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  // The core of your code will likely live here.

  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
  // Log.info("Sending Hello World to the cloud!");
  // Particle.publish("Hello world!");
  // delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!
}

int setNPColor(String colorName)
{

  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;

  if (colorName == "yellow")
  {
    red = 255;
    green = 255;
    blue = 0;
  }
  else if (colorName == "blue")
  {
    red = 0;
    green = 0;
    blue = 255;
  }
  else
  {
    red = 0;
    green = 0;
    blue = 0;
  }

  for (int i = 0; i < ring.numPixels(); i++)
  {
    ring.setPixelColor(i, red, green, blue);
    ring.setBrightness(80);
  }

  ring.show();
  return 0;
}