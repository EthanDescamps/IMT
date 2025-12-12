SRC_DIR = scrc
INC_DIR = include

SRC = $(SRC_DIR)/matrix.cpp \
      $(SRC_DIR)/quaternion.cpp \
      $(SRC_DIR)/vector3d.cpp \
      $(SRC_DIR)/msckf.cpp \
      main.cpp

OBJ = $(SRC:.cpp=.o)

CXX      = g++
CXXFLAGS = -Wall -g -I$(INC_DIR)  -w

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# règle générique : .cpp -> .o (fonctionne pour fichiers à la racine et dans sous-dossiers)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean all
clean:
	rm -f $(OBJ) $(TARGET)
