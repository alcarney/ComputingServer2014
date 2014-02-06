PYTHON_FLAGS = -lpthread -ldl -lutil -lm -lpython2.7 -Xlinker -export-dynamic

test: PyFunc.o
	g++ -o test test.cpp PyFunc.o $(PYTHON_FLAGS)


PyFunc.o:
	g++ -c PyFunc.cpp $(PYTHON_FLAGS)

clean:
	rm *.o

