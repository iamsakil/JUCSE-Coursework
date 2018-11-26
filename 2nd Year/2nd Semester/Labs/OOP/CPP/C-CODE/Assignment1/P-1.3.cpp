#include<iostream>
#define MSIZE 100
using namespace std;

class item{
    int code,qty;
    char name[20];
    public:
    float rate;
    void get_info(){
        cout<<endl<<"Enter the name of the item"<<endl;
        cin>>name;
        cout<<endl<<"Enter the quantity of the item"<<endl;
        cin>>qty;
        cout<<endl<<"Enter the rate for the item"<<endl;
        cin>>rate;
        cout<<"\n ITEM SUCCESSFULLY ADDED\n";
    }
    
    void ratechange(){
        cout<<endl<<"Enter the modified price: ";
        cin>>rate;
        cout<<"\n RATE SUCCESSFULLY CHANGED\n\n";
    }
    
    void display(){
        cout<<"Rate is= "<<rate<<endl<<"Quantity is= "<<qty<<endl;;
    }
    void set_code(int itcode){
        code=itcode;
    }
    
    int get_code(){
        return code;
    }
    
    void set_qty(int num){
        qty=qty+num;
    }
    
    int get_qty(){
        return qty;
    }

};
class itemlist{
    item ilist[MSIZE];
    int i,count;
    int itcode;
    public:
    	itemlist()
		{
		count=0;
		}
    void add_item(){
    	int flag=0;
    	cout<<endl<<"Enter the code for the new item to check if it already exists or not: ";
        cin>>itcode;
        for(i=0;i<count;i++){
            if(ilist[i].get_code()==itcode){
            	flag=1;
                cout<<"The item you want to add already exists"<<endl;
                break;
                }
            }
            if(flag==0){
                cout<<"OK. Now enter details of the new item: "<<endl;
                ilist[i].set_code(itcode);
                ilist[i].get_info();
                count++;
            }
    }
    void change_rate(){
        int flag=0;
        cout<<endl<<"Enter the itemcode for which you want to change rate: ";
        cin>>itcode;
        
        for(i=0;i<count;i++){
            if(ilist[i].get_code()==itcode){
                ilist[i].ratechange();
                flag=1;
            }
        }
        if(flag==0){
            cout<<"SORRY!! NO ITEM FOUND ACCORDING TO YOUR ENTRY"<<endl;
        }
    }
    void issue_receive(){
        int num,flag=0;
        int choice;
        cout<<endl<<"What you want to do?\n 1.Issue 2.Receive"<<endl;
        cin>>choice;
        cout<<"Enter the itemcode please: ";
        cin>>itcode;
        if(choice==1){
            for(i=0;i<count;i++){
                if(ilist[i].get_code()==itcode){
                    flag=1;
                    cout<<endl<<"How many items do you want to issue?";
                    cin>>num;
                    if(ilist[i].get_qty()>=num){
                        ilist[i].set_qty(-num);
                        cout<<"\n ITEM SUCCESSFULLY ISSUED.\n";
                        }
                    else{
                        cout<<"SORRY! The item you want is OUT OF STOCK"<<endl;
                    }
                }
        }
        if(flag==0){
            cout<<"SORRY!! NO ITEM FOUND ACCORDING TO YOUR ENTRY"<<endl;
        }
    }
        else if(choice==2){
            for(i=0;i<count;i++){
                if(ilist[i].get_code()==itcode){
                        flag=1;
                        cout<<endl<<"How many items do you want the system to receive?";
                        cin>>num;
                        ilist[i].set_qty(num);
                        cout<<"\n ITEM SUCCESSFULLY RECEIVED.\n";
                        }
                    }
            if(flag==0){
                cout<<"SORRY!! NO ITEM FOUND ACCORDING TO YOUR ENTRY"<<endl;
            }
        }
        
    }
    void display_price_qty(){
        int flag=0;
        cout<<endl<<"Enter the itemcode to know price and quantity: ";
        cin>>itcode;
        for(i=0;i<count;i++){
            if(ilist[i].get_code()==itcode){
                ilist[i].display();
                flag=1;
            }
        }
        if(flag==0){
            cout<<"SORRY!! NO ITEM FOUND ACCORDING TO YOUR ENTRY"<<endl;
        }
        
    }
};

int main(){
    itemlist list;
    int ch;
    cout<<"Hello, what you want to do?\n"<<endl<<"Here is list to help you out:\n"<<endl;
    while(1){
    	cout<<"\n\n________________________________________________\n\n";
    	cout<<endl<<"1.ADD AN ITEM\n\n2.CHANGE RATE OF AN ITEM\n\n3.ISSUE OR RECEIVE AN EXISTING ITEM\n\n4.DISPLAY RATE AND QUANTITY OF AN ITEM\n\n0.TO EXIT\n";
        cout<<"\n________________________________________________\n\n";
		cout<<endl<<"Enter your choice: ";
        cin>>ch;
        if(ch==0)
            break;
            
        switch(ch){
            case 1:
                list.add_item();
                break;
            case 2:
                list.change_rate();
                break;
            case 3:
                list.issue_receive();
                break;
            case 4:
                list.display_price_qty();
                break;        
        }
    }
    return 0;
}
