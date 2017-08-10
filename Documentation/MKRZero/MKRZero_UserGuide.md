# USER GUIDE (WORK IN PROGRESS) 

1. [Introduction](#introduction)
	- [Why Conductivity, Temperature, and Depth?]
	- [Before You Get Started](#before-you-get-started)
2. [The CTDizzle Mk4](#the-ctdizzle-mk4)
	- [Specifications](#specifications)
3. [Build Instructions](#build-instructions)
	- [Software Setup](#software-setup)
		- [Setting Up the Arduino IDE](#setting-up-the-arduino-ide)
		- [Setting Up the Arduino MKRZero](#setting-up-the-arduino-mkrzero)
		- [Formatting the SD Card](#formatting-the-sd-card)
		- [Setting Up the Required Libraries](#setting-up-the-required-libraries)
	- [Breadboard Testing](#breadboard-testing)
	- [Bench Test]
		- [Calibrating the EC EZO]
	- [Case Construction and Potting]
		- [End Cap and Flange Preparation]
	- [Protoboard Soldering]
		- [Switch Cable Extension] 
4. [Corrosion](#corrosion)
5. [Pre-deployment Procedure](#pre-deployment-procedure)
6. [Deployment Procedure](#deployment-procedure)
7. [Recovery Procedure](#recovery-procedure)
8. [Battery Charging Procedure]
9. [Data Download and Analysis]
	- [The West Coast]
	- [Yaquina Bay]
	- [Oregon Shelf]
10. [Using the MATLAB Plotter]
11. [Index of Jargon]
	
## Introduction

Oceanographic equipment is often expensive and inaccessible for students and citizen oceanographers. The OpenCTD helps reduce costs and allows individuals to collect conductivity, temperature, and depth data with an easy-to-build device. It is still being refined and isn't quite ready for use in scientific research yet, but in its current stat it will give you data suitable for learning and teaching. 

Check out the [original OpenCTD](https://github.com/OceanographyforEveryone/OpenCTD) if you want to build a lower cost device out of easily accessible tools and materials. Many thanks to Andrew Thaler, Kersey Sturdivant, and Russell Neches for providing the initial framework for the OpenCTD. 

![Original OpenCTD](https://raw.githubusercontent.com/CTDizzle/CTDizzle/master/Documentation/Images/OpenCTDVersions.jpg)
_Versions of the OpenCTD. Photo taken by Andrew Thaler._

### Why Conductivity, Temperature, and Depth?

Temperature itself is an incredibly useful parameter as so many other ocean properties and phenomena rely on or are impacted by it.
For example, temperature plays a role in how much gas (such as oxygen) seawater can hold, which in turn impacts productivity of fisheries along the Oregon coast. Similar to factors such as food availability, water movement, and predation; temperature also influences the growth rate, welfare, and reproductive potential of many organisms. Temperate is also one of the major factors that influences the density of seawater, which in turn plays a role in global water circulation. By monitoring ocean temperature over space and time, scientists are able to come up with connections between temperature and other aspects of the ocean.

Conductivity by itself isn't a particularly useful, but when combined with temperature and pressure through an empirical calculation, it allows one determine the salinity of the water. Salinity is essentially the concentration of dissolved salts and also plays a role in determining density. Saltier water is more dense than fresher water (assuming the temperature is the same for both).

In a two dimensional world (think latitude and longitude), the temperature and salinity of the surface ocean varies with location and time. In the Arctic, near Greenland, it is cold enough for sea ice to form. As the ice forms, the salinity of the water increases because the saltiness has no where to go, as a result, a mass of saltier, denser water begins to sink to the bottom of the ocean. This water then begins a long journey to the Eastern Pacific, changing in temperature and salinity every so slightly. These values also vary with depth!

The true depth of the ocean is difficult to measure. The average depth of the ocean is 4000m and the deepest part is just under 11000m. That would be a long tape measure! Scientists have come up with a variety of methods for determining water depth, including sonar measurements, satellite altimetery, and pressure readings. The CTD uses pressure to determine water depth, which is easily calculated through an empirical formula.

The CTD is the workhorse tool of oceanography. By building your own, I hope that you can gain an appreciation for the data, how it is collected, and what it tells us about our oceans.


### Before You Get Started

This guide is intended to be used by students at Toledo High School and includes concepts and procedures to reflect that.

This guide was designed so that you can build the CTDizzle with little to no experience with programming or tools. If you are confused on a topic, or require additional information, please do not hesitate to contact the author.

There are likely cheaper and/or better sensor options out there. This guide only covers the parts outlined in the parts list. If you decide to use different sensors or parts, it is your responsibility to ensure that all parts are compatible with your setup.

It should be noted that this guide assumes that you are running everything through Windows. As such, there is no Linux or mac OS support for the MATLAB and R processing scripts at this time. Please make sure that you are able to find an equivalent program for the steps that use third-party programs.

## The CTDizzle Mk4

This is the fourth rendition of the CTDizzle. Its construction is a little different than the original CTD, as it uses some different sensor and parts. It costs about 700 USD to construct and doesn't require any tools that can't be easily found at your local hardware store. If you have all the parts and tools on hand, you should be able to build it in a weekend!


### Specifications
* Max Depth: 130m
* EC Accuracy: <1% after calibration
* Temperature Accuracy: +/- 0.1 C
* Pressure Accuracy: +/- 100 mbar
* Max Sampling Rate: 1 Hz
* Battery Life: ~ 100 hours (3.7v 4400mAh)

Battery life ultimately depends on the battery that you use. It is recommended that you stick with the 3.7v LiPo family. 


## Build Instructions

### Software Setup
#### Setting Up the Arduino IDE
The Arduino Integrated Development Environment (IDE) is simple to use. It is recommended that the user maintain the default directories that the Arduino IDE download wizard creates. To install Arduino…

1. Go to https://www.arduino.cc/en/main/software.
2. Select the Windows Installer version.
3. Follow the installation wizard.
4. Set up shortcuts as desired.


#### Setting up the MKRZero
The MKRZero is officially supported by Arduino. The required package does not come pre-installed with the Arduino IDE, so you will need to install it using the Boards Manager.

1. Open the Arduino IDE.
2. Navigate to Tools > Board > Board Manager
3. Search for Arduino SAMD Boards. Select Install.
4. After it has installed, navigate to Tools > Boards. 
5. Select MKRZero.
6. Connect your MKRZero to your computer via microUSB. 
7. Navigate to Tools > Port. Select the available COM Port. 

Your MKRZero should now be upload ready. Disconnect from your computer if desired. It is recommended that you keep track of which USB port you plugged the MKRZero into. That way you don't have to worry about changing the com port every time you connect it to the computer.


#### Formatting the SD Card
It is also necessary to format the microSD card that will be used to store the data. 

1. Insert the microSD card into a USB adapter and plug into a computer.
2. Navigate to Windows Explorer, right click your microUSB card and select Format.
3. Under file system, select FAT. 
4. Select Start. 
6. Your card should now be formatted. 
7. OPTIONAL: Navigate to your SD card through Windows Explorer. If desired create and additional folder to save old data. 

Another option is to install the [SD Card Formatter](https://www.sdcard.org/downloads/formatter_4/) developed by the SD Association. If you think you might play around with a Raspberry Pi in the future, this application is particularly useful.

#### Setting Up the Required Libraries
Several libraries are needed to allow the OpenCTD operating code to work. These libraries allow communication with the sensors and the use of unique commands. They can either be found within the Arduino IDE or downloaded from GitHub. Libraries native within the IDE are automatically included by the IDE and no further steps are necessary to include them. The following instructions show how to download and access the third party libraries. 

|Native Libraries|Third Party Libraries|
|:---:|:---:|
|SPI|TSYS01|
|Wire|MS5837|
|SD|SparkFunDS3234RTC|

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

If you are using different sensors, make sure to use the right libraries!

### Breadboard Testing
Most of the purchased parts should already be breadboard compatible, but there are a couple that you will need to solder header pins to.
If you followed along with the parts list, you should have enough extra to practice soldering. Start by breaking off a strip of protoboard and 4 or five header pins from the main strip. Place the small header strip into the protoboard and practice connecting the two. You'll use less solder than you first expect and will happen pretty quickly!  Don't forget to check the you have the appropriate temperature for the solder you are using. Please use protective eyewear and appropriate clothing.

Once you are confident with your newfound soldering skills, solder header pins to the DeadOn RTC and any other parts that need it.

[Picture of DeadOn RTC with header pins here.]

The next step is to remove the DF13 connectors on the temperature and pressure sensors. After you have removed them, carefully strip away ~1cm of insulation to expose the wire. 

[Picture of exposed wire here.]

Both the temperature and pressure sensors use the same communication protocol (I2C). In the final product, similar wires will be soldered to the same pin on the MKRZero. Each device has a unique address, so the MKRZero is capable of differentiating between the two. 
After you have striped the wires, you can solder together the same colored wires of the sensors. It is recommended that you intertwine the wires to make things less messy. If you aren't confident in your soldering ability, feel free to practice with some other wire.

[Picture of soldered wires here.]

Now is the time to set things up on the breadboard!

Place the MKRZero, EC EZO, and DeadOn RTC on the breadboard. Don't forget to install the SD card and coin cell!

[Picture of prelim setup here].

Next, connect everything together using the pinout guide.

[Picture of setup here.]


### Bench Test

Once you have the breadboard setup, connect your MKRZero to your computer and upload the MKRZero_OpCode.

[Picture of connection here.]

Open the serial monitor. If you have everything set up correctly, you should see data printing to the screen in the form of:
Date (mm/dd/yyyy), Time (HH:mm:ss), EC (uS/cm), T (degC), P (mbar), SAL (EC EZO), Depth (Sketch), SAL (Sketch). 

[Picture of output.]


- The date should be representative of the date that your computer is set to. The time should be close to the time that your computer is set to, but may be behind by about 30 seconds. This is due to upload delay. If your time is drastically off or incoherent, remove the battery and power cycle the system. 

- The conductivity value should be zero. If it is not present in the output, try switching the Tx and Rx lines. Alternatively, you can change the pins in the code. Note in the above image, the EC is missing in the first line. It takes time for the EC circuit to initialize and thus is missing for the first sample.

- The temperature should be representative of the ambient temperature of the room you are performing the test in. It may be handy to have a thermometer nearby to check this. The temperature probe is factory calibrated, but if further calibration is needed, a two-point calibration is recommended.

- The pressure sensor should be spitting out values between 1000 and 1050 depending on your elevation and sensor accuracy. If you are near sea level, the value should be within a few millibars of 1013. The pressure sensor is factory calibrated, but if values appear to be drastically off (e.g. 86000 or -6000), first check your pinout connections. If still incorrect, contact the manufacturer. 


Calibrating the Conductivity Sensor

Unlike the factory calibrated temperature and pressure sensors, the conductivity probe/circuit require a user calibration. First, you will need to leave you complete setup in a temperature controlled room over night (such as a cold storage room or cafeteria refrigerator).

The next morning, take your calibration solutions, calibration procedure, and computer to your setup. Follow along with the calibration procedure found in the documentation folder (in progress). Conductivity is highly dependent on temperature, so it is important that you be as precise as possible! Using the provided plots, determine the temperature of the room and corresponding conductivity value to the nearest 100 uS/cm. Don't forget to bring a parka!

After you have confirmed proper calibration of the probe, it should not need to be calibrated for another year. You can now cut the cable if you do not plan to implement the BNC connectors into your design. Please note that cutting the cable voids the Atlas-Scientific warranty, so it important to first test the probe to see if it works. 


### Case Construction and Potting
Once everything checks out and your breadboard tests are successful, you can begin to put the pressure case together.

#### End Cap and Flange Prep
If you purchased the Blue Robotics case found in the MKR parts list, you will have two end caps with two holes. One end cap will house the temperature and conductivity sensor, and the other will house the pressure sensor and switch.
For the end cap that you will use for the conductivity sensor, one of the holes will need to be drilled out to 12mm in order to accomodate the conducitivity probe. 

Install the end caps onto the flanges without the o-ring. Using sandpaper, scuff up the internal surface of the end cap and flange. This will increase the bonding capacity of the urethane with the surface.


If using a blank end cap, drill two 10mm holes into one of the caps. This will be considered the end cap that will be used for the switch and vent. Make sure there is enough space in between the holes to allow you to tighten the aluminum bulkheads with a wrench. 
 
![Switch and Vent Endcap](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/HolesEndcap.jpg)
_Example of two holes drilled into an end cap._

Clean the end cap and flange with alcohol. Now you can install the aluminum bulkheads that comprise the switch and vent. You'll want to grease up the bulkhead O-ring before installation. Don't forget to tighten them down! Next, install the end cap on the flange. Don't forget to add a greased up O-ring! Tighten all of the screws in a star pattern. Next, use a high grit sandpaper to scuff up the inside portion of the end cap and flange.

![Endcap + Flange](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/NoEpoxySwitchVent.jpg)
_Example of end cap and flange connected with bulkheads installed. Now is a good time to use the sanpaper._

You can also epoxy this end cap if you want an additional seal. Here is an example. It is recommended that you wrap the outside of the flange with masking tape to prevent debris and epoxy from entering the O-ring grooves. Any slight deviation in the O-ring surface will increase the risk of leakage.
![Epoxy Endcap](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/TapeFlange.jpg)
_Note: It is recommended that you use the potting kit to minimize mess and bubbling. You will notice that there is some slight bubbling in the picture above. To get rid of bubble after placing the epoxy, you can put the end cap in a vacuum chamber._

In the other end cap, drill two 10mm holes and one 12mm hole. To increase the internal space for the electrical compenents, it is recommended that you place the 12mm hole as close to the flange wall as possible, while still leaving a little space for epoxy to surround the EC probe. You can connect the end cap to the flange to act as a guide.

Use a high grit sandpaper to rough up the end cap and flange. Clean with alcohol. Install the temperature and pressure sensors in the 10mm holes. Next, install the end cap onto the flange. The next part is a little tricky.

Insert the EC probe into the 12mm hole. Allow it to extend through until it is approximately even with the temperature probe height. Reinstall the rubber probe guard to prevent any epoxy or glue entering the sensor area. The probe may not fit perfectly within the hole, so it is recommended you attempt to make it as perpendicular with the end cap as possible, and then add a couple drops of superglue to hold it in place. You can use the acrylic tube as stand. Epoxy this end cap in a fashion similar to the previous end cap. As the EC probe now is a site for leaking, it is recommended that you use plenty of epoxy. Allow it to cure for 24 hours.


### Protoboard Soldering
It is recommended that you connect one component to the Qduino at a time and view the output in the serial monitor after each sensor installation. It may be easiest to start with the SD module, then the RTC, Atlas EC EZO, and then the sensors. 

Trim the protoboard so that it will fit within the internal dimensions of the main tube. Align the components as you see fit. Carefully tack a couple pins of each compenent to the protoboard to keep them in place. Cut lengths of solid core wire to bridge between the corresponding pins for each of your boards. This is where the needle hemostats come in handy. Also note that you can attach the matching pins of the RTC and Transflash together. Both of these use Serial Peripheral Interface (SPI) to communicate with the Qduino, but there is enough of a delay between operations that they can use the same pins.

It isn't necessary, but installing a quick disconnect for the sensors helps when you need to reprogram, charge, or pull data from the protoboard. You can solder one half of the 4-pin JST connector to the temperature and pressure sensors and the other half to the Qduino. Make sure you have the correct pin orientation!

Now is the time to decide if you want to cut the EC probe cable. Leaving the BNC connector has a couple advantages. It makes it easier to disconnect from the protoboard and there is no confusion over the probe communication. A downside to this is that there is a lot of excess cable. There is probably room for this excess cable in the internal space, but it may be cramped. 

- If you decide to cut the cable, follow the Atlas-Scientific guide to cable cutting. Recall that Atlas-Scientific will not accept returns of probes with cut capbles. Once cut, solder one half of the 2-pin JST connector to the probe leads, and the other half to the corresponding pins on the EC EZO. 

![WiredProtoTop](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/WiredProtoTop.jpg)
![WiredProtoBot](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/Wiredproto.jpg)
![WiredProtoExample](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/Wiredproto2.jpg)
![WiredProtoExample2](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/ProtoOverview.jpg)


#### Switch Cable Extension
It is not recommended that you cut the battery cables to install the switch, as this may have an impact on the charging of the battery. Instead, use a JST extension cable to tie the switch into. First, cut the ground line of the extension cable at roughly the midpoint. Solder a switch lead onto each end of the ground line. 
- Take care when soldering, as the wire will heat up quickly when maintaining contact with the soldering iron. This may result in deformation of the JST connector and you will not be able to use it. 

![JSTSwitch](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/SwitchCable.jpg)

![MessOfWires](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/Innards3.jpg)



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


![Completed](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/Finished.jpg)


## Corrosion
The screws used in the end caps are made of 316 SS and the main body of the unit is made of anodized aluminum.
When two dissimilar metals interact in seawater, galvanic corrosion can occur. The metal on the lower end of the galvanic scale (aluminum in this case) will begin to corrode after an extended period of time. Cathodic protection is one method to mitigating the corrosion of the end caps. This can be done by installing an anode (commonly made of zinc). 

I am currently searching for a non-invasive way of adding a zinc anode to the device. Another option is to replace the stainless steel screws with the aluminum equivalent.


## Predeployment Procedure
The deployment plan of your OpenCTD plays a role in the sampling regime.
- If you plan to take profiles, it should be set to sample as frequently as possible.
- If you plan to leave the OpenCTD in the same location for several hours or days, it should be set to sample every minute to few minutes. Doing this will increase the battery life. Another way to increase the battery life is by turning off the EC EZO LEDs. Instructions on how to do this can be found in the EZ EZO Datasheet.

## Deployment Procedure
The device should be fully assembled and the proper sampling regime selected prior to reaching the study site. 
1.	Confirm all sensors, plugs, bulkheads, and end caps are secure. 
2.	Remove any sensor covers on the conductivity, temperature, and pressure sensors.
3.	Turn the external switch clockwise until it can turn no further. The unit should now turn ON. 
  - If you are using an acrylic case, the EC EZO LED should begin to alternate between green and cyan, indicating that the conductivity sensor is now sampling. If the EZO remains green, it is not continuously sampling and the deployment should be postponed until the proper code is uploaded. If the EZO is consistently flashing a red LED in between green and cyan, it is possible there is ground fault or communication error in the system and connections should be checked. 
4.	If step 3 is satisfied, then you can begin deployment!
  - If profiling with the unit, it is suggested that it be left in the top few meters of the water column for approximately five minutes to allow for equilibrium. Once ready to profile, bring the unit to just below the surface, and allow it to descend at a rate around 0.25 m/s (~1 fathom every 10 seconds). The unit is only capable of sampling at a maximum of 1 Hz, so the slower the descent the better. 
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
1. Turn off the device.
2. Remove the switch/purge end cap. 
3. Remove the main electronics board and disconnect the battery switch cable.
4. Plug the battery directly into the MKRZero.
5. Connect the MKRZero to your computer or compatible wall outlet.

The MKRZero has the ability to charge a single-cell lithium ion battery when connected to a computer or microUSB outlet adapter. Simply plug in the battery to the MKRZero and connect the unit to a computer via microUSB. An orange LED should appear, indicating that the battery is charging. Even though the battery has a built in overcharge and damage prevention circuit, it is important that you do not charger your battery for too long.

It is recommended that you do not charge the battery through the JST switch cable, and only by plugging the battery directly into the MKRZero.

I am currently working on a method that will allow you to determine the current charge on your battery.

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

The application will also create a folder in your C: drive labeled "OpenCTD_Data". It will store the plots and tables you created and name them based on the date and time of the first line of the file. For new plots it will create a new folder within OpenCTD_Data and name it based on the date and time. For the individual files, naming goes by Plot Type_MMDDYY-HHmmss.

![PlotterDirectory](https://github.com/CTDizzle/CTDizzle/blob/master/Documentation/Images/DirectoryforPlotter.PNG)

### Is the data reasonable?

#### The West Coast (Move this to case construction section).

The west coast of the United States has one of the most adverse wave climates in the world. 

#### In a Bay

The OpenCTD is capable of observing changes over several days. The pressure sensor is capable of rectifying changes is tidal height and changes in temperature and salinity can be seen to follow. 

Yaquina Bay is an excellent place to test the OpenCTD. Under the right conditions, the device can be used find the depth of the salt wedge, or the extent of the river plume in the bay. 

Every couple of months students from Oregon State University will sample from the Yaquina Bay Bridge up to Toledo during various stages of the tidal cycle. The Oregon Coast Aquarium also continuosly collects salinity and temperature data on the water that is pumped in from the bay. 


#### The Oregon Shelf




## Index of Jargon

In no particular order...

|Term|Description|
|:---:|:---|
|BNC|[Bayonet Neill-Concelmen connector](https://en.wikipedia.org/wiki/BNC_connector). Typically the terminator on a coaxial cable|
|SPI|[Serial Peripheral Interface] (https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus). A synchronous serial communication interface typically used in short distance communication. One device is considered the master device and the others the slave. The slave select (SS) pin allows the microcontroller to select which device it talks to.|
|I2C|[Inter-Integrated Circuit](https://en.wikipedia.org/wiki/I%C2%B2C). Often pronouced I-squared-C or I-two-C. It only uses two lines for communication but is communicates slower than SPI|
|TX|Serial transmitter on a device. |
|RX|Serial reciever on a device. |
|Absolute Pressure|The OpenCTD measures absolute pressure. In the reported values, the atmospheric pressure is included. If your OpenCTD reads 1100 mbar, that does not mean it is at ~11 meter depth, but more likely ~1m assuming your atmospheric pressure is 1000 mbar.|
|Gauge Pressure| To get gauge pressure, simply subtract atmospheric pressure from the absolute pressure.|





	
