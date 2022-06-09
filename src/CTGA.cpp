#include "CTGA.hpp"

std::shared_ptr<CAbstractFormat> CTGA::clone() const {
    return std::make_shared<CTGA>(*this);
}

void CTGA::loading() {

    std::ifstream is{ filePath, std::ios::in | std::ios::binary };

    if ( !is.good() ) {
        throw cantOpen();
    }

    loadHeader( is );

    if ( header.blockLength != 0 || header.colorMapType != 0 ) throw badHeader();
    if ( header.depth != 24 && header.depth != 32 ) throw bitsPerPixel();
    if ( header.imageType & COMPRESS_BIT ) throw compressed();
    height = header.height;
    width = header.width;

    getInfo();

    if ( header.depth == 24 ) {
        for ( auto i = 0; i < header.height; i++ ) {
            std::vector<unsigned char> tmp;
            for ( auto j = 0; j < header.width; j++ ) {
                RGB c {};
                is.read(reinterpret_cast<char *>(&c), sizeof(RGB));
                if ( ! is.good() ) throw notEnoughData();
                auto gray = grayscale(c);
                tmp.push_back(gray);
            }
            pixels.push_back(tmp);
        }
    }
    else if ( header.depth == 32 ) {
        for ( auto i = 0; i < header.height; i++ ) {
            std::vector<unsigned char> tmp;
            for ( auto j = 0; j < header.width; j++ ) {
                int a;
                RGB c {};
                is.read(reinterpret_cast<char *>(&a), sizeof(int));
                if ( ! is.good() ) throw notEnoughData();
                is.read(reinterpret_cast<char *>(&c), sizeof(RGB));
                if ( ! is.good() ) throw notEnoughData();
                auto gray = grayscale(c);
                tmp.push_back(gray);
            }
            pixels.push_back(tmp);
        }
    }
}

void CTGA::getInfo() {
    printBanner();
    std::cout << "File name      - " << fileName << std::endl;
    std::cout << "Height         - " << height << std::endl;
    std::cout << "Width          - " << width << std::endl;
    std::cout << "Depth          - " << int(header.depth) << std::endl;
}

void CTGA::loadHeader( std::ifstream& is ) {
    is.read( reinterpret_cast<char *>(&header), sizeof(header) );
    if ( !is.good() ) throw badHeader();
}
