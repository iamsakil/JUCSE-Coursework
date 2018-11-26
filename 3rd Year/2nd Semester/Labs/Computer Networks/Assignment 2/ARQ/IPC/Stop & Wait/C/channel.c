#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_DELAY 3           // Maximum delay for data frames

// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
    int seq_num;
} sender_queue, receiver_queue;

int main()
{
	key_t sendq_key,receiveq_key;
	int sendq_id,receiveq_id;

	sendq_key = ftok("progfile1", 65);
	receiveq_key = ftok("progfile3", 75);

	// msgget creates a message queue
    // and returns identifier
    sendq_id = msgget(sendq_key, 0666 | IPC_CREAT);
    receiveq_id = msgget(receiveq_key, 0666 | IPC_CREAT);
    receiver_queue.mesg_type = 1;

    while(1)
    {
        printf("___________________________________________________________\n");
        printf("                 Frame Receiving\n");
        printf("___________________________________________________________\n");

        // msgrcv to receive message
        msgrcv(sendq_id, &sender_queue, sizeof(sender_queue), 1, 0);
        printf("Message received from sender queue: %s\n", sender_queue.mesg_text);

        if(strcmp(sender_queue.mesg_text,"EXIT")==0)
        {
        	//Copy message from sender queue to receiver queue
	        strcpy(receiver_queue.mesg_text, sender_queue.mesg_text);

	        // msgsnd to send message to receiver queue
		    msgsnd(receiveq_id, &receiver_queue, sizeof(receiver_queue), 0);
            break;
        }

        //Generate random delay using rand() and sleep()
        int rnd_number = rand()%MAX_DELAY;
        printf("Delay generated: %d secs\n", rnd_number);
        sleep(rnd_number);
        printf("Delay complete.\n");

        //Copy message from sender queue to receiver queue
        strcpy(receiver_queue.mesg_text, sender_queue.mesg_text);

        receiver_queue.seq_num = sender_queue.seq_num;

        // msgsnd to send message to receiver queue
	    msgsnd(receiveq_id, &receiver_queue, sizeof(receiver_queue), 0);
	    printf("Message delivered to receiver queue: %s\n", receiver_queue.mesg_text);
    }
    
    printf("___________________________________________________________\n");
    printf("            Transmission stopped by user\n");
    printf("___________________________________________________________\n");

    // to destroy the message queue
    msgctl(sendq_id, IPC_RMID, NULL);

	return 0;
}