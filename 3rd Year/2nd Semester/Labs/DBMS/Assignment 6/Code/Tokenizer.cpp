#include <bits/stdc++.h>
using namespace std;

enum Token{SELECT = 1, WHERE = 2, FROM = 3, AS = 4, AND = 5, OR = 6, ID = 7, STRING = 8, COMMA = 9, EQ = 10, SEMICOL = 11,  STAR = 12, END = 13};
enum State{Start, IDBeg, StrBeg};

extern unordered_map<string, int> Keywords;

//Function to get the next token from input string
Token getNextToken(string& in, int& i, string& yytext, int& row, int& col){
	char ch;
	yytext.clear();
	bool flag = false;
	State cur_state = Start;
	while(!flag){
		(i >= in.length()) ? (ch = '\0') : (ch = in[i]);
		i++;
		col++;
		switch(cur_state){
			case Start :
				switch(ch){
					case '*' :
						return STAR;
					case ';' :
						return SEMICOL;
					case ',' :
						return COMMA;
					case '=' :
						return EQ;
					case '\n' :
						row++;
						col = 0;
						break;
					case ' '  :
					case '\t' :
						break;
					case '\'' :
						cur_state = StrBeg;
						break;
					case '\0' :
						return END;
						break;
					default:
						if(ch >= 'A' && ch <= 'Z' || ch == '_' || ch >= '0' && ch <= '9'){
							yytext.push_back(ch);
							cur_state = IDBeg;
						}else if(ch >= 'a' && ch <= 'z'){
							yytext.push_back(ch + 'A' - 'a');
							cur_state = IDBeg;
						}
						break;
				}
				break;
			case IDBeg :
				if(ch >= 'A' && ch <= 'Z' || ch == '_' || ch >= '0' && ch <= '9'){
					yytext.push_back(ch);
				}else if(ch >= 'a' && ch <= 'z'){
					yytext.push_back(ch + 'A' - 'a');
				}else{
					cur_state = Start;
					i--;
					col--;
					int x = Keywords[yytext];
					if(x > 0){
						return (Token)x;
					}
					return ID;
				}
				break;
			case StrBeg :
				if(ch == '\0'){
					cout << "Unmatched string literal, row = " << row << " col = " << col << endl;
					return END;
				}
				if(ch == '\''){
					cur_state = Start;
					return STRING;
				}else if(ch == '\n'){
					row++; col = 0;
				}
				yytext.push_back(ch);
		}
	}
}
