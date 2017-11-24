# Makefile for the whole of the backend server

CC?=gcc
CFLAGS?=-g -O2

CFLAGS:=$(CFLAGS)
CPPFLAGS:=-I../include -Iinclude/
LIBS:=
LDFLAGS:=

OUT:=backend
OBJ:=backend.o
include editor/make.config

# Targets
.PHONY: all clean

all: $(OUT)

clean:
	rm -f $(OBJ) $(OUT)

$(OUT): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)
