#include<cstdio> 
#include<iostream> 
#include<cstdlib> 
using namespace std; 
class String{ 
    char* s; 
    int len; 
    static int cp; 
    public: 
        String(int k=0){ 
            len=k; 
        } 
        String(const String &a){ 
            cp=cp+1; 
            cout<<"Objects copied using copy constructor using reference count : "<<cp<<endl; 
            len=a.len; 
            s=(char*)malloc(len*sizeof(char)); 
            for(int i=0; i<len; i++) 
                s[i]=a.s[i]; 
        }  
         
        ~String(){ 
            if(cp>0) 
                cout<<"Destroying objects created using destructor : "<<cp<<endl; 
            cp=cp-1; 
            if(cp==0) 
                delete s; 
        } 
}; 
int String::cp=0; 
int main(){ 
    String s1; 
    String s2(s1);      //three objects copied. 
    String s3(s1); 
    String s4(s1); 
    return 0; 
}
