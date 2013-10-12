//
//  AnalogRead by Justin James Clayden
//  - Prints the value of analog port 0 to the Serial port
//

void setup() {
 
 Serial.begin(9600);
 analogReference(DEFAULT);
  
}

void loop() {
  
  Serial.println(analogRead(0));
  delay(250);
  
}
