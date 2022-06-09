#pragma once

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <memory>
#include "CAbstractFormat.hpp"
#include "CKeyHandler.hpp"

#define FPP 2

/**
 * Class representing animation player
 */
class CPlayer {
public:
    /**
     * Function managing animation creating and playing
     * @param files to be played
     * @param ascii_signs ascii transition
     */
    void manageSequence( std::vector < std::shared_ptr< CAbstractFormat > >& files, std::map< int, char >& ascii_signs );
private:
    /**
     * Selecting frames to play from all loaded images
     * @param files all loaded images
     */
    void framesSelect( std::vector< std::shared_ptr< CAbstractFormat > >& files );

    /**
     * Prints list of all files
     * @param files all loaded files
     * @throw unexpectedEndOfInput when read EOF
     * @throw badChoice when input out of range
     */
    static void printFileList(std::vector< std::shared_ptr< CAbstractFormat > >& files);

    /**
     * Switching 2 files to create right order of images
     * @throw unexpectedEndOfInput when read EOF
     * @throw badChoice when input out of reange
     */
    void switchFiles();

    /**
     * Function playing animation
     * Keeps playing until it gets stopped by pressing enter
     * @param ascii_signs ascii transition
     */
    void animate( std::map< int, char >& ascii_signs );

    /**
     * Inserting files in alphabetical order
     * @param frame to be inserted
     */
    void alphabeticalInput( std::shared_ptr< CAbstractFormat >& frame );

    /**
     * Frames of current animation
     */
    std::vector< std::shared_ptr< CAbstractFormat > > frames;
};

