PYTHON_FLAGS = -lpthread -ldl -lutil -lm -lpython2.7 -Xlinker -export-dynamic

PyFunc.o:
	g++  PyFunc.cpp $(PYTHON_FLAGS)

Functions.o: PyFunc.o
	g++ -c  PyFunc.o Functions.cpp $(PYTHON_FLAGS)

clean:
	rm *.o

