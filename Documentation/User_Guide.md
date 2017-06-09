# WORK IN PROGRESS 
	
## Introduction
Oceanographic equipment is often expensive and inaccessible for students and citizen oceanographers. The OpenCTD allows individuals to collect conductivity, temperature, and depth data with a cheap and easy-to-build device. It isn’t suitable for scientific research yet, but that doesn’t mean it won’t provide you with information about the ocean! 

Check out the [original OpenCTD](https://github.com/OceanographyforEveryone/OpenCTD) if you want to build a lower cost device.
Many thanks to Andrew Thaler, Kersey Sturdivant, and Russell Neches for providing the framework for the OpenCTD. 

![Original OpenCTD](https://github.com/OceanographyforEveryone/OpenCTD/blob/master/Images/ctds.jpg)
_Examples of the original OpenCTD._

![CTDizzle](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/20170517_185546.jpg)
_The CTDizzle Mk3_




## Before You Get Started

There are likely cheaper and/or better sensor options out there. This guide only works for parts listed in the Parts_List.
It is your responsibility to ensure that all parts are compatible with your setup. This build guide also assumes that you are running everything off of Windows. 


## Build Instructions

### Setup
#### Setting Up the Arduino IDE
The Arduino Integrated Development Environment (IDE) is simple to use. It is recommended that the user maintain the default directories that the Arduino IDE download wizard creates. To install Arduino…

1. Go to https://www.arduino.cc/en/main/software.
2. Select the Windows Installer version.
3. Follow the installation wizard.
4. Set up shortcuts as desired.

#### Setting up the Qduino Mini
The Qduino Mini is not an officially supported by Arduino. It is necessary to download the board package that is specific for the Qduino from the Sparkfun GitHub. **IF THIS STEP IS NOT COMPLETED, YOU RUN THE RISK OF BRICKING YOUR QDUINO WHEN ATTEMPTING TO UPLOAD.**

1. Open the Arduino IDE.
2. Navigate to File > Preferences
3. In Additional Board URLs, add the following link:
https://raw.githubusercontent.com/sparkfun/Arduino_Boards/master/IDE_Board_Manager/package_sparkfun_index.json
4. Navigate to Tools > Board > Boards Manager.
5. In the Boards Manager window, search for SparkFun AVR Boards. Install SparkFun AVR Boards.
6. Navigate to Tools > Boards > Qduino Mini. **Any other board selection will brick your Qduino.**
7. Connect your Qduino Mini to the computer via microUSB. Turn on the Qduino.
8. Navigate to Tools > Port. Select the available COM port. Make a note of which port is selected and which USB port you are using on your computer. If using a different USB port for later uploads, your com port will need to be changed to what is available. 
Your Qduino Mini should now be upload ready. This will be tested after installing additional libraries.

#### Formatting the SD Card
It is also necessary to format the microSD card that will be used to store the data. 

1. Insert your microSD card into a USB adapter and plug into the computer.
2. Navigate to Windows Explorer, right click your microUSB card and select format.
3. Under file system, select FAT32. Select Start. A
4. Your card should now be formatted. 
5. OPTIONAL: Navigate to your SD card through Windows Explorer. If desired create and additional folder to save old data. 

#### Setting Up the Required Libraries
Several libraries are needed to allow the OpenCTD operating code to work. These libraries allow communication with the sensors and allow the use of unique commands. They can either be found within the Arduino IDE or downloaded from GitHub. Libraries native within the IDE are automatically included by the operating code and no further steps are necessary to include them. The following instructions show how to download and access the third party libraries. 

|Native Libraries|Third Party Libraries|
|:---:|:---:|
|SPI|Qduino|
|SoftwareSerial|TSYS01|
|Wire|MS5837|
|SD|SparkFunDS3234RTC|

The Qduino library is automatically made available through the previous step.

##### TSYS01 Temperature Sensor Library
The temperature sensor requires the TSYS01 library. To access the library:
1.	Go to https://github.com/bluerobotics/BlueRobotics_TSYS01_Library
2.	Select the Clone or download button. Click on Download Zip.
3.	Navigate to your downloads folder through Windows Explorer.
4.	Right click on the BlueRobotics_TSYS01_Library-master folder. Select extract all.
5.	Select browse.
6.	Navigate to Windows (C:) > Program Files (x86) > Arduino > libraries. Click on select folder.
7.	The TSYS01 library can now be included by the operating code.

##### MS5837 Pressure Sensor Library
The pressure sensor requires the MS5837 library. To access the library:
1.	Go to https://github.com/bluerobotics/BlueRobotics_MS5837_Library
2.	Select the Clone or download button. Click on Download Zip.
3.	Navigate to your downloads folder through Windows Explorer.
4.	Right click on the BlueRobotics_MS5837_Library-master folder. Select extract all.
5.	Select browse.
6.	Navigate to Windows (C:) > Program Files (x86) > Arduino > libraries. Click on select folder.
7.	The MS5837 library can now be included by the operating code.

##### DeadOn RTC Library
The DeadOn RTC requires the SparkFunDS3234RTC library. To access the library:
1.	Go to https://github.com/sparkfun/SparkFun_DS3234_RTC_Arduino_Library
2.	Select the Clone or download button. Click on Download Zip.
3.	Navigate to your downloads folder through Windows Explorer.
4.	Right click on the SparkFun_DS3234_RTC_Arduino_Library-master folder. Select extract all.
5.	Select browse.
6.	Navigate to Windows (C:) > Program Files (x86) > Arduino > libraries. Click on select folder.
7.	The SparkFunDS3234RTC library can now be included by the operating code. Note that during future uploads, the Arduino IDE may classify the DeadOn RTC library as “Uncategorized”. The library should still function even though this message appears.


### Board Prep
It is necessary to prepare several electronic components and sensors with some preliminary soldering. 
- Solder breakaway header strips to boards that require them. (Qduino, Transflash, RTC)
- It is recommended you keep the BNC connectors on the EC kit for testing and calibration. If you think you might want to shorten the conductivity probe cable, you can do that later. Make sure you have enough though!
- If you think you might not use the DF13 connects on the temperature and pressure sensors, now is a good time to cut them off. Carefully strip away ~1cm of insulation. Tin the ends to prevent stray wires.
- The following pictures show the use of JST connectors to allow easy removal of the sensors from the main protoboard. If you are using these connectors, now is a good time to solder to the sensors. Make sure to remember which wires you solder to the JST pins!

### Breadboard and Testing Setup
Set up the Qduino Mini, Transflash, RTC, and EC EZO on the breadboard. **If you change the pinouts in the physical build or the code, it is recommended that you record these changes.**

1. Following the pinout list, connect the Transflash and RTC to the Qduino.
  - Install your microSD card and 12mm coin cell. 
  - Connect the Qduino to your computer. Navigate to File > Open. Open the file named “Mk3OpCode”. Select upload.
  - Navigate to Tools > Serial Monitor.
  - In the serial monitor, you should see Qduino begin to spit out information. There won't be any data because you haven't hooked up the sensors yet!
	
2. Connect the temperature and pressure sensors to the Qduino.
  - It is okay to solder the green wires together (same goes for the white wires). Each device has a unique address that allows the Qduino to differentiate between the two.
  - Fire up the Qduino again and check the output. You should now see temperature and pressure in the serial monitor. 
  
3. Connect the EC probe to the EC EZO, then the EC EZO to the Qduino. (Using the BNC connector.)
  - Once connected, fire up the Qduino. You should see an EC value of 0.00 when the probe is in open air. 
  - You may notice that on a power cycle, the first reported line will not show an EC value. This is because the EC EZO is still warming up.

4. Once you have all the sensors and parts connected, ensure that the data output appears reasonable.
	In the serial monitor, it will take the form of...

_Date (MM/DD/YY) , Time (HH:mm:ss) , Conductivity (uS/cm) , Temperature (C) , Pressure (mbar)_

![Serial Monitor](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/SerialMonitor.png) 

_Note: The first line does not show EC because it takes time for the EC EZO to process incoming setup commands. This happens every time the unit is power cycled. The provided processing materials will automatically remove this line, but you will need to remove it on your own otherwise._

- The date should be representative of the date that your computer is set to. The time should be close to the time that your computer is set to, but may be behind by about 30 seconds. This is due to upload delay. If your time is drastically off or incoherent, remove the battery and power cycle the system. 

- The conductivity value should be zero. If it is not present in the output, try switching the Tx and Rx lines. Alternatively, you can change the pins in the code. Note in the above image, the EC is missing in the first line. It takes time for the EC circuit to initialize and thus is missing for the first sample.

- The temperature should be representative of the ambient temperature of the room you are performing the test in. It may be handy to have a thermometer nearby to check this. The temperature probe is factory calibrated, but if further calibration is needed, a two-point calibration is recommended.

- The pressure sensor should be spitting out values between 1000 and 1030 depending on your elevation. If you are near sea level, the value should be within a few millibars of 1013. The pressure sensor is factory calibrated, but if values appear to be drastically off (e.g. 86000 or -6000), first check your pinout connections. If still incorrect, contact the manufacturer. 

5. Now is a good time to calibrate the conductivity sensor. Follow along with the calibration procedure found in Documentation (in progress).
  - It is recommended that you do not cut the probe cable until after calibration, in the event that there may be a manufactuer defect. Cutting the cable prior to testing the probe will void any warranty and return policy that Atlas Scientific may have. 
  - A two point calibration is highly encouraged. Conductivity is highly dependent on temperature, so it is recommended that you calibrate the probe in a temperature controlled area (such as a cafeteria refrigerator or cold storage room).
  - After you have confirmed proper calibration of the probe, it should not need to be calibrated for another year. You can now cut the cable if you do not plan to implement the BNC connectors into your design. 


### Case Construction and Potting
Once everything checks out and your breadboard tests are successful, you can begin to put the pressure case together.

#### End Cap and Flange Prep
If using a blank end cap, drill two 10mm holes into one of the caps. This will be considered the end cap that will be used for the switch and vent. Make sure there is enough space in between the holes to allow you to tighten the aluminum bulkheads with a wrench. 
 
![Switch and Vent Endcap](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/20170605_104802_001.jpg)
_Example of two holes drilled into an end cap._

**Need diagram of sandpaper and flange**

After you have drilled the holes, use a high grit sandpaper to scuff up the inside portion of the end cap and flange. Clean the end cap and flange with alcohol. Now you can install the aluminum bulkheads that comprise the switch and vent. You'll want to grease up the bulkhead O-ring before installation. Don't forget to tighten them down! Next, install the end cap on the flange. Don't forget to add a greased up O-ring! Tighten all of the screws in a star pattern.

![Endcap + Flange](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/20170605_151845.jpg)
_Example of end cap and flange connected with bulkheads installed._

You can also epoxy this end cap if you want an additional seal. Here is an example. It is recommended that you wrap the outside of the flange with masking tape to prevent debris and epoxy from entering the O-ring grooves. Any slight deviation in the O-ring surface will increase the risk of leakage.
![Epoxy Endcap](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/20170605_203238.jpg)
_Note: It is recommended that you use the potting kit to minimize mess and bubbling. You will notice that there is some slight bubbling in the picture above. To get rid of bubble after placing the epoxy, you can put the end cap in a vacuum chamber._

In the other end cap, drill two 10mm holes and one 12mm hole. To increase the internal space for the electrical compenents, it is recommended that you place the 12mm hole as close to the flange wall as possible, while still leaving a little space for epoxy to surround the EC probe. You can connect the end cap to the flange to act as a guide.

**Picture of sensor end cap here**

Use a high grit sandpaper to rough up the end cap and flange. Clean with alcohol. Install the temperature and pressure sensors in the 10mm holes. Next, install the end cap onto the flange. The next part is a little tricky.

Insert the EC probe into the 12mm hole. Allow it to extend through until it is approximately even with the temperature probe height. Reinstall the rubber probe guard to prevent any epoxy or glue entering the sensor area. The probe may not fit perfectly within the hole, so it is recommended you attempt to make it as perpendicular with the end cap as possible, and then add a couple drops of superglue to hold it in place. You can use the acrylic tube as stand. Epoxy this end cap in a fashion similar to the previous end cap. As the EC probe now is a site for leaking, it is recommended that you use plenty of epoxy. Allow it to cure for 24 hours.


### Protoboard Soldering
It is recommended that you connect one component to the Qduino at a time and view the output in the serial monitor after each sensor installation. It may be easiest to start with the SD module, then the RTC, Atlas EC EZO, and then the sensors. 

Trim the protoboard so that it will fit within the internal dimensions of the main tube. Align the components as you see fit. Carefully tack a couple pins of each compenent to the protoboard to keep them in place. Cut lengths of solid core wire to bridge between the corresponding pins for each of your boards. This is where the needle hemostats come in handy. Also note that you can attach the matching pins of the RTC and Transflash together. Both of these use Serial Peripheral Interface (SPI) to communicate with the Qduino, but there is enough of a delay between operations that they can use the same pins.

It isn't necessary, but installing a quick disconnect for the sensors helps when you need to reprogram, charge, or pull data from the protoboard. You can solder one half of the 4-pin JST connector to the temperature and pressure sensors and the other half to the Qduino. Make sure you have the correct pin orientation!

Now is the time to decide if you want to cut the EC probe cable. Leaving the BNC connector has a couple advantages. It makes it easier to disconnect from the protoboard and there is no confusion over the probe communication. A downside to this is that there is a lot of excess cable. There is probably room for this excess cable in the internal space, but it may be cramped. 

- If you decide to cut the cable, follow the Atlas-Scientific guide to cable cutting. Recall that Atlas-Scientific will not accept returns of probes with cut capbles. Once cut, solder one half of the 2-pin JST connector to the probe leads, and the other half to the corresponding pins on the EC EZO. 

**Picture of possible protoboard set up here**

#### Switch Bridge Extension
It is not recommended that you cut the battery cables to install the switch, as this may have an impact on the charging of the battery. Instead, use a JST extension cable to tie the switch into. First, cut the ground line of the extension cable at roughly the midpoint. Solder a switch lead onto each end of the ground line. 
- Take care when soldering, as the wire will heat up quickly when maintaining contact with the soldering iron. This may result in deformation of the JST connector and you will not be able to use it. 


**Picture of JST extension here**




**Picture of mess of wires here**
   



### Final Case Construction
After you have soldered everything and tested the data output, you can finish constructing the case.

1. Ensure the flanges are clean. Grease the flange O-rings for the sensor end cap and install them.
2. Install the sensor end cap onto the acrylic tube. 
3. Sort the wires.
4. Connect the Qduino to the battery via the JST extension. Ensure that the switch is off or removed. 
5. Place a desiccant pack in the acrylic tube. 
6. Connect your sensors to the protoboard. Place the protoboard and battery in the tube. It is recommended that you tape the battery to the protoboard. 
7. Pack the acrylic tube with some sort of packing material if there is some play in the internal wiring and components. 
8. Remove the purge plug from the switch and vent end cap. Install the switch and vent end cap on the acrylic tube.
9. Reinstall the switch and plug. 
10. Turn on the device and look for the LEDs on the EC EZO. 



 

**Picture of a finished OpenCTD here**









## Predeployment Procedure
Deployment plan of your OpenCTD plays a role in the sampling regime.
- If you plan to take profiles, it should be set to sample as frequently as possible, which at this point is roughly 1 Hz.
- If you plan to leave the OpenCTD in the same spot for several hours or days, it should be set to sample every minute to few minutes. Doing this will increase the battery life. Another way to increase the battery life is by turning off the EC EZO LEDs. Instructions on how to do this can be found in the EZ EZO Datasheet (in the Resources page). 

## Deployment Procedure
The device should be fully assembled and the proper sampling regime selected prior to reaching the study site. 
1.	Confirm all sensors, plugs, bulkheads, and end caps are secure. 
2.	Remove any sensor covers on the conductivity, temperature, and pressure sensors.
3.	Turn the external switch clockwise until it can turn no further. The unit should now turn ON. 
  - The Atlas Scientific EC EZO LED should begin to alternate between green and cyan, indicating that the conductivity sensor is now sampling. If the EZO remains green, it is not continuously sampling and the deployment should be postponed until the proper code is uploaded. If the EZO is consistently flashing a red LED in between green and cyan, it is possible there is ground fault or communication error in the system and connections should be checked. 
4.	If step 3 is satisfied, then you can begin deployment!
  - If profiling with the unit, it is suggested that it be left in the top few meters of the water column for approximately ten minutes to allow for equilibrium. Once ready to profile, bring the unit to just below the surface, and allow it to descend at a rate around 0.25 m/s (~1 fathom every 10 seconds). The unit is only capable of sampling at a maximum of 1 Hz, so the slower the descent the better. 
  - If planning to leave the unit at a particular site for an extended period of time, it is recommended that the user ensure that the device is properly secured and **ON** prior to leaving the site. 

## Recovery Procedure
1.	After recovering the unit, turn the main switch counter-clockwise until the EC EZO LEDs turn off (usually ½ to 1 rotation). Do not turn it any further or you may risk introducing water to the internals.
2.	Spray the unit down with fresh water if possible. 
3.	If biofouling has accrued on the device, carefully remove the tape used to protect the case. If tape was not used to prevent biofouling, carefully use a soft bristle brush or plastic paint scraper to remove any fouling on the case. 
  - For the sensors, use a soft bristle toothbrush or sponge to remove any biofouling. **Do not use a brush on the conductivity probe head.** If biofouling in the EC probe sensing area is non-compliant, you can place the probe in a 5% HCl solution and then use cotton swabs to remove obstructions. You can also try using freshwater or canned-air.
4.	Dry the device.
5.	Replace all sensor caps.
6.	The device can be deployed again if the user desires.
  - If the unit is primarily used for profiling, the device is ready to go once the user decides to collect data again. If there is concern that the battery may be low, refer to the Battery Charging Procedure.
  - If another stationary deployment is planned, the battery will likely need to be charged or replaced. This requires the user to open up the device. 

## Battery Charging Procedure
The Qduino Mini has the ability to charge a single-cell lithium ion battery when connected to a computer or microUSB outlet adapter. The user can flash the Qduino FuelGauge sketch (found in Arduino IDE examples folder) to the Qduino to have the charge percentage reported to the serial monitor to ensure that the battery is not connected to the charging system for too long. Simply plug in the battery to the Qduino and connect the unit to a computer via microUSB. Don't forget to remove the SD card, so as to not record any unnecessary data.

By default, the Qduino charges batteries at 100 mA. To increase the charge rate to 500 mA, you can solder the SJ1 pad on the backside of the Qduino.

The length of time a unit can be deployed is ultimately restricted by the battery used. Currently, a 3.7V 6000mAh LiPo will run the unit for approximately 160 hours. Battery life can be extended by turning off the LEDs on the EC EZO or decreasing sampling frequency. 


## Data Download and Analysis

### Accessing and Plotting the Data
Currently, the user is required to open the device to access the data. **Make sure the device is dry before continuing.**
This is done by removing the switch and vent endcap and removing the microSD card. Take care when removing the end cap, as it is important to keep the O-rings clean. 

1. Connect the microSD card to your computer using an adapter.
2. Transfer the RAWCTD files you are interested in to your computer. It may be necessary to open these to check for dates and times.
3. Save all the files on the SD card to a seperate folder on the SD card labeled "Old Data".
4. There are several methods to process and analyze the data...
  - Through the provided MATLAB script.
  - Through the provided R script.
  - Through the provided Microsoft Excel spreadsheet (in progress).
  - Through your processing program of choice. RAWCTD files are comma-seperated.
5. Once you are finished looking at the data, delete the RAWCTD files in the main directory of the SD card. This keeps things from getting cluttered. 
6. Reinstall the microSD card and end cap. If you think the O-rings look a little dirty, clean and reapply silicone grease before continuing. 

### Reading Raw Data
RAWCTD files are comma-seperated. Data will appear in five columns in the order of...

|MM/DD/YYYY|HH:mm:ss|Conductivity (µS/cm)|Temperature (°C)|Pressure (mbar)|
|:---:|:---:|:---:|:---:|:---:|

![CSVexample](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/CSVExample.png)

_Example of data from a RAWCTD file. Note that the conductivity values are incorrect due to an improper calibration of the conductivity sensor._

If looking to plot the data on your own, it is important to realize that the pressure measurements are representative of absolute pressure, which includes the atmospheric pressure component. To convert to gauge pressure, simply subtract atmospheric pressure from the absolute pressure. This can be done by assuming the first pressure value recorded is the atmospheric pressure (if you turn the unit on above the water. When you subtract this value, you may get a few negative pressure values in the beginning and end of your file. You will need to remove those lines from the file.

Another option is to simply assume that atmospheric pressure is 1000 mbar. Doing this may force your depth calculations to be +/- 20cm off of the actual depth.

### Using the MATLAB Plotter
If you have access to MATLAB, simply run the script. If you do not have access to MATLAB, you can download the CTDPlotter application. It is a free MATLAB based application that only requires you to install a free MCR runtime. Both methods will give you the following results. It should be noted that the plotter is currently designed for use by fishermen in the U.S. Temperature has been converted to Fahrenheit and depth has been changed to fathoms. 

If you run the application, it will take a minute or two for a search window to pop up. Here you can select the file you are interested in plotting. 

![Pop Up](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/PlotterPopUp.png)

After selecting open, another minute will pass by and three windows will pop up. One window is a representation of the data as a profile, another window shows the data over time, and the last is a table of the processed data.

![Output](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/PlotterOutput.png)

The application will also create a folder in your C: drive labeled "OpenCTD_Data". It will store the plots and tables you created and name them based on the date and time of the first line of the file. 

![PlotterDirectory](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/DirectoryforPlotter.PNG)






	
