/*
This sketch is a combination of code written by the folks at Adafruit, Atlas-Scientific, Blue Robotics, Oceanography For Everyone, Sea-Bird Scientific, and SparkFun.
It is used by the CTDizzle Mk4 and based around the Arduino MKRZero. 
Contact Ian Black with any questions regarding this sketch.
Email: blackia@oregonstate.edu

This sketch will print data to a .CSV in the form of:
Date , Time , Conductivity , Temperature , Pressure , Depth , Salinity, Density 
Density is still being tested.

ISSUES
Assumes atmospheric pressure is 1013 mbar.
Latitude and the autotime function need to be adjusted manually in the sketch. 
Latitude should be the latitude at which you anticipate your deployment.
The autotime function needs to be uncommented for the initial upload. Then it needs to be commented out and the sketch uploaded again.
The RTC reverts back to the initial upload time after a power cycle if you do not comment out the autotime function. 
*/

#include <SD.h>   //Used by SD module.
#include <SPI.h>   //Used by SD module and RTC.
#include <Wire.h>   //Used by temperature and pressure sensors.
#include "TSYS01.h" //Used by temperature sensor.
#include "MS5837.h" //Used by pressure sensor.
#include <SparkFunDS3234RTC.h> //Used by the RTC.

#define latitude 45.00   //Expected latitude of deployment in decimal degrees. Used in gravity calculation.
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

//Salinity coeffiecients and callouts.
float SalA1=2.070e-5, SalA2=-6.370e-10, SalA3=3.989e-15;
float SalB1=3.426e-2, SalB2=4.464e-1, SalB3=4.215e-1, SalB4=-3.107e-3;
float Salc0=6.766097e-1, Salc1=2.00564e-2, Salc2=1.104259e-4, Salc3=-6.9698e-7, Salc4=1.0031e-9;
float Sala0= 0.0080, Sala1= -0.1692, Sala2= 25.3851, Sala3= 14.0941, Sala4= -7.0261, Sala5= 2.7081;
float Salb0= 0.0005, Salb1= -0.0056, Salb2= -0.0066, Salb3 =-0.0375, Salb4= 0.0636, Salb5= -0.0144;
float Salk =0.0162, SalCStandard=42.914;
float R, RpNumerator, RpDenominator, Rp, rT, RT, s;

//Density coeffiecients and callouts.
float DensB0=8.24493e-1, DensB1=-4.0899e-3, DensB2=7.6438e-5, DensB3=-8.2467e-7, DensB4=5.3875e-9;
float DensC0=-5.72466e-3, DensC1=1.0227e-4, DensC2=-1.6546e-6;
float DensD0=4.8314e-4;
float DensA0=999.842594, DensA1=6.793952e-2, DensA2=-9.095290e-3, DensA3=1.001685e-4, DensA4=-1.120083e-6, DensA5=6.536332e-9;
float DensFQ0=54.6746, DensFQ1=-0.603459, DensFQ2=1.09987e-2, DensFQ3=-6.1670e-5;
float DensG0=7.944e-2, DensG1=1.6483e-2, DensG2=-5.3009e-4;
float Densi0=2.2838e-3, Densi1=-1.0981e-5, Densi2=-1.6078e-6;
float DensJ0=1.91075e-4;
float DensM0=-9.9348e-7, DensM1=2.0816e-8, DensM2=9.1697e-10;
float DensE0=19652.21, DensE1=148.4206, DensE2=-2.327105, DensE3=1.360477e-2, DensE4=-5.155288e-5;
float DensH0=3.239908, DensH1=1.43713e-3, DensH2=1.16092e-4, DensH3=-5.77905e-7;
float DensK0=8.50935e-5, DensK1=-6.12293e-6, DensK2=5.2787e-8;
float t2, t3, t4, t5, s32;
float sigma, Densk, kw, aw, bw, density, val;

//Pressure to depth conversion callouts.
float x, gr;

File datafile; 

void setup() {      //Start your engines.
  Serial.begin(9600); 
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
  
  delay(2000);   //Wait two seconds before continuing.
} 



void loop() {     //And around we go.
    rtc.update();   //Update the time.
    tsensor.read();  //Read what the temperature is and hold it.
    t=tsensor.temperature(); //Define the temperature as a floating point to make the salinity and density calculations a little easier.
    delay(10);
    psensor.read();  //Read what the pressure is.
    p=(psensor.pressure()-1013)/100;   //Calculate pressure in decibars.
    delay (10);
  
    if (Serial1.available()>0){   //If comms with the EC EZO are established
      received_from_sensor=Serial1.readBytesUntil(13,EC_data,48);   //Read the incoming data.
      EC_data[received_from_sensor]=0;
    }
    if ((EC_data[0] >= 48) && (EC_data[0] <= 57)){
      print_EC_data();  //Parse out the EC from the EC EZO string.
    }

  R = ((f_ec/1000)/SalCStandard);    //PSS-78 calculations.
  RpNumerator = ( SalA1*p)*( SalA2*pow(p,2))+( SalA3*pow(p,3));
  RpDenominator = 1*( SalB1*t)+( SalB2*pow(t,2))+( SalB3*R)+( SalB4*t*R);
  Rp = 1+(RpNumerator/RpDenominator);
  rT =  Salc0 +( Salc1*t)+( Salc2*pow(t,2))+( Salc3*pow(t,3))+( Salc4*pow(t,4));
  RT=R/(rT*Rp);
  s = ( Sala0+( Sala1*pow(RT,0.5))+( Sala2*RT)+( Sala3*pow(RT,1.5))+( Sala4*pow(RT,2))+( Sala5*pow(RT,2.5)))+((t-15)/(1+ Salk*(t-15)))*( Salb0+( Salb1*pow(RT,0.5))+( Salb2*RT)+( Salb3*pow(RT,1.5))+( Salb4*pow(RT,2))+( Salb5*pow(RT,2.5)));
  delay(10);
  
  //Density Calculation (EOS80)
  t2=t*t;
  t3 = t*t2;
  t4 = t*t3;
  t5 = t*t4;
  if (s <= 0.0) s = 0.000001;
  s32 = pow(s, 1.5);
  p /= 10.0;    //Put pressure in bars.
  sigma = DensA0 + DensA1*t + DensA2*t2 + DensA3*t3 + DensA4*t4 + DensA5*t5 + (DensB0 + DensB1*t + DensB2*t2 + DensB3*t3 + DensB4*t4)*s + (DensC0 + DensC1*t + DensC2*t2)*s32 + DensD0*s*s;
  kw = DensE0 + DensE1*t + DensE2*t2 + DensE3*t3 + DensE4*t4;
  aw = DensH0 + DensH1*t + DensH2*t2 + DensH3*t3;
  bw = DensK0 + DensK1*t + DensK2*t2;
  Densk = kw + (DensFQ0 + DensFQ1*t + DensFQ2*t2 + DensFQ3*t3)*s + (DensG0 + DensG1*t + DensG2*t2)*s32 + (aw + (Densi0 + Densi1*t + Densi2*t2)*s + (DensJ0*s32))*p + (bw + (DensM0 + DensM1*t + DensM2*t2)*s)*p*p;
  val = 1 - p / Densk;
  if (val) sigma = sigma / val - 1000.0;  //Calculate density anomaly.
  delay(10);

  //Pressure to depth conversion.
  x = sin(latitude / 57.29578);
  x = x * x;
  gr = 9.780318 * (1.0 + (5.2788e-3 + 2.36e-5 * x) * x) + 1.092e-6 * p;
  depth = ((((-1.82e-15 * p + 2.279e-10) * p - 2.2512e-5) * p + 9.72659) * p)/gr;    //Calculate depth.
  delay(10);
  
   if (datafile) {
    datafile.print(String(rtc.month()));    //Print month to SD card.
    datafile.print("/");
    datafile.print(String(rtc.date()));   //print date to SD card.
    datafile.print("/");
    datafile.print(String(rtc.year())); //Print year to SD card.
    datafile.print(",");   //Comma delimited.
    datafile.print(String(rtc.hour()));   //Print hour to SD card.
    datafile.print(":");
    datafile.print(String(rtc.minute()));
    datafile.print(":");
    datafile.print(String(rtc.second())); //Print date to SD card.
    datafile.print(",");   //Comma delimited.
    datafile.print(EC);   //Print the floating point EC.
    datafile.print(",");
    datafile.print(t);   //Print temperature to SD card.
    datafile.print(",");
    datafile.print(psensor.pressure());   //Print pressure in millibars to SD card.
    datafile.print(",");
    datafile.print(depth);    //Print depth to SD card.
    datafile.print(",");
    datafile.print(s);    //Print sketch derived salinity to SD card.
    datafile.print(",");
    datafile.println(sigma);  //Print density anomaly to the SD card.
    datafile.flush();   //Close the file.

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
        Serial.print('0');}  
    Serial.print(String(rtc.minute()));
    Serial.print(":");
    if(rtc.second()<10){
        Serial.print('0');}  
    Serial.print(String(rtc.second())); //Print date to SD card.
    Serial.print(",");
    Serial.print(EC);   //Print EC to serial monitor.
    Serial.print(",");
    Serial.print(t);   //Print temperature to serial monitor.
    Serial.print(",");
    Serial.print(psensor.pressure());   //Print pressure to serial monitor.
    Serial.print(",");
    Serial.print(depth);    //Print depth to serial monitor.
    Serial.print(",");
    Serial.print(s);    //Print sketch derived salinity to serial monitor.
    Serial.print(",");
    Serial.println(sigma);
  }
  delay(940);
}

void print_EC_data(void) {   //Called to parse the incoming data. Strings come in the form of EC,TDS,SAL,GRAV.  
  EC = strtok(EC_data, ",");                                     
  f_ec= atof(EC); //Convert EC to a floating point number to make salinity calculations a little easier.           
}
