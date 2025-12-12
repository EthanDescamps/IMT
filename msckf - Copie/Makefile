SRC_DIR = src
INC_DIR = include

# Tous les .cpp : ceux dans src/ + main.cpp à la racine
SRC = $(SRC_DIR)/matrix.cpp \
      $(SRC_DIR)/quaternion.cpp \
      $(SRC_DIR)/vector3d.cpp \
      $(SRC_DIR)/msckf.cpp \
      main.cpp

OBJ = $(SRC:.cpp=.o)

HEADERS = $(INC_DIR)/types.h

CXX = g++
CXXFLAGS = -Wall -g -I$(INC_DIR) -w

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# règle générique valable pour tous les .cpp (src/ et racine)
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean all
clean:
	rm -f $(OBJ) $(TARGET)
