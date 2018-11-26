#include <bits/stdc++.h>
#include "Tokenizer.cpp"
using namespace std;

enum ParserState{S = 1, Select = 2, Col = 3, As = 4, Rename = 5, Star = 6, From = 7, Table = 8, Where = 9, Id = 10, Eq = 11, String = 12, AndOr = 13, Run = 14};
// SELECT = 1, WHERE = 2, FROM = 3, AS = 4, AND = 5, OR = 6, ID = 7, STRING = 8, COMMA = 9, EQ = 10, SEMICOL = 11,  STAR = 12, END = 13

extern unordered_map<string, int> Columns;
extern vector<string> ColNames;

//Function to parse input query
bool parse(string& query, vector<int>& display_colums, vector<string>& display_col_names){
	bool ALL = false;
	Token token;
	int i = 0, row = 1, col = 1;
	string yytext;
	ParserState cur_state = S;
	while(token = getNextToken(query, i, yytext, row, col)){
		switch(cur_state){
			case S :
				if(token == SELECT){
					cur_state = Select;
				}else{
					cout << "Keyword SELECT expected, row = " << row << " col = " << col - yytext.length() << endl;
					return false;
				}
				break;
			case Select :
				if(token == STAR){
					if(display_colums.size() != 0){
						cout << "Asteric not expected after selecting some column(s)!" << endl;
						return false;
					}	
					cur_state = Star;
					ALL = true;
					for(int j = 0; j < 4; j++){ // 4 is to be replaced by no. of columns in the DB
						display_colums.push_back(j);
						display_col_names.push_back(ColNames[j]);
					}
				}else if(token == ID){
					if(ALL){
						cout << "Keyword FROM expected after asteric, row = " << row << " col = " << col - yytext.length() << endl;
						return false;
					}
					if(Columns.find(yytext) == Columns.end()){
						cout << "Column name \'" << yytext << "\' not found in the DB, row = " << row << " col = " << col - yytext.length() << endl;
						return false;
					}
					int j = Columns[yytext];
					display_colums.push_back(j);
					display_col_names.push_back(ColNames[j]);
					cur_state = Col;
				}else{
					cout << "Identifier or asteric expected, row = " << row << " col = " << col - yytext.length() << endl;
					return false;
				}
				break;
			case Col :
				if(token == COMMA){
					cur_state = Select;
				}else if(token == FROM){
					cur_state = From;
				}else if(token == AS){
					cur_state = As;
				}else {
					cout << "Keyword AS, FROM or Comma expected, row = " << row << " col = " << col - yytext.length() << endl;
					return false;
				}
				break;
			case As :
				if(token == ID){
					cur_state = Rename;
					display_col_names[display_col_names.size() - 1] = yytext;
				}else{
					cout << "Identifier expected, row = " << row << " col = " << col - yytext.length() << endl;
					return false;
				}
				break;
			case Rename :
				if(token == FROM){
					cur_state = From;
				}else if(token == COMMA){
					cur_state = Select;
				}else{
					cout << "Keyword FROM or Comma expected, row = " << row << " col = " << col - yytext.length() << endl;
					return false;
				}
				break;
			case Star :
				if(token == FROM){
					cur_state = From;
				}else{
					cout << "Keyword FROM expected, row = " << row << " col = " << col - yytext.length()<< endl;
					return false;
				}
				break;
			case From :
				if(token == ID){
					if(yytext != "MYDB"){
						cout << "Undefined table name, row = " << row << " col = " << col - yytext.length() << endl;
						return false;
					}
					cur_state = Table;
				}else{
					cout << "Identifier expected, row = " << row << " col = " << col - yytext.length() << endl;
					return false;
				}
				break;
			case Table :
				if(token == WHERE){
					cur_state = Where;
				}else if(token == SEMICOL){
					cur_state = Run;
				}else{
					cout << "Keyword WHERE or Semicolon expected, row = " << row << " col = " << col - yytext.length() << endl;
					return false;
				}
				break;
			case Where :
				if(token == ID){
					cur_state = Id;
				}else{
					cout << "Identifier expected, row = " << row << " col = " << col - yytext.length() << endl;
					return false;
				}
				break;
			case Id :
				if(token == EQ){
					cur_state = Eq;
				}else{
					cout << "Comparator (Only \'=\' allowed) expected, row = " << row << " col = " << col << endl;
					return false;
				}
				break;
			case Eq :
				if(token == STRING){
					cur_state = String;
				}else{
					cout << "String expected, row = " << row << " col = " << col - yytext.length() << endl;
					return false;
				}
				break;
			case String :
				if(token == AND){
					cur_state = AndOr;
				}else if(token == OR){
					cur_state = AndOr;
				}else if(token == SEMICOL){
					cur_state = Run;
				}else{
					cout << "Keyword AND, OR or Semicolon expected, row = " << row << " col = " << col - yytext.length() << endl;
					return false;
				}
				break;
			case AndOr :
				if(token == ID){
					cur_state = Id;
				}else{
					cout << "Identifier expected, row = " << row << " col = " << col - yytext.length() << endl;
					return false;
				}
				break;
			case Run :
				if(token == END){
					return true;
				}else{
					cout << "Unexpected token after semicolon, row = " << row << " col = " << col - yytext.length() << endl;
					return false;
				}
				break;
		}
	}
}
