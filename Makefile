CC = gcc
CFLAGS = -Iinclude -Wall -g
SRC = src/qSim.c src/event.c src/queue.c src/teller.c src/customer.c
OBJ = $(SRC:.c=.o)
TARGET = bin/qSim

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
