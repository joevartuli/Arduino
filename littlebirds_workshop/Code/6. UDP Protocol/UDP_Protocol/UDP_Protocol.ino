// UDP Protocol - hacked from Examples:Ethernet:UDPSendReceiveString
// Receive packets from the server and do something with it
// Send packets to the server on the basis of joystick position

#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008

#define JOY_X A3
#define LED_Pin 3
#define LED_GND 2

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x10 }; // Set this last byte to the one on your silver sticker
IPAddress ip(192, 168, 1, 116); // Set this last digit to the one on your silver sticker

unsigned int localPort = 8888;      // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "X ";       // a string to send back

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup() {
  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);

  Serial.begin(9600);
  
  Serial.println("Booting");
  
  pinMode(LED_Pin, OUTPUT);
  pinMode(LED_GND, OUTPUT);
  digitalWrite(LED_GND, LOW);
  
  for (int i=0; i<100; i++) {
    digitalWrite(LED_Pin, HIGH);
    delay(20);
    digitalWrite(LED_Pin, LOW);
    delay(20);
  }
}

void loop() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if(packetSize)
  {
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

    // read the packet into packetBufffer
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.println(packetBuffer);
    
    // Parse out the value
    if (packetBuffer[0] == '1') {
     digitalWrite(LED_Pin, HIGH); 
    } else {
     digitalWrite(LED_Pin, LOW); 
    }

    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    // Read the X Joystick
    int joy_val = 255-analogRead(JOY_X)/4;
    // Structure the reply packet
    sprintf(ReplyBuffer, "%i", 255);
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
  delay(10);
}

