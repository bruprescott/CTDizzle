/*
This sketch is a combination of code written by the folks at Adafruit, Atlas-Scientific, Blue Robotics, Oceanography For Everyone, and SparkFun.
It is used by the CTDizzle Mk4 and based around the Arduino MKRZero. 
Contact Ian Black for questions or comments regarding this sketch. 
Email: blackia@oregonstate.edu

This sketch will print data to a .CSV with 7 columns:
Date , Time , EC , T , P , Depth(sketch derived) , Sal(sketch derived) 

ISSUES
Does not consider latitudinal variation in gravity. Assumes g=9.806 m/s^2 
Assumes atmospheric pressure is 1013 mbar.
These impact the depth and salinity calculations ever so slightly.

*/

#include <SD.h>   //Used by SD module.
#include <SPI.h>   //Used by SD module and RTC.
#include <Wire.h>   //Used by temperature and pressure sensors.
#include "TSYS01.h" //Used by temperature sensor.
#include "MS5837.h" //Used by pressure sensor.
#include <SparkFunDS3234RTC.h>

//Common variables you are most likely to change based on your needs.
#define FluidDensity 1024   //Density in kg/m^3. This varies with water conditions and location.
#define SD_chipselect 28    //Chip select for the MKRZero.
#define g 9.806   //Gravity in m/s^2. Varies with latitude.
#define RTC_chipselect 7    //Chip select for the DeadOn RTC.
#define calTemp 14.50   //EC calibration temperature to the nearest hundredth of a degree.
//End of common variables. 

float EC_float = 0; //Visit Atlas-Scientific for documentation on EZ EZO.
char EC_data[48];
byte received_from_sensor = 0;
byte string_received = 0;
String inputstring = "";
char *EC; //Char pointer used in string parsing.  
float f_ec;  //Turns SAL into a floating point for calculations.    
#define A1 2.070*pow(10,-5)  //Following variables are used to calculate salinity.
#define A2 -6.370*pow(10,-10)  //Based on PSS-78. See AppNote 14 by SBE for more info. 
#define A3 3.989*pow(10,-15)
#define B1 3.426*pow(10,-2)
#define B2 4.464*pow(10,-1)
#define B3 4.215*pow(10,-1)
#define B4 -3.107*pow(10,-3)
#define c0 6.766097*pow(10,-1)
#define c1 2.00564*pow(10,-2)
#define c2 1.104259*pow(10,-4)
#define c3 -6.9698*pow(10,-7)
#define c4 1.0031*pow(10,-9)
#define a0 0.0080
#define a1 -0.1692
#define a2 25.3851
#define a3 14.0941
#define a4 -7.0261
#define a5 2.7081
#define b0 0.0005
#define b1 -0.0056
#define b2 -0.0066
#define b3 -0.0375
#define b4 0.0636
#define b5 -0.0144
#define k 0.0162
#define CStandard 42.914
float R;
float RpNumerator;
float RpDenominator;
float Rp;
float rT;
float RT;
float Salinity;   //Calculate salinity as a floating point.

TSYS01 tsensor; //Define temperature functions.
float T;  //Calculate temperature as a floating point.

MS5837 psensor;   //Define pressure functions.
#define COEFF1 -1.82*pow(10,-15)  //Following variables are used to calculate depth.
#define COEFF2 2.279*pow(10,-10) //See AppNote 69 by SBE for more info.
#define COEFF3 2.2512*pow(10,-5) 
#define COEFF4 9.72659  
float GaugeP;   //Calculate gauge pressure as a floating point.
float Depth;    //Calculate depth as a floating point.

File datafile; 



void setup() {      //Start your engines.
  Serial.begin(9600);     //MKRZero comms with computer at 9600bps.
  delay(10);     //Wait 10 milliseconds before continuing. 
  Serial1.begin(9600);    //Comms between EC EZO and MKRZero at 9600 bps.
  delay(10);     
  Wire.begin();   //Set up I2C comms.
  delay(10);  
  rtc.begin(RTC_chipselect);  //Enable the RTC. 
  delay(10);
  
  if (SD.begin(SD_chipselect)) {  //If a SD card is detected on the defined chip select...
    char filename[]= "rawCTD00.CSV";    
    delay (1000);  //Wait a second before continuing.
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
    Serial.println("No SD card detected. Check your setup."); //Display this message if the card is not detected.
    return; //And then exit setup.
  }
    
  delay(100);     //Wait 100 milliseconds before continuing. 
  tsensor.init();   //Initialize the temperature sensor.
  delay(70);     //Wait 70 milliseconds before continuing. 
  psensor.init();   //Initialize the pressure sensor.
  delay(100);    //Wait 100 milliseconds before continuing. 
  psensor.setModel(MS5837::MS5837_30BA);    //Define the model of the pressure sensor.
  psensor.setFluidDensity(FluidDensity); //Set approximate fluid density for pressure sensor. Varies with location.

  //rtc.autoTime();   //After an initial upload, the RTC will keep the same time as your computer. Comment out this line and re-upload to have the RTC maintain time.
  
  delay(2000);   //Wait 2 seconds
}



void loop() {     //And around we go.
    rtc.update();   //Update the time.
    if (Serial1.available()>0){   //If comms with the EC EZO are established
      received_from_sensor=Serial1.readBytesUntil(13,EC_data,48);   //Read the incoming data.
      EC_data[received_from_sensor]=0;
    }
    if ((EC_data[0] >= 48) && (EC_data[0] <= 57)){
      print_EC_data(); //If incoming EZO data is a digit and not a letter, parse it. 
    }

  psensor.read();  //Read what the pressure is.
  GaugeP=(psensor.pressure()-1013)/100;   //GaugeP is in decibars. Assumes atmospheric pressure is 1000 mbar.
  delay(10);
  Depth = (((((COEFF1*GaugeP+COEFF2)*(GaugeP)-COEFF3)*(GaugeP)+COEFF4)*(GaugeP))/g);   //Depth is in meters.
  delay(10);

  tsensor.read();  //Read what the temperature is and hold it.
  T=tsensor.temperature(); //Define the temperature as a floating point to make salinity calculation a little easier.
  delay(10);

  R = ((f_ec/1000)/CStandard);    //PSS-78 calculations.
  RpNumerator = (A1*GaugeP)*(A2*pow(GaugeP,2))+(A3*pow(GaugeP,3));
  RpDenominator = 1*(B1*T)+(B2*pow(T,2))+(B3*R)+(B4*T*R);
  Rp = 1+(RpNumerator/RpDenominator);
  rT = c0 +(c1*T)+(c2*pow(T,2))+(c3*pow(T,3))+(c4*pow(T,4));
  RT=R/(rT*Rp);
  Salinity = (a0+(a1*pow(RT,0.5))+(a2*RT)+(a3*pow(RT,1.5))+(a4*pow(RT,2))+(a5*pow(RT,2.5)))+((T-15)/(1+k*(T-15)))*(b0+(b1*pow(RT,0.5))+(b2*RT)+(b3*pow(RT,1.5))+(b4*pow(RT,2))+(b5*pow(RT,2.5)));
  
   if (datafile) {
    if(rtc.month()<10){
       datafile.print('0');}    //Print a zero for aesthetics.
    datafile.print(String(rtc.month()));    //Print month to SD card.
    datafile.print("/");
    if(rtc.date()<10){
        datafile.print('0');} //Print a zero for aesthetics.
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
    datafile.print(tsensor.temperature());   //Print temperature to SD card.
    datafile.print(",");
    datafile.print(psensor.pressure());   //Print pressure to SD card.
    datafile.print(",");
    datafile.print(Depth);    //Print depth to SD card.
    datafile.print(",");
    datafile.println(Salinity);    //Print sketch derived salinity to SD card.
    datafile.flush();   //Close the file.

    Serial.print(String(rtc.month()) + "/" + String(rtc.date()) + "/" + String(rtc.year())); //Print date to serial monitor.
    Serial.print(",");   //Comma delimited.
    Serial.print(String(rtc.hour()) + ":" + String(rtc.minute())+":"+String(rtc.second()));  //Print hours, minutes, seconds to serial monitor.
    Serial.print(",");
    Serial.print(EC);   //Print the floating point EC to serial monitor.
    Serial.print(",");
    Serial.print(tsensor.temperature());   //Print temperature to serial monitor.
    Serial.print(",");
    Serial.print(psensor.pressure());   //Print pressure to serial monitor.
    Serial.print(",");
    Serial.print(Depth);    //Print depth to serial monitor.
    Serial.print(",");
    Serial.println(Salinity);    //Print sketch derived salinity to serial monitor.
  }
  else{
    Serial.println("Something went wrong.");  //If the file is not created or appended, display this message.
  }
  delay(960);
}



void print_EC_data(void) {   //Called to parse the incoming data. Strings come in the form of EC,TDS,SAL,GRAV.  
  EC = strtok(EC_data, ",");                                     
  f_ec= atof(EC); //Convert EC to a floating point number to make salinity calculations a little easier.           
}
