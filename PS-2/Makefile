all: interactive-shell

interactive-shell: interactive-shell.o
	g++ -std=c++17 interactive-shell.o -o interactive-shell

interactive-shell.o: interactive-shell.cpp
	g++ -std=c++17 -c interactive-shell.cpp -o interactive-shell.o

clean:
	rm -f interactive-shell.o interactive-shell

.PHONY: all clean run
