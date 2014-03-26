server: utils.o python_ui.o
	gcc -c server.c utils.o python_ui.o -o server.o

utils.o:
	gcc -c server_utils.c -o utils.o

python_ui.o:
	gcc -c python_ui.c -o python_ui.o

clean:
	rm *.o
