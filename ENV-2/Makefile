all: main

main: main.o MyComplex.o mergeSort.o
	g++ -std=c++17 main.o MyComplex.o mergeSort.o -o main

main.o: Code/main.cpp myIncludes/MyComplex.h myIncludes/mergeSort.h
	g++ -std=c++17 -c Code/main.cpp -I./myIncludes -o main.o

MyComplex.o: Code/MyComplex.cpp myIncludes/MyComplex.h
	g++ -std=c++17 -c Code/MyComplex.cpp -I./myIncludes -o MyComplex.o

mergeSort.o: Code/mergeSort.cpp myIncludes/mergeSort.h myIncludes/MyComplex.h
	g++ -std=c++17 -c Code/mergeSort.cpp -I./myIncludes -o mergeSort.o

run: main
	./main

clean:
	rm -f *.o main

.PHONY: all clean run

