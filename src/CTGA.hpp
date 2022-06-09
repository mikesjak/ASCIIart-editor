#pragma once

#include "CAbstractFormat.hpp"

#define COMPRESS_BIT 8u

/**
 * Class representing TGA file
 */
class CTGA : public CAbstractFormat {
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
         * Loads all header
         * @param is if stream from loaded file
         */
        void loadHeader( std::ifstream& is ) override;
    private:
        /**
         * File header containing all file information
         */
        struct file_header {
            unsigned char blockLength;
            unsigned char colorMapType;
            unsigned char imageType;
            unsigned char CMSpecification[5];

            unsigned short int originX;
            unsigned short int originY;
            unsigned short int width;
            unsigned short int height;

            unsigned char depth;
            unsigned char descriptor;
        };

        /**
         * Prints all loaded information about specific file
         */
        void getInfo() override;

        /**
         * TGA file header
         */
        file_header header;
};
