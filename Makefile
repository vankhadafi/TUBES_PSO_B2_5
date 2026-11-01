CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c99
SRC = src/main.c src/prompt.c src/navigation.c src/file_utils.c src/executor.c
OBJ = $(SRC:.c=.o)
TARGET = myshell

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
