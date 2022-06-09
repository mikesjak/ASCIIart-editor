#pragma once

#include <iostream>
#include <memory>

#include "CAbstractEffect.hpp"

/**
 * class representing 'Make darker' effect
 * makes file darker by some degree
 * @inherit CAbstractEffect
 */
class CDark : public CAbstractEffect {
    public:
        /**
        * Manages darkness of the image
        * @param files files to be modified
        * @param ascii_sign ascii transition
        * @throw unexpectedEndOfInput when reads EOF
        */
        virtual void manage( std::vector <std::shared_ptr<CAbstractFormat>>& files, const std::map< int, char >& ) override;

        /**
         * Prints help for 'make darker' effect
         */
        virtual void help() override;

        /**
        * Prints 'make darker' banner
        */
        virtual void banner() override;
    protected:
        /**
        * Makes each pixel darker
        * @param file pixels of given file
        * @param ascii_signs ascii transition
        * @param choice value of value to be changed
        */
        virtual void adjustLight( std::shared_ptr<CAbstractFormat>& file, const std::map< int, char >& ascii_signs, int& choice );
};
