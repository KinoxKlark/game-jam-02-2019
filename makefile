include makefile_vars
export

GCC = g++
GCC_FLAGS = -Wall -std=c++11 -g -Os -I $(I_DIR)

ifeq ($(OS), win32)
GCC_LIBS = -L $(L_DIR)
else
GCC_LIBS = 
endif
GCC_LIBS += -lsfml-graphics 
GCC_LIBS += -lsfml-window 
GCC_LIBS += -lsfml-system 
#GCC_LIBS += -lsfml-audio 
#GCC_LIBS += -lsfml-network

ifeq ($(OS),win32)
GCC_FLAGS += -DWIN32
endif

DLL = $(DLL_DIR)

BUILD_DIR = ./build
SOURCES_DIR = ./sources
OBJECTS_DIR = ./objects

all: game

game: main.o game.o renderer.o inputs.o copy_dll build_dir
	$(GCC) $(GCC_FLAGS) $(OBJECTS_DIR)/main.o \
				 		$(OBJECTS_DIR)/game.o \
					    $(OBJECTS_DIR)/renderer.o \
						$(OBJECTS_DIR)/inputs.o \
			-o build/game.exe $(GCC_LIBS)

main.o: $(SOURCES_DIR)/main.cpp $(SOURCES_DIR)/intrinsic.h objects_dir
	$(GCC) $(GCC_FLAGS) -c $(SOURCES_DIR)/main.cpp -o $(OBJECTS_DIR)/main.o

game.o: $(SOURCES_DIR)/game.cpp $(SOURCES_DIR)/game.h $(SOURCES_DIR)/intrinsic.h  objects_dir
	$(GCC) $(GCC_FLAGS) -c $(SOURCES_DIR)/game.cpp -o $(OBJECTS_DIR)/game.o

renderer.o: $(SOURCES_DIR)/renderer.cpp $(SOURCES_DIR)/renderer.h $(SOURCES_DIR)/intrinsic.h  objects_dir
	$(GCC) $(GCC_FLAGS) -c $(SOURCES_DIR)/renderer.cpp -o $(OBJECTS_DIR)/renderer.o

inputs.o: $(SOURCES_DIR)/inputs.cpp $(SOURCES_DIR)/inputs.h $(SOURCES_DIR)/intrinsic.h  objects_dir
	$(GCC) $(GCC_FLAGS) -c $(SOURCES_DIR)/inputs.cpp -o $(OBJECTS_DIR)/inputs.o


copy_dll: build_dir
ifeq ($(OS), win32)
	copy $(DLL)\*.dll $(BUILD_DIR)
endif


objects_dir:
ifeq ($(OS), win32)
	if not exist "$(OBJECTS_DIR)" mkdir $(OBJECTS_DIR)
else
	mkdir -p $(OBJECTS_DIR)
endif

build_dir:
ifeq ($(OS),win32)
	if not exist "$(BUILD_DIR)" mkdir $(BUILD_DIR)
else
	mkdir -p $(BUILD_DIR)
endif

clean:
ifeq ($(OS), win32)
	del $(BUILD_DIR)\*.exe
	del $(BUILD_DIR)\*.dll
	del $(OBJECTS_DIR)\*.o
else
	rm $(BUILD_DIR)/*.exe
	rm $(OBJECTS_DIR)/*.o
endif
