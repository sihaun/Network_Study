#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

int main() {
    // 16비트 정수 변환 예제
    uint16_t host_short = 0x1234;
    uint16_t network_short = htons(host_short);
    uint16_t converted_host_short = ntohs(network_short);

    printf("16-bit Host short: 0x%04x\n", host_short);
    printf("16-bit Network short: 0x%04x\n", network_short);
    printf("Converted back to Host short: 0x%04x\n", converted_host_short);

    // 32비트 정수 변환 예제
    uint32_t host_long = 0x12345678;
    uint32_t network_long = htonl(host_long);
    uint32_t converted_host_long = ntohl(network_long);

    printf("32-bit Host long: 0x%08x\n", host_long);
    printf("32-bit Network long: 0x%08x\n", network_long);
    printf("Converted back to Host long: 0x%08x\n", converted_host_long);

    return 0;
}
