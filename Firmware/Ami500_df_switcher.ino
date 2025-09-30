/******************************************
 * 
 * Amiga 500 / 500+ DF switcher V. 1.0
 * -----------------------------------
 * 
 * Controller: Attiny25 
 *  
 * pin6: buzzer
 * pin7: 4066 switch normal
 * pin8: 4066 switch inverted
 * pin9: reset line (low=active)
 * 
 * pin1 (6): buzzer
 * pin3 (2): 4066 switch normal
 * pin4 (3): 4066 switch inverted
 * pin2 (7): reset line (low=active)
 * 
 * do 2 reset within 2 seconds to changhe df 1/0
 * Fuse: clk/8 - 8Mhz internal clock
*/

#include <EEPROM.h>

const int Buzz = 0; //pin5;
const int Norm = 2; //pin7;
const int Revs = 4; //pin3;
const int Rset = 3; //pin2;
int rstState = 0;
int dfState = 0;
int lastState =1;
int numRes=0;
unsigned long delayStart = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(Buzz, OUTPUT);
  pinMode(Norm, OUTPUT);
  pinMode(Revs, OUTPUT);
  digitalWrite(Buzz, LOW);
  digitalWrite(Norm, LOW);
  digitalWrite(Revs, LOW);
  pinMode(Rset, INPUT_PULLUP);
  dfState =EEPROM.read(0);
  if (dfState>1){dfState=0;}
  setSwitch(dfState);
  delay(60);
}

void loop() {
  // read the state of the pushbutton value:
  rstState = digitalRead(Rset);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (rstState == LOW && lastState == 1) {
    lastState=0;
   }

    //flip-flop state
    if (rstState == HIGH && lastState == 0) {
      numRes++;
      delayStart = millis(); 
      lastState=1;
    }

    //reset counter after 2sec
    if (numRes>0 && ((millis() - delayStart) >= 400)) { //330 = 2Sec. on attiny
      numRes=0;
    }

    //switch signal
    if (numRes>1){
      if (dfState==0) {
      setSwitch(1);
      dfState=1;
    } else {
      setSwitch(0);
      dfState=0;
    }
    numRes=0;
    EEPROM.write(0, dfState);
    delay(100);
    }


}

void setSwitch (int mState)
{
   if (mState==0) {
      digitalWrite(Revs, LOW);
      delay(1);
      digitalWrite(Norm, HIGH);
      digitalWrite(Buzz, HIGH);
      delay(60);
      digitalWrite(Buzz, LOW);
    } else {
      digitalWrite(Norm, LOW);
      delay(1);
      digitalWrite(Revs, HIGH);
      digitalWrite(Buzz, HIGH);
      delay(20);
      digitalWrite(Buzz, LOW);
      delay(20);
      digitalWrite(Buzz, HIGH);
      delay(40);
      digitalWrite(Buzz, LOW);
    }
}
