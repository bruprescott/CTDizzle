/*
This sketch allows you to collect temperature and depth data and send it to your phone via the Adafruit Bluefruit LE phone application.
It does not consider efficiency and will be update as new functions are discovered.
Some of this code is repurposed from sketches created by Adafruit and Blue Robotics. 
If building your own sensor, please support them by purchasing parts from their online stores.
For questions or comments regarding this sketch, send an email to Ian Black (blackia@oregonstate.edu).
*/

#include <Adafruit_BLE.h> //Used by bluetooth module.
#include <Adafruit_BluefruitLE_SPI.h>
#include "Adafruit_BluefruitLE_UART.h"
#include "RTClib.h" 
#include <string.h>
#include <SD.h>  
#include <SPI.h>   
#include <Wire.h> 
#include "TSYS01.h" //Used by TSYS01 temperature sensor.
#include "MS5837.h" //Used by MS5837 pressure sensor.

//Computational values you might want to change. Not a significant impact on depth calculation for most applications if unknown.
#define latitude 45.00  //Latitude of deployment in decimal degrees. 
#define AtmP 1013  //Standard atmospheric pressure in millibars.


//Bluetooth stuff. Borrowed from Adafruit and John Park.
#define BLUEFRUIT_SPI_CS 8
#define BLUEFRUIT_SPI_IRQ 7
#define BLUEFRUIT_SPI_RST 4 
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
uint8_t readPacket(Adafruit_BLE *ble, uint16_t timeout);
float parsefloat(uint8_t *buffer);
void printHex(const uint8_t * data, const uint32_t numBytes);
extern uint8_t packetbuffer[];
char buf[60];

//RTC stuff.
RTC_PCF8523 rtc; 

//SD and file stuff.
File datafile; 
File recentfile;
Sd2Card card;
SdVolume volume;
SdFile root;


//Sensor stuff.
TSYS01 tsensor;  
MS5837 psensor;
float t,p; 
float t_f;
float x,gr,depth,fathoms; 

float measuredvbat = analogRead(9);

void setup(){  //Start your engines.
  Serial.begin(115200);
  Wire.begin();
  rtc.begin();
  //rtc.adjust(DateTime(__DATE__, __TIME__)); //Comment out this line after initial upload to maintain time. Adjust time to sketch time. 
  pinMode(10, OUTPUT);
  DateTime now = rtc.now();
  if (SD.begin(10)) { //Create a file with the current month, day, hour, and minute as the file name.
    char filename[] = "00000000.CSV";   
      filename[0] = now.month()/10 + '0'; 
      filename[1] = now.month()%10 + '0'; 
      filename[2] = now.day()/10 + '0'; 
      filename[3] = now.day()%10 + '0'; 
      filename[4] = now.hour()/10 + '0'; 
      filename[5] = now.hour()%10 + '0'; 
      filename[6] = now.minute()/10 + '0'; 
      filename[7] = now.minute()%10 + '0';

    //The file "LAST.CSV" only contains depth and temperature data and is used to stream data to your phone.
    //It contains the same data as the file created under filename for the time you turned on your device.
    //It can be considered a temporary file.
    SD.remove("LAST.CSV"); //Remove the file "LAST.CSV".
    delay (100);      
    
    if(!SD.exists(filename)){ 
        datafile=SD.open(filename,FILE_WRITE); //Create a new file if the file doesn't already exist.
        recentfile=SD.open("LAST.CSV",FILE_WRITE); //Create the file "LAST.CSV".
      }
  }
  
  delay(100);
  tsensor.init();   //Initialize the temp sensor.
  delay(100);     
  psensor.init();   //Initialize the pressure sensor.
  psensor.setModel(MS5837::MS5837_30BA);    //Define the pressure sensor model.
  psensor.setFluidDensity(1028);  //Set the approximate fluid density of deployment. Global ocean average is 1035.

  ble.begin(); //Set up bluetooth connectivity.
  ble.echo(false);  //Turn off echo.
  ble.verbose(false);  //Turn off any debug info from the bluetooth module.
  while (! ble.isConnected()) { //Wait for connection.
      delay(500);
  }
  ble.setMode(BLUEFRUIT_MODE_DATA); //Set to data mode.
  delay(3000); 
} //Set up time is ~4 seconds



void depth_calc(){  //Conversion from millibars to fathoms.  See AN69 by Seabird Scientific.
  psensor.read();  //Read the pressure sensor.
  p=(psensor.pressure()- AtmP)/100;   //Assumes defined atmospheric pressure. Converts from millibars to decibars.
  x = sin(latitude / 57.29578); //Lines 126-128 are used to calculate the gravity variation with latitude.
  x = x * x;
  gr = 9.780318 * (1.0 + (5.2788e-3 + 2.36e-5 * x) * x) + 1.092e-6 * p;
  depth = ((((-1.82e-15 * p + 2.279e-10) * p - 2.2512e-5) * p + 9.72659) * p)/gr; //Depth in meters.
  fathoms = depth * 0.546807;  //1 meter = 0.546807 fathoms
}



void temp_calc(){ //Conversion from Celsius to Fahrenheit.
  tsensor.read(); //Read the temperature sensor.
  t=tsensor.temperature(); //Temperature is in Celsius.
  t_f = (t * 1.8)+ 32; //Convert to Fahrenheit.
}



void PrintToFile(){  //Function for printing data to the SD card and a serial monitor.
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
    datafile.print(fathoms);   //Print temperature to SD card.
    datafile.print(",");
    datafile.println(t_f);   //Print pressure in decibars to SD card.
    datafile.flush();   //Close the file.

    ble.print(now.month(),DEC);    //Print month to your phone.
    ble.print("/");
    ble.print(now.day(),DEC);   //print date to your phone.
    ble.print("/");
    ble.print(now.year(),DEC); //Print year to your phone.
    ble.print(",");   //Comma delimited.
    ble.print(now.hour(),DEC);   //Print hour to your phone.
    ble.print(":");
    ble.print(now.minute(),DEC);
    ble.print(":");
    ble.print(now.second(),DEC); //Print date to your phone.
    ble.print(",");
    ble.print(fathoms);   //Print temperature to your phone.
    ble.print(",");
    ble.println(t_f);   //Print pressure in decibars to your phone.
    
   }

   if(recentfile){
    //recentfile.print(now.month(),DEC);    //Uncomment these lines if you want date and time in the LAST.CSV output.
    //recentfile.print("/");
    //recentfile.print(now.day(),DEC);   
    //recentfile.print("/");
    //recentfile.print(now.year(),DEC); 
    //recentfile.print(",");  
    //recentfile.print(now.hour(),DEC);   
    //recentfile.print(":");
    //recentfile.print(now.minute(),DEC);
    //recentfile.print(":");
    //recentfile.print(now.second(),DEC); 
    //recentfile.print(",");   
    recentfile.print(fathoms);   //Print depth to LAST.CSV
    recentfile.print(",");
    recentfile.println(t_f);   //Print Fahrenheit to LAST.CSV
    recentfile.flush();   //Flush the file.
    }
}



void loop(){  //And around we go...
    temp_calc(); //Get the temp and perform conversions.
    delay(40);
    depth_calc(); //Get the pressure and perform conversions.
    delay(40);
    PrintToFile(); //Print data to SD card and serial monitor.
    delay(1000); //Wait 900 milliseconds.
    if (ble.available()>0){ //If a connection is made...
      DataTransfer();  //...wait for several command options from user.
    }
}//Loop time is just over 1 second.



void DataTransfer(){ //Function options for when a bluetooth connection is made.
  while(ble.available()>0){ //While connected via bluetooth...
    int CMD = ble.read();  //...Read any incoming user value.
    switch (CMD){
      case 'T':  //Communication Test Command
        ble.println("Comms Test Successful");
        break;
      //case 'L':  //File list only works in IDE serial monitor...
      //   card.init(SPI_HALF_SPEED,10); 
      //   volume.init(card);
      //  uint32_t volumesize;
      //  volumesize = volume.blocksPerCluster();    
      //  volumesize *= volume.clusterCount();       
      //  volumesize *= 512;                           
      //  volumesize /= 1024;
      //  ble.print("Volume size (Mbytes): "); //Total volume size of SD card, NOT remaining space.
      //  volumesize /= 1024;
      //  ble.println(volumesize);
      //  root.openRoot(volume);
      //  root.ls(LS_R | LS_DATE | LS_SIZE);  //Lists files on SD card.
      //  break;
      case 'Q': 
         ble.println("Stopping sensors and closing files...");
         datafile.flush();  //Clear leftovers.
         datafile.close();  //Close the main file.
         delay(10);
         recentfile.flush(); //Clear leftovers.
         recentfile.close(); //Close the temporary file.
         delay(1000);
         ble.println("Files closed. Ready for next command.");
         break;
      case 'V':  //Queries the board and calculates the battery voltage.
        measuredvbat *= 2; // we divided by 2, so multiply back
        measuredvbat *= 3.3; // Multiply by 3.3V, our reference voltage
        measuredvbat /= 1024; // convert to voltage        
        ble.print("Voltage: " ); 
        ble.println(measuredvbat);
        break;
      case 'S':  //The "S" Command.
        ble.println("Sending data from the most recent file in..."); 
        ble.print("3...");
        delay(1000);
        ble.print("2...");
        delay(1000);
        ble.println("1...");
        File mostrecentfile=SD.open("LAST.CSV"); //Reopens the temporary file...
          if(mostrecentfile){
            while(mostrecentfile.available()){
              ble.write(mostrecentfile.read());  //...and sends it to your phone.
            }
            mostrecentfile.close();  //Close it.
          }
        break;
    }
  }  
}


