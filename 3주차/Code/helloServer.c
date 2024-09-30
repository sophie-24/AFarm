#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// 에러 메시지를 출력하고 프로그램을 종료하는 함수 선언
void error_handling(const char *message);

int main(int argc, char *argv[]){
    int serv_sock;               // 서버 소켓 파일 디스크립터
    int clnt_sock;               // 클라이언트 소켓 파일 디스크립터

    struct sockaddr_in serv_addr; // 서버 주소 정보를 담는 구조체
    struct sockaddr_in clnt_addr; // 클라이언트 주소 정보를 담는 구조체
    socklen_t clnt_addr_size;     // 클라이언트 주소 크기를 저장하는 변수

    char message[] = "Hello World!"; // 클라이언트에게 보낼 메시지

    // 실행 인자 확인, 올바른 사용법 출력
    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]); // 프로그램 실행 방법을 알려줌
        exit(1);                               // 실행 인자가 부족할 경우 종료
    }

    // 서버 소켓 생성 (IPv4, TCP 사용)
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1){
        error_handling("socket() error"); // 소켓 생성 실패 시 에러 처리
    }

    // 서버 주소 구조체 초기화 및 설정
    memset(&serv_addr, 0, sizeof(serv_addr));           // 구조체 초기화
    serv_addr.sin_family = AF_INET;                     // IPv4 사용
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);      // 모든 IP 주소에서 접속 허용
    serv_addr.sin_port = htons(atoi(argv[1]));          // 포트 번호 설정 (네트워크 바이트 순서로 변환)

    // 서버 소켓에 주소 정보 바인딩
    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        error_handling("bind() error"); // 바인딩 실패 시 에러 처리
    }

    // 클라이언트 연결 대기 (최대 5개의 연결 요청 대기)
    if(listen(serv_sock, 5) == -1){
        error_handling("listen() error"); // 대기 실패 시 에러 처리
    }

    clnt_addr_size = sizeof(clnt_addr); // 클라이언트 주소 구조체 크기 저장
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size); // 클라이언트 연결 수락 (accept)
    if(clnt_sock == -1){
        error_handling("accept() error"); // 연결 수락 실패 시 에러 처리
    }

    // 클라이언트에게 메시지 전송
    write(clnt_sock, message, sizeof(message));
    close(clnt_sock); // 클라이언트 소켓 닫기
    close(serv_sock); // 서버 소켓 닫기

    return 0;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수 정의
void error_handling(const char *message){
    fputs(message, stderr);  // 표준 에러에 메시지 출력
    fputc('\n', stderr);
    exit(1);                 // 프로그램 종료
}
