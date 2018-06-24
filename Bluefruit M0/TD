#include "RTClib.h" 
#include <string.h>
#include <SD.h>  
#include <SPI.h>   
#include <Wire.h> 
#include "TSYS01.h" 
#include "MS5837.h" 

#define latitude 45.00  

RTC_PCF8523 rtc; //RTC

File datafile;

TSYS01 tsensor;  
MS5837 psensor;
float t,p; 
float t_f;
float x,gr,depth,fathoms; 



//////////////////////////////////////////////////
void setup(){  //Start your engines.
  Serial.begin(115200);
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(__DATE__, __TIME__));
  pinMode(10, OUTPUT);
  DateTime now = rtc.now();
  
  if (SD.begin(10)) {
    char filename[] = "00000000.CSV";   
      filename[0] = now.month()/10 + '0'; 
      filename[1] = now.month()%10 + '0'; 
      filename[2] = now.day()/10 + '0'; 
      filename[3] = now.day()%10 + '0'; 
      filename[4] = now.hour()/10 + '0'; 
      filename[5] = now.hour()%10 + '0'; 
      filename[6] = now.minute()/10 + '0'; 
      filename[7] = now.minute()%10 + '0';    
    if(!SD.exists(filename)){ 
        datafile=SD.open(filename,FILE_WRITE);  
      }
  }
  delay(100);
  tsensor.init();   
  delay(100);     
  psensor.init();   
  psensor.setModel(MS5837::MS5837_30BA);    
  psensor.setFluidDensity(1028);
  delay(3000); 
}
//////////////////////////////////////////////////
//////////////////////////////////////////////////
void depth_calc(){  //Conversion from millibars to fathoms.  
  psensor.read();  
  p=(psensor.pressure()-1013)/100;   
  x = sin(latitude / 57.29578);
  x = x * x;
  gr = 9.780318 * (1.0 + (5.2788e-3 + 2.36e-5 * x) * x) + 1.092e-6 * p;
  depth = ((((-1.82e-15 * p + 2.279e-10) * p - 2.2512e-5) * p + 9.72659) * p)/gr;
  fathoms = depth * 0.546807;
}
//////////////////////////////////////////////////
//////////////////////////////////////////////////
void temp_calc(){ //Conversion from Celsius to Fahrenheit.
  tsensor.read(); 
  t=tsensor.temperature(); 
  t_f = (t * 1.8)+ 32;
}
//////////////////////////////////////////////////
//////////////////////////////////////////////////
void PrintToFile(){
   DateTime now = rtc.now();
   if(datafile){
    datafile.print(now.month(),DEC);    //Print month to SD card.
    datafile.print("/");
    datafile.print(now.day(),DEC);   //print date to SD card.
    datafile.print("/");
    datafile.print(now.year(),DEC); //Print year to SD card.
    datafile.print(",");   //Comma delimited.
    datafile.print(now.hour(),DEC);   //Print hour to SD card.
    datafile.print(":");
    datafile.print(now.minute(),DEC);
    datafile.print(":");
    datafile.print(now.second(),DEC); //Print date to SD card.
    datafile.print(",");   //Comma delimited.
    datafile.print(t_f);   //Print temperature to SD card.
    datafile.print(",");
    datafile.println(fathoms);   //Print pressure in decibars to SD card.
    datafile.flush();   //Close the file.

    Serial.print(now.month(),DEC);    //Print month to SD card.
    Serial.print("/");
    Serial.print(now.day(),DEC);   //print date to SD card.
    Serial.print("/");
    Serial.print(now.year(),DEC); //Print year to SD card.
    Serial.print(",");   //Comma delimited.
    Serial.print(now.hour(),DEC);   //Print hour to SD card.
    Serial.print(":");
    Serial.print(now.minute(),DEC);
    Serial.print(":");
    Serial.print(now.second(),DEC); //Print date to SD card.
    Serial.print(",");   //Comma delimited.
    Serial.print(t_f);   //Print temperature to SD card.
    Serial.print(",");
    Serial.println(fathoms);   //Print pressure in decibars to SD card.
   }
}
//////////////////////////////////////////////////
//////////////////////////////////////////////////
void loop(){  //And around we go...
    temp_calc(); 
    delay(40);
    depth_calc(); 
    delay(40);
    PrintToFile();
   
    delay(1000);
}
