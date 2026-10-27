CC=g++
CFLAGS=-Wall -std=c++17
BINS=main
all: clean main

	
main:
	$(CC) $(CFLAGS) -o main main.cpp
	
clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)
	
