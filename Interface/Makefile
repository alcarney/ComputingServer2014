PYTHON_FLAGS = -lpthread -ldl -lutil -lm -lpython2.7 -Xlinker -export-dynamic

PyI.o:
	g++ -c PyI.cpp  $(PYTHON_FLAGS)

clean:
	rm *.o
	rm postage 

