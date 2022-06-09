#include "CAplication.hpp"

CAplication::CAplication() {
    try {
        loadTransition();
    }
    catch ( std::exception & ex ) {
        std::cout << ex.what() << std::endl;
        return;
    }
    welcomeMessage();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000) );
    menu();
}

void CAplication::welcomeMessage () {
    std::system("clear");
    std::cout << "    /$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$ /$$$$$$                       /$$                  \n";
    std::cout << "   /$$__  $$ /$$__  $$ /$$__  $$|_  $$_/|_  $$_/                      | $$                  \n";
    std::cout << "  | $$  \\ $$| $$  \\__/| $$  \\__/  | $$    | $$    /$$$$$$   /$$$$$$  /$$$$$$                \n";
    std::cout << "  | $$$$$$$$|  $$$$$$ | $$        | $$    | $$   |____  $$ /$$__  $$|_  $$_/                \n";
    std::cout << "  | $$__  $$ \\____  $$| $$        | $$    | $$    /$$$$$$$| $$  \\__/  | $$                  \n";
    std::cout << "  | $$  | $$ /$$  \\ $$| $$    $$  | $$    | $$   /$$__  $$| $$        | $$ /$$              \n";
    std::cout << "  | $$  | $$|  $$$$$$/|  $$$$$$/ /$$$$$$ /$$$$$$|  $$$$$$$| $$        |  $$$$/              \n";
    std::cout << "  |__/  |__/ \\______/  \\______/ |______/|______/ \\_______/|__/         \\___/                \n";
    std::cout << "                                                                                            \n";
    std::cout << "                                                                                            \n";
    std::cout << "    /$$$$$$  /$$$$$$$$ /$$   /$$ /$$$$$$$$ /$$$$$$$   /$$$$$$  /$$$$$$$$  /$$$$$$  /$$$$$$$ \n";
    std::cout << "   /$$__  $$| $$_____/| $$$ | $$| $$_____/| $$__  $$ /$$__  $$|__  $$__/ /$$__  $$| $$__  $$\n";
    std::cout << "  | $$  \\__/| $$      | $$$$| $$| $$      | $$  \\ $$| $$  \\ $$   | $$   | $$  \\ $$| $$  \\ $$\n";
    std::cout << "  | $$ /$$$$| $$$$$   | $$ $$ $$| $$$$$   | $$$$$$$/| $$$$$$$$   | $$   | $$  | $$| $$$$$$$/\n";
    std::cout << "  | $$|_  $$| $$__/   | $$  $$$$| $$__/   | $$__  $$| $$__  $$   | $$   | $$  | $$| $$__  $$\n";
    std::cout << "  | $$  \\ $$| $$      | $$\\  $$$| $$      | $$  \\ $$| $$  | $$   | $$   | $$  | $$| $$  \\ $$\n";
    std::cout << "  |  $$$$$$/| $$$$$$$$| $$ \\  $$| $$$$$$$$| $$  | $$| $$  | $$   | $$   |  $$$$$$/| $$  | $$\n";
    std::cout << "   \\______/ |________/|__/  \\__/|________/|__/  |__/|__/  |__/   |__/    \\______/ |__/  |__/\n\n";

    std::cout << "   ____  _  _          __   __   __ _  _  _  ____        _  _   __   __ _  ____  ____   \n";
    std::cout << "  (  _ \\( \\/ )       _(  ) / _\\ (  / )/ )( \\(  _ \\      ( \\/ ) (  ) (  / )(  __)/ ___)  \n";
    std::cout << "   ) _ ( )  /       / \\) \\/    \\ )  ( ) \\/ ( ) _ (      / \\/ \\  )(   )  (  ) _) \\___ \\  \n";
    std::cout << "  (____/(__/        \\____/\\_/\\_/(__\\_)\\____/(____/      \\_)(_/ (__) (__\\_)(____)(____/  \n";

}

void CAplication::turningOff() {
    std::system("clear");
    std::cout << "Thank you for using our program." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000) );
    std::cout << "Goodbye!" << std::endl;
}

void CAplication::menu() {
    std::vector< std::shared_ptr<CAbstractFormat> > loadedFiles;
    int choice;
    CLoader loader;
    try {
        loadedFiles = loader.loadFiles( ascii_signs );
    }
    catch ( std::exception & ex ) {
        std::cout << ex.what() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000) );
        loadedFiles = loader.loadFiles( ascii_signs );
    }
    addLoadedFiles(loadedFiles);
    while (true) {
        std::system("clear");
        std::cout << "Program menu:" << std::endl;
        std::cout << "   1. LOAD"    << std::endl;
        std::cout << "   2. EDIT"    << std::endl;
        std::cout << "   3. Sequence"<< std::endl;
        std::cout << "   4. END"     << std::endl;

        std::cin >> choice;
        try {
            switch (choice) {
                default:
                    if ( std::cin.eof() ) throw unexpectedEndOfInput();
                    throw badChoice();
                case (1):
                    loadedFiles = loader.loadFiles( ascii_signs );
                    addLoadedFiles(loadedFiles);
                    break;
                case (2):
                    CEditor::editorMenu( files, ascii_signs );
                    break;
                case (4):
                    turningOff();
                    return;
                case (3):
                    CPlayer player;
                    player.manageSequence( files, ascii_signs );
                    break;
            }
        }
        catch ( std::exception & ex ) {
            std::cout << ex.what() << std::endl;
            break;
        }
    }
}

void CAplication::loadTransition() {
    std::string cwd = std::filesystem::current_path();
    cwd = cwd += "/src/transition.txt";
    int count = 0;

    char ascii_sign;
    std::ifstream data;
    data.open(cwd);
    if ( !data ) 
        throw cannotOpenFile();
    while ( true ) {
        data >> ascii_sign;
        if ( data.eof() ) break;
        ascii_signs.insert({count++, ascii_sign});
    }
    ascii_signs.insert({count, ' '});
}

void CAplication::addLoadedFiles(std::vector<std::shared_ptr<CAbstractFormat>> &loadedFiles) {
    for ( auto&file : loadedFiles )
        files.push_back(file);
}
