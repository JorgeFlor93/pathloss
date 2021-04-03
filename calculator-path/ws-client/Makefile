CC=g++ 
CF=-Wall -g 
BUILD=build2/


all: build clienthttp.cpp ${BUILD}clienthttp.o 
	${CC} ${CF} ${BUILD}clienthttp.o -L/usr/local/lib -lixwebsocket -lcrypto -lssl -lz -lpthread -o main

build:
	mkdir build2

${BUILD}clienthttp.o: clienthttp.cpp
	${CC} ${CF} -c clienthttp.cpp -o ${BUILD}clienthttp.o

PHONE: clean

clean: 
	rm -fr build2/ main
