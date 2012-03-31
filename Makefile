CXX      = g++
CXXFLAGS = -g -Wall $(shell pkg-config --cflags gtk+-2.0)
LDFLAGS  = $(shell pkg-config --libs gtk+-2.0) -lnotify

all: fortuner

fortuner: src/main.o src/settings.o
	$(CXX) -o $@ $^ $(LDFLAGS)

src/main.o: src/main.cpp
	$(CXX) -o $@ -c $(CXXFLAGS) $<

src/settings.o: src/settings.cpp
	$(CXX) -o $@ -c $(CXXFLAGS) $<

.PHONY: clean cleanest

clean:
	rm src/*.o

cleanest: clean
	rm fortuner
