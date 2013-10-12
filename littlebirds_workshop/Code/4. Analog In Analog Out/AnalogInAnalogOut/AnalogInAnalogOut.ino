
//
//  AnalogInAnalogOut  by Justin James Clayden
//  - Maps the value of analogInput 0 to PWM on pin 5
//

#define xpot A3
#define ypot A2
#define red 6
#define green 5
#define blue 3

void setup() {
	// Defines
	pinMode(xpot, INPUT);
	pinMode(ypot, INPUT);
	pinMode(red, INPUT);
	pinMode(green, INPUT);
	pinMode(blue, INPUT);

}

void loop() {
	int xpotValue = analogRead(xpot);
	int ypotValue = analogRead(ypot);

	int redv = map(xpotValue, 0, 1023, 255, 0);
	int bluev = map(ypotValue, 0, 1023, 0, 255);

	analogWrite(red, redv); 
	analogWrite(blue, bluev);
	
	delay(50); 

}
