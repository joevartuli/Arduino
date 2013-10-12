// HelloArduino by Justin James Clayden

// Demonstrate:
// Reading digital inputs
// Reading analog inputs
// printing to the Serial Port

// Compile and upload the sketch
// Open the serial port

#define yellow 8
#define red 12
#define blue 9
#define green A1
#define joystick A0
#define y_axis A2
#define x_axis A3


void setup() {
  Serial.begin(9600);
  Serial.println("Hello");
  delay(1000);
  Serial.println("Arduino");

  pinMode(yellow,INPUT);
  
}


void loop() {
  
  // Read a digital input
  boolean button_state = digitalRead(pin_a); // Happens to be the blue button
  
  // Read an analog input
  int x_stick = analogRead(a1); // Happens to be the X joystick
  
  // Print to the serial port
  Serial.print("X: ");
  Serial.print(x_stick);
  Serial.print(" Blue Button: ");
  Serial.println(button_state);
  
}
