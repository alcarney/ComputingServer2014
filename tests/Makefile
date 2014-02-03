PYTHON_FLAGS = -lpthread -ldl -lutil -lm -lpython2.7 -Xlinker -export-dynamic

test: test.o
	g++ -o postage test.o $(PYTHON_FLAGS)

test.o:
	g++ -c test.cpp $(PYTHON_FLAGS)

example: example.o
	g++ -o example example.o $(PYTHON_FLAGS)

example.o:
	g++ -c example.cpp $(PYTHON_FLAGS)


clean:
	rm *.o
	rm postage 

