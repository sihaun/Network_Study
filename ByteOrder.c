#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

int main() {
    // 16비트 정수 선언
    unsigned short host_short = 0x1234;
    unsigned short network_short = htons(host_short);

    // 32비트 정수 선언
    unsigned long host_long = 0x12345678;
    unsigned long network_long = htonl(host_long);

    // 결과 출력
    printf("Host short: 0x%04x\n", host_short);
    printf("Network short: 0x%04x\n", network_short);
    printf("Host long: 0x%08lx\n", host_long);
    printf("Network long: 0x%08lx\n", network_long);

    return 0;
}
