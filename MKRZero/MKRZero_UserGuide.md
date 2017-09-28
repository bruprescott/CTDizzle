# CTDizzle User Manual

## 09/27/17 Note to THS
I forgot to grab the right spare parts, so you may have to wait on the instructions for soldering the final electronics package. In the mean time, you can desolder the female header pins on the MKRZero and solder some male header pins in place. If everyone has the male headers installed on the MKRZero, we can begin soldering things together as a group on Thursday (09/28/17). If you have difficulty getting the solder to melt when desoldering, first add more solder. You can always use the desoldering tool or solder wick to clean up afterward. 

If you decide to try to begin soldering everything together, just remember to follow to pinout guide. You want to think about how the wire, solder, and pins connect and if you are soldering the right pins together. You can test the completeness of your wiring by using the connectivity function on a multimeter.

Another thing people can do is begin to abrade the inside of the end caps and flanges (with the provided sandpaper or a dremel). If you do this, you basically want to remove the anodization on the metal until you see bare aluminum. DO NOT USE SANDPAPER ON THE O-RING GROOVES.


## THS Checklist

*Not in any particular order.*

|Task|Complete By|Check|
|:---:|:---:|:---:|
|Header Soldering|Sept. 18|X
|SD Card Formatting|Sept. 22|X
|Arduino Software Setup|Sept. 22|X
|Breadboard Testing|Sept. 26|X
|Breadboard Test Data Check|Sept. 27|X
|Conductivity Calibration|Sept. 29| This can be done at the end.
|Switch Cable|Sept. 29|This can be done at the end.
|Desolder Female Headers on MKRZero|Oct. 3|
|Solder Male Headers on MKRZero|Oct. 3|
|Sensors Installed in End Caps|Oct. 3
|End Cap Holes Drilled|Oct. 5|
|End Cap Potting|Oct. 9|
|Protoboard Soldering|Oct. 10|
|Protoboard Data Check|Oct. 10|
|Final Case Construction|Oct.23|
|Battery Charge|Oct. 24|
|Final Data Check|Oct. 24|
|Test Deployment|TBD|


## Links (THS: LOOK HERE FOR MORE INFORMATION ON PARTS AND PROCEDURES)
[Parts List](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/MKRZero_Parts_List.md)

[Code](https://github.com/CTDizzle/CTDizzle/tree/master/MKRZero/ArduinoFiles)

[Pinout Guide](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/MKRZero_Pinouts.md)

[Resources and Literature](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Resources.md)

[EC Cal Procedure](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/EC_Cal_Procedure.docx)

[Data Processing](https://github.com/CTDizzle/CTDizzle/tree/master/Data%20Processing)

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
		- [Switch End Cap](#switch/presure-end-cap)
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

This guide was written so that you can build your very own CTDizzle. If you are confused on a topic, or require additional information, please do not hesitate to contact Ian Black (blackia@oregonstate.edu) if you are unable to find what you need in your own research. 

There are likely cheaper and better sensor options out there. This guide only covers the parts outlined in the parts list. If you decide to use different sensors or parts, it is your responsibility to ensure that all parts are compatible with your setup.

It should be noted that this guide assumes that you are running everything through Windows. As such, there is no Linux or macOS support for the MATLAB and R processing scripts at this time. Please make sure that you are able to find an equivalent program or script modification for the steps that use third-party programs.


### Why Conductivity, Temperature, and Depth?

Temperature itself is incredibly useful as so many other ocean properties and phenomena are impacted by it.
One study suggests that rockfish prefer to hang out in a certain water temperature range. Commercial trawls in Alaska and Oregon have reported a greater abundance of the fish in temperatures ranging between 4 and 7 degC ([Vestfals, 2010](http://ir.library.oregonstate.edu/xmlui/handle/1957/12047?show=full)). Many other studies show that temperature also impacts the growth rate, welfare, and reproductive potential of other marine organisms. Temperature also influences factors such as water density, pH, and how much gas seawater can hold. By monitoring ocean temperature over space and time, scientists are able to come up with connections between temperature and other aspects of our oceans.

Conductivity by its lonesome isn't a particularly useful, but when combined with temperature and pressure through some empirical calculations, you can get values such as salinity, density, and sound velocity. Salinity is essentially the concentration of dissolved salts in the water. Salty, cold water is more dense than fresh, warm water, and this is easily seen in the Columbia River plume. During the winter, the Columbia River outputs a lot of freshwater. This freshwater can form a layer that is about 20m thick and extends almost 300km offshore ([Saldias et al, 2016](http://onlinelibrary.wiley.com/doi/10.1002/2015JC011431/full)). The density of this plume is low enough that there have been cases where gliders have become stuck between the layers!

Depth is sometimes difficult to measure. The average depth of the ocean is 4000m, with the deepest part reaching almost 11000m. That would be a long tape measure! Scientists have come up with a variety of methods for measuring depth, such as sonar measurments, satellite altimetry, and pressure readings. The CTD uses pressure to determine water depth, which is easily calculated through an empirical formula.

The CTD is the workhorse tool of oceanography. By building your own, I hope that you gain an appreciation for the science, how it is collected and used, and what it tells us about our oceans.


### The CTDizzle Mk4

This is the fourth rendition of the CTDizzle. Its construction is a little different from the original OpenCTD, as it uses some different sensors and parts. It costs about 700 USD to build and doesn't require any tools that can't be easily found at your local hardware store. If you have all the parts and tools on hand, you should be able to build it in a weekend!

![Versions](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/Versions.jpg)
*Left to Right: CTDizzle Mk1, Mk3, and Mk4. The Mk2 is currently being used as a doorstop*


#### Specifications
* Max Depth: 120m
* Conductivity Accuracy: <1% after calibration
* Temperature Accuracy: +/- 0.1 C
* Pressure Accuracy: +/- 100 mbar
* Max Sampling Rate: 1 Hz
* Battery Life: ~ 60 hours sampling at 1 Hz (3.7v 2200 mAh)

Battery life ultimately depends on the battery that you use. It is recommended that you stick with the 3.7v LiPo JST-PH connector family. 


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


##### TSYS01 Temperature and MS5837 Pressure Sensor Libraries
The temperature sensor requires the TSYS01 library. The pressure sensor requires the MS5837 library. To access the libraries:
1. In the Arduino IDE, navigate to Sketch > Include Library > Manage Libraries. 
2. In the search bar, type "BlueRobotics".
3. Click on the BlueRobotics TSYS01 Library. Select Install.
4. Click on the BlueRobotics MS5837 Library. Select Install.
5. These libraries are now automatically included when using the operating code.


##### DeadOn RTC Library
The DeadOn RTC requires the SparkFunDS3234RTC library. To access the library:
1.	Go to https://github.com/sparkfun/SparkFun_DS3234_RTC_Arduino_Library.
2.	Select the Clone or download button. Click on Download Zip.
3. 	In the Arduino IDE, navigate to Sketch > Include Library > Add .ZIP Library.
4. 	Go to Downloads. Select the SparkFun_DS3234_RTC_Arduino_Library-master folder.
5. 	The DeadOn RTC library is now available for use. Note that during future uploads, the Arduino IDE may classify the DeadOn RTC library as “Uncategorized”. The library should still function even though this message appears.

If you are using different sensors, make sure to use the right libraries!


### Breadboard Testing

|Tools|Protective Equipment|
|:---:|:---:|
|Soldering Iron|Eye Pro|
|Hemostats|Nitrile Gloves|
|Wire Strippers|
|Breadboard|
|Third Hand|

Most of the parts are already breadboard compatible, but you will need to solder header pins to the DeadOn RTC. If you aren't familiar with soldering, take the time to practice with some header pins and protoboard. It is recommended that you use hemostats or tweezers to cleanly break the header pins. You'll use less solder than you first expect and it will happen pretty quickly. Once you think you are ready, solder some header pins to the DeadOn RTC! It isn't necessary, but if you want your solder job to be nice and shiny, you can use a soft bristle brush and some alcohol to wipe away the excess flux. 

Here is [SparkFun's Guide to Soldering Through-Holes](https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering) if you need a tutorial.

![Picture of DeadOn RTC with header pins here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/SolderedRTC.jpg)
*DeadOn RTC with soldered headers.*

Next you need to prepare the temperature and pressure sensors. Remove the DF13 connects from each sensor. Then strip away roughly 1cm of insulation on each of the wires and tin the ends to prevent loose strands.

![Picture of exposed wire here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/Pressure.jpg)
*Trimmed pressure sensor wires.*

Both the temperature and pressure sensors use I2C to communicate with the MKRZero and share the same pinouts. Each device has a unique address, so the MKRZero is capable of differentiating between the two. For the bench testing phase, it is okay to connect similar wires with a single alligator clip.

Now is the time to set things up on the breadboard!
Place the MKRZero, EC EZO, and DeadOn RTC on the breadboard. Don't forget to install the SD card and coin cell!

![Picture of setup here](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/BareBreadboard.jpg)
*Board setup before all the messy jumper wires.*

Connect everything together as outlined in the pinout guide. Remember that VCC in this scenario is 3.3v. Under no circumstances should you connect the temperature sensor, pressure sensor, or DeadOn RTC to the 5v supply on the MKRZero. You will likely fry the electronics, and then you would be out ~$144! 

Here is the [Sparkfun Guide to Using a Breadboard](https://learn.sparkfun.com/tutorials/how-to-use-a-breadboard).

Here is the [SparkFun Guide to Circuitry](https://learn.sparkfun.com/tutorials/what-is-a-circuit).


#### Sensors and Pinouts

You can power the MKRZero through a 5v source or a 3.7v LiPo battery. For breadboard testing, you'll want to hook up the MKRZero to your computer via microUSB cable. It should be noted that most of the accessory boards are only 3.3v tolerant. You should only hook the boards up to VCC and not the 5v pin.

For the pinouts, you'll see the name of the boards at the head of each table. You'll want to connect one pin on the left side to the other pin on the right side. Take the CLK pin on the DeadOn RTC for example. You'll want to connect this pin to the SCK (pin 9) on the MKRZero.

##### Common Pins

GND - This is your ground pin. Commonly seen as the negative (-) on a battery. It is essential for ensuring that your circuit is complete and safe. If you do not properly ground a device, you increase the risk of damage or electrical shock.

VCC - This is your power supply pin. Commonly seen as the positive (+) on a battery. It is essential for powering the devices.

TX - This is the transmit pin of your device. This is the pin that sends data during serial communication.

RX - This is the receive pin of your devices. This is the pin that receives data during serial communication. If sending data from one device to another, you'll hook up the Tx line of the sending device to the Rx line of the receiving device.

SCL - This is the clock line, which allows the MKRZero to tell the device when to send data.

SDA - This is the data line. It allows the device to send data to the MKRZero.



##### The DeadOn RTC

The DeadOn RTC (the red board with the battery holder) is what allows the CTD to maintain time even when powered off. You'll want to connect each pin on the RTC to the MKRZero as follows. For VCC and GND, you can connect them to the + and - on the breadboard, as you will need to power multiple boards at once. SQW is not needed because we only want the RTC to keep time. If you wanted to add an alarm, you could implement the SQW pin.


|DeadOn RTC|MKRZero|	
|:------------:|:------------:|	
|GND|GND|	
|VCC|VCC|	
|SQW|Not Applicable|
|CLK|9 (SCK)|
|MISO|10 (MISO)|	
|MOSI|8 (MOSI)|	
|SS|D7|	


##### The SD Card

SD capabilities are native to this board. No soldering or connections needed here. This pin is called out in the operating code. 

|Board SD|MKRZero|
|:--------------------:|:--------------------:|
|CS|28|

##### The Temperature Sensor

The TSYS01 temperature sensor (the aluminum sensor with the cage) communicates with the MKRZero via the I2C communication protocol. You'll notice in the pressure sensor section that the pinouts are the same as the temperature sensor. This is okay, as each sensor has a unique address that allows the MKRZero to tell the difference between the two.

|TSYS01 Temperature Sensor|MKRZero|	
|:------------:|:------------:|	
|Red|VCC|	
|Black|GND|	
|Green|12 (SCL)|	
|White|11 (SDA)|	

##### The Pressure Sensor

The MS5837 pressure sensor (the aluminum sensor with the flat top) also communicates with the MKRZero via I2C. For the breadboard testing phase, you can connect the green wires of the pressure and temperature sensor together, the white wires together, etc.. 

|MS5837 Pressure Sensor|MKRZero|	
|:------------:|:------------:|	
|Red|VCC|	
|Black|GND|	
|Green|12 (SCL)|	
|White|11 (SDA)|	


##### The EC EZO Circuit

The EC EZO (the green board with the epoxy layer) is what controls the EC probe and sends data to the MKRZero. This board communicates via Universal Asynchronous Receiver/Transmitter (UART). This is a complex board, and it is possible to program it seperately using the MKRZero. You will do this later when you calibrate conductivity sensor.

|EC EZO|MKRZero|	
|:------------:|:------------:|	
|Tx|13 (Rx)|	
|Rx|14 (Tx)|	
|VCC|VCC|	
|GND|GND|	

TX on one side connects to RX on the other. TX should never attach to TX.

##### The EC Probe

The EC Probe is not actively powered. Instead, the EC EZO drives a voltage on PRB1. As seawater bridges the gap in the probe, current will pass to PRB2 and the EC EZO will be able to calculate conductivity. 

|Atlas-Scientific EC K1.0 Probe|EC EZO|	
|:------------:|:------------:|
|Red|PRB1|	
|Black|PRB2|	

After you cut the EC probe cable, the lead to PRB orientation does not matter. It is important that you make sure that the probe leads do not interact. If you are concerned that your pins may short, use a multimeter to check the connectivity. 

Most of the modules can be connected with the standard M/M jumper wire. For the temperature and pressure sensors you will need to use some alligator clips to make the proper connections. The EC probe will need to connected to the EC circuit via the BNC connector. Note that the BNC connector will need to be cut later, but for the bench test and calibration stages, it is okay to leave it on.

![Picture of setup with jumper wires here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/MessyWires.jpg)
*Board setup with jumper wires.*

After you double check the connections it is time to fire it up! Connect your MKRZero to the computer and upload the MKRZero_OpCode.
Make sure the rtc.autotime() function is uncommented for the first upload. After the first upload, comment out the rtc.autotime() function and re-upload. We do this so that the RTC maintains the time instead of reverting back to the original upload time evertime it loses power.

Open the serial monitor (Ctrl+Shift+M). If you have everything set up correctly, you should see data printing to the screen in the form of:

Date (mm/dd/yyyy), Time (HH:mm:ss), Conductivity (uS/cm), Temperature (degC), Absolute Pressure (mbar), Depth (m), Salinity (PSU) 

![Picture of output.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/SerialMonitorOutput.PNG)
*Date,Time,EC,T,P,Depth,Salinity*

The date and time should be close to the time that your computer is set to. It may be off by about 30-60 seconds due to upload delay.  If your time is drastically off or incoherent, remove the battery and power cycle the system. Note that the autotime function will need to be commented out of the code for the final sketch upload or else your CTD will revert to the same time on a power cycle.

The conductivity value should be zero. If it is not present in the output, try switching the Tx and Rx lines. If for some reason you begin to see ASCII or random letters in your EC output, try putting the probe in a cup of tap water. Sometimes the EC circuit can be upset by the electrical noise of the probe. 

The temperature should be representative of the ambient temperature of the room you are performing the test  in. It may be handy to have a thermometer nearby to check this. The temperature probe is factory calibrated, but if further calibration is needed, a two-point calibration is recommended.

The pressure sensor should be spitting out values between 1000 and 1050 depending on your elevation and sensor accuracy. At sea level, atmospheric pressure is around 1013 mbar. The pressure sensor is factory calibrated, but if values appear to be drastically off, first check your pinout connections. If still incorrect, contact the manufacturer. 

Depth is sketch-derived using the empirical equation outlined in [UNESCO Marine 44](http://unesdoc.unesco.org/images/0005/000598/059832eb.pdf). For the CTDizzle, there is no consideration for latitude, so gravity is assumed to be 9.806 m/s^2. It is also assumed that atmospheric pressure is 1013 mbar. For your bench tests you can ignore this value.

Salinity is also sketch-derived per the same paper. You can also ignore this value during bench tests.

Don't forget to check the output on the SD card! Pull the card, put it in and adapter and plug it into your computer. 
Opening up the SD card in Windows explorer should give you a window similar to this..

![USB](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/USBPopup.PNG)
*Note that a good way to see if you collected data is to look at the file size. Files with ~5 kb are representative of a deployment that lasted a few minutes. The file with ~4000 kb is representative of a deployment that lasted about 24 hours.* 

Opening up one of the .csv files will give you...

![CSV](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/CSVOutput.PNG)
*The data format is the same as the format in the serial monitor. This was opened in MS Excel.*

Once you are finished checking everything, reinstall the microSD card. Now it is time to calibrate the conductivity probe!


### Calibrating Conductivity

|Tools|Protective Equipment|
|:---:|:---:|
|Small Plastic Cup|Nitrile Gloves|

Unlike the factory calibrated temperature and pressure sensors, the conductivity kit requires a user calibration. First, you will need to leave your complete setup and calibration solutions in a temperature controlled room over night. You might also be able to complete this by leaving everything in a refrigerator. If you want to observe how the temperature fluctuates over several hours, power your setup with a battery and leave it running!

![Picture of calibration setup here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/CalSetup.jpg)
*Super high-tech calibration setup in a cold room.*

Once you are certain that your calibration solution has been in a stable environment for some time, grab a calibration procedure and connect the MKRZero to your computer. Follow along with the calibration procedure step by step. It is important that you note the temperature of the solution to the nearest hundredth of a degree. You can do this with a separate temperature probe if you have one on hand, or you can assume that the temperature your CTD is recording is representative of the solution if the solution has been in the room for a few hours. 

Conductivity is highly dependent on temperature, so it is important that you be as precise as possible! Using the provided spreadsheet or plots, take your calibration temperature and find the corresponding conductivity value to the nearest 100 uS/cm. You'll use these values in the calibration procedure. Don't forget to write down your calibration temperature (to the nearest hundredth), as it will later need to be manual input into the operating code.

In addition to temperature, conductivity of a solution also depends on the concentration of ions, the nature of the ions, and the viscosity of the solution. For our calibration application, we can consider these to be already known or negligible.

Here is a new [Google spreadsheet](https://docs.google.com/spreadsheets/d/1NTyalpajds06tLAo7uXbJdM82hv5m03zCGFynGOxZ1g/edit?usp=sharing) that will help determine the conductivity values to input for your calibration temperature.

After you have confirmed proper calibration of the probe, it won't need another calibration for a year. You can now cut the cable down to 6-8" in length. Please note that cutting the cable voids the Atlas-Scientific warranty, so it important to first test the probe to see if it works. After you have cut the cable, you can remove the protective cap (the one with the serial number on it) as it takes up unnecessary room in the pressure case.


### Case Construction and Potting
Once everything checks out and your breadboard tests are successful, you can begin to put the pressure case together.

|Tools|Protective Equipment|
|:---:|:---:|
|Plastic Cups|Eye Pro|
|Plastic Stir Rod|Nitrile Gloves|
|Sand Paper|Safety Mask|
|Tape|
|Round File|
|2mm Hex Wrench|


#### Switch/Pressure End Cap 

Designate one end cap and flange set as your switch/pressure sensor end cap and the other your conductivity/temperature end cap.

For each set, connect the two pieces together using the six M2 screws. Don't worry about installing the O-Ring just yet. Once connected, use sandpaper to prepare the inner surface of each flange and end cap set. Alternatively, use a marker to outline where the two pieces meet and sand accordingly. Abrasion of the surface will allow the urethane you will apply later to bond more readily to the metal surface. Use a low grit sandpaper to remove anodization until you begin to see bare aluminum. Try not to abrade the O-ring groove.

Here are some [videos](https://www.masterbond.com/resources/video-library?tid=354) on how to prepare a bonding surface.

**NOTE FOR THS STUDENTS**

The end caps that you have are blank and will need two holes drilled into them. Here are the [Blue Robotics drawings for the 2" end caps](http://docs.bluerobotics.com/assets/images/WTE/drawings/WTE2/WTE2-P-END-CAP-2-2X10MM-R1.png). Additional information can be found in the [Blue Robotics documentation](http://docs.bluerobotics.com/watertight-enclosures/).

Once you have drilled the two 10mm holes, on **one end cap per CTD**, one of the holes will need to be drilled out to 12mm to accomodate the EC probe.


![Picture of prepared end cap here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/2.PNG)
*Flange with the internal side abraded.*

Remove the face plate from the flange. Use isopropyl alcohol to clean the surface thoroughly. Install the switch and pressure bulkheads, with O-rings, using the penetrator wrenches. Don't forget to abrade the inner bulkheads as well!

![Picture of installed bulkheads here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/1.PNG)
*Picture of the pressure and switch bulkheads installed.*



#### Conductivity/Temperature End Cap

Do the same thing with the other end cap. After sufficient abrasion, install the temperature sensor in the end cap.

The conductivity sensor has too large a diameter for the pre-drilled holes, so you will need to drill out **one** of the holes to 12mm or 15/32". It may be a tight fit for the probe, so use a round file to make it the right size. Once you have the proper hole size, insert the probe so that it sticks out of the end cap approximately 2-3". To keep it in place, rig up a stand that will hold the probe in the right spot, or hot glue it into place from the outside. Tape over the probe hole to prevent any material from entering the sensing area.

After you have prepared each end cap, you can re-connect them to the flanges. Make sure everything is clean. Wrap the O-Ring grooves of the flange in tape to prevent any spillage getting into the grooves during the next step.


#### Applying the Urethane

The urethane you are using is called Urethane 75a. It is specifically designed for potting of electronics and cables that are placed in seawater. It is important to use plastic tools during mixing so as not to introduce moisture to the urethane. Using wood or paper mixing tools will upset the cure process.

![Picture of Urethane here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/5.PNG)
*Blurry picture of the urethane bottles.*

The urethane should have come with a small packet detailing the best practices of use for the material. The most important things to do are to ensure that the surfaces the urethane will contact are sufficiently abraded and that there is no moisture. Moisture induces bubbles which ultimately weakens the waterproofing capabilities of the urethane. 

Pour equal amounts of each urethane component into seperate cups. You should pour enough so that the combined amount is at least 3 oz. Using less may not be enough to generate the exothermic reaction needed for the curing process. Pour two components into one cup. Slowly mix with the stirring stick for two minutes and take care not to introduce bubbles. You will have five total minutes of working time. At around three minutes, the mixture will become thicker and more difficult to pour. Mixing too quickly can generate too much heat and reduce your overall working time. 

Here are some [videos](https://www.masterbond.com/resources/video-library?tid=354) on how to mix and apply two part epoxies.

![No Urethane](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/7.PNG)
*Conductivity and temperature sensors ready to be potted.*

Pour the urethane into each end cap until it reaches the brim of the flange. Tap the edges of the flange with a clean plastic stir rod to shake up any bubbles attached to the walls. 

Note that in some fashion the switch also acts as a purge plug. So you may only want to fill up to the bottom of the switch portion that you screw into the bulkhead.

![Picture of urethane and end caps here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/6.PNG)
*Poured urethane.*

![Pic2](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/4.PNG)
*Poured urethane.*

Allow to cure for a minimum of 12 hours.


### Completing the Circuit

|Tools|Protective Equipment|
|:---:|:---:|
|Soldering Iron|Eye Pro|
|Hemostats|Nitrile Gloves|
|Wire Strippers|
|Third Hand|

While your end caps are curing, you can begin to solder the electrical components together.

There are two options for soldering everything together. You can solder everything together with free wire, which may get a little messy but offers more flexibility in the tight pressure case. The other option is to place everything on a nifty MKRZero protoboard. Note that where you place the wires is up to you. Do not follow the pictures below.

![GNDVCC](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/GNDVCC.jpg)

You'll want to arrange the RTC and EC EZO so that you can easily solder corresponding pins. You also want to minimize the width of the protoboard package. One thing to keep in mind is that you will want the SD card pointed in the direction of the switch/pressure end cap. 

![Split](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/Split.jpg)

In this case, the pressure sensor will be connected to the 4-Pin JST connector located on the RTC side of the protoboard, and the temperature and conductivity probe will be connected to the 6-Pin JST connector located on the EC EZO side of the protoboard.

![Split2](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/Split2.jpg)

There is no set orientation for wiring everything up, nor is there a predetermined wire length for connections (although I recommend leaving about 6" of wire on the EC probe and temperature sensors). It is recommended that you test the connectivity of every connection to make sure you aren't creating any shorts. Make a note of which wire goes where, because after your urethane is done curing, you will want to make sure you have the right wires hooked up! Solder everything together as described by the pinout guide. If you want to avoid using a ton of heat shrink, you can use UY2 cold splice connectors. There is no specific orientation for the EC probe leads to the EC EZO. You'll want to make sure you are soldering corresponding wires for the JST connectors.

![JSTPressure](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/JST2Pressure.jpg)
*An example of a JST connector on the pressure sensor.*

![RTCEZO](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/RTCEZO2.jpg)
*Everything set up facing the RTC and EC EZO.*

In order to get everything to fit, I ended up trimming the header pins on each of the modules. Once you have them ordered, you can trim them to a length that works for you. 


![MainZero](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/MainZero.jpg)
*Everything set up facing the MKRZero.


#### Switch Cable 
In order to externally turn off the CTDizzle, we need to install a switch. It is not recommended that you cut the battery cables to install the switch, as this may have an impact on the charging of the battery. Instead, use a JST extension cable to tie the switch into. 

First, cut the cable at the midpoint and trim each end so that about two inches remains on each side. Using a cold splice connector, reconnect the VCC (red) line. Then connect a switch lead (blue wires in the switch bag) to each of the ground leads using another two cold splice connectors. 

![Picture of Switch cable here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/SwitchCable.jpg)
*Example of a switch cable with cold splice connectors.*

### Final Case Construction

|Tools|Protective Equipment|
|:---:|:---:|
|O-Ring Pick|Nitrile Gloves|
|Hemostats|

The CTD is going to depths where pressure is roughly 200 psi. This pressure is experienced from all directions. The optimal shape for a pressure case would be spherical, but it is often difficult to fabricate spheres, so the next best option is to use a cylindrical case. If you have a spherical and a cylindrical case with the same wall thickness, the cylinder will typically have half the strength as the sphere. Cylindrical pressure cases are typically closed off by hemispherical (rounded) or torispherical (flat) end caps. We are using the Blue Robotics aluminum tube case for several main reasons, the compatibility of sensors, the ease of access, and the robustness of aluminum over acrylic.

Rectangular pressure cases, while much easier to manufacture, can't really withstand pressure as well as cylindrical cases. There are more failure points and the odd shape of the O-Rings increases the potential of more leak points. Force is being exerted on the pressure case in all directions, and with a rectangular case, there are more points where the case can fail as some areas are not as well supported (think corners vs. walls).

The depth limiting factor for this CTD build is the conductivity probe, which the manufacturer states can only withstand a maximum of 200 PSI or ~ 140m water depth.

After you have soldered everything and tested the data output, you can finish constructing the case.

1. Ensure the flanges are clean. Grease the flange O-rings for the conductivity/temp end cap and install them.
2. Install the conductivity/temp end cap into the tube, ensuring the 6pin JST is connected.
3. Sort the wires, board, and battery.
4. Connect the MKRZero to the battery via the JST extension. Ensure that the switch is off or removed. 
5. Place a desiccant pack in the pressure case. 
6. Connect your pressure sensor to the protoboard via the 4-pin JST. Connect the switch to the switch cable. 
7. Pack the aluminum tube with some sort of packing material if there is some play in the internal wiring and components. 
8. Turn on the device using the switch. Note that the MKRZero does not turn on the LEDs when using battery power.
9. Turn off the device. Pull the card and check to see if a file is created and data is being output.

![MKRZeroOut](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/TopOpen.jpg)

![Picture of completed device here.](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/Complete.jpg)
*The CTDizzle Mk4.*

Congratulations, you just built a working CTD!

## Corrosion
The screws used in the end caps are made of 316 SS and the main body of the unit is made of aluminum.
When two dissimilar metals interact in seawater, galvanic corrosion can occur. The metal on the lower end of the galvanic scale (aluminum in this case) will begin to corrode after an extended period of time. Cathodic protection is one method to mitigating the corrosion of the end caps. This can be done by installing an anode (commonly made of zinc). 

For now, there isn't a way to connect an anode (mostly due to no one manufacturing a 2mm threaded zinc). It is important to make sure that deployments are short (few days at most) and that the device is washed with freshwater when recovered. 

## Predeployment Procedure
The deployment plan of your OpenCTD plays a role in the sampling regime.
- If you plan to take profiles, it should be set to sample as frequently as possible. The loop section of your code should restart about once per second.
- If you plan to leave the OpenCTD in the same location for several hours or days, it should be set to sample less frequently, anywhere between one minute to fifteen minutes depending on the deployment length. For example, if you are going to leave it out for a few days, sampling once every five minutes might be the way to go. 

To determine how long your battery will last, you need to take your battery mAh and divide it by your peak amperage. I've found that when all sensors are sampling, the draw is about 35 mA.


## Deployment Procedure
The device should be fully assembled and the proper sampling regime selected prior to reaching the study site. 
1.	Confirm all sensors, plugs, bulkheads, and end caps are secure. 
2.	Remove any sensor covers on the conductivity, temperature, and pressure sensors.
3.	Turn the external switch clockwise until it can turn no further. The unit should now turn ON. 

If profiling with the unit, it is suggested that it be left in the top few meters of the water column for approximately five minutes to allow for equilibrium. Once ready to profile, bring the unit to just below the surface, and allow it to descend at a rate around 0.25 m/s (~1 fathom every 10 seconds). The unit is only capable of sampling at a maximum of 1 Hz, so the slower the descent the better. 

If planning to leave the unit at a particular site for an extended period of time, it is recommended that the user ensure that the device is properly secured and **ON** prior to leaving the site. 

## Recovery Procedure
1.	After recovering the unit, turn the main switch counter-clockwise for 1 full rotation. Do not turn it any further or you may risk introducing water to the internals.
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
4. Plug the battery directly into the MKRZero or other LiPo charger if available.
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
  - Through the provided [Google spreadsheet](https://docs.google.com/spreadsheets/d/1aZhM47wCaqce_ChUhZ3tBHn-EBdLj1RdgtKbndEPGLw/edit#gid=0) (in progress).
  - Through your processing program of choice. RAWCTD files are comma-seperated.
  
5. Once you are finished looking at the data, delete the RAWCTD files in the main directory of the SD card. This keeps things from getting cluttered. 

6. Reinstall the microSD card and end cap. If you think the O-rings look a little dirty, clean and apply silicone grease before continuing. 

#### Downcast vs Upcast (For Profile Deployments)

For near real-time data, Sea-Bird recommends that you look at the data that is collected while the device is travelling down the water column (downcast). This is so that the body of an instrument does not inhibit the flow of water through the sensors or induce mixing that may result in misleading values. This assumes that you have left the device at the surface long enough for it to reach equilibrium with the surrounding water.

If you did not give the unit enough time to reach equilibrium, your upcast data may be more representative of the water properties. 

