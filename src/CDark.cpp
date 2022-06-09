#include "CDark.hpp"


void CDark::adjustLight( std::shared_ptr<CAbstractFormat> & file, const std::map< int, char > & ascii_signs, int & choice) {
    int asciiValues = (256/ascii_signs.size());
    for ( auto &row : (file->pixels) ) {
        for ( auto &pixel : row ) {
            if (pixel != 255)
                pixel += (asciiValues*choice);
            if (pixel > (255-(asciiValues*choice))) pixel = 255;
        }
    }
}

void  CDark::manage( std::vector <std::shared_ptr<CAbstractFormat>>& files, const std::map< int, char > & ascii_signs ) {
    int choice;
    createOldVersion(files);
    std::system("clear");
    std::cout << "Select the intensity from 1-10!" << std::endl;
    std::cin >> choice;
    if ( std::cin.eof() ) throw unexpectedEndOfInput();

    std::cout << "Managing light" << std::endl;
    dotsAnimation();
    for ( auto&file : files )
        adjustLight( file, ascii_signs, choice );

    reversing(files);
}

void CDark::help() {
    std::system("clear");
    banner();
    std::cout << " INTENSITY" << std::endl;
    std::cout << "  - The multiple of changed amount\n" << std::endl;
    std::cout << "This effect will change each pixel changes to darker according to intensity" << std::endl;
    std::cout << "\nPress Enter to exit" << std::endl;
    while ( !CKeyHandler::kbhit() ) {}
    CKeyHandler::getch();
}

void CDark::banner() {
    std::cout << "+---------------------+" << std::endl;
    std::cout << "|     Make darker     |" << std::endl;
    std::cout << "+---------------------+" << std::endl;
}