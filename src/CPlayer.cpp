#include "CPlayer.hpp"

void CPlayer::manageSequence( std::vector< std::shared_ptr< CAbstractFormat > >& files, std::map< int, char >& ascii_signs ) {

    framesSelect( files );
    for ( auto& frame : frames ) std::cout << frame->fileName << std::endl;

    if ( frames.size() > 1 ){
        switchFiles();
    }

    if ( frames.size() == 1 ) {
        frames[0]->print(ascii_signs);
        return;
    }
    while ( true ) {
        animate( ascii_signs );
        std::cout << "Press enter for Play!" << std::endl;
        std::cout << "Press Space and Enter to exit!\n" << std::endl;
        while ( !CKeyHandler::kbhit() ) {}
        if ( CKeyHandler::getch() == 32 ) break;
    }
}

void CPlayer::printFileList ( std::vector< std::shared_ptr< CAbstractFormat > >& files ) {
    int counter = 0;
    for ( auto &f : files ) {
        std::cout << counter <<". " << f->fileName << std::endl;
        counter++;
    }
}

void CPlayer::framesSelect( std::vector< std::shared_ptr< CAbstractFormat > >& files ) {

    int choice;
    std::cout << "Do you want to use all imported images?" << std::endl;
    std::cout << "  1. Yes" << std::endl;
    std::cout << "  2. No" << std::endl;
    std::cin >> choice;
    if ( std::cin.eof() ) throw unexpectedEndOfInput();
    if ( choice != 1 && choice != 2 ) throw badChoice();
    if ( choice == 1 ) {
        for ( unsigned int i = 0; i < files.size(); i++ ) {
            alphabeticalInput(files[i]);
        }
        return;
    }

    std::string tmp, chosenFrames;
    std::cout << "Choose frames you want to be in sequence!" << std::endl;
    printFileList(files);
    std::cin >> chosenFrames;
    if ( std::cin.eof() ) throw unexpectedEndOfInput();
    std::getline(std::cin, tmp);
    if ( std::cin.eof() ) throw unexpectedEndOfInput();
    chosenFrames.append(tmp);
    tmp.clear();

    for (char chosenFrame : chosenFrames) {
        std::string c;
        c.append(1, chosenFrame);
        if ( c == " " ) {
            std::shared_ptr< CAbstractFormat > file = files[stoi(tmp)];
            alphabeticalInput(file);
            tmp.clear();
        }
        else {
            tmp.append(c);
        }
    }
    if ( !tmp.empty() ) {
        auto file = (files[stoi(tmp)]);
        alphabeticalInput(file);
        tmp.clear();
    }
}

void CPlayer::switchFiles() {
    while ( true ) {
        std::system("clear");
        std::cout << "If you want to swap order of files input their index!" << std::endl;
        std::cout << "If you are ready press R!\n" << std::endl;
        printFileList(frames);

        std::string choice, tmp, num;
        int X, Y;
        X = Y = -1;
        std::cin >> choice;
        if ( std::cin.eof() ) throw unexpectedEndOfInput();
        std::getline(std::cin, num);
        if ( std::cin.eof() ) throw unexpectedEndOfInput();
        if ( choice == "R" ) break;
        else {
            choice.append(num);
            for (char s : choice) {
                std::string c;
                c.append(1, s);
                if ( c == " " ) {
                    if ( X == -1 ) X = stoi(tmp);
                    else Y = stoi(tmp);
                    tmp.clear();
                }
                else {
                    if ( !std::isdigit(s) ) throw badChoice();
                    tmp.append(c);
                }
            }
        }
        if (!tmp.empty()) {
            if (Y == -1) {
                Y = stoi(tmp);
            }
            else throw badChoice();
        }
        if ( std::cin.eof() ) throw unexpectedEndOfInput();
        if ( X == -1 || Y == -1 || X == Y || X < 0 || Y < 0 || X > int(frames.size()-1) || Y > int(frames.size()-1) ) {
            throw badChoice();
        }
        std::swap(frames[X], frames[Y]);
    }
}

void CPlayer::animate( std::map< int, char >& ascii_signs ) {

    unsigned int i = 0;
    while ( !CKeyHandler::kbhit() ) {
        std::cout << "Press enter for Pause!\n" << std::endl;
        frames[i++]->showImage(ascii_signs);
        std::this_thread::sleep_for(std::chrono::milliseconds(100*FPP));
        i = i % frames.size();
    }
    CKeyHandler::getch();
}

void CPlayer::alphabeticalInput( std::shared_ptr< CAbstractFormat >& frame ) {

    if (frames.empty()) {
        frames.push_back(frame);
        return;
    }
    std::string name = frame->fileName;
    auto it = frames.begin();
    for ( unsigned int i = 0; i < frames.size(); i++ ) {
        std::cout << name << " VS " << frames[i]->fileName << std::endl;
        if ( (frames[i]->fileName > name) && (frames[i]->fileName.size() == name.size()) ) break;
        if ( frames[i]->fileName.size() > name.size() ) break;
        it++;
    }

    frames.insert(it, frame);
}
