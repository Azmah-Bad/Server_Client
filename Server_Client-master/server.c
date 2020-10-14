#include "server.h"

int main(int argc, char const *argv[])
{

    if (argc != 3)
    {
        printf("Error syntax : ./server <port_server> <port_server_UDP>");
        return (1);
    }

    int PORT = atoi(argv[1]);
    int PORT_UDP = atoi(argv[2]); 
    // initialize variables
    int mSocket, mConnection, clientLength;
    struct sockaddr_in serverAddress,serverUDPAddress, clientAddress;

    int mSocketUDP,
        mConnectionUDP, clientLengthUDP;

    //create sockets
    mSocket = socket(AF_INET, SOCK_STREAM, 0);
    mSocketUDP = socket(AF_INET, SOCK_DGRAM, 0);

    // verify the socket creation worked
    if (mSocket < 0 || mSocketUDP < 0)
    {
        printf("error when creating socket...\n");
        return 1;
    }
    else
        printf("socket created with success...\n");

    // makes the port reuseable
    int reuse = 1;
    setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    // set socketAddress random values to 0
    memset((char *)&serverAddress, 0, sizeof(serverAddress));
    // assign IP, PORT
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_family = AF_INET;

    serverUDPAddress.sin_port = htons(PORT_UDP);
    serverUDPAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverUDPAddress.sin_family = PF_INET; 

    //bind
    int bindValue = bind(mSocket, ((struct sockaddr *)&serverAddress), sizeof(serverAddress));
    int bindUDPValue = bind(mSocketUDP, ((struct sockaddr *)&serverAddress), sizeof(serverAddress));

    if (bindValue != 0 || bindUDPValue != 0)
    {
        printf("socket bind failed...\n");
        return 1;
    }
    else
    {
        printf("socket binded successfully...\n");
    }

    //listen
    if ((listen(mSocket, 5)) != 0 && (listen(mSocketUDP, 5)) != 0  )
    {
        printf("Listen failed...\n");
        return 1;
    }
    else
        printf("Server listening..\n");

    clientLength = sizeof(clientAddress);
    
    fd_set readfds;
    FD_ZERO(&readfds); 
    int maxfdp = mSocketUDP+1;
    //accept
    while (1)
    {        
        printf("listening to port %d and %d\n ",PORT,PORT_UDP);
        printf("Waiting for clients\n");

            
        FD_SET(mSocket,&readfds);
        FD_SET(mSocketUDP,&readfds);
       
        select(maxfdp, &readfds, NULL,NULL,NULL);

        if (FD_ISSET(mSocket, &readfds))
        {
            printf("TCP connection achieved ...\n");
            mConnection = accept(mSocket, (struct sockaddr *)&clientAddress, &clientLength);
            printf("connection accepted from %d port %d 👋\n", htonl(clientAddress.sin_addr.s_addr), htons(clientAddress.sin_port));

            int pid = fork();

            if (pid == 0) // fork to concurrently handle requests 
            {
                // if fork == 0 child process running while parent handles request 
                char userInput[100];

                // get data from socket
                int readValue = read(mConnection, userInput, sizeof(userInput));
                if (readValue < 0)
                {
                    printf("reading failed...\nread value: %d\n", readValue);
                    return 1;
                }
                else
                {
                    printf("data read with success 🎉...\nDATA :");
                    printf("%s", userInput); // print it
                    printf("\n");

                    // write data back to client
                    int writeValue = write(mConnection, userInput, sizeof(userInput));
                    if (writeValue < 0)
                    {
                        printf("writing failed...\nwrite value: %d\n", writeValue);
                        return 1;
                    }
                    else
                    {
                        printf("data written back to client with success 🎉...\n");
                    }
                }
                printf("killing child process 😭\n");
                exit(0);
            }
            else
            {
                printf("child process running pid :%d...",pid);
                close(mConnection);
            }
        } 
        
        if (FD_ISSET(mSocketUDP, &readfds))
        {   
            printf("UDP connection achieved ...\n");
            mConnection = accept(mSocket, (struct sockaddr *)&clientAddress, &clientLength);
            printf("connection accepted from %d port %d 👋\n", htonl(clientAddress.sin_addr.s_addr), htons(clientAddress.sin_port));
            char userInput[100];

            int readValue = read(mConnection, userInput, sizeof(userInput));
            if (readValue < 0)
            {
                printf("reading failed...\nread value: %d\n", readValue);
                return 1;
            }
            else
            {
                printf("data read with success 🎉...\nDATA :");
                printf("%s", userInput); // print it
                printf("\n");
            }
        
        }
       
        
    }
    return 0;
}
