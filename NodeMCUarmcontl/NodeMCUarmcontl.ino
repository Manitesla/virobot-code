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
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
//#include <PulseSensorPlayground.h>   
//#include <Servo.h>
//Servo middle,leftt,rightt,claw;
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
SoftwareSerial arduinoUno(D6,D5);
//PulseSensorPlayground pulseSensor; 
#include <Wire.h>

#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define BLYNK_PRINT Serial

float vref = 3.3;
float resolution = vref / 1023.0;
float temperature;
BlynkTimer timer;
BlynkTimer timer1;
const int PulseWire = A0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 2;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;   

/*float vref = 3.3;
float resolution = vref / 1023.0;
float temperature;*/
int adata1 =0;
int adata2 =0;
int adata3 =0;
int adata4 =0;
int adata5 =0;
int adata6 =0;
int adata7 =0;

int data;
String cdata;
int a,b,c,d,x,y,z,e,f;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] ="AqoEYKLmTxvHGfFfUCEL9_NnXzhffa4m";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "manikant";
char pass[] = "manikant12";
int ap=90;
int bp=140;
int cp=95;
int fp=287;
int servoup=0;
int servofrnt=1;
int claw=2;
int base=3;
void setup()
{
pinMode(A0,INPUT);

  // Debug console
  Serial.begin(9600);
 
  pwm.begin();
 pwm.setPWMFreq(50);
  
arduinoUno.begin(9600);
 // timer.setInterval(1000L, sendUptime);
  timer1.setInterval(1000L, sendUptime1);
   timer.setInterval(1000L, sendUptime);

// pwm.setPWM(servoup,0,ap);
 
// pwm.setPWM(servofrnt,0,bp);
 
// pwm.setPWM(claw,0,cp);
  
 //pwm.setPWM(base,0,fp);
  
// pwm.setPWM(base,0,fp);
  Blynk.begin(auth, ssid, pass);
 
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
 //   pulseSensor.analogInput(PulseWire);   
 // pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
 // pulseSensor.setThreshold(Threshold);   
  // if (pulseSensor.begin()) {
  //  Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
   delay(10);
  }
   


/*void sendUptime()
{
   int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".


if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);   
   Blynk.virtualWrite(V8,myBPM);
   
 // Print th value inside of myBPM. 
}
  
  }*/
  void sendUptime1()
{
  if(data<30)
  {
    data=0;
    
    }
     if(data>30 && data<90)
    {
      data=data+30;
         Blynk.virtualWrite(V6,data);
          // "myBPM" hold this BPM value now. 
        Serial.println(data);  
    }
 
   
  }
   void sendUptime()
{
     float temperature = analogRead(A0);//lm35 is connected to pin A0 on NodeMcu
  temperature = (temperature * resolution);
 temperature = temperature * 25.0;
  Serial.print("LM35 temperature: ");//serial print the value 
  Serial.println(temperature);
  float t=(temperature*1.8)+32+7;
Blynk.virtualWrite(V8,temperature+15.0);
delay(500);
Blynk.virtualWrite(V8,temperature+16.004);

// Blynk.virtualWrite(V6,data);
          // "myBPM" hold this BPM value now. 
     //   Serial.println(data);
    

         
  }
  
  
void loop()
{
  
  if(Serial.available()==0)
  {
  Blynk.run();
   timer.run();
   
  if(a>=0)
   {
    
  if(ap>a)
  {
    Serial.println(ap);
    for(int j=ap; j>=a; j--)
    {
       
      pwm.setPWM(servoup,0,j);
      delay(5);
      }
    }
     if(ap<a)
  {
    
    for(int j=ap; j<=a; j++)
    {
      
      pwm.setPWM(servoup,0,j);
      delay(5);
      }
    }
   ap=a;
   }
   if(b>0)
   {
   if(bp>b)
  {
    for(int j=bp; j>=b; j--)
    {
      pwm.setPWM(servofrnt,0,j);
      delay(5);
      }
    }
     if(bp<b)
  {
    for(int j=bp; j<=b; j++)
    {
      pwm.setPWM(servofrnt,0,j);
      delay(5);
      }
    }
   bp=b;
   }
   if(c>0)
   {
    if(cp>c)
  {
    for(int j=cp; j>=c; j--)
    {
      pwm.setPWM(claw,0,j);
      delay(5);
      }
    }
     if(cp<c)
  {
    for(int j=cp; j<=c; j++)
    {
      pwm.setPWM(claw,0,j);
      delay(5);
      }
    }
   cp=c;
   }
   if(f>0)
   {
    if(fp>f)
  {
    for(int j=fp; j>=f; j--)
    {
      pwm.setPWM(base,0,j);
      delay(5);
      }
    }
     if(fp<f)
  {
    for(int j=fp; j<=f; j++)
    {
      pwm.setPWM(base,0,j);
      delay(5);
      }
    }
   fp=f;
   }
 //   pwm.setPWM(servoup,0,a);
  // pwm.setPWM(servofrnt,0,b);
  //pwm.setPWM(claw,0,c);
  //  pwm.setPWM(base,0,f);
    adata1 =x;
  adata2 =y;
  adata3 =d;
   adata4 =e;
 //  adata5=b;
  // adata6=c;
   //   adata7=d;

  
  cdata=cdata + adata1+","+adata2+","+adata3+","+adata4;//+","+adata5+","+adata6+","+adata7;
   Serial.println(cdata);
   arduinoUno.println(cdata);
     
   delay(1000);
   cdata="";
 
   if((d==0&&e==0))
   {
    digitalWrite(0,HIGH);
    }
  
   
   
  }
  
     if ( arduinoUno.available()>0)
  {
     timer1.run();
   

     data=arduinoUno.parseInt();
     //Serial.println(data1);
     
  }
  
  
       
 
   
 
 // middle.write(a);
 //leftt.write(b);
  //rightt.write(c);
  //claw.write(f);

  
  
}
BLYNK_WRITE(V0)

{
     d = param[0].asInt();
}
BLYNK_WRITE(V1)

{  
   x = param[0].asInt();
   y = param[1].asInt();
   //Serial.println(x);

 // moveControl(x,y); 
 }
BLYNK_WRITE(V2)

{    a = param[0].asInt();
    
    
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
     e = param[0].asInt();
}
BLYNK_WRITE(V7)

{
     f = param[0].asInt();
}
