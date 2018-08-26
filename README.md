# Welcome!
This repository contains the build information for the CTDizzle; a simple to construct salinity and temperature sensor.

The newest version is the CTDizzle Mk5. This version of the CTD is based around the Adafruit Bluefruit M0 Feather and allows a user to communicate with the CTD via Bluetooth. To get started, go to the Mk5 folder. Older versions of the CTDizzle are no longer supported, but the build information can be found in the Legacy folder.

If you have any questions about the CTDizzle, contact Ian Black (blackia@oregonstate.edu).


## Log

|Date|Note|
|:---:|:---|
 |11/12/16| Switched from DS18B20 to TSYS01. Switched from 14Bar to 30Bar. Switched from HI Probe to Atlas-Scientific kit.
 |11/13/16| Added RTC. Switched from PVC to Blue Robotics case.
 |02/17/17| Added temperature compensation for EC EZO.|
 |04/14/17| Data now output in .CSV instead of .TXT.
 |05/20/17| Added new file creation on power cycle. Data files are now named RAWCTDXX.csv (where XX is a number in sequence starting at 00).
 |07/17/17| Removed temperature compensation for EC EZO due to bad readings.
 |08/06/17| Added downcast filter for R script.
 |08/10/17| Switched from Loctite Marine to Urethane 75a.
 |08/10/17| Officially switched to MKRZero. No more planned updates for Qduino build. Edited parts list and pinout guide to reflect change.
 |08/11/17| Added depth and salinity calculations to MKRZero_OpCode. Updated MATLAB tool.
 |08/19/17| Changed atmospheric pressure assumption to 1013 mbar. Organized directories. User manual overhaul.
 |08/24/17| Updated user manual.
 |09/01/17| Added EC calibration spreadsheet.
 |09/22/17| Updated software install instructions. Added more detail.
 |10/03/17| Added more pictures.
 |11/05/17| Added density anomaly calculation. New datafiles now have 8 columns. (Date,Time,EC,T,P,Depth,Sal,Sigma)
 |12/29/17| Minor maintenance.
 |01/18/18| Found error in depth calculation. Fixed.
 |01/31/18| Updated MATLAB scripts with latitude window prompt. Implemented EC temp compensation (not tested).
 |03/07/18| Recent deployments show a periodic double printing of EC data, which throws off the rest of the printed line. Reasons unknown. Working on fix. 
 |07/24/18| Switched to the Adafruit Bluefruit M0. Allows for data viewing via mobile device.
 |07/25/18| Implemented temperature compensation for EC EZO with reading fix.
 |08/19/18| Formatted repository. Newest CTDizzle version is located in the Mk5 folder. The Legacy folder contains build information for past versions.

