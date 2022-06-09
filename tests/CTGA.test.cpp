#include "../src/CTGA.hpp"
#include <cassert>

int main () {

    bool ext = false;
    CTGA file;

    // TGA great file
    file.filePath="examples/TGA/pic.tga";
    try {
        file.loading();
    }
    catch ( std::exception & ex ){
        ext = true;
    }
    assert(!ext);

    // BMP to TGA loader
    file.filePath="examples/BMP/corrupted.bmp";
    ext = false;
    try {
        file.loading();
    }
    catch ( std::exception & ex ){
        ext = true;
    }
    assert(ext);

    // Wrong file header
    file.filePath="examples/TGA/corrupted.tga";
    ext = false;
    try {
        file.loading();
    }
    catch ( std::exception & ex ){
        ext = true;
    }
    assert(ext);

    // Not enough data
    file.filePath="examples/TGA/NH.tga";
    ext = false;
    try {
        file.loading();
    }
    catch ( std::exception & ex ){
        ext = true;
    }
    assert(ext);
}