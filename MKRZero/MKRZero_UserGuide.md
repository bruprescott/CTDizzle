# CTDizzle User Manual

:+1: This emoji indicates sections that are directed toward the high school students I will be working with during my research project. Some of the sections may have information that is related to the Oregon coast. Updates will be made often as new information, methods, and procedures are discovered.

## Other Links
[Parts List](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/MKRZero_Parts_List.md)

[Code](https://github.com/CTDizzle/CTDizzle/tree/master/MKRZero/ArduinoFiles)

[Pinout Guide](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/MKRZero_Pinouts.md)

[Resources and Literature](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Resources.md)

[EC Cal Procedure](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/EC_Cal_Procedure.docx)


## Contents

1. [Introduction](#introduction)
	- [Before You Get Started](#before-you-get-started)
	- [Why Conductivity, Temperature, and Depth?](#why-conductivity,-temperature,-and-depth?)
	- [The CTDizzle Mk4](#the-ctdizzle-mk4)
	- [Specifications](#specifications)
2. [Build Instructions](#build-instruction)
	- [Software Setup](#software-setup)
		- [Setting Up the Arduino IDE](#setting-up-the-arduino-ide)
		- [Setting Up the Arduino MKRZero](#setting-up-the-arduino-mkrzero)
		- [Formatting the SD Card](#formatting-the-sd-card)
		- [Setting Up the Required Libraries](#setting-up-the-required-libraries)
	- [Breadboard Testing](#breadboard-testing)
		- [Calibrating Conductivity](#calibrating-conductivity)
	- [Case Construction and Potting](#case-construction-and-potting)
		- [Switch End Cap](#switch-end-cap)
		- [Conductivity/Temperature End Cap](#conductivity/temperature-end-cap)
		- [Applying the Urethane](#applying-the-urethane)
	- [Completing the Circuit](#completing-the-circuit)
		- [Switch Cable](#switch-cable)
	- [Final Case Construction](#final-case-construction)
3. [Corrosion](#corrosion)
4. [Pre-deployment Procedure](#pre-deployment-procedure)
5. [Deployment Procedure](#deployment-procedure)
6. [Recovery Procedure](#recovery-procedure)
7. [Battery Charging Procedure](#battery-charging-procedure)
8. [Data Download and Analysis](#data-download-and-analysis)
	- [Accessing and Plotting the Data](#accessing-and-plotting-the-data)

## Introduction

Oceanographic equipment is often expensive and inaccessible for students and citizen scientists. The OpenCTD is a relatively cheap, buildable device that allows individuals to easily collect conductivity, temperature, and pressure data. It is still being refined and doesn't quite produce research quality data, but in its current state it is a great tool for teaching and learning. 

Check out the [original OpenCTD](https://github.com/OceanographyforEveryone/OpenCTD) if you want to build a lower cost device using easily accessible materials and tools. Many thanks to Andrew Thaler, Kersey Sturdivant, and Russell Neches for providing the initial framework for the OpenCTD. 

![Original OpenCTD](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/OpenCTDVersions.jpg)
_Variations of the original OpenCTD. Photo taken by Andrew Thaler._


### Before You Get Started

This guide was written so that you can build your very own CTDizzle. If you are confused on a topic, or require additional information, please do not hesitate to contact the author if you are unable to find what you need in your own research. 

There are likely cheaper and better sensor options out there. This guide only covers the parts outlined in the parts list. If you decide to use different sensors or parts, it is your responsibility to ensure that all parts are compatible with your setup.

It should be noted that this guide assumes that you are running everything through Windows. As such, there is no Linux or macOS support for the MATLAB and R processing scripts at this time. Please make sure that you are able to find an equivalent program or script modification for the steps that use third-party programs.


### Why Conductivity, Temperature, and Depth?

:+1: Temperature itself is incredibly useful as so many other ocean properties and phenomena are impacted by it.
One study suggests that rockfish prefer to hang out in a certain water temperature range. Commercial trawls in Alaska and Oregon have reported a greater abundance of the fish in temperatures ranging between 4 and 7 degC ([Vestfals, 2010](http://ir.library.oregonstate.edu/xmlui/handle/1957/12047?show=full)). Many other studies show that temperature also impacts the growth rate, welfare, and reproductive potential of other marine organisms. Temperature also influences factors such as water density, pH, and how much gas seawater can hold. By monitoring ocean temperature over space and time, scientists are able to come up with connections between temperature and other aspects of our oceans.

:+1: Conductivity by itself isn't a particularly useful, but when combined with temperature and pressure through some empirical calculations, you can get values such as salinity, density, and sound velocity. Salinity is essentially the concentration of dissolved salts in the water. Salty, cold water is more dense than fresh, warm water, and this is easily seen in the Columbia River plume. During the winter, the Columbia River outputs a lot of freshwater. This freshwater can form a layer that is about 20m thick and extends almost 300km offshore ([Saldias et al, 2016](http://onlinelibrary.wiley.com/doi/10.1002/2015JC011431/full)). The density of this plume is low enough that there have been cases where gliders have become stuck between the layers!

:+1: Depth is sometimes difficult to measure. The average depth of the ocean is 4000m, with the deepest part reaching almost 11000m. That would be a long tape measure! Scientists have come up with a variety of methods for measuring depth, such as sonar measurments, satellite altimetry, and pressure readings. The CTD uses pressure to determine water depth, which is easily calculated through an empirical formula.

:+1: The CTD is the workhorse tool of oceanography. By building your own, I hope that you gain an appreciation for the science, how it is collected and used, and what it tells us about our oceans.


### The CTDizzle Mk4

This is the fourth rendition of the CTDizzle. Its construction is a little different from the original CTD, as it uses some different sensors and parts. It costs about 700 USD to build and doesn't require any tools that can't be easily found at your local hardware store. If you have all the parts and tools on hand, you should be able to build it in a weekend!

:+1: The primary difference between the Mk3 and Mk4 is the transition from the Qduino Mini to the MKRZero. The MKRZero boasts significantly more storage space, so sketches can be much more complex. With the addition of the MKRZero, the microSD module is no longer needed as the MKRZero has an onboard SD module. 

:+1: The Mk4 can be built using the 2" or 3" watertight enclosures. Each type has its advantages and disadvantages. The 2" version is much more compact and is easily attached to small platforms such as crab pots or ROVs, however, internal space is limited so battery life is much less and adding extra components is unlikely. The 3" version has much more internal space than the 2" version, and as such can hold a larger battery making extended field tests a possibility. You can also add other sensors if desired, so long as the MKRZero can support additions. The downside to the 3" version is that it is much larger. 


### Specifications
* Max Depth: 120m
* Conductivity Accuracy: <1% after calibration
* Temperature Accuracy: +/- 0.1 C
* Pressure Accuracy: +/- 100 mbar
* Max Sampling Rate: 1 Hz
* Battery Life: ~ 100 hours (3.7v 4400 mAh)

Battery life ultimately depends on the battery that you use. A 3.7 6000mAh LiPo will give you approximately 160 hours of battery life when sampling at 1 Hz. It is recommended that you stick with the 3.7v LiPo JST-PH connector family. 


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

|Tools|Protective Equipment|
|:---:|:---:|
|Soldering Iron|Eye Pro|
|Hemostats|Nitrile Gloves|
|Wire Strippers|
|Breadboard|
|Third Hand|

:+1: Most of the parts are already breadboard compatible, but you will need to solder header pins to the DeadOn RTC. If you aren't familiar with soldering, take the time to practice with some header pins and protoboard. It is recommended that you use hemostats to cleanly break the header pins. There should be enough extra. You'll use less solder than you first expect and it will happen pretty quickly. Once you think you are ready, solder some header pins to the DeadOn RTC! It isn't necessary, but if you want your solder job to be nice and shiny, you can use a soft bristle brush and some alcohol to wipe away the excess flux. 

:+1: If you mess up, don't forget that you will have a solder sucker on hand!

[SparkFun's Guide to Soldering Through-Holes](https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering)

![Picture of DeadOn RTC with header pins here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/SolderedRTC.jpg)
*DeadOn RTC with soldered headers.*

Next you need to prepare the temperature and pressure sensors. Remove the DF13 connects from each sensor. Then strip away roughly 1cm of insulation on each of the wires. Tin the ends of the wires to prevent loose strands. 

![Picture of exposed wire here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/Pressure.jpg)
*Trimmed pressure sensor wires.*

:+1: Both the temperature and pressure sensors use I2C to communicate with the MKRZero. In the final product, similar wires can be soldered to the same pin. Each device has a unique address, so the MKRZero is capable of differentiating between the two. 
After you have striped the wires, you can connect them together during the bench test phase. It is recommended that you intertwine the wires to make things less messy. Don't forget to tin the wire ends to prevent loose strands. If you aren't confident with your soldering ability yet, feel free to practice with some other wire.

Now is the time to set things up on the breadboard!
Place the MKRZero, EC EZO, and DeadOn RTC on the breadboard. Don't forget to install the SD card and coin cell!

![Picture of setup here](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/BareBreadboard.jpg)
*Board setup before all the messy jumper wires.*

Connect everything together as outlined in the pinout guide. After you double check you connections it is time to fire it up!Connect your MKRZero to the computer and upload the MKRZero_OpCode.

![Picture of setup with jumper wires here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/MessyWires.jpg)
*Board setup with jumper wires.*

Open the serial monitor (Ctrl+Shift+M). If you have everything set up correctly, you should see data printing to the screen in the form of:
Date (mm/dd/yyyy), Time (HH:mm:ss), Conductivity (uS/cm), Temperature (degC), Absolute Pressure (mbar), Depth (m), Salinity (PSU) 

![Picture of output.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/SerialMonitorOutput.PNG)
*Date,Time,EC,T,P,Depth,Salinity*

The date should be representative of the date that your computer is set to. The time should be close to the time that your computer is set to, but may be behind by about 30 seconds. This is due to upload delay. If your time is drastically off or incoherent, remove the battery and power cycle the system. Note that the autotime function will need to be commented out of the code for the final sketch upload or else your CTD will revert to the same time on a power cycle.

The conductivity value should be zero. If it is not present in the output, try switching the Tx and Rx lines. Alternatively, you can change the pins in the code. Note in the above image the EC is reporting a nonzero value due to noise. Noisiness can be test by placing the probe in some tap water. 

The temperature should be representative of the ambient temperature of the room you are performing the test in. It may be handy to have a thermometer nearby to check this. The temperature probe is factory calibrated, but if further calibration is needed, a two-point calibration is recommended.

The pressure sensor should be spitting out values between 1000 and 1050 depending on your elevation and sensor accuracy. At sea level, atmospheric pressure is around 1013 mbar. The pressure sensor is factory calibrated, but if values appear to be drastically off, first check your pinout connections. If still incorrect, contact the manufacturer. 

Depth is sketch-derived using the empirical equation outlined in [UNESCO Marine 44](http://unesdoc.unesco.org/images/0005/000598/059832eb.pdf). For the CTDizzle, there is no consideration for latitude, so gravity is assumed to be 9.806 m/s^2. It is also assumed that atmospheric pressure is 1013 mbar.

Salinity is also sketch-derived per the same paper. 

Don't forget to check the output on the SD card! 
Opening up the SD card in windows explorer should give you a window similar to this..

![USB](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/USBPopup.PNG)
*Note that a good way to see if you collected data is to look at the file size. Files with ~5 kb are representative of a deployment that lasted a few minutes. The file with ~4000 kb is representative of a deployment that lasted about 24 hours.* 

Opening up one of the .csv files will give you...

![CSV](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/CSVOutput.PNG)
*The data format is the same as the format in the serial monitor. This was opened in MS Excel/*

### Calibrating Conductivity

|Tools|Protective Equipment|
|:---:|:---:|
|Small Plastic Cup|Nitrile Gloves|

:+1: Unlike the factory calibrated temperature and pressure sensors, the conductivity kit requires a user calibration. First, you will need to leave your complete setup and calibration solutions in a temperature controlled room over night (such as a cold storage room or cafeteria refrigerator).

![Picture of calibration setup here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/CalSetup.jpg)
*Super high-tech calibration setup in a cold room.*

 :+1: The next morning, take your calibration procedure and computer to your setup. Follow along with the calibration procedure found in the documentation folder Conductivity is highly dependent on temperature, so it is important that you be as precise as possible! Using the provided plots, determine the temperature of the room and corresponding conductivity value to the nearest 100 uS/cm. Don't forget to bring a parka!

After you have confirmed proper calibration of the probe, it won't need another calibration for a year. You can now cut the cable if you do not plan to implement the BNC connectors into your design. Please note that cutting the cable voids the Atlas-Scientific warranty, so it important to first test the probe to see if it works. 


### Case Construction and Potting
Once everything checks out and your breadboard tests are successful, you can begin to put the pressure case together.

|Tools|Protective Equipment|
|:---:|:---:|
|Plastic Cups|Eye Pro|
|Plastic Stir Rod|Nitrile Gloves|
|Sand Paper|Safety Mask|
|Tape|
|Round File|


#### Switch End Cap 

Designate one end cap and flange set as your switch/pressure sensor (S/P) end cap and the other your conductivity/temperature (C/T) end cap.

For each set, connect the two pieces together using the six M2 screws. Don't worry about installing the O-Ring just yet. Once connected, use sandpaper to prepare the inner surface of each flange and end cap set. Abrasion of the surface will allow the urethane you will apply later to bond more readily to the metal surface. Use a low grit sandpaper to remove anodization until you begin to see bare aluminum.

Here are some [videos](https://www.masterbond.com/resources/video-library?tid=354) on how to mix and apply two part epoxies.

![Picture of prepared end cap here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/2.PNG)
*Flange with the internal side abraded.*

Remove the face plate from the flange. Use isopropyl alcohol to clean the surface thoroughly. Install the switch and pressure 

![Picture of installed bulkheads here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/1.PNG)
*Picture of the pressure and switch bulkheads installed.*

#### Conductivity/Temperature End Cap

Do the same thing with the other end cap. The conductivity sensor has too large a diameter for the pre-drilled holes, so you will need to drill out one of the holes to 15/32". It may be a tight fit for the probe, so use a round file to make it the right size. Once you have the proper hole size, insert the probe so that it sticks out of the end cap approximately 2". To keep it in place, rig up a stand that will hold the probe in the right spot, or super glue it into place from the outside. 

After you have prepared each end cap, you can re-connect them to the flanges. Make sure everything is clean. Wrap the O-Ring grooves of the flange in tape to prevent any spillage getting into the grooves during the next step.

#### Applying the Urethane

:+1: The urethane you are using is called Urethane 75a. It is specifically designed for potting of electronics and cables that are placed in seawater. It is important to use plastic tools during mixing so as not to introduce moisture to the urethane. Using wood or paper mixing tools runs the risk of upsetting the curing process. 

![Picture of Urethane here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/5.PNG)
*Blurry picture of the urethane bottles.*

Pour equal amounts of each urethane component into seperate cups. You should use a minimum of three ounces of each. Using less may not be enough to generate the exothermic reaction needed for the curing process. Pour two components into one cup. Slowly mix with the stirring stick for two minutes and take care not to introduce bubbles. You will have five total minutes of working time. At around three minutes, the mixture will become thicker and more difficult to pour. Mixing too quickly can generate too much heat and reduce your overall working time. 

To get rid of bubbles, you can also use a vacuum chamber.

Here are some [videos](https://www.masterbond.com/resources/video-library?tid=354) on how to mix and apply two part epoxies.

![No Urethane](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/7.PNG)
*Conductivity and temperature sensors ready to be potted.*

Next, pour the urethane into each end cap until it reaches the brim of the flange. 

![Picture of urethane and end caps here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/6.PNG)
*Poured urethane.*

![Pic2](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/4.PNG)
*Poured urethane.*


Allow to cure for 24 hours. 


### Completing the Circuit

|Tools|Protective Equipment|
|:---:|:---:|
|Soldering Iron|Eye Pro|
|Hemostats|Nitrile Gloves|
|Wire Strippers|
|Third Hand|

While your end caps are curing, you can begin to solder the electrical components together.

:+1: If using the 2" version of the pressure case, soldering everything to a protoboard may make things inside the case a little cramped. It might be easier to solder components directly together. You will need to remove the headers already installed on the MKRZero and the DeadOn RTC. Use the provided solder sucker to make removal of the headers easier. You'll also have to bend the headers on the EC EZO to allow easier soldering of the pins. 

![Get bent](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/EZOBend.jpg)
*Bent pins of the EC EZO.*

It isn't necessary, but installing a quick disconnect for the sensors helps when you need to reprogram, charge, or pull data from the protoboard. If desired, you can also solder the temperature and pressure JST plugs to the MKRZero. Make a note of which wire goes where, because after your urethane is done curing, you will want to make sure you have the right wires hooked up!

Cut the EC probe cable, leaving approximately six inches of cable. Strip the wires and tin the leads.

![Probe Leads](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/ProbeLeads.jpg)
*Cut EC probe cable.*

Note that Atlas-Scientific no longer covers probe faults after you cut the cable. 

Solder everything together as described by the pinout guide. If you want to avoid using a ton of heat shrink, you can use UY2 cold splice connectors. There is no specific orientation for the EC probe leads to the EC EZO.

![Picture of main protoboard with JST here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/CrappyWiring.PNG)
*Mess of wires.*

#### Switch Cable 
In order to externally turn off the CTDizzle, we need to install a switch. It is not recommended that you cut the battery cables to install the switch, as this may have an impact on the charging of the battery. Instead, use a JST extension cable to tie the switch into. First, cut the ground line of the extension cable at roughly the midpoint. Solder a switch lead onto each end of the ground line. 
- Take care when soldering, as the wire will heat up quickly when maintaining contact with the soldering iron. This may result in deformation of the JST connector and you will not be able to use it. Alternatively, you can use cold splice connectors.

![Picture of Switch cable here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/SwitchCable.jpg)
*Example of a switch cable with cold splice connectors.*

### Final Case Construction

|Tools|Protective Equipment|
|:---:|:---:|
|O-Ring Pick|Nitrile Gloves|
|Hemostats|
|2mm Hex Wrench|

After you have soldered everything and tested the data output, you can finish constructing the case.

1. Ensure the flanges are clean. Grease the flange O-rings for the sensor end cap and install them.
2. Install the C/T end cap into the tube.
3. Sort the wires, board, and battery.
4. Connect the MKRZero to the battery via the JST extension. Ensure that the switch is off or removed. 
5. Place a desiccant pack in the pressure case. 
6. Connect your sensors to the protoboard. Place the protoboard and battery in the tube. It is recommended that you tape the battery to the protoboard. 
7. Pack the aluminum tube with some sort of packing material if there is some play in the internal wiring and components. 
8. Connect the pressure and switch leads.
9. Turn on the device using the switch. Note that the MKRZero does not turn on the LEDs when using battery power.
10. Turn off the device. Pull the card and check to see if a file is created and data is being output.

![Picture of completed device here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/Complete.jpg)
*The CTDizzle Mk4.*

## Corrosion
:+1: The screws used in the end caps are made of 316 SS and the main body of the unit is made of aluminum.
When two dissimilar metals interact in seawater, galvanic corrosion can occur. The metal on the lower end of the galvanic scale (aluminum in this case) will begin to corrode after an extended period of time. Cathodic protection is one method to mitigating the corrosion of the end caps. This can be done by installing an anode (commonly made of zinc). 

## Predeployment Procedure
The deployment plan of your OpenCTD plays a role in the sampling regime.
- If you plan to take profiles, it should be set to sample as frequently as possible.
- If you plan to leave the OpenCTD in the same location for several hours or days, it should be set to sample every minute to fifteen minutes. Doing this will increase the battery life. Another way to increase the battery life is by turning off the EC EZO LEDs. Instructions on how to do this can be found in the EZ EZO Datasheet.

## Deployment Procedure
The device should be fully assembled and the proper sampling regime selected prior to reaching the study site. 
1.	Confirm all sensors, plugs, bulkheads, and end caps are secure. 
2.	Remove any sensor covers on the conductivity, temperature, and pressure sensors.
3.	Turn the external switch clockwise until it can turn no further. The unit should now turn ON. 

If profiling with the unit, it is suggested that it be left in the top few meters of the water column for approximately five minutes to allow for equilibrium. Once ready to profile, bring the unit to just below the surface, and allow it to descend at a rate around 0.25 m/s (~1 fathom every 10 seconds). The unit is only capable of sampling at a maximum of 1 Hz, so the slower the descent the better. 

If planning to leave the unit at a particular site for an extended period of time, it is recommended that the user ensure that the device is properly secured and **ON** prior to leaving the site. 

## Recovery Procedure
1.	After recovering the unit, turn the main switch counter-clockwise until the EC EZO LEDs turn off (usually ½ to 1 rotation). Do not turn it any further or you may risk introducing water to the internals.
2.	Spray the unit down with fresh water if possible. 
3.	If biofouling has accrued on the device, carefully remove the tape used to protect the case. If tape was not used to prevent biofouling, carefully use a soft bristle brush or plastic paint scraper to remove any fouling on the case. 

For the sensors, use a soft bristle toothbrush or sponge to remove any biofouling. **Do not use a brush on the conductivity probe head.** If biofouling in the EC probe sensing area is non-compliant, you can place the probe in a 5% HCl solution and then use cotton swabs to remove obstructions. You can also try using freshwater or canned-air.

4.	Dry the device.
5.	Replace all sensor caps.

If the unit is primarily used for profiling, the device is ready to go once the user decides to collect data again. If there is concern that the battery may be low, refer to the Battery Charging Procedure.

If another stationary deployment is planned, the battery will likely need to be charged or replaced. This requires the user to open up the device.

## Battery Charging Procedure
1. Turn off the CTD.
2. Remove the switch/purge end cap. 
3. Remove the main electronics board and disconnect the battery switch cable.
4. Plug the battery directly into the MKRZero.
5. Connect the MKRZero to your computer or compatible wall outlet.

The MKRZero has the ability to charge a single-cell lithium ion battery when connected to a computer or microUSB outlet adapter. Simply plug in the battery to the MKRZero and connect the unit to a computer via microUSB. An orange LED should appear, indicating that the battery is charging. Even though the battery has a built in overcharge and damage prevention circuit, it is important that you do not charge your battery for too long.

It is recommended that you do not charge the battery through the JST switch cable.


## Data Download and Analysis

### Accessing and Plotting the Data
Currently, the user is required to open the device and pull the microSD card to access the data. **Make sure the device is dry before continuing.** Take care when removing the end cap, as it is important to keep the O-rings clean. 

1. Connect the microSD card to your computer using an adapter.
2. Transfer the RAWCTD files you are interested in to your computer. It may be necessary to open these to check for dates and times. One way to differentiate between actual data and a test file is the file size.
3. Save all the files on the SD card to a seperate folder on the SD card labeled "Old Data".
4. There are several methods to process and analyze the data...
  - Through the provided MATLAB script.
  - Through the provided R script.
  - Through the provided Microsoft Excel spreadsheet (in progress).
  - Through your processing program of choice. RAWCTD files are comma-seperated.
  
5. Once you are finished looking at the data, delete the RAWCTD files in the main directory of the SD card. This keeps things from getting cluttered. 

6. Reinstall the microSD card and end cap. If you think the O-rings look a little dirty, clean and apply silicone grease before continuing. 

#### Downcast vs Upcast (For Profile Deployments)

For near real-time data, Sea-Bird recommends that you look at the data that is collected while the device is travelling down the water column (downcast). This is so that the body of an instrument does not inhibit the flow of water through the sensors or induce mixing that may result in misleading values. 
