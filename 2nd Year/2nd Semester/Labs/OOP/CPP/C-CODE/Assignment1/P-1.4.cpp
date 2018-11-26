#include <iostream>
#include <ctime>
#define MAX 100
using namespace std;
struct subjects{
	int s1,s2,s3,s4,s5;
};
class student{
	int roll;
	char name[20],course[20];
	string date;
	struct subjects marks;
	int m_check;
	public:
		student(){
		m_check=0;
		}
		void set_roll(int roll_no){
			roll=roll_no;
		}
		int get_roll(){
			return roll;
		}
		void get_info(){
			char slash='/';
			cout<<"\n Enter the student's name: ";
			cin>>name;
			cout<<"\n Enter the course to enroll the student: ";
			cin>>course;
			time_t now=time(0);
			date=ctime(&now);
			cout<<"\n Date and time of admission is recorded from system.\n Student is admitted successfully\n"<<endl;
		}
		void get_marks(){
			m_check=1;
			cout<<"\n Enter the marks in 5 subjects\n";
			cout<<"\n Subject 1: ";
			cin>>marks.s1;
			cout<<"\n Subject 2: ";
			cin>>marks.s2;
			cout<<"\n Subject 3: ";
			cin>>marks.s3;
			cout<<"\n Subject 4: ";
			cin>>marks.s4;
			cout<<"\n Subject 5: ";
			cin>>marks.s5;
		}
		int get_mcheck(){
			return m_check;
		}
		void show_details(){
			cout<<"\n Name of the student: "<<name<<endl;
			cout<<"\n Roll number of the student: "<<roll<<endl;
			cout<<"\n Course name: "<<course<<endl;
			cout<<"\n Admission date: "<<date<<endl;
			cout<<"\n Marks of the student in 5 different subjects is as follows: \n\n";
			cout<<"\n\n Subject 1: ";
			cout<<marks.s1;
			cout<<"\n---------------";
			cout<<"\n\n Subject 2: ";
			cout<<marks.s2;
			cout<<"\n---------------";
			cout<<"\n\n Subject 3: ";
			cout<<marks.s3;
			cout<<"\n---------------";
			cout<<"\n\n Subject 4: ";
			cout<<marks.s4;
			cout<<"\n---------------";
			cout<<"\n\n Subject 5: ";
			cout<<marks.s5;
			cout<<"\n---------------";
		}
};

class all_students{
	student stdnt[MAX];
	int i,roll_no,count;
	public:
		
		all_students(){
		count=0;
		}
		
		void admission(){
			int flag=0;
			cout<<"\nEnter the roll no for the student: ";
			cin>>roll_no;
			for(i=0;i<count;i++){
	            if(stdnt[i].get_roll()==roll_no){
	            	flag=1;
	                cout<<"\nSorry! The roll number already exists"<<endl;
	                break;
	                }
            }
            if(flag==0){
                cout<<"\nOK. Now enter details of the new student: "<<endl;
                stdnt[i].set_roll(roll_no);
                stdnt[i].get_info();
                count++;
            }
		}
		
		void receive_marks(){
			int flag=0;
			cout<<"\nEnter the roll no for the student for entry of marks: ";
			cin>>roll_no;
			for(i=0;i<count;i++){
	            if(stdnt[i].get_roll()==roll_no){
	                stdnt[i].get_marks();
	                flag=1;
            	}
        	}
        if(flag==0){
            cout<<"SORRY!! There is no such student with roll no "<<roll_no<<endl;
        }
	}
	
	void marksheet(){
		int flag=0;
			cout<<"\nEnter the roll no for the student to prepare his/her marksheet: ";
			cin>>roll_no;
			for(i=0;i<count;i++){
	            if(stdnt[i].get_roll()==roll_no && stdnt[i].get_mcheck()==1){
	                stdnt[i].show_details();
	                flag=1;
            	}
            	else if(stdnt[i].get_roll()==roll_no && stdnt[i].get_mcheck()==0){
            		flag=1;
            		cout<<"\n Unable to show marksheet.\n\nMarks for roll no "<<roll_no<<" has not been entered yet";
				}
        	}
        if(flag==0){
            cout<<"SORRY!! There is no such student with roll no "<<roll_no<<endl;
        }
	}
	
	void total_students(){
		cout<<"\n Total number of students who have taken admission is: "<<count<<endl;
	}
};

int main(){
	all_students all_st;
	int ch;
	cout<<"Hello, what you want to do?\n"<<endl<<"Here is list to help you out:\n"<<endl;
	while(1){
		cout<<"\n-------------------------List of options-----------------------------\n\n";
    	cout<<endl<<"\t1.ADMIT A STUDENT\n\n\t2.ENTER MARKS OF A STUDENT\n\n\t3.GENERATE MARKSHEET OF A STUDENT\n\n\t4.DISPLAY TOTAL NUMBER OF STUDENTS WHO HAVE TAKEN ADMISSION\n\n\t0.TO EXIT\n";
    	cout<<"\n\n---------------------------------------------------------------------\n\n";
        cout<<endl<<"Enter your choice: ";
        cin>>ch;
        if(ch==0)
            break;
            
        switch(ch){
            case 1:
                all_st.admission();
                break;
            case 2:
                all_st.receive_marks();
                break;
            case 3:
                all_st.marksheet();
                break;
            case 4:
                all_st.total_students();
                break; 
			default:
				cout<<"\n Enter correctly"<<endl;       
        }
    }
    return 0;
}
