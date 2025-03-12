CC=gcc
CFLAGS=-W -g -std=c99

LDFLAGS=-lraylib -lm# -lgdi32 -lwinmm
APP_NAME=commotion
EXEC=bin/$(APP_NAME)

ifndef DEMO
DEMO=orbit
endif

SOURCES=$(wildcard src/*.c src/**/*.c) src/demo/impl/$(DEMO).c
HEADERS = $(wildcard src/*.h src/**/*.h)
OBJS=$(SOURCES:.c=.o)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

all: $(EXEC) makefile

clean:
	rm -fr $(EXEC) $(OBJS)

run:
	./$(EXEC)

.PHONY: all clean run
