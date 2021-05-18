CC=g++ 
CF=-Wall -g 


all: clienthttp.cpp clienthttp.o 
	${CC} ${CF} clienthttp.o -L/usr/local/lib -lixwebsocket -lcrypto -lssl -lz -lpthread -o main

clienthttp.o: clienthttp.cpp
	${CC} ${CF} -c clienthttp.cpp -o clienthttp.o

PHONE: clean

clean: 
	rm -f main clienthttp.o
