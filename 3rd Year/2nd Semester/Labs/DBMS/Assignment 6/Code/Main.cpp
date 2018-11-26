#include <bits/stdc++.h>
#include "Parser.cpp"
using namespace std;

/*
	Name : MyDB.txt
	Columns : ROLL, FNAME, LNAME, DEPT
	Query : select [columns] from MyDB;
*/

unordered_map<string, int> Keywords;
unordered_map<string, int> Columns;
vector<string> ColNames;

//Function to split the query entered by user
void split(string& line, vector<string>& cols){
	string str;
	for(int i = 0; i < line.length(); i++){
		if(line[i] == ' ' || line[i] == '\t'){		//In case of white space
			if(!str.empty()){
				cols.push_back(str);
				str.clear();
			}
		}else{										//If not white space
			str.push_back(line[i]);
		}
	}
	if(!str.empty()){
		cols.push_back(str);
	}
}

//Function to execute the query
void execute(string query){
	// Parse the query
	vector<int> display_colums;
	vector<string> display_col_names;
	if(!parse(query, display_colums, display_col_names)){		//Parsing the query and exiting if non-parceable
		return;
	}
	// Actual Implementation of the query
	ifstream in("MyDB.txt");
	if(!in){
		cout << "Database not found !" << endl;					//If Database table file is not present
		exit(0);
	}
	
	for(int i = 0;  i < display_col_names.size(); i++){
		cout << display_col_names[i] << "\t";					//Printing header for output
	}
	cout << endl;
	
	string line;
	while(in){
		getline(in, line);
		vector<string> cols;
		if(line.length() > 0){
			split(line, cols);
			for(int i = 0;  i < display_colums.size(); i++){
				cout << cols[display_colums[i]] << "\t";		//Displaying required attributes
			}
			cout << endl;
		}
	}
	in.close();
}

int main(int argc, char *argv[]){
	Keywords["SELECT"] = SELECT;
	Keywords["WHERE"] = WHERE;
	Keywords["FROM"] = FROM;
	Keywords["AS"] = AS;
	Keywords["AND"] = AND;
	Keywords["OR"] = OR;

	Columns["ROLL"] = 0;
	Columns["FNAME"] = 1;
	Columns["LNAME"] = 2;
	Columns["DEPT"] = 3;

	ColNames.push_back("ROLL");
	ColNames.push_back("FNAME");
	ColNames.push_back("LNAME");
	ColNames.push_back("DEPT");
	
	char query[1024];
	while(1){
		printf("SQL>");
		scanf("%[^;]s", query);
		if(strcmp("exit", query)==0)
			break;
		execute(string(query) + ";");
		fflush(stdin);
	}
}
