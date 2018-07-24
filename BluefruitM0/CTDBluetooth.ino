/*
This sketch allows you to collect conductivity, temperature, and depth data and send it to your phone via the Adafruit Bluefruit phone application.
The application is available for both Android and iOS devices.
The current output of the phone plots is conductivity (uS/cm), temperature (C), absolute pressure (millibars). There exist functions to change these to units of choice.
This sketch does not consider efficiency and will be updated as new functions and commands are implemented.
Some of this code is repurposed from sketches created by Adafruit and Blue Robotics. 
If building your own sensor, please support them by purchasing parts from their online stores.
For questions or comments regarding this sketch or the Arduino-based CTD project, send an email to Ian Black (blackia@oregonstate.edu).

Don't forget to check out these other open source CTD variants!
Arduino-based Sonde  https://github.com/glockridge/MooredApplication
OpenCTD https://github.com/OceanographyforEveryone/OpenCTD
PiCTD https://github.com/haanhouse/pictd
Conduino https://github.com/kpdangelo/OpenCTDwithConduino
 */


/*----------Initialization---------*/
#include <Adafruit_BLE.h> 
#include <Adafruit_BluefruitLE_SPI.h>
#include "Adafruit_BluefruitLE_UART.h"
#include "RTClib.h" 
#include <string.h>
#include <SD.h>  
#include <SPI.h>   
#include <Wire.h>
#include "TSYS01.h" 
#include "MS5837.h"
#include <avr/dtostrf.h> //For temperature value concatenation.
#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

/*----------Stuff you might want to change.---------*/
#define latitude 45.00    //This is your deployment latitude. It is used in the pressure to depth conversion.
#define address 100     //This is the I2C address of the EC EZO.
String BROADCAST_NAME = "CTDizzle Mk5";  //You can name your CTD anything!
/*---------------------------------------*/

#define BLUEFRUIT_SPI_CS 8
#define BLUEFRUIT_SPI_IRQ 7
#define BLUEFRUIT_SPI_RST 4 
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
uint8_t readPacket(Adafruit_BLE *ble, uint16_t timeout);
float parsefloat(uint8_t *buffer);
void printHex(const uint8_t * data, const uint32_t numBytes);
extern uint8_t packetbuffer[];
char buf[60];
File datafile; 
File recentfile;
RTC_PCF8523 rtc; 
TSYS01 tsensor; 
MS5837 psensor;
float AirTemp, Celsius, Fahrenheit, Kelvin; 
float AtmP, x, gr, AbsPressure,Decibars, Meters, Feet, Fathoms;
char ec_data[48];   
byte in_char = 0, i = 0 ;                             
char *ec, *tds, *sal, *sg;                      
float ec_float, tds_float, sal_float, sg_float;                 
String BROADCAST_CMD = String("AT+GAPDEVNAME=" + BROADCAST_NAME);
float SalA1=2.070e-5, SalA2=-6.370e-10, SalA3=3.989e-15;
float SalB1=3.426e-2, SalB2=4.464e-1, SalB3=4.215e-1, SalB4=-3.107e-3;
float Salc0=6.766097e-1, Salc1=2.00564e-2, Salc2=1.104259e-4, Salc3=-6.9698e-7, Salc4=1.0031e-9;
float Sala0= 0.0080, Sala1= -0.1692, Sala2= 25.3851, Sala3= 14.0941, Sala4= -7.0261, Sala5= 2.7081;
float Salb0= 0.0005, Salb1= -0.0056, Salb2= -0.0066, Salb3 =-0.0375, Salb4= 0.0636, Salb5= -0.0144;
float Salk =0.0162, SalCStandard=42.914;
float R, RpNumerator, RpDenominator, Rp, rT, RT, Salinity;


/*----------Functions---------*/
float PressureZero(){  //Determines atmospheric pressure if the user turns the unit on above water.
  psensor.read();
  AtmP=psensor.pressure();
  return AtmP;
}



float AirTemperature(){  //Determines air temperature if the user turns the unit on above water.
  tsensor.read();
  AirTemp=tsensor.temperature();
  return AirTemp;
}



void setup(){  //Start your engines.
  Serial.begin(115200);
  delay(500);
  Wire.begin();
  delay(500);
  rtc.begin();
  
    //rtc.adjust(DateTime(__DATE__, __TIME__));

  DateTime now = rtc.now();
  delay(250);
  pinMode(10, OUTPUT);
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
    SD.remove("PLOT.CSV"); //This is a temporary file that is created to send data to the mobile device.
    delay (250);       
    if(!SD.exists(filename)){ 
        datafile=SD.open(filename,FILE_WRITE); //Create a new file if the file doesn't already exist.
        recentfile=SD.open("PLOT.CSV",FILE_WRITE); 
      }
    }  
  tsensor.init();   //Initialize the temp sensor.
  delay(250);     
  psensor.init();   //Initialize the pressure sensor.
  delay(250);
  psensor.setModel(MS5837::MS5837_30BA);    //Define the pressure sensor model.
  psensor.setFluidDensity(1028);  //Set the approximate fluid density of deployment. Global ocean average is 1035. Coastal/estuarine waters between 1024-1035.
  PressureZero();
  AirTemperature();
  ble.begin(); //Set up bluetooth connectivity.
  ble.echo(false);  //Turn off echo.
  BROADCAST_CMD.toCharArray(buf, 60);
  ble.sendCommandCheckOK(buf);
  ble.verbose(false);  //Turn off any debug info from the bluetooth module.
  while (! ble.isConnected()) { //Wait for connection.
      delay(500);
    }
  ble.setMode(BLUEFRUIT_MODE_DATA); //Set to data mode.
  delay(500);
  Wire.beginTransmission(address);
  Wire.write(76);
  Wire.write(44);
  Wire.write(48);
  Wire.endTransmission();
} //Set up time is ~3 seconds



void get_pressure_depth(){  //Conversion from pressure to depth.  See AN69 by Seabird Scientific.
  psensor.read();  //Read the pressure sensor.
  AbsPressure=psensor.pressure();
  Decibars=(psensor.pressure()- AtmP)/100;   
  x = sin(latitude / 57.29578);
  x = x * x;
  gr = 9.780318 * (1.0 + (5.2788e-3 + 2.36e-5 * x) * x) + 1.092e-6 * Decibars;
  Meters = ((((-1.82e-15 * Decibars + 2.279e-10) * Decibars - 2.2512e-5) * Decibars + 9.72659) * Decibars)/gr; //Depth in meters.
  Feet = Meters * 3.28084;
  Fathoms = Feet/6;
}



void get_temperature(){ 
  tsensor.read();
  Celsius=tsensor.temperature();
  Fahrenheit=Celsius*1.8+32;     
  Kelvin=Celsius+273.15;     
}



void send_temperature(){
  char sendtemp[20];
  dtostrf(Celsius,4,3,sendtemp);
  Wire.beginTransmission(address); 
  Wire.write(84);  //ASCII for T
  Wire.write(44);  //ASCII for ,
  Wire.write(sendtemp);
  Wire.endTransmission();
}



void get_conductivity(){
  byte i = 0;  
  Wire.beginTransmission(address); 
  Wire.write(114);   //ASCII for r.                                            
  Wire.endTransmission();      
  delay(600);  //Wait 600 milliseconds.
  Wire.requestFrom(address, 48, 1); //Get the data string from the EC EZO.
  while (Wire.available()) {  //If information is being received.//
      in_char = Wire.read();  //read it.
      ec_data[i] = in_char;   //Turn it into an array.               
      i += 1;                                  //incur the counter for the array element.
      if (in_char == 0) {                      //if we see that we have been sent a null command.
        i = 0;                                 //reset the counter i to 0.
        Wire.endTransmission();                //end the I2C data transmission.
        break;                                 //exit the while loop.
        }
      }
  if (isDigit(ec_data[0])) {
    byte i = 0;                             
    ec = strtok(ec_data, ",");     
    tds = strtok(NULL, ",");         
    sal = strtok(NULL, ",");       
    sg = strtok(NULL, ",");           
    ec_float=atof(ec);
    tds_float=atof(tds);
    sal_float=atof(sal);
    sg_float=atof(sg);
    }
}



void calc_salinity(){
   R = ((ec_float/1000)/SalCStandard);    //PSS-78 calculations.
   RpNumerator = ( SalA1*Decibars)*( SalA2*pow(Decibars,2))+( SalA3*pow(Decibars,3));
   RpDenominator = 1*( SalB1*Celsius)+( SalB2*pow(Celsius,2))+( SalB3*R)+( SalB4*Celsius*R);
   Rp = 1+(RpNumerator/RpDenominator);
   rT =  Salc0 +( Salc1*Celsius)+( Salc2*pow(Celsius,2))+( Salc3*pow(Celsius,3))+( Salc4*pow(Celsius,4));
   RT=R/(rT*Rp);
   Salinity = ( Sala0+( Sala1*pow(RT,0.5))+( Sala2*RT)+( Sala3*pow(RT,1.5))+( Sala4*pow(RT,2))+( Sala5*pow(RT,2.5)))+((Celsius-15)/(1+ Salk*(Celsius-15)))*( Salb0+( Salb1*pow(RT,0.5))+( Salb2*RT)+( Salb3*pow(RT,1.5))+( Salb4*pow(RT,2))+( Salb5*pow(RT,2.5)));
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
    datafile.print(ec_float);   //Options: ec_float, Salinity
    datafile.print(",");
    datafile.print(Celsius);   //Options: Celsius, Fahrenheit, Kelvin
    datafile.print(",");
    datafile.println(AbsPressure); //Options: Decibars, Meters, Feet, Fathoms
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
    ble.print(ec_float);  
    ble.print(",");
    ble.print(Celsius);   
    ble.print(",");
    ble.println(AbsPressure);
   }

   if(recentfile){
    recentfile.print(ec_float);  
    recentfile.print(",");
    recentfile.print(Celsius);   
    recentfile.print(",");
    recentfile.print(AbsPressure);
    recentfile.println();
    recentfile.flush();   //Flush the file.
    }
}



void loop(){  //And around we go...
    get_temperature(); //Get the temp and perform conversions.
    send_temperature(); //Send the temperature to the EC EZO.
    get_pressure_depth(); //Get the pressure and perform conversions.
    delay(300);
    get_conductivity(); //Get the conductivity.
    calc_salinity(); //Calculate salinity
    PrintToFile(); //Save data to file.
    delay(100); //Wait 800 milliseconds.
    if (ble.available()>0){ //If a connection is made...
      CommandMode();  //...continue to collect data and wait for several command options from user.
    }
}//Loop time is ~ 1 second.



void CommandMode(){ //Function options for when a bluetooth connection is made.
  while(ble.available()>0){ //While connected via bluetooth...
    int CMD = ble.read();  //...Read any incoming user value.    
    switch (CMD){     
      case 'T':{  //Communication Test Command
        ble.println("Comms Test Successful");
        break;}     
      
      case 'Q':{ 
         ble.println("Closing files...");
         datafile.flush();  //Clear leftovers.
         datafile.close();  //Close the main file.
         delay(1000);
         recentfile.flush(); //Clear leftovers.
         recentfile.close(); //Close the temporary file.
         delay(1000);
         ble.println("Files closed. Ready for next command.");
         break;}
        
      case 'V':{  //Queries the board and calculates the battery voltage.
        float measuredvbat = analogRead(9);
        measuredvbat *= 2; // we divided by 2, so multiply back
        measuredvbat *= 3.3; // Multiply by 3.3V, our reference voltage
        measuredvbat /= 1024; // convert to voltage        
        ble.print("Battery Voltage: " ); 
        ble.print(measuredvbat);
        ble.println(" V");
        if (measuredvbat<3.50 && measuredvbat>3.30){
           ble.println("It is recommended that you recharge or swap the battery soon.");  
        }
        if (measuredvbat<=3.30){
          ble.println("Battery voltage dangerously low."); 
          delay(1000);
          ble.println("Recharge or swap the battery immediately.");
        }
        break;}

      case 'S':{  //The send command. Sends data for viewing as a CSV.
        ble.println("Sending data from the PLOT file in 1 second."); 
        File mostrecentfile=SD.open("PLOT.CSV"); //Reopens the temporary file...
        delay(1000);
          if(mostrecentfile){
            while(mostrecentfile.available()){
              ble.write(mostrecentfile.read());  //...and sends it to your phone.
            }
            mostrecentfile.close();  //Close it.
          }
        break;}
        
      case 'P':{ //The plot command. Sends delayed data for viewing as a plot in the Bluefruit App.
        ble.println("Sending data from the most recent file in 20 seconds."); 
        ble.println("Switch to plotter view now.");
        delay(20000);
        File mostrecentfile=SD.open("PLOT.CSV"); //Reopens the temporary file...
          if(mostrecentfile){
            while(mostrecentfile.available()){
              ble.write(mostrecentfile.read());  //...and sends it to your phone.
            }
            mostrecentfile.close();  //Close it.
          }
        break;}

      case 'I':{
        ble.print("Device ID: ");
        ble.println(BROADCAST_NAME); 
        ble.print("Atmospheric Pressure: ");
        ble.print(AtmP);
        ble.println(" mbars");    
        ble.print("Air Temperature: ");
        ble.print(AirTemp);
        ble.println(" degC");   
        break;}
    }
  }  
}

