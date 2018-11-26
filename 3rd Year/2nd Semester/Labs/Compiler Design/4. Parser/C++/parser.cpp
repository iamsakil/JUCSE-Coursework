#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <stack>
#include <fstream>
using namespace std;
class term
{
	private:
	string name;
	bool is_term;
	bool isEpsilon;
	vector<vector<string> > P;
	int prod_num;
	public:
		term(string name,bool is_term)
		{
			this->name=name;
			this->is_term=is_term;
			isEpsilon=(name=="eps");
			prod_num=-1;
			// producesEpsilon=false;
			startNew();
		}

		bool isEmpty()
		{
			return P[0].size()==0;
		}

		bool givesEpsilon()
		{
			if(!is_term)
				return name=="eps";
			else
			{
				for(int i=0;i<P.size();i++)
				{
					if(P[i].size()==1 && P[i][0]=="eps")
						return true;
				}
				return false;
			}
		}
		vector<vector<string> >& getProductions()
		{
			return P;
		}

		vector<string>& getProduction(int j)
		{
			return P[j];
		}
		
		void setProductions(vector<vector<string> > &v)
		{

			P.clear();
			for(int i=0;i<v.size();i++)
				P.push_back(v[i]);
			prod_num=P.size()-1;
		}

		string getName()
		{
			return name;
		}


		void print();
		void print(int n);
		void addToCurrent(term &t);
		void addToCurrent(string s);
		void startNew();

};

void term :: addToCurrent(term &t)
{
	P[prod_num].push_back(t.getName());
}

void term :: addToCurrent(string s)
{
	P[prod_num].push_back(s);
}

void term :: startNew()
{
	prod_num++;
	P.push_back(vector<string>());
}

void term :: print()
{
	int i,j;
	cout<<name<<" -> ";
	for(i=0;i<=prod_num;i++)
	{
		for(j=0;j<P[i].size();j++)
			cout<<P[i][j]<<" ";
		if(i<prod_num)
			cout<<" | ";
	}
	cout<<endl;
}

void term :: print(int n)
{
	int i,j;
	cout<<name<<" -> ";
	i=n;

	for(j=0;j<P[i].size();j++)
		cout<<P[i][j]<<" ";
	
}

class TopDownParser
{
	vector<term> nt;
	vector<term> t;
	vector<set<string> > FIRST;
	vector<set<string> > FOLLOW;
	vector<vector<pair<int,int> > > TABLE;
	map<string,int> MNT;
	map<string,int> MT;

	public:

	int isTerminal(string s)
	{
		if(MT.find(s)!=MT.end())
			return 1;
		return 0;
	}

	int isNonTerminal(string s)
	{
		if(MNT.find(s)!=MNT.end())
			return 1;
		return 0;
	}

	TopDownParser(vector<term> &nt,vector<term> &t)
	{
		this->nt=nt;
		this->t=t;
		int i;
		for(i=0;i<nt.size();i++)
			MNT[nt[i].getName()]=i;
		for(i=0;i<t.size();i++)
			MT[t[i].getName()]=i;
	}

	set<string> getFirst(vector<string> &s)
	{
		set<string> ST;
		for(int i=0;i<s.size();i++)
		{
			set<string> tmp=getFirst(s[i]);
			for(set<string>::iterator it=tmp.begin();it!=tmp.end();++it)
				ST.insert(*it);
			if(tmp.find("eps")==tmp.end())
				break;
		}
		return ST;
	}

	void addToTable(string rowNonTerminal,string columnTerminal,pair<int,int> pIndex)
	{
		int i,j;

		if(MNT.find(rowNonTerminal)==MNT.end())
		{
			cout<<rowNonTerminal<<" not found"<<endl;
			return;
		}


		if(MT.find(columnTerminal)==MT.end())
		{
			cout<<columnTerminal<<" not found "<<endl;
			return;
		}

		i=MNT[rowNonTerminal];
		j=MT[columnTerminal];
		if(TABLE[i][j].first!=-1 && TABLE[i][j].second!=-1)
		{
			cout<<"ERROR"<<endl;
			nt[TABLE[i][j].first].print(TABLE[i][j].second);
			cout<<endl;
			cout<<"--------------"<<endl;
			nt[pIndex.first].print(pIndex.second);

		}
		TABLE[i][j]=pIndex;
		return;
	}

	void constructTable()
	{
		int i,j,k;
		TABLE.resize(nt.size());
		for(i=0;i<TABLE.size();i++)
			TABLE[i].resize(t.size());

		for(i=0;i<TABLE.size();i++)
			for(j=0;j<TABLE[i].size();j++)
				TABLE[i][j].first=TABLE[i][j].second=-1;
		for(i=0;i<nt.size();i++)
		{
			vector<vector<string> > P=nt[i].getProductions();
			for(j=0;j<P.size();j++)
			{
				set<string> first=getFirst(P[j]);
				for(set<string>::iterator it=first.begin();it!=first.end();++it)
				{
					if(*it=="eps")
						continue;
					// cout<<"Added "<<nt[i].getName()<<"\t"<<*it<<endl;
					// cout<<i<<"\t"<<j<<endl;
					addToTable(nt[i].getName(),*it,make_pair(i,j));
				}
				// if(nt[i].getName()=="E'" && P[j][0]=="eps")
				// 	cout<<"Squeak"<<"\t"<<first.size()<<"\t"<<*first.begin()<<endl;
				if(first.find("eps")==first.end())
					continue;

				set<string> &follow=FOLLOW[i];
				for(set<string>::iterator it=follow.begin();it!=follow.end();++it)
				{
					// cout<<"Added "<<nt[i].getName()<<"\t"<<*it<<endl;
					// cout<<i<<"\t"<<j<<endl;

					addToTable(nt[i].getName(),*it,make_pair(i,j));
				}
			}
		}
		return;
	}

	set<string> getFirst(string s)
	{
		if(isTerminal(s))
		{
			set<string> st;
			st.insert(s);
			return st;
		}
		else if(isNonTerminal(s))
		{
			return FIRST[MNT[s]];
		}
		return set<string>();
	}

	void unionFirst(string s,set<string> &ST)
	{
		if(isTerminal(s))
		{
			if(s!="eps")
				ST.insert(s);
			return;
		}
		else if(isNonTerminal(s))
		{
			for(set<string>::iterator it=FIRST[MNT[s]].begin();it!=FIRST[MNT[s]].end();++it)
			{
				if(*it!="eps")
					ST.insert(*it);
			}
			return;
		}
	}
	set<string> getFollow(string s)
	{
		if(isNonTerminal(s))
			return FOLLOW[MNT[s]];
		return set<string>();
	}


	void calculateFollow(string start)
	{
		int i,j,k;
		FOLLOW.resize(nt.size());
		FOLLOW[MNT[start]].insert("$");
		bool added;
		int prod=100000;
		do
		{
			added=false;
			
			/*RULE 1*/
			
			for(i=0;i<nt.size();i++)
			{
				vector<vector<string> > P=nt[i].getProductions();
				// cout<<nt[i].getName()<<endl;
				for(j=0;j<P.size();j++)
				{
					set<string> ST;
					for(k=P[j].size()-1;k>=1;k--)
					{
						set<string> temp=getFirst(P[j][k]);
						if(temp.find("eps")==temp.end())
							ST.clear();

						unionFirst(P[j][k],ST);
						string var=P[j][k-1];
						if(isTerminal(var))
							continue;
						for(set<string>::iterator it=ST.begin();it!=ST.end();++it)
						{
							if(FOLLOW[MNT[var]].find(*it)==FOLLOW[MNT[var]].end())
							{
								// cout<<"Added "<<*it <<" to "<<var<<endl;
								FOLLOW[MNT[var]].insert(*it);
								added=true;
							}
						}
					}
				}
			}
			
			/*RULE 2*/
			for(i=0;i<nt.size();i++)
			{
				vector<vector<string> > P=nt[i].getProductions();
				for(j=0;j<P.size();j++)
				{
					set<string> ST;
					for(k=P[j].size()-1;k>=0;k--)
					{
						string var=P[j][k];
						// cout<<P[j][k]<<" * "<<endl;
						if(isNonTerminal(var))
						{
							for(set<string>::iterator it=FOLLOW[i].begin();it!=FOLLOW[i].end();++it)
							{
								// if(nt[i].getName()=="declaration_list" && var)
								if(FOLLOW[MNT[var]].find(*it)==FOLLOW[MNT[var]].end())
								{
									// cout<<"Added "<<*it <<" to "<<var<<" in production "<<nt[i].getName()<<endl;
									FOLLOW[MNT[var]].insert(*it);
									added=true;
								}
							}
						}
						set<string> temp=getFirst(var);
						if(temp.find("eps")==temp.end())
							break;
					}
				}
			}

		}while(added);
	}
	void calculateFirst()
	{
		int i,j,k;
		FIRST.resize(nt.size());
		bool added;
		do
		{
			added=false;
			for(i=0;i<nt.size();i++)
			{
				vector<vector<string> > P=nt[i].getProductions();
				for(j=0;j<P.size();j++)
				{
					for(k=0;k<P[j].size();k++)
					{
						if(isTerminal(P[j][k]))
						{
							if(FIRST[i].find(P[j][k])==FIRST[i].end())
							{
								FIRST[i].insert(P[j][k]);
								added=true;
							}
							if(P[j][k]!="eps")
								break;
						}
						else
						{
							set<string> &ST=FIRST[MNT[P[j][k]]];
							for(set<string>:: iterator it=ST.begin();it!=ST.end();++it)
							{
								if(FIRST[i].find(*it)==FIRST[i].end())
								{
									FIRST[i].insert(*it);
									added=true;
								}
							}
							if(ST.find("eps")==ST.end())
								break;
						}
					}
					if(k==P[j].size())
						FIRST[i].insert("eps");
				}
			}
		}while(added);
	}

	void printFirst()
	{
		for(int i=0;i<nt.size();i++)
		{
			set<string> &ST=FIRST[i];
			cout<<nt[i].getName()<<" : ";
			// cout<<ST.size();
			for(set<string>:: iterator it=ST.begin();it!=ST.end();++it)
				cout<<*it<<" ";
			cout<<endl;
		}
	}

	void printFollow()
	{
		for(int i=0;i<nt.size();i++)
		{
			set<string> &ST=FOLLOW[i];
			cout<<nt[i].getName()<<" : ";
			for(set<string>:: iterator it=ST.begin();it!=ST.end();++it)
				cout<<*it<<" ";
			cout<<endl;
		}
	}

	void printTable()
	{
		int i,j;
		// for(j=0;j<t.size();j++)
		// {
		// 	if(t[j].getName()=="eps")
		// 		continue;
		// 	cout<<"\t\t"<<t[j].getName();
		// }
		// cout<<endl;

		for(i=0;i<TABLE.size();i++)
		{
			// cout<<nt[i].getName()<<"\t\t";
			for(j=0;j<TABLE[i].size();j++)
			{
				int x,y;
				x=TABLE[i][j].first;
				y=TABLE[i][j].second;
				if(x>=0 && y>=0)
				{
					// vector<vector<string> > P=nt[x].getProductions();
					cout<<nt[i].getName()<<","<<t[j].getName()<<"\t";
					nt[x].print(y);
					cout<<endl;
				}
				else
				{
					;
					// cout<<"-";
				}
				// cout<<"\t\t";
			}
			// cout<<endl;
		}
	}

	void setMaps()
	{
		for(int i=0;i<nt.size();i++)
		{
			// cout<<nt[i].getName()<<endl;
			MNT[nt[i].getName()]=i;
		}

		for(int i=0;i<t.size();i++)
		{
			// cout<<t[i].getName()<<endl;
			MT[t[i].getName()]=i;
		}
	}
	void printProductions()
	{
		for(int i=0;i<nt.size();i++)
			nt[i].print();
	}

	void leftRecursion()
	{
		int n=nt.size();
		int i,j,k,t1,t2;
		for(i=0;i<n;i++)	//standard Algo
		{
			for(j=0;j<i;j++)
			{
				vector<vector<string> > vi=nt[i].getProductions();
				vector<vector<string> > vj=nt[j].getProductions();
				vector<vector<string> > newP;
				for(k=0;k<vi.size();k++)
				{
					if(vi[k][0]!=nt[j].getName())
					{
						newP.push_back(vi[k]);
					}
					else
					{
						for(t1=0;t1<vj.size();t1++)
						{
							newP.push_back(vector<string>());

							for(t2=0;t2<vj[t1].size();t2++)
								newP[newP.size()-1].push_back(vj[t1][t2]);
							for(t2=1;t2<vi[k].size();t2++)
								newP[newP.size()-1].push_back(vi[k][t2]);
						}
					}
				}
				nt[i].setProductions(newP);
			}
			immediateRecursion(i);
		}
	}
	
	void immediateRecursion(int v)
	{
		if(nt[v].isEmpty())
		{
			cout<<"Yo";	
			return;
		}
		vector<vector<string> > P=nt[v].getProductions();
		//original list of productions
		int i,j;	
		vector<int> imm;
		for(i=0;i<P.size();i++)
		{
			if(P[i][0]==nt[v].getName())	//identify immediate left recursion elements
			{
				imm.push_back(i);
			}
		}

		if(imm.size()==0)	//nothing to be removed
			return;

		term A=term(nt[v].getName()+"\'",true);	//create new production A' from A

		for(i=0;i<imm.size();i++) //stuff
		{
			for(j=1;j<P[i].size();j++)
				A.addToCurrent(P[i][j]);
			A.addToCurrent(A);
			A.startNew();
		}

		A.addToCurrent(string("eps"));	//epsilon stuff
		nt.push_back(A);				//add the new term
		vector<vector<string> > newP;
		//create an altogether new set of productions
		for(i=0;i<P.size();i++)
		{
			if(P[i][0]==nt[v].getName())
				continue;
			newP.push_back(vector<string>());
			for(j=0;j<P[i].size();j++)
			{
				if(P[i][j]!="eps")
					newP[newP.size()-1].push_back(P[i][j]);
			}
			newP[newP.size()-1].push_back(A.getName());
		}

		nt[v].setProductions(newP);		//set it

	}

	void predictiveParsing(string start,vector<string> &inp)
	{
		stack<string> S;
		S.push("$");
		S.push(start);
		int a=0;
		// cout<<inp[a]<<endl;
		while(S.top()!="$")
		{
			// cout<<S.top()<<endl;
			if(S.top()==inp[a])
			{
				// cout<<"yo";
				cout<<"Match "<<inp[a]<<endl;
				S.pop();
				a++;
			}
			else if(isTerminal(S.top()))
			{
				// cout<<"yo";

				cout<<"ERROR!"<<endl;
				return;
			}
			else 
			{
				int i=MNT[S.top()];
				int j=MT[inp[a]];
				int x=TABLE[i][j].first;
				int y=TABLE[i][j].second;
				if(x==-1 && y==-1)
				{
					cout<<"ERROR!"<<endl;
					return;
				}
				nt[x].print(y);
				cout<<endl;
				// cout<<"yo";
				vector<string> P=nt[x].getProduction(y);
				S.pop();
				for(int j=P.size()-1;j>=0;j--)
					if(P[j]!="eps")
						S.push(P[j]);
			}
		}
		return;
	}

};


void readFromfile(char * filename)
{
	int i,j;
	ifstream fin;
	fin.open(filename,ios::in);
	set<string> ST;
	string s;
	vector<term> nt;
	vector<term> t;
	vector<string> inp;
	vector<int> strt;
	while(!fin.eof())
	{
		fin>>s;
		inp.push_back(s);
		if(s=="->")
		{
			term T=term(inp[inp.size()-2],false);
			nt.push_back(T);
			strt.push_back(inp.size()-2);
		}

		if(s!="|" && s!="->")
			ST.insert(s);
	}
	for(i=0;i<nt.size();i++)
		ST.erase(nt[i].getName());
	ST.erase("eps");
	ST.erase("$");
	for(set<string>::iterator it=ST.begin();it!=ST.end();++it)
		t.push_back(term((*it),true));
	t.push_back(term("eps",true));
	t.push_back(term("$",true));
	// for(i=0;i<nt.size();i++)
	// 	cout<<nt[i].getName()<<endl;
	// for(i=0;i<t.size();i++)
	// 	cout<<t[i].getName()<<endl;
	for(i=0;i<strt.size();i++)
	{
		int b=strt[i]+2;
		int e=((i+1)<strt.size())?strt[i+1]:inp.size();
		for(j=b;j<e;j++)
		{
			if(inp[j]=="|")
				nt[i].startNew();
			else
				nt[i].addToCurrent(inp[j]);
		}
	}
	// cout<<"YOoooooooooooo"<<endl;
	// cout<<nt.size()<<endl;
	// for(i=0;i<nt.size();i++)
	// {
	// 	cout<<"Hey"<<endl;
	// 	nt[i].print();
	// }
	TopDownParser TP=TopDownParser(nt,t);

	TP.printProductions();
	TP.leftRecursion();
	cout<<endl<<endl;
	cout<<endl<<"Printing productions after removing left recursion"<<endl<<endl;
	TP.printProductions();
	TP.setMaps();
	// cout<<TP.isNonTerminal("E'")<<endl;
	TP.calculateFirst();
	cout<<endl<<"Printing FIRST"<<endl<<endl;
	TP.printFirst();
	TP.calculateFollow("E");
	cout<<endl<<"Printing FOLLOW"<<endl<<endl;
	TP.printFollow();
	TP.constructTable();
	cout<<endl<<"Printing TABLE"<<endl<<endl;
	TP.printTable();

	return;
}

int main()
{
	/*SET 1*/
	// term S=term(string("S"),false);
	// term A=term(string("A"),false);
	// term a=term(string("a"),true);
	// term b=term(string("b"),true);
	// term c=term(string("c"),true);
	// term d=term(string("d"),true);
	// term eps=term(string("eps"),true);

	// S.addToCurrent(A);
	// S.addToCurrent(a);
	// S.startNew();
	// S.addToCurrent(b);

	// A.addToCurrent(A);
	// A.addToCurrent(c);
	// A.startNew();
	// A.addToCurrent(A);
	// A.addToCurrent(S);
	// A.addToCurrent(d);
	// A.startNew();
	// A.addToCurrent(eps);
	// A.startNew();
	// A.addToCurrent(d);
	// S.print();
	// A.print();
	
	// vector<term> v1;
	// vector<term> v2;

	// v1.push_back(S);
	// v1.push_back(A);

	// v2.push_back(a);
	// v2.push_back(b);
	// v2.push_back(d);
	// v2.push_back(c);
	// v2.push_back(eps);

	// TopDownParser TP=TopDownParser(v1,v2);

	/*SET 2*/
	// term E=term("E",false);
	// term T=term("T",false);
	// term F=term("F",false);
	// term plus=term("+",true);
	// term minus=term("-",true);
	// term mult=term("*",true);
	// term openb=term("(",true);
	// term closeb=term(")",true);
	// term id=term("id",true);
	// term end=term("$",true);
	// term eps=term("eps",true);

	// E.addToCurrent(E);
	// E.addToCurrent(plus);
	// E.addToCurrent(T);
	// E.startNew();
	// E.addToCurrent(T);

	// T.addToCurrent(T);
	// T.addToCurrent(mult);
	// T.addToCurrent(F);
	// T.startNew();
	// T.addToCurrent(F);

	// F.addToCurrent(openb);
	// F.addToCurrent(E);
	// F.addToCurrent(closeb);
	// F.startNew();
	// F.addToCurrent(id);

	// vector<term> v1;
	// vector<term> v2;

	// v1.push_back(E);
	// v1.push_back(T);
	// v1.push_back(F);

	// v2.push_back(plus);
	// v2.push_back(minus);
	// v2.push_back(openb);
	// v2.push_back(closeb);
	// v2.push_back(mult);
	// v2.push_back(id);
	// v2.push_back(eps);
	// v2.push_back(end);
	// TopDownParser TP=TopDownParser(v1,v2);

	// /*TEST PHASE*/
	// TP.printProductions();
	// TP.leftRecursion();
	// cout<<endl<<endl;
	// cout<<endl<<"Printing productions after removing left recursion"<<endl<<endl;
	// TP.printProductions();
	// TP.setMaps();
	// // cout<<TP.isNonTerminal("E'")<<endl;
	// TP.calculateFirst();
	// cout<<endl<<"Printing FIRST"<<endl<<endl;
	// TP.printFirst();
	// TP.calculateFollow(E.getName());
	// cout<<endl<<"Printing FOLLOW"<<endl<<endl;
	// TP.printFollow();
	// TP.constructTable();
	// cout<<endl<<"Printing TABLE"<<endl<<endl;
	// TP.printTable();

	// vector<string> input;
	// input.push_back("id");
	// input.push_back("+");
	// input.push_back("id");
	// input.push_back("*");
	// input.push_back("id");
	// input.push_back("$");
	// cout<<"Beginning Predictive Parsing"<<endl;
	// TP.predictiveParsing(E.getName(),input);

	/*SET 3*/
	



	/*Non terminals*/	

	// term program=term("program",false);
	// term declaration_list=term("declaration_list",false);
	// term declaration=term("declaration",false);
	// term var_declaration=term("var_declaration",false);
	// term type=term("type",false);
	// term fun_declaration=term("fun_declaration",false);
	// term params=term("params",false);
	// term compound_stmt=term("compound_stmt",false);
	// term local_declarations=term("local_declarations",false);
	// term statement_list=term("statement_list",false);
	// term statement=term("statement",false);
	// term expression_stmt=term("expression_stmt",false);
	// term selection_stmt=term("selection_stmt",false);
	// term return_stmt=term("return_stmt",false);
	// term expression=term("expression",false);
	// term var=term("var",false);
	// term simple_expression=term("simple_expression",false);
	// term relop=term("relop",false);
	// term EXP=term("EXP",false);
	// term addop=term("addop",false);
	// term TERM=term("TERM",false);
	// term mulop=term("mulop",false);
	// term factor=term("factor",false);
	// term temp1=term("temp1",false);
	// term temp2=term("temp2",false);
	// term temp3=term("temp3",false);

	// vector<term> v1;
	// vector<term> v2;

	

	


	// /*Terminals*/
	// term ID=term("ID",true);
	// term semi=term(";",true);
	// term INT=term("int",true);
	// term VOID=term("void",true);
	// term lpar1=term("(",true);
	// term rpar1=term(")",true);
	// term lpar2=term("{",true);
	// term rpar2=term("}",true);
	// term IF=term("if",true);
	// term ELSE=term("else",true);
	// term RETURN=term("return",true);
	// term lt=term("<",true);
	// term gt=term(">",true);
	// term plus=term("+",true);
	// term minus=term("-",true);
	// term mult=term("*",true);
	// term DIV=term("/",true);
	// term num=term("NUM",true);
	// term equal=term("=",true);
	// term eps=term("eps",true);
	// term end=term("$",true);

	// /*RULES*/

	// program.addToCurrent(declaration_list);

	// declaration_list.addToCurrent(declaration_list);
	// declaration_list.addToCurrent(declaration);
	// declaration_list.startNew();
	// declaration_list.addToCurrent(declaration);

	// // temp3.addToCurrent(semi);
	// // temp3.startNew();
	// // temp3.addToCurrent(lpar1);
	// // temp3.addToCurrent(params);
	// // temp3.addToCurrent(rpar1);
	// // temp3.addToCurrent(compound_stmt);

	// declaration.addToCurrent(var_declaration);
	// declaration.startNew();
	// declaration.addToCurrent(fun_declaration);

	// // declaration.addToCurrent(type);
	// // declaration.addToCurrent(ID);
	// // declaration.addToCurrent(temp3);	
	// var_declaration.addToCurrent(type);
	// var_declaration.addToCurrent(ID);
	// var_declaration.addToCurrent(semi);

	// type.addToCurrent(INT);
	// type.startNew();
	// type.addToCurrent(VOID);

	// fun_declaration.addToCurrent(type);
	// fun_declaration.addToCurrent(ID);
	// fun_declaration.addToCurrent(lpar1);
	// fun_declaration.addToCurrent(params);
	// fun_declaration.addToCurrent(rpar1);
	// fun_declaration.addToCurrent(compound_stmt);

	// params.addToCurrent(type);
	// params.addToCurrent(ID);

	// compound_stmt.addToCurrent(lpar2);
	// compound_stmt.addToCurrent(local_declarations);
	// compound_stmt.addToCurrent(statement_list);
	// compound_stmt.addToCurrent(rpar2);

	// local_declarations.addToCurrent(local_declarations);
	// local_declarations.addToCurrent(var_declaration);
	// local_declarations.startNew();
	// local_declarations.addToCurrent(eps);

	// statement_list.addToCurrent(statement_list);
	// statement_list.addToCurrent(statement);
	// statement_list.startNew();
	// statement_list.addToCurrent(eps);

	// statement.addToCurrent(expression_stmt);
	// statement.startNew();
	// statement.addToCurrent(compound_stmt);
	// statement.startNew();
	// statement.addToCurrent(selection_stmt);
	// statement.startNew();
	// statement.addToCurrent(return_stmt);

	// expression_stmt.addToCurrent(expression);
	// expression_stmt.addToCurrent(semi);
	// expression_stmt.startNew();
	// expression_stmt.addToCurrent(semi);

	// selection_stmt.addToCurrent(IF);
	// selection_stmt.addToCurrent(lpar1);
	// selection_stmt.addToCurrent(expression);
	// selection_stmt.addToCurrent(rpar1);
	// selection_stmt.addToCurrent(statement);
	// selection_stmt.addToCurrent(temp1);
	// selection_stmt.startNew();
	// selection_stmt.addToCurrent(IF);
	// selection_stmt.addToCurrent(lpar1);
	// selection_stmt.addToCurrent(expression);
	// selection_stmt.addToCurrent(rpar1);
	// selection_stmt.addToCurrent(statement);
	// selection_stmt.addToCurrent(ELSE);
	// selection_stmt.addToCurrent(statement);

	// // temp1.addToCurrent(eps);
	// // temp1.startNew();
	// // temp1.addToCurrent(ELSE);
	// // temp1.addToCurrent(statement);

	// return_stmt.addToCurrent(RETURN);
	// return_stmt.addToCurrent(semi);

	// expression.addToCurrent(var);
	// expression.addToCurrent(equal);
	// expression.addToCurrent(expression);
	// expression.startNew();
	// expression.addToCurrent(simple_expression);

	// var.addToCurrent(ID);
	
	// simple_expression.addToCurrent(EXP);
	// simple_expression.addToCurrent(temp2);
	// simple_expression.addToCurrent(relop);
	// simple_expression.addToCurrent(EXP);
	// simple_expression.startNew();
	// simple_expression.addToCurrent(EXP);

	// temp2.addToCurrent(relop);
	// temp2.addToCurrent(EXP);
	// temp2.startNew();
	// temp2.addToCurrent(eps);

	// relop.addToCurrent(lt);
	// relop.startNew();
	// relop.addToCurrent(gt);

	// EXP.addToCurrent(EXP);
	// EXP.addToCurrent(addop);
	// EXP.addToCurrent(TERM);
	// EXP.startNew();
	// EXP.addToCurrent(TERM);

	// addop.addToCurrent(plus);
	// addop.startNew();
	// addop.addToCurrent(minus);

	// TERM.addToCurrent(TERM);
	// TERM.addToCurrent(mulop);
	// TERM.addToCurrent(factor);
	// TERM.startNew();
	// TERM.addToCurrent(factor);

	// mulop.addToCurrent(mult);
	// mulop.startNew();
	// mulop.addToCurrent(DIV);

	// factor.addToCurrent(lpar1);
	// factor.addToCurrent(expression);
	// factor.addToCurrent(rpar1);
	// factor.startNew();
	// factor.addToCurrent(var);
	// factor.startNew();
	// factor.addToCurrent(num);

	// v1.push_back(program);
	// v1.push_back(declaration_list);
	// v1.push_back(declaration);
	// v1.push_back(var_declaration);
	// v1.push_back(type);
	// v1.push_back(fun_declaration);
	// v1.push_back(params);
	// v1.push_back(compound_stmt);
	// v1.push_back(local_declarations);
	// v1.push_back(statement_list);
	// v1.push_back(statement);
	// v1.push_back(expression_stmt);
	// v1.push_back(selection_stmt);
	// v1.push_back(return_stmt);
	// v1.push_back(expression);
	// v1.push_back(var);
	// v1.push_back(simple_expression);
	// v1.push_back(relop);
	// v1.push_back(EXP);
	// v1.push_back(addop);
	// v1.push_back(TERM);
	// v1.push_back(mulop);
	// v1.push_back(factor);
	// // v1.push_back(temp3);
	// // v1.push_back(temp1);
	// // v1.push_back(temp2);

	// v2.push_back(ID);
	// v2.push_back(semi);
	// v2.push_back(INT);
	// v2.push_back(VOID);
	// v2.push_back(lpar1);
	// v2.push_back(rpar1);
	// v2.push_back(lpar2);
	// v2.push_back(rpar2);
	// v2.push_back(IF);
	// v2.push_back(ELSE);
	// v2.push_back(RETURN);
	// v2.push_back(lt);
	// v2.push_back(gt);
	// v2.push_back(plus);
	// v2.push_back(minus);
	// v2.push_back(mult);
	// v2.push_back(DIV);
	// v2.push_back(num);
	// v2.push_back(equal);
	// v2.push_back(eps);
	// v2.push_back(end);

	// TopDownParser TP=TopDownParser(v1,v2);

	// // /*TEST PHASE*/
	// TP.printProductions();
	// TP.leftRecursion();
	// cout<<"After left recursion removal"<<endl<<endl;
	// TP.printProductions();
	// TP.setMaps();
	
	// cout<<"Printing First"<<endl;
	// TP.calculateFirst();
	// cout<<endl<<endl;
	// TP.printFirst();

	// cout<<"Printing follow"<<endl;
	// TP.calculateFollow(program.getName());	
	// cout<<endl<<endl;
	// TP.printFollow();

	// TP.constructTable();
	// TP.printTable();

	readFromfile("o3.txt");
}