
CC=g++ 
CF=-Wall -g 
BUILD=build/
EXECUTOR=Executor/
CALCULATOR=Calculator/
MATRIX=MatrixCalculator/
COMMUNICATIONS=Communications/
LOSS=Pathloss/

main: main.cpp ${BUILD}Executor.o ${BUILD}ExecutableFactory.o  ${BUILD}Websocket.o json.hpp ${EXECUTOR}Executor.hpp \
${BUILD}distance.o ${BUILD}coordinate.o ${BUILD}area.o ${BUILD}Pathloss.o ${BUILD}ExecutablePathloss.o
	${CC} ${CF} main.cpp ${BUILD}Executor.o ${BUILD}ExecutableFactory.o ${BUILD}Websocket.o ${BUILD}Pathloss.o ${BUILD}ExecutablePathloss.o \
	${BUILD}coordinate.o ${BUILD}area.o ${BUILD}distance.o -L/usr/local/lib -lixwebsocket -lssl -lcrypto -lz -lpthread -o main

${BUILD}Executor.o: ${EXECUTOR}Executor.cpp ${EXECUTOR}ExecutableFactory.hpp ${EXECUTOR}Executable.hpp ${EXECUTOR}Executor.hpp json.hpp
	${CC} ${CF} -c ${EXECUTOR}Executor.cpp -o ${BUILD}Executor.o

${BUILD}ExecutableFactory.o: ${EXECUTOR}ExecutableFactory.cpp ${LOSS}ExecutablePathloss.hpp ${EXECUTOR}Executor.hpp ${CALCULATOR}Calculator.hpp ${EXECUTOR}ExecutableFactory.hpp ${LOSS}Pathloss.hpp json.hpp
	${CC} ${CF} -c ${EXECUTOR}ExecutableFactory.cpp -o ${BUILD}ExecutableFactory.o

${BUILD}Websocket.o: ${COMMUNICATIONS}Websocket.cpp ${COMMUNICATIONS}Websocket.hpp json.hpp
	${CC} ${CF} -c ${COMMUNICATIONS}Websocket.cpp -o ${BUILD}Websocket.o

${BUILD}distance.o: ${LOSS}distance.cc  ${LOSS}distance.hh ${LOSS}coordinate.hpp
	${CC} ${CF} -c  ${LOSS}distance.cc -o ${BUILD}distance.o
	
${BUILD}coordinate.o: ${LOSS}coordinate.cpp  ${LOSS}coordinate.hpp
	${CC} ${CF} -c  ${LOSS}coordinate.cpp -o ${BUILD}coordinate.o

${BUILD}area.o: ${LOSS}area.cpp  ${LOSS}area.hpp ${LOSS}distance.hh
	${CC} ${CF} -c  ${LOSS}area.cpp -o ${BUILD}area.o

${BUILD}Pathloss.o: ${LOSS}Pathloss.cpp ${LOSS}Pathloss.hpp json.hpp ${LOSS}area.hpp 
	${CC} ${CF} -c ${LOSS}Pathloss.cpp -o ${BUILD}Pathloss.o

${BUILD}ExecutablePathloss.o: ${LOSS}ExecutablePathloss.cpp ${EXECUTOR}Executor.hpp ${LOSS}Pathloss.hpp ${LOSS}ExecutablePathloss.hpp json.hpp
	${CC} ${CF} -c ${LOSS}ExecutablePathloss.cpp -o ${BUILD}ExecutablePathloss.o





