#include "client.h"

int main(int argc, char const *argv[])
{
    char userInput[100];

    char address[] = "127.0.0.1";
    char *cp = &address;

    // get user input
    gets(userInput);

    // create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket < 0)
    {
        printf("error when creating socket");
        return 1;
    }

    struct in_addr my_addr;
    struct sockaddr_in p_addr;
    memset((char *)&my_addr, 0, sizeof(my_addr));

    printf("inet_aton: %d\n", inet_aton(cp, &my_addr));
    printf("address: %s\n", address);
    printf("my_addr: %d\n", my_addr.s_addr);

    struct sockaddr_in serverAddress;
    memset((char *)&my_addr, 0, sizeof(my_addr));
    serverAddress.sin_port = 5000;
    serverAddress.sin_addr.s_addr = INADDR_LOOPBACK;
    serverAddress.sin_family = AF_INET;

    socklen_t socketLen = sizeof(serverAddress);

    // connect
    int connectValue = connect(clientSocket, ((struct sockaddr* ) &serverAddress), &socketLen);


    printf("connect value: %d\n", connectValue);



    return 0;
}
