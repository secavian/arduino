Arduino libraries by Ralf Thompson
--------------------------

This is a collection of basic libraries intended to make common (and some not so common) tasks easier to use.

Libraries include:

* Button:
  * Detect if push button is pressed
  * Use push button like switch (toggle, slide, etc)
* ByteConvertLib
  * Write float and integer types to byte arrays and back again
* I2CLib
  * Base class for I2C devices (BMP 180, BNO 055)
* Led
  * Simplifies turning led's on and off, including logical tests and toggling.
* VoltageDetect
  * Reads voltage present on analog pin


In addition, there are several not so basic libraries to support various devices.

Libraries include:

* BMP_180:
  * Library to asynchronously read temperature and pressure values from the Bosch BMP 180 barometeric sensor.
* BNO055
  * Library to asynchronously read values from the Bosch BNO 055 IMU sensor.
* GPS_MTK3339
  * Library to asynchronously read values from Adafruit's Ultimate GPS breakout
* XBee2
  * Library to support API communications via XBee
