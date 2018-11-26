#include<iostream>
#include<math.h>
using namespace std;

class complex
{
	public:
	 float re;
	 float im;
	
	 
	 void input(void);
	 void addition(void);
	 void subtraction(void);		
};

complex complex1, complex2, complex3;


void complex::input(void)
{
	char character1, character2;
	cout<<"\nEnter complex number in X+iY format: ";
	cin>>re;
	cin>>character1;
	cin>>character2;
	cin>>im;
	if(character1 == '-')
		im = -im;
}

void complex::addition(void)
{
	re = complex1.re + complex2.re;
	im = complex1.im + complex2.im;	
}

void complex::subtraction(void)
{
	re = complex1.re - complex2.re;
	im = complex1.im - complex2.im;	
}


int main()
{
	int ch;
	cout<<endl;
	
	while(1){
		cout<<"\n What you want to do?\n";
		cout<<"\n 1.GIVE INPUT 2.ADD 3.SUBSTRACT 0.TO EXIT:\t";
		cin>>ch;
		
		if(ch==0)
			break;
			
		switch(ch){
			case 1:
				complex1.input();
				complex2.input();
				break;
			case 2:
				complex3.addition();
				cout<<"\nAddition of two given complex number is: "<<complex3.re;
				if(complex3.im < 0)
					cout<<"-i"<<fabs(complex3.im)<<endl;
				else if(complex3.im > 0)
					cout<<"+i"<<complex3.im<<endl;
				else
					cout<<endl;
					break;
			case 3:
				complex3.subtraction();
				cout<<"\nSubtraction of two given complex number is: "<<complex3.re;
				if(complex3.im < 0)
					cout<<"-i"<<fabs(complex3.im)<<endl;
				else if(complex3.im > 0)
					cout<<"+i"<<complex3.im<<endl<<endl;
				else 
					cout<<endl;
				
				cout<<endl;
				break;
			}
		}
	return 0;
}
