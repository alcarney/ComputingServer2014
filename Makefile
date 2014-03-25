PYTHON_FLAGS = -lpthread -ldl -lutil -lm -lpython2.7 -Xlinker -export-dynamic

Route_Logistics: tools/Sockets/server.o
	g++ main.cpp tools/Sockets/server.o  -o Route_Logistics -std=c++11

tools/Sockets/server.o:
	cd tools/Sockets ; make

GUI/UI.o:
	cd GUI; make

