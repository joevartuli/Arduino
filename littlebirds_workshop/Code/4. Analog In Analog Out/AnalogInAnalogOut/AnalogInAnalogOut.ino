
//
//  AnalogInAnalogOut  by Justin James Clayden
//  - Maps the value of analogInput 0 to PWM on pin 5
//

#define xpot A3
#define ypot A2
#define red 6
#define green 5
#define blue 3
#define speaker 7
#define rumble 4


void setup() {
	// Defines
	pinMode(xpot, INPUT);
	pinMode(ypot, INPUT);
	pinMode(red, OUTPUT);
	pinMode(green, OUTPUT);
	pinMode(blue, OUTPUT);
	pinMode(speaker, OUTPUT);
	pinMode(rumble, OUTPUT);

	digitalWrite(rumble, HIGH); 
	delay(1000);
	digitalWrite(rumble, LOW); 

}

void loop() {
	int xpotValue = analogRead(xpot);
	int ypotValue = analogRead(ypot);

	int redv = map(xpotValue, 0, 1023, 255, 0);
	int bluev = map(ypotValue, 0, 1023, 0, 255);

	analogWrite(red, redv); 
	analogWrite(blue, bluev);
	
	delay(50);

	// for (int i = 5; i < 150; i++) {
	// 	for (int j = 0; j < 10; j++) {
	// 		digitalWrite(speaker, HIGH); 
	// 		delay(.1*i);
	// 		digitalWrite(speaker, LOW); 
	// 		delay(.1*i);
	// 	}
	// } 

}
