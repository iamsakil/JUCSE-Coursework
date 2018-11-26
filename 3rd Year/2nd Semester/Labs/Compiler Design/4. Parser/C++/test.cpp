#include <iostream>
#include <vector>
using namespace std;
void print(vector<int> v)
{
	for(int i=0;i<v.size();i++)
		cout<<v[i]<<"\t";
	cout<<endl;
}
int main()
{
	vector<int> v;
	for(int i=0;i<10;i++)
		v.push_back(i);
	vector<int> x(10,1);
	x.append(v);	
	print(v);
}