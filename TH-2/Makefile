all: demo-application

demo-application: demo-application.o lib_sch.so
	g++ -std=c++11 demo-application.o -o demo-application -L. -l_sch  -Wl,-rpath,. -lpthread

demo-application.o: demo-application.cpp
	g++ -std=c++11 -c demo-application.cpp -o demo-application.o

clean:
	rm -f *.o *.so *.out

lib_sch.so: lib_sch.cpp
	g++ -std=c++11 -fPIC -c lib_sch.cpp -o lib_sch.o
	g++ -std=c++11 -shared -o lib_sch.so lib_sch.o -lpthread
