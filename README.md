# CAN_Bus_Tests

Testing the communication of a MCP2515 + TJA1050  board with Arduino UNO.
Based on the [Site:](https://lastminuteengineers.com/mcp2515-can-module-arduino-tutorial/)

Connections:
```
Arduino UNO - MCP2515
+5V - Vcc
GND - GND
10 - CS
12 - SO
11 - SI
13 - SCK
2 - INT
```

## Project tree:
```
C:.
├───MCP2515_Arduino_UNO_simple_two_node_CAN_Network_Receiver_Node
│   ├───src
└───MCP2515_Arduino_UNO_simple_two_node_CAN_Network_Transmitter_Node
    ├───src
PS C:\Projetos_GitHub\CAN_Bus_Tests> 
```


## Serial Log:
The comunication worked.

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


