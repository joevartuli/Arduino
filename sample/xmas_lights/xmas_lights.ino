int d12Pin = 12;
int d11Pin = 11;
int d10Pin = 10;
int d9Pin = 9;
int d8Pin = 8;
int d7Pin = 7;
int sequenceRate = 100;
int beatRate = 200;

void setup() {                
  pinMode(d12Pin, OUTPUT);
  pinMode(d11Pin, OUTPUT);
  pinMode(d10Pin, OUTPUT);
  pinMode(d9Pin, OUTPUT);
  pinMode(d8Pin, OUTPUT);
  pinMode(d7Pin, OUTPUT);
}

void loop() {
  flashInSequence();
  off(); delay(100);
  skipABeat();
  off(); delay(100);
  skipAnInverseBeat();
  off(); delay(100);
  inverseSwitch();
  off(); delay(2000);

} 

void flashInSequence() {
  offOnSwith(d7Pin, d12Pin); delay(sequenceRate);
  offOnSwith(d12Pin, d11Pin); delay(sequenceRate);
  offOnSwith(d11Pin, d10Pin); delay(sequenceRate);
  offOnSwith(d10Pin, d9Pin); delay(sequenceRate);
  offOnSwith(d9Pin, d8Pin); delay(sequenceRate);
  offOnSwith(d8Pin, d7Pin); delay(sequenceRate);
}

void skipABeat() {
  offOnSwith(d8Pin, d12Pin); delay(beatRate);
  offOnSwith(d12Pin, d10Pin); delay(beatRate);
  offOnSwith(d10Pin, d8Pin); delay(beatRate);
}

void skipAnInverseBeat() {
  offOnSwith(d8Pin, d11Pin); delay(beatRate);
  offOnSwith(d11Pin, d9Pin); delay(beatRate);
  offOnSwith(d9Pin, d7Pin); delay(beatRate);
}

void inverseSwitch() {
  turnOnOdds();
  delay(1000);
  turnOffOdds();
  turnOnEvens();
  delay(1000);
}

void turnOnOdds() {
   digitalWrite(d7Pin, HIGH); 
   digitalWrite(d9Pin, HIGH); 
   digitalWrite(d11Pin, HIGH);
}

void turnOffOdds() {
   digitalWrite(d7Pin, LOW);
   digitalWrite(d9Pin, LOW);
   digitalWrite(d11Pin, LOW);   
}

void turnOnEvens() {
  digitalWrite(d8Pin, HIGH);
  digitalWrite(d10Pin, HIGH);
  digitalWrite(d12Pin, HIGH);   
}

void turnOffEvens() {
  digitalWrite(d8Pin, LOW);
  digitalWrite(d10Pin, LOW);
  digitalWrite(d12Pin, LOW); 
}

void offOnSwith(int offPin, int onPin) {
  digitalWrite(onPin, HIGH);
  digitalWrite(offPin, LOW);
}

void off() {
 for (int i = d7Pin; i <= d12Pin; i++) {
   digitalWrite(i, LOW); 
 } 
 
}

