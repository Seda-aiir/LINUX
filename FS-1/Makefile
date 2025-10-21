all: main

main: ReadFromFile.o
	g++ -std=c++17 ReadFromFile.o -o main

ReadFromFile.o: ReadFromFile.cpp
	g++ -std=c++17 -c ReadFromFile.cpp -o ReadFromFile.o

clean:
	rm -f ReadFromFile.o main

.PHONY: all clean

