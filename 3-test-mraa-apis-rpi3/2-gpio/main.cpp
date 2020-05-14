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
#define GPIO_PIN_1 22
#define GPIO_PIN_2 23
#define GPIO_PIN_3 12

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
    mraa::Gpio gpio_2(GPIO_PIN_2);
    mraa::Gpio gpio_3(GPIO_PIN_3);

    /* set GPIO to output */
    status = gpio_1.dir(mraa::DIR_OUT);
    if (status != mraa::SUCCESS) {
        printError(status);
        return EXIT_FAILURE;
    }

    /* set GPIO to output */
    status = gpio_2.dir(mraa::DIR_OUT);
    if (status != mraa::SUCCESS) {
        printError(status);
        return EXIT_FAILURE;
    }

    /* toggle both GPIO's */

    int counter = 0;
    while (flag) {
        counter++;

        status = gpio_1.write(1);
        if (status != mraa::SUCCESS) {
            printError(status);
            return EXIT_FAILURE;
        }
        status = gpio_2.write(0);
        if (status != mraa::SUCCESS) {
            printError(status);
            return EXIT_FAILURE;
        }

        usleep(25000);

        status = gpio_1.write(0);
        if (status != mraa::SUCCESS) {
            printError(status);
            return EXIT_FAILURE;
        }

        status = gpio_2.write(1);
        if (status != mraa::SUCCESS) {
            printError(status);
            return EXIT_FAILURE;
        }

        usleep(50000);

        std::cout << "salut " << counter << std::endl;
    }
    //! [Interesting]
    return EXIT_SUCCESS;
}


