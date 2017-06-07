//Adapted from the Atlas Scientific Sample Code by Oceanography For Everyone.
//This sketch is used for communicating with and calibrating the Atlas-Scientific EC EZO.
//The EC EZO may fail to read an initial "C,0", so it may need to be sent more than once to stop continuous reading mode.

#include <SoftwareSerial.h>   //Allows communication with the EC EZO
SoftwareSerial ecSerial(9,8); //Qduino RX, Qduino TX
byte rx_byte = 0;        //Stores incoming byte.

void setup() {    //Start your engines.
  Serial.begin(9600);    //Baud rate to 9600.
  ecSerial.begin(9600);  //EC EZO baud rate to 9600
}

void loop() {
  if (Serial.available()) {     //If a command is sent to the EC EZO from the serial monitor.
    rx_byte = Serial.read();  //The byte becomes that command.
    ecSerial.write(rx_byte);   //The byte is sent to the EC EZO.
  }
  if (ecSerial.available()) {   //If a information is sent to the Qduino from the EC EZO.
    rx_byte = ecSerial.read();    //The byte becomes the data from the EC EZO.
    Serial.write(rx_byte);    //The incoming value or response is displayed in the serial monitor.
  }
}
