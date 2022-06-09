#include "CAbstractFormat.hpp"

void CAbstractFormat::print(std::map<int, char> & ascii_signs) {
    showImage(ascii_signs);
    std::cout << "\nPress Enter to exit review." << std::endl;
    while ( !CKeyHandler::kbhit() ) {}
    CKeyHandler::getch();
}

unsigned char CAbstractFormat::grayscale(RGB rgb) {
    return int(float(0.3 * rgb.red) + float(0.6 * rgb.green) + float(0.1 * rgb.blue));
}

void CAbstractFormat::columnAveraging () {

    std::vector< std::vector<unsigned char> > avgPixels;

    unsigned int row;
    for ( row = 0; row < height && (row+COLUMN <= height); row += COLUMN ) {
        std::vector< unsigned char > avgRow;
        for ( unsigned int i = 0; i < width; i++ ) {
            int sum = 0;
            for ( unsigned int j = row; j < row+COLUMN; j++ ) {
                sum += pixels[j][i];
            }
            int avg = sum/COLUMN;
            avgRow.push_back(avg);
        }
        avgPixels.push_back(avgRow);
    }
    if ( row < height ) {
        std::vector< unsigned char > avgRow;
        for ( unsigned int i = 0; i < width ; i++) {
            int sum = 0;
            for ( unsigned int j = row; j < height; j++ ) {
                sum += pixels[j][i];
            }
            unsigned int avg = sum/(height - row);
            avgRow.push_back(avg);
        }
        avgPixels.push_back(avgRow);
    }
    pixels=avgPixels;
}

std::vector<unsigned char> CAbstractFormat::averageRow( const std::vector<unsigned char>& row ) {
    int sum = 0,
        count = 0;
    std::vector< unsigned char > avgVec;
    for ( auto it = row.begin(); it != row.end(); it++ ) {
        sum += (*it);
        count ++;
        if ( count == ROW ) {
            int avg = int(sum/ROW);
            count = sum = 0;
            avgVec.push_back(avg);
        }
    }
    if ( count != 0 ) {
        int avg = sum/count;
        avgVec.push_back(avg);
    }
    return avgVec;
}

void CAbstractFormat::rowAveraging() {
    std::vector< unsigned char > tmp;
    for ( std::vector< unsigned char >& vec : pixels ) {
        tmp = averageRow(vec);
        vec = tmp;
    }
}

void CAbstractFormat::average() {
    for ( auto i = 0; ( width > MAXperRow/2 && height > MAXperColumn/2 ) ; i++ ){
        rowAveraging();
        width = pixels[0].size();
        columnAveraging();
        height = pixels.size();
    }
    while ( width > MAXperRow ) {
        rowAveraging();
        width = pixels[0].size();
    }
    while ( height > MAXperColumn ) {
        columnAveraging();
        height = pixels.size();
    }
}

void CAbstractFormat::getFilename( std::string& path ) {
    std::string file_name = path;
    file_name.erase(file_name.end()-4, file_name.end());
    unsigned int i;
    for ( i = file_name.size() - 1; i >= 0; i-- ) {
        if ( file_name[i] == '/' ) break;
    }
    file_name.erase(file_name.begin(), file_name.begin()+i+1);
    fileName = file_name;
}

void CAbstractFormat::showImage(std::map<int, char> & ascii_signs) {
    system("clear");
    int ascii_values = int((256/ascii_signs.size())+1);
    for ( auto i = pixels.size() - 1; i > 0; i-- ) {
        std::vector<unsigned char>& row = pixels[i];
        for ( auto j = row.size()-1; j > 0; j-- ){
            int count = (((255-(row[j]))/ascii_values));
            auto rgb = ascii_signs.find(count);
            if ( rgb->first > int(ascii_signs.size()-1) || rgb->first < 0 ){
                std::cout << int(row[j]) << " " << count << std::endl;
            }
            std::cout << rgb->second;
        }
        auto rgb = ascii_signs.find((255-(row[0]))/ascii_values);
        std::cout << rgb->second << std::endl;
    }
}

void CAbstractFormat::printBanner() {
    std::cout << "+-----------------------------+" << std::endl;
    std::cout << "|          File info          |" << std::endl;
    std::cout << "+-----------------------------+" << std::endl;
}

//=====================================================================================================================

const char * badFormat::what( void ) const noexcept {
    return "Bad format!";
}

const char * unexpectedEndOfInput::what( void ) const noexcept {
    return "Unexpected end of input!";
}

const char * badChoice::what( void ) const noexcept {
    return "Wrong input!";
}

const char * badHeader::what( void ) const noexcept {
    return "Bad header!";
}

const char * cantOpen::what( void ) const noexcept {
    return "Can't open file!";
}

const char * compressed::what( void ) const noexcept {
    return "File was compressed";
}

const char * bitsPerPixel::what( void ) const noexcept {
    return "File is compressed!";
}

const char * notEnoughData::what( void ) const noexcept {
    return "Not enough data!";
}