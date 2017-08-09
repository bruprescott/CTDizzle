/* Sketch Version 1.6
 *
 * This sketch is a combination of code written by folks at Adafruit, Atlas-Scientific, Blue Robotics, Oceanography For Everyone, and SparkFun.
 * It is intended to be used within an OpenCTD based around the Qduino Mini.
 * Feel free to modify this sketch as you see fit.
 * For questions about this code, please contact Ian Black (blackia@oregonstate.edu).
 * 
 * Data is printed to a .CSV in the form of Date,Time,EC,T,P.
 * Please note that this data is in its most raw form.
 * If you aren't sure how to process this data, please look at the R and MATLAB plotters available on the OceanographForEveryone and CTDizzle GitHubs.
 */

#include <SD.h>   //Used by the SD module.
#include <SPI.h>  //Used by the SD module and RTC.
#include <Wire.h>   //Used by the temperature and pressure sensors.
#include <SoftwareSerial.h>   //Used by the EC EZO.
#include "TSYS01.h" //Used by the temperature sensor. Visit BlueRobotics for documentation.
#include "MS5837.h" //Used by the pressure sensor. Visit BlueRobotics for documentation.
#include <SparkFunDS3234RTC.h>  //Used by the RTC. Visit SparkFun for documentation

//Common variables you may want to change.
//You may also want to change things with the rtc.autotime() command located on line 51.
#define SD_chipselect 4  
#define RTC_chipselect 5
#define EZOrx 9   //Rx on EZO goes to pin # on Qduino.
#define EZOtx 8   //Tx on EZO goes to pin # on Qduino.
#define FluidDensity 1024  //Used by pressure sensor for pressure calculations.
//End of common variables.

SoftwareSerial ecSerial(EZOrx,EZOtx); 
float EC_float = 0; //Visit Atlas-Scientific for documentation on EZ EZO.
char EC_data[48];
char *EC;
byte received_from_sensor = 0;
byte string_received = 0;

TSYS01 tsensor; //Define temperature functions.

MS5837 psensor;   //Define pressure functions.

File datafile;

void setup() {      //Start your engines.
  Serial.begin(9600);     //Set the baud rate to 9600.
  delay(10);
  ecSerial.begin(9600);     //Communicate with the EZO at 9600 bps.
  delay(10);
  Wire.begin();

  rtc.begin(RTC_chipselect);    //Chip select for RTC is pin 5.
  //rtc.autoTime();  //Time updates with IDE time everytime you upload. Comment out after time sync to have rtc maintain time.

  if (SD.begin(SD_chipselect)) {  //If an SD card is detected on the defined pin..
  char filename[]= "rawCTD00.CSV";
  for(uint8_t i=0;i<100;i++){
    filename[6]=i/10+'0';
    filename[7]=i%10+'0';
    if(!SD.exists(filename)){
      datafile=SD.open(filename,FILE_WRITE); //Create a file with a name in series. Example: RAWCTD00.csv, RAWCTD01.csv
      break;
    }
   }
  }  

  tsensor.init();   //Initialize the temperature sensor.
  delay(10);
  
  psensor.init();   //Initialize the pressure sensor.
  psensor.setModel(MS5837::MS5837_30BA);    //Define the model of the pressure sensor.
  psensor.setFluidDensity(FluidDensity); //Set approximate fluid density for pressure sensor.

  delay(970);   //Wait half a second before continuing.
}   //Setup takes ~1 second to complete.



void loop() {     //And around we go.
  tsensor.read();  //Read what the temperature is and hold it.
  delay(10);
  psensor.read();  //Read what the pressure is and hold it.
  delay(10);
  
  if (ecSerial.available() > 0) {     //If comms are established with the EC EZO.
    received_from_sensor = ecSerial.readBytesUntil(13,EC_data,48);  //Read incoming data from the EZO.
    EC_data[received_from_sensor] = 0;    //Null terminate the data.
    } 
  if ((EC_data[0] >= 48) && (EC_data[0] <= 57)){
    parse_data(); //If incoming EZO data is a digit and not a letter, parse it. 
  }
  delay(10);
  
  rtc.update();   //Update the time.
  
  if (datafile) {
    datafile.print(String(rtc.month()) + "/" + String(rtc.date()) + "/" + String(rtc.year())); //Print date to SD card.
    datafile.print(",");   //Comma delimited.
    datafile.print(String(rtc.hour()) + ":" + String(rtc.minute())+":"+String(rtc.second()));  //Print hours, minutes, seconds to SD card.
    datafile.print(",");
    datafile.print(EC); //Print EC to SD card.
    datafile.print(",");
    datafile.print(tsensor.temperature());   //Print temperature to SD card.
    datafile.print(",");
    datafile.println(psensor.pressure());   //Print pressure to SD card.
    datafile.flush();   //Close the file.

    Serial.print(String(rtc.month()) + "/" + String(rtc.date()) + "/" + String(rtc.year())); //Print date to SD card.
    Serial.print(",");   //Comma delimited.
    Serial.print(String(rtc.hour()) + ":" + String(rtc.minute())+":"+String(rtc.second()));  //Print hours, minutes, seconds to SD card.
    Serial.print(",");
    Serial.print(EC);
    Serial.print(",");
    Serial.print(tsensor.temperature());
    Serial.print(",");
    Serial.println(psensor.pressure());
  }
  delay(970); //Wait 750 milliseconds.
  //Total loop time is ~1 second.
}

void parse_data() {   //If the parse_data function is called, parse incoming EZO data at the commas.
  EC = strtok(EC_data, ",");
}

