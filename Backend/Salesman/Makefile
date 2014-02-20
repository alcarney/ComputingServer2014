sales: Salesman.o Location.o
	g++ test.cpp Salesman.o Location.o

Location.o:
	g++ -c Location.cpp

Salesman.o: Location.o
	g++ -c Salesman.cpp Location.o

clean:
	rm *.o *.out
