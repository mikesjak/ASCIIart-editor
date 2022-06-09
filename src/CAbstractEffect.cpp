#include "CAbstractEffect.hpp"

void CAbstractEffect::dotsAnimation() {
    std::cout << "." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500) );
    std::cout << ".." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500) );
    std::cout << "..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500) );
}

void CAbstractEffect::createOldVersion(std::vector< std::shared_ptr<CAbstractFormat> > &files) {
    old_pixels.clear();
    old_pixels.reserve(files.size());
    for ( auto&file : files ) {
        std::vector < std::vector< unsigned char > > curr;
        for (auto &row: file->pixels) {
            curr.push_back(row);
        }
        old_pixels.push_back(curr);
    }
}

void CAbstractEffect::reversing(std::vector< std::shared_ptr<CAbstractFormat> > &files) {
    int choice;
    std::cout << "Do you want to reverse changes?" << std::endl;
    std::cout << "  1. Yes" << std::endl;
    std::cout << "  2. No" << std::endl;
    std::cin >> choice;
    if ( std::cin.eof() ) throw unexpectedEndOfInput();
    if ( choice == 1 ) reverseChanges(files);
    else if ( choice != 2 ) throw badChoice();
}

void CAbstractEffect::reverseChanges( std::vector< std::shared_ptr<CAbstractFormat> > &files ){
    int index = 0;
    for ( auto& file : files ) {
        swap( file->pixels, old_pixels[index] );
        index++;
    }
    old_pixels.clear();
}
