#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct{
    int *buffer;
    int in;
    int out;
}Queue;

int main(){
	int p,c,buffer_size,num_size,output,consumed;
    int *total;
    
    Queue *q;
    
    pid_t pid;

    printf("Enter producer number: ");
    scanf("%d", &p);
    printf("Enter consumer number: ");
    scanf("%d", &c);
    printf("Enter number of items: ");
    scanf("%d",&num_size);
    printf("Enter buffer size: ");
	scanf("%d",&buffer_size);
    buffer_size++;
    
    sem_t *full;
    sem_t *empty;
    sem_t *mutex;
    sem_t *mutex_consumer;

    q = (Queue *)mmap(NULL , sizeof(Queue), PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS , -1, 0);
    q->buffer = (int *)mmap(NULL , buffer_size*sizeof(int), PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS , -1, 0);
    q->in = 0;
    q-> out = 0;
    total = (int *)mmap(NULL , sizeof(int), PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS , -1, 0);
    *total = 0;

    sem_unlink("/semaphore1");
    full = sem_open("/semaphore1", O_CREAT,  0644, 0);
    sem_unlink("/semaphore2");
    empty = sem_open("/semaphore2", O_CREAT,  0644, buffer_size-1);
    sem_unlink("/semaphore3");
    mutex = sem_open("/semaphore3", O_CREAT,  0644, 1);
    sem_unlink("/semaphore4");
    mutex_consumer = sem_open("/semaphore4", O_CREAT,  0644, 1);
    
    pid = fork();

    if(pid < 0)
    	perror("Error\n");
    else if(pid == 0){
        for(int i = 0;i < p;i++){
        if(!fork()){
        	for(int j=1;j <= num_size;j++){
                sem_wait(empty);
                sem_wait(mutex);
                printf("produced %d by producer %d\n", j, i);
                q->buffer[q->in] = j;
                q->in = (q->in + 1) % buffer_size;
                sem_post(mutex);
                sem_post(full);

            }
 		printf("%d producer finished\n",i);
        exit(1);
        }
   }
    for(int i = 0;i < p;i++)
        wait(NULL);
    printf("All producer finished\n");
    for(int i=0;i < c;i++)
        sem_post(full);
    exit(1);
    }
    else
    {   
        for(int i = 0;i < c;i++){
        if(!fork()){
            
            while(1){
            sem_wait(full);
            sem_wait(mutex);
            if(q->in == q->out){
                sem_post(mutex);
                sem_post(full);
                break;
            }
            consumed = q->buffer[q->out];
            output = q->out;
            q->out = (q->out + 1) % buffer_size;
            sem_post(mutex);
            sem_post(empty);
            sem_wait(mutex_consumer);
            *total = *total + consumed;
            printf("consumed %d by consumer %d\n", consumed, i);
            sem_post(mutex_consumer);
        }
        printf("consumer %d finished\n",i);
        exit(1);
    }
    }
    for(int i = 0;i < c;i++)
        wait(NULL);
    }
    wait(NULL);
    printf("All consumer finished\n");
    printf("TOTAL AMOUNT %d\n",  *total);
    sem_close(full);
    sem_unlink("/semaphore1");
    sem_close(empty);
    sem_unlink("/semaphore2");
    sem_close(mutex);
    sem_unlink("/semaphore3");
    sem_close(mutex_consumer);
    sem_unlink("/semaphore4");
    return 0;
}
