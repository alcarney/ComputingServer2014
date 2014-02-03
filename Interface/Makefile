PYTHON_FLAGS = -lpthread -ldl -lutil -lm -lpython2.7 -Xlinker -export-dynamic

PythonInterpreter.o:
	g++ -c PyI.cpp  $(PYTHON_FLAGS)

clean:
	rm *.o
	rm postage 

