PYTHON_FLAGS = -lpthread -ldl -lutil -lm -lpython2.7 -Xlinker -export-dynamic

Route_Logistics: GUI/UI.o
	g++ main.cpp GUI/UI.o -o Route_Logistics $(PYTHON_FLAGS) -std=c++11

GUI/UI.o:
	cd GUI; make

