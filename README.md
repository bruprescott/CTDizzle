# Welcome!
If you are looking for the build guide to the original OpenCTD, it can be found at the [Oceanography For Everyone GitHub](https://github.com/OceanographyforEveryone/OpenCTD).

The CTDizzle and OpenCTD have a lot in common. Some information, code, and scripts are shared between the two GitHub accounts. You should check here first for CTDizzle updates. This repository contains the code, resources, and build guide for the CTDizzle based around the MKRZero. You can also find the legacy build guide for the Qduino version, but no additional updates will be made for that setup. 

![BothVersions](https://github.com/CTDizzle/CTDizzle/blob/master/MKRZero/Documentation/Images/BothVersions.jpg)
*The three-inch and two-inch versions of the CTDizzle.*

## Log

|Date|Note|
|:---:|:---|
 |11/12/16| Switch from DS18B20 to TSYS01. Switch from 14Bar to 30Bar. Switch from HI Probe to Atlas-Scientific kit.
 |11/13/16| Added RTC. Switch from PVC to Blue Robotics case.
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
 
 
## Planned Updates
- Density output in RAWCTD files.
- Sound velocity output in RAWCTD files.
- GUI for the MATLAB tool.
- Downcast for MATLAB tool.
- Cleaner plots.
- Config file on SD card.
