#include <iostream>
#include <ctime>
#define MAX 100
using namespace std;

class balance{
	int acc_no;
	float balan;
	string updation_date;
	public:
		void set_accno(int acc_number){
			acc_no=acc_number;
		}
		int get_accno(){
			return acc_no;
		}
		int get_balance(){
			return balan;
		}
		void updation(int new_acc,int amount,string transaction_date){
			if(new_acc==1)
				balan=amount;
			else
				balan=balan+amount;
			time_t now=time(0);
			updation_date=ctime(&now);
		}
		void show_date(){
			cout<<updation_date<<endl;
		}
};

class transaction{
	balance acc_list[MAX];
	int acc_number,i,count;
	string transaction_date;
	float amount;
	int trans_type;
	public:
		transaction(){
			count=0;
		}
		void new_account(){
			int flag=0;
			int new_acc=0;
			char ch;
			cout<<"\n Enter account number for new customer: ";
			cin>>acc_number;
			for(i=0;i<count;i++){
						if(acc_list[i].get_accno()==acc_number){
							flag=1;
							cout<<"\n Sorry! There is an existing customer with same account number.";
							cout<<"\n Try a different account number";
						}
					}
			if(flag==0){
				new_acc=1;
				acc_list[i].set_accno(acc_number);
				cout<<"\n Account number approved.\n";
				cout<<"\n Do you want to deposit some money? (y/n): ";
				cin>>ch;
				if(ch=='y'||ch=='Y'){
					cout<<"\n\n Enter the amount you want to add: ";
					cin>>amount;
					cout<<"\n\n Amount deposited successfully.";
				}
				else{
					amount=0;
					cout<<"\n\n OK. The account is a zero balance account as of now";
				}
				time_t now=time(0);
				transaction_date=ctime(&now);
				acc_list[i].updation(new_acc,amount,transaction_date);
				count++;
			}
		}
		void transact(){
			cout<<"\n TRANSACTION IN PROGRESS\n\n";
			int flag=0;
			cout<<"\n\n Enter the account number: ";
			cin>>acc_number;
			cout<<"\n\n What you want to do?";
			cout<<"\n\n 1.Withdraw 2.Deposit 3.Check Info of the account: ";
			cin>>trans_type;
			switch(trans_type){
				case 1:
					cout<<"\n WITHDRAWAL IN PROGRESS\n\n";
					for(i=0;i<count;i++){
						if(acc_list[i].get_accno()==acc_number){
							flag=1;
							cout<<"\n\n Enter the amount you want to withdraw: ";
							cin>>amount;
							if(acc_list[i].get_balance()>=amount){
								time_t now=time(0);
								transaction_date=ctime(&now);
								acc_list[i].updation(0,-amount,transaction_date);
								cout<<"\n\n Thank you. Your withdrawal is successful";
							}
							else
								cout<<"\n\n You have INSUFFICIENT BALANCE for withdrawal";
						}
					}
					if(flag==0){
						cout<<"\n\n There is no such existing account";
					}
					break;
				case 2:
					cout<<"\n DEPOSIT IN PROGRESS\n\n";
					for(i=0;i<count;i++){
						if(acc_list[i].get_accno()==acc_number){
							flag=1;
							cout<<"\n\n Enter the amount you want to deposit: ";
							cin>>amount;
							time_t now=time(0);
							transaction_date=ctime(&now);
							acc_list[i].updation(0,amount,transaction_date);
							cout<<"\n\n Thank you. Your deposit is successful.";
						}
					}
					if(flag==0){
						cout<<"\n\n There is no such existing account";
					}
					break;
				case 3:
					cout<<"\n ACCESSING ACCOUNT INFO.... \n\n";
					for(i=0;i<count;i++){
						if(acc_list[i].get_accno()==acc_number){
							flag=1;
							cout<<"\n\n Account balance is Rs. "<<acc_list[i].get_balance()<<endl;
							cout<<"\n\n Last date of updation: ";
							acc_list[i].show_date();
						}
					}
					if(flag==0){
						cout<<"\n\n There is no such existing account";
					}
					break;
			}
		}
};

int main(){
	transaction trans_obj;
	int choice;
	cout<<"Hello, what you want to do?\n"<<endl<<"Here is list to help you out:\n"<<endl;
	while(1){
		cout<<"\n-------------------------List of options-----------------------------\n\n";
    	cout<<endl<<"\t1.MAKE A NEW ACCOUNT\n\n\t2.TRANSACT OR CHECK ACCOUNT INFO\n\n\t0.TO EXIT\n";
    	cout<<"\n\n---------------------------------------------------------------------\n\n";
        cout<<endl<<"Enter your choice: ";
        cin>>choice;
        if(choice==0)
            break;
            
        switch(choice){
            case 1:
                trans_obj.new_account();
                break;
            case 2:
                trans_obj.transact();
                break;      
        }
    }
    return 0;
}
