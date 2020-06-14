## Pinouts

Adafruit M0 Bluefruit LE I/O pins are only 3.3v tolerant.
All sensors operate via I2C.

If you use a voltage isolator, then you do not need pull-up resistors.

If you do not use a voltage isolator, then you will need two 4.7 kOhm resistors to pull-up the SDA and SCL lines. See I2C section of EC EZO datasheet for wiring diagram (starting at pg. 46).

If you are using the Adalogger Featherwing, you do not need to solder anything else other than the headers.

You will need to use the protoboard area on the double featherwing to wire the EC EZO.


|M0 Bluefruit|TSYS01 Temperature Sensor|
|:--------------------:|:--------------------:|
|VCC|Red Wire|
|GND|Black Wire|
|SCL (Pin 21)|Green Wire|
|SDA (Pin 20)|White Wire|

|M0 Bluefruit|MS5837-30Ba Pressure Sensor|
|:--------------------:|:--------------------:|
|VCC|Red Wire|
|GND|Black Wire|
|SCL (Pin 21)|Green Wire|
|SDA (Pin 20)|White Wire|

|M0 Bluefruit|EC EZO|
|:--------------------:|:--------------------:|
|VCC|VCC|
|GND|GND|
|SCL (Pin 21)|SCL (which is the TX on the EZO)|
|SDA (Pin 20)|SDA (which is the RX on the EZO)|

For the EC EZO to probe connection, the easiest thing to do is use the BNC. If you opt to use individual leads, then the orientation of PRB to lead does not matter. Just make sure to calibrate your conductivity probe after you solder everything together.

|EC EZO|Probe|
|:--------------------:|:--------------------:|
|PRB1|Lead 1 (Red)|
|PRB2|Lead 2 (Black)|
