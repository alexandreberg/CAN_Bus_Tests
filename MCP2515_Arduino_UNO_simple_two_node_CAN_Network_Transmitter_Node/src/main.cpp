/* Testing the communication of a MCP2515 + TJA1050  board with Arduino UNO
Based on the Site: https://lastminuteengineers.com/mcp2515-can-module-arduino-tutorial/

Connections:
Arduino UNO - MCP2515
+5V - Vcc
GND - GND
10 - CS
12 - SO
11 - SI
13 - SCK
2 - INT

The comunication worked.
*/

#include <Arduino.h>

// Transmitter Node
#include <CAN.h>

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("CAN Sender");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending packet ... ");

  CAN.beginPacket(0x12);
  CAN.write('h');
  CAN.write('e');
  CAN.write('l');
  CAN.write('l');
  CAN.write('o');
  CAN.endPacket();

  Serial.println("done");

  delay(1000);

  // send extended packet: id is 29 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending extended packet ... ");

  CAN.beginExtendedPacket(0xabcdef);
  CAN.write('w');
  CAN.write('o');
  CAN.write('r');
  CAN.write('l');
  CAN.write('d');
  CAN.endPacket();

  Serial.println("done");

  delay(1000);
}