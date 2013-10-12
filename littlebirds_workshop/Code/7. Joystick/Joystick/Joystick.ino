#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008

// Joystick Game Client by Justin James Clayden
// FOR YOU TO DO!
// - Set your MAC addy and IP below- you'll find them on your silver sticker

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0B }; // Change the last byte to the one we assigned to you.
//IPAddress ip(192, 168, 1, 100);  // Change the last number to the one we assigned to you.
IPAddress ip(192, 168, 1, 111);  // Change the last number to the one we assigned to you.


#define JOY_X A3
#define JOY_Y A2
#define PAD_up 8
#define PAD_down A1
#define PAD_left 9
#define PAD_right 12 // Interfers with Ethernet.. :(

#define RGB_Red 6
#define RGB_Grn 5
#define RGB_Blu 3

#define SPK 7
int speaker_pitch = 50; // Unsupported
long last_millis;
boolean speaker_state = false;

#define RUMBLE 4

boolean DEBUG_Serial = false;

unsigned int localPort = 8888;      // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char ReplyBuffer[] = "XABF";       // a string to send back  (X Joystick, Accell button, Brake button)

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup() {
  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);

  Serial.begin(9600);

  if (DEBUG_Serial) {
    Serial.println("Booting");
  }

  pinMode(PAD_up, INPUT);
  pinMode(PAD_down, INPUT);
  pinMode(PAD_left, INPUT);

  pinMode(RGB_Red, OUTPUT);
  pinMode(RGB_Grn, OUTPUT);
  pinMode(RGB_Blu, OUTPUT);

  pinMode(SPK, OUTPUT);
  pinMode(RUMBLE, OUTPUT);

  // Rumble test
  for (int r=1; r<3; r++) {
    digitalWrite(RUMBLE, HIGH);
    delay(500);
    digitalWrite(RUMBLE, LOW);
    delay(300);
  }

  // Noise test
  fireTest();
  fireTest();

  // Flash 'em!
  analogWrite(RGB_Blu, 0);
  analogWrite(RGB_Grn, 0);
  for (int r=0; r<255; r+=8) {
    analogWrite(RGB_Red, r);
    delay(10);
  }
  analogWrite(RGB_Red, 0);

  for (int g=0; g<255; g+=8) {
    analogWrite(RGB_Grn, g);
    delay(10);
  }
  analogWrite(RGB_Grn, 0);

  for (int b=0; b<255; b+=8) {
    analogWrite(RGB_Blu, b);
    delay(10);
  }
  analogWrite(RGB_Blu, 0);

  //
 // last_millis = millis();

}

void loop() {

//  // Idle the speaker
//
//  long elapsed_millis = millis() - last_millis;
//  last_millis = millis();
//  // Silence if pitch is 0
//  if (speaker_pitch > 0) {
//    if (elapsed_millis % speaker_pitch == 0) {
//      // Toggle the speaker
//      speaker_state = !speaker_state;
//      digitalWrite(SPK, speaker_state);
//    }
//  }

  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();

  if(packetSize)
  {
    if (DEBUG_Serial) {
      Serial.print("Received packet of size ");
      Serial.println(packetSize);
      Serial.print("From ");
      IPAddress remote = Udp.remoteIP();
      for (int i =0; i < 4; i++)
      {
        Serial.print(remote[i], DEC);
        if (i < 3)
        {
          Serial.print(".");
        }
      }
      Serial.print(", port ");
      Serial.println(Udp.remotePort());
    }

    // read the packet into packetBufffer
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    if (DEBUG_Serial) {
      Serial.println("Contents:");
      Serial.println(packetBuffer);
    }
    // Parse the packetBuffer for peripheral driving info.
    // Element
    // 0: Red
    // 1: Green
    // 2: Blue
    // 3: Make noise
    // 4: Rumble actuation

    analogWrite(RGB_Red, packetBuffer[0]);
    analogWrite(RGB_Grn, packetBuffer[1]);
    analogWrite(RGB_Blu, packetBuffer[2]);

    // TODO: Pitch from packetBuffer[3];
    //speaker_pitch = packetBuffer[3];
    if (packetBuffer[3] != 0) fireNoise();

    if (packetBuffer[4] == 0) {
      digitalWrite(RUMBLE, LOW);
    } 
    else {
      digitalWrite(RUMBLE, HIGH);
    }

    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    
    // If the fire button is held down, fire! (Nope, only if the server allows it)

    // Format the packet
    sprintf(ReplyBuffer,"%c%i%i%i",XJoy(),buttonPressed(PAD_up),buttonPressed(PAD_down),buttonPressed(PAD_left));
    //Serial.println(ReplyBuffer);
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
  delay(10);
}

void fireTest() {
  for (int t=0; t<3; t++) {
    for (int s=0; s<3; s++) {
      for (int i=5; i<150; i+=2) {
        digitalWrite(SPK, HIGH);
        delayMicroseconds(50);
        digitalWrite(SPK, LOW);
        delayMicroseconds(i+3*i);
      }
    }
  }
}

void fireNoise() {
    for (int s=0; s<3; s++) {
      for (int i=5; i<150; i+=20) {
        digitalWrite(SPK, HIGH);
        delayMicroseconds(50);
        digitalWrite(SPK, LOW);
        delayMicroseconds(i+3*i);
      }
    }
}

// Joystick and button pad support
//////////////////////////////////



// Map the X joystick to a more useful range.  Do it in a single digit for MAX power, er.. efficiency
byte XJoy() {

  // read the X joystick and map it to a limited character range (i.e. legal ASCII) 32-255
  byte x_joy = 32 + (1023-analogRead(JOY_X))/8;  
  
  if (x_joy > 90 && x_joy < 102) x_joy = 96;

  return x_joy;// TODO if you like: Be forgiving about the center position
  

}


// Helper Function for buttons and joystick
// TRUE FALSE  1 0
boolean buttonPressed(int button_number) {

  // Special-case PAD_down, as it is an analog input
  if (button_number == PAD_down) {
    return (analogRead(PAD_down) == 0);
  } 
  else {
    return (digitalRead(button_number) == 0); 
  }

}




