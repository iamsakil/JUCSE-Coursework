#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<math.h>

int channel[50]={0},n,tf=5,ttemp[10],a=0,k=2,w=0;
int ds[10]={1,1,1,1,1,1,1,1,1,1},is[10]={0},js[10]={0};
int status[10]={1,1,1,1,1,1,1,1,1,1};

typedef struct
{int data[5];
int dest;
int time;}station;

void send(int sno);
int stat_ini();
int send_data();
void collision();

int backoff()
{
  int kmax=15,r,s,tb;
  if(k>kmax)
  {
    printf("station exceeded its limit\n%d:",k);
    exit(0);
  }
  else
  {
    s=(pow(2,k)-1);
    r=rand()%s;
    tb=r*tf;
    k=k+1;
  }
  return (tb);
}


station stat[10];
int main()
{
  int i,j,ch;
  printf("*******************************************************************************");
  printf("\n\tCARRIER SENSE MULTIPLE ACCESS WITH COLLISION DETECTION\t\n");
  printf("\t\t\t\tCSMA|CD\t\t\t\t\n");
  printf("*******************************************************************************\n");
  printf("Enter the number of stations :");
  scanf("%d",&n);
    for(i=1;i<=n;i++)
     {printf("\nEnter 1, If station%d want to transmit signal :",i);
      scanf("%d",&ch);
      stat[i].time=0;
        if(ch==1)
         {
          printf("\nEnter time of sending signal of station%d :",i);
          scanf("%d",&stat[i].time);
          a++;
          status[i]=0;
          l:printf("\nEnter destination of station%d :",i);
          scanf("%d",&stat[i].dest);
          if(stat[i].dest==i||stat[i].dest<1||stat[i].dest>n)
          {printf("Wrong destination,Try again\n");
           goto l;}
          printf("\nEnter the data(3-Bit data) :");
           for(j=1;j<=3;j++)
           {scanf("%d",&stat[i].data[j]);}
            }
     }
  for(i=1;i<=n;i++)
  {ttemp[i]=stat[i].time;}
  send_data();
  return 0;
}

void collision(int sno)
{
  int i,tb;
  for(i=1;i<=n;i++)
  {
    if(status[i]!=1)
    {
      stat[i].time=ttemp[i];
      is[i]=0,js[i]=0,ds[i]=1;
    }
  }
  
  for(i=1;i<=(n*5);i++)
    channel[i]=0;
  printf("jamming signal sent\n");
  tb=backoff();
  stat[sno].time=stat[sno].time+tb;
  printf("station backoff by:%d",tb);
  send_data();
}

int stat_ini() //to slect the least time
{
  int x,i,min;
  for(i=1;i<=n;i++)
  {
    if(stat[i].time!=0)
    {
      min=i;
      break;
    }
  }
  x=stat[min].time;
  for(i=1;i<=n;i++)
  {
    if(x>stat[i].time&&stat[i].time!=0)
      x=stat[i].time;}
    printf("Time:%d\n",x);
  return x;
}


int send_data() //to the state which sends data
{
  int tmin=stat_ini(),t,i,tb;
  for(t=tmin;;t++)
  {
    for(i=1;i<=n;i++)
    {
      if(t==stat[i].time)
      {//printf("\nstation:%d",i);
        if(ds[i]==1&&channel[i*5-4]!=0)                              //for non-persistent
        {
          tb=backoff();
          printf("channel not free backing off by:%dsec",tb);
          stat[i].time=stat[i].time+tb;
        }
        else
        {
        send(i);
        stat[i].time++;}
        
      }
    }
    printf("\n");
    for(i=1;i<=(n*5);i++)
      printf("%d",channel[i]);
    getch();
  }
}

void send(int sno)
{
    int databit=0;
    if(ds[sno]<=3)
    databit=stat[sno].data[ds[sno]];
    printf("\nDatabit=%d\nsno:%d\n",databit,sno);
    	if(is[sno]==0 && js[sno]==0)		//sending for first time
	     {is[sno]=js[sno]=sno*5-4;
		channel[sno*5-4]=databit;}
		else
        {
         if(channel[is[sno]+1]!=0 || channel[js[sno]-1]!=0)
          {

			printf("\nCollision!!\n");
			getch();
			collision(sno);
           }
		    else
            {if(ds[sno]<=3)
              {
		        int x;
			   if(sno!=n)
                { if(is[sno]<=(n*5)-1||stat[sno].dest!=n)
			      {is[sno]++;}
			      for(x=is[sno];x>sno*5-4;x--)
			      channel[x]=channel[x-1];
			     }
			   if(sno!=1)
			     {if(js[sno]>=2||stat[sno].dest==1)
			       {js[sno]--;}
                   for(x=js[sno];x<sno*5-4;x++)
			       channel[x]=channel[x+1];
                 }
			   channel[sno*5-4]=databit;
			  }
			else
			{
			int x;
			if(sno!=n)
			{
			     if(is[sno]<=(n*5)-1||stat[sno].dest!=n)
			     is[sno]++;
			     x=is[sno];
                 int j;
                 for(j=1;j<=3;x--)
                 {channel[x]=channel[x-1];j++;}
                 if(x!=(sno*5-4)||x==1)
                 {channel[x]=0;}
             }
			if(sno!=1)
			{
			      if(js[sno]>=2||stat[sno].dest==1)
			      js[sno]--;
			      x=js[sno];
                  int j;
			      for(j=1;j<=3;x++)
			      {channel[x]=channel[x+1];
			      j++;}
                  channel[x]=0;
            }
			if(channel[stat[sno].dest*5-3]==stat[sno].data[3])
                {{printf("\n Data sending succesfull.\n");
                  status[sno]=1;
                  w++;
                  getch();}
                if(a==w)
                 {printf("All signals sent successfully\n");
                  exit(0);}}
                  channel[sno*5-4]=databit;}}
        }
    ds[sno]++;
}