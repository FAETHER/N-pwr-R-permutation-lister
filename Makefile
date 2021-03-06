ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname -s 2>/dev/null || echo not')
endif

#OBJS specifies which files to compile as part of the project 
OBJS = ./*cpp
#HEADS = ./*.h

#CC specifies which compiler we're using 
CC = g++

# -w suppresses all warnings 
# -Wl,-subsystem,windows gets rid of the console window 
COMPILER_FLAGS = -w 

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -static-libgcc -static-libstdc++
 
#OBJ_NAME specifies the name of our exectuable 
OBJ_NAME = perm.exe 


#This is the target that compiles our executable 
all : 
	$(CC) $(OBJS) $(HEADS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)