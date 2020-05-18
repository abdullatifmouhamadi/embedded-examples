/*
 * Author: ABDULLATIF Mouhamadi <bourou01dev@gmail.com>
 *
 * License: MIT
 *
 * 
 */

//
#include <iostream>
//#include <RF24/nRF24L01.h>
#include <RF24/RF24.h> // SPI and work with GPIO (BCM numbering) is already implemented in the library

using namespace std;

#define PIN_CE 17 // (chip enable)
#define PIN_CSN 0 // (chip select not)

uint8_t pipeNumber;
uint8_t payloadSize;

int main() {

  RF24 radio(PIN_CE, PIN_CSN); // create a radio object
  radio.begin();
  // data transmission channel (from 0 to 125), 5 - at a frequency of 2.405 GHz
  radio.setChannel(5);
  // signal gain level (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
  radio.setPALevel(RF24_PA_HIGH);
  // data rate (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1 Mbps
  radio.setDataRate(RF24_1MBPS);
  // open the pipe with the address 0x7878787878LL to receive data (in total there can be pipes 0 - 5)
  radio.openReadingPipe(0, 0x7878787878LL);

  // We allow you to place user data in an acknowledgment packet
  radio.enableAckPayload();

  // allow sending a confirmation packet for receiving data on all pipes to the transmitter (default is true)
  radio.setAutoAck(true);

  // allow dynamically changing block size of useful data on all pipes (max 32 bytes)
  radio.enableDynamicPayloads();

  // module configuration output
  radio.printDetails();
  // turn on the receiver, start listening to open pipes
  radio.startListening(); 

  cout << "Start listening..." << endl;

  while (true) {

    // If the buffer contains received data, then we pass the address of the variable (must be of type uint8_t)
    // in which you want to put the number of the pipe on which the data was received
    if (radio.available(&pipeNumber)) {

      payloadSize = radio.getDynamicPayloadSize(); // get the size of the received useful data
      char payload[payloadSize];
      string receivedData;

      // We read the received data into the payload array indicating the size of this array in bytes
      radio.read(&payload, payloadSize);

      for (uint8_t i = 0; i < payloadSize; i++) {
        receivedData += payload[i];
      }

      cout << "Pipe number : " << (int) pipeNumber << " ";
      cout << "Payload size : " << (int) payloadSize << " ";    
      cout << "Data: " << receivedData << endl;

      char ackData[] = "Data from buffer";

      // We put the data in the FIFO buffer. As soon as the packet is received, the data from the buffer
      // will be sent to this transmitter along with a confirmation packet for receiving its data
      radio.writeAckPayload(0, &ackData, sizeof(ackData));
    }
  }
  return 0;
}