# ASCIIart-editor

### Final project for _Programming and Algorithmics 2_ course <br/>
## [![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)

## About
- Second semester final project for BI-PA2
- ASCIIart editor currently working with BMP and TGA files

## How it works
Go to project folder and type
```
make all
```
which compiles all necessary files and creates a doxygen documentation. <br>
then run it and the program will lead you all the way to editing.


## How to run project
Go to project folder and type:
```
make compile && make run
```

## Options in makefile
```
make/make all      - compiles project and documentation
make clean         - deletes everything that could be created by make all or test_all
make count         - counts number of lines in code
make compile       - compiles whole project
make doc           - creates documentation using doxygen
make run           - runs project
make test_all      - runs all tests
```
