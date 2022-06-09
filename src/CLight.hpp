#pragma once

#include <iostream>
#include <memory>

#include "CAbstractEffect.hpp"

/**
 * Class representing 'Make lighter' effect
 * makes file lighter by some degree
 * @inherit CAbstractEffect
 */
class CLight : public CAbstractEffect {
    public:
        /**
        * Manages brightens the image
        * @param files files to be modified
        * @param ascii_sign ascii transition
        * @throw unexpectedEndOfInput when reads EOF
        * @throw badChoice when input out of range
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
        * Makes each pixel brighter
        * @param file pixels of given file
        * @param ascii_sign ascii transition
        * @param choice value of value to be changed
        */
        static void adjustLight( std::shared_ptr<CAbstractFormat>&, const std::map< int, char >&, int& );
};
