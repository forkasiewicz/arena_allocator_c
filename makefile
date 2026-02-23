CC = clang
TARGET = main
SRC = main.c arena.c

CFLAGS_RELEASE = -std=c17 -O2 -Wall -Wextra -Wpedantic
CFLAGS_DEBUG = -std=c17 -g3 -O0 -Wall -Wextra -Wpedantic -fsanitize=address,undefined -fno-omit-frame-pointer

.PHONY: all debug run run-debug clean

all:
	$(CC) $(CFLAGS_RELEASE) $(SRC) -o $(TARGET)

debug:
	$(CC) $(CFLAGS_DEBUG) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

run-debug: debug
	./$(TARGET)

clean:
	rm -f $(TARGET)
