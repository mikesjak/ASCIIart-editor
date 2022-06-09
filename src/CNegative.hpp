#pragma once

#include "CAbstractEffect.hpp"

/**
 * Class representing 'Negate' effect
 * negates whole image
 * @inherit CAbstractEffect
 */
class CNegative : public CAbstractEffect {
    public:
        /**
        * Manages grayscale of the image
        * @param files files to be modified
        * @param ascii_sign ascii transition
        * @throw unexpectedEndOfInput when reads EOF
        * @throw badChoice when input out of range
        */
        virtual void manage( std::vector <std::shared_ptr<CAbstractFormat>>& files, const std::map< int, char > & ) override;

        /**
        * Prints help for 'Negative' effect
        */
        virtual void help() override;

        /**
        * Prints 'Negative' banner
        */
        virtual void banner() override;
    protected:
        /**
         * Negates all pixels in picture
         * @param file
         */
        void negate( std::shared_ptr<CAbstractFormat>& file);
};
