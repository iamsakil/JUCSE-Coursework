#include <iostream>
#include <vector>
#include <string>
using namespace std;
class term
{
public:
	string name;
	bool is_term;
	bool isEpsilon;
	int prod_num;
	public:
		term(string name,bool is_term)
		{
			this->name=name;
			this->is_term=is_term;
			isEpsilon=(name=="eps");
			prod_num=-1;
			startNew();
		}

		vector<vector<term> >& getProductions()
		{
			return P;
		}

		string getName()
		{
			return name;
		}


		void print();
		void addToCurrent(term &t);
		void startNew();

};


void term :: print()
{
	int i,j;
	cout<<name<<" -> ";
	for(i=0;i<=prod_num;i++)
	{
		for(j=0;j<P[i].size();j++)
			cout<<P[i][j].name<<" ";
		if(i<prod_num)
			cout<<" | ";
	}
	cout<<endl;
}

class TopDownParser
{
	vector<term> nt;
	vector<term> t;
	vector<vector<vector<term> > > P;
	public:

	void term :: addToCurrent(int x)
	{
		P[x][].push_back(t);
	}

void term :: startNew()
{
	prod_num++;
	P.push_back(vector<term>());
}

	TopDownParser(vector<term> &nt,vector<term> &t)
	{
		this->nt=nt;
		this->t=t;
	}

	void printProductions()
	{
		for(int i=0;i<nt.size();i++)
			nt[i].print();
	}

	void immediateRecursion(int v)
	{
		vector<vector<term> > P=nt[v].getProductions();
		int i,j;
		cout<<nt[v].getName()<<endl;
		vector<int> imm;
		for(i=0;i<P.size();i++)
		{
			// cout<<P[i][0].getName()<<endl;
			if(P[i][0].getName()==nt[v].getName())
				imm.push_back(i);
		}

		for(i=0;i<imm.size();i++)
		{
			// cout<<imm[i]<<endl;
			// P.erase(P.begin()+imm[i]);
			P[imm[i]][0].name="hello";
		}

	}



};
int main()
{
	term S=term(string("S"),false);
	term A=term(string("A"),false);
	term a=term(string("a"),true);
	term b=term(string("b"),true);
	term c=term(string("c"),true);
	term d=term(string("d"),true);
	term eps=term(string("eps"),true);

	S.addToCurrent(A);
	S.addToCurrent(a);
	S.startNew();
	S.addToCurrent(b);

	A.addToCurrent(A);
	A.addToCurrent(c);
	A.startNew();
	A.addToCurrent(S);
	A.addToCurrent(d);
	A.startNew();
	A.addToCurrent(eps);
	
	// S.print();
	// A.print();
	
	vector<term> v1;
	vector<term> v2;

	v1.push_back(S);
	v1.push_back(A);

	v2.push_back(a);
	v2.push_back(b);
	v2.push_back(d);
	v2.push_back(c);
	v2.push_back(eps);

	TopDownParser TP=TopDownParser(v1,v2);

	// TP.printProductions();
	// TP.immediateRecursion(1);
	TP.printProductions();

}