#include<iostream>
#include<cstdlib>
#include<stdio.h>

using namespace std;

class Prim
{

    struct node
    {
      int start,end,weight;
      struct node *next;                  
    };
   
       node *head_1;                        //for the initial graph
    node *head_2;                       //for the final graph (i.e. the MST) 
   
       public :
       
       Prim()                                // Constructor
    {
        head_1=head_2=NULL;
    }
    
    void push(int);                        /* to push edges into the initial graph,
                                               forming a min-priority queue */
    void pop(int,int);                     /* pop the edge from the initial graph,
                                                which has been included in the MST */
     void create_MST(int,int,int);       // creating edges of the MST
     void select_edge(int*,int,int);         /* to select the edges from the initial graph,
                                             which are to be inserted into the MST */  
     void show_list1();                  // to display the initial graph
     void show_list2();                    // to display the MST

};

void Prim :: push(int i)
{
     node *temp_1, *list_1;
    temp_1 = new node;
    temp_1->next = NULL;
    
    cout<<"\nEnter PATH-"<<i<<"\n";
    cout<<"Enter address(i.e. vertex index) of the source village : ";
    cin>>temp_1->start;
    cout<<"Enter address(i.e. vertex index) of the destination village : ";
    cin>>temp_1->end;
    cout<<"Enter cost to this path :";
    cin>>temp_1->weight;
    
    /* creating the min-priority queue..priority is the weight of the edge or path */ 
    
    if (head_1==NULL || temp_1->weight < head_1->weight)       // if the edge pushed is to be made the head
    {
        if(head_1!=NULL)
            temp_1->next = head_1;
        head_1 = temp_1;
    }
    else                                  // traverse the list until getting its exact position of insertion
    {                                                    
        list_1 = head_1;
            
        while (list_1->next != NULL && (list_1->next)->weight <= temp_1->weight)
        {                                                                
            list_1 = list_1->next;
        }
            
        temp_1->next = list_1->next;
        list_1->next = temp_1;
    }
}


void Prim :: pop(int start , int end)
{
    int flag = 0;
    node *temp_1, *prev_1;
    if(head_1==NULL)
        cout<<"The list is empty\n";
        
    else
    {
        temp_1 = head_1;
        prev_1 = temp_1;
        
        while(temp_1!= NULL && !flag)                        // to find the exact match and pop it
        {
            if(temp_1->start == start && temp_1->end == end )
            {
                if(temp_1==head_1)                          // if exact match is found with the head
                {
                    head_1=temp_1->next;                    // head->neaxt is the new head
                    delete temp_1;                          // popping the head
                    flag = 1;
                }
                else                                       // if match is found with any node part from head
                {
                    prev_1->next = temp_1->next;         
                    delete temp_1;                         // popping the node
                    flag = 1;
                }
            }
            else                                           // if it doesn't match with the node
            {
                prev_1 = temp_1;                           // keeping track of the current node as previous
                temp_1 = temp_1->next;                     // travesing one node forward
            }
        }
        
    }
}

void Prim::create_MST(int start , int end , int weight)
{
    node *temp_2, *list_2;
    temp_2 = new node;
    temp_2->start = start;
    temp_2->end = end; 
    temp_2->weight = weight;  
    temp_2->next = NULL;
    
    if (head_2==NULL || temp_2->start < head_2->start )   // if the edge pushed is to be made the head
    {
        if(head_2!=NULL)
            temp_2->next = head_2;
        head_2 = temp_2; 
    }
    else                                // traverse the list until getting its exact position of insertion
    {
        list_2 = head_2;
        
        /* edges with same starting points are kept in consecutive positions in the MST..
                the MST starts with edges containing starting vertices with smallest index */
                     
        while (list_2->next != NULL && (list_2->next)->start < temp_2->start)  
            {                                           
                list_2 = list_2->next;
            }
            temp_2->next = list_2->next;
            list_2->next = temp_2;
    }
}



void Prim::select_edge(int *d,int n,int signal)
{
    /* d is an integer array of size equal to number of vertices in the initial graph,
         with all elements as 0 initially...d[i]=1 means the vertex with
            index (i+1) is there in the MST */
        
    node *temp_1, *min;
    int count_1=0,count_2;
    if(head_2==NULL)               //to create the first node of the MST            
    {
        count_1++;                 //keeping a count of how many vertices have been inserted into the MST 
        d[0]=1;                    //vertex 1 is pushed into the MST
        temp_1 = head_1;
        while(temp_1->next!=NULL && temp_1->start!=1 && temp_1->end!=1)//no match with the vertex ,traverse
        {
            temp_1 = temp_1->next;
        }
        if(temp_1->start==1)                             //match is found(case-1)
        {
            create_MST(1,temp_1->end,temp_1->weight);    //pushing the edge into the MST
            d[(temp_1->end)-1]=1;                // i.e. the end vertex of the same is pushed into the MST
            pop(temp_1->start,temp_1->end);              //popping the edge from the initial graph
        }
        else                                           //if (temp_1->end)==1..match is found(case-2)
        {
            create_MST(temp_1->start,1,temp_1->weight);    //pushing the edge into the MST
            d[(temp_1->start)-1]=1;                // i.e. the end vertex of the same is pushed into the MST
            pop(temp_1->start,temp_1->end);                //popping the edge from the initial graph
        }

    }
    int step = 1;
    //creating other nodes of the MST
    while(count_1<(n-1) && head_1!=NULL)       //the MST will contain (n-1) number of edges
    {
            min=NULL;
            count_1++;
            if(signal)                        //to show intermediate steps
            {
                cout<<"\n\t\t  DISPLAYING THE MST (Stage-"<<step++<<")\n";
                show_list2();
            }
            int *p;              /* p is an integer array containing all the vertices (indices) 
                                        currently present in the MST */
                                    
            p = new int[count_1];
            count_2=0;
            for(int i=0;i<n;i++)       // to create elements of p with the help of array d
            {
                if(d[i]==1)              // pushing the vertex present in the MST into p
                {
                    p[count_2]=i+1;     
                    count_2++;
                }
            }
            /* for each vertices currently present in the MST,searching for a match */
            for(count_2=0;count_2<count_1;count_2++)  
            {                                          
                temp_1 = head_1;
                while(temp_1->next!=NULL && temp_1->start!=p[count_2] && temp_1->end!=p[count_2] )//no match 
                {
                    temp_1 = temp_1->next;
                }
                /* if match is found and there is already a minimum, check if it is the minimum */
                if(min!=NULL && (temp_1->start==p[count_2] || temp_1->end==p[count_2]) && temp_1->weight<min->weight) 
                {      
                    if(temp_1->start==p[count_2])                   //match is found(case-1)
                    {                                             
                        if(d[temp_1->end-1]!=1)              // checking if the edge is not there in MST
                            min = temp_1;
                    }
                    else                            //if (temp_1->end)=p[count_2]..match is found(case-2)
                    {
                        if(d[temp_1->start-1]!=1)              // checking if the edge is not there in MST
                            min = temp_1;
                    }
                }
                /* if match is found and there is no minimum , make it minimum */
                else if((temp_1->start==p[count_2] || temp_1->end==p[count_2])  && min==NULL) 
                {
                    if(temp_1->start==p[count_2])              //match is found(case-1)
                    {                                             
                        if(d[temp_1->end-1]!=1)              // checking if the edge is not there in MST
                            min = temp_1;
                    }
                    else                             //if (temp_1->end)=p[count_2]..match is found(case-2)
                    {
                        if(d[temp_1->start-1]!=1)              // checking if the edge is not there in MST
                            min = temp_1;
                    }
                }
            }
            
            if(min==NULL)                 // if no minimum cost edge is found
            {
                cout<<"\nNO MST EXISTS FOR THE GIVEN GRAPH!!!\n";
                break;
            }
            else
            {
                create_MST(min->start,min->end,min->weight);        //pushing the edge into the MST
                if(d[min->start-1]==1)                        //case-1
                    d[min->end-1]=1;                          // end vertex of the same is pushed into the MST
                else                                          //case-2
                    d[min->start-1]=1;                          //start vertex of the same is pushed into the MST
                pop(min->start,min->end);                        //popping the edge from the initial graph
                
            }
    
        }
    
}

void Prim::show_list1()                                        // show the initial graph                         
{
  node *temp_1;
  temp_1=head_1;                                        
  cout<<"\t\t   Start   "<<"end   "<<"Weight   \n";
  while(temp_1!=NULL)
      {
         cout<<"\t\t    "<<temp_1->start<<"       "<<temp_1->end<<"      "<<temp_1->weight<<"\n";
         temp_1=temp_1->next;
      }
      
}

void Prim::show_list2()                                        //show final spanning tree
{
  node *temp_2;
  temp_2=head_2;                                        
  cout<<"\t\t   Start   "<<"end   "<<"Weight   \n";
  while(temp_2!=NULL)
      {
         cout<<"\t\t    "<<temp_2->start<<"       "<<temp_2->end<<"      "<<temp_2->weight<<"\n";
         temp_2=temp_2->next;
      }
      
    cout<<"\n\n";
}


int main()
{
    Prim a;
     int i,N,M,k,flag;
    cout<<"Enter number of villages (3<=N<=250) :";
    cin>>N;
    cout<<"Enter number of inter-connecting paths (N<=M<=250): ";
     cin>>M;
     
      int *d;
      d=new int[N];
    for(i=0;i<N;i++)
    d[i]=0;

    cout<<"Do you want to show the intermediate steps?(0/1) ";
    cin>>flag;
    for(i=1;i<=M;i++)
        a.push(i);
        
    cout<<"\n\t\tDISPLAYING THE INITIAL GRAPH\n\n";
    a.show_list1();

    a.select_edge(d,N,flag);
    
       cout<<"\n\t\tFINAL MINIMUM COST SPANNING TREE\n";
    a.show_list2();

      
      return 0;
}
