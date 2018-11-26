#include <bits/stdc++.h>

using namespace std;

int nCr(int n, int r);

class Pascal {

	friend ostream& operator<<(ostream& os, const Pascal& data);

public:
	void generate(int row_cnt);
	int get(int r, int c);
	void comb_generate(int r);
	
private:
	int row; 
	vector<vector<int>> data;
};

void Pascal::generate(int r) {

	//data.clear();
	row = r;
	data.resize(r, vector<int>(r, 0));
	
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < i; ++j) {
			if (j == 0 || j == i - 1)
				data[i][j] = 1;
			else {
				data[i][j] = data[i-1][j] + data[i-1][j - 1];
			}
		} 		
	}	
}

int Pascal::get(int r, int c) {
	//return data[r][c];
	return nCr(r,c);
}

void Pascal::comb_generate(int r) {

	cout << endl;
	cout << "\n By combination:" << endl;
	cout << endl;
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < r - i; ++j)
			cout << "   ";
		for (int j = 0; j <= i; ++j) {
			cout << setw(3) << nCr(i,j) << "   ";
		}
		
		cout << endl; 		
	}	
}

ostream& operator<<(ostream& os, const Pascal& d) {
	for (int i = 0; i < d.row; ++i) {
		for (int j = 0; j < d.row - i; ++j)
			os << "   ";
		for (int j = 0; j < i; ++j) {
			os << setw(3) << d.data[i][j] << "   ";
		}
		
		os << "\n";
	}
	
	return os;
}

int nCr(int n, int r) {
	if (r == 0) return 1;
	if (n < r) return 0;
	
	return (nCr(n - 1, r) + nCr(n - 1, r - 1));
}

int main() {
	int choice;
	Pascal p;
	while(1){
		cout<<"\n\n List of options:\n";
		cout<<"\n_________________________________\n";
		cout<<"\n\n1.PRINT PASCAL'S TRIANGLE\n\n2.CHECK ANY ENTRY\n\n0.TO EXIT\n";
		cout<<"\n_________________________________\n";
		cout<<"\n Enter your choice: ";
		cin>>choice;
		switch(choice){
			case 1:{
				cout << "\n Please enter the numer of rows: " ;
				int row_cnt;
				cin >> row_cnt;
				p.generate(row_cnt);
				cout << p;
				break;
			}
			case 2:{
				cout << "\n Please enter the numer of rows: " ;
				int row_cnt;
				cin >> row_cnt;
				p.generate(row_cnt);
				
				//p.comb_generate(row_cnt - 1);
				
				int row_n, col_n;
				
				cout << "\n Enter a row and col: ";
				cin >> row_n >> col_n;
				cout <<"\n The corresponding value is= "<<p.get(row_n,col_n) << endl;
				break;
			}
			case 0:{
				return 0;
			}
			default:{
				cout<<"\n\n ENTER ACCORDING TO OPTIONS!!!!!\n\n";
				continue;
			}
		}
	}
	return 0;
}
