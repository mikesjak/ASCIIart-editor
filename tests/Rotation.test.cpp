#include "../src/CBMP.hpp"
#include "../src/CRotate.hpp"
#include <cassert>

class test_CRotate : public CRotate {
public:
    void rotateR( std::shared_ptr<CAbstractFormat>& file ) {
        CRotate::rotateRight(file);
    }
    void rotateL( std::shared_ptr<CAbstractFormat>& file ) {
        CRotate::rotateLeft(file);
    }
    void rotateV( std::shared_ptr<CAbstractFormat>& file ) {
        CRotate::flipVertically(file);
    }
    void rotateH( std::shared_ptr<CAbstractFormat>& file ) {
        CRotate::flipHorizontally(file);
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

    // left->right
    test_CRotate rotate;
    rotate.rotateR(fp);
    rotate.rotateL(fp);
    assert( comparePixels( file, file2 ) );

    // 2x horizontally
    rotate.rotateH(fp);
    rotate.rotateH(fp);
    assert( comparePixels( file, file2 ) );

    // 2x vertically
    rotate.rotateV(fp);
    rotate.rotateV(fp);
    assert( comparePixels( file, file2 ) );

    // 4x right
    rotate.rotateR(fp);
    rotate.rotateR(fp);
    rotate.rotateR(fp);
    rotate.rotateR(fp);
    assert( comparePixels( file, file2 ) );

    return 0;
}