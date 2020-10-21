out:=hw2
.PHONY: all clean

all:
	gcc -Wall  -o $(out).bin main.c util.c primes.c -lm -pthread

clean:
	rm -rf $(out).bin
