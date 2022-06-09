#include "CLoader.hpp"

std::map < std::string, std::shared_ptr< CAbstractFormat > > CLoader::formats = {{"bmp", std::make_shared<CBMP>(CBMP()) },
                                                                                 {"tga", std::make_shared<CTGA>(CTGA()) } };


std::vector<std::shared_ptr<CAbstractFormat> > CLoader::loadFiles( std::map<int, char> &ascii) {
    ascii_signs = ascii;
    files.clear();
    loadImages();
    return files;
}


void CLoader::loadImages() {
    std::system("clear");
    std::string path;
    std::cout << "Enter file or directory to import: ";
    std::cin >> path;
    if ( path.empty() ) {
        throw noPath();
    }
    if ( ! isFile( path ) ) {
        findFiles( path );
    }
    else {
        dir = false;
        if ( !std::filesystem::is_regular_file( path ) ) throw badFileFormat();
        std::string suffix = findSuffix( path );
        fileCreate(path, suffix);
    }
}

void CLoader::findFiles(const std::string & path ) {
    std::string file_name;
    std::string suffix;
    int choice;

    std::cout << "Do you want to load all compatible files without seeing ASCIIart?" << std::endl;
    std::cout << "  1. Yes" << std::endl;
    std::cout << "  2. No" << std::endl;
    std::cin >> choice;
    if ( std::cin.eof() ) throw unexpectedEndOfInput();
    if ( choice != 1 && choice != 2 ) throw badChoice();
    choice = choice % 2;
    dir = choice;

    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        file_name = entry.path();
        suffix = findSuffix(file_name);
        fileCreate(file_name, suffix);
    }
    if ( files.empty() ) {
        std::system("clear");
        std::cout << "There were no compatible files, please import different one." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(3000) );
        loadImages();
    }
}

void CLoader::fileCreate(std::string & file_name, std::string & suffix ) {

    std::system("clear");
    auto it = formats.find(suffix);
    if ( it == formats.end() ) {
        std::cout << "Didn't find right file format!" << std::endl;
        return;
    }
    auto file = it->second->clone();
    file->filePath = file_name;
    file->getFilename( file_name );
    try {
        file->loading();
    }
    catch ( std::exception & ex ) {
        if (!dir){
            std::cout << ex.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000) );
        }
        return;
    }
    file->average();

    if ( dir ) {
        addFile(file);
        return;
    }
    std::cout << "Do you want to show ASCIIart?" << std::endl;
    std::cout << "   1 -> YES" << std::endl;
    std::cout << "   2 -> NO" << std::endl;

    int choice;
    std::cin >> choice;
    if ( std::cin.eof() ) throw unexpectedEndOfInput();
    if ( choice == 1 ) {
        file->print(ascii_signs);
        addFile(file);
    }
    else if ( choice == 2 )
        addFile(file);
    else {
        throw badChoice();
    }
}

void CLoader::addFile(std::shared_ptr<CAbstractFormat>& file ) {
    files.emplace_back(file);
}

std::string CLoader::findSuffix(const std::string& file_name){
    std::string suffix;
    std::string file_suffix = file_name;
    file_suffix.erase( file_suffix.begin(), file_suffix.end() - 3 );
    for (auto & map_it: formats) {
        suffix = map_it.first;
        if ( file_suffix == suffix ) return suffix;
        std::string tpm_suffix = suffix;
        transform(tpm_suffix.begin(), tpm_suffix.end(), tpm_suffix.begin(), ::toupper);
        if ( file_suffix == tpm_suffix ) return suffix;
    }
    return "false";
}

bool CLoader::isFile(const std::string & path ) {
    return !(std::filesystem::is_directory(path));
}

// ==============================================================

const char * badFileFormat::what() const noexcept {
    return "Bad file format!";
}

const char * cannotOpenFile::what() const noexcept {
    return "Cannot open file!";
}

const char * noPath::what() const noexcept {
    return "No path given!";
}