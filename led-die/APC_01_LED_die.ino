//-------------------------------------------------------
//
// APC magazine - October 2012 edition
//
// LED Die - (c) Darren Yates 17 August 2012
// includes LED spin on down-press, slowing on up-press
//
//-------------------------------------------------------

// assign output pins to variables
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int led5 = 6;
int led6 = 7;
int led7 = 8;
// assign switch pin as input 
int inSwitch = 9;
// assign variables used elsewhere
int swPressed = 0;
int dloop = 0;
int roll = 0;
int ledloop = 0;
// assign LED combinations for each roll to an array
int die1[] = {
  led4};
int die2[] = {
  led2,led6};
int die3[] = {
  led1,led4,led7};
int die4[] = {
  led1,led2,led6,led7};
int die5[] = {
  led1,led2,led4,led6,led7};
int die6[] = {
  led1,led2,led3,led5,led6,led7};
int spin[] = {
  led1,led2,led5,led7,led6,led3};
int dieStop[] = {
};

// set LED pins to output mode
// set switch pin to use pull-up resistor (saves us a resistor!)
void setup() {
  for (int y=2; y < 9; y++) {
      pinMode (y, OUTPUT); // set required pins 2-8 to OUTPUT mode
  }
  pinMode(inSwitch,INPUT_PULLUP);
  digitalWrite(inSwitch,HIGH);
  
// light all LEDs for two seconds (2000ms) to test connections  
  for (int y=0; y < 6; y++) {
      digitalWrite(die6[y],HIGH); // light up the roll for a six
  }
  digitalWrite(led4,HIGH); // light up the middle LED too
 
 delay(2000); // wait two seconds
 
  for (int y=0; y < 6; y++) {
      digitalWrite(die6[y],LOW); // turn off the six LEDs for a 'six'
  }
  digitalWrite(led4,LOW); // turn off the middle LED
}

void loop() {
  // read switch input  
  int sw_check = digitalRead(inSwitch);
  // if not pressed, flash middle LED with 5% duty cycle, once every half-a-second.  
  if (sw_check == HIGH) {
    digitalWrite(led4,HIGH);
    delay(25);
    digitalWrite(led4,LOW);
    delay(475);
  }
  // otherwise
  else
    // while switch is pressed down, spin the die 
  {
    while (sw_check == LOW) {
      swPressed = 1;
      for(int x=0; x<6; x++) {
        sw_check = digitalRead(inSwitch);
        //        if(x==0) {digitalWrite(led3,LOW);}
        digitalWrite(spin[x-1],LOW);
        digitalWrite(spin[x],HIGH);
        delay(60); 
        digitalWrite(led3,LOW);
      }
    }
    // how switch as been left go, random run die roll and slow
    randomSeed(micros());
    if (swPressed==1) {
      swPressed = 0;
      for(dloop = 0; dloop < 50; dloop++) {
        delay(dloop);
        roll = random(1,7);        

        // turn all LEDs off         
        for (int y=2; y < 9; y++) {
          digitalWrite(y,LOW);
        }
        // light up LEDs based on value of (roll)        
        switch (roll) {
        case 1:
          digitalWrite(led4,HIGH);
          break;
        case 2:
          for (int y=0; y < 2; y++) {
            digitalWrite(die2[y],HIGH);
          }
          break;
        case 3:
          for (int y=0; y < 3; y++) {
            digitalWrite(die3[y],HIGH);
          }
          break;
        case 4:
          for (int y=0; y < 4; y++) {
            digitalWrite(die4[y],HIGH);
          }
          break;
        case 5:
          for (int y=0; y < 5; y++) {
            digitalWrite(die5[y],HIGH);
          }
          break;
        case 6:
          for (int y=0; y < 6; y++) {
            digitalWrite(die6[y],HIGH);
          }
        }
      }
      // when spin as stop, show value for three seconds, then restart      
      delay(3000); // 3000ms or 3s
      // turn off all LEDs
      for (int y=2; y < 9; y++) {
        digitalWrite(y,LOW);
      }
    }
  }
}

