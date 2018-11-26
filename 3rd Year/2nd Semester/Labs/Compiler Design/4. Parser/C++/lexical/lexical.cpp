#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class lexical
{
	char *filename;
	public:
	lexical(char * f)
	{
		filename=f;
	}

	void startSeperating();
};

// void lexical::test()
// {
// 	ifstream fin;
// 	fin.open(filename,ios::in);
// 	while(!fin.eof())
// 	{
// 		char c;
// 		fin.get(c);
// 		printf("%c\n",c);
// 	}
// }

void lexical :: startSeperating()
{
	
}
int main()
{
	lexical L=lexical("lexical.cpp");
	int t=10;
	char c;
	while(t--)
		cout<<L.getNext(c)<<endl;
	cout<<L.peek(c)<<endl;
	cout<<L.getNext(c)<<endl;
	return 0;
}