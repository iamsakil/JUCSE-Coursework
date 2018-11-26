#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define size 5

int min(int a,int b)
{
   if(a<b)
	return a;

   return b;
}

// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
    int seq_num;
} message;

//structure for acknowledgement
struct ack_buffer {
    long ack_type;
    char ack_text[100];
    int seq_num;
} acknowledgement;
 
int main()
{
    key_t key,ack_key;
    int msgid,ack_id,time_out,ack_flag;
 
    // ftok to generate unique key
    key = ftok("progfile1", 65);
    ack_key = ftok("progfile2", 70);
 
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;
    ack_id = msgget(ack_key, 0666 | IPC_CREAT);

    int resend_flag = 0;
    char s[100];
    char ch1[2];
    while(1)
    {
	    printf("Write data to transmit or enter EXIT to stop: ");
	    gets(s);
	    if(strcmp(s,"EXIT")==0)
	    {
			strcpy(message.mesg_text,s);
			msgsnd(msgid, &message, sizeof(message), 0);
		 	break;
	    }
	    int n=strlen(s);
	    int i=0;
	    while(i<n)
	    {
    		int count=0;
	    	if(resend_flag==0)
	    	{
	    		printf("___________________________________________________________\n");
		        printf("                    Message Sending\n");
		        printf("___________________________________________________________\n");
				int j;
				for(j=0;j<size;j++)
				{
				   if(i+j>=n)
				   	break;
				   ch1[0]=s[i+j];
				   ch1[1]='\0';
				   count++;
				   strcpy(message.mesg_text,ch1);
				   message.seq_num = i+j+1;
				   // msgsnd to send message
				   msgsnd(msgid, &message, sizeof(message), 0);
				   // display the message
				   printf("Frame sent is : %s \n", message.mesg_text);
				}
				//i++;
	        }
	        else
	        {
	        	printf("___________________________________________________________\n");
   	            printf("                Retransmission started\n");
		        printf("___________________________________________________________\n");
				int j;
				for(j=0;j<size;j++)
				{
				   if(i+j>=n)
					break;
				   ch1[0]=s[i+j];
				   ch1[1]='\0';
				   count++;
				   strcpy(message.mesg_text,ch1);
				   // msgsnd to send message
				   msgsnd(msgid, &message, sizeof(message), 0);
				   // display the message
				   printf("Frame sent is : %s \n", message.mesg_text);
				}
	        }

	        printf("___________________________________________________________\n");
	        printf("                   Acknowledgement\n");
	        printf("___________________________________________________________\n");
	        int c=0;
	        while(c<count)
	        {
	        	ack_flag = 0;
	        	time_out = 3;
	        	while(time_out--)
	        	{
		         	printf("Waiting for acknowledgement....\n");
			    	// msgrcv waits for ack from receiver
			    	int ack_ret=msgrcv(ack_id, &acknowledgement, sizeof(acknowledgement), 1, IPC_NOWAIT);
				    if(ack_ret>=0 && message.seq_num==acknowledgement.seq_num)
			        {
			              ack_flag = 1;
			    	      break;
			        }
			        sleep(1);
		    	}
		    	if(ack_flag==0)
		    	{
		    		resend_flag = 1;
		    		printf("Time out!\n");
		    		// i+=c;
		    		i=c;
		    		break;
		    	}
		    	else
		    	{
		    		resend_flag = 0;
		    		//printf("Acknowledgement received is : %s \n", acknowledgement.ack_text);
		    		printf("Acknowledgement received.\n");
		    		i++;
		    		c++;
		    	}
		    }
	    }
	    strcpy(message.mesg_text, "EOF");
	    // msgsnd to send EOF
	    msgsnd(msgid, &message, sizeof(message), 0);
    }

    printf("___________________________________________________________\n");
    printf("           Transmission stopped by user\n");
    printf("___________________________________________________________\n");

    // to destroy the acknowledgement queue
	msgctl(ack_id, IPC_RMID, NULL);
 
    return 0;
}
