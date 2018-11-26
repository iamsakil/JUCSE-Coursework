#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <stack>
#include <map>
//#include "infixpostfix.cpp"
using namespace std;

class node
{
	public:
		char symbol;		//stores the symbol
		bool isOperator;	//tells if the node denotes an operator
		node *left;			//left child
		node * right;		//right child
		int number;			//number of leaf
		bool nullable;		//tells if the node is nullable or not
		set<int> firstpos;	//the set of leaf positions in firstpos
		set<int> lastpos;	//the set of leaf positions in lastpos
};

typedef node* Node;

class state
{
	set<int> s;	//stores the positions that uniquely identifies the state
	map<char,int> tran;//defines transition of character to other states
	public:

	bool marked;
	state()
	{
		s=set<int>();
		marked=false;
	}

	bool isEmpty()
	{
		return s.size()==0;
	}
	void print()
	{
		cout<<"Positons Contained : ";
		for(set<int>::iterator it1=s.begin();it1!=s.end();++it1)
			cout<<*it1<<"\t";
		cout<<endl;
	}
	void addTransition(char c,int i)
	{
		tran[c]=i;
	}

	bool exists(int n)
	{
		return s.find(n)!=s.end();
	}
	int getTransition(char c)
	{
		if(tran.find(c)==tran.end())
			return -1;
		return tran[c];
	}
	void mark()
	{
		marked=true;
	}

	void unmark()
	{
		marked=false;
	}

	void insert(int n)
	{
		s.insert(n);
	}

	bool isSimilar(state &st)	//checks if 2 states are similar
	{
		if(st.s.size()!=(this->s.size()))
			return false;
		set<int>::iterator it1;
		set<int>::iterator it2;
		for(set<int>::iterator it1=s.begin(),it2=st.s.begin();it1!=s.end();++it1,++it2)
			if(*it1 != *it2)
				return false;
		return true;
	}

};

vector<Node> leaves;
vector<set<int> > followpos;

Node make_node(char c)	//allocates a node
{
	Node n=(Node)malloc(sizeof(node));
	n->symbol=c;
	n->isOperator=(c=='|')||(c=='*')||(c=='+');
	n->left=n->right=NULL;
	n->firstpos=set<int>();
	n->lastpos=set<int>();
	return n;
}

bool isOperator(char c)
{
	return (c=='|')||(c=='*')||(c=='+');
}

void inorder(Node root)	//does an inorder traversal and creates a list of leaves
{
	if(root!=NULL)
	{
		inorder(root->left);
		if(root->left==NULL && root->right==NULL)
		{
			leaves.push_back(root);
			root->number=leaves.size()-1;
		}
		else
			root->number=-1;
		inorder(root->right);
	}
}

void inorder2(Node root)	//does an inorder traversal of the syntax tree and prints property of every node
{
	if(root!=NULL)
	{
		inorder2(root->left);
		cout<<root->symbol<<" "<<(root->nullable?("Nullable"):("Not Nullable"))<<endl;
		cout<<"Firstpos : ";
		for(set<int>::iterator it=root->firstpos.begin();it!=root->firstpos.end();++it)
			cout<<*it<<" ";
		cout<<endl;
		cout<<"Lastpos : ";
		for(set<int>::iterator it=root->lastpos.begin();it!=root->lastpos.end();++it)
			cout<<*it<<" ";
		cout<<endl<<"---------------------"<<endl;
		inorder2(root->right);
	}
}


bool compute_nullable(Node root)	//checks if root is nullable using standard rules
{
	if(root==NULL)
		return false;

	if(root->left==NULL && root->right==NULL)
	{
		root->nullable=false;
		return false;
	}
	else if(root->symbol=='+')	//concatenation operator
	{
		return(root->nullable=(compute_nullable(root->left) & compute_nullable(root->right)));
	}
	else if(root->symbol=='|')	//or operator
	{
		return(root->nullable=(compute_nullable(root->left) | compute_nullable(root->right)));
	}
	else if(root->symbol=='*')	//closure operator
	{
		compute_nullable(root->left);
		compute_nullable(root->right);
		return(root->nullable=true);
	}
	else	//wrong operator
	{
		cout<<root->symbol<<endl;
		cout<<"Wrong operator or symbol"<<endl;
		return false;
	}
}

Node compute_lastpos(Node root)
{
	if(root==NULL)
		return NULL;
	// cout<<root->symbol<<"\t"<<root->number<<endl;
	if(root->number!=-1)
	{
		(root->lastpos).insert(root->number);
		return root;
	}

	else if(root->symbol=='|')	//lastpos(left child) U lastpos(right child)
	{
		Node a=compute_lastpos(root->left);
		Node b=compute_lastpos(root->right);
		for(set<int>::iterator it=(a->lastpos).begin();it!=(a->lastpos).end();++it)
			(root->lastpos).insert(*it);
		for(set<int>::iterator it=(b->lastpos).begin();it!=(b->lastpos).end();++it)
			(root->lastpos).insert(*it);
		return root;
	}

	else if(root->symbol=='*') //lastpos(child)
	{
		Node a=compute_lastpos(root->left);
		for(set<int>::iterator it=(a->lastpos).begin();it!=(a->lastpos).end();++it)
			(root->lastpos).insert(*it);
		return root;
	}

	else if(root->symbol=='+')	//lastpos(right child) U { EMPTY if right child is not nullable else lastpos(left child)}
	{
		Node a=compute_lastpos(root->left);
		Node b=compute_lastpos(root->right);
		for(set<int>::iterator it=(b->lastpos).begin();it!=(b->lastpos).end();++it)
			(root->lastpos).insert(*it);
		if(b->nullable)
		{
			for(set<int>::iterator it=(a->lastpos).begin();it!=(a->lastpos).end();++it)
				(root->lastpos).insert(*it);
		}
		return root;
	}

	else
	{
		cout<<"Wrong symbol"<<endl;
		return NULL;
	}
}

Node compute_firstpos(Node root)
{
	if(root==NULL)
		return NULL;
	// cout<<root->symbol<<"\t"<<root->number<<endl;
	if(root->number!=-1)
	{
		(root->firstpos).insert(root->number);
		return root;
	}

	else if(root->symbol=='|')	//or operator
	{
		Node a=compute_firstpos(root->left);
		Node b=compute_firstpos(root->right);
		for(set<int>::iterator it=(a->firstpos).begin();it!=(a->firstpos).end();++it)
			(root->firstpos).insert(*it);
		for(set<int>::iterator it=(b->firstpos).begin();it!=(b->firstpos).end();++it)
			(root->firstpos).insert(*it);
		return root;
	}

	else if(root->symbol=='*')	//closure operator
	{
		Node a=compute_firstpos(root->left);
		for(set<int>::iterator it=(a->firstpos).begin();it!=(a->firstpos).end();++it)
			(root->firstpos).insert(*it);
		return root;
	}

	else if(root->symbol=='+')	//concatenation operator
	{
		Node a=compute_firstpos(root->left);
		Node b=compute_firstpos(root->right);
		set<int> st;
		for(set<int>::iterator it=(a->firstpos).begin();it!=(a->firstpos).end();++it)
			(root->firstpos).insert(*it);
		if(a->nullable)
		{
			for(set<int>::iterator it=(b->firstpos).begin();it!=(b->firstpos).end();++it)
				(root->firstpos).insert(*it);
		}
		return root;
	}

	else
	{
		cout<<"Wrong symbol"<<endl;
		return NULL;
	}
}

void compute_followpos(Node root)
{
	if(root==NULL)
		return;
	if(root->symbol=='+')
	{
		Node c1=root->left;
		Node c2=root->right;
		for(set<int>::iterator it=(c1->lastpos).begin();it!=(c1->lastpos).end();++it)
		{
			for(set<int>::iterator it2=(c2->firstpos).begin();it2!=(c2->firstpos).end();++it2)
				followpos[*it].insert(*it2);
		}
	}

	if(root->symbol=='*')
	{
		Node c1=root->left;
		for(set<int>::iterator it=(c1->lastpos).begin();it!=(c1->lastpos).end();++it)
		{
			for(set<int>::iterator it2=(c1->firstpos).begin();it2!=(c1->firstpos).end();++it2)
				followpos[*it].insert(*it2);
		}
	}

	compute_followpos(root->left);
	compute_followpos(root->right);
	return;

}

void build_dfa(Node root)
{
	vector<state> V;
	state S;
	int i,j,k;

	//building first state S
	for(set<int>::iterator it=(root->firstpos).begin();it!=(root->firstpos).end();++it)
			S.insert(*it);

	V.push_back(S);
	vector<char> symbols;
	set<char> temp;
	for(i=0;i<leaves.size();i++)	//building the set of distinct symbols
	{
		if(temp.find(leaves[i]->symbol)==temp.end() && leaves[i]->symbol!='#' && !leaves[i]->isOperator)
		{
			temp.insert(leaves[i]->symbol);
			symbols.push_back(leaves[i]->symbol);
		}
	}

	while(1)
	{
		for(i=0;i<V.size();i++)
		{
			if(!V[i].marked)
			{
				break;
			}
		}
		if(i==V.size())	//no unmarked state left
			break;
		V[i].marked=true;

		for(j=0;j<symbols.size();j++)
		{
			state U;
			for(k=0;k<followpos.size();k++)
			{
				if(leaves[k]->symbol==symbols[j] && V[i].exists(k))
				{
					for(set<int>::iterator it=followpos[k].begin();it!=followpos[k].end();++it)
					{
						U.insert(*it);
					}
				}

			}

			if(U.isEmpty())
				continue;
			for(k=0;k<V.size();k++)
			{
				if((U.isSimilar(V[k])))
				{
					break;
				}
			}

			if(k==V.size())
			{
				V.push_back(U);
			}
			V[i].addTransition(symbols[j],k);
		}
	}

	for(i=0;i<V.size();i++)
	{
		cout<<"State "<<i<<" : ";
		if(V[i].exists(leaves.size()-1))
			cout<<"ACCEPT STATE";
		cout<<endl;
		V[i].print();
		for(j=0;j<symbols.size();j++)
		{
			cout<<symbols[j]<<" : ";
			int t=V[i].getTransition(symbols[j]);
			if(t==-1)
				cout<<"None"<<endl;
			else
				cout<<t<<endl;
		}
		cout<<"------------------"<<endl;
	}
}

Node build_syntax_tree(string &s)	//uses postfix evaluation algorithm to build the syntax tree
{
	Node a,b,root;
	stack<Node> st;
	for(int i=0;i<s.size();i++)
	{
		if(isOperator(s[i]))
		{
			if(s[i]=='|' || s[i]=='+')
			{
				a=st.top();
				st.pop();
				b=st.top();
				st.pop();
				root=make_node(s[i]);
				root->left=b;
				root->right=a;
				st.push(root);
			}
			else if(s[i]=='*')
			{
				root=make_node(s[i]);
				a=st.top();
				st.pop();
				root->left=a;
				root->right=NULL;
				st.push(root);
			}
		}
		else
		{
			b=make_node(s[i]);
			st.push(b);
		}
	}
	root=make_node('+');//make concatenation operator
	root->left=st.top();
	st.pop();
	root->right=make_node('#');
	inorder(root);	//initialising list of leaves
	return root;
}


int main()
{
	string s;
	s=get_postfix();//gets input converted to postfix
	Node root=build_syntax_tree(s);

	// for(int i=0;i<leaves.size();i++)
	// 	cout<<leaves[i]->symbol<<"\t"<<leaves[i]->number<<endl;

	followpos=vector<set<int> >(leaves.size());
	compute_nullable(root);
	compute_firstpos(root);
	compute_lastpos(root);
	compute_followpos(root);

	cout<<"Doing in order traversal of syntax tree :"<<endl;
	inorder2(root);

	cout<<"Printing followpos : "<<endl;
	for(int i=0;i<followpos.size();i++)
	{
		cout<<i<<" - "<<" - "<<leaves[i]->symbol<<endl;;
		for(set<int>::iterator it=followpos[i].begin();it!=followpos[i].end();++it)
			cout<<*it<<"\t";
		cout<<endl;
	}

	cout<<"Printing States with transition"<<endl;
	build_dfa(root);

}
