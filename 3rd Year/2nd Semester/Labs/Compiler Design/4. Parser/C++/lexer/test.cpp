#include <bits/stdc++.h>
#include <cstring>
#include "tokenseparator.cpp"

bool iscmnt;

bool IsSymbol(char s1)
{
	string s(1,s1);

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

bool IsSymbol(string s)
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


/**********************************Token splitting*************************************/

vector<string> startSplitting(string s,bool* iscmnt)
{

	vector<string> tokens;
	bool sf=false;
	int i=0;
	while(s[i]==' ' || s[i]=='\t')
		i++;

	string x="";

	for(;i<s.size() ;i++)
	{

		if(*iscmnt==true)
		{
			if(s[i]=='*' && s[i+1]=='/')
			{
				*iscmnt=false;
				i++;
			}

		}

		else
		{

			if((s[i]==' '|| s[i]=='\t') )
			{
				if(*iscmnt==false)
				tokens.push_back(x);
				x="";

				while(i<s.size() && ( s[i]==' ' || s[i]=='\t'))
					i++;
				if(i<s.size())

					if(s[i]=='/' && s[i+1]=='/')
					{
						return tokens;
					}

					else if(s[i]=='/'&& s[i+1]=='*')
					{
						*iscmnt=true;
						i++;
					}

					else
					x+=s[i];
			}

			else if(IsSymbol(s[i]))
			{

				if(s[i]=='/')
				{
					if(s[i+1]=='/')
					{
						return tokens;
					}

					else if(s[i+1]=='*')
					{
						tokens.push_back(x);
						x="";
						*iscmnt=true;
						i++;

					}

				}
				if(!IsSymbol(x) && *iscmnt==false)
				{
					tokens.push_back(x);
					x="";
					x+=s[i];
					i++;
				}



				while(IsSymbol(s[i]) && *iscmnt==false)
				{
					if(s[i]=='/' && s[i+1]=='/')
					{
						return tokens;
					}

					else if(s[i]=='/' && s[i+1]=='*')
					{
						tokens.push_back(x);
						x="";
						*iscmnt = true;
						i++;
					}

					else
					{
						string y=x;
						y+=s[i];
						if(IsSymbol(y))
						x+=s[i];
						else
						break;
						i++;
					}
				}

				if(*iscmnt == false)
				{
					tokens.push_back(x);
				}
				x="";

				if(i<s.size() && *iscmnt==false)
				{
					x+=s[i];

				}

			}
			else
			{
				string y=x;
				if(IsSymbol(y))
				{
					tokens.push_back(x);
					x="";
				}

				x+=s[i];
			}

		}

	}
	if(*iscmnt==false)
		tokens.push_back(x);
	return tokens;
}




/*************************************************MAIN FUNCTION*******************************/


int main()
{
	string s;
    ofstream fout;
    ifstream infile;
    infile.open("Sample.c",ios :: in);
    fout.open("database.txt",ios :: out);

    iscmnt=false;
	int lnum=0;

	while(getline(infile,s))
	{

		cout<<"Line Read : "<<s<<"\n";
		vector<string> tokens;
		tokens.clear();

		tokens=startSplitting(s,&iscmnt);


		 for(int i=0;i<tokens.size();i++)
		 {

		 	token* t=new token(lnum+1,tokens[i]);
		 	fout.write((char*)t,sizeof(token));

		 }

	 if(infile.peek()==EOF) break;
	 lnum++;
	}

	infile.close();
	fout.close();
	ifstream fin;
	fin.open("database.txt",ios :: in);

	cout<<"\t\tLINE NO\t|\t"<<"TOKEN ID\t|\t"<<"TOKEN"<<"\t|\t"<<"TYPE\n";
	cout<<"-----------------------------------------------------------------------------\n";


	while(true)
	{
		token *t1=new token();
		fin.read((char*)t1,sizeof(token));
		cout<<"\t\t"<<t1->returnlineno()<<"\t|\t"<<rand()%500+200<<"\t|\t"<<t1->returnsym()<<"\t|\t"<<t1->returntype()<<"\n";
		cout<<"--------------------------------------------------------------------------\n";

		if(fin.peek()==EOF) break;
	}


	cout<<"\n";

	fin.close();
}
