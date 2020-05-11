/*
 * Author: ABDULLATIF Mouhamadi <bourou01dev@gmail.com>
 *
 * License: MIT
 *
 */
#include <iostream>
//! [Interesting]
#include "mraa.h"

int main(void) {
    const char* board_name = mraa_get_platform_name();
    std::cout << "hello mraa" << std::endl \
              << "Version: " << mraa_get_version() << std::endl \
              << "Running on " << board_name << std::endl;
    mraa_deinit();
    return MRAA_SUCCESS;
}


