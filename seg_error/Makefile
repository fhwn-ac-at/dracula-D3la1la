# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -Werror -Iinclude

# Source files and object files
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

# Output executable name
TARGET = snakes_and_ladders

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
