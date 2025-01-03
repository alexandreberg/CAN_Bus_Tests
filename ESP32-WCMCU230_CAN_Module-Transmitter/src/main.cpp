#include <Arduino.h>

/* Transmitter (Sender)
Tested ok with ESP32 dev kit 1 and CAN module MCU230.
Wiring:
CAN transceiver	ESP32
3V3	3V3
GND	GND
CTX	GPIO_5
CRX	GPIO_4

Source: https://github.com/sandeepmistry/arduino-CAN

// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

Serial Log in the receiver side:
(The receiver tested was an Arduino UNO with MCP2515 CAN module)

```
CAN Receiver Callback

Received packet with id 0x12 and length 5

hello



Received extended packet with id 0xABCDEF and length 6

world



Received packet with id 0x12 and length 5

ESP32
```
*/

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
  Serial.print("Sending CAN packet at 500kbps from ESP32 esp32doit-devkit-v1 board ... ");

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
  CAN.write(' ');  
  CAN.endPacket();

  CAN.beginPacket(0x12);
  CAN.write('E');
  CAN.write('S');
  CAN.write('P');
  CAN.write('3');
  CAN.write('2');
  CAN.endPacket();


  Serial.println("done");

  delay(1000);
}

