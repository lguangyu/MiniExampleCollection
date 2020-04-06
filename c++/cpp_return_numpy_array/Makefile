PYTHON_INCLUDE=
PYTHON_LIB=
NUMPY_INCLUDE=
NUMPY_LIB=
CXX=g++
CXXSTD:=-std=c++11
override CFLAGS:=$(CXXSTD) $(CFLAGS) -fPIC -Wall $(PYTHON_INCLUDE) $(NUMPY_INCLUDE) -MMD -MP
override LDFLAGS:=$(LDFLAGS) $(PYTHON_LIB) $(NUMPY_LIB)

TARGET = module.so
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPENDS = $(SOURCES:.cpp=.d)

.PHONY: build
build: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -shared -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

.PHONY: run
run: build
	./check.py

.PHONY: clean
clean:
	-rm -f $(TARGET)
	-rm -f $(OBJECTS)
	-rm -f $(DEPENDS)

-include $(DEPENDS)
