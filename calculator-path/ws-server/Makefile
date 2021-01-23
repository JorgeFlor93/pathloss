
CC=g++ 
CF=-Wall -g 
BUILD=build/
EXECUTOR=Executor/
CALCULATOR=Calculator/
MATRIX=MatrixCalculator/
COMMUNICATIONS=Communications/
LOSS=Pathloss/
MODEL=Pathloss/models/

main: main.cpp ${BUILD}Executor.o ${BUILD}ExecutableFactory.o  ${BUILD}Websocket.o ${BUILD}EmisorFactory.o ${BUILD}ModelFactory.o ${BUILD}SingletonPathloss.o ${BUILD}PathlossArea.o  ${BUILD}PathlossLine.o ${BUILD}fspl.o ${BUILD}hata.o \
${BUILD}Emisor.o ${BUILD}ExecutablePathloss.o ${BUILD}egli.o ${BUILD}Algorithm.o common.h json.hpp
	${CC} ${CF} main.cpp ${BUILD}Executor.o ${BUILD}ExecutableFactory.o ${BUILD}Websocket.o ${BUILD}EmisorFactory.o ${BUILD}ModelFactory.o ${BUILD}SingletonPathloss.o  ${BUILD}PathlossArea.o ${BUILD}PathlossLine.o ${BUILD}ExecutablePathloss.o \
	${BUILD}fspl.o ${BUILD}hata.o ${BUILD}egli.o ${BUILD}Emisor.o ${BUILD}Algorithm.o -L/usr/local/lib -lixwebsocket -lssl -lcrypto -lz -lpthread -o main

${BUILD}Executor.o: ${EXECUTOR}Executor.cpp ${EXECUTOR}ExecutableFactory.hpp ${EXECUTOR}Executable.hpp ${EXECUTOR}Executor.hpp 
	${CC} ${CF} -c ${EXECUTOR}Executor.cpp -o ${BUILD}Executor.o

${BUILD}ExecutableFactory.o: ${EXECUTOR}ExecutableFactory.cpp ${LOSS}ExecutablePathloss.hpp ${EXECUTOR}Executor.hpp  ${EXECUTOR}ExecutableFactory.hpp 
	${CC} ${CF} -c ${EXECUTOR}ExecutableFactory.cpp -o ${BUILD}ExecutableFactory.o

${BUILD}Websocket.o: ${COMMUNICATIONS}Websocket.cpp ${COMMUNICATIONS}Websocket.hpp 
	${CC} ${CF} -c ${COMMUNICATIONS}Websocket.cpp -o ${BUILD}Websocket.o

${BUILD}Emisor.o: ${LOSS}Emisor.cpp  ${LOSS}Emisor.hpp ${LOSS}AbsPathloss.hpp 
	${CC} ${CF} -c  ${LOSS}Emisor.cpp -o ${BUILD}Emisor.o

${BUILD}PathlossArea.o: ${LOSS}PathlossArea.cpp ${LOSS}PathlossArea.hpp ${LOSS}IPathloss.hpp 
	${CC} ${CF} -c ${LOSS}PathlossArea.cpp -o ${BUILD}PathlossArea.o

${BUILD}PathlossLine.o: ${LOSS}PathlossLine.cpp ${LOSS}PathlossLine.hpp ${LOSS}IPathloss.hpp 
	${CC} ${CF} -c ${LOSS}PathlossLine.cpp -o ${BUILD}PathlossLine.o

${BUILD}ExecutablePathloss.o: ${LOSS}ExecutablePathloss.cpp 
	${CC} ${CF} -c ${LOSS}ExecutablePathloss.cpp -o ${BUILD}ExecutablePathloss.o

${BUILD}SingletonPathloss.o: ${LOSS}SingletonPathloss.cpp  ${LOSS}SingletonPathloss.hpp
	${CC} ${CF} -c  ${LOSS}SingletonPathloss.cpp -o ${BUILD}SingletonPathloss.o

${BUILD}Algorithm.o: ${LOSS}Algorithm.cpp  ${LOSS}Algorithm.hpp ${LOSS}AbsPathloss.hpp 
	${CC} ${CF} -c  ${LOSS}Algorithm.cpp -o ${BUILD}Algorithm.o

${BUILD}ModelFactory.o: ${LOSS}ModelFactory.cpp  ${LOSS}ModelFactory.hpp
	${CC} ${CF} -c  ${LOSS}ModelFactory.cpp -o ${BUILD}ModelFactory.o

${BUILD}EmisorFactory.o: ${LOSS}EmisorFactory.cpp  ${LOSS}EmisorFactory.hpp
	${CC} ${CF} -c  ${LOSS}EmisorFactory.cpp -o ${BUILD}EmisorFactory.o

${BUILD}fspl.o: ${MODEL}fspl.cc ${MODEL}fspl.hh
	${CC} ${CF} -c ${MODEL}fspl.cc -o ${BUILD}fspl.o

${BUILD}hata.o: ${MODEL}hata.cc ${MODEL}hata.hh
	${CC} ${CF} -c ${MODEL}hata.cc -o ${BUILD}hata.o

${BUILD}egli.o: ${MODEL}egli.cc ${MODEL}egli.hh
	${CC} ${CF} -c ${MODEL}egli.cc -o ${BUILD}egli.o

