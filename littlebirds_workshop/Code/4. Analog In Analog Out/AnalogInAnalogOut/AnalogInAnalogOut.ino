
//
//  AnalogInAnalogOut  by Justin James Clayden
//  - Maps the value of analogInput 0 to PWM on pin 5
//

#define potIn 0
#define ledPin 5

void setup() {
  pinMode(potIn, INPUT);
  analogReference(DEFAULT);//INTERNAL);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
 
  int potInValue = analogRead(potIn);
  int mappedValue = map(potInValue, 0, 1023, 255, 0);
 Serial.println(potInValue);
 analogWrite(ledPin, mappedValue);
 delay(50); 
  
}
