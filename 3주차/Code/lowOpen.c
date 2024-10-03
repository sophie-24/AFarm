#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void error_handling(const char *message);

int main(void){
    int fd; // 파일 디스크립터
    char buf[] = "Let's go!\n"; // 파일에 쓸 문자열

    fd = open("data.txt", O_CREAT|O_WRONLY|O_TRUNC); // 파일 열기 (읽기/쓰기, 파일이 없으면 생성, 파일이 있으면 내용 삭제)
    if(fd == -1){
        error_handling("open() error"); // 파일 열기 실패 시 에러 처리
    }
    printf("file descriptor: %d\n", fd); // 파일 디스크립터 출력

    if(write(fd, buf, sizeof(buf)) == -1){ // 파일에 문자열 쓰기
        error_handling("write() error"); // 쓰기 실패 시 에러 처리
    }

    close(fd); // 파일 닫기

    return 0;
}

void error_handling(const char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
