CXX := g++
PYTHON_INCLUDE_PATH = -I/usr/include/python3.5
CFLAGS :=

.PHONY: build
build: clib.so

clib.so: clib.o
	$(CXX) -fPIC -shared -o $@ $^

%.o: %.cpp
	$(CXX) $(CFLAGS) $(PYTHON_INCLUDE_PATH) -fPIC -c -o $@ $<

.PHONY: clean
clean:
	-rm -f *.o
	-rm -f *.so
