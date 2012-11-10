int d13Pin = 13;

void setup() {                
  pinMode(d13Pin, OUTPUT);     
}

void loop() {
  flashAtRate(200);
  flashAtRate(1000);
  flashAtRate(200);
  delay(4000);
} 

void flashAtRate(int rate) {
  delay(rate);
  digitalWrite(d13Pin, HIGH);
  delay(rate);
  digitalWrite(d13Pin, LOW);
  delay(rate);
  digitalWrite(d13Pin, HIGH);
  delay(rate);
  digitalWrite(d13Pin, LOW);
  delay(rate);
  digitalWrite(d13Pin, HIGH);
  delay(rate);
  digitalWrite(d13Pin, LOW);
}
