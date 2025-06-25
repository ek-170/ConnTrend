CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -Iinclude
LDFLAGS := -lm

PKG_CONFIG  := pkg-config
NL_CFLAGS   := $(shell $(PKG_CONFIG) --cflags libnl-3.0)
NL_LIBS     := $(shell $(PKG_CONFIG) --libs libnl-3.0)
CXXFLAGS    += $(NL_CFLAGS)
CXXFLAGS 	  += -Iinclude/
LDFLAGS     += $(NL_LIBS)

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp, build/%.o, $(SRCS))
TARGET := conntrend
OUTPUT_DIR := build

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $(OUTPUT_DIR)/$@

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

.PHONY: debug
debug: CXXFLAGS += -g -O0 -fsanitize=address,undefined,leak
debug: LDFLAGS  += -fsanitize=address,undefined,leak
debug: clean all run

.PHONY: clean
clean:
	rm -rf build

.PHONY: run
run: all
	@echo "------- Running ConnTrend -------"
	@./$(OUTPUT_DIR)/$(TARGET) --interval 5 --duration 10

.PHONY: test
test:
	$(CXX) $(CXXFLAGS) test/parser_test.cpp -o test/parser_test $(LDFLAGS)
	./test/parser_test

.PHONY: dbuild
dbuild:
	docker build -t conntrend-dev .

.PHONY: drun
drun:
	docker run --rm -dt -v "$(PWD)":/app -w /app conntrend-dev
