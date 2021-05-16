/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
 #include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Adafruit_VL53L0X.h"
Adafruit_VL53L0X lox = Adafruit_VL53L0X();


// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial nodemcu(2,3); // RX, TX
long int data;
String mystring;
char rdata;
int clockwise=326;
int counterclockwise =357;
int firstvalue,secondvalue,thirdvalue,fourthvalue,fifthvalue,sixthvalue;
 String getValue(String data, char seperator ,int index)
 {
  int found=0;
  int strIndex[]={0,-1};
  int maxIndex = data.length() -1;
  for(int i=0 ;i<=maxIndex && found <= index; i++)
  {if (data.charAt(i) ==seperator || i==maxIndex)
  {
    found++;
  strIndex[0] =strIndex[1]+1;
  strIndex[1]=(i==maxIndex)?i+1 : i;
  
 }

  }
   return found > index ? data.substring(strIndex[0],strIndex[1] ): "";

  }
  Servo arm;
Servo arm1 ;
Servo arm2;
Servo arm3;
Servo arm4;
Servo arm5;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  nodemcu.begin(9600);
    pwm.begin();
 
  pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz  
  pwm.setPWMFreq(60);  // Analog servos run at ~50 Hz updates
 arm.attach(11 );
arm1.attach(10);
arm2.attach(9);
arm3.attach(8);
arm4.attach(6);
arm5.attach(5);
  delay(10);
     pwm.setPWM(0,0,330);
                pwm.setPWM(1,0,330);
                 pwm.setPWM(2,0,330);
                  pwm.setPWM(3,0,330);
                   pwm.setPWM(4,0,330);
                    pwm.setPWM(5,0,330);
                   
/*
    while (! Serial) {
    delay(1);
  }
 /* arm.attach(11 );
arm1.attach(10);
arm2.attach(9);
arm3.attach(8);
arm4.attach(6);
arm5.attach(5);*/


/*
  
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
*/

  
}

void loop() { 
  
  
   // run over and over
  if (nodemcu.available()>0) {
  //  data = nodemcu.parseInt();
  
 //   Serial.print(data);

   rdata = nodemcu.read();
   //   Serial.println(rdata);
     
   mystring= mystring+ rdata;
   if(rdata=='\n')
   {
    String l = getValue(mystring, ',' ,0);
    String m = getValue(mystring,',',1);
    String n = getValue(mystring,',',2);
     String o = getValue(mystring, ',' ,3);
      String p = getValue(mystring, ',' ,4);
       String q = getValue(mystring, ',' ,5);
  firstvalue= l.toInt();
   secondvalue=m.toInt();
    thirdvalue=n.toInt();
    fourthvalue = o.toInt();
    fifthvalue= p.toInt();
    sixthvalue= q.toInt();
    mystring="";
   Serial.println(firstvalue);
     Serial.println(secondvalue);
      Serial.println(thirdvalue);
      Serial.println(fourthvalue);
      Serial.println(fifthvalue);
      Serial.println(sixthvalue);
       Serial.println("\t");
       delay(100);
        arm.write(firstvalue);
          arm1.write(secondvalue);
            arm2.write(thirdvalue);
              arm3.write(fourthvalue);
                arm4.write(fifthvalue);
                  arm5.write(sixthvalue);
      
       
  /*

         if(firstvalue<1650 && firstvalue>1400 || firstvalue==0){
       //arm.writeMicroseconds(clockwise);
        pwm.setPWM(0,0,330);

       
       }
      if (secondvalue<1650&& secondvalue>1400 || secondvalue==0)
      {
      //  arm.writeMicroseconds(counterclockwise); 
      pwm.setPWM(1,0,330);

        }
           if (thirdvalue<1650 && thirdvalue>1400  || thirdvalue==0 )
      {
      //  arm.writeMicroseconds(counterclockwise); 
      pwm.setPWM(2,0,330);

        }
               if (fourthvalue<1650 && fourthvalue>1400  ||fourthvalue==0)
      {
      //  arm.writeMicroseconds(counterclockwise); 
      pwm.setPWM(3,0,330);

        }
               if (fifthvalue<1650 && fifthvalue>1400  || fifthvalue==0)
      {
      //  arm.writeMicroseconds(counterclockwise); 
      pwm.setPWM(4,0,330);

        }
               if (sixthvalue<1650 && sixthvalue>1400 || sixthvalue==0)
      {
      //  arm.writeMicroseconds(counterclockwise); 
      pwm.setPWM(5,0,330);

        }
        
        
     
      if(firstvalue>1660){
       //arm.writeMicroseconds(clockwise);
        pwm.setPWM(0,0,328);

       
       }
      else if (firstvalue<1390)
      {
      //  arm.writeMicroseconds(counterclockwise); 
      pwm.setPWM(0,0,358);

        }

     if(secondvalue>1660){
      // arm1.writeMicroseconds(clockwise);
           pwm.setPWM(1,0,358);

       }
      else if (secondvalue<1390)
      {
       // arm1.writeMicroseconds(counterclockwise); 
           pwm.setPWM(1,0,325);

        }
       
          if(thirdvalue>1660){
      // arm2.writeMicroseconds(clockwise);
           pwm.setPWM(2,0,325);

       }
      else if (thirdvalue<1390)
      {
        //arm2.writeMicroseconds(counterclockwise); 
            pwm.setPWM(2,0,358);
}

         if(fourthvalue>1660){
       //arm3.writeMicroseconds(clockwise);
           pwm.setPWM(3,0,356);

       }
      else if (fourthvalue<1390)
      {
        //arm3.writeMicroseconds(counterclockwise);
            pwm.setPWM(3,0,327);

        }
              

          if(fifthvalue>1660){
       //arm4.writeMicroseconds(clockwise);
           pwm.setPWM(4,0,359);

       }
      else if (fifthvalue<1390)
      {
       // arm4.writeMicroseconds(counterclockwise);
           pwm.setPWM(4,0,325);

       }
 /* 
          if(sixthvalue>1660){
      // arm5.writeMicroseconds(clockwise);
           pwm.setPWM(5,0,counterclockwise);

       }
      else if (sixthvalue<1390)
      {
       // arm5.writeMicroseconds(counterclockwise); 
           pwm.setPWM(5,0,clockwise);

        }
        */

       } 
 /*
    VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
    */
  
 }
  
  
 }
  
  


 
