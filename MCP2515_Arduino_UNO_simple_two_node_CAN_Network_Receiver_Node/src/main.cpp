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
Serial Log:
```
CAN Receiver Callback

Received extended packet with id 0xABCDEF and length 5
world

Received packet with id 0x12 and length 5
hello

Received extended packet with id 0xABCDEF and length 5
world

Received packet with id 0x12 and length 5
hello
```
*/

#include <Arduino.h>

// Receiver
#include <CAN.h>

//Function Prototypes:
void onReceive(int packetSize);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("CAN Receiver Callback");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  // register the receive callback
  CAN.onReceive(onReceive);
}

void loop() {
  // do nothing
}

void onReceive(int packetSize) {
  // received a packet
  Serial.print("Received ");

  if (CAN.packetExtended()) {
    Serial.print("extended ");
  }

  if (CAN.packetRtr()) {
    // Remote transmission request, packet contains no data
    Serial.print("RTR ");
  }

  Serial.print("packet with id 0x");
  Serial.print(CAN.packetId(), HEX);

  if (CAN.packetRtr()) {
    Serial.print(" and requested length ");
    Serial.println(CAN.packetDlc());
  } else {
    Serial.print(" and length ");
    Serial.println(packetSize);

    // only print packet data for non-RTR packets
    while (CAN.available()) {
      Serial.print((char)CAN.read());
    }
    Serial.println();
  }

  Serial.println();
}