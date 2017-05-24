.PHONY:

FLAGS = -Wall -ansi -pedantic -static -std=c++14
EXE = asap-factory-example.exe
CPP = example.cpp

build:
	g++ $(FLAGS) -o $(EXE) $(CPP)

run: build
	./$(EXE)
