
/* 
    This code is in the public domain
    For use with "Link2fs_Multi"
    Jimspage.co.nz
    My thanks to the Guys that gave me snippets of code. 
    
    This sets the complete Arduino card for "keys" input except pin 13.
    Attach a switch to any pin (except 13) and program that pin in "Multi"
    Pin 13 is used for the servo to indicate flaps.
    For this servo code to work you must tick "<G" (Flap position) in Multi.
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
