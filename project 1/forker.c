/* example1.c */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// #include <linux/kernel.h>
// #include <linux/module.h>

int main(){
    // 從呼叫 fork 開始, 會分成兩支程序多工進行
    pid_t PID = fork();

    switch(PID){
        // PID == -1 代表 fork 出錯
        case -1:
            perror("fork()");
            exit(-1);
        
        // PID == 0 代表是子程序
        case 0:
            printf("I'm Child process\n");
            printf("Child's PID is %d\n", getpid());
            char command[256];
            sprintf(command, "cat /proc/%d/maps", getpid());
            system(command);
            sleep(3)
            break;
        
        // PID > 0 代表是父程序
        default:
            printf("I'm Parent process\n");
            printf("Parent's PID is %d\n", getpid());
            char command[256];
            sprintf(command, "cat /proc/%d/maps", getpid());
            system(command);
    }

    return 0;
}