/***** A.1 * File Include                       *******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <error.h>
/***** B.1 * Definition of New Constants        *******************************/
/***** C.1 * Declaration of Variables(LOCAL)    *******************************/
/***** C.2 * Declaration of Variables(EXTERN)   *******************************/
/***** D.1 * Definition of Functions(LOCAL)     *******************************/
/***** D.2 * Definition of Functions(EXTERN)    *******************************/

int main(int argc, char* argv[])
{
    int serv_sock;
    int clnt_sock;
    int data_len = 0;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = 0;

    char msg[1024] = { 0x00, };

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        perror("socket()");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        perror("bind() : ");
    
    if (listen(serv_sock, 5) == -1)
        perror("listen() : ");

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if (clnt_sock == -1)
        perror("accept() : ");

    data_len = read(clnt_sock, msg, 1024);
    if (data_len == -1) {
 	perror("read() : ");   
    }

    printf("Echo message : %s\n", msg);
    
    write(clnt_sock, msg, 1024);
    
    close(clnt_sock);
    close(serv_sock);
    
    return 0;
}
