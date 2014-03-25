PYTHON_FLAGS = -lpthread -ldl -lutil -lm -lpython2.7 -Xlinker -export-dynamic
SERVER_FILES = tools/Sockets/server.o tools/Sockets/utils.o tools/Sockets/python_ui.o

Route_Logistics: tools/Sockets/server.o
	g++ main.cpp $(SERVER_FILES) -o Route_Logistics -std=c++11

tools/Sockets/server.o:
	cd tools/Sockets ; make

GUI/UI.o:
	cd GUI; make

