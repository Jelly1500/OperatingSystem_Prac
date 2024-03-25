#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>

#define BILLION 1000000000L

int main() {
        struct timespec start, end;
        double elapsed;
        pid_t pid;
        pid_t firstPid=getpid();
        int x=1;
        clock_gettime(CLOCK_MONOTONIC, &start);
	// 총 2개의 프로세스 생성
        switch(pid=fork()) {
                case -1: // fork 실패
                        perror("fork");
                        exit(1);
                        break;
                case 0: // 자식 프로세스
                        x+=500;
                        break;
                default: // 부모 프로세스
                        break;
        }
	// 총 4개의 프로세스 생성
        switch(pid=fork()) {
                case -1: // fork 실패
                        perror("fork");
                        exit(1);
                        break;
                case 0: // 자식 프로세스
                        x+=250;
                        break;
                default: // 부모 프로세스
                        break;

        }
	// 총 8개의 프로세스 생성
        switch(pid=fork()) {
                case -1: // fork 실패
 			perror("fork");
                        exit(1);
                        break;
                case 0: // 자식 프로세스
                        x+=125;
                        break;
                default: // 부모 프로세스
                        break;
        }
        printf("CurrentPID : %d\n", (int)getpid());
	// 작업
        for(int i=x; i<=x+124; i++) {
                printf("%d ", i * 7);
        }
        printf("\n\n");
	 // 시간 측정
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed = (end.tv_sec - start.tv_sec);
        elapsed += (end.tv_nsec - start.tv_nsec) / (double)BILLION;
        printf("PID : %d, x : %d, 실행 시간: %.09lf 초\n",(int)getpid(), x, elapsed);
}
