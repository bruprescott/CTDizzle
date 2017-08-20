# CTDizzle User Manual

:+1: This emoji indicates sections that are directed toward the students I will be working with during my research project. Many of these sections may include information that is specific to the Oregon Coast.


## Contents
1. [Links to Other Documentation](#links)
2. [Introduction](#introduction)
	- [Before You Get Started](#before-you-get-started)
	- [Why Conductivity, Temperature, and Depth?](#why-conductivity,-temperature,-and-depth?)
	- [The CTDizzle Mk4](#the-ctdizzle-mk4)
	- [Specifications](#specification)
4. [Build Instructions]
	- [Software Setup]
		- [Setting Up the Arduino IDE]
		- [Setting Up the Arduino MKRZero]
		- [Formatting the SD Card]
		- [Setting Up the Required Libraries]
	- [Breadboard Testing]
	- [Bench Test]
		- [Calibrating the EC EZO]
	- [Case Construction and Potting]
		- [End Cap and Flange Preparation]
	- [Protoboard Soldering]
		- [Switch Cable Extension] 
5. [Corrosion](#corrosion)
6. [Pre-deployment Procedure](#pre-deployment-procedure)
7. [Deployment Procedure](#deployment-procedure)
8. [Recovery Procedure](#recovery-procedure)
9. [Battery Charging Procedure]
10. [Data Download and Analysis]
	- [The West Coast]
	- [Yaquina Bay]
	- [Oregon Shelf]
11. [Using the MATLAB Plotter]


## Links
[Parts List](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/MKRZero_Parts_List.md)

[Code](https://github.com/CTDizzle/CTDizzle/tree/master/MKRZero/ArduinoFiles)

[Pinout Guide](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/MKRZero_Pinouts.md)

[Resources and Literature](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Resources.md)

[Cal Procedure]

	
## Introduction

Oceanographic equipment is often expensive and inaccessible for students and citizen scientists. The OpenCTD is a relatively cheap, buildable device that allows individuals to easily collect conductivity, temperature, and pressure data. It is still being refined and doesn't quite produce research quality data, but in its current state it is a great tool for teaching and learning. 

Check out the [original OpenCTD](https://github.com/OceanographyforEveryone/OpenCTD) if you want to build a lower cost device using easily accessible materials and tools. Many thanks to Andrew Thaler, Kersey Sturdivant, and Russell Neches for providing the initial framework for the OpenCTD. 

![Original OpenCTD](https://raw.githubusercontent.com/CTDizzle/CTDizzle/master/Documentation/Images/OpenCTDVersions.jpg)
_Variations of the original OpenCTD. Photo taken by Andrew Thaler._


### Before You Get Started

This guide was written so that you can build your very own CTDizzle. If you are confused on a topic, or require additional information, please do not hesitate to contact the author.

There are likely cheaper and better sensor options out there. This guide only covers the parts outlined in the parts list. If you decide to use different sensors or parts, it is your responsibility to ensure that all parts are compatible with your setup.

It should be noted that this guide assumes that you are running everything through Windows. As such, there is no Linux or mac OS support for the MATLAB and R processing scripts at this time. Please make sure that you are able to find an equivalent program for the steps that use third-party programs.


### :+1: Why Conductivity, Temperature, and Depth?

Temperature itself is incredibly useful as so many other ocean properties and phenomena are impacted by it.
One study suggests that rockfish prefer to hang out in a certain water temperature range. Commercial trawls in Alaska and Oregon have reported a greater abundance of the fish in temperatures ranging between 4 and 7 degC ([Vestfals, 2010](http://ir.library.oregonstate.edu/xmlui/handle/1957/12047?show=full)). Many other studies show that temperature also impacts the growth rate, welfare, and reproductive potential of other marine organisms. Temperature also influences factors such as water density, pH, and how much gas seawater can hold. By monitoring ocean temperature over space and time, scientists are able to come up with connections between temperature and other aspects of our oceans.

Conductivity by itself isn't a particularly useful, but when combined with temperature and pressure through some empirical calculations, you can get values such as salinity, density, and sound velocity. Salinity is essentially the concentration of dissolved salts in the water. Salty, cold water is more dense than fresh, warm water, and this is easily seen in the Columbia River plume. During the winter, the Columbia River outputs a lot of freshwater. This freshwater can form a layer that is about 20m thick and extends almost 300km offshore ([Saldias et al, 2016](http://onlinelibrary.wiley.com/doi/10.1002/2015JC011431/full)). The density of this plume is low enough that there have been cases where gliders have become stuck between the layers!

Depth is sometimes difficult to measure. The average depth of the ocean is 4000m, with the deepest part reaching almost 11000m. That would be a long tape measure! Scientists have come up with a variety of methods for measuring depth, such as sonar measurments, satellite altimetry, and pressure readings. The CTD uses pressure to determine water depth, which is easily calculated through an empirical formula.

The CTD is the workhorse tool of oceanography. By building your own, I hope that you gain an appreciation for the science, how it is collected and used, and what it tells us about our oceans.


### The CTDizzle Mk4

This is the fourth rendition of the CTDizzle. Its construction is a little different from the original CTD, as it uses some different sensors and parts. It costs about 700 USD to build and doesn't require any tools that can't be easily found at your local hardware store. If you have all the parts and tools on hand, you should be able to build it in a weekend!

:+1: Currently, the Mk4 has been constructed using the Blue Robotics 2" and 3" watertight enclosures. Each size has its advantages and disadvantages. The 2" version is much smaller, but there isn't a lot of wiggle room within the case, so upgrades and additions are much more difficult. The 3" version has a lot of internal room, so you can use a larger battery or add another sensor, but it takes up much more space if you plan to attach the device to a ROV or crab pot. 


### Specifications
* Max Depth: 120m
* Conductivity Accuracy: <1% after calibration
* Temperature Accuracy: +/- 0.1 C
* Pressure Accuracy: +/- 100 mbar
* Max Sampling Rate: 1 Hz
* Battery Life: ~ 100 hours

Battery life ultimately depends on the battery that you use. This build uses a 3.7v 44000 mAh LiPo, but you can find larger or smaller batteries that will fit your needs. It is recommended that you stick with the 3.7v LiPo JST-PH connector family. 


## Build Instructions

### Software Setup
#### Setting Up the Arduino IDE
The Arduino Integrated Development Environment (IDE) is simple to use. It is recommended that you maintain the default directories that the Arduino IDE download wizard creates. To install Arduino…

1. Go to https://www.arduino.cc/en/main/software.
2. Select the Windows Installer version.
3. Follow the installation wizard.
4. Set up shortcuts as desired.


#### Setting up the MKRZero
The MKRZero was designed and is officially supported by Arduino. The required package does not come pre-installed with the Arduino IDE, so you will need to install it using the Boards Manager.

1. Open the Arduino IDE.
2. Navigate to Tools > Board > Board Manager
3. Search for "Arduino SAMD Boards". Select Install.
4. After it has installed, navigate to Tools > Boards. 
5. Select MKRZero.
6. Connect your MKRZero to your computer via microUSB. 
7. Navigate to Tools > Port. Select the available COM Port. 

Your MKRZero should now be upload ready. It is recommended that you keep track of which USB port you plugged the MKRZero into. That way you don't have to worry about changing the com port every time you connect it to the computer.


#### Formatting the SD Card
It is also necessary to format the microSD card that will be used to store the data. 

1. Insert the microSD card into a USB adapter and plug into a computer.
2. Navigate to Windows Explorer, right click your microUSB card and select Format.
3. Under file system, select FAT. 
4. Select Start. 
6. Your card should now be formatted. 
7. OPTIONAL: Navigate to your SD card through Windows Explorer. If desired create and additional folder to save old data. 

Another option is to install the [SD Card Formatter](https://www.sdcard.org/downloads/formatter_4/) developed by the SD Association. This application is particularly useful if you like to tinker with the Raspberry Pi.


#### Setting Up the Required Libraries
Several libraries are needed to allow the CTDizzle operating code to work. These libraries allow communication with the sensors and the use of unique commands. They can either be found within the Arduino IDE or downloaded from GitHub. Libraries native within the IDE are automatically included by the IDE and no further steps are necessary to include them. The following instructions show how to download and access the third party libraries. 

|Native Libraries|Third Party Libraries|
|:---:|:---:|
|SPI|TSYS01|
|Wire|MS5837|
|SD|SparkFunDS3234RTC|


##### TSYS01 Temperature Sensor Library
The temperature sensor requires the TSYS01 library. To access the library:
1.	Go to https://github.com/bluerobotics/BlueRobotics_TSYS01_Library.
2.	Select the Clone or download button. Click on Download Zip.
3.	Navigate to your downloads folder through Windows Explorer.
4.	Right click on the BlueRobotics_TSYS01_Library-master folder. Select extract all.
5.	Select browse.
6.	Navigate to Windows (C:) > Program Files (x86) > Arduino > libraries. Click on select folder.
7.	The TSYS01 library can now be included by the operating code.


##### MS5837 Pressure Sensor Library
The pressure sensor requires the MS5837 library. To access the library:
1.	Go to https://github.com/bluerobotics/BlueRobotics_MS5837_Library.
2.	Select the Clone or download button. Click on Download Zip.
3.	Navigate to your downloads folder through Windows Explorer.
4.	Right click on the BlueRobotics_MS5837_Library-master folder. Select extract all.
5.	Select browse.
6.	Navigate to Windows (C:) > Program Files (x86) > Arduino > libraries. Click on select folder.
7.	The MS5837 library can now be included by the operating code.


##### DeadOn RTC Library
The DeadOn RTC requires the SparkFunDS3234RTC library. To access the library:
1.	Go to https://github.com/sparkfun/SparkFun_DS3234_RTC_Arduino_Library.
2.	Select the Clone or download button. Click on Download Zip.
3.	Navigate to your downloads folder through Windows Explorer.
4.	Right click on the SparkFun_DS3234_RTC_Arduino_Library-master folder. Select extract all.
5.	Select browse.
6.	Navigate to Windows (C:) > Program Files (x86) > Arduino > libraries. Click on select folder.
7.	The SparkFunDS3234RTC library can now be included by the operating code. Note that during future uploads, the Arduino IDE may classify the DeadOn RTC library as “Uncategorized”. The library should still function even though this message appears.

If you are using different sensors, make sure to use the right libraries!


### Breadboard Testing

Tools: Soldering Iron, Hemostats, Wire Strippers, Breadboard, Third Hand
Protective Equipment: Eye Protection, Nitrile Gloves

:+1: Most of the parts are already breadboard compatible, but you will need to solder header pins to the DeadOn RTC. If you aren't familiar with soldering, take the time to practice with some header pins and protoboard. There should be enough extra. You'll use less solder than you first expect and it will happen pretty quickly. Once you think you are ready, solder some header pins to the DeadOn RTC! It isn't necessary, but if you want your solder job to be nice and shiny, you can use a soft bristle brush and some alcohol to wipe away the excess flux. 

![Picture of DeadOn RTC with header pins here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/SolderedRTC.jpg)
*DeadOn RTC with soldered headers.*

Next you need to prepare the temperature and pressure sensors. Remove the DF13 connects from each sensor. Then strip away roughly 1cm of insulation on each of the wires. Tin the ends of the wires to prevent loose strands. 

![Picture of exposed wire here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/Pressure.jpg)
*Trimmed pressure sensor wires.*

:+1: Both the temperature and pressure sensors use I2C to communicate with the MKRZero. In the final product, similar wires will be soldered to the same pin. Each device has a unique address, so the MKRZero is capable of differentiating between the two. 
After you have striped the wires, you can solder together the same colored wires of the sensors. It is recommended that you intertwine the wires to make things less messy. If you aren't confident with your soldering ability yet, feel free to practice with some other wire.

Now is the time to set things up on the breadboard!
Place the MKRZero, EC EZO, and DeadOn RTC on the breadboard. Don't forget to install the SD card and coin cell!

![Picture of setup here](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/BareBreadboard.jpg)
*Board setup before all the messy jumper wires.*

Connect everything together as outlined in the pinout guide. After you double check you connections it is time to fire it up!

![Picture of setup with jumper wires here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/MessyWires.jpg)
*Board setup with jumper wires.*


### Bench Test

Once you have the breadboard setup, connect your MKRZero to the computer and upload the MKRZero_OpCode.

Open the serial monitor (Ctrl+M). If you have everything set up correctly, you should see data printing to the screen in the form of:
Date (mm/dd/yyyy), Time (HH:mm:ss), EC (uS/cm), T (degC), P (mbar), Depth (Sketch), SAL (Sketch). 

[Picture of output.]






- The date should be representative of the date that your computer is set to. The time should be close to the time that your computer is set to, but may be behind by about 30 seconds. This is due to upload delay. If your time is drastically off or incoherent, remove the battery and power cycle the system. 

- The conductivity value should be zero. If it is not present in the output, try switching the Tx and Rx lines. Alternatively, you can change the pins in the code. Note in the above image, the EC is missing in the first line. It takes time for the EC circuit to initialize and thus is missing for the first sample.

- The temperature should be representative of the ambient temperature of the room you are performing the test in. It may be handy to have a thermometer nearby to check this. The temperature probe is factory calibrated, but if further calibration is needed, a two-point calibration is recommended.

- The pressure sensor should be spitting out values between 1000 and 1050 depending on your elevation and sensor accuracy. If you are near sea level, the value should be within a few millibars of 1020. The pressure sensor is factory calibrated, but if values appear to be drastically off (e.g. 86000 or -6000), first check your pinout connections. If still incorrect, contact the manufacturer. 


### Calibrating the Conductivity Sensor

Tools: Small Plastic Cup (x2)
Protective Equipment: Nitrile Gloves

:+1: Unlike the factory calibrated temperature and pressure sensors, the conductivity probe/circuit require a user calibration. First, you will need to leave your complete setup and calibration solutions in a temperature controlled room over night (such as a cold storage room or cafeteria refrigerator).

[Picture of calibration setup here.]

 :+1: The next morning, take your calibration procedure and computer to your setup. Follow along with the calibration procedure found in the documentation folder (in progress). Conductivity is highly dependent on temperature, so it is important that you be as precise as possible! Using the provided plots, determine the temperature of the room and corresponding conductivity value to the nearest 100 uS/cm. Don't forget to bring a parka!

After you have confirmed proper calibration of the probe, it won't need another calibration for a year. You can now cut the cable if you do not plan to implement the BNC connectors into your design. Please note that cutting the cable voids the Atlas-Scientific warranty, so it important to first test the probe to see if it works. 


### Case Construction and Potting
Once everything checks out and your breadboard tests are successful, you can begin to put the pressure case together.

#### Switch/Purge End Cap Preparation
Select one end cap and flange as your switch/purge end cap. Connect them together with the six M2 screws. Don't worry about installing the o-ring just yet. Once connected, use sandpaper to prepare the inner surface of the flange and end cap. After preparing the end cap, clean each surface with isopropyl alcohol. By scuffing up the internal surface, you are increading the bonding capacity of the urethane you will later apply.

[Picture of prepared end cap here.]

Remove the face plate from the flange. Install the switch and pressure 

[Picture of installed bulkheads here.]

#### Conductivity and Pressure Sensor End Cap

Next, do the same thing with the other end cap. The conductivity sensor has too large a diameter for the pre-drilled holes, so you will need to drill out one of the holes to 12mm diameter.

[Picture of drilled out hole here.]


After you have prepared each end cap, you can re-connect them to the flanges. Make sure everything is clean. Wrap the O-Ring grooves of the flange in masking tape to prevent any spillage from the next step.

#### Applying the Urethane

:+1: The urethane you are using is called Urethane 75a. It is specifically designed for potting of electronics and cables that are placed in seawater.

[Picture of Urethane station here.]

Prior to mixing the urethane, it is important to have your vacuum (if you are going to use one) and stand ready for use. It is recommended that you use a vacuum chamber to remove any bubbles during the curing process.

Once you have your end caps setup, make sure that the wires are out of the way. Mix the two urethane components together in a 1:1 ratio. Start by mixing 1 cup of each at a time. Here are some (videos)[https://www.masterbond.com/resources/video-library?tid=354] on how to mix and apply two part epoxies.

[Picture of mixture here.]

Next, pour the urethane into each end cap until it reaches the brim of the flange. Turn on the vacuum chamber for about three minutes. Remove any remaining bubbles with a toothpick.

[Picture of urethane and end caps here.]

Allow to cure for 24 hours. 


### Protoboard Soldering

While your end caps are curing, you can begin to solder the electrical components together.

First, orient the MKRZero on the protoboard so that the SD card faces the switch end cap. Below that, install the RTC, and below the RTC, install the EC EZO.  Using 22 AWG solid core wire, solder wires to the corresponding pins of the MKRZero, RTC, and EC EZO. It is recommended that you test this setup in case there are any ground faults.

[Picture of main protoboard here.]

It isn't necessary, but installing a quick disconnect for the sensors helps when you need to reprogram, charge, or pull data from the protoboard. If desired, you can also solder the temperature and pressure JST plugs to the MKRZero. Make a note of which wire goes where, because after your urethane is done curing, you will want to make sure you have the right wires hooked up!

[Picture of main protoboard with JST here.]

Now is the time to decide if you want to cut the EC probe cable. Leaving the BNC connector has a couple advantages. It makes it easier to disconnect from the protoboard and there is no confusion over the probe communication. A downside to this is that there is a lot of excess cable. There is probably room for this excess cable in the internal space, but it may be cramped. 

- If you decide to cut the cable, follow the Atlas-Scientific guide to cable cutting. Recall that Atlas-Scientific will not accept returns of probes with cut cables. Once cut, solder one half of the 2-pin JST connector to the probe leads, and the other half to the corresponding pins on the EC EZO. 


#### Switch Cable Extension
In order to externally turn off the OpenCTD, we need to install a switch. It is not recommended that you cut the battery cables to install the switch, as this may have an impact on the charging of the battery. Instead, use a JST extension cable to tie the switch into. First, cut the ground line of the extension cable at roughly the midpoint. Solder a switch lead onto each end of the ground line. 
- Take care when soldering, as the wire will heat up quickly when maintaining contact with the soldering iron. This may result in deformation of the JST connector and you will not be able to use it. 

[Picture of extension here.]


### Final Case Construction
After you have soldered everything and tested the data output, you can finish constructing the case.

1. Ensure the flanges are clean. Grease the flange O-rings for the sensor end cap and install them.
2. Install the sensor end cap onto the acrylic tube. 
3. Sort the wires.
4. Connect the MKRZero to the battery via the JST extension. Ensure that the switch is off or removed. 
5. Place a desiccant pack in the pressure case. 
6. Connect your sensors to the protoboard. Place the protoboard and battery in the tube. It is recommended that you tape the battery to the protoboard. 
7. Pack the aluminum tube with some sort of packing material if there is some play in the internal wiring and components. 
8. Remove the purge plug from the switch and vent end cap. Install the switch and vent end cap on the acrylic tube.
9. Reinstall the switch and plug. 
10. Turn on the device and look for the LEDs on the EC EZO. 

[Picture of completed device here.]

## Corrosion
:+1: The screws used in the end caps are made of 316 SS and the main body of the unit is made of anodized aluminum.
When two dissimilar metals interact in seawater, galvanic corrosion can occur. The metal on the lower end of the galvanic scale (aluminum in this case) will begin to corrode after an extended period of time. Cathodic protection is one method to mitigating the corrosion of the end caps. This can be done by installing an anode (commonly made of zinc). 


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
1. Turn off the CTD.
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
:+1:


#### Yaquina Bay

:+1:

The OpenCTD is capable of observing changes over several days. The pressure sensor is capable of rectifying changes is tidal height and changes in temperature and salinity can be seen to follow. 

Yaquina Bay is an excellent place to test the OpenCTD. Under the right conditions, the device can be used find the depth of the salt wedge, or the extent of the river plume in the bay. 

Every couple of months students from Oregon State University will sample from the Yaquina Bay Bridge up to Toledo during various stages of the tidal cycle. The Oregon Coast Aquarium also continuosly collects salinity and temperature data on the water that is pumped in from the bay. 


#### The Oregon Shelf

:+1:


## Index of Jargon

In no particular order...

|Term|Description|
|:---:|:---|
|BNC|[Bayonet Neill-Concelmen Connector](https://en.wikipedia.org/wiki/BNC_connector). Typically the terminator on a coaxial cable|
|SPI|[Serial Peripheral Interface] (https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus). A synchronous serial communication interface typically used in short distance communication. One device is considered the master device and the others the slave. The slave select (SS) pin allows the microcontroller to select which device it talks to.|
|I2C|[Inter-Integrated Circuit](https://en.wikipedia.org/wiki/I%C2%B2C). Often pronouced I-squared-C or I-two-C. It only uses two lines for communication but is communicates slower than SPI|
|TX|Serial transmitter on a device. |
|RX|Serial reciever on a device. |
|Absolute Pressure|The OpenCTD measures absolute pressure. In the reported values, the atmospheric pressure is included. If your OpenCTD reads 1100 mbar, that does not mean it is at ~11 meter depth, but more likely ~1m assuming your atmospheric pressure is 1000 mbar.|
|Gauge Pressure| To get gauge pressure, simply subtract atmospheric pressure from the absolute pressure.|





	
