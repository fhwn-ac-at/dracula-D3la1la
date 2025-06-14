CC = clang
CFLAGS = -Wall -Wextra -Werror -Iinclude
SRC = src/main.c src/board.c src/game.c src/stats.c
OBJ = $(SRC:.c=.o)
TARGET = snl

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
