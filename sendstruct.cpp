/*  
 *  LoRa 868 / 915MHz SX1272 LoRa module
 *  
 *  Copyright (C) Libelium Comunicaciones Distribuidas S.L. 
 *  http://www.libelium.com 
 *  
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 3 of the License, or 
 *  (at your option) any later version. 
 *  
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see http://www.gnu.org/licenses/. 
 *  
 *  Version:           1.1
 *  Design:            David Gascón 
 *  Implementation:    Covadonga Albiñana & Victor Boria
 */
 
// Include the SX1272 and SPI library: 
#include "arduPiLoRa.h"
#include "Structy.cpp"
#include <string>
#include <iostream>
using namespace std;
int e;

char message1 [] = "Packet 1, wanting to see if received packet is the same as sent packet";
char message2 [] = "Packet 2, broadcast test";

void setup()
{
  // Print a start message
  printf("SX1272 module and Raspberry Pi: send packets with ACK and retries\n");
  
  // Power ON the module
  e = sx1272.ON();
  printf("Setting power ON: state %d\n", e);
  
  // Set transmission mode
  e = sx1272.setMode(4);
  printf("Setting Mode: state %d\n", e);
  
  // Set header
  e = sx1272.setHeaderON();
  printf("Setting Header ON: state %d\n", e);
  
  // Select frequency channel
  e = sx1272.setChannel(CH_10_868);
  printf("Setting Channel: state %d\n", e);
  
  // Set CRC
  e = sx1272.setCRC_ON();
  printf("Setting CRC ON: state %d\n", e);
  
  // Select output power (Max, High or Low)
  e = sx1272.setPower('H');
  printf("Setting Power: state %d\n", e);
  
  // Set the node address
  e = sx1272.setNodeAddress(3);
  printf("Setting Node address: state %d\n", e);
  
  // Print a success message
  printf("SX1272 successfully configured\n\n");
  delay(1000);
}

void loop(bool ty)
{   
    packet obj;
    string m;
    getline(cin, m);
    char *cstr = &m[0];
    obj.name=m;
    obj.type = ty;// Send message1 and print the result
    int l = sizeof(obj);
    uint8_t * data = reinterpret_cast<uint8_t*>(&obj);
    cout << l << "\n";
    cout << "Contents of obj\n";
    for (int i = 0; i<l; i++)
    { 
      printf("%02X%c",*(data+i),(i%16==15)?'\n':' ');
    } 
      cout <<'\n' << sizeof(*data)<< "data\n" << *data << '\n';
    e = sx1272.sendPacketTimeoutACKRetries(8, data, l, (uint16_t ) 1000 );
    printf("Packet sent, state %d\n",e);
    
}

int main (){
	setup();
        printf("Input message\n");
        bool ty = true;
	while(1){
		loop(ty);
		ty = !ty;
	}
	return (0);
}
