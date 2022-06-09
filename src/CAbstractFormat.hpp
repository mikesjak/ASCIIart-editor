#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <memory>
#include <string>
#include <cstdio>
#include <map>
#include "CKeyHandler.hpp"

// CONSTANTS for averaging
#define ROW 2
#define COLUMN 3
#define MAXperRow 200
#define MAXperColumn 150

/**
 * Abstract file format class
 */
class CAbstractFormat {
    public:
        virtual ~CAbstractFormat() = default;

        /**
        * Creates a new object to be pushed into storage
        * @return unique_ptr of *this
        */
        virtual std::shared_ptr<CAbstractFormat> clone() const = 0;

        /**
        * Load the given picture
        */
        virtual void loading() = 0;

        /**
        * Manages picture printing
        * Waits for user to press Enter
        */
        void print(std::map<int, char> & );

        /**
        * Creates average values of chunks ROW*COLUMN
        */
        void average();

        /**
         * Separates filename from file path
         * @param path given file path
         */
        void getFilename( std::string& path );

        /**
         * Prints the image to the terminal
         * @param ascii_signs
         */
        void showImage(std::map<int, char> & ascii_signs);

        /**
         * Filename
         */
        std::string fileName;

        /**
         * Path to the file
         */
        std::string filePath;

        /**
         * Matrix of pixels
         */
        std::vector < std::vector< unsigned char > > pixels;

        /**
         * Height of the file
         */
        unsigned int height = 0;

        /**
         * Width of the file
         */
        unsigned int width = 0;

protected:
        /**
         * Colors from one pixel
         */
        struct RGB {
            unsigned char blue;
            unsigned char red;
            unsigned char green;
        };


        /**
         * Loads all headers
         * @param is if stream from loaded file
         */
        virtual void loadHeader( std::ifstream& is ) = 0;

        /**
         * Prints out all information about file
         */
        virtual void getInfo() = 0;

        /**
        * Counts how grey each pixel is
        * @param rgb Color bits of each pixel
        * @return grey value of the pixel
        */
        static unsigned char grayscale( RGB );

        /**
        * Prints whole picture of ASCII art
        * @param ascii_signs map of ascii transition
        */
        void columnAveraging ();

        /**
        * Counts average value of ROW pixels next to each other in a single row
        * @param row to modify
        * @return modified row with average values
        */
        static std::vector<unsigned char> averageRow( const std::vector<unsigned char>& );

        /**
        * Manages row averaging values in rows
        */
        void rowAveraging();

        /**
         * Banner to show while showing information about currently loaded file
         */
        static void printBanner();

};

//=====================================================================================================================

/**
 * Thrown if bad format is given
 */
class badFormat : public std::exception {
public:
    const char * what( ) const noexcept;
};

/**
 * Thrown if user unexpectedly ended input
 */
class unexpectedEndOfInput : public std::exception {
    public:
        const char * what() const noexcept;
};

/**
 * Thrown if user entered wrong number
 */
class badChoice : public std::exception {
    public:
        const char * what( ) const noexcept;
};

/**
 * Thrown if user entered wrong number
 */
class badHeader : public std::exception {
public:
    const char * what( ) const noexcept;
};

/**
 * Thrown if file cannot be openned
 */
class cantOpen : public std::exception {
public:
    const char * what( ) const noexcept;
};

/**
 * Thrown if file is compressed
 */
class compressed : public std::exception {
public:
    const char * what( ) const noexcept;
};

/**
 * Thrown if file has wrong BPP
 */
class bitsPerPixel : public std::exception {
public:
    const char * what( ) const noexcept;
};

/**
 * Thrown if file doesn't contain necessary data
 */
class notEnoughData : public std::exception {
public:
    const char * what( ) const noexcept;
};