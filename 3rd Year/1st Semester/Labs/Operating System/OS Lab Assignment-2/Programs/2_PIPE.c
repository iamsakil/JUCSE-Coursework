#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 100
#define READ 0
#define WRITE 1

int main(){
    char writemsg[BUFFER_SIZE];
    char readmsg[BUFFER_SIZE];
    int fd[2];
    int df[2];
    pid_t pid;
    if ((pipe(fd) == -1) || (pipe(df) == -1)) {
    perror("Pipe Failed\n");
    return 1;
    }
    pid = fork();
    if (pid < 0) {
    perror("Fork Failed\n");
    return 1;
    }
    if (pid == 0) {
        close(fd[WRITE]);
        read(fd[READ], readmsg, BUFFER_SIZE);
        printf("Receiver received: %s\n",readmsg);
        close(fd[READ]);
        close(df[READ]);
        sleep(2);
        printf("Receiver called: ");
        scanf("%s", writemsg);
        write(df[WRITE], writemsg, strlen(writemsg)+1);
        close(df[WRITE]);
    }
    else {
        sleep(1);
        close(fd[READ]);
        printf("Caller called: ");
        scanf("%s", writemsg);
        write(fd[WRITE], writemsg, strlen(writemsg)+1);
        close(fd[WRITE]);
        close(df[WRITE]);
        read(df[READ], readmsg, BUFFER_SIZE);
        printf("Caller received: %s\n",readmsg);
        close(df[READ]);
    }
return 0;
}