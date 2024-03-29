
CC=g++ 
CF=-Wall -g -rdynamic
BUILD=build/
EXECUTOR=Executor/
CALCULATOR=Calculator/
MATRIX=MatrixCalculator/
COMMUNICATIONS=Communications/
LOSS=Pathloss/
MODEL=Pathloss/models/

main: ${BUILD}main
	cp ${BUILD}main ./main

${BUILD}main: main.cpp ${BUILD}Executor.o ${BUILD}ExecutableFactory.o  ${BUILD}RandomIdClient.o ${BUILD}Websocket.o ${BUILD}EmisorFactory.o ${BUILD}HttpGetAntenna.o ${BUILD}HttpGetArea.o ${BUILD}HttpGetAbs.o ${BUILD}ModelFactory.o ${BUILD}SingletonPathloss.o ${BUILD}PathlossArea.o ${BUILD}PathlossLine.o ${BUILD}PathlossPoint.o ${BUILD}sui.o ${BUILD}fspl.o ${BUILD}ecc33.o ${BUILD}cost.o ${BUILD}hata.o ${BUILD}itwom.o ${BUILD}soil.o ${BUILD}Emisor.o ${BUILD}ExecutablePathloss.o ${BUILD}ericsson.o ${BUILD}egli.o ${BUILD}pel.o ${BUILD}Model.o common.h json.hpp
	${CC} ${CF} main.cpp ${BUILD}Executor.o ${BUILD}ExecutableFactory.o ${BUILD}RandomIdClient.o ${BUILD}Websocket.o ${BUILD}EmisorFactory.o ${BUILD}ModelFactory.o ${BUILD}SingletonPathloss.o ${BUILD}HttpGetAbs.o ${BUILD}PathlossArea.o ${BUILD}PathlossLine.o ${BUILD}PathlossPoint.o ${BUILD}ExecutablePathloss.o \
	${BUILD}fspl.o ${BUILD}hata.o ${BUILD}itwom.o ${BUILD}egli.o ${BUILD}pel.o ${BUILD}cost.o ${BUILD}ecc33.o ${BUILD}soil.o ${BUILD}sui.o ${BUILD}ericsson.o ${BUILD}Emisor.o ${BUILD}Model.o ${BUILD}HttpGetAntenna.o ${BUILD}HttpGetArea.o  -L/usr/local/lib -lixwebsocket -lssl -lcrypto -lz -lpthread -o ${BUILD}main

${BUILD}Executor.o: ${EXECUTOR}Executor.cpp ${EXECUTOR}ExecutableFactory.hpp ${EXECUTOR}Executable.hpp ${EXECUTOR}Executor.hpp 
	${CC} ${CF} -c ${EXECUTOR}Executor.cpp -o ${BUILD}Executor.o

${BUILD}ExecutableFactory.o: ${EXECUTOR}ExecutableFactory.cpp ${LOSS}ExecutablePathloss.hpp ${EXECUTOR}Executor.hpp  ${EXECUTOR}ExecutableFactory.hpp 
	${CC} ${CF} -c ${EXECUTOR}ExecutableFactory.cpp -o ${BUILD}ExecutableFactory.o

${BUILD}Websocket.o: ${COMMUNICATIONS}Websocket.cpp ${COMMUNICATIONS}Websocket.hpp 
	${CC} ${CF} -c ${COMMUNICATIONS}Websocket.cpp -o ${BUILD}Websocket.o

${BUILD}RandomIdClient.o: RandomIdClient.cpp  RandomIdClient.hpp
	${CC} ${CF} -c  RandomIdClient.cpp -o ${BUILD}RandomIdClient.o

${BUILD}Emisor.o: ${COMMUNICATIONS}Emisor.cpp  ${COMMUNICATIONS}Emisor.hpp ${LOSS}PathlossAbs.hpp 
	${CC} ${CF} -c  ${COMMUNICATIONS}Emisor.cpp -o ${BUILD}Emisor.o

${BUILD}HttpGetArea.o: ${COMMUNICATIONS}HttpGetArea.cpp  ${COMMUNICATIONS}HttpGetArea.hpp ${COMMUNICATIONS}HttpGet.hpp 
	${CC} ${CF} -c  ${COMMUNICATIONS}HttpGetArea.cpp -o ${BUILD}HttpGetArea.o

${BUILD}HttpGetAbs.o: ${COMMUNICATIONS}HttpGetAbs.cpp  ${COMMUNICATIONS}HttpGetAbs.hpp ${COMMUNICATIONS}HttpGet.hpp 
	${CC} ${CF} -c  ${COMMUNICATIONS}HttpGetAbs.cpp -o ${BUILD}HttpGetAbs.o

${BUILD}HttpGetAntenna.o: ${COMMUNICATIONS}HttpGetAntenna.cpp  ${COMMUNICATIONS}HttpGetAntenna.hpp ${COMMUNICATIONS}HttpGet.hpp 
	${CC} ${CF} -c  ${COMMUNICATIONS}HttpGetAntenna.cpp -o ${BUILD}HttpGetAntenna.o

${BUILD}PathlossArea.o: ${LOSS}PathlossArea.cpp ${LOSS}PathlossArea.hpp ${LOSS}PathlossInterface.hpp 
	${CC} ${CF} -c ${LOSS}PathlossArea.cpp -o ${BUILD}PathlossArea.o

${BUILD}PathlossLine.o: ${LOSS}PathlossLine.cpp ${LOSS}PathlossLine.hpp ${LOSS}PathlossInterface.hpp 
	${CC} ${CF} -c ${LOSS}PathlossLine.cpp -o ${BUILD}PathlossLine.o

${BUILD}PathlossPoint.o: ${LOSS}PathlossPoint.cpp ${LOSS}PathlossPoint.hpp ${LOSS}PathlossInterface.hpp 
	${CC} ${CF} -c ${LOSS}PathlossPoint.cpp -o ${BUILD}PathlossPoint.o

${BUILD}ExecutablePathloss.o: ${LOSS}ExecutablePathloss.cpp 
	${CC} ${CF} -c ${LOSS}ExecutablePathloss.cpp -o ${BUILD}ExecutablePathloss.o

${BUILD}SingletonPathloss.o: ${LOSS}SingletonPathloss.cpp  ${LOSS}SingletonPathloss.hpp
	${CC} ${CF} -c  ${LOSS}SingletonPathloss.cpp -o ${BUILD}SingletonPathloss.o

${BUILD}Model.o: ${LOSS}Model.cpp  ${LOSS}Model.hpp ${LOSS}PathlossAbs.hpp 
	${CC} ${CF} -c  ${LOSS}Model.cpp -o ${BUILD}Model.o

${BUILD}ModelFactory.o: ${LOSS}ModelFactory.cpp  ${LOSS}ModelFactory.hpp
	${CC} ${CF} -c  ${LOSS}ModelFactory.cpp -o ${BUILD}ModelFactory.o

${BUILD}EmisorFactory.o: ${COMMUNICATIONS}EmisorFactory.cpp  ${COMMUNICATIONS}EmisorFactory.hpp
	${CC} ${CF} -c  ${COMMUNICATIONS}EmisorFactory.cpp -o ${BUILD}EmisorFactory.o

${BUILD}fspl.o: ${MODEL}fspl.cc ${MODEL}fspl.hh
	${CC} ${CF} -c ${MODEL}fspl.cc -o ${BUILD}fspl.o

${BUILD}hata.o: ${MODEL}hata.cc ${MODEL}hata.hh
	${CC} ${CF} -c ${MODEL}hata.cc -o ${BUILD}hata.o

${BUILD}egli.o: ${MODEL}egli.cc ${MODEL}egli.hh
	${CC} ${CF} -c ${MODEL}egli.cc -o ${BUILD}egli.o

${BUILD}pel.o: ${MODEL}pel.cc ${MODEL}pel.hh
	${CC} ${CF} -c ${MODEL}pel.cc -o ${BUILD}pel.o

${BUILD}cost.o: ${MODEL}cost.cc ${MODEL}cost.hh
	${CC} ${CF} -c ${MODEL}cost.cc -o ${BUILD}cost.o

${BUILD}ecc33.o: ${MODEL}ecc33.cc ${MODEL}ecc33.hh
	${CC} ${CF} -c ${MODEL}ecc33.cc -o ${BUILD}ecc33.o

${BUILD}soil.o: ${MODEL}soil.cc ${MODEL}soil.hh
	${CC} ${CF} -c ${MODEL}soil.cc -o ${BUILD}soil.o

${BUILD}sui.o: ${MODEL}sui.cc ${MODEL}sui.hh
	${CC} ${CF} -c ${MODEL}sui.cc -o ${BUILD}sui.o	

${BUILD}ericsson.o: ${MODEL}ericsson.cc ${MODEL}ericsson.hh
	${CC} ${CF} -c ${MODEL}ericsson.cc -o ${BUILD}ericsson.o

${BUILD}itwom.o: ${MODEL}itwom3.0.cc ${MODEL}itwom3.0.hh
	${CC} ${CF} -c ${MODEL}itwom3.0.cc -o ${BUILD}itwom.o