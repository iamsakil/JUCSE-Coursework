// #include <iostream>
// #include <string>
// #include <fstream>
// #include <vector>
#include <bits/stdc++.h>
#include<cstring>
#include "tokenseparator.cpp"

// void startSplitting(string &s,vector<string> &tokens)
// {
// 	int i=0;
// 	while(s[i]==' ' || s[i]=='\t')
// 		i++;

// 	string x;

// 	for(;i<s.size();i++)
// 	{

// 		if(s[i]==' '|| s[i]=='\t')
// 		{
// 			tokens.push_back(x);
// 			x="";

// 			while(i<s.size() && ( s[i]==' ' || s[i]=='\t'))
// 				i++;
// 			if(i<s.size())
// 				x.append(s[i]);
// 		}
// 		else
// 		{
// 			x.append(s[i]);
// 		}
// 	}
// }
int main()
{
	string s;
    ofstream fout;
    // fout.open("database.txt",ios :: out);
	cin>>s;
	token t =token(0,s);
	cout<<t.prefixesOf()<<endl;
	// vector<string> tokens;
	// startSplitting(s,tokens);

	// //iterator :: vector<string> itr;

	// while(int i=0;i<tokens.size();i++)
	// {
	// 	token t=token(i,tokens[i]);
	// 	fout.write((char*)&t,sizeof(token));
	// }

	// fout.close();
	// ifstream fin;
	// token t1;
	// fin.open("database.txt",ios :: out);
	// while(fin.read((char*)&t1,sizeof(token))!=eof)
	// {
	// 	cout<<t1.returnlineno()<<" "<<t1.returnsym()<<" "<<t1.returntype()<<"\n";
	// }
}