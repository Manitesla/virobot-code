/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on NodeMCU.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right NodeMCU module
  in the Tools -> Board menu!

  For advanced settings please follow ESP examples :
   - ESP8266_Standalone_Manual_IP.ino
   - ESP8266_Standalone_SmartConfig.ino
   - ESP8266_Standalone_SSL.ino

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
SoftwareSerial arduinoUno(3,1);

#include <Wire.h>

//#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int adata1 =0;
int adata2 =0;
int adata3 =0;
int adata4 =0;

String cdata;
int a,b,c,d,x,y,z;
#define lmotorf 5 //Motor A1
#define lmotorb 4//Motor A2
#define rmotorf 0 //Motor B1
#define rmotorb 2 //Motor B2
//#define enbb 10
//#define enba 9
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] ="AqoEYKLmTxvHGfFfUCEL9_NnXzhffa4m";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "manikant";
char pass[] = "manikant12";
int servoup=0;
int servofrnt=1;
int claw=2;
int minRange = 312;
int maxRange = 712;
int noSpeed = 0;

void setup()
{
  // Debug console
  Serial.begin(9600);
 
 // pwm.begin();
  //pwm.setPWMFreq(50);
  
  delay(10);
  

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
 //   pwm.setPWM(servoup,0,a);
   //pwm.setPWM(servofrnt,0,b);
 /*   //pwm.setPWM(claw,0,c);
  
  adata1 =x;
  adata2 =y;
  adata3 =a ;
   adata4 =d;

  
  cdata=cdata + adata1+","+adata2+","+adata3+","+adata4;
   Serial.println(cdata);
   arduinoUno.println(cdata);
   delay(1000);
   cdata="";*/
}
void moveControl(int x, int y)
{
 Serial.println(x);
 Serial.println(y);
   if(x >= minRange && y >= maxRange && x<=maxRange)  
  { 

  digitalWrite(lmotorb,HIGH);
  digitalWrite(rmotorb,HIGH);
  digitalWrite(lmotorf,LOW);
  digitalWrite(rmotorf,LOW);
 
  }
else if(x >= minRange && y <= minRange && x<= maxRange)
  {
    
 digitalWrite(lmotorf,HIGH);
  digitalWrite(rmotorf,HIGH);
  digitalWrite(lmotorb,LOW);
  digitalWrite(rmotorb,LOW);
   
  }
    // move  right
  else if(y >= minRange && x >= maxRange && y<= maxRange)
  {  
    
  digitalWrite(lmotorf,HIGH);
  digitalWrite(rmotorf,LOW);
  digitalWrite(rmotorb,HIGH);
  digitalWrite(lmotorb,LOW);

 
  }

  // moveleft
  else if(y >= minRange && x <= minRange && y <= maxRange)  
  {
  digitalWrite(lmotorf,LOW);
  digitalWrite(rmotorf,HIGH);
  digitalWrite(rmotorb,LOW);
  digitalWrite(lmotorb,HIGH);  
}
 // move forward LEFT
 

  else if(y < maxRange && y > minRange && x < maxRange && x > minRange)
  {
 
  digitalWrite(lmotorf,LOW);
  digitalWrite(lmotorb,LOW);
  digitalWrite(rmotorf,LOW);
  digitalWrite(rmotorb,LOW);
  }
}
BLYNK_WRITE(V0)

{
     a = param[0].asInt();
}
BLYNK_WRITE(V1)

{  
   x = param[0].asInt();
   y = param[1].asInt();
   //Serial.println(x);

  moveControl(x,y); 
 }
BLYNK_WRITE(V2)

{    z = param[0].asInt();
    
    
}

BLYNK_WRITE(V3)

{
     b = param[0].asInt();
}

BLYNK_WRITE(V4)

{
     c = param[0].asInt();
}
BLYNK_WRITE(V5)

{
     d = param[0].asInt();
}
