# Inspired by https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/blob/master/Makefile

CXX=g++
CXXFLAGS = -Wall -pedantic -std=c++17 -g 

HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
TESTS = $(wildcard tests/*.test.cpp)
LIBRARIES=-lstdc++fs
PROGRAM = mikesj17

.PHONY: all
all: compile doc
	-rm -f build/*.o

.PHONY: run
run: $(PROGRAM)
	-rm -f build/*.o
	./app


.PHONY: compile
compile: $(PROGRAM)

mikesj17: build/main
	cp $< $@

build/main: $(OBJECTS)
	mkdir -p $(@D)
	$(CXX) $^ -o $@ $(LIBRARIES)

build/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -c -o $@ 

debug/%.test: tests/%.test.cpp $(filter-out build/main.o,$(OBJECTS))
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $< $(filter-out build/main.o,$(OBJECTS)) -I src/ -o $@

doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

.PHONY: clean
clean:
	-rm -rf build/ doc/ mikesj17 debug/ .idea/

.PHONY: test_all
test_all: $(TESTS:tests/%.test.cpp=debug/%.test)
	./tests/test.sh

count:
	./src/count.sh

# Dependencies
CAbstractEffect.o: src/CAbstractEffect.cpp src/CAbstractEffect.hpp \
 src/Format_header.hpp src/CAbstractFormat.hpp src/CKeyHandler.hpp \
 src/CBMP.hpp src/CTGA.hpp
CAbstractFormat.o: src/CAbstractFormat.cpp src/CAbstractFormat.hpp \
 src/CKeyHandler.hpp
CAplication.o: src/CAplication.cpp src/CAplication.hpp \
 src/Effect_header.hpp src/CAbstractEffect.hpp src/Format_header.hpp \
 src/CAbstractFormat.hpp src/CKeyHandler.hpp src/CBMP.hpp src/CTGA.hpp \
 src/CLight.hpp src/CDark.hpp src/CNegative.hpp src/CRotate.hpp \
 src/CPlayer.hpp src/CEditor.hpp src/CLoader.hpp
CBMP.o: src/CBMP.cpp src/CBMP.hpp src/CAbstractFormat.hpp \
 src/CKeyHandler.hpp
CDark.o: src/CDark.cpp src/CDark.hpp src/CAbstractEffect.hpp \
 src/Format_header.hpp src/CAbstractFormat.hpp src/CKeyHandler.hpp \
 src/CBMP.hpp src/CTGA.hpp
CEditor.o: src/CEditor.cpp src/CEditor.hpp src/Format_header.hpp \
 src/CAbstractFormat.hpp src/CKeyHandler.hpp src/CBMP.hpp src/CTGA.hpp \
 src/Effect_header.hpp src/CAbstractEffect.hpp src/CLight.hpp \
 src/CDark.hpp src/CNegative.hpp src/CRotate.hpp
CKeyHandler.o: src/CKeyHandler.cpp src/CKeyHandler.hpp
CLight.o: src/CLight.cpp src/CLight.hpp src/CAbstractEffect.hpp \
 src/Format_header.hpp src/CAbstractFormat.hpp src/CKeyHandler.hpp \
 src/CBMP.hpp src/CTGA.hpp
CLoader.o: src/CLoader.cpp src/CLoader.hpp src/Format_header.hpp \
 src/CAbstractFormat.hpp src/CKeyHandler.hpp src/CBMP.hpp src/CTGA.hpp
CNegative.o: src/CNegative.cpp src/CNegative.hpp src/CAbstractEffect.hpp \
 src/Format_header.hpp src/CAbstractFormat.hpp src/CKeyHandler.hpp \
 src/CBMP.hpp src/CTGA.hpp
CPlayer.o: src/CPlayer.cpp src/CPlayer.hpp src/CAbstractFormat.hpp \
 src/CKeyHandler.hpp
CRotate.o: src/CRotate.cpp src/CRotate.hpp src/CAbstractEffect.hpp \
 src/Format_header.hpp src/CAbstractFormat.hpp src/CKeyHandler.hpp \
 src/CBMP.hpp src/CTGA.hpp
CTGA.o: src/CTGA.cpp src/CTGA.hpp src/CAbstractFormat.hpp \
 src/CKeyHandler.hpp
main.o: src/main.cpp src/CAplication.hpp src/Effect_header.hpp \
 src/CAbstractEffect.hpp src/Format_header.hpp src/CAbstractFormat.hpp \
 src/CKeyHandler.hpp src/CBMP.hpp src/CTGA.hpp src/CLight.hpp \
 src/CDark.hpp src/CNegative.hpp src/CRotate.hpp src/CPlayer.hpp \
 src/CEditor.hpp src/CLoader.hpp

