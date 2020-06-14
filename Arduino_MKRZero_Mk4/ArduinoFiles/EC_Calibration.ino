//Adapted from the Atlas Scientific Sample Code by Oceanography For Everyone.
//This sketch is used for communicating with and calibrating the Atlas-Scientific EC EZO.
//The EC EZO may fail to read an initial "C,0", so it may need to be sent more than once to stop continuous reading mode.

byte rx_byte = 0;        //Stores incoming byte.

void setup() {    //Start your engines.
  Serial.begin(9600);    //Baud rate to 9600.
  Serial1.begin(9600);  //Communication with the EC EZO at 9600 bps.
}

void loop() {
  if (Serial.available()) {     //If a command is sent to the EC EZO from the serial monitor...
    rx_byte = Serial.read();  //the byte becomes that command...
    Serial1.write(rx_byte);   //then the byte is sent to the EC EZO.
  }
  if (Serial1.available()) {   //If a information is sent to the MKRZero from the EC EZO...
    rx_byte = Serial1.read();    //the byte becomes the data from the EC EZO...
    Serial.write(rx_byte);    //then the incoming value or response is displayed in the serial monitor.
  }
}
