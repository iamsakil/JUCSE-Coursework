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

		for(i=0;i<TABLE.size();i++)
		{
			for(j=0;j<TABLE[i].size();j++)
			{
				int x,y;
				x=TABLE[i][j].first;
				y=TABLE[i][j].second;
				if(x>=0 && y>=0)
				{
					cout<<nt[i].getName()<<","<<t[j].getName()<<"\t";
					nt[x].print(y);
					cout<<endl;
				}
				else
				{
					;
					// cout<<"-";
				}
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
	TP.calculateFollow(nt[0].getName());
	cout<<endl<<"Printing FOLLOW"<<endl<<endl;
	TP.printFollow();
	TP.constructTable();
	cout<<endl<<"Printing TABLE"<<endl<<endl;
	TP.printTable();

	return;
}

int main()
{
	readFromfile("o2.txt");
}
