GCC = g++
GCC_FLAGS = -Wall -std=c++11 -I "D:\Librairies\Cpp\SFML-2.4.2\include"
GCC_LIBS = -L "D:\Librairies\Cpp\SFML-2.4.2\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

DLL = "D:\Librairies\Cpp\SFML-2.4.2\bin"

BUILD_DIR = .\build
SOURCES_DIR = .\sources
OBJECTS_DIR = .\objects

all: game

game: main.o game.o copy_dll build_dir
	$(GCC) $(GCC_FLAGS) $(OBJECTS_DIR)\main.o $(OBJECTS_DIR)\game.o -o build\game.exe $(GCC_LIBS)

main.o: $(SOURCES_DIR)\main.cpp objects_dir
	$(GCC) $(GCC_FLAGS) -c $(SOURCES_DIR)\main.cpp -o $(OBJECTS_DIR)\main.o

game.o: $(SOURCES_DIR)\game.cpp $(SOURCES_DIR)\game.h objects_dir
	$(GCC) $(GCC_FLAGS) -c $(SOURCES_DIR)\game.cpp -o $(OBJECTS_DIR)\game.o

copy_dll: build_dir
	copy $(DLL)\*.dll $(BUILD_DIR)

objects_dir:
	if not exist "$(OBJECTS_DIR)" mkdir $(OBJECTS_DIR)

build_dir:
	if not exist "$(BUILD_DIR)" mkdir $(BUILD_DIR)
