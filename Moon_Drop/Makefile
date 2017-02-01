

#OBJS specifies which files to compile as part of the project
OBJS = main.cpp graphics.cpp game.cpp input.cpp sprite.cpp animatedSprites.cpp player.cpp level.cpp cam.cpp tinyxml2.cpp tile.cpp Rectangle.cpp
#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I/home/jarron/Desktop/Moon_Drop/headers 


#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L/usr/lib -L/usr/local/lib 

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w -Wl,-subsystem -std=c++14
#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf 

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Skygrade

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
