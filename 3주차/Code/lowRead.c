#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUF_SIZE 100

void error_handling(const char *message);

int main(void){
    int fd; // 파일 디스크립터
    char buf[BUF_SIZE]; // 파일에 쓸 문자열

    fd = open("data.txt", O_RDONLY); // 파일 열기 (읽기 전용)
    if(fd == -1){
        error_handling("open() error"); // 파일 열기 실패 시 에러 처리
    }
    printf("file descriptor: %d\n", fd); // 파일 디스크립터 출력

    if(read(fd, buf, sizeof(buf)) == -1){ // 파일에서 문자열 읽기
        error_handling("read() error"); // 읽기 실패 시 에러 처리
    }
    printf("file data: %s", buf); // 읽은 문자열 출력

    close(fd); // 파일 닫기
    return 0;
}