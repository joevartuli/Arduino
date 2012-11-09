//--------------------------------------------------------------
//
// APC magazine - December 2012 edition
//
// Simple LED Weatherstation - (c) Darren Yates 13 October 2012
//
//--------------------------------------------------------------

#include <TimerOne.h>
#include <dht11.h>
dht11 DHT11;
#define DHT11PIN 11

// set up the Uno pins, 2-8: seven-segment display, 9-10: digit drivers
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int led5 = 6;
int led6 = 7;
int led7 = 8;
int dm1 = 9;
int dm2 = 10;

int inSwitch = 12;
int DHTread = 0;

byte pins[7] = {
  2,3,4,5,6,7,8};
byte numbers[21][7] = { // can't take credit for this but it's a clever way of storing SSD digit data
  { 1,1,1,1,1,1,0  }, //zero {c,d,e,b,a,f,g}
  { 1,0,0,1,0,0,0  }, //one
  { 0,1,1,1,1,0,1  }, //two
  { 1,1,0,1,1,0,1  }, //three
  { 1,0,0,1,0,1,1  }, //four
  { 1,1,0,0,1,1,1  }, //five
  { 1,1,1,0,1,1,1  }, //six
  { 1,0,0,1,1,0,0  }, //seven
  { 1,1,1,1,1,1,1  }, //eight
  { 1,1,0,1,1,1,1  }, //nine
  { 0,0,0,0,0,0,0  }, //off
  { 0,0,0,1,1,1,1  }, //degree - 11
  { 0,1,1,0,1,1,0  }, //C - 12
  { 0,0,1,0,0,0,1  }, //r - 13
  { 1,0,1,0,0,1,1  }, //h - 14
  { 1,1,1,1,0,0,1  }, //d - 15
  { 1,1,0,1,0,1,1  }, //y - 16
  { 0,1,1,0,1,1,1  }, //E - 17
  { 0,0,0,0,0,0,1  }, //- - 18
  { 0,0,0,1,1,1,1  }, // o - 19 (top percent)
  { 1,1,1,0,0,0,1  } // bottom o - 20 (bottom percent)
};

byte digit1 = 15;
byte digit2 = 16;

void setup() { // setup loop, run only once at the start

  for (int y=2; y < 9; y++) {
    pinMode (y, OUTPUT); // set required pins 2-8 to OUTPUT mode
  }
  pinMode(dm1,OUTPUT); // set pin 'dm1' to output mode
  pinMode(dm2,OUTPUT); // set pin 'dm2' to output mode
  digitalWrite(dm1,HIGH); // pull pin 'dm1' high
  digitalWrite(dm2,LOW); // push pin 'dm2' low

  pinMode(inSwitch,INPUT_PULLUP); // set pin 'inSwitch' to use internal pull-up resistor

  Timer1.initialize(8000);  // set display time per digit (microseconds), 8000 = 125Hz
  Timer1.attachInterrupt(update); // when timer overruns, call the 'update' procedure below

  delay(2000); // do nothing for two seconds

  DHTread = DHT11.read(DHT11PIN); // read data from DHT11 sensor
  digit1 = 17; // set digit1 to 'E'
  switch (DHTread) // depending on the error code return, do one of the following:
  {
  case DHTLIB_OK: 
    digit2 = 0; // show 'E0'
    break;
  case DHTLIB_ERROR_CHECKSUM: 
    digit2 = 1; // show 'E1'
    break;
  case DHTLIB_ERROR_TIMEOUT: 
    digit2 = 2; // show 'E2'
    break;
  case DHTLIB_ERROR_ACKNOW: 
    digit2 = 3; // show 'E3'
    break;
  default: 
    digit2 = 4; // show 'E4'
    break;
  }
  delay(2000); // delay two seconds
  digit1=10; // digit1 turn off
  digit2=10; // digit2 turn off
  delay(1000); // delay one second
}

void update() { // this procedure sets up the two-digit multiplexing,
  // the timer interrupt means this runs every 8ms

  for (int i=2; i<8; i++) {
    digitalWrite(pins[i],LOW); // pull all seven-segment display elements low
  }

  digitalWrite(dm1, !digitalRead(dm1)); // swap dm1 pin state eg if it was high, make it low etc.
  digitalWrite(dm2, !digitalRead(dm2)); // swap dm2 pin state eg if it was high, make it low etc.

  if (digitalRead(dm1) == HIGH) { // if first digit is switched on,
    for(int x=0; x<8; x++) {
      digitalWrite(pins[x],numbers[digit1][x]); // write data to led pins based on the number to be displayed
    }
  }    

  if (digitalRead(dm2) == HIGH) { // if second digit is switched on,
    for(int x=0; x<8; x++) {
      digitalWrite(pins[x],numbers[digit2][x]); // write data to led pins based on the number to be displayed
    }
  }    

}

void showNumber(byte data) { // quicker way of separating a two-digit number to display of separate SSDs

  digit1 = data / 10; // find the tens digit (modulo)
  digit2 = data % 10; // find the units digit (remainder)

}

void loop() { // runs after the setup loop and runs continuously until reset or power removed

  showNumber(DHT11.temperature); // show the current two-digit temp
  delay(1000); // wait 1 second
  digit1 = 11; // show 'degrees C' code
  digit2 = 12;
  delay(1000); // wait 1 second
  digit1 = 10; // blank both displays
  digit2 = 10; // 
  delay(1000); // wait 1 second
  showNumber(DHT11.humidity); // show two-digit humidity reading
  DHTread = DHT11.read(DHT11PIN); // read new data from DHT11
  delay(1000); // wait 1 second
  digit1 = 19; // show percentage symbol
  digit2 = 20;
  //delay(1000); // wait 1 second
  //digit1 = 13; // show 'r' on digit1
  //digit2 = 14; // show 'h' on digit2
  delay(1000); // wait 1 second
  digit1 = 10; // show '-' on digit1
  digit2 = 10; // show '-' on digit2
  delay(1000); // wait 1 second, then loop again...

}


