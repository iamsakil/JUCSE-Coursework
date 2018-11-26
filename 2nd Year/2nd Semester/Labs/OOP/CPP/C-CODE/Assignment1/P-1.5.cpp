#include<iostream>
#include<new>
#include<cstdlib>
using namespace std;
class array{
	int *ptr;
	int size;
	public:
		array(int sz,int n=0)
		{
			int i;
			try{
				ptr=new int[sz];
			}
			catch(bad_alloc xa){
				cout<<"MEMORY ALLOCATION UNSUCCESSFUL\n\n";
				exit(EXIT_FAILURE);
			}
			for(i=0;i<sz;i++)
				ptr[i]=n;
			size=sz;
		}
		~array(){
			delete [] ptr;
		}
		array(const array &a)
		{
			int i;
			try{
				ptr=new int[a.size];
			}
			catch(bad_alloc xa){
				cout<<"MEMORY ALLOCATION UNSUCCESSFUL\n\n";
				exit(EXIT_FAILURE);
			}
			for(i=0;i<a.size;i++){
				this->ptr[i]=a.ptr[i];	
			}
			size = a.size;
		}
		array(const int *a,int n)
		{
			int i;
			try{
				ptr=new int[n];
			}
			catch(bad_alloc xa){
				cout<<"MEMORY ALLOCATION UNSUCCESSFUL\n\n";
				exit(EXIT_FAILURE);
			}
			for(i=0;i<n;i++){
				ptr[i] = a[i];
			}
			size = n;
		}
		array operator+(array &b)
		{
			cout<<b.size<<endl;
			array c(size);
			int i;
			for(i=0;i<size;i++)
			{
				c.ptr[i]=ptr[i]+b.ptr[i];
			}
			return c;	
		}
		array operator=(array b)
		{
			int i;
			for(i=0;i<this->size;i++)
				this->ptr[i]=b.ptr[i];
			return *this;	
		}
		int &operator[](int i)
		{
			if(i<0 || i>this->size)
			{
				cout<<"\n INDEX IS NOT WITHIN PERMISSIBLE RANGE\n";
				exit(1);
			}
			return this->ptr[i];
		}
		void input()
		{
			int i;
			cout<<"Enter the numbers:";
			for(i=0;i<size;i++)
			{
				cin>>ptr[i];
			}
		}
		void show()
		{
			int i;
			cout<<"\n\n ARRAY SIZE: "<<size<<endl;
			for(i=0;i<size;i++)
			{
				cout<<ptr[i]<<endl;
			}
		}
		friend array operator*(array &a,int n)
		{
			int i;
			cout<<"array*n in this:"<<a.size<<endl;
			array c(a.size);
			for(i=0;i<a.size;i++)
			{
				c.ptr[i]=n*a.ptr[i];
			}
			return c;
		}
		friend array operator*(int n,array &a)
		{
			int i;
			cout<<" n*array in this:"<<a.size<<endl;
			array c(a.size);
			for(i=0;i<a.size;i++)
			{
				c.ptr[i]=n*a.ptr[i];
			}
			return c;
		}
		friend int min(int a,int b)
		{
			if(a<=b)
				return 0;
			else
				return 1;
		}
};

int main()
{
	int choice;
	while(1)
	{
		cout<<"\n-------------------------List of options-----------------------------\n\n";
    	cout<<endl<<"\t1.CREATE AN ARRAY OBJECT\n\n\t2.CREATE AND INITIALIZE AN ARRAY OBJECT WITH ANOTHER\n\n\t3.INITIALIZATION WITH C ARRAY\n\n";
		cout<<"\t4.ADD TWO OBJECTS\n\n\t5.ASSIGN WITH ANOTHER OBJECT\n\n\t6.RETURN iTH VALUE OF ARRAY\n\n\t7.MULTIPLICATION WITH A CONSTANT\n\n\t0.TO EXIT\n";
    	cout<<"\n\n---------------------------------------------------------------------\n\n";
        cout<<endl<<"Enter your choice: ";
		cin>>choice;
		if(choice==0)
            break;
		switch(choice)
		{
			case 1: {
						int size,n;
						char ch;
						cout<<"\n ENTER SIZE OF THE ARRAY: ";
						cin>>size;
						cout<<"\n\n REQIURE INITIALIZATION?? [y/n] (DEFAULT INITIALIZATION WITH ZERO): ";
						cin>>ch;
						if(ch=='y'||ch=='Y')
						{
							cout<<"\n\nEnter the number to initialize with: ";
							cin>>n;
							array a(size,n);
							a.show();
						}
						else if(ch=='n'||ch=='N')
						{
							array a(size);
							a.show();
						}
						else
							cout<<"\n\n WRONG CHOICE\n";
					}	
						break;
			case 2: { 
						int size2;
						cout<<"ENTER ARRAY SIZE: ";
						cin>>size2;
						array m(size2);
						m.input();
						array b(m);
						cout<<"\n\nSHOWING M:";
						m.show();
						cout<<"\n\nSHOWING B:";
						b.show();
					}
						break;
			case 3:	{
						int sz,k;
						cout<<"\n\nENTER SIZE OF STANDARD C ARRAY: ";
						cin>>sz;
						int ar[sz];
						cout<<"\n\n NOW ENTER THE ELEMENTS: ";
						for(k=0;k<sz;k++)
						cin>>ar[k];
						cout<<"INITIALIZING WITH A ARRAY\n\n";
						array z(ar,sz);
						cout<<"\n\nSHOWING C:";
						z.show();
					}
						break;
			case 4:	{
						int size3,n3;
						cout<<"\n\nENTER ARRAY SIZE: ";
						cin>>size3;
						array d(size3);
						d.input();
						d.show();
						array e(size3);
						e.input();
						e.show();
						array f(size3); 
						f=d+e;
						cout<<"SHOWING RESULT:\n";
						f.show();
					}
						break;
			case 5:	{						
						int size4;
						cout<<"\n\n ENTER ARRAY SIZE: ";
						cin>>size4;
						array a(size4);
						a.input();
						a.show();
						cout<<"Creating an object and assigning it with a...\n";
						array g(size4);
						cout<<"\n\nSHOWING INITIAL G:\n";
						g.show();
						g=a;
						cout<<"\n\nSHOWING NEW G:\n";
						g.show();
					}
						break;
			case 6: {
						int size,q;
						cout<<"\n\n ENTER ARRAY SIZE: ";
						cin>>size;
						array h(size);
						h.input();
						h.show();
						cout<<"ENTER THE INDEX i:";
						cin>>q;
						cout<<h[q]<<endl;
					}
						break;
			case 7: {
						int size,q,r;
						char c;
						cout<<"\n\nENTER ARRAY SIZE: ";
						cin>>size;
						array l(size);
						l.input();
						l.show();
						cout<<"\n\nENTER THE NUMBER TO MULTIPLY WITH: ";
						cin>>q;
						cout<<"\n\n\t1.ARRAY*C\t2.C*ARRAY\n\n";
						cout<<"Enter Your Choice:";
						cin>>r;
						if(r==1)
						{
							l=q*l; 
							cout<<"RESULT:\n";
							l.show();
						}
						else if(r==2)
						{
							l=l*q;
							cout<<"RESULT:\n";
							l.show();
						}
						else
							cout<<"\n\nWRONG CHOICE!!!!\n\n";
					}	
						break;
			default:
				cout<<"\n ENTER CORRECTLY\n\n FOLLOW THE GIVEN OPTIONS PLEASE\n\n";			
		}
	}
}
