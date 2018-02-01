# Welcome!
If you are looking for the build guide to the original OpenCTD it can be found at the [Oceanography For Everyone GitHub](https://github.com/OceanographyforEveryone/OpenCTD).

The CTDizzle and OpenCTD have a lot in common. Some information, code, and scripts are shared between the two GitHub accounts. You should check here first for CTDizzle updates. This repository contains the code, resources, and build guide for the CTDizzle based around the MKRZero. The Qduino Mini version is no longer supported, but if you are looking for those resources, please do not hesitate to contact Ian Black (blackia@oregonstate.edu).

## To Get Started
Navigate to the MKRZero folder. There you will find a build guide, pinout guide, parts list, and calibration procedure for the conductivity probe. There is also a folder that houses the Arduino code needed for operation and calibration as well as a documentation folder with additional information.

For a comprehensive build guide, select the MKRZero_UserGuide.md file. Good luck!


![BothVersions](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/BothVersions.jpg)
*The three-inch and two-inch versions of the CTDizzle.*

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
 
## Planned Updates
- Sound velocity output in RAWCTD files.
- GUI for the MATLAB tool.
- Downcast/upcast for MATLAB tool.
- Cleaner plots.
- Config file on SD card.
