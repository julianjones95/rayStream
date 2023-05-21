
SRC_FILES := $(wildcard ../Server/*.cpp)
SRC_FILES := $(filter-out ../Server/server.cpp, $(SRC_FILES))

runTests: compile run

run: 
	output/out

compile:
	g++ *.cpp $(SRC_FILES) -o output/out
