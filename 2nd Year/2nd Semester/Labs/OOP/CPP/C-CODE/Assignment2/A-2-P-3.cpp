#include<stdio.h> 
#include<iostream> 
#include<ctime> 
#include<fstream> 
#include<string> 
using namespace std; 
 
         
class Books{                                                     //Class Books, to store the properties of a book like accession number, 
    protected:                                                    //name of book, name of author, date of issuing and card number under which     
    int accn_no;                                                //it has been issued 
    char name[50]; 
    char author[50]; 
    int ddi,mmi,yyi; 
    int card_number; 
    public: 
        void get_info(int cno, const char *file);             //Member fucntion to get information of book and write it into the file "Books.txt" 
        void print_info(const char* file);                         //Member function to display information of a book 
        int ret_accn_no();                                        //Member function to return acsession number of a book 
        int find_diff(int cdd, int cmm, int cyy);                //Member function to find the difference in days between two dates 
        int check_time(int d, int m, int y);                    //Member function to check validity of date entered 
         
}; 
 
class Journals: private Books{                                     //Class Journals, having all properties as that of Books, along with 
    long long issue_no;                                         //additional attributes like issue number, date of publishing and volume number 
    int dd,mm,yy; 
    int volume_no; 
    public: 
        void get_info(int cno);                                 //Member function to get information of Journal and store it in "Journals.txt" 
        void print_info(const char* file);                                         //Member function to display information of a journal 
        int ret_accn_no();                                         //Member function to return accession number of a Journal 
        friend int Books::check_time(int d, int m, int y);         //Friend function to check validity of date entered by u ser 
}; 
 
 
class Student{                                                     //Class Student to store student details like name, card number, numbrt of books issued 
    char name[50];                                                //Fine incurred and list of books issued 
    int card_no; 
    int count; 
    int fine; 
    Books b; 
    public: 
        Student(){                                                 //Constructor to initialise count of books to 0 
            count=0; 
        } 
        void get_info(int n);                                     //Member function to take student's details as input 
        int ret_card_no();                                        //Member function to return card number of student 
        void issue_book();                                        //Member function which allows a student to issue a book 
        int ret_count();                                         //Member function to return number of books issued by a student 
        void return_book(int card);                                //Member function which allows a student to return a book  
}; 
     
class Faculty{     
    char name[50]; 
    int card_no; 
    Books b; 
    Journals j; 
    int count_b; 
    int count_j; 
    public: 
        Faculty(){ 
            count_b=count_j=0; 
        } 
        void get_info(int n); 
        int ret_card_no(); 
        void issue_book(); 
        void issue_journal(); 
        int ret_count_books(); 
        int ret_count_journals(); 
        void return_book(int card); 
        void return_journal(int card); 
}; 
 
 
void Books::get_info(int cno, const char *file="Books.DAT"){     
    char ch; 
    cout<<"Enter Name: "; 
    scanf(" %[^\n]s", name);
    cout<<"Enter Author's Name: "; 
    scanf(" %[^\n]s", author); 
    cout<<"Enter Accession Number: "; 
    cin>>accn_no; 
    cout<<"Enter Date of Issuing: "; 
    cin>>ddi>>ch>>mmi>>ch>>yyi; 
     
    while(check_time(ddi,mmi,yyi)==1){ 
        cout<<"Wrong Date! Enter Again: "; 
        cin>>ddi>>ch>>mmi>>ch>>yyi; 
    } 
    card_number=cno; 
    ofstream f1(file, ios::out|ios::app); 
    f1.write((char*)this, sizeof(*this)); 
    f1.close(); 
    (*this).print_info("BooksList.txt"); 
} 
 
void Books::print_info(const char* file){ 
            ofstream f1(file, ios::out|ios::app); 
            f1<<"\n\nDetails Of Book: "; 
            f1<<"\nAccession Number: "<<accn_no; 
            f1<<"\nName of Book: "<<name; 
            f1<<"\nName of Author: "<<author; 
            f1<<"\nDate of Issuing: "<<ddi<<"/"<<mmi<<"/"<<yyi; 
            f1<<"\nIssued By: "<<card_number; 
            f1.close(); 
} 
 
int Books::ret_accn_no(){ 
    return accn_no; 
} 
 
int Books::find_diff(int cdd, int cmm, int cyy){ 
    const int monthdays[13] = {0,0,31,59,90,120,151,181,212,243,273,304,334}; 
    int days=0; 
    days=(cyy-2000)*365+(monthdays[cmm])+cdd; 
    if(cmm>=3) 
        days+=(cyy-2000)/4; 
    else 
        days+=((cyy-2000-1)/4); 
    days=days-(((yyi-2000)*365)+monthdays[mmi]+ddi); 
    if(mmi>=3) 
        days-=(yyi-2000)/4; 
    else 
        days-=((yyi-2000-1)/4);         
    if(days<=15) 
        return 0; 
    return days-15; 
} 
 
int Books::check_time(int d, int m, int y){                             //Member function to check for validity of date 
    if(d>31 || m>12) 
        return 1; 
    time_t t = time(0);   // get time now 
    struct tm * now = localtime( & t ); 
    if ((y==(now->tm_year+1900)) && m==(now->tm_mon+1) && d>(now->tm_mday)) 
        return 1; 
    else if ((y==(now->tm_year+1900)) && m>(now->tm_mon+1)) 
        return 1; 
    else if(y>(now->tm_year+1900)) 
        return 1; 
    if(m==4 || m==9|| m==6 || m==11){ 
        if(d>30) 
            return 1; 
    } 
     
    if(y%4==0){ 
        if(y%100==0){ 
            if(y%400==0){ 
                if(m==2 && d>29) 
                    return 1; 
                else 
                    if(m==2 &&d>28) 
                        return 1; 
            } 
            else 
                if(m==2 &&d>28) 
                    return 1; 
        } 
        else 
            if(m==2 &&d>28) 
                return 1; 
    } 
    else 
        if(m==2 &&d>28) 
            return 1; 
    return 0;     
} 
 
void Journals::get_info(int cno){ 
            char ch; 
            Books::get_info(cno, "Journals.DAT"); 
            cout<<"Enter Issue Number: "; 
            cin>>issue_no; 
            cout<<"\nEnter Date of Publishing: "; 
            cin>>dd>>ch>>mm>>ch>>yy; 
            while(check_time(dd,mm,yy)==1){ 
                cout<<"Wrong Date! Enter Again: "; 
                cin>>dd>>ch>>mm>>ch>>yy; 
            } 
            cout<<"\nEnter Volume Number: "; 
            cin>>volume_no; 
             
            ofstream f1("Journals.DAT", ios::out|ios::app); 
            f1.write((char*)this, sizeof(*this)); 
            f1.close(); 
            (*this).print_info("JournalsList.txt"); 
} 
 
void Journals::print_info(const char* file){ 
    ofstream f1(file, ios::out|ios::app); 
    f1<<"\n\nDetails Of Journal: "; 
    f1<<"\nAccession Number: "<<accn_no; 
    f1<<"\nName of Book: "<<name; 
    f1<<"\nName of Author: "<<author; 
    f1<<"\nDate of Issuing: "<<ddi<<"/"<<mmi<<"/"<<yyi; 
    f1<<"\nIssued By: "<<card_number; 
    f1<<"\nIssue Number: "<<issue_no<<endl; 
    f1<<"\nDate of Publishing: "<<dd<<"/"<<mm << "/"<< yy<<endl; 
    f1<<"\nVolume Number: "<<volume_no<<endl; 
    f1.close(); 
}         
 
 
int Journals::ret_accn_no(){ 
    return accn_no; 
} 
 
void Student::get_info(int n){ 
    cout<<"Enter Student's Name: "; 
    scanf(" %[^\n]s", name); 
    card_no=n; 
} 
 
int Student::ret_card_no(){ 
        return card_no; 
} 
 
void Student::issue_book(){ 
    if(count>=2){ 
        cout<<"Sorry! No more books can be issued!"; 
        return; 
    } 
    else{ 
        b.get_info(card_no); 
        count++; 
        cout<<"\nBook Issued for 15 Days!"; 
    } 
} 
 
 
int Student::ret_count(){ 
    return count; 
} 
         
void Student::return_book(int card){ 
            int temp,i; 
            if(count==0){ 
                cout<<"No Books Issued!";      
            } 
            else{ 
                int flag=0; 
                cout<<"Enter Accession Number of Book: "; 
                cin>>temp; 
                ifstream f1; 
                ofstream f2,f3; 
                f1.open("Books.DAT", ios::in|ios::binary); 
                f2.open("BTemp.DAT", ios::out|ios::app|ios::binary);  
                f3.open("BooksListNew.txt", ios::out|ios::app); 
                f1.seekg(0); 
                Books b; 
                while(!f1.eof()){ 
                    f1.read((char*)&b, sizeof(b)); 
                    if(temp==b.ret_accn_no() && card==card_no &&flag==0){ 
                        flag=1; 
                        time_t t = time(0);   // get time now 
                        struct tm * now = localtime( & t );     
                        fine=b.find_diff((now->tm_mday),(now->tm_mon+1),(now->tm_year+1900)); 
                        cout<<"Book Found! Fine Is: "<<fine; 
                        --count;         
                    } 
                    else{ 
                        f2.write((char*)&b, sizeof(b)); 
                        b.print_info("BooksListNew.txt"); 
                    } 
                } 
                if(flag==0){ 
                    cout<<"No Such Book Issued!"; 
                    fine=0; 
                } 
                f1.close(); 
                f2.close(); 
                f3.close(); 
                remove("Books.DAT"); 
                rename("BTemp.DAT", "Books.DAT"); 
                remove("BooksList.txt"); 
                rename("BooksListNew.txt", "BooksList.txt"); 
            } 
} 
     
void Faculty::get_info(int n){ 
    cout<<"Enter Faculty's Name: "; 
    scanf(" %[^\n]s", name); 
    card_no=n; 
} 
 
int Faculty::ret_card_no(){ 
    return card_no; 
} 
 
 
void Faculty::issue_book(){ 
    if(count_b>=10) 
        cout<<"Maximum Limit Reached!"; 
    else{ 
        b.get_info(card_no); 
        count_b++; 
    } 
} 
 
void Faculty::issue_journal(){ 
    if(count_j>=10) 
        cout<<"Maximum Limit Reached!"; 
    else{ 
        j.get_info(card_no); 
        count_j++; 
    } 
} 
 
 
int Faculty::ret_count_books(){ 
    return count_b; 
} 
int Faculty::ret_count_journals(){ 
    return count_j; 
} 
 
void Faculty::return_book(int card){ 
            int temp,i; 
            if(count_b==0){ 
                cout<<"No Books Issued!";      
            } 
            else{ 
                int flag; 
                cout<<"Enter Accession Number of Book: "; 
                cin>>temp; 
                flag=0; 
                ifstream f1; 
                ofstream f2,f3; 
                f1.open("Books.DAT", ios::in); 
                f2.open("BTemp.DAT", ios::out|ios::app); 
                f3.open("BooksListNew.txt", ios::out|ios::app); 
                f1.seekg(0); 
                Books b; 
                while(!f1.eof()){ 
                    f1.read((char*)&b, sizeof(b)); 
                     if(temp==b.ret_accn_no() && card==card_no){ 
                        flag=1; 
                        cout<<"Book Returned!\n"; 
                        count_b--;         
                    } 
                    else{ 
                        f2.write((char*)&b, sizeof(b)); 
                        b.print_info("BooksListNew.txt"); 
                    } 
                } 
                 
                if(flag==0){ 
                    cout<<"No Such Book Issued!"; 
                } 
                f1.close(); 
                f2.close(); 
                f3.close(); 
                 
                remove("Books.DAT"); 
                rename("BTemp.DAT", "Books.DAT"); 
                remove("BooksList.txt"); 
                rename("BooksListNew.txt", "BooksList.txt"); 
            } 
} 
 
void Faculty::return_journal(int card){ 
            int temp,i; 
            if(count_j==0){ 
                cout<<"No Journals Issued!";      
            } 
            else{ 
                int flag; 
                cout<<"Enter Accession Number of Journal: "; 
                cin>>temp; 
                flag=0; 
                ifstream f1; 
                ofstream f2,f3; 
                f1.open("Journals.DAT", ios::in); 
                f2.open("JTemp.DAT", ios::out|ios::app); 
                f3.open("JournalsListNew.txt", ios::out|ios::app); 
                f1.seekg(0); 
                Journals j; 
                while(!f1.eof()){ 
                    f1.read((char*)&j, sizeof(j)); 
                    if(temp!=j.ret_accn_no()|| card!=card_no){ 
                        f2.write((char*)&j, sizeof(j)); 
                        j.print_info("JournalsListNew.txt"); 
                    } 
                    else if(temp==j.ret_accn_no() && card==card_no){ 
                        flag=1; 
                        cout<<"Book Returned!\n"; 
                        count_j--;         
                    } 
                } 
                 
                if(flag==0){ 
                    cout<<"No Such Journal Issued!"; 
                } 
                f1.close(); 
                f2.close(); 
                f3.close(); 
                 
                remove("Journals.DAT"); 
                rename("JTemp.DAT", "Journals.DAT"); 
                remove("JournalsList.txt"); 
                rename("JournalsListNew.txt", "JournalsList.txt"); 
            } 
} 
 
int main(){ 
    Student s[100]; 
    Faculty f[100]; 
    int ch1,ch2,i,temp,track; 
    int count_s=0; 
    int count_f=0; 
    while(1){ 
    	cout<<"\n\n____________________________________________\n";
        cout<<"\n\n Enter 1 for Student.\n\n 2 for Faculty.\n\n 0 to Exit: "; 
        cout<<"\n____________________________________________\n\n";
        cin>>ch1; 
        if(ch1==0) 
            return 0; 
        if(ch1==1){ 
            cout<<"Enter Student Card Number: "; 
            cin>>temp; 
            track=-1; 
            for(i=0; i<count_s; i++){ 
                if(s[i].ret_card_no()==temp){ 
                    track=i; 
                    break; 
                }     
            } 
            if(track==-1){ 
                s[count_s].get_info(temp); 
                count_s++; 
                track=count_s-1; 
            } 
            cout<<"To Issue Book, Press 1\nTo Return Book, Press 2: "; 
            cin>>ch2; 
            if(ch2==1){ 
                s[track].issue_book(); 
            } 
            if(ch2==2){ 
                s[track].return_book(temp); 
            } 
        } 
        if(ch1==2){ 
            cout<<"Enter Faculty Card Number: "; 
            cin>>temp; 
            track=-1; 
            for(i=0; i<count_f; i++){ 
                if(f[i].ret_card_no()==temp){ 
                    track=i; 
                    break; 
                }     
            } 
            if(track==-1){ 
                f[count_f].get_info(temp); 
                count_f++; 
                track=count_f-1; 
            } 
            cout<<"To Issue Book, Press 1\nTo Return Book, Press 2\nTo Issue Journal, Press 3\nTo Return Journal, Press 4: "; 
            cin>>ch2; 
            if(ch2==1){ 
                f[track].issue_book(); 
            } 
            if(ch2==2){ 
                f[track].return_book(temp); 
            } 
            if(ch2==3){ 
                f[track].issue_journal(); 
            } 
            if(ch2==4){ 
                f[track].return_journal(temp); 
            } 
        } 
    } 
    return 0; 
}
