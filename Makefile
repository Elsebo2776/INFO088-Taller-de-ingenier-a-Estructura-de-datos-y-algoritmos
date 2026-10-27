CC=g++
CFLAGS=-Wall -std=c++17
BINS=sol1 sol2
all: clean sol1 sol2

sol1:
	$(CC) $(CFLAGS) -o sol1 solucion1.cpp
	
sol2:
	$(CC) $(CFLAGS) -o sol2 solucion2.cpp
	
main:
	$(CC) $(CFLAGS) -o main main.cpp
	
clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)
	
