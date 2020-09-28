CFLAGS = -g -Wall -DDEBUG
LDLAGS = -g -Wall -DDEBUG

all : server client

server.o: server.c server.h
	gcc ${CFLAGS} -c server.c  -o server.o

server: server.o
	gcc ${LDLAGS} server.o -o server

client.o: client.c client.h
	gcc ${CFLAGS} -c client.c  -o client.o

client: client.o
	gcc ${LDLAGS} client.o -o client

clean: 
	\rm -rf *.o server client