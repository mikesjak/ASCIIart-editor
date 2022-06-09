#include "CBMP.hpp"

std::shared_ptr<CAbstractFormat> CBMP::clone() const {
    return std::make_shared<CBMP>(*this);
}

void CBMP::loading() {

    std::ifstream is{ filePath, std::ios::in | std::ios::binary };
    if ( !is ) throw cantOpen();


    loadHeader( is );

    height = dibheader.height;
    width  = dibheader.width;
    getInfo();

    // Header securing
    if ( file_header.name[0] != 'B' || file_header.name[1] != 'M' ) throw badFormat();
    if ( dibheader.height < 0 ) throw badStart();
    if ( dibheader.compression ) throw compressed();
    if ( dibheader.bits_per_pixel != 32 && dibheader.bits_per_pixel != 24 ) throw bitsPerPixel();

    is.seekg(file_header.offset, std::ifstream::beg);

    if ( dibheader.bits_per_pixel == 24 ) {
        unsigned int padding = 4 - (width*3) % 4;
        if (padding == 4) padding = 0;
        for ( int i = 0; i < dibheader.height; i++ ) {
            std::vector <unsigned char> tmpvec;
            for ( unsigned int j = 0; j < dibheader.width; j++) {
                RGB tmp24 { 0, 0, 0,};
                is.read( reinterpret_cast<char*> (&tmp24), sizeof(RGB) );
                if ( ! is.good() ) throw notEnoughData();
                auto tmp_val = grayscale(tmp24);
                auto it = tmpvec.begin();
                tmpvec.insert(it, tmp_val);
            }
            for ( unsigned int j = 0; j < padding; ++j ){
                unsigned char rest;
                is.read(reinterpret_cast<char *>(&rest), sizeof(rest));
            }
            pixels.push_back(tmpvec);
        }
    }
    else if ( dibheader.bits_per_pixel == 32 ) {
        for (int i = 0; i < dibheader.height; i++) {
            std::vector<unsigned char> tmpvec;
            for (unsigned int j = 0; j < dibheader.width; j++) {
                unsigned char alpha;
                RGB tmp32{0, 0, 0,};
                is.read(reinterpret_cast<char *> (&alpha), sizeof(alpha));
                is.read(reinterpret_cast<char *> (&tmp32), sizeof(RGB));
                if ( ! is.good() ) throw notEnoughData();
                auto tmp_val = grayscale(tmp32);
                auto it = tmpvec.begin();
                tmpvec.insert(it, tmp_val);
            }
            pixels.push_back(tmpvec);
        }
    }
}

void CBMP::getInfo() {
    printBanner();
    std::cout << "File name      - " << fileName << std::endl;
    std::cout << "Format         - " << file_header.name << std::endl;
    std::cout << "Size           - " << file_header.size << std::endl;
    std::cout << "Offset         - " << file_header.offset << std::endl;
    std::cout << "Header size    - " << dibheader.header_size << std::endl;
    std::cout << "Height, Width  - " << dibheader.height << " " << dibheader.width  << " " << std::endl;
    std::cout << "Color planes   - " << dibheader.bits_per_pixel << std::endl;
    std::cout << "Bits per pixel - " << dibheader.bits_per_pixel << std::endl;
    std::cout << "Compression    - " << dibheader.compression << std::endl;
    std::cout << "Image size     - " << dibheader.image_size << std::endl;
}

void CBMP::loadHeader( std::ifstream& is ) {
    is.read( reinterpret_cast<char*> (&file_header.name), 2*sizeof(char));
    if ( !is.good() ) throw badHeader();
    is.read( reinterpret_cast<char*> (&file_header.size), sizeof(int));
    if ( !is.good() ) throw badHeader();
    is.read( reinterpret_cast<char*> (&file_header.garbage), sizeof(int));
    if ( !is.good() ) throw badHeader();
    is.read( reinterpret_cast<char*> (&file_header.offset), sizeof(int));
    if ( !is.good() ) throw badHeader();

    is.read( reinterpret_cast<char*> (&dibheader), sizeof(DIBHeader));
    if ( !is.good() ) throw badHeader();

    unsigned int count = dibheader.header_size-24;
    int tmp;
    for ( auto i = count; i > 0; i -= sizeof(int) ) {
        is.read( reinterpret_cast<char*> (&tmp), sizeof(int));
        if ( !is.good() ) throw badHeader();
    }
}

// =========================================================================================================

const char * badStart::what() const noexcept {
    return "File doesn't begin in the lower left corner!";
}
