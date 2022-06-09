#include "../src/CBMP.hpp"
#include "../src/CNegative.hpp"
#include <cassert>

class test_CNegate : public CNegative {
public:
    void negate(std::shared_ptr<CAbstractFormat> file) {
        CNegative::negate(file);
    }
};

bool comparePixels ( CBMP& file1, CBMP& file2 ) {
    unsigned int j, i = 0;
    for ( auto& row : file1.pixels ) {
        j = 0;
        for ( auto&c : row ) {
            if (c != file2.pixels[i][j]) return false;
            j++;
        }
        i++;
    }
    return true;
}

int main () {

    CBMP file;
    file.filePath="examples/BMP/cat.bmp";
    file.loading();
    std::shared_ptr<CAbstractFormat> fp = std::make_shared<CBMP>(file);

    CBMP file2;
    file2.filePath="examples/BMP/cat.bmp";
    file2.loading();

    test_CNegate neg;
    neg.negate(fp);
    neg.negate(fp);
    assert(comparePixels( file, file2 ));

    return 0;
}