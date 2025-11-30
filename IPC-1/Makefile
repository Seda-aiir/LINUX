all: signal-echo

signal-echo: signal-echo.o
	g++ -std=c++11 signal-echo.o -o signal-echo

signal-echo.o: signal-echo.cpp
	g++ -std=c++11 -c signal-echo.cpp -o signal-echo.o

clean:
	rm -f signal-echo.o signal-echo
