#pragma once

#include <filesystem>
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "CPlayer.hpp"
#include "CEditor.hpp"
#include "CLoader.hpp"

/**
 * Class to cooperate loading with moving forward to editing
 */
class CAplication {
    public:

        /**
        * Constructor and also a main function in this class
        * Takes care of the whole run
        */
        CAplication ();
    private:
        /**
        * Loads transition from a file transition.txt
         * @throw cannotOpenFile() when file cannot be read
        */
        void loadTransition ();

        /**
        * Main menu of the program
         * @throw unexpectedEnxOfInput when reads EOF
         * @throw badChoice when input is out of range
        */
        void menu ();

        /**
        * Shows ASCIIart
        */
        static void welcomeMessage() ;

        /**
        * TurningOff messages
        */
        static void turningOff() ;

        /**
         * Pushes loaded files to local storage
         * @param loadedFiles files loaded in CLoader
         */
        void addLoadedFiles( std::vector < std::shared_ptr<CAbstractFormat> >& loadedFiles );

        /**
         * ASCII transition
         */
        std::map< int, char > ascii_signs;

        /**
         * Storage of files
         */
        std::vector < std::shared_ptr<CAbstractFormat> > files;
};