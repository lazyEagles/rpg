
VPATH = ../rpg ../src
CFLAGS = -g --std=c99

all: mpg rpg body_gen

body_gen: body_gen.o position.o
	$(CC) $(CFLAGS) -I.. $^ -o $@ -lm

mpg: mpg.o position.o
	$(CC) $(CFLAGS) -I.. $^ -o $@ -lm

rpg: test.o position.o
	$(CC) $(CFLAGS) -I.. $^ -o $@ -lm

%.o: %.c position.h
	$(CC) $(CFLAGS) -I.. -c $< -o $@

position.o: position.c position.h
	$(CC) $(CFLAGS) -I.. -c $< -o $@

.PHONY: clean
clean:
	rm *.o mpg rpg body_gen

