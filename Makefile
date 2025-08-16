CC=gcc
CFLAGS=-Wall -Wextra -std=c99

SOURCES=vm.c snekobject.c stack.c sneknew.c main.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=gc_test

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)
