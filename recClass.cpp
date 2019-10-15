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
#include "Classy.cpp"

int e;
char my_packet[100];

void setup()
{
  // Print a start message
  printf("SX1272 module and Raspberry Pi: receive packets with ACK and retries\n");
  
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
  e = sx1272.setNodeAddress(8);
  printf("Setting Node address: state %d\n", e);
  
  // Print a success message
  printf("SX1272 successfully configured\n\n");
  delay(1000);
}

void loop(Classy obj)
{
  // Receive message
  e = sx1272.receivePacketTimeoutACK(10000);
  if ( e == 0 )
  {
    printf("Receive packet with ACK and retries, state %d\n",e);
    obj.setName("default value");
    obj.setType(false);
    printf("%s\n",obj.getName());
    obj.getType();
    Classy * ptr = &obj;
    printf("Printing pointer %d \n",ptr);
    printf("%d, %d\n", sizeof(obj), sx1272.packet_received.length);
    for (unsigned int i = 0; i < sx1272.packet_received.length; i++)
    {
      printf("%d, %d, ",(i),*(ptr+i));
      my_packet[i] = (uint8_t)sx1272.packet_received.data[i];
      *ptr = (Classy) sx1272.packet_received.data;
      //if(i < sizeof(obj))
         //*(ptr+i) = sx1272.packet_received.data[i];
      printf("%d \n " , (uint8_t) my_packet[i]);
      if (i < 45){
        //*(ptr+i + 1) = my_packet[2*i];
      }
    }
    //obj = *(&my_packet+1);
    obj.getType();
    //printf("%s\n",obj.getName());
    printf("\nMessage: %s\n", my_packet);
  }
  else {
   // printf("Transmission Failed, state %d\n",e);
  }
}

int main (){
  setup();
  static Classy obj;
  while(1){
    printf("started loop \n");
    loop(obj);
  }
  return (0);
}
        
