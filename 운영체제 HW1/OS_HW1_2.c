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
                        x+=800;
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
                        x+=400;
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
                        x+=200;
                        break;
                default: // 부모 프로세스
                        break;
        }
	// 총 16개의 프로세스 생성
        switch(pid=fork()) {
                case -1:
                        perror("fork");
                        exit(1);
                        break;
                case 0:
                        x+=100;
                        break;
                default:
                        break;

        }
	// 현재 x 변수에 1001 이상의 값이 저장되어 있다면 
	// 해당 프로세스에서는 작업을 진행하지 않는다.
        if(x < 1000) {
                printf("CurrentPID : %d\n", (int)getpid());
                // 작업
                for(int i=x; i<=x+99; i++) {
                        printf("%d ", i * 7);
                }
                printf("\n\n");
                // 현재 프로세스 작업 시간 측정
                clock_gettime(CLOCK_MONOTONIC, &end);
                elapsed = (end.tv_sec - start.tv_sec);
                elapsed += (end.tv_nsec - start.tv_nsec) / (double)BILLION;
   printf("PID : %d, x : %d, 실행 시간: %.09lf 초\n",(int)getpid(), x, elapsed);
        }
}
