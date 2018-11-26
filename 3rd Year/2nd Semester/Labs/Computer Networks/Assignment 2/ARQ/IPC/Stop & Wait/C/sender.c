#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
 
// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
    int seq_num;
} sender_queue;

//structure for acknowledgement
struct ack_buffer {
    long ack_type;
    char ack_text[100];
    int seq_num;
} acknowledgement;
 
int main()
{
    key_t key,ack_key;
    int msg_id,ack_id,time_out=3,temp_time,ack_flag;
 
    // ftok to generate unique key
    key = ftok("progfile1", 65);
    ack_key = ftok("progfile2", 70);
 
    // msgget creates a message queue
    // and returns identifier
    msg_id = msgget(key, 0666 | IPC_CREAT);
    sender_queue.mesg_type = 1;
    ack_id = msgget(ack_key, 0666 | IPC_CREAT);

    int resend_flag = 0;
    char s[100];
    char ch1[2];
    while(1)
    {
    	printf("___________________________________________________________\n");
		printf("Write message to transmit or enter EXIT to stop: ");
		gets(s);
	    if(strcmp(s,"EXIT")==0)
	    {
			strcpy(sender_queue.mesg_text,s);
			msgsnd(msg_id, &sender_queue, sizeof(sender_queue), 0);
		 	break;
	    }
	    int n=strlen(s);
	    int i;
	    for(i=0;i<n;i++)
	    {
	    	if(resend_flag==0)
	    	{
	    		printf("___________________________________________________________\n");
		        printf("                    Frame Sending\n");
		        printf("___________________________________________________________\n");
				ch1[0]= s[i];
				ch1[1]='\0';
		        strcpy(sender_queue.mesg_text,ch1);
		        sender_queue.seq_num = i+1;
	        }
	        else
	        {
	         	printf("___________________________________________________________\n");
   	            printf("                Retransmission started\n");
		        printf("___________________________________________________________\n");
	        }
	 
	    	// msgsnd to send message
	        msgsnd(msg_id, &sender_queue, sizeof(sender_queue), 0);
	    	// display the message
	        printf("Message sent is : %s \n", sender_queue.mesg_text);

	        printf("___________________________________________________________\n");
	        printf("                   Acknowledgement\n");
	        printf("___________________________________________________________\n");

	        ack_flag = 0;
	        temp_time = time_out;
	        while(temp_time--) 
	        {
		        printf("Waiting for acknowledgement....\n");
		        int ack_ret=msgrcv(ack_id, &acknowledgement, sizeof(acknowledgement), 1, IPC_NOWAIT);
			    // msgrcv waits for ack from receiver
			    if(ack_ret>=0 && sender_queue.seq_num==acknowledgement.seq_num)
			    {
			    	ack_flag = 1;
			    	break;
			    }
			    sleep(1);
	        }
	        if(ack_flag==0)
	        {
	        	i--;
	    	    resend_flag = 1;
	            printf("Time out!\n");
	        }
	        else
	        {
	    	    resend_flag = 0;
	    	    printf("Acknowledgement received is : %s \n", acknowledgement.ack_text);
	    	}
	    }
	    strcpy(sender_queue.mesg_text, "EOF");
	    // msgsnd to send EOF
	    msgsnd(msg_id, &sender_queue, sizeof(sender_queue), 0);
    }

    printf("___________________________________________________________\n");
    printf("           Transmission stopped by user\n");
    printf("___________________________________________________________\n");

    // to destroy the acknowledgement queue
	msgctl(ack_id, IPC_RMID, NULL);
 
    return 0;
}
