TARGET_EXEC ?= realpath

BUILD_DIR ?= ./build
SRC_DIRS ?= ./source
LIB_DIR ?= ./lib

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find ./include -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CXX := g++
STANDARD := -std=c++11
OPT := -O3
WARN_FLAGS := -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wcast-qual -Wcast-align
DEBUG_FLAGS := -g -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
ASAN := -fsanitize=address,undefined

CPPFLAGS = $(INC_FLAGS) $(STANDARD) $(OPT) $(WARN_FLAGS) $(DEBUG_FLAGS) $(ASAN) -MMD -MP -fPIC

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(CPPFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: lib
lib: $(OBJS)
	$(MKDIR_P) $(LIB_DIR)
	$(CXX) $(CPPFLAGS) -shared -o $(LIB_DIR)/librealpath.so $(OBJS)

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR) $(LIB_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
