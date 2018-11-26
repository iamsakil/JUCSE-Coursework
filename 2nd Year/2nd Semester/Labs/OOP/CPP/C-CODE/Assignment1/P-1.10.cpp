#include <iostream>
#include <ctime>
#define MAX 100
using namespace std;

class savings{
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
			cout<<updation_date<<endl<<endl;
		}
};

class current{
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
	savings sav_list[MAX];
	current cur_list[MAX];
	int acc_number,i,count1,count2;
	string transaction_date;
	float amount;
	int trans_type;
	public:
		transaction(){
			count1=0;
			count2=0;
		}
		void new_account(){
			int flag=0;
			int new_acc=0,ch_type;
			char ch;
			cout<<"\n Enter type of account: 1.Savings 2.Current : ";
			cin>>ch_type;
			if(ch_type==1){
				cout<<"\n Enter account number for new customer: ";
				cin>>acc_number;
				for(i=0;i<count1;i++){
							if(sav_list[i].get_accno()==acc_number){
								flag=1;
								cout<<"\n Sorry! There is an existing savings account with same account number.";
								cout<<"\n\n Try a different account number\n\n";
							}
						}
				if(flag==0){
					new_acc=1;
					sav_list[i].set_accno(acc_number);
					cout<<"\n Account number approved.\n\n Savings account created\n";
					cout<<"\n\n Enter the amount you want to deposit: ";
					while(cin>>amount){
						if(amount>=500){
							cout<<"\n\n Amount deposited successfully.\n\n";
							break;
						}
						else{
							cout<<"\n\n Minimum of Rs.500 is to be kept in savings account!\n Please enter again....\n\n";
							}
						}
						
					}
					time_t now=time(0);
					transaction_date=ctime(&now);
					sav_list[i].updation(new_acc,amount,transaction_date);
					count1++;
				}
			else if(ch_type==2){
				cout<<"\n Enter account number for new customer: ";
				cin>>acc_number;
				for(i=0;i<count2;i++){
							if(cur_list[i].get_accno()==acc_number){
								flag=1;
								cout<<"\n Sorry! There is an existing current account with same account number.";
								cout<<"\n Try a different account number\n\n";
							}
						}
				if(flag==0){
					new_acc=1;
					cur_list[i].set_accno(acc_number);
					cout<<"\n Account number approved.\n\n New current account created\n";
					cout<<"\n\n Enter the amount you want to deposit: ";
					cin>>amount;
					cout<<"\n\n Amount deposited successfully.";
					}
					time_t now=time(0);
					transaction_date=ctime(&now);
					cur_list[i].updation(new_acc,amount,transaction_date);
					count2++;
			}
		}
		void transact(){
			cout<<"\n TRANSACTION IN PROGRESS\n\n";
			int flag=0,acc_type;
			cout<<"\n Enter account type: 1.Savings 2.Current : ";
			cin>>acc_type;
			if(acc_type==1){
				cout<<"\n SAVINGS ACCOUNT TRANSACTION IN PROGRESS........\n";
				cout<<"\n\n Enter the savings account number: ";
				cin>>acc_number;
				cout<<"\n\n What you want to do?";
				cout<<"\n\n 1.Withdraw 2.Deposit 3.Check Info of the account: ";
				cin>>trans_type;
				switch(trans_type){
					case 1:
						cout<<"\n WITHDRAWAL IN PROGRESS\n\n";
						for(i=0;i<count1;i++){
							if(sav_list[i].get_accno()==acc_number){
								flag=1;
								cout<<"\n\n Enter the amount you want to withdraw: ";
								cin>>amount;
								if(sav_list[i].get_balance()>=amount+500){
									time_t now=time(0);
									transaction_date=ctime(&now);
									sav_list[i].updation(0,-amount,transaction_date);
									cout<<"\n\n Thank you. Your withdrawal is successful\n";
								}
								else
									cout<<"\n\n You have INSUFFICIENT BALANCE for withdrawal\n\n";
							}
						}
						if(flag==0){
							cout<<"\n\n There is no such existing savings account\n\n";
						}
						break;
					case 2:
						cout<<"\n DEPOSIT IN PROGRESS\n\n";
						for(i=0;i<count1;i++){
							if(sav_list[i].get_accno()==acc_number){
								flag=1;
								cout<<"\n\n Enter the amount you want to deposit: ";
								cin>>amount;
								time_t now=time(0);
								transaction_date=ctime(&now);
								sav_list[i].updation(0,amount,transaction_date);
								cout<<"\n\n Thank you. Your deposit is successful.\n\n";
							}
						}
						if(flag==0){
							cout<<"\n\n There is no such existing savings account\n\n";
						}
						break;
					case 3:
						cout<<"\n ACCESSING ACCOUNT INFO.... \n\n";
						for(i=0;i<count1;i++){
							if(sav_list[i].get_accno()==acc_number){
								flag=1;
								cout<<"\n\n Account balance is Rs. "<<sav_list[i].get_balance()<<endl;
								cout<<"\n\n Last date of updation: ";
								sav_list[i].show_date();
							}
						}
						if(flag==0){
							cout<<"\n\n There is no such existing savings account\n\n";
						}
						break;
				}
			}
			else if(acc_type==2){
				cout<<"\n CURRENT ACCOUNT TRANSACTION IN PROGRESS........\n";
				cout<<"\n\n Enter the current account number: ";
				cin>>acc_number;
				cout<<"\n\n What you want to do?";
				cout<<"\n\n 1.Withdraw 2.Deposit 3.Check Info of the account: ";
				cin>>trans_type;
				switch(trans_type){
					case 1:
						cout<<"\n WITHDRAWAL IN PROGRESS\n\n";
						for(i=0;i<count2;i++){
							if(cur_list[i].get_accno()==acc_number){
								flag=1;
								cout<<"\n\n Enter the amount you want to withdraw: ";
								cin>>amount;
								if(cur_list[i].get_balance()-amount>=-20000){
									time_t now=time(0);
									transaction_date=ctime(&now);
									cur_list[i].updation(0,-amount,transaction_date);
									cout<<"\n\n Thank you. Your withdrawal is successful\n\n";
								}
								else
									cout<<"\n\n Withdrawl not possible!! Overdraft limit is exceeding.\n\n";
							}
						}
						if(flag==0){
							cout<<"\n\n There is no such existing current account\n\n";
						}
						break;
					case 2:
						cout<<"\n DEPOSIT IN PROGRESS\n\n";
						for(i=0;i<count2;i++){
							if(cur_list[i].get_accno()==acc_number){
								flag=1;
								cout<<"\n\n Enter the amount you want to deposit: ";
								cin>>amount;
								if(cur_list[i].get_balance()+amount<=20000){
									time_t now=time(0);
									transaction_date=ctime(&now);
									cur_list[i].updation(0,amount,transaction_date);
									cout<<"\n\n Thank you. Your deposit is successful.\n\n";
								}
								else
									cout<<"\n Entered amount of money cannot be deposited in that current account!\n\n Rs.20000 is maximum limit to keep in current account";
							}
						}
						if(flag==0){
							cout<<"\n\n There is no such existing current account\n\n";
						}
						break;
					case 3:
						cout<<"\n ACCESSING ACCOUNT INFO.... \n\n";
						for(i=0;i<count2;i++){
							if(cur_list[i].get_accno()==acc_number){
								flag=1;
								int cur_bal;
								cur_bal=cur_list[i].get_balance();
								if(cur_bal>=0)
									cout<<"\n\n Account balance is Rs. "<<cur_bal<<endl;
								else
									cout<<"\n\n No balance. Overdraft is Rs. "<<-cur_bal<<endl;
								cout<<"\n\n Last date of updation: ";
								cur_list[i].show_date();
							}
						}
						if(flag==0){
							cout<<"\n\n There is no such existing current account\n\n";
						}
						break;
				}
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
			default:
				cout<<"\n WRONG CHOICE!!\n\n Enter according to options given\n\n";
				break;      
        }
    }
    return 0;
}
