CXX      := g++
CXXFLAGS := -pthread -pedantic-errors -Wall
LDFLAGS  := -L/usr/lib -lstdc++ -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
OBJ_DIR2  := $(BUILD)/objects2
APP_DIR  := $(BUILD)/apps
TARGET   := alloc
TARGET2  := prov-rep
INCLUDE  := -Iinclude/
SRC      := $(wildcard src/alloc.cpp)
SRC2     := $(wildcard src/prov-rep.cpp)

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
OBJECTS2 := $(SRC2:%.cpp=$(OBJ_DIR2)/%.o)

all: 	build $(APP_DIR)/$(TARGET) $(APP_DIR)/$(TARGET2)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@echo "1"
	@echo $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(OBJ_DIR2)/%.o: %.cpp
	@mkdir -p $(@D)
	@echo "2"
	@echo $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	@echo "3"
	@echo $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

$(APP_DIR)/$(TARGET2): $(OBJECTS2)
	@mkdir -p $(@D)
	@echo "4"
	@echo $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET2) $(OBJECTS2)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR2)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(OBJ_DIR2)/*
	-@rm -rvf $(APP_DIR)/*
