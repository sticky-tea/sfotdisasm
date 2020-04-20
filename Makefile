CC=g++
CFLAGS=-Wall
SOURCES=opcodes.cpp main.cpp
EXDIR=bin
EXECUTABLE=sfotdisasm

all:
	mkdir $(EXDIR) && $(CC) $(SOURCES) $(CFLAGS) -o $(EXDIR)/$(EXECUTABLE)

install:
	install $(EXDIR)/$(EXECUTABLE) /usr/local/bin

uninstall:
	rm /usr/local/bin/$(EXECUTABLE)