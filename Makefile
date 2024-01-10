CC = gcc
CFLAGS = -O3 -pedantic -std=c99 -Wall -Wextra
LIBM = -lm

all: \
	emulate \
	intcode \
	day02a day02b \
	day07a day07b \
	day11a day11b \
	day12a day12b \
	day13a day13b \
	day14a day14b \
	day15a day15b \
	day16a day16b \
	day17a day17b \
	day18a day18b \
	day19a day19b \
	day20a day20b \
	day21a \
	day22a day22b \
	day24a day24b \
	day25z

emulator: lib/emulator.h lib/emulator.c
	$(CC) $(CFLAGS) -c lib/emulator.c -o emulator.o

parser: lib/parser.h lib/parser.c
	$(CC) $(CFLAGS) -c lib/parser.c -o parser.o

emulate: tools/emulate.c emulator parser
	$(CC) $(CFLAGS) $< -o emulate.o emulator.o parser.o

intcode: tools/intcode.c emulator parser
	$(CC) $(CFLAGS) $< -o intcode.o emulator.o parser.o -Wno-unused-parameter

permutation_iterator: lib/permutation_iterator.h lib/permutation_iterator.c
	$(CC) $(CFLAGS) -c lib/permutation_iterator.c -o permutation_iterator.o

qdbmp: include/qdbmp.h include/qdbmp.c -Wno-type-limits
	$(CC) $(CFLAGS) -c include/qdbmp.c -o qdbmp.o

bitmap: lib/bitmap.h lib/bitmap.c qdbmp
	$(CC) $(CFLAGS) -c lib/bitmap.c -o bitmap.o

day02a: src/day02a.c emulator parser
	$(CC) $(CFLAGS) $< -o $@.o emulator.o parser.o
	
day02b: src/day02b.c emulator parser
	$(CC) $(CFLAGS) $< -o $@.o emulator.o parser.o
	
day07a: src/day07a.c emulator parser permutation_iterator
	$(CC) $(CFLAGS) $< -o $@.o emulator.o parser.o permutation_iterator.o
	
day07b: src/day07b.c emulator parser permutation_iterator
	$(CC) $(CFLAGS) $< -o $@.o emulator.o parser.o permutation_iterator.o
	
day11a: src/day11a.c emulator parser
	$(CC) $(CFLAGS) $< -o $@.o emulator.o parser.o
	
day11b: src/day11b.c emulator parser bitmap
	$(CC) $(CFLAGS) $< -o $@.o emulator.o parser.o qdbmp.o bitmap.o
	
day12a: src/day12a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day12b: src/day12b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day13a: src/day13a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day13b: src/day13b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day14a: src/day14a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day14b: src/day14b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day15a: src/day15a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day15b: src/day15b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day16a: src/day16a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day16b: src/day16b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day17a: src/day17a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day17b: src/day17b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day18a: src/day18a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day18b: src/day18b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day19a: src/day19a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day19b: src/day19b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day20a: src/day20a.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day20b: src/day20b.c
	$(CC) $(CFLAGS) $< -o $@.o
	
day21a: src/day21a.c
	$(CC) $(CFLAGS) $< -o $@.o

day22a: src/day22a.c
	$(CC) $(CFLAGS) $< -o $@.o

day22b: src/day22b.c
	$(CC) $(CFLAGS) $< -o $@.o

day24a: src/day24a.c
	$(CC) $(CFLAGS) $< -o $@.o

day24b: src/day24b.c
	$(CC) $(CFLAGS) $< -o $@.o

day25z: src/day25z.c
	$(CC) $(CFLAGS) $< -o $@.o

clean:
	rm -rf *.o
