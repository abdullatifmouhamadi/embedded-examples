/*
 * Author: ABDULLATIF Mouhamadi <bourou01dev@gmail.com>
 *
 * License: MIT
 *
 * 
 */

#include <iostream>
//#include <RF24/nRF24L01.h>
#include <RF24/RF24.h> // SPI and work with GPIO (BCM numbering) is already implemented in the library

using namespace std;

#define PIN_CE 17 // (chip enable)
#define PIN_CSN 0 // (chip select not)

int main() {
  
  RF24 radio(PIN_CE, PIN_CSN); // create a radio object
  radio.begin();
  // data transmission channel (from 0 to 125), 5 - at a frequency of 2.405 GHz
  radio.setChannel(5);
  // transmitter gain level  (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
  radio.setPALevel(RF24_PA_HIGH);
  // data rate (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1 Mbps
  radio.setDataRate(RF24_1MBPS);
  // allow receiving a packet of confirmation of data reception (default is true)
  radio.setAutoAck(true);
  // allow dynamically changing block size of useful data
  radio.enableDynamicPayloads();
  
  // If the transmitter does not receive a response from the receiver, then it will repeat the sending of data.
  // The wait between each retry, in multiples of 250,
  // the maximum is 15. 0 means 250 μs, (15 * 250) +250 = 4000 μs,
  // and the number of attempts before delivery, maximum 15
  radio.setRetries(15, 15); // the method is available only to the transmitter

  // open a pipe with a unique ID (at the same time only one pipe can be opened for data transfer)
  radio.openWritingPipe(0x7878787878LL);

  // payload block can be up to 32 bytes
  char text[] = "Hello world!";
  char ackData[24];

  while (true) {

    // By default, the transmitter asks the receiver to confirm receipt of data,
    // and the receiver, having received the data and checking the CRC, returns a data acknowledgment packet to the transmitter.
    
    // We pass the address of the variable and its size in bytes, the value of which will be as useful data
    // And we check the availability of the returned data acknowledgment packet
    if (radio.write(&text, sizeof(text))) {
      cout << "Delivered " << (int) sizeof(text) << " byte" << endl;
    }
    else {
      cout << "Data not delivered" << endl; // transmitter data not received or received with CRC error
    }

    // If the buffer contains received data from the acknowledgment packet
    if (radio.isAckPayloadAvailable()) {
      // we read data from the buffer into the ackData array indicating how many total bytes can fit in the array
      radio.read(&ackData, sizeof(ackData));
      string FIFO;
      for (uint8_t i = 0; i < sizeof(ackData); i++) {
        FIFO += ackData[i];
      }
      //Serial.println(FIFO);
      cout << "FIFO : "<< FIFO << endl;

      // If all three FIFO buffers are full, then clear
      if (radio.rxFifoFull()) {
        cout << "Buffer full" << endl;
        radio.flush_rx(); // buffer clearing
      }
    }  

    delay(1000);
  }

}
