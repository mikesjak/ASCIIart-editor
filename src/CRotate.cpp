#include "CRotate.hpp"

void CRotate::banner() {
    std::cout << "+------------------+" << std::endl;
    std::cout << "|      Rotate      |" << std::endl;
    std::cout << "+------------------+" << std::endl;
}

void CRotate::help() {
    std::system("clear");
    std::cout << "RIGHT " << std::endl;
    std::cout << "  - Pick to rotate picture 90 degrees right " << std::endl;
    std::cout << "LEFT " << std::endl;
    std::cout << "  - Pick to rotate picture 90 degrees left " << std::endl;
    std::cout << "UPSIDE DOWN " << std::endl;
    std::cout << "  - Pick to rotate picture 180 degrees " << std::endl;
    std::cout << "\nPress Enter to exit" << std::endl;
    while ( !CKeyHandler::kbhit() ) {}
    CKeyHandler::getch();
}

void  CRotate::manage( std::vector <std::shared_ptr<CAbstractFormat>>& files, const std::map< int, char > & ascii_signs ) {
    menu( files );
}

void CRotate::menu( std::vector <std::shared_ptr<CAbstractFormat>>& files ) {
    int choice;
    createOldVersion(files);
    std::system("clear");
    banner();
    std::cout << "Select rotation type!" << std::endl;
    std::cout << "1. Right" << std::endl;
    std::cout << "2. Left" << std::endl;
    std::cout << "3. Flip horizontally" << std::endl;
    std::cout << "4. Flip vertically" << std::endl;
    std::cout << "5. Help" << std::endl;

    if ( std::cin.eof() ) throw unexpectedEndOfInput();
    std::cin >> choice;
    if ( choice != 1 && choice != 2 && choice != 3 && choice != 4 ) {
        throw badChoice();
    }
    if ( choice == 5 ) {
        help();
        menu(files);
        return;
    }
    for ( auto& file : files ) {
        switch (choice) {
            case 1:
                rotateRight(file);
                break;
            case 2:
                rotateLeft(file);
                break;
            case 3:
                flipHorizontally(file);
                break;
            case 4:
                flipVertically(file);
                break;
            default:
                std::cout << "Bad input!" << std::endl;
                return;
        }
    }
    reversing(files);
}

void CRotate::rotateRight( std::shared_ptr<CAbstractFormat>& file ) {
    auto vec = file->pixels;

    std::vector< std::vector< unsigned char > > rotated_vec;

    for ( long unsigned int i = 0; i < vec[0].size(); i++ ) {
        std::vector< unsigned char > tmp;
        tmp.resize(vec.size());
        rotated_vec.push_back(tmp);
    }
    unsigned int col = vec.size()-1;
    for ( auto&c : vec ) {
        int row = 0;
        for ( auto r : c ) {
            (rotated_vec[row])[col] = r;
            row++;
        }
        col--;
    }
    file->pixels = rotated_vec;
}

void CRotate::rotateLeft( std::shared_ptr<CAbstractFormat>& file ) {
    auto vec = file->pixels;

    std::vector< std::vector< unsigned char > > rotated_vec;

    for ( long unsigned int i = 0; i < vec[0].size(); i++ ) {
        std::vector< unsigned char > tmp;
        tmp.resize(vec.size());
        rotated_vec.push_back(tmp);
    }
    int col = 0;
    for ( auto&c : vec ) {
        unsigned int row = vec[0].size()-1;
        for ( auto r : c ) {
            (rotated_vec[row])[col] = r;
            row--;
        }
        col++;
    }
    file->pixels = rotated_vec;
}

void CRotate::flipHorizontally( std::shared_ptr<CAbstractFormat>& file ) {
    unsigned int size = ((file->pixels).size())-1;
    for ( unsigned int i = 0; i <= size/2; i++ ) {
        std::swap(file->pixels[i], file->pixels[size-i]);
    }
}

void CRotate::flipVertically( std::shared_ptr<CAbstractFormat> & file ) {
    for ( auto&row : file->pixels ) {
        unsigned int size = row.size()-1;
        for ( unsigned int i = 0; i <= size/2; i++)
            std::swap(row[i], row[size-i]);
    }
}
