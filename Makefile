OBJS := src/main.cpp src/SQL.cpp src/twitch_functions.cpp src/twitch_utility.cpp
BIN := TWITCH
LIBS := -lcurl -ljsoncpp -lsqlite3
CC = g++


install:
	@echo "Compiling files....."
	${CC} ${OBJS} -o ${BIN}  ${LIBS}

clean:
	@echo "cleaning up....."
	rm -rf ${BIN}