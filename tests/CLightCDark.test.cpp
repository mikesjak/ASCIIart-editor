#include "../src/CBMP.hpp"
#include "../src/CLight.hpp"
#include "../src/CDark.hpp"
#include <cassert>

class test_CLight : public CLight {
public:
    std::map<int, char> ascii = { {0, '$'}, {1, '@'}, {2, '#'}, {3, '%'}, {4, '0'}, {5, 'a'}, {6, ':'}, {7, '*'}, {8, '-'}, {9, '`'}, {10, '.'}, {11, ' '} };

    void lighten( std::shared_ptr<CAbstractFormat>& file ) {
        int choice = 1;
        CLight::adjustLight(file, ascii, choice);
    }
};

class test_CDark : public CDark {
public:
    std::map<int, char> ascii = { {0, '$'}, {1, '@'}, {2, '#'}, {3, '%'}, {4, '0'}, {5, 'a'}, {6, ':'}, {7, '*'}, {8, '-'}, {9, '`'}, {10, '.'}, {11, ' '} };

    void darken( std::shared_ptr<CAbstractFormat>& file ) {
        int choice = 1;
        CDark::adjustLight(file, ascii, choice);
    }
};

bool comparePixels ( CBMP& file1, CBMP& file2 ) {
    unsigned int j, i = 0;
    for (auto &row: file1.pixels) {
        j = 0;
        for (auto &c: row) {
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

    test_CLight l;
    test_CDark d;

    l.lighten(fp);
    d.darken(fp);
    assert(comparePixels(file, file2));

    for ( int i = 0; i < 4; i++ )
        l.lighten(fp);

    for ( int i = 0; i < 4; i++ )
        d.darken(fp);

    assert(comparePixels(file, file2));
}