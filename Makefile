CC=gcc
LINK=-Wall `pkg-config --cflags --libs emotion elementary`
BIN=./bin/entasy
OUT= -o $(BIN)

all:
	$(CC) ./src/entasy_main.c $(OUT) $(LINK)

clean:
	rm -rf $(BIN)

