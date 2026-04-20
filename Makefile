CC = gcc
CFLAGS = -Wall -Iinclude

SRCS = main.c $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

TARGET = terminal

$(TARGET): $(OBJS)
	rm -f terminal
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	rm -f *.o src/*.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
