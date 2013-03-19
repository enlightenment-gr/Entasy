CC=gcc
LINK=-Wall `pkg-config --cflags --libs emotion elementary`
BIN=./bin/entasy
OUT= -o $(BIN)
UNITS= ./src/entasy_cb.c ./src/entasy_tracklist.c ./src/entasy_flipper.c ./src/entasy_control_buttons.c ./src/entasy_sliders.c

all:
	$(CC) $(UNITS) ./src/entasy_main.c $(OUT) $(LINK)

clean:
	rm -rf $(BIN)

