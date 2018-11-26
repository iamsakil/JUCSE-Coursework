#include <bits/stdc++.h>
#include <cstring>
#include "tokenseparator.cpp"
#include "dfa.cpp"
class Lexer
{
	bool iscmnt;
	char* filename;
	// vector<string> symtab;
	vector<token> tok;
	set<string> symtab;
	Dfa *id_regex;
	Dfa *num2_regex;
	Dfa *num_regex;
	public:

	Lexer(char* filename)
	{
		this->filename=filename;
		set_regexes();
	}

	void set_regexes()
	{
		// num_regex=Dfa("(0|1|2|3|4|5|6|7|8|9)+(0|1|2|3|4|5|6|7|8|9)*");
		
		// id_regex=Dfa("(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)+(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)*");
		// id_regex=new Dfa("ab|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|ab|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*+");
		// id_regex->createDfa();

		// num_regex=new Dfa("01|2|3|4|5|6|7|8|9|01|2|3|4|5|6|7|8|9|*+");
		// num_regex->createDfa();

		// id_regex=Dfa("(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)+(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)*");
		// id_regex=Dfa("(0|1|2|3|4|5|6|7|8|9)+(0|1|2|3|4|5|6|7|8|9)*");
		// id_regex.createDfa();
		// cout<<id_regex->check_expression("12345av")<<" "<<id_regex->check_expression("1234")<<" "<<id_regex->check_expression("abc")<<endl;
		// cout<<num_regex->check_expression("12345av")<<" "<<num_regex->check_expression("1234")<<" "<<num_regex->check_expression("abc")<<endl;

	}
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

	void startLexer()
	{
		string s;
	    ofstream fout;
	    ifstream infile;
	    infile.open(filename,ios :: in);
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
		
		cout<<"\t\tLINE NO\t|\t"<<"TOKEN\t|\t"<<"TYPE\n";
		cout<<"----------------------------------------------------------------\n";


		while(true)
		{
			token *t1=new token();
			fin.read((char*)t1,sizeof(token));
			cout<<"\t\t"<<t1->returnlineno()<<"\t|\t"<<t1->returnsym()<<"\t|\t"<<t1->returntype()<<"\n";
			cout<<"----------------------------------------------------------------\n";	
			if(t1->returnsym().size()!=0 )
			{
				tok.push_back(*t1);
			}
			if(t1->returntype()=="id" && t1->returnsym().size()!=0)
				symtab.insert(t1->returnsym());

			if(fin.peek()==EOF) break;
		}


		cout<<"\n";

		fin.close();

		for(int i=0;i<tok.size();i++)
			cout<<tok[i].returnsym()<<endl;
		for(set<string>::iterator it=symtab.begin();it!=symtab.end();++it)
			cout<<"~ "<<*it<<endl;
	}
};



/*************************************************MAIN FUNCTION*******************************/


int main()
{
	Lexer L=Lexer("Sample.c");
	// return 0;
	L.startLexer();
}