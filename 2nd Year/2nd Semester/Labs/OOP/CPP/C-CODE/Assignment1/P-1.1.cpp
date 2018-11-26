#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class Time
{
    int hr, mint, sec, format;
    string tm_zn;

 public:
    void get_time();
    void show_time();
    void add_time();
    bool check(string time){
            int len = time.length();
            if(time[0] >= '2' && time[1] > '4')  return false;
            else if(time[3] >= '6' || time[6] >= '6') return false;
            return true;
        }
 
    int check_format(string time) {
        int len = time.length();
        if(len == 8)
                return 24;
        return 12;
	}
 
};
void Time::get_time()
{
    string tm_string,tmz;
    cout<<"For 24 hr format enter like-(HR:MIN:SEC)\n"<<endl;
    cout<<"For 12 hr format enter like-(HR:MIN:SEC)(SPACE)(AM/PM))\n\nNow enter the time: ";
   	cin.clear();
    fflush(stdin);
    getline(cin, tm_string,'\n');
    cin.clear();
    fflush(stdin);    
    if(!check(tm_string)) {
        cout<<"\nSORRY! You have entered wrong!!!!"<<endl;
        exit(0);
    }
    format = check_format(tm_string);
    if(format==24) {
        cout<<"You have entered in 24 hr format"<<endl;
     hr=(tm_string[0]-48)*10+tm_string[1]-48;
     mint=(tm_string[3]-48)*10+tm_string[4]-48;
     sec=(tm_string[6]-48)*10+tm_string[7]-48;
    }
    else if(format==12){
        cout<<"You have entered in 12 hr format"<<endl;
     hr=(tm_string[0]-48)*10+tm_string[1]-48;
     mint=(tm_string[3]-48)*10+tm_string[4]-48;
     sec=(tm_string[6]-48)*10+tm_string[7]-48;
     tm_zn = tm_string.substr(9,2);
    }
}
void Time::show_time()
{
	int hr1;
    if(format==24)
    {
        if(hr<=12)
        {
        	hr1=hr;
            cout<<endl<<endl<<"Your time in 12 hrs format is =   "<<hr1<<" : "<<mint<<" : "<<sec<< "  AM ";
        }
        else
        {
            hr1=hr-12;
            cout<<endl<<endl<<"Your time in 12 hrs format is =   "<<hr1<<" : "<<mint<<" : "<<sec<<"  PM ";
        }
    }
    else if(format==12)
    {
        if(tm_zn=="Am" || tm_zn=="AM" || tm_zn=="aM" || tm_zn=="am")
        {
        	cout<<"\n\nCHECK\n\n";
        	hr1=hr;
            cout<<endl<<endl<<"Your time in 24 hrs format is ::   "<<hr1<<" : "<<mint<<" : "<<sec;
        }
        else if(tm_zn=="Pm" || tm_zn=="PM" || tm_zn=="pM" || tm_zn=="pm")
        {
            hr1=hr+12;
            cout<<endl<<endl<<"Your time in 24 hrs format is ::   "<<hr1<<" : "<<mint<<" : "<<sec;
        }
    }

}
void Time::add_time()
{
    int add_min,hr1;
    cout<<endl<<endl<<"How many minutes do you want to add?? :  ";
    cin>>add_min;
    if(format==24)
    {
    	hr1=0;
        mint=mint+add_min;
        if(mint>=60)
        {
            hr=hr+mint/60;
            mint=mint%60;
    
            if(hr<12)
            {
            	hr1=hr;
                cout<<endl<<endl<<"After addition your time in 12 hrs format is =   "<<hr1<<" : "<<mint<<" : "<<sec<< "  AM ";
            }
            else if(hr>=12 && hr<24)
            {
                hr1 = hr - 12;
                cout<<endl<<endl<<"After addition your time in 12 hrs format is =   "<<hr1<<" : "<<mint<<" : "<<sec<<"  PM ";
            }
            else if(hr>=24)
			{
                hr1=hr-24;
                cout<<endl<<endl<<"After addition your time in 12 hrs format is ::   "<<hr1<<" : "<<mint<<" : "<<sec<<" AM (Next Day) ";
			}
        }
        else
        {
            if(hr<12)
            {
            	hr1=hr;
                cout<<endl<<endl<<"After addition your time in 12 hrs format is =   "<<hr1<<" : "<<mint<<" : "<<sec<< "  AM ";
            }
            else if(hr>=12 && hr<24)
            {
                hr1 = hr - 12;
                cout<<endl<<endl<<"After addition your time in 12 hrs format is =   "<<hr1<<" : "<<mint<<" : "<<sec<<"  PM ";
            }
            else if(hr>=24)
			{
                hr1=hr-24;
                cout<<endl<<endl<<"After addition your time in 12 hrs format is ::   "<<hr1<<" : "<<mint<<" : "<<sec<<" AM (Next Day) ";
			}
        }
    
    }
    else if(format==12)
        {
        	hr1=0;
            mint=mint+add_min;
            if(tm_zn=="Pm" || tm_zn=="PM" || tm_zn=="pM" || tm_zn=="pm")
            {
                hr=hr+12;
            }
            if(mint>=60)
            {
                hr=hr+mint/60;
                mint=mint%60;
    
                if(hr>=24)
                {
                    hr1=hr-24;
                    cout<<endl<<endl<<"After addition your time in 24 hrs format is ::   "<<hr1<<" : "<<mint<<" : "<<sec<<" (Next Day) ";
                }
                else
                {
                	hr1=hr;
                    cout<<endl<<endl<<"After addition your time in 24 hrs format is ::   "<<hr1<<" : "<<mint<<" : "<<sec;
                }
            }
            else
            {
                if(hr>=24)
                {
                    hr1=hr-24;
                    cout<<endl<<endl<<"After addition your time in 24 hrs format is ::   "<<hr1<<" : "<<mint<<" : "<<sec<<" (Next Day) ";
                }
                else
                {
                	hr1=hr;
                    cout<<endl<<endl<<"After addition your time in 24 hrs format is ::   "<<hr1<<" : "<<mint<<" : "<<sec;
                }
            }
        }
}
int main()
{    
    int ch,choice;
    Time tm;
	cout<<endl<<"What you want to do?"<<endl<<"Here is list to help you out:\n"<<endl;
    while(1){
	    cout<<"\n-------------------------List of options-----------------------------\n\n";
    	cout<<endl<<"\t1.ENTER THE TIME\n\n\t0.TO EXIT\n";
    	cout<<"\n\n---------------------------------------------------------------------\n\n";
        cout<<endl<<"Enter your choice: ";
        cin>>ch;
        if(ch==0)
            break;
            
	    switch(ch){
	    	case 1:
	    		tm.get_time();
	    		tm.show_time();
	    		while(1){
	    			cout<<"\n\nDo want to add some minutes? (YES=1/NO=2)\t";
	    			cin>>choice;
				    if(choice==1){
				    	cout<<"\n You entered YES\n";
				    	tm.add_time();
				    	break;
				    }
				    else if(choice==2)
					{
						cout<<"\n You entered NO\n";
						break;
					}
					else
						cout<<"\n Enter correctly please\n\n";
				}
	    		break;
	    	default:
	    		cout<<"WRONG CHOICE!!!!!!!!!!! \n ENTER AGAIN\n\n";
		}
	    
	}
    return 0;
}
