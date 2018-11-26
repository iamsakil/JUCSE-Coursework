#include <iostream>
#include <fstream>
#include <string>
using namespace std;



class token
{
	int lineno;
	string sym;
	char type;
	string KeywordDatafile;
	public:
	token(int lnum,string symb)
	{
		KeywordDatafile="keyword.txt";
		lineno=lnum;
		sym = symb;
		type=checktype(sym);
	}

	token(int lnum,char symb[])
	{
		lineno=lnum;
		sym = string(symb);
		type=checktype(sym);
	}

	char checktype(string sym);

	int returnlineno(){return lineno;} 

	string returnsym(){return sym;}

	string returntype()
	{
		if(type=='i'){return "Integer";}
		else if(type=='s'){return "Symbol";}
		else if(type=='k'){return "Keyword";}
		else {return "Token";}

	}

	bool isInteger(string s);
	bool isKeyword(string s);
	bool isSymbol(string s);
	int prefixesOf();

};

bool token :: isSymbol(string s)
{
	ifstream fin;
	bool flag=false;
	string temkey;
	fin.open("symbol.txt",ios::in );

	while(!fin.eof())
	{
		getline(fin,temkey);
		if(s==temkey)
		{
			flag=true;
			break;
		}
	}

	fin.close();
	return flag;
}

int token :: prefixesOf()
{
	ifstream fin;
	string temkey,s=sym;
	int cnt=0;
	fin.open("symbol.txt",ios::in );
	while(!fin.eof())
	{
		int i;
		getline(fin,temkey);
		for(i=0;i<s.size();i++)
			if(s[i]!=temkey[i])
				break;
		if(i==s.size())
			cnt++;
	}

	fin.close();
	return cnt;
}

bool token:: isKeyword(string s)
{
	ifstream fin;
	bool flag=false;
	string temkey;
	fin.open("keyword.txt",ios::in );

	while(!fin.eof())
	{
		getline(fin,temkey);
		if(s==temkey)
		{
			flag=true;
			break;
		}
	}

	return flag;
}


bool token:: isInteger(string s)
{
	int i;
	if(s[0]!='-' || s[0]!='+' || s[0]<'0' || s[0]>'9')
		return false;
	for(i=1;i<s.size() && s[i]>='0' && s[i]<='9' ;i++);

	return i==s.size();
}



char token :: checktype(string sym)
{
	char tp;
	int num;
	if(isSymbol(sym))
	{
		tp = 's';
	}

	else if (isInteger(sym))
	{
		tp='i';
	}

	else if (isKeyword(sym))
	{
		tp='k';
	}

	else
	{
		tp='v';
	}
	return tp;
}

