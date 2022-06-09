#pragma once

#include "CAbstractFormat.hpp"
#include "CKeyHandler.hpp"

/**
 * Abstract effect class
 */
class CAbstractEffect {
    public:
        virtual ~CAbstractEffect() = default;

        /**
         * Manages the whole effect
         * @param files Files to be modified
         * @param ascii_signs ASCII transition
         */
        virtual void manage( std::vector <std::shared_ptr<CAbstractFormat>>& files, const std::map< int, char >& ascii_signs) = 0;

        /**
         * Creates a short message about each effect
         */
        virtual void help() = 0;

        /**
         * Each effect has its own banner that is displayed
         */
        virtual void banner() = 0;

        /**
         * Creates animation from dots
         */
        static void dotsAnimation();

        /**
         * Created copies of pixel matrix for each file
         * @param files files that are being modified
         */
        void createOldVersion( std::vector<  std::shared_ptr<CAbstractFormat>> &files );

        /**
         * function managing reverting effects
         * @param files files that may be reverted
         */
        void reversing( std::vector<  std::shared_ptr<CAbstractFormat>> &files );
    private:
        /**
        * Function reversing done changes
        * @param files files to be reversed
        */
        void reverseChanges( std::vector<  std::shared_ptr<CAbstractFormat>> &files );

        /**
         * Vector of unchanged file pixels
         */
        std::vector <std::vector < std::vector< unsigned char > > > old_pixels;
};

