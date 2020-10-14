CFLAGS = -g -Wall -DDEBUG
LDLAGS = -g -Wall -DDEBUG

all : server client clientUDP

server.o: server.c server.h
	gcc ${CFLAGS} -c server.c  -o server.o

server: server.o
	gcc ${LDLAGS} server.o -o bin/server

client.o: client.c client.h
	gcc ${CFLAGS} -c client.c  -o client.o

client: client.o
	gcc ${LDLAGS} client.o -o bin/client

clientUDP.o: clientUDP.c client.h
	gcc ${CFLAGS} -c clientUDP.c  -o clientUDP.o

clientUDP: clientUDP.o
	gcc ${LDLAGS} clientUDP.o -o bin/client


clean: 
	\rm -rf *.o server client clientUDP