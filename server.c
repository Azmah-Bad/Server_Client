#include "server.h"

int main(int argc, char const *argv[])
{
    //create socket
    int s = socket(AF_INET, SOCK_STREAM, 0);

    // verify the socket creation worked
    if (s < 0)
    {
        printf("error when creating socket");
        return 1;
    }

    int reuse = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    struct sockaddr_in my_addr;
    memset((char *)&my_addr, 0, sizeof(my_addr));
    my_addr.sin_port = htons(5000);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_addr.sin_family = AF_INET;
    struct sockaddr_in p_addr;

    //p_addr = &my_addr;

    //bind
    int bindValue = bind(s, ((struct sockaddr* ) &my_addr), sizeof(my_addr));



    
    //listen
    int listenValue = listen(s,5);

    socklen_t socketLen = sizeof(p_addr);


    //accept
    while (1)
    {   
        if(listenValue < 0){
            return 1;
        }
        printf("listnening on port 5000\n");
        int acceptValue = accept(s, (struct sockaddr *) p_addr, &socketLen);
        printf("valeur de accept %d \n", acceptValue);
    }

    return 0;
}
