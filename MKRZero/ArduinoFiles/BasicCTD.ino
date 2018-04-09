//This version will send temperature to the EC EZO.
//Data is printed to a CSV in the form of Date, Time, EC, T, AbsP

#include <SD.h>   //Used by SD module.
#include <SPI.h>   //Used by SD module and RTC.
#include <Wire.h>   //Used by temperature and pressure sensors.
#include "TSYS01.h" //Used by temperature sensor.
#include "MS5837.h" //Used by pressure sensor.
#include <SparkFunDS3234RTC.h> //Used by the RTC.

#define FluidDensity 1024   //Density in kg/m^3. This varies with water conditions and location.
#define SD_chipselect 28    //Chip select for the MKRZero.
#define RTC_chipselect 7    //Chip select for the DeadOn RTC.

float EC_float = 0, f_ec; //Define conductivity callouts.
char EC_data[48], *EC;
byte received_from_sensor = 0, string_received = 0;
String inputstring = "";  

TSYS01 tsensor;//Define temperature callouts.
float t; 

MS5837 psensor;   //Define pressure callouts.
float p, depth; 

File datafile; 

void setup() {      //Start your engines.
  Serial.begin(9600); 
  delay(100);     //Wait 10 milliseconds before continuing. 
  Serial1.begin(9600);    //Comms between EC EZO and MKRZero at 9600 bps.
  delay(100);     
  Wire.begin();   //Set up I2C comms.
  delay(100);  
  rtc.begin(RTC_chipselect);  //Enable the RTC. 
  delay(100);
  
  if (SD.begin(SD_chipselect)) {  //If a SD card is detected on the defined chip select...
    char filename[]= "rawCTD00.CSV";    
    for(uint8_t i=0;i<100;i++){
      filename[6]=i/10+'0';
      filename[7]=i%10+'0';
      if(!SD.exists(filename)){ //...create a file with a name in series. Example: RAWCTD00.csv, RAWCTD01.csv
        datafile=SD.open(filename,FILE_WRITE);  //A new file is created when the device is power cycled.
        break;
      }
    }
  }
  else {
    return;
  }
    
  delay(100);    
  tsensor.init();   //Initialize the temperature sensor.
  delay(100);     
  psensor.init();   //Initialize the pressure sensor.
  delay(100);    
  psensor.setModel(MS5837::MS5837_30BA);    //Define the model of the pressure sensor.
  psensor.setFluidDensity(FluidDensity); //Set approximate fluid density for pressure sensor. Varies with location.

  //rtc.autoTime();   //After an initial upload, the RTC will keep the same time as your computer. Comment out this line and re-upload to have the RTC maintain time.
  
  delay(2700);   //Wait three seconds before continuing.
} 


void loop() {     //And around we go.
    rtc.update();   //Update the time.
    psensor.read();  //Read what the pressure is.
    p=psensor.pressure()+175+1013;
    tsensor.read();  //Read what the temperature is and hold it.
    t=tsensor.temperature();
    Serial1.print('T'); //Send temperature data to the EC EZO.
    Serial1.print(',');
    Serial1.print(tsensor.temperature());
    Serial1.print('\r');
    delay(310);
    if (Serial1.available()>0){   //If comms with the EC EZO are established
      received_from_sensor=Serial1.readBytesUntil(13,EC_data,48);   //Read the incoming data.
      Serial1.flush();
      EC_data[received_from_sensor]=0;
      if ((EC_data[0] >= 48) && (EC_data[0] <= 57)){
         EC = strtok(EC_data, ",");                                      
         f_ec= atof(EC); //Convert EC to a floating point number to make salinity calculations a little easier.       
      }
    }
    delay(600);
    if(f_ec < 50000){  //If output EC is below 50000 (arbitrary threshold not to be less than 42 PSU equivalent)
    rtc.update();   //Update the time.
    
    if (datafile) {
      datafile.print(String(rtc.month()));    //Print month to SD card.
      datafile.print("/");
      datafile.print(String(rtc.date()));   //print date to SD card.
      datafile.print("/");
      datafile.print(String(rtc.year())); //Print year to SD card.
      datafile.print(",");   //Comma delimited.
      if(rtc.hour()<10){
         datafile.print('0');}   //Print a zero for aesthetics.
      datafile.print(String(rtc.hour()));   //Print hour to SD card.
      datafile.print(":");
      if(rtc.minute()<10){
         datafile.print('0');}  //Print a zero for aesthetics.
      datafile.print(String(rtc.minute()));
      datafile.print(":");
      if(rtc.second()<10){
         datafile.print('0');}  //Print a zero for aesthetics.
      datafile.print(String(rtc.second())); //Print date to SD card.
      datafile.print(",");   //Comma delimited.
      datafile.print(EC);   //Print the floating point EC.
      datafile.print(",");
      datafile.print(t);   //Print temperature to SD card.
      datafile.print(",");
      datafile.println(p);   //Print pressure in decibars to SD card.
      datafile.flush();   //Close the file.
      Serial1.flush();
    
      Serial.print(String(rtc.month()));    //Print month to SD card.
      Serial.print("/");
      Serial.print(String(rtc.date()));   //print date to SD card.
      Serial.print("/");
      Serial.print(String(rtc.year())); //Print year to SD card.
      Serial.print(",");   //Comma delimited.
          if(rtc.hour()<10){
             Serial.print('0');}   //Print a zero for aesthetics.
      Serial.print(String(rtc.hour()));   //Print hour to SD card.
      Serial.print(":");
          if(rtc.minute()<10){
             Serial.print('0');}  //Print a zero for aesthetics.
      Serial.print(String(rtc.minute()));
      Serial.print(":");
          if(rtc.second()<10){
            Serial.print('0');}  //Print a zero for aesthetics.
      Serial.print(String(rtc.second())); //Print date to SD card.
      Serial.print(",");   //Comma delimited.
      Serial.print(EC);   //Print the floating point EC.
      Serial.print(",");
      Serial.print(t);   //Print temperature to SD card.
      Serial.print(",");
      Serial.println(p);   //Print pressure in decibars to SD card.
      Serial.flush();
    }
  delay(90); //Loop about every second.
  
  }
  else{   //If the EC value is much larger than expected, 
    delay(1000);
    return; //restart the loop because something went wrong.
   }
}

