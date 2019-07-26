# Makefile for building: helloqt
CC          = gcc
CXX         = g++
LINKER      = g++
LFLAGS      = -lm -static

OBJECTS     = helloqt.o
DSTTARGET   = helloqt
# Default rule
all: $(DSTTARGET)


$(DSTTARGET): $(OBJECTS)
	$(LINKER)  $(LFLAGS)  -o $@  $(OBJECTS)

helloqt.o: helloqt.cpp
	$(CXX) -c  -o  $@  $<  

clean:
	rm  $(OBJECTS)  helloqt.exe