CC=gcc
LINK=-Wall `pkg-config --cflags --libs emotion elementary`
BIN=./bin/entasy
OUT= -o $(BIN)

all:
	$(CC) ./src/entasy_cb.c ./src/entasy_main.c $(OUT) $(LINK)

clean:
	rm -rf $(BIN)

