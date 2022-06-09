#include "CEditor.hpp"


std::map <int, std::shared_ptr< CAbstractEffect > > CEditor::effects = {{1, std::make_shared<CLight>(CLight()) },
                                                                        {2, std::make_shared<CDark>(CDark())   },
                                                                        {3, std::make_shared<CRotate>(CRotate())},
                                                                        {4, std::make_shared<CNegative>(CNegative())}
                                                                        };

int CEditor::chooseEffect() {
    int chosenEffect;
    std::system("clear");
    std::cout << "Choose effect you want to apply:" << std::endl;
    std::cout << "   1. Make lighter" << std::endl;
    std::cout << "   2. Make darker" << std::endl;
    std::cout << "   3. Rotate" << std::endl;
    std::cout << "   4. Negative" << std::endl;
    std::cout << "   0. back" << std::endl;
    std::cin >> chosenEffect;
    if ( std::cin.eof() ) throw unexpectedEndOfInput();
    if ( chosenEffect < 0 || chosenEffect > 5 ) {
        throw badChoice();
    }
    return chosenEffect;
}

void CEditor::editorMenu( std::vector<std::shared_ptr<CAbstractFormat>>& files, std::map< int, char >& ascii_signs ) {
    std::system("clear");
    std::vector<std::shared_ptr<CAbstractFormat>> filesToModify;
    if ( files.empty() ) throw noGivenFiles();

    // Effect choosing
    int chosenEffect = chooseEffect();
    auto it = effects.find(chosenEffect);
    auto effect = it->second;

    // Choosing files to modify
    int choice;
    std::cout << "Do you want to apply this effect to all files without seeing result?" << std::endl;
    std::cout << "  1. Yes" << std::endl;
    std::cout << "  2. No" << std::endl;
    std::cin >> choice;
    if ( std::cin.eof() ) throw unexpectedEndOfInput();
    if ( choice == 1 ) {
        for ( auto&file : files )
            filesToModify.push_back(file);
    }
    else if ( choice == 2 ) {
        std::cout << "Choose a pictures to modify!" << std::endl;
        int counter = 0;
        for ( auto &f : files ) {
            std::cout << counter <<". " << f->fileName << std::endl;
            counter++;
        }
        std::string chosenFrames, tmp;
        std::cin >> chosenFrames;
        if ( std::cin.eof() ) throw unexpectedEndOfInput();
        std::getline(std::cin, tmp);
        if ( std::cin.eof() ) throw unexpectedEndOfInput();
        chosenFrames.append(tmp);
        tmp.clear();

        // Separating file indexes from string
        for (char chosenFrame : chosenFrames) {
            std::string c;
            c.append(1, chosenFrame);
            if ( c == " " ) {
                std::shared_ptr< CAbstractFormat > file = files[stoi(tmp)];
                filesToModify.push_back(file);
                tmp.clear();
            }
            else {
                tmp.append(c);
            }
        }
        if ( !tmp.empty() ) {
            auto file = (files[stoi(tmp)]);
            filesToModify.push_back(file);
            tmp.clear();
        }
    }
    else throw badChoice();

    try {
        effect->manage( files, ascii_signs );
    }
    catch ( std::exception & ex ) {
        std::system("clear");
        std::cout << ex.what() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        return;
    }
    if ( choice == 2 ) {
        for ( auto&file : filesToModify )
            file->print(ascii_signs);
    }
}

const char * noGivenFiles::what() const noexcept {
    return "No files given!";
}
