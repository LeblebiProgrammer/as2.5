CC = gcc
CFLAGS = -g -Wall

all: my_ps

my_ps: my_ps.c
	$(CC) $(CFLAGS) -o my_ps my_ps.c


clean:
	rm -f my_ps.o my_ps
