
CC=g++ 
CF=-Wall -g 
BUILD=build/
EXECUTOR=Executor/
CALCULATOR=Calculator/
MATRIX=MatrixCalculator/
COMMUNICATIONS=Communications/
LOSS=Pathloss/
MODEL=Pathloss/models/

main: main.cpp ${BUILD}Executor.o ${BUILD}ExecutableFactory.o  ${BUILD}Websocket.o ${BUILD}Antenna.o ${BUILD}Pathloss.o  ${BUILD}fspl.o ${BUILD}hata.o \
${BUILD}distance.o ${BUILD}ExecutablePathloss.o
	${CC} ${CF} main.cpp ${BUILD}Executor.o ${BUILD}ExecutableFactory.o ${BUILD}Websocket.o ${BUILD}Antenna.o  ${BUILD}Pathloss.o ${BUILD}ExecutablePathloss.o \
	${BUILD}fspl.o ${BUILD}hata.o ${BUILD}distance.o  -L/usr/local/lib -lixwebsocket -lssl -lcrypto -lz -lpthread -o main

${BUILD}Executor.o: ${EXECUTOR}Executor.cpp ${EXECUTOR}ExecutableFactory.hpp ${EXECUTOR}Executable.hpp ${EXECUTOR}Executor.hpp json.hpp ${LOSS}common.h
	${CC} ${CF} -c ${EXECUTOR}Executor.cpp -o ${BUILD}Executor.o

${BUILD}ExecutableFactory.o: ${EXECUTOR}ExecutableFactory.cpp ${LOSS}ExecutablePathloss.hpp ${EXECUTOR}Executor.hpp  ${EXECUTOR}ExecutableFactory.hpp ${LOSS}Pathloss.hpp json.hpp ${LOSS}common.h
	${CC} ${CF} -c ${EXECUTOR}ExecutableFactory.cpp -o ${BUILD}ExecutableFactory.o

${BUILD}Websocket.o: ${COMMUNICATIONS}Websocket.cpp ${COMMUNICATIONS}Websocket.hpp json.hpp
	${CC} ${CF} -c ${COMMUNICATIONS}Websocket.cpp -o ${BUILD}Websocket.o

${BUILD}distance.o: ${LOSS}distance.cc  ${LOSS}distance.hh ${LOSS}common.h
	${CC} ${CF} -c  ${LOSS}distance.cc -o ${BUILD}distance.o

${BUILD}Pathloss.o: ${LOSS}Pathloss.cpp ${LOSS}Pathloss.hpp ${LOSS}common.h
	${CC} ${CF} -c ${LOSS}Pathloss.cpp -o ${BUILD}Pathloss.o

${BUILD}ExecutablePathloss.o: ${LOSS}ExecutablePathloss.cpp 
	${CC} ${CF} -c ${LOSS}ExecutablePathloss.cpp -o ${BUILD}ExecutablePathloss.o

${BUILD}Antenna.o: ${LOSS}Antenna.cpp  ${LOSS}Antenna.hpp ${LOSS}common.h
	${CC} ${CF} -c  ${LOSS}Antenna.cpp -o ${BUILD}Antenna.o

${BUILD}fspl.o: ${MODEL}fspl.cc ${MODEL}fspl.hh
	${CC} ${CF} -c ${MODEL}fspl.cc -o ${BUILD}fspl.o

${BUILD}hata.o: ${MODEL}hata.cc ${MODEL}hata.hh
	${CC} ${CF} -c ${MODEL}hata.cc -o ${BUILD}hata.o

