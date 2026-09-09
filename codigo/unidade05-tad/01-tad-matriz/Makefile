CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDLIBS = -lm

TARGET = cliente_matriz
OBJS = matriz.o cliente_matriz.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS)

matriz.o: matriz.c matriz.h
	$(CC) $(CFLAGS) -c matriz.c

cliente_matriz.o: cliente_matriz.c matriz.h
	$(CC) $(CFLAGS) -c cliente_matriz.c

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
