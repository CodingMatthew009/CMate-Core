#Build Lib and Sandbox
FLAGS = -Wall -std=c++20
FILES = $(wildcard Source/*.cpp) $(wildcard Source/Math/*.cpp)  
FILES_OBJ = $(FILES:.cpp=.o)

cmate-core.a: $(FILES_OBJ)
	ar rcs cmate-core.a $(FILES_OBJ)

%.o: %.cpp
		g++ $(FLAGS) -c $< -o $@

clean:
		rm cmate-core.a $(FILES_OBJ)

#Sandbox: $(FILES_OBJ)
#		g++ -o Sandbox $(FILES_OBJ)

#%.o: %.cpp
#		g++ $(FLAGS) -c $< -o $@

#clean:
#		rm Sandbox $(FILES_OBJ)
