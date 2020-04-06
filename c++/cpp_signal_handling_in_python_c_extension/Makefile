PYTHON_INCLUDE=
PYTHON_LIB=
CXX=g++
CXXSTD:=-std=c++11
override CFLAGS:=$(CXXSTD) $(CFLAGS) -fPIC -Wall $(PYTHON_INCLUDE) -MMD -MP
override LDFLAGS:=$(LDFLAGS) $(PYTHON_LIB)

TARGET = foo.so
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPENDS = $(SOURCES:.cpp=.d)

.PHONY: build
build: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -shared -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

.PHONY: check
check: build
	./check.py

.PHONY: clean
clean:
	-rm -f $(TARGET)
	-rm -f $(OBJECTS)
	-rm -f $(DEPENDS)

-include $(DEPENDS)
