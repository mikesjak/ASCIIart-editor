#pragma once

#include "CAbstractFormat.hpp"

/**
 * Class representing BMP file
 * @inherit CAbstractFormat
 */
class CBMP : public CAbstractFormat {
    public:
        /**
        * Creates a new object to be pushed into storage
        * @return unique_ptr of *this
        */
        std::shared_ptr<CAbstractFormat> clone() const override;

        /**
         * Loads whole BMP file including headers
         * @throw badStart when pixel map doesn't start in lower left corner
         */
        void loading() override;

        /**
        * Loads all headers
        * @param is if stream from loaded file
        */
        void loadHeader(  std::ifstream& is  ) override;
    private:
        /**
         * Bitmap file header structure
         */
        struct FileHeader {
            char name[2];
            unsigned int size;
            unsigned int garbage;
            unsigned int offset;
        };

        /**
         * DIB header structure
         */
        struct DIBHeader {
            unsigned int header_size;
            unsigned int width;
            int height;
            uint16_t color_planes;
            uint16_t bits_per_pixel;
            unsigned int compression;
            unsigned int image_size;
        };

        /**
         * Stores file headers
         */
        FileHeader file_header;

        /**
         * Stores DIB headers
         */
        DIBHeader dibheader;

        /**
         * Prints all loaded information about specific file
         */
        void getInfo() override;
};

//=====================================================================================================================

/**
 * exception thrown when no files loaded yet
 */
class badStart : public std::exception {
    public:
        const  char *  what() const noexcept;
};

