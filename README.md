# Airspeed-Indicator-for-flight-simulation

Analog airspeed indicator for flight simulation with servo and 3d print.

## Hardware

I use an arduino uno with a servo motor driving a gear with a multiplication of 2.66. I need multiplication because servo can only turn from 0 to 180 degrees and the airspeed indicator need 360 degrees. For the structure and gears i use the files from alvaroalea : https://www.thingiverse.com/thing:2489322 . I just replaced the 3d printed axis by a metal axis.

## Software

To extract data from the flight simulator i use a software named Link2Fs from : http://www.jimspage.co.nz/intro.htm , it is very easy to extract the airspeed and transmit it via the serial connection to the arduino which control the servo. The fonction to drive the angle of the servo from the indicated airspeed is made of 2 linear regression to approximate the real gauge.
This is the code i use based on an exemple from the software.

![Multi_Keys_with_flaps_servo.ino](\Multi_Keys_with_flaps_servo.ino)

```C++


/* 
    This code is in the public domain
    For use with "Link2fs_Multi"
    Jimspage.co.nz
    My thanks to the Guys that gave me snippets of code, i've just modified to have a servo for the airspeed. 
    
    This sets the complete Arduino card for "keys" input except pin 13.
    Attach a switch to any pin (except 13) and program that pin in "Multi"
    Pin 13 is used for the servo to indicate airspeed.
    For this servo code to work you must tick "<P" (airspeed) in Multi.
    Everything to do with "Keys"  starts with a "K" in this code.

*/

#include <Servo.h>
Servo flapsServo;



int CodeIn;// used on all serial reads
int KpinNo; 
int Koutpin;
String flaps;

String KoldpinStateSTR, KpinStateSTR, Kstringnewstate,Kstringoldstate;

void setup() 
{
  Kstringoldstate = "111111111111111111111111111111111111111111111111111111111111111111111";
  
  for (int KoutPin = 2; KoutPin < 70; KoutPin++)// Get all the pins ready for "Keys"  
  {
    pinMode(KoutPin, INPUT);
    digitalWrite(KoutPin, HIGH);  
  }
 Serial.begin(115200); 
 pinMode(13, OUTPUT);// For the servo.
 flapsServo.attach(9);
 flapsServo.write(0);
  
}

void loop() {
  {KEYS();} //Check the "keys" section
  if (Serial.available()) {
    CodeIn = getChar();
    if (CodeIn == '=') {EQUALS();} // The first identifier is "="
    if (CodeIn == '<') {LESSTHAN();}// The first identifier is "<"
    if (CodeIn == '?') {QUESTION();}// The first identifier is "?"
    if (CodeIn == '/') {SLASH();}// The first identifier is "/" (Annunciators)
  }

}

char getChar()// Get a character from the serial buffer
{
  while(Serial.available() == 0);// wait for data
  return((char)Serial.read());// Thanks Doug
}

void EQUALS(){      // The first identifier was "="
 CodeIn = getChar(); // Get another character
  switch(CodeIn) {// Now lets find what to do with it
    case 'A'://Found the second identifier
       //Do something
    break;
     
    case 'B':
       //Do something
    break;
     
    case 'C':
       //Do something
    break;
     }
}

void LESSTHAN(){    // The first identifier was "<"
CodeIn = getChar(); // Get another character
  switch(CodeIn) {// Now lets find what to do with it
    case 'A'://Found the second identifier
       //Do something
    break;
     
    case 'B':
       //Do something
    break;
     
    case 'P'://Found the second identifier ("G" Flaps position)
      flaps = "";
      flaps += getChar();
      flaps += getChar();
      flaps += getChar();
      int flapsi = flaps.toInt(); 
      float fi;// convert it to an integer (Thanks Phill)
      //flapsi += 0;// Manual correction to suit servo zero.
      if(flaps == "001")
      {
        flapsServo.write(0);
      }
      if(flapsi > 100)
      {
      fi = (1.8625*flapsi - 35)/2.66; 
      }
      else
      {
       fi = (1.8625*flapsi - 55)/2.66;
      }
      flapsServo.write(fi); // Manual fiddle to get full span of servo.
      // Note.. Using the "Map" method slows it down.
      //Serial.println(fi); // Used for testing
    break;
     }
}

void QUESTION(){    // The first identifier was "?"
CodeIn = getChar(); // Get another character
  switch(CodeIn) {// Now lets find what to do with it
    case 'A'://Found the second identifier
       //Do something
    break;
     
    case 'B':
       //Do something
    break;
     
    case 'C':
       //Do something
    break;
     }
}
void SLASH(){    // The first identifier was "/" (Annunciator)
  //Do something
}
void KEYS() 
{
  Kstringnewstate = "";
  for (int KpinNo = 2; KpinNo < 70; KpinNo++){
    KpinStateSTR = String(digitalRead(KpinNo)); 
    KoldpinStateSTR = String(Kstringoldstate.charAt(KpinNo - 2));
    if (KpinStateSTR != KoldpinStateSTR)
    {
      if (KpinNo != 13){
      //Serial.print ("D"); 
      if (KpinNo < 10) Serial.print ("0");
      //Serial.print (KpinNo);
      //Serial.println (KpinStateSTR);
      }
    }
    Kstringnewstate += KpinStateSTR;
  }
  Kstringoldstate = Kstringnewstate;
}
```
