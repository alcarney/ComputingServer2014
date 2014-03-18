test: utils.o
	g++ -o test server.c utils.o

utils.o:
	gcc -c server_utils.c -o utils.o

clean:
	rm test
	rm *.o
