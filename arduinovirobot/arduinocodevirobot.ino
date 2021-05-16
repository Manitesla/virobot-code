
 #include <Wire.h>
 #include <SoftwareSerial.h>
 // create servo object to control a servo
// twelve servo objects can be created on most boards
//#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
//#include <PulseSensorPlayground.h> 
 SoftwareSerial nodemcu(2,3); // RX, TX
long int data;
//PulseSensorPlayground pulseSensor;  
String mystring;
char rdata;
int obstacle=A4;
#define lmotorf 4 //Motor A1
#define lmotorb 5 //Motor A2
#define rmotorf 6 //Motor B1
#define rmotorb 7 //Motor B2
#define enbb 10
#define enba 9
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                      
int uvled=A1;
int  line_val [ 5 ]={0};
int  near_val = 0 ; 
int  clp_val = 0 ; 
int  i ,near=1,clp=0,n=0;
int s2=12,s3=11,s4=8,s1=A2,s5=A3;
int maspeed=125,mbspeed=125;//115

int firstvalue,secondvalue,thirdvalue,fourtvalue,z=128,fifthvalue,sixvalue,sevenvalue;
int minRange = 312;
int maxRange = 712;
int noSpeed = 0;
void linefollow();
void moveControl();
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

//HIGH black
//LOW white

void setup() {
pinMode(lmotorf,OUTPUT);
pinMode(rmotorf,OUTPUT);
pinMode(lmotorb,OUTPUT);
pinMode(rmotorb,OUTPUT);
pinMode( enbb,OUTPUT);
pinMode( enba,OUTPUT);
  pinMode(A0,INPUT);
   pinMode( uvled,OUTPUT);
   pinMode(obstacle,INPUT);
// middle.attach(9); 
// leftt.attach(10); 
//rightt.attach(13); 
//claw.attach(6); 
Serial.begin ( 9600 ) ; 
  nodemcu.begin(9600);
    pinMode ( s2, INPUT ) ; 
    
    pinMode ( s3 , INPUT ) ; 
    
    pinMode ( s4, INPUT ) ; 
     pinMode ( s1, INPUT ) ; 
      pinMode ( s5, INPUT ) ; 
   
    pinMode ( near , INPUT ) ; 
    pinMode ( clp , INPUT ) ; 
//      pulseSensor.analogInput(PulseWire);   
  //pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  //pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
  // if (pulseSensor.begin()) {
   // Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
//  }
}
void  read_sensor ( ) 
{ 
  line_val [ 1 ] = digitalRead ( s1 ) ; 
    line_val [ 2 ] = digitalRead ( s2 ) ; 
     line_val [ 3 ] = digitalRead ( s3 ) ; 
      line_val [ 4 ] = digitalRead ( s4) ; 
      line_val [ 5 ] = digitalRead ( s5 ) ; 
      Serial.print(    "s1 = ");
    Serial.print(     line_val [ 1 ]);
    Serial.print(    "\t ");
      Serial.print(    "s5 = ");
     Serial.print(  line_val [ 5 ]);
        Serial.print(    "\t ");
       Serial.print(    "s2 = ");
      Serial.println(   line_val [ 2 ]);
   
 
 // near_val = digitalRead ( near ) ; 
 // clp_val = digitalRead ( clp ) ; 
}

void loop() {
//read_sensor ( ) ;

   // run over and over
  if (nodemcu.available()>0) {
    
 
      
     //  Serial.println(temperature1);
  
    
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
     String o = getValue(mystring,',',3);
    //   String p = getValue(mystring,',',4);
     //    String q = getValue(mystring,',',5);
      //     String r = getValue(mystring,',',6);
 
  firstvalue= l.toInt();
   secondvalue=m.toInt();
   thirdvalue=n.toInt();
  fourtvalue=o.toInt();
//  fifthvalue=p.toInt();
 // sixvalue=q.toInt();
  //sevenvalue=r.toInt();
   
   
    mystring="";
/*
     float temperature = analogRead(A0);//lm35 is connected to pin A0 on NodeMcu
  temperature = (temperature * resolution);
  temperature = temperature * 111.0;
 // Serial.print("LM35 temperature: ");//serial print the value 
  Serial.println(temperature);*/

    
   Serial.println(secondvalue);
      Serial.println(thirdvalue);
       Serial.println("\t");   
        Serial.println(fourtvalue);
        Serial.println(firstvalue);
      //    Serial.println(sixvalue);
      //     Serial.println(sevenvalue);
         
     if(fourtvalue==1 && thirdvalue==1)
     {
      int myBPM =analogRead(A0);
      Serial.println(myBPM);
      int my=map(myBPM,490,950,50,90);
      
      Serial.println(my);
       nodemcu.write(my);
   
      nodemcu.println(my);
      //analogWrite( uvled,255);
      
      
      }
        if(fourtvalue==0 && thirdvalue==0)
     {
     digitalWrite( uvled,HIGH);
     }
       else
       {
        digitalWrite( uvled,LOW);
        }
     }
  //  claw.write(0); 
   }
    
   
   
 /*else if(nodemcu.available()==0)
  {
 int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
  //   Serial.println(myBPM);                                           // "myBPM" hold this BPM value now. 
// Serial.println(myBPM); 
if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
//Serial.println(myBPM); 

    nodemcu.write(myBPM);
    
      nodemcu.println(myBPM);
}
  }
   */  
  
 
 /*  if(digitalRead(obstacle)==1)
   {
    
    
digitalWrite(lmotorf,LOW);
digitalWrite(rmotorf,LOW);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
    }*/

  if(thirdvalue==0 && fourtvalue==1 )
      {
        read_sensor ( ) ;
        linefollow();
      
   //    Serial.println("linefollow ");
      } 
  if( thirdvalue==1 && fourtvalue==0 )
      {
       moveControl( firstvalue, secondvalue); 
    //   Serial.println("movecontrol progrm ");
      }
    
 }
void moveControl(int x, int y)
{
  

   if(x >= minRange && y >= maxRange && x<=maxRange)  
  { 
 //   z=-255./512.*firstvalue+255.;
// z=((-255./512.)*secondvalue)+255.;
    analogWrite(enbb,z);
analogWrite(enba,z);  
  digitalWrite(lmotorb,HIGH);
  digitalWrite(rmotorb,HIGH);
  digitalWrite(lmotorf,LOW);
  digitalWrite(rmotorf,LOW);
 
  }
else if(x >= minRange && y <= minRange && x<= maxRange)
  {    // z=((255./512.)*secondvalue)-255.;
    analogWrite(enbb,z);
analogWrite(enba,z);  
 digitalWrite(lmotorf,HIGH);
  digitalWrite(rmotorf,HIGH);
  digitalWrite(lmotorb,LOW);
  digitalWrite(rmotorb,LOW);
   
  }
    // move  right
  else if(y >= minRange && x >= maxRange && y<= maxRange)
  {  
    
    // z=((255./512.)*secondvalue)-255.;
    analogWrite(enbb,z);
analogWrite(enba,z);  
  digitalWrite(lmotorf,HIGH);
  digitalWrite(rmotorf,LOW);
  digitalWrite(rmotorb,HIGH);
  digitalWrite(lmotorb,LOW);

 
  }

  // moveleft
  else if(y >= minRange && x <= minRange && y <= maxRange)  
  {
    // z=-255./512.*secondvalue+255.;
       //  z=((-255./512.)*secondvalue)+255.;
      // int z1=125;
  analogWrite(enbb,z);
analogWrite(enba,z);  
  digitalWrite(lmotorf,LOW);
  digitalWrite(rmotorf,HIGH);
  digitalWrite(rmotorb,LOW);
  digitalWrite(lmotorb,HIGH);  
}
 // move forward LEFT
 

  else if(y < maxRange && y > minRange && x < maxRange && x > minRange)
  {
  digitalWrite(enbb,LOW);
  digitalWrite(enba,LOW);
  digitalWrite(lmotorf,LOW);
  digitalWrite(lmotorb,LOW);
  digitalWrite(rmotorf,LOW);
  digitalWrite(rmotorb,LOW);
  }
}


void linefollow()
{
   // maspeed=fourtvalue,mbspeed=fourtvalue;
if((line_val [ 4 ]==LOW)&&(line_val [ 3 ]==LOW)&&(line_val [2]==LOW)) 
{

digitalWrite(lmotorf,LOW);
digitalWrite(rmotorf,LOW);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
//n++;
/*
if(n==1)
{
   Serial.println(    "N = ");
    Serial.print(   n);
    Stop();
    delay(1500);
  forward();
  delay(250);
  left();
   delay(1900);

  
  }
  if(n==2)
{
    Stop();
    delay(1500);
     forward();
  delay(150);
  right();
   delay(2300);

  
  }
*/

}
 else if((line_val [ 4 ]==HIGH)&&(line_val [ 3 ]==HIGH)&&(line_val [2]==HIGH)) 
{
  analogWrite(enbb,mbspeed);
analogWrite(enba,maspeed); 
digitalWrite(lmotorf,LOW);
digitalWrite(rmotorf,LOW);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);


}
  else if(((line_val [ 4 ]==HIGH)&&(line_val [ 3 ]==LOW)&&(line_val [2]==HIGH))||((line_val [ 5 ]==HIGH)&&(line_val [ 4 ]==HIGH)&&(line_val [ 3 ]==LOW)&&(line_val [2]==HIGH)&&(line_val [ 1 ]==HIGH) )) 
{
analogWrite(enbb,mbspeed);
analogWrite(enba,maspeed);
digitalWrite(lmotorf,HIGH);
digitalWrite(rmotorf,HIGH);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}
  else if(((line_val [ 4 ]==LOW)&&(line_val [ 3 ]==LOW)&&(line_val [2]==HIGH))||((line_val [5]==LOW)&&(line_val [ 4 ]==LOW)&&(line_val [ 3 ]==LOW)&&(line_val [2]==HIGH)&&(line_val [1]==HIGH)) )
{
analogWrite(enbb,mbspeed);
analogWrite(enba,maspeed);
digitalWrite(lmotorf,HIGH);
digitalWrite(rmotorf,LOW);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,HIGH);
}
  else if(((line_val [ 4 ]==LOW)&&(line_val [ 3 ]==HIGH)&&(line_val [2]==HIGH))||(( line_val [ 5 ]==LOW)&&(line_val [ 4 ]==LOW)&&(line_val [ 3 ]==HIGH)&&(line_val [2]==LOW)&&(line_val [1]==HIGH) ))
{
analogWrite(enbb,mbspeed);
analogWrite(enba,maspeed);
digitalWrite(lmotorf,HIGH);
digitalWrite(rmotorf,LOW);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,HIGH);
}
   else if(((line_val [ 4 ]==HIGH)&&(line_val [ 3 ]==LOW)&&(line_val [2]==LOW))||((line_val [ 5 ]==HIGH)&&(line_val [ 4 ]==HIGH)&&(line_val [ 3 ]==LOW)&&(line_val [2]==LOW)&&(line_val [ 1]==LOW)) )
{
analogWrite(enbb,mbspeed);
analogWrite(enba,maspeed);
digitalWrite(lmotorf,LOW);
digitalWrite(rmotorf,HIGH);
digitalWrite(lmotorb,HIGH);
digitalWrite(rmotorb,LOW);
}
   else if(((line_val [ 4 ]==HIGH)&&(line_val [ 3 ]==HIGH)&&(line_val [2]==LOW))|| ((line_val [ 5 ]==HIGH)&&(line_val [ 4 ]==LOW)&&(line_val [ 3 ]==LOW)&&(line_val [2]==LOW)&&(line_val [ 1 ]==LOW)))
{
analogWrite(enbb,mbspeed);
analogWrite(enba,maspeed);
digitalWrite(lmotorf,LOW);
digitalWrite(rmotorf,HIGH);
digitalWrite(lmotorb,HIGH);
digitalWrite(rmotorb,LOW);
}
/*  else
{
digitalWrite(lmotorf,LOW);
digitalWrite(rmotorf,LOW);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}*/
 // }
else
{
    analogWrite(enbb,mbspeed);
analogWrite(enba,maspeed);
digitalWrite(lmotorf,LOW);
digitalWrite(rmotorf,LOW);
digitalWrite(lmotorb,LOW);
digitalWrite(rmotorb,LOW);
}

}
  
