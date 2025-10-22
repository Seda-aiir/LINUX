all: CopyFile

CopyFile: CopyFile.o
	g++ -std=c++17 CopyFile.o -o CopyFile

CopyFile.o: CopyFile.cpp
	g++ -std=c++17 -c CopyFile.cpp -o CopyFile.o

clean:
	rm -f CopyFile.o CopyFile

