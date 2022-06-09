#pragma once

#include "CAbstractEffect.hpp"

/**
 * Class representing 'Rotate' effect
 * can rotate in 4 directions
 * @inherit CAbstractEffect
 */
class CRotate : public CAbstractEffect {
    public:
        /**
        * manages rotation of the image
        * @param file file to be rotated
        * @param ascii_sign ascii transition
        */
        virtual void manage( std::vector <std::shared_ptr<CAbstractFormat>>& files, const std::map< int, char >& ) override;

        /**
        * banner prints 'Rotate' banner
        */
        virtual void banner() override;
    protected:
        /**
         * menu Menu to coordinate rotating
         * @param file File to be rotated
         * @throw unexpectedEndOfInput when read EOF
         * @throw badChoice when input out of range
         */
        void menu( std::vector <std::shared_ptr<CAbstractFormat>>& files);


         /**
         * help prints help for 'Rotate' effect
         */
         virtual void help() override;

         /**
         * rotateRight function to rotated whole picture 90 degrees right
         * @param file File to be rotated
         */
        static void rotateRight( std::shared_ptr<CAbstractFormat>& file );

        /**
         * rotateRight function to rotated whole picture 90 degrees left
         * @param file File to be rotated
         */
        static void rotateLeft( std::shared_ptr<CAbstractFormat>& file );

        /**
         * flipHorizontally flips file horizontally
         * @param file File to be flipped
         */
        static void flipHorizontally( std::shared_ptr<CAbstractFormat>& );

        /**
         * rotateRight flips file vertically
         * @param file File to be flipped
         */
        static void flipVertically( std::shared_ptr<CAbstractFormat>& );
};
