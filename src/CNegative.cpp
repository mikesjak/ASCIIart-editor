#include "CNegative.hpp"

void  CNegative::manage( std::vector <std::shared_ptr<CAbstractFormat>>& files, const std::map< int, char > & ascii_signs) {
    std::system("clear");
    createOldVersion(files);
    int choice = 0;
    std::cout << "Choose a number:" << std::endl;
    std::cout << "  1. Negation" << std::endl;
    std::cout << "  2. Help" << std::endl;

    std::cin >> choice;
    if ( std::cin.eof() ) throw unexpectedEndOfInput();
    switch (choice) {
        case 1:
            std::cout << "Negating" << std::endl;
            dotsAnimation();
            for ( auto& file : files)
                negate( file );
            reversing(files);
            break;
        case 2:
            help();
            manage( files, ascii_signs );
            return;
        default:
            throw badChoice();
    }
}

void CNegative::help() {
    std::system("clear");
    banner();
    std::cout << "This effect will negate whole picture!" << std::endl;
    std::cout << "\nPress Enter to exit" << std::endl;
    while ( !CKeyHandler::kbhit() ) {}
    CKeyHandler::getch();
}

void CNegative::banner() {
    std::cout << "+---------------------+" << std::endl;
    std::cout << "|       Negative      |" << std::endl;
    std::cout << "+---------------------+" << std::endl;
}

void CNegative::negate( std::shared_ptr<CAbstractFormat>& file ) {
    for ( auto& it : file->pixels ) {
        for ( auto& sign : it ) {
            sign = 255-sign;
        }
    }
}
