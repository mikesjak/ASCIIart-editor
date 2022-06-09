#pragma once

#include <filesystem>
#include <algorithm>
#include <iostream>
#include <iostream>
#include <fstream>
#include <fstream>
#include <string>
#include <thread>
#include <memory>
#include <string>
#include <cstdio>
#include <vector>
#include <map>

#include "CAbstractFormat.hpp"
#include "CBMP.hpp"
#include "CTGA.hpp"

/**
 * Class managing loading files
 */
class CLoader {
    public:
        /**
         * Manages all loading in this program
         * @param files vector of currently loaded files
         * @param ascii
         * @return
         */
        std::vector<std::shared_ptr<CAbstractFormat> > loadFiles( std::map< int, char >& ascii );
private:
        /**
        * Function to coordinate everything about loading
        * @throw noPath when no path was given
        * @throw badFileFormat when the file is neither BMP or TGA
        */
        void loadImages ();

        /**
        * Finds all pictures in a directory
        * @param path Path to a directory
        * @throw unexpectedEndOfInput when read EOF
        * @throw badChoice when input is out of range
        */
        void findFiles ( const std::string & );

        /**
        * Takes care of file creating with the right suffix
        * @param file_name name of the file
        * @param suffix suffix of the file
        * @throw unexpectedEndOfInput when read EOF
        * @throw badChoice when input is out of range
        */
        void fileCreate( std::string &, std::string &);

        /**
        * @param path filesystem path
        * @return true if this is a path file
        */
        static bool isFile ( const std::string & );

        /**
        * Checks if a given file ends with right suffix
        * @param file_name Name of a file this is checking
        * @return suffix if the right suffix is found, else return "false"
        */
        static std::string findSuffix ( const std::string &);


        /**
         * Push a file pointer to storage
         * @param file to add to storage
         */
        void addFile( std::shared_ptr< CAbstractFormat >& file );

        /**
         * ASCII transition
         */
        std::map< int, char > ascii_signs;

        /**
         * Vector of currently loaded files
         */
        std::vector< std::shared_ptr<CAbstractFormat> > files;

        /**
        * Map to create files
        */
        static std::map < std::string, std::shared_ptr< CAbstractFormat > > formats;

        /**
        * Boolean of inputted path
        * @true when given path is directory
        * @false when given path is file
        */
        bool dir = false;
};

/**
 * Exception if no files were added
 */
class badFileFormat : public std::exception {
public:
    const char * what( ) const noexcept;
};

/**
 * Exception if the file cannot be opened
 */
class cannotOpenFile : public std::exception {
public:
    const char * what( ) const noexcept;
};

/**
 * Exception if given path is wrong
 */
class noPath : public std::exception {
public:
    const char * what( ) const noexcept;
};
