
CPP_FILES = $(wildcard src/*.cpp)

compile:
	clang++ -std=c++11 -o build/glui $(CPP_FILES) -Iinclude/ -Ilib/ -lglfw -lGL -lGLU -lGLEW
	
run:
	./build/glui
