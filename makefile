GCC_FLAGS = -Wall

BUILD_DIR = .\build
SOURCES_DIR = .\sources
OBJECTS_DIR = .\objects

all: game

game: main.o build_dir
	g++ -Wall $(OBJECTS_DIR)\main.o -o build\game.exe

main.o: $(SOURCES_DIR)\main.cpp objects_dir
	g++ -Wall -c $(SOURCES_DIR)\main.cpp -o $(OBJECTS_DIR)\main.o

objects_dir:
	if not exist "$(OBJECTS_DIR)" mkdir $(OBJECTS_DIR)

build_dir:
	if not exist "$(BUILD_DIR)" mkdir $(BUILD_DIR)
