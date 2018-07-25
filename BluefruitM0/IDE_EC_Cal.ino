//This sketch allows you to calibrate your EC EZO and probe from a serial monitor on your computer.
//It was adapted from the the EC_I2C example code created by Atlas Scientific.

#include <Wire.h>
#include <avr/dtostrf.h> //For temperature value concatenation.
#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

#define address 100   //Address of EC EZO.
char computerdata[20];           //we make a 20 byte character array to hold incoming data from a pc/mac/other.
byte received_from_computer = 0; //we need to know how many characters have been received.
byte code = 0;                   //used to hold the I2C response code.
char ec_data[48];                //we make a 48 byte character array to hold incoming data from the EC circuit.
byte in_char = 0;                //used as a 1 byte buffer to store inbound bytes from the EC Circuit.
byte i = 0;                      //counter used for ec_data array.
char *ec, *tds, *sal, *sg;                      
float ec_float, tds_float, sal_float, sg_float;                  //float var used to hold the float value of the specific gravity.



void setup() {
  Serial.begin(115200);
  delay(100);
  Wire.begin();
  delay(100);
}



void loop() {
  byte i = 0;                   //counter used for DO_data array.
  if (Serial.available() > 0) {                                           //if data is holding in the serial buffer
    received_from_computer = Serial.readBytesUntil(13, computerdata, 48); //we read the data sent from the serial monitor(pc/mac/other) until we see a <CR>. We also count how many characters have been received.
    computerdata[received_from_computer] = 0;                             //stop the buffer from transmitting leftovers or garbage.
    computerdata[0] = tolower(computerdata[0]);                           //we make sure the first char in the string is lower case.
    Wire.beginTransmission(address);                                      //call the circuit by its ID number.
    Wire.write(computerdata);    //transmit the command that was sent through the serial port.
    Wire.endTransmission();                                               //end the I2C data transmission.

    delay(600);                    

    Wire.requestFrom(address, 100, 1); //call the circuit and request 20 bytes (this may be more than we need)
    code = Wire.read();               //the first byte is the response code, we read this separately.

    switch (code) {                   //switch case based on what the response code is.
      case 1:                         //decimal 1.
        Serial.println("Success");    //means the command was successful.
        break;                        //exits the switch case.

      case 2:                         //decimal 2.
        Serial.println("Failed");     //means the command has failed.
        break;                        //exits the switch case.

      case 254:                      //decimal 254.
        Serial.println("Pending");   //means the command has not yet been finished calculating.
        break;                       //exits the switch case.

      case 255:                      //decimal 255.
        Serial.println("No Data");   //means there is no further data to send.
        break;                       //exits the switch case.
    }


    while (Wire.available()) {       //are there bytes to receive.
      in_char = Wire.read();         //receive a byte.
      ec_data[i] = in_char;          //load this byte into our array.
      i += 1;                        //incur the counter for the array element.
      if (in_char == 0) {            //if we see that we have been sent a null command.
        i = 0;                       //reset the counter i to 0.
        Wire.endTransmission();      //end the I2C data transmission.
        break;                       //exit the while loop.
      }
    }
    
    if (isDigit(ec_data[0])) {
      string_pars();                  //If the first char is a number we know it is a DO reading, lets parse the DO reading
    }
    else {                            //if it’s not a number
      Serial.println(ec_data);        //print the data.
      for (i = 0; i < 48; i++) {      //step through each char
        ec_data[i] = 0;               //set each one to 0 this clears the memory
      }
    }
  }
  }

    
}


void string_pars() {                  //this function will break up the CSV string into its 4 individual parts. EC|TDS|SAL|SG.
  byte i = 0;                                      //this is done using the C command “strtok”.

  ec = strtok(ec_data, ",");          //let's pars the string at each comma.
  tds = strtok(NULL, ",");            //let's pars the string at each comma.
  sal = strtok(NULL, ",");            //let's pars the string at each comma.
  sg = strtok(NULL, ",");             //let's pars the string at each comma.

  Serial.print("EC:");                //we now print each value we parsed separately.

  Serial.println(ec);                 //this is the EC value.

  Serial.print("TDS:");               //we now print each value we parsed separately.
  Serial.println(tds);                //this is the TDS value.

  Serial.print("SAL:");               //we now print each value we parsed separately.
  Serial.println(sal);                //this is the salinity value.

  Serial.print("SG:");               //we now print each value we parsed separately.
  Serial.println(sg);                //this is the specific gravity.

  //uncomment this section if you want to take the values and convert them into floating point number.
  /*
    ec_float=atof(ec);
    tds_float=atof(tds);
    sal_float=atof(sal);
    sg_float=atof(sg);
  */
}
