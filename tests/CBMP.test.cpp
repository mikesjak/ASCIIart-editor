#include "../src/CBMP.hpp"
#include <cassert>

int main () {
    bool ext = false;
    CBMP file;

    // TGA file into BMP loader
    file.filePath="examples/TGA/vagner.tga";
    try {
        file.loading();
    }
    catch ( std::exception & ex ){
        ext = true;
    }
    assert(ext);

    // Wrong file header
    file.filePath="examples/BMP/corrupted.bmp";
    ext = false;
    try {
        file.loading();
    }
    catch ( std::exception & ex ){
        ext = true;
    }
    assert(ext);

    // Wrong DIB header
    file.filePath="examples/BMP/BS.bmp";
    ext = false;
    try {
        file.loading();
    }
    catch ( std::exception & ex ){
        ext = true;
    }
    assert(ext);

    // Not enough data
    file.filePath="examples/BMP/NH.bmp";
    ext = false;
    try {
        file.loading();
    }
    catch ( std::exception & ex ){
        ext = true;
    }
    assert(ext);

    // Right file
    file.filePath="examples/BMP/cat.bmp";
    ext = false;
    try {
        file.loading();
    }
    catch ( std::exception & ex ){
        ext = true;
        std::cout << ex.what() << std::endl;
    }
    assert(!ext);

    return 0;
}