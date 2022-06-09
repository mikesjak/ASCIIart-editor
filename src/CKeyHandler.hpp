#pragma once

#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>

/**
 * Class representing video player
 * Inspired by: https://itecnote.com/tecnote/r-c-non-blocking-keyboard-input/
 */
class CKeyHandler {
    public:
        /**
         * Function to detect key press
         * @return value > 0 if its not pressed
         * @return 0 when pressed
         */
        static int kbhit();

        /**
         * Function to get information which key was pressed
         * @return value of pressed key
         */
        static int getch();
};

