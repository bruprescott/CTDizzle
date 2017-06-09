## Pinouts

VCC is always 3.3v.

|DeadOn RTC|Qduino Mini|	
|:------------:|:------------:|		
|GND|GND|	
|VCC|VCC|	
|SQW|Not Applicable|
|CLK|D15 (SCLK)|	, ![RTC](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/RTC.jpg)
|MISO|D14 (MISO)|	
|MOSI|D16 (MOSI)|	
|SS|D5|	

SQW is not needed unless you want to implement an alarm function.


|MicroSD Transflash|Qduino Mini|
|:--------------------:|:--------------------:|
|CD|Not Applicable|
|DO|D14 (MISO)|	
|GND|GND|
|SCK|D15 (SCLK)|
|VCC|VCC|)
|DI|D16 (MOSI)|
|CS|D4|

CD is not needed unless you want to implement a card detect function.



|TSYS01 Temperature Sensor|Qduino Mini|	
|:------------:|:------------:|	
|Red|VCC|	
|Black|GND|	
|Green|D3 (SCL)|	
|White|D2 (SDA)|	


|MS5837 Pressure Sensor|Qduino Mini|	
|:------------:|:------------:|	
|Red|VCC|	
|Black|GND|	
|Green|D3 (SCL)|	
|White|D2 (SDA)|	


|EC EZO|Qduino Mini|	
|:------------:|:------------:|	
|Tx|D8|	
|Rx|D9|	
|VCC|VCC|	
|GND|GND|	


|Atlas-Scientific EC K1.0 Probe|Qduino Mini|	
|:------------:|:------------:|
|Red|PRB1|	
|Black|PRB2|	

Wire-PRB orientation does not matter. If using a probe from a different manufacturer, you will need to first test the connectivity to determine which wires to use. 


