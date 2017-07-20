//Need to add RTC.

#include <SD.h>   //Used by SD module.
#include <SPI.h>   //Used by SD module and RTC.
#include <Wire.h>   //Used by temperature and pressure sensors.
#include "TSYS01.h" //Used by temperature sensor.
#include "MS5837.h" //Used by pressure sensor.

#define FluidDensity 1024   //Density in kg/m^3. This varies with water conditions and location.

float EC_float = 0; //Visit Atlas-Scientific for documentation on EZ EZO.
char EC_data[48];
char *EC;
byte received_from_sensor = 0;

TSYS01 tsensor; //Define temperature functions.
MS5837 psensor;   //Define pressure functions.

File datafile;

void setup() {      //Start your engines.
  Serial.begin(9600);     //Set the baud rate to 9600 bps.
  delay(100);
  Serial1.begin(9600);
  delay(100);
  Wire.begin();   //Set up I2C comms.
  if (SD.begin(28)) {  //If a SD card is detected on pin 28...
    char filename[]= "rawCTD00.CSV";    
    delay (800);
    for(uint8_t i=0;i<100;i++){
      filename[6]=i/10+'0';
      filename[7]=i%10+'0';
      if(!SD.exists(filename)){ //...create a file with a name in series. Example: RAWCTD00.csv, RAWCTD01.csv
        datafile=SD.open(filename,FILE_WRITE);  //A new file is created when the device is power cycled.
        break;
      }
      delay (500);  //Wait half a second before continuing.
    }
    delay (500);    //Wait half a second before continuing.
  }
  else {
    Serial.println("No SD card detected."); //Display this message if the card is not detected.
    Serial.println("*Check to see if the card is installed.");
    Serial.println("*Check to see if you have the right CS pin for your board.");
    return; 
  }
  tsensor.init();   //Initialize the temperature sensor.
  psensor.init();   //Initialize the pressure sensor.
  psensor.setModel(MS5837::MS5837_30BA);    //Define the model of the pressure sensor.
  psensor.setFluidDensity(FluidDensity); //Set approximate fluid density for pressure sensor. Varies with location.
  delay(1000);     //Wait a second before continuing. 
}   //Setup takes about three seconds to complete.


void loop() {     //And around we go.
  tsensor.read();  //Read what the temperature is and hold it.
  delay(10);    //Wait ten milliseconds.
  psensor.read();  //Read what the pressure is and hold it.
  delay(10);   //Wait ten milliseconds.
  if (Serial1.available() > 0) {     //If comms are established with the EC EZO.
    received_from_sensor = Serial1.readBytesUntil(13,EC_data,48);  //Read incoming data from the EZO.
    EC_data[received_from_sensor] = 0;    //Null terminate the data.
    } 
  if ((EC_data[0] >= 48) && (EC_data[0] <= 57)){
    EC = strtok(EC_data, ",");    //Parse the incoming data at the commas.
  }
  delay(10);
  if (datafile) {
    datafile.print(EC);
    datafile.print(",");
    datafile.print(tsensor.temperature());   //Print temperature to SD card.
    datafile.print(",");
    datafile.println(psensor.pressure());   //Print pressure to SD card.
    datafile.flush();   //Close the file.
    delay(10); //Wait ten milliseconds.
    Serial.print(EC);
    Serial.print(",");
    Serial.print(tsensor.temperature());   //Print temperature to SD card.
    Serial.print(",");
    Serial.println(psensor.pressure());   //Print pressure to SD card.
  }
  else{
    Serial.println("Error. Check your circuit setup.");
  }
  delay(960);
}   //Loop completes about once per second. 



