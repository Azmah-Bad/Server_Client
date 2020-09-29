#include "client.h"
#define PORT 10000

int main(int argc, char const *argv[])
{
    char userInput[100];

    // init the addresses
    struct sockaddr_in serverAddress;

    // create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket == -1)
    {
        printf("error when creating socket");
        return 1;
    }
    else
    {
        printf("creating socket with success...\n");
    }

    memset((char *)&serverAddress, 0, sizeof(serverAddress));

    // printf("inet_aton: %d\n", inet_aton(cp, &serverAddress));
    // printf("address: %s\n", address);
    // printf("my_addr: %d\n", serverAddress.s_addr);

    // assign IP, PORT
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    serverAddress.sin_family = AF_INET;

    socklen_t addressLength = sizeof(serverAddress);

    // connect
    int connectValue = connect(clientSocket, ((struct sockaddr *)&serverAddress), addressLength);

    if (connectValue < 0)
    {
        printf("connection failed...\nconnect value: %d\n", connectValue);
        return 1;
    }
    else
    {
        printf("connected to server...\n");
    }

    // get user input
    gets(userInput);

    //write data into the socket
    int writeValue = write(clientSocket, userInput, sizeof(userInput));
    if (writeValue < 0)
    {
        printf("writing failed...\nwrite value: %d\n", writeValue);
        return 1;
    }
    else
    {
        printf("data written with success 🎉...\n");

        // read data that is comming back from server
        int readValue = read(clientSocket, userInput, sizeof(userInput));
        if (readValue < 0)
        {
            printf("reading failed...\nread value: %d\n", readValue);
            return 1;
        }
        else
        {
            printf("data received from server with success 🎉...\nDATA :");
            printf("%s", userInput); // print it
            printf("\n");
        }
    }

    return 0;
}
