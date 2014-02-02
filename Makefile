PYTHON_FLAGS = -lpthread -ldl -lutil -lm -lpython2.7 -Xlinker -export-dynamic

postage: test.o
	g++ -o postage test.o $(PYTHON_FLAGS)

test.o:
	g++ -c test.cpp $(PYTHON_FLAGS)

clean:
	rm *.o
	rm postage 

