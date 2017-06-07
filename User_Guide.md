# WORK IN PROGRESS 
	

## Introduction
Oceanographic equipment is often expensive and inaccessible for students and citizen oceanographers. The OpenCTD allows individuals to collect conductivity, temperature, and depth data with a cheap and easy-to-build device. It isn’t suitable for scientific research yet, but that doesn’t mean it won’t provide you with information about the ocean! 

Check out the [original OpenCTD](https://github.com/OceanographyforEveryone/OpenCTD) if you want to build a cheaper device.
Many thanks to Andrew Thaler, Kersey Sturdivant, and Russell Neches for providing the framework for the OpenCTD. 

**Before You Get Started**

There are cheaper and/or better sensor options out there. This guide only works for parts listed in the Parts_List.
It is your responsibility to ensure that all parts are compatible with your setup.


## Pinouts
VCC is always 3.3v.

|DeadOn RTC|Qduino Mini|	
|:------------:|:------------:|	
|GND|GND|	
|VCC|VCC|	
|SQW|Not Applicable|	
|CLK|D15 (SCLK)|	
|MISO|D14 (MISO)|	
|MOSI|D16 (MOSI)|	
|SS|D5|	

Note: SQW is not used unless you want to implement an alarm function.

|MicroSD Transflash|Qduino Mini|
|:--------------------:|:--------------------:|
|CD|Not Applicable|
|DO|D14 (MISO)|	
|GND|GND|
|SCK|D15 (SCLK)|
|VCC|VCC|
|DI|D16 (MOSI)|
|CS|D4|

Note: CD is not used unless you want to implement a card detect function.

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

|K1.0 Probe|Qduino Mini|	
|:------------:|:------------:|	
|Red|PRB1|	
|Black|PRB2|	

Note: This only applies if you decide to cut the probe cable.




 


Build Instructions

Step 1: Setting Up Arduino and the Qduino Mini
	The Arduino Integrated Development Environment (IDE) is simple to use. It is recommended that the user maintain the default directories that the Arduino IDE download wizard creates. To install Arduino…
a)	Go to https://www.arduino.cc/en/main/software.
b)	Select the Windows Installer version.
c)	Follow the installation wizard.
d)	Set up shortcuts as desired.
The Qduino Mini is not an officially supported by Arduino. It is necessary to download the board package that is specific for the Qduino from the Sparkfun GitHub. WARNING: IF THIS STEP IS NOT COMPLETED, YOU RUN THE RISK OF BRICKING YOUR QDUINO WHEN ATTEMPTING TO UPLOAD.
a)	Open the Arduino IDE.
b)	Navigate to File > Preferences
c)	In Additional Board URLs, add the following link:
https://raw.githubusercontent.com/sparkfun/Arduino_Boards/master/IDE_Board_Manager/package_sparkfun_index.json
d)	Navigate to Tools > Board > Boards Manager.
e)	In the Boards Manage window, search for SparkFun AVR Boards. Install SparkFun AVR Boards.
f)	Navigate to Tools > Boards > Qduino Mini. Refer to the above WARNING.
g)	Connect your Qduino Mini to your computer via microUSB. Turn on the Qduino.
h)	Navigate to Tools > Port. Select the available COM port. Make a note of which port is selected and which USB port you are using on your computer. If using a different USB port for later uploads, your port will need to be changed to what is available. 
Your Qduino Mini should now be upload ready. This will be tested after installing additional libraries.
It is also necessary to format the microSD card that will be used to store the data. 
a)	Insert your microSD card into a USB adapter and plug into your computer.
b)	Navigate to Windows Explorer, right click your microUSB card and select format.
c)	Under file system, select FAT32. Select Start.
d)	Navigate to your microSD card in Windows Explorer.
e)	Create a new text file named “datalog.txt” and save it to the microSD card.
f)	If desired, create additional folders to save sketches and old data.
Step 2: Setting Up the Required Libraries
	Several libraries are needed to allow the OpenCTD operating code to work. They can either be found within the Arduino IDE or downloaded from GitHub. Libraries native within the IDE are automatically included by the operating code and no further steps are necessary. The following instructions show how to download and access the third party libraries. 

Native Libraries	Third Party Libraries
SPI	Qduino
SoftwareSerial	TSYS01
Wire	MS5837
SD	SparkFunDS3234RTC

The Qduino library is automatically made available through Step 1. 

The temperature sensor requires the TSYS01 library. To access the library:
a)	Go to https://github.com/bluerobotics/BlueRobotics_TSYS01_Library
b)	Select the Clone or download button. Click on Download Zip.
c)	Navigate to your downloads folder through Windows Explorer.
d)	Right click on the BlueRobotics_TSYS01_Library-master folder. Select extract all.
e)	Select browse.
f)	Navigate to Windows (C:) > Program Files (x86) > Arduino > libraries. Click on select folder.
g)	The TSYS01 library can now be included by the operating code.

The pressure sensor requires the MS5837 library. To access the library:
a)	Go to https://github.com/bluerobotics/BlueRobotics_MS5837_Library
b)	Select the Clone or download button. Click on Download Zip.
c)	Navigate to your downloads folder through Windows Explorer.
d)	Right click on the BlueRobotics_MS5837_Library-master folder. Select extract all.
e)	Select browse.
f)	Navigate to Windows (C:) > Program Files (x86) > Arduino > libraries. Click on select folder.
g)	The MS5837 library can now be included by the operating code.

The DeadOn RTC requires the SparkFunDS3234RTC library. To access the library:
a)	Go to https://github.com/sparkfun/SparkFun_DS3234_RTC_Arduino_Library
b)	Select the Clone or download button. Click on Download Zip.
c)	Navigate to your downloads folder through Windows Explorer.
d)	Right click on the SparkFun_DS3234_RTC_Arduino_Library-master folder. Select extract all.
e)	Select browse.
f)	Navigate to Windows (C:) > Program Files (x86) > Arduino > libraries. Click on select folder.
g)	The SparkFunDS3234RTC library can now be included by the operating code. Note that during upload, the Arduino IDE may classify the DeadOn RTC library as “Uncategorized”. The library should still function if this occurs.

Step 3: Preliminary Soldering and Breadboard Setup
	It is necessary to prepare several electronic components and sensors with some preliminary soldering. 
•	The temperature and pressure sensors come default with a DF13-type connector. This connector is not needed and can be removed unless the user desire to implement the connectors in the build. After removing the connector, carefully strip away ~1cm at the end of each wire.
•	At this point, the conductivity probe is connected to the EC EZO by a BNC connector. As the breadboard setup is temporary, it is not necessary to cut the cable at this moment. If the user desires the conductivity probe be permanently potted in the casing, it is not necessary to cut the BNC connector. Cutting the cable prior to testing the probe will void any warranty and return policy that Atlas Scientific may have. 
•	Solder the appropriate header pins to the Qduino, DeadOn RTC, and microSD Transflash. 
•	 If a faster charge rate is desired, the user can solder the SJ1 pad on the backside of the Qduino. This changes the charge rate from 100 mA to 500 mA.
•	Using the pinout section as a guide, attach all electronic parts to the Qduino Mini via jumper wires.

Step 4: Breadboard Testing
	Install your formatted microSD card, 12mm coin cell, and battery. After your breadboard has been set up, you can now turn on the Qduino and upload the operating code. 

Navigate to File > Open. Open the file named “OpenCTD_Mk3_OpCode”. Select upload.

In the Arduino IDE, navigate to Tools > Serial Monitor. Immediately, you should see a string of numbers separated by commas. The data represents…

Date (MM/DD/YY) , Time (HH:mm:ss) , Conductivity (uS/cm) , Temperature (C) , Pressure (mbar)

 

The date should be representative of the date that your computer is set to. The time should be close to the time that your computer is set to, but may be behind by about 30 seconds. This is due to upload delay. If your time is drastically off or incoherent, remove the battery and power cycle the system. 

The conductivity value should be zero or near zero if already calibrated. If it is not present in the output, try switching the Tx and Rx lines. Alternatively, you can change the pins in the code. Note in the above image, the EC is missing in the first line. It takes time for the EC circuit to initialize and thus is missing for the first sample.

The temperature should be representative of the ambient temperature of the room you are performing the test in. It may be handy to have a thermometer nearby to check this. The temperature probe is factory calibrated, but if further calibration is needed, a two-point calibration is recommended.

The pressure sensor should be spitting out values between 1000 and 1030 depending on your elevation. If you are near sea level, the value should be within a few millibars of 1013. The pressure sensor is factory calibrated, but if values appear to be drastically off (e.g. 86000 or -6000), first check your pinout connections. If still incorrect, contact the manufacturer. 

If the output seems reasonable, the EC probe can now be calibrated. There are two methods for calibrating the conductivity probe of the unit. The first method is a single point calibration, which is discouraged. The second method is a two point calibration and provides much more accurate data. For best results, it is recommended that you calibrate the probe in a temperature controlled area as conductivity readings are highly dependent on temperature. Refer to the EC_Cal Procedure for a two-point calibration method. Once calibrated, cables can be cut and soldered as necessary.
Step 5: Case Construction and Potting
Clean each end of the acrylic tube case and aluminum flanges with Kimwipes and isopropyl alcohol. Grease the appropriate O-rings for the flange. Install these O-rings and insert the flanges into the case. Set this setup aside and cover with Kimwipes to prevent dust accumulation.

The aluminum bulkheads of the sensors and blanks easily mar when using unorthodox tools. It is recommended that you use a 14mm wrench or purchase the Blue Robotics wrench tool to tighten and remove them.

   

At this stage, the user can decide if permanent potting is necessary. If the unit is subjected to conditions that warrant the replacement of sensors, it is recommended that user avoid permanently potting the sensors in place. 

Designate one end cap as the switch and vent end cap and the other the sensor end cap, now referred to as endcap #1 and #2 respectively.  For endcap #1, install two blank plug bulkheads. Remember to grease the O-Rings prior to installation. Use two crescent wrenches to tighten the bulkheads. If you begin to strip the bulkheads, you have probably tightened them enough.

 

•	To pot the sensors in place, remove a flange from the case and connect to the end cap with sensors, ensuring the O-Ring is in place and that all six screws are tightened. 
•	Using sand paper, rough up the aluminum surfaces for the upcoming epoxy step. Place the flange+sensor endcap vertical so that the sensors are pointed down. 
•	Fill with Loctite 2-Ton Marine Epoxy up to the top of the bulkhead nuts. 
•	Allow to cure overnight.
•	The pressure and temperature sensor wires are exposed in the bulkheads. The user can decide to fix these in place with potting compound.
•	After curing overnight, ensure that all seals seem appropriate. If there is concern of an improper seal, do not hesitate to add more potting compound. 

Step 6: Final Soldering
It is recommended that you connect one component to the Qduino at a time and test Qduino output after each component installation. It may be easiest to start with the SD module, then the RTC, Atlas EC EZO, and then the sensors. 

Align the components on the protoboard as you see fit. Carefully tack a couple pins of each component to the protoboard to keep them in place. Cut lengths of solid core wire to bridge the corresponding pins for each of your boards. If you cut the EC probe cable, the wires do not have a designated PRB location and can be soldered to either PRB so long as the other one is soldered to the other PRB. You can solder the corresponding leads of the temperature and pressure sensors together prior to soldering to the Qduino. If using lead-free solder, take care with your placement of the soldering iron, as lead-free solder typically requires higher heat to flow.


 


 
 

Cut the ground line of the JST extension cable at the approximate midpoint. Solder a switch lead to both ends. 

 






Your final setup should look similar to this.

 


After everything is soldered and the unit turns on and collects data appropriately, you can finish constructing the case. 
•	Grease the end cap O-Rings.
•	Install the sensor end cap first. Tighten the M2 screws in a star pattern.
•	Connect the switch leads to the switch on the other end cap. Turn the unit on and off with the switch to ensure it works.
•	Prior to performing the final seal, pull the microSD card and ensure that it has been properly recording data. If so, delete the test files.
•	Install the switch and vent end cap. Tighten the M2 screws in a star pattern.
•	If desired, tape the unit with plumber’s tape to make cleaning easier in the future.
 
 

A finished OpenCTD.











 

 







Deployment Procedure
The device should be fully assembled and the proper sampling regime selected prior to reaching the study site. 
1.	Confirm all sensors, plugs, bulkheads, and end caps are tight and secure. 
2.	Remove any sensor covers on the conductivity, temperature, and pressure sensors.
3.	Turn the external switch clockwise until it can turn no further. The unit should now turn ON.
a.	The Atlas Scientific EC EZO LED should begin to alternate between green and cyan, indicating that the conductivity sensor is now sampling. If the EZO remains green, it is not continuously sampling and the deployment should be postponed until the proper code is uploaded. If the EZO is consistently flashing a red LED in between green and cyan, it is possible there is ground fault or communication error in the system and connections should be checked. You may notice that the EZO flashes red a couple times after start-up. This indicates that the EZO is unable to process incoming requests until it has completed its boot sequence.
4.	If step 3 is satisfied, then you can begin deployment!
If profiling with the unit, it is suggested that it be left in the top few meters of the water column for approximately ten minutes to allow for equilibrium. Once ready to profile, bring the unit to just below the surface, and allow it to descend at a rate around 0.25 m/s (~1 fathom every 10 seconds). The unit is only capable of sampling at a maximum of 1 Hz. 
If planning to leave the unit at a particular site for an extended period of time, it is recommended that the user ensure that the device is properly secured and ON prior to leaving the site. 

Recovery Procedure
1.	After recovering the unit, turn the main switch counter-clockwise until the LEDs turn off (usually ½ to 1 rotation). Do not turn it any further.
2.	Spray the unit down with fresh water if possible. 
3.	If biofouling has accrued on the device, carefully remove the tape used to protect the case. If tape was not used to prevent biofouling, carefully use a soft bristle brush or plastic paint scraper to remove any fouling on the case. 
a.	For the sensors, use a soft bristle toothbrush or sponge to remove any biofouling. Do not use a brush on the conductivity probe head. Do not insert anything into the conductivity cell. Use freshwater and/or canned air to clean sensors.
4.	Dry the device.
5.	Replace all sensor caps.
6.	The device can be deployed again if the user desires.
a.	If the unit is primarily used for profiling, the device is ready to go once the user decides to collect data again. If there is concern that the battery may be low, refer to the Battery Charging Procedure.
b.	If another in-situ deployment is planned, the battery will likely need to be charged or replaced. Refer to the Battery Charging Procedure if charging is needed. Refer to the Battery Replacement Procedure if battery replacement is needed. 







Battery Charging Procedure
	The Qduino Mini has the ability to charge a single-cell lithium ion battery when connected to a computer or microUSB adapter. The user can flash the FuelGauge sketch to the Qduino to have the charge percentage reported to the serial monitor to ensure that the battery is not connected to the charging system for too long. Simply plug in the battery to the Qduino and connect the unit to a computer via microUSB. It is recommended that the microSD card be removed during charging so as to not record unnecessary data.
	The length of time a unit can be deployed is ultimately restricted by the battery used. Currently, a 3.7V 6000mAh LiPo will run the unit for approximately 170 hours. Battery life can be extended by turning off the LEDs on the EC EZO and the Qduino Mini. 


Data Download and Analysis
	Currently, the user is required to open the device to access the microSD card. Ensure that the unit is dry prior to deconstruction. Using a 2.5mm hex key, remove the six screws holding the switch and vent end cap in place. Carefully remove the wires connected to the switch. Pull the board far enough out of the case to access the microSD card. Remove the SD card, place in a SD card reader of choice, and plug into a computer.
	Navigate to the SD card directory. At minimum, the top directory will contain a file labeled “LOGGER00.csv”. There may be other folders, but those will contain sketches or old data sets. There may be additional files in sequence with LOGGER00 if the device was turned on and off multiple times. Every time power is cycled, it creates a new file to log. This allows the user to create a single file for every profile.The csv file contains five columns. The following picture shows what the file may look like if using Microsoft Excel to view the raw data.

MM/DD/YYYY , HH:mm:ss , Conductivity (µS/cm) , Temperature (°C) , Pressure (mbar)

 
Note: The conductivity output in this figure is rubbish due to an improper calibration. Typical ocean/estuary conductivity readings range between 20000 to 38000 uS/cm.














OpenCTDPlotter
	The OpenCTDPlotter is proprietary MATLAB run standalone application. You do not need MATLAB to run this application, only a free runtime that can either be downloaded or installed with the package. Currently, it will take your raw data and convert temperature to Fahrenheit, pressure to depth, and all three sensor value to salinity and plot those values. Simply open the application, navigate to the file you want to access, and select open. It may take a minute to load.

 

After selecting open, three windows will appear. 
•	One contains a table of data that has been converted. 
•	Another contains time-series plots of temperature, salinity, and depth. 
•	The last contains profile plots of temperature and salinity.
 
You can save these by navigating to the File > Save As, for each window. It is important that you change the Save as type to something like .jpg or .png.
If you do not want to use the OpenCTDPlotter application, there are Microsoft Excel spreadsheets and R code available that perform the same conversion process. These require slightly more data manipulation by the user.  If you want a copy of the code for any of these, contact Ian Black.


Additional Resources

EC EZO Datasheet:
https://www.atlas-scientific.com/_files/_datasheets/_circuit/EC_EZO_Datasheet.pdf

TSYS01 Datasheet: http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FTSYS01%7FA%7Fpdf%7FEnglish%7FENG_DS_TSYS01_A.pdf%7FG-NICO-018

MS5837 Datasheet:
http://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FMS5837-30BA%7FB1%7Fpdf%7FEnglish%7FENG_DS_MS5837-30BA_B1.pdf%7FCAT-BLPS0017

Watertight Enclosure Documentation:
http://docs.bluerobotics.com/watertight-enclosures/

MicroSD Transflash Breakout Documentation:
https://github.com/sparkfun/microSD_Transflash_Breakout/tree/V_1.4

DeadOn RTC Guide:
https://learn.sparkfun.com/tutorials/deadon-rtc-breakout-hookup-guide


	
