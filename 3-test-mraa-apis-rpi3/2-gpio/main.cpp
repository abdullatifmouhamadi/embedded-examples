/*
 * Author: ABDULLATIF Mouhamadi <bourou01dev@gmail.com>
 *
 * License: MIT
 *
 * Example usage: Toggles GPIO's 23 and 24 recursively. Press Ctrl+C to exit
 *
 */

/* standard headers */
#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/* mraa headers */
#include "mraa/common.hpp"
#include "mraa/gpio.hpp"

/* gpio declaration */
#define GPIO_PIN_1 23
#define GPIO_PIN_2 24

volatile sig_atomic_t flag = 1;

void sig_handler(int signum) {
    if (signum == SIGINT) {
        std::cout << "Exiting..." << std::endl;
        flag = 0;
    }
}




int main(void) {
    mraa::Result status;

    /* install signal handler */
    signal(SIGINT, sig_handler);

    //! [Interesting]
    /* initialize GPIO pin */
    mraa::Gpio gpio_1(GPIO_PIN_1);

    /* initialize GPIO pin */
    mraa::Gpio gpio_2(GPIO_PIN_2);


}


