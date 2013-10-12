//
//  DigitalInDigitalOut  by Justin James Clayden
//  - Maps the state of the button on buttonPin to the LED on ledPin
//
 
 int ledPin = 13;
 int buttonPin = 9;

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(ledPin, OUTPUT);  
  pinMode(buttonPin, INPUT); 
 
}

void loop() {
  
  boolean buttonValue = digitalRead(buttonPin);
  //digitalWrite(ledPin, !buttonValue);
  if (buttonValue == LOW) {  // On the input shield, LOW represents pressed
  digitalWrite(ledPin, HIGH);
  } else {
   digitalWrite(ledPin,LOW); 
  }
  
}
