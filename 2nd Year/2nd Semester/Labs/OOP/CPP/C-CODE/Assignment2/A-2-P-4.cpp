#include<stdio.h> 
#include<stdlib.h> 
#include<iostream> 
using namespace std; 
 
 
struct node{ 
    int priority; 
    int info; 
    struct node *link; 
}; 
 
 
class PriorityQueue{ 
    node* front; 
    public: 
        PriorityQueue(){ 
            front=NULL; 
        } 
        void Insert(int, int); 
        int Delete(); 
        void Display(); 
        int IsEmpty(); 
}; 
 
int main(){ 
    PriorityQueue p; 
    int ch,item,item_priority; 
    while(1){ 
        cout<<"\n\nEnter 1 To Insert\n2 To Delete\n3 To Display Priority Queue\n0 to Exit:  "; 
        cin>>ch; 
        switch(ch){ 
        case 1: 
            cout<<"Enter The Item to be added into the Queue: "; 
            cin>>item; 
            cout<<"Enter Priority: "; 
            cin>>item_priority; 
            p.Insert(item, item_priority); 
            break; 
        case 2: 
            cout<<"Deleted Element Is: "<<p.Delete()<<endl; 
            break; 
        case 3: 
            p.Display(); 
            break; 
        case 0: 
            exit(0); 
        default : 
            cout<<"Wrong Choice! Enter Again!"; 
        } 
    } 
} 
 
 
void PriorityQueue::Insert(int item, int priority){ 
    node *tmp, *q; 
    tmp = new node; 
    tmp->info = item; 
    tmp->priority = priority; 
    if (front == NULL || priority < front->priority){ 
        tmp->link = front; 
        front = tmp; 
    } 
    else{ 
        q = front; 
        while (q->link != NULL && q->link->priority <= priority) 
            q=q->link; 
        tmp->link = q->link; 
        q->link = tmp; 
       } 
} 
 
 
int PriorityQueue::Delete(){ 
    node *tmp; 
    int val; 
    if(front == NULL) 
        cout<<"Queue Underflow\n"; 
    else{ 
        tmp = front; 
        val=front->info; 
        front = front->link; 
        free(tmp); 
        return val; 
    } 
} 
 
 
int PriorityQueue::IsEmpty(){ 
 
    if( front == NULL ) 
        return 1; 
    else 
        return 0; 
} 
 
 
void PriorityQueue::Display(){ 
    struct node *ptr; 
    ptr=front; 
    if(IsEmpty()) 
        cout<<"Queue Is Empty! \n"; 
    else{ 
        cout<<"Queue Is: "; 
        cout<<"Priority\t\tItem\n"; 
        while(ptr!=NULL){ 
            cout<<"\t\t"<<ptr->priority<<"\t\t"<<ptr->info<<endl; 
            ptr=ptr->link; 
        } 
    } 
}
