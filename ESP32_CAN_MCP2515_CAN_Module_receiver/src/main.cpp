/*Based on https://how2electronics.com/esp32-can-bus-communication-with-mcp2515-module/
It worked with this topology:

ESP32 (Transmitter) - Module MCP2515 <== CAN BUS ==> Module MCP2515 - ESP32 (Receiver)

Wiring:
Module MCP2515 - ESP32
VCC - Vin (+5V)
GND - GND
CS - GPIO5
SO - GPIO19
SI - GPIO23
SCK - GPIO18

Testado ok, transmitiu e recebeu na outra ponta
Sender:
st:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0030,len:1184
load:0x40078000,len:13232
load:0x40080400,len:3028
entry 0x400805e4
CAN Sender MCP2515 + ESP32
CAN Message sent: ACK received
CAN Message sent: ACK received
CAN Message sent: ACK received



Receiver:
rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0030,len:1184
load:0x40078000,len:13232
load:0x40080400,len:3028
entry 0x400805e4
CAN Receiver MCP2515 + ESP32
CAN Data received: 1041011081081119997110ACK sent
CAN Data received: 1041011081081119997110ACK sent
CAN Data received: 1041011081081119997110ACK sent
CAN Data received: 1041011081081119997110ACK sent
*/

#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>
 
struct can_frame canMsg;
struct MCP2515 mcp2515(5); // CS pin is GPIO 5
 
#define CAN_ACK_ID 0x037  // CAN ID for acknowledgment
 
void setup()
{
  Serial.begin(115200);
  Serial.println("CAN Receiver MCP2515 + ESP32");
  SPI.begin();
 
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}
 
 
void loop()
{
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK)
  {
    if (canMsg.can_id == 0x036)  // Check if the message is from the sender
    {
      Serial.print("CAN Data received: ");
      Serial.print(canMsg.data[0]);
      Serial.print(canMsg.data[1]);
      Serial.print(canMsg.data[2]);
      Serial.print(canMsg.data[3]);
      Serial.print(canMsg.data[4]);
      Serial.print(canMsg.data[5]);
      Serial.print(canMsg.data[6]);
      Serial.print(canMsg.data[7]);
 
      // Send acknowledgment
      canMsg.can_id  = CAN_ACK_ID;  // Use ACK ID
      canMsg.can_dlc = 0;           // No data needed for ACK
      mcp2515.sendMessage(&canMsg);
      Serial.println("ACK sent");
    }
  }
}