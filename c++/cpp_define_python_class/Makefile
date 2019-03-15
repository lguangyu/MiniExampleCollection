CXXSTD = -std=c++11
PYTHON_INCLUDE = -I/usr/include/python3.5
PYTHON_LIB =
override CXXFLAGS := $(CXXFLAGS)
override LDFLAGS := $(LDFLAGS)

TARGET = foo.so
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPENDENCIES = $(SOURCES:.cpp=.d)


.PHONY: build
build: $(TARGET)


$(TARGET): $(OBJECTS)
	$(CXX) -shared -o $@ $^ $(LDFLAGS) $(PYTHON_LIB)


%.o: %.cpp
	$(CXX) $(CXXSTD) $(CXXFLAGS) $(PYTHON_INCLUDE) -fPIC -c -MMD -MP -o $@ $<


.PHONY: check
check: build
	./check.py


.PHONY: clean
clean:
	-rm -f $(TARGET)
	-rm -f $(OBJECTS)
	-rm -f $(DEPENDENCIES)


-include $(DEPENDENCIES)
