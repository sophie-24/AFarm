#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// 에러 메시지를 출력하고 프로그램을 종료하는 함수 선언
void error_handling(const char *message);

int main(int argc, char *argv[]){
    int sock; // 소켓 파일 디스크립터
    struct sockaddr_in serv_addr; // 서버 주소 정보를 담는 구조체
    char message[30];// 서버에게 보낼 메시지
    int str_len; // 메시지 길이

    // 실행 인자 확인, 올바른 사용법 출력
    if(argc != 3){
        printf("Usage: %s <IP> <port>\n", argv[0]); // 프로그램 실행 방법을 알려줌
        exit(1);                                      // 실행 인자가 부족할 경우 종료
    }

    // 소켓 생성 (IPv4, TCP 사용)
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        error_handling("socket() error"); // 소켓 생성 실패 시 에러 처리
    }

    // 서버 주소 구조체 초기화 및 설정
    memset(&serv_addr, 0, sizeof(serv_addr));           // 구조체 초기화
    serv_addr.sin_family = AF_INET;                     // IPv4 사용
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);     // 서버 IP 주소 설정
    serv_addr.sin_port = htons(atoi(argv[2]));          // 서버 포트 번호 설정 (네트워크 바이트 순서로 변환)

    // 서버에 연결 요청
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        error_handling("connect() error"); // 연결 요청 실패 시 에러 처리
    }

    // 서버로 전송할 메시지 입력
    str_len = read(sock, message, sizeof(message)-1); // 서버로부터 전송받은 메시지 읽기
    if(str_len == -1){
        error_handling("read() error"); // 읽기 실패 시 에러 처리
    }
    printf("Message from server: %s\n", message); // 서버로부터 전송받은 메시지 출력

    close(sock); // 소켓 닫기

    return 0;
}

void error_handling(const char *message){
    fputs(message, stderr); // 에러 메시지 출력
    fputc('\n', stderr);
    exit(1);                 // 프로그램 종료
}
