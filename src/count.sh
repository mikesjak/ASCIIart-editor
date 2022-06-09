#!/bin/bash

HEADERS=$( cat src/*.hpp | wc -l )
CPP=$( cat src/*.cpp | wc -l )
TESTS=$( cat tests/*.cpp | wc -l )
TOTAl=$(($HEADERS+$CPP+$TESTS))
echo "HEADERS: $HEADERS"
echo "CPP:     $CPP"
echo "TESTS:   $TESTS"
echo "TOTAL:   $TOTAl"
