#include "CLight.hpp"

void CLight::adjustLight( std::shared_ptr<CAbstractFormat> & file, const std::map< int, char > & ascii_sign, int & choice) {
    int asciiValues = (256/ascii_sign.size());
    for ( auto &row : (file->pixels) ) {
        for ( auto &pixel : row ) {
            if (pixel != 0)
                pixel -= (asciiValues*choice);
            if (pixel < (asciiValues*choice)) pixel = 0;
        }
    }
}

void  CLight::manage( std::vector <std::shared_ptr<CAbstractFormat>>& files, const std::map< int, char > & ascii_sign ) {
    int choice;
    createOldVersion(files);
    std::system("clear");
    banner();
    std::cout << "Select the intensity from 1-10!" << std::endl;
    std::cout << "Enter 0 for help!" << std::endl;

    std::cin >> choice;
    if ( std::cin.eof() ) throw unexpectedEndOfInput();
    if ( choice == 0 ) {
        help();
        manage(files, ascii_sign);
        return;
    }
    else if ( choice < 0 || choice > 10 ) throw badChoice();

    std::cout << "Managing light" << std::endl;
    dotsAnimation();
    for ( auto& file : files )
        adjustLight( file, ascii_sign, choice );

    reversing(files);
}

void CLight::help() {
    std::system("clear");
    banner();
    std::cout << " INTENSITY" << std::endl;
    std::cout << "  - The multiple of changed amount\n" << std::endl;
    std::cout << "This effect will change each pixel changes to darker according to intensity" << std::endl;
    std::cout << "\nPress Enter to exit" << std::endl;
    while ( !CKeyHandler::kbhit() ) {}
    CKeyHandler::getch();
}

void CLight::banner() {
    std::cout << "+-----------------+" << std::endl;
    std::cout << "|   Make lighter  |" << std::endl;
    std::cout << "+-----------------+" << std::endl;
}