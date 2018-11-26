#include <iostream>
#include <string.h>
#include <ctype.h>
#include <cstdlib>
#include <string>
#define  MAX 5000
using namespace std;
class infixtopostfix
{

		char postfixstring[MAX], stack[MAX] ;
		char *s, *t ;
		int top ;
	public :
		infixtopostfix() ;
		void setexpr(char *str) ;
		void push(char c) ;
		char pop() ;
		void convert() ;
		int priority (char c) ;
		string show() ;
		void printstack(){for(int i=0;i<top;i++) cout<<stack[i]<<" "; cout<<"\n";}
		
		
} ;
infixtopostfix :: infixtopostfix()
{
	top = -1 ;
	// strcpy (postfixstring,"") ;
	// strcpy (stack,"") ;
	postfixstring[0]=0;
	stack[0]=0;
	t = postfixstring ;
	s = ""  ;
}
void infixtopostfix :: setexpr ( char *str )
{
	s = str ;
	int k=0;
	char s1[5000];
	for(int i=0;i<strlen(str);i++)
	{
		if(str[i]=='*')
		{
			s1[k++]=str[i];
			s1[k++]='P';
		}
		
		else
		{
			s1[k++]=str[i];
		}
	}
	
	s1[k]='\0';
	strcpy(s,s1);

//	cout<<s<<"\n";
}
void infixtopostfix :: push ( char c )
{
	if ( top == MAX );
	//	cout << "\nStack is full\n" ;
	else
	{
		top++ ;
		stack[top] = c ;
	}
}
char infixtopostfix :: pop( )
{
	if ( top == -1 )
	{
	//	cout << "\nStack is empty\n" ;
		return -1 ;
	}
	else
	{
		char item = stack[top] ;
		top-- ;
		return item ;
	}
}


void infixtopostfix :: convert( )
{
	while ( *s )
	{
	//	cout<<"Next Char :"<<(*s)<<"\n";
	  //  printstack();
	  //  cout<<"Next Char :"<<(*s)<<"\n";
		if ( *s == ' ' || *s == '\t' )
		{
			s++ ;
			continue ;
		}
		if ( isdigit ( *s ) || isalpha ( *s ) )
		{
			while ( isdigit ( *s ) || isalpha ( *s ) )
			{
				*t = *s ;
				s++ ;
				t++ ;
				if(!(*s || *t))
					break;
			}
		}
		if ( *s == '(' )
		{
			push ( *s ) ;
			s++ ;
		}
		char opr ;
		if ( *s=='*' || *s == '+' || *s == '/' || *s == '%' || *s == '-' || *s == '$' || *s=='|' )
		{
			if ( top != -1 )
			{
				opr = pop() ;
			//	cout<<"Popped Operator : "<<opr;
				while ( priority ( opr ) >= priority ( *s )  )
				{
				
					*t = opr ;
					t++ ;
					opr = pop( ) ;
					
				}
				push ( opr ) ;
				push ( *s ) ;
			
			}
			else
				push ( *s ) ;
				
			s++ ;
		}
		
	
		if ( *s == ')' )
		{
			opr = pop( ) ;
			while ( ( opr ) != '(' )
			{
				*t = opr ;
				t++ ;
				opr =  pop( ) ;
			}
			s++ ;
		}
	}
	while ( top != -1 )
	{
		char opr = pop( ) ;
		*t = opr ;
		t++ ;
	}
	*t = '\0' ;
}
int infixtopostfix :: priority ( char c )
{
	if ( c == '$' )
		return 4 ;
	if(c=='*')
		return 3;
    /*	if (  c == '/' || c == '%' )
		return 3 ;*/
	else
	{
		if ( c == '+' || c == '-' )
			return 2 ;
		if(c =='|')
		{
			return 1;
		}
		else
			return 0 ;
	}
}
string infixtopostfix :: show()
{
	char pfixexpr[5000];
	int k=0;
	for(int i=0;i<strlen(postfixstring);i++)
	{
		if(postfixstring[i]!='P')
		{
			pfixexpr[k++]=postfixstring[i];
		}
	}
	pfixexpr[k]='\0';

	int i=0;
	
	for(i=0;pfixexpr[i];i++)
	{
		if(pfixexpr[i]=='|' || pfixexpr[i]=='*' || pfixexpr[i]=='+' ||(pfixexpr[i]>='a' && pfixexpr[i]<='z') || (pfixexpr[i]>='A' && pfixexpr[i]<='Z') || (pfixexpr[i]>='0' && pfixexpr[i]<='9'))
			continue;
		else
			break;
	}
	pfixexpr[i]=0;
	cout<<pfixexpr<<" yo"<< endl;
	return string(pfixexpr);
	// cout<<pfixexpr;
	// cout << endl ;
}

string get_postfix(string regex)
{
	int i;
	// return regex;
	// char expr[MAX] ;
	infixtopostfix *q=new infixtopostfix() ;
 
	// cout << "\nEnter an expression in infix form:\n  | for 'or' \n * for 'closure'\n + for 'concatenation' \n> " ;
	// cin.getline (expr, MAX) ;
 	char * expr=(char*)malloc(sizeof(char)*(regex.size()+1));
 	for(i=0;i<regex.size();i++)
 		expr[i]=regex[i];
 	expr[i]=0;
	q->setexpr (expr) ;
	q->convert() ;
 
	// cout << "\nThe postfix expression is: " ;
	return(q->show());
}