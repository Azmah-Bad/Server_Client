#include "server.h"
#define PORT 5000

int main(int argc, char const *argv[])
{
    // initialize variables
    int mSocket, mConnection, clientLength;
    struct sockaddr_in serverAddress, clientAddress;

    //create socket
    mSocket = socket(AF_INET, SOCK_STREAM, 0);

    // verify the socket creation worked
    if (mSocket < 0)
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

    //bind
    int bindValue = bind(mSocket, ((struct sockaddr *)&serverAddress), sizeof(serverAddress));

    if (bindValue != 0)
    {
        printf("socket bind failed...\n");
        return 1;
    }
    else
    {
        printf("socket binded successfully...\n");
    }

    //listen
    if ((listen(mSocket, 5)) != 0)
    {
        printf("Listen failed...\n");
        return 1;
    }
    else
        printf("Server listening..\n");

    clientLength = sizeof(clientAddress);

    //accept
    while (1)
    {
        printf("listnening on port 5000...\n");
        mConnection = accept(mSocket, (struct sockaddr *)&clientAddress, &clientLength);
        printf("connection accepted...\n");

        // TODO get data from socket 
        // TODO print it
        // TODO send it back 
    }

    return 0;
}
