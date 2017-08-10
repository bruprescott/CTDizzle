## Pinouts

MKRZero I/O pins are only 3.3v tolerant.

|DeadOn RTC|MKRZero|	
|:------------:|:------------:|	
|GND|GND|	
|VCC|VCC|	
|SQW|Not Applicable|
|CLK|9 (SCL)|
|MISO|10 (MISO)|	
|MOSI|8 (MOSI)|	
|SS|D7|	

SQW is not needed unless you want to implement an alarm function.


|Board SD|MKRZero|
|:--------------------:|:--------------------:|
|CS|28|

SD capabilities are native to this board.

|TSYS01 Temperature Sensor|MKRZero|	
|:------------:|:------------:|	
|Red|VCC|	
|Black|GND|	
|Green|12 (SCL)|	
|White|11 (SDA)|	


|MS5837 Pressure Sensor|MKRZero|	
|:------------:|:------------:|	
|Red|VCC|	
|Black|GND|	
|Green|12 (SCL)|	
|White|11 (SDA)|	


|EC EZO|MKRZero|	
|:------------:|:------------:|	
|Tx|13|	
|Rx|14|	
|VCC|VCC|	
|GND|GND|	

TX on one side connects to RX on the other. TX should never attach to TX.

|Atlas-Scientific EC K1.0 Probe|EC EZO|	
|:------------:|:------------:|
|Red|PRB1|	
|Black|PRB2|	

It is possible to use the BNC adapter in this build. 
