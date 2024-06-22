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
    int serv_sock;  // 서버 소켓 파일 디스크립터를 저장할 변수
    int clnt_sock;  // 클라이언트 소켓 파일 디스크립터를 저장할 변수
    int data_len = 0;  // 데이터의 길이를 저장할 변수

    struct sockaddr_in serv_addr;  // 서버의 주소 정보를 저장할 구조체
    struct sockaddr_in clnt_addr;  // 클라이언트의 주소 정보를 저장할 구조체
    socklen_t clnt_addr_size = 0;  // 클라이언트의 주소 정보 크기를 저장할 변수

    char msg[1024] = { 0x00, };  // 메시지를 저장할 버퍼

    // 명령행 인수가 2개가 아니면 (프로그램 이름, 서버 포트) 사용법을 출력하고 종료
    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    // TCP 소켓을 생성
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        perror("socket()"); // 오류 메세지 출력 함수

    // serv_addr 구조체를 0으로 초기화
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  // 주소 체계를 IPv4로 설정
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // IP 주소를 모든 네트워크 인터페이스로 설정
    serv_addr.sin_port = htons(atoi(argv[1]));  // 포트 번호 설정

    // 소켓에 주소 정보를 바인딩
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        perror("bind() : ");  // 오류 메세지 출력 함수
    
    // 클라이언트의 연결 요청을 대기
    if (listen(serv_sock, 5) == -1)
        perror("listen() : "); // 오류 메세지 출력 함수

    // 클라이언트의 주소 정보 크기를 설정
    clnt_addr_size = sizeof(clnt_addr);
    // 클라이언트의 연결 요청을 수락
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if (clnt_sock == -1)
        perror("accept() : "); // 오류 메세지 출력 함수

    // 클라이언트로부터 데이터를 수신
    data_len = read(clnt_sock, msg, 1024);
    if (data_len == -1) {
     perror("read() : ");   
    }

    // 클라이언트로부터 받은 메시지를 출력
    printf("Echo message : %s\n", msg);
    
    // 클라이언트에게 메시지를 전송
    write(clnt_sock, msg, 1024);
    
    // 클라이언트 소켓을 닫음
    close(clnt_sock);
    // 서버 소켓을 닫음
    close(serv_sock);
    
    return 0;
}