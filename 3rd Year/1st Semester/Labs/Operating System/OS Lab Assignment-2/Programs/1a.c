#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	int i;
	pid = fork();
	if (pid < 0) { 
		fprintf(stderr, "Fork Failed");
	    return 1;
	}
	else if (pid == 0) { 
	
        	for (i = 1; i <= 10; i++){
            	usleep(3000);
            	printf("Process Y- %d\n",i);
            }
            exit(0);
	}
	else { 
		if(!fork()){
			for (i = 1; i <= 10; i++){
            	printf("Process X- %d\n",i);
            	usleep(2000);
            	}
            exit(0);
        }
	wait(NULL);
	wait(NULL);
	printf("Child Complete\n");
	}
	return 0;
}
