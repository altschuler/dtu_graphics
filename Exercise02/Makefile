ID := 01
EXE := e$(ID)
BIN_DIR := 02561-02-$(ID)
SRC_DIR := 02561-02-$(ID)

CC := clang++

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/Angel/*.cpp)
OBJ_FILES := $(addprefix $(SRC_DIR)/obj/,$(notdir $(CPP_FILES:.cpp=.o)))
CC_FLAGS := -std=c++0x \
-I$(SRC_DIR)/Angel \
-lglut -lGL -lGLU -lGLEW

$(SRC_DIR)/obj/%.o: $(SRC_DIR)/Angel/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $<

$(SRC_DIR)/obj/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $<

all: run

build: $(OBJ_FILES)
	$(CC) $(CC_FLAGS) -g -o $(BIN_DIR)/$(EXE) $^

.PHONY: run
run: build
	cd $(BIN_DIR) && ./$(EXE)

clean:
	rm -f $(OBJ_FILES) $(BIN_DIR)/$(EXE)
