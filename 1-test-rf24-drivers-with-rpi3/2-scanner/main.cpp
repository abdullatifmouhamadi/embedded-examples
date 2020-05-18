/*
 * Author: ABDULLATIF Mouhamadi <bourou01dev@gmail.com>
 *
 * License: MIT
 *
 * Plages de fréquences du scanner ISM (2400 MHz à 2527 MHz)
 */

// 
#include <iostream>
#include <RF24/RF24.h>
 
using namespace std;

#define PIN_CE 17
#define PIN_CSN 0
#define NUM_CHANNELS 126
 
uint8_t values[NUM_CHANNELS];
const int num_reps = 100;
 
int main() {

  RF24 radio(PIN_CE, PIN_CSN);
  radio.begin();
  radio.setAutoAck(false); // interdiction d'envoi automatique de paquets d'accusé de réception pour tous les tuyaux
 
  radio.startListening(); // entrée mode récepteur
  radio.stopListening();
 
  radio.printDetails(); // sortie de configuration
 
  // Sortie d'en-tête supérieure
  for (int i = 0; i < NUM_CHANNELS; ++i) {
    cout << hex << (i >> 4);
  }

  cout << endl;

  // Sortie d'en-tête inférieure
  for (int i = 0; i < NUM_CHANNELS; ++i) {
    cout << hex << (i & 0xf);
  }

  cout << endl;
 
  while (true) {

    memset(values, 0, sizeof(values)); // toutes les valeurs de canal sont réinitialisées
 
    // Balayer tous les canaux num_reps
    for (int k = 0; k < num_reps; ++k) {
      for (int i = 0; i < NUM_CHANNELS; ++i) {

        radio.setChannel(i);
 
        radio.startListening();
        delayMicroseconds(130); // parce que le temps de commutation entre les voies du module est de 130 μs
        radio.stopListening();
 
        // Vérification de la présence de la fréquence porteuse sur le canal sélectionné (fréquence)
        if (radio.testCarrier()) { 
          ++values[i];
        }
      }
    }
  
    // Impression de la mesure de canal en un chiffre hexadécimal
    for (int i = 0; i < NUM_CHANNELS; ++i) {
      cout << hex << min(0xf, (values[i] & 0xf));
    }
    cout << endl;
  }
  return 0;
}

