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
    int sock;
    struct sockaddr_in serv_addr;
    char msg[1024] = { 0x00, };
    int str_len = 0;

    if (argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        perror("socket()");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        perror("connect()");
   
    printf("Input message : ");
    scanf("%s", msg); 
    
    str_len = write(sock, msg, 1024);
    if (str_len == -1)
        perror("write()");
    
    memset(msg, 0, 1024);

    str_len = read(sock, msg, 1024);
    if (str_len == -1)
        perror("read()");
    
    printf("Message from server : %s\n", msg);
    close(sock);
    return 0;
}
