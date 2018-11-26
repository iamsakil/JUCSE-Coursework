#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int receivedFrames[200];
 
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

int isReceived(int seq_num, int pos)
{
    if(pos==-1)
        return 0;

    for(int i=0;i<=pos;i++)
    {
        if (receivedFrames[i]==seq_num)
        {
            return 1;
        }
    }
    return 0;
}
 
int main()
{
    for(int i=0;i<200;i++)
    {
        receivedFrames[i] = -1;
    }

    key_t receiverq_key,ack_key;
    int receiverq_id,ack_id;
 
    // ftok to generate unique key
    receiverq_key = ftok("progfile3", 75);
    ack_key = ftok("progfile2", 70);
 
    // msgget creates a message queue
    // and returns identifier
    receiverq_id = msgget(receiverq_key, 0666 | IPC_CREAT);
    ack_id = msgget(ack_key, 0666 | IPC_CREAT);
    acknowledgement.ack_type = 1;

    int ack_number = 0,pos = -1;
    char ack_no_str[100],rcv_msg_buffer[100];

    while(1)
    {
        printf("___________________________________________________________\n");
        printf("                 Frame Receiving\n");
        printf("___________________________________________________________\n");

        // msgrcv to receive message
        msgrcv(receiverq_id, &message, sizeof(message), 1, 0);
     
        if(strcmp(message.mesg_text,"EXIT")==0)
            break;
        if(strcmp(message.mesg_text,"EOF")==0)
        {
            printf("END OF FRAMES signal received.\n");
            printf("___________________________________________________________\n");
            printf("Complete message is: ");
            printf("%s\n", rcv_msg_buffer);
            strcpy(rcv_msg_buffer, "");
            ack_number = 0;
            printf("___________________________________________________________\n");
            printf("Waiting for next message...........\n");
            continue;
        }
        else
        {
            printf("Seq num of the frame: %d\n", message.seq_num);
            if (isReceived(message.seq_num, pos)==0)
            {
                pos++;
                receivedFrames[pos] = message.seq_num;
                strcat(rcv_msg_buffer, message.mesg_text);
            }
        }
        // display the message
        printf("Frame received is : %s \n", message.mesg_text);

        printf("___________________________________________________________\n");
        printf("               Acknowledgement Sending\n");
        printf("___________________________________________________________\n");

        ack_number++;
        sprintf(ack_no_str, "%d", ack_number);
        strcpy(acknowledgement.ack_text, ack_no_str);
        acknowledgement.seq_num = message.seq_num;
        // msgsnd to send acknowledgement
        msgsnd(ack_id, &acknowledgement, sizeof(acknowledgement), 0);
        printf("Acknowledgement sent is %d.\n",ack_number);
    }
    
    printf("___________________________________________________________\n");
    printf("            Transmission stopped by user\n");
    printf("___________________________________________________________\n");

    // to destroy the message queue
    msgctl(receiverq_id, IPC_RMID, NULL);

    return 0;
}