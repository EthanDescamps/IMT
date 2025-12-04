SRC = matrix.cpp quaternion.cpp vector3d.cpp main.cpp
OBJ = $(SRC:.cpp=.o) 
CXXFLAGS = -Wall -g

main : $(OBJ)
	g++ -o $@  $^

clean:
	rm -f *.o main

 
