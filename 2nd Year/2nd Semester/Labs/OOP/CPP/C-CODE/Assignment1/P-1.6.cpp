#include<cstdio> 
#include<iostream> 
#include<cstring> 
#include<cstdlib> 
using namespace std; 
class String{ 
    char* s; 
    int len; 
    public: 
        String(int n=0,char c=' '){ 
            len=n; 
            int i; 
            s=(char*)(malloc(len*sizeof(char))); 
            for(i=0;i<len;i++) 
                s[i]=c; 
        } 
        String(char*p, int size){ 
            len=size; 
            s=p; 
        } 
        String(const String &a){ 
            len=a.len; 
            s=(char*)malloc(len*sizeof(char)); 
            for(int i=0; i<len; i++) 
                s[i]=a.s[i]; 
        }  
        void input(); 
        String operator+(String &t); 
        bool operator<(String &t);                         
        bool operator>(String &t); 
        bool operator==(String &t);                     
        void disp(); 
        int length(); 
}; 

void String::input(){
    cin>>this->s; 
}

String String::operator+(String &t){ 
            String con; 
             int l1,l2,i; 
            l1=(*this).length(); 
            l2=t.length(); 
            con.s=(char*)(malloc((l1+l2+1)*(sizeof(char))));             
            for(i=0; i<(l1+l2); i++){ 
                if(i<l1) 
                    con.s[i]=this->s[i]; 
                else 
                    con.s[i]=t.s[i-l1]; 
            } 
            s[l1+l2]='\0'; 
            return con; 
}

bool String::operator<(String &t){ 
            String rel; 
            int l1,l2,c,i; 
            c=0; 
            while(this->s[c]==t.s[c]) 
                c++; 
             
            if(int(this->s[c])<int(t.s[c])) 
                return true; 
            return false; 
}                             
  
bool String::operator>(String &t){ 
            String rel; 
            int l1,l2,c,i; 
            c=0; 
            while(this->s[c]==t.s[c]) 
                c++; 
             
            if(int(this->s[c])>int(t.s[c])) 
                return true; 
            return false; 
} 
   
bool String::operator==(String &t){ 
            String rel; 
            int l1,l2,c,i; 
            c=0; 
            l1=(*this).length(); 
            l2=t.length(); 
            (*this).disp(); 
            cout<<endl; 
            t.disp(); 
            while(this->s[c]==t.s[c]) 
                c++; 
            cout<<c; 
            if(l1==l2 && c==(l1+l2-2)) 
                return true; 
            return false; 
} 
                                     
void String::disp(){ 
            len=strlen(this->s); 
            for(int i=0; i<(len); i++) 
                cout<<(this->s[i]); 
}
    
int String::length(){ 
    return (strlen(this->s)); 
} 

String init(){ 
    int x,n; 
    char c; 
    char* p;
    while(1){
    	cout<<"\n\n__________________________________________________________________\n\n";
    	cout<<"\n\n Enter 1 to initialize string with a given character and a given length\n\n Enter 2 to initialize it with a given string : "; 
	    cout<<"\n\n__________________________________________________________________\n\n";
		cin>>x; 
	    if(x==1){ 
	        cout<<"\n\n Enter size of string : "; 
	        cin>>n; 
	        while(n<=0){ 
	            cout<<"\n\n Length Invalid! Try Again: "; 
	            cin>>n; 
	        } 
	        cout<<"\n\n Enter Initial character to initialise string with: "; 
	        cin>>c; 
	        String st(n,c); 
	        return st; 
	    } 
	    else if(x==2){
	        cout<<"\n\n Enter SIZE of string: "; 
	        cin>>n; 
	        p=(char*)malloc(n*sizeof(char)); 
	        cout<<"\n\n Enter the string : "; 
	        for(int i=0; i<n; i++) 
	            cin>>p[i];             
	        String st(p,n); 
	        return st; 
	    }
	    else{
	    	cout<<"\n\n Enter according to the options given!!!!\n\n";
	    	continue;
		}
	}
}

int main(){ 
    int i,n,ch; 
    String a,b; 
    char op,plus='+'; 
     
    while(1){
    	cout<<"\n\n______________________________________________________________\n\n";
        cout<<"Enter 1 for Initialization of the string\n\nEnter 2 to concatenate two strings using operator overloading.\n\nEnter 3 to compare two strings using operator overloading.\n\nEnter 0 to exit\n"; 
        cout<<"\n\n______________________________________________________________\n\n";
		cout<<"\n\n Enter your choice: ";
		cin>>ch;
		switch(ch){
			case 0:
            	return 0;
	        case 1:{
	        	a=init(); 
			    cout<<"\n\n String A is: "; 
			    a.disp(); 
			    cout<<endl<<endl;
				break;
			}
	        case 2:{
	        	String obj,s1,s2; 
	            cout<<"\n\n Enter the two strings like this STRING1(space)+(space)STRING2 to concatenate: \n";
	            cout<<"\t";
	            s1.input();
	            cin>>plus;
	            s2.input(); 
	            obj=s1+s2; 
	            cout<<"The concatenated string is : ";     
	            obj.disp(); 
	            cout<<endl;
				break;
			}
	        case 3:{
	        	String obj,s1,s2; 
	            bool res; 
	            cout<<"\n\n Enter the 1st string to be checked by relational operator :\t";
	            s1.input();
				cout<<"\n\n Enter the 2nd string to be checked by relational operator :\t"; 
	            s2.input();
	            res=(s1==s2); 
	            if(res==true) 
	                cout<<"\n\n Strings are equal!"; 
	            else{ 
	                cout<<"\n\n Enter Operator: ( < or >): "; 
	                cin>>op; 
	                if(op=='>') 
	                    res=s1>s2; 
	                if(op=='<') 
	                    res=s1<s2; 
	                cout<<"Result Is: "; 
	                if(res==1) 
	                    cout<<"True"; 
	                else 
	                    cout<<"False"; 
	            } 
	            cout<<endl;
				break;
			}
	        default:{
	        	cout<<"\n\n Enter according to the options given!!!!\n\n";
				break;
			}
		}
    } 
    return 0; 
}
