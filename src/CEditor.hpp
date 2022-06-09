#pragma once

#include "CAbstractFormat.hpp"
#include "CAbstractEffect.hpp"
#include "CDark.hpp"
#include "CLight.hpp"
#include "CRotate.hpp"
#include "CNegative.hpp"

/**
 * Class representing Image editor
 */
class CEditor {
    public:
        /**
        * Takes care of effect selection
         * @throw unexpectedEndOfInput when reads EOF
         * @throw badChoice when input out of range
        */
        static void editorMenu( std::vector<std::shared_ptr<CAbstractFormat>>& files, std::map< int, char >& ascii_signs );

        /**
         * Map of ascii transition
         * @source src/transition.txt
         */
        std::map< int, char > ascii_signs;

private:
        /**
         * Function representing Effect menu
         * @return index of users chosen effect
         * @throw unexpectedEndOfInput when reads EOF
         * @throw badChoice when input out of range
         */
        static int chooseEffect();

        /**
         * Map to use effects
         */
        static std::map < int, std::shared_ptr< CAbstractEffect > > effects;
};