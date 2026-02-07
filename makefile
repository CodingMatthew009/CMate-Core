FLAGS = -Wall -std=c++20
FILES = Sandbox.cpp $(wildcard Source/*.cpp) $(wildcard Source/Math/*.cpp) $(wildcard Source/Math/ProceduralNoise/*.cpp) 
FILES_OBJ = $(FILES:.cpp=.o)

Sandbox: $(FILES_OBJ)
		g++ -o Sandbox $(FILES_OBJ)

%.o: %.cpp
		g++ $(FLAGS) -c $< -o $@

clean:
		rm Sandbox $(FILES_OBJ)
