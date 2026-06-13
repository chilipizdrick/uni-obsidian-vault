CXX ?= c++
CXXFLAGS += -O0

all: foo

.PHONY: all clean

foo: foo.o
	$(CXX) $(CXXFLAGS) -o $@ foo.o

.cpp.o:
	$(CXX) ${CXXFLAGS} -o $@ -c $<

.map:
	touch $@

bar:
	echo $@

clean:
	rm -Rf foo foo.o
