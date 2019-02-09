include makefile_vars
export

GCC = g++
GCC_FLAGS = -Wall -std=c++11 -I $(I_DIR)
GCC_LIBS = -L $(L_DIR) \
	-lsfml-graphics \
	-lsfml-window \
	-lsfml-system \
	-lsfml-audio

DLL = $(DLL_DIR)

BUILD_DIR = .\build
SOURCES_DIR = .\sources
OBJECTS_DIR = .\objects

all: game

game: main.o game.o renderer.o copy_dll build_dir
	$(GCC) $(GCC_FLAGS) $(OBJECTS_DIR)\main.o $(OBJECTS_DIR)\game.o $(OBJECTS_DIR)\renderer.o -o build\game.exe $(GCC_LIBS)

main.o: $(SOURCES_DIR)\main.cpp $(SOURCES_DIR)\intrinsic.h objects_dir
	$(GCC) $(GCC_FLAGS) -c $(SOURCES_DIR)\main.cpp -o $(OBJECTS_DIR)\main.o

game.o: $(SOURCES_DIR)\game.cpp $(SOURCES_DIR)\game.h $(SOURCES_DIR)\intrinsic.h  objects_dir
	$(GCC) $(GCC_FLAGS) -c $(SOURCES_DIR)\game.cpp -o $(OBJECTS_DIR)\game.o

renderer.o: $(SOURCES_DIR)\renderer.cpp $(SOURCES_DIR)\renderer.h $(SOURCES_DIR)\intrinsic.h  objects_dir
	$(GCC) $(GCC_FLAGS) -c $(SOURCES_DIR)\renderer.cpp -o $(OBJECTS_DIR)\renderer.o

copy_dll: build_dir
	copy $(DLL)\*.dll $(BUILD_DIR)

objects_dir:
	if not exist "$(OBJECTS_DIR)" mkdir $(OBJECTS_DIR)

build_dir:
	if not exist "$(BUILD_DIR)" mkdir $(BUILD_DIR)

clean:
	del $(BUILD_DIR)\*.exe
	del $(BUILD_DIR)\*.dll
	del $(OBJECTS_DIR)\*.o
