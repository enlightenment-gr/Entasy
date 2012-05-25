CC=gcc
LINK=-Wall `pkg-config --cflags --libs emotion elementary gstreamer-0.10`
OUT= -o ./bin/entasy

all:
	$(CC) ./src/entasy_main.c $(OUT) $(LINK)
