/*
 * Author: ABDULLATIF Mouhamadi <bourou01dev@gmail.com>
 *
 * License: MIT
 *
 * Test de prise en charge du module par la bibliothèque RF24 (si connecté correctement)
 */
#include <iostream>
#include <RF24/RF24.h>

using namespace std;

#define PIN_CE 17
#define PIN_CSN 0

int main(void) {

	RF24 radio(PIN_CE, PIN_CSN);
	radio.begin();

	if (radio.isPVariant()) {
		cout << "The module is supported" << endl;
		radio.printDetails(); 
	}
	else {
		cout << "Unknown module" << endl;
	}
}