// 필요한 헤더 파일들을 포함시킵니다.
#include <stdio.h>      // 표준 입출력 함수를 위한 헤더 파일
#include <stdlib.h>     // exit 함수 등을 위한 헤더 파일
#include <string.h>     // 문자열 처리 함수를 위한 헤더 파일
#include <unistd.h>     // Unix 표준 함수를 위한 헤더 파일 (close, write, read 등)
#include <arpa/inet.h>  // 인터넷 주소 변환 함수를 위한 헤더 파일
#include <sys/socket.h> // 소켓 관련 함수를 위한 헤더 파일
#include <error.h>      // 에러 처리 함수를 위한 헤더 파일

int main(int argc, char* argv[])
{
    int sock;  // 소켓 파일 디스크립터를 저장할 변수
    struct sockaddr_in serv_addr;  // 서버의 주소 정보를 저장할 구조체
    char msg[1024] = { 0x00, };  // 메시지를 저장할 버퍼
    int str_len = 0;  // 메시지의 길이를 저장할 변수

    // 명령행 인수가 3개가 아니면 (프로그램 이름, 서버 IP, 서버 포트) 사용법을 출력하고 종료
    if (argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    // TCP 소켓을 생성
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        perror("socket()");

    // serv_addr 구조체를 0으로 초기화
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  // 주소 체계를 IPv4로 설정
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);  // IP 주소 설정
    serv_addr.sin_port = htons(atoi(argv[2]));  // 포트 번호 설정

    // 서버에 연결
    if (connect(sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        perror("connect()"); // 오류 메세지 출력 함수
   
    // 사용자로부터 메시지를 입력받음
    printf("Input message : ");
    scanf("%s", msg); 
    
    // 서버에 메시지를 전송
    str_len = write(sock, msg, 1024);
    if (str_len == -1)
        perror("write()");
    
    // 메시지 버퍼를 0으로 초기화
    memset(msg, 0, 1024);

    // 서버로부터 메시지를 수신
    str_len = read(sock, msg, 1024);
    if (str_len == -1)
        perror("read()");
    
    // 서버로부터 받은 메시지를 출력
    printf("Message from server : %s\n", msg);
    
    // 소켓을 닫음
    close(sock);
    
    return 0;
}