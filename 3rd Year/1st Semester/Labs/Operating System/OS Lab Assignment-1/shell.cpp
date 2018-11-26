#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <sys/param.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <dirent.h>
#include <fstream>

using namespace std;

char *read_line(){

	int bufsize=1024;
  	int pos=0;
  	char *buff=(char *)malloc(sizeof(char)*bufsize);
  	int c;
  	while (1) {
    	c = getchar();
    	if (c==EOF || c=='\n') {
      		buff[pos]='\0';
      		return buff;
    	} 
    	else
      		buff[pos]=c;
    	pos++;
  	}
}

vector<string> string_tokenize(char *line){
    int i=0;
    vector<string> tokens;
    string token;

    while(line[i]){
    	if(line[i]==' '){
    		tokens.push_back(token);
    		token.clear(); i++;
    	}
    	else{
    		token.push_back(line[i]);
    		i++;
    	}
    }
    if(!token.empty()) tokens.push_back(token);
    return tokens;
}

int main() {

	char *line;
	vector<string> token;

	while(1){

		char buffer[MAXPATHLEN];
		char *path = getcwd(buffer, MAXPATHLEN);
        strcat(path,"$");
        printf("%s@",getenv("USER") );
        printf("%s ",path);
		line=read_line();
        if(!strcmp(line,"exit"))
            break;
        token=string_tokenize(line);
		string command=token[0];
		if(command=="echo"){
			string op;
			unsigned int i=1;
			while(i<token.size()){
				op += token[i] + " ";
				i++;
			}
			cout << op << endl;
		}

		else if(command == "cd") {
			if(token.size()>1) {
		    	int rc = chdir(token[1].c_str());
			}
		    else {
		    	struct passwd *pw = getpwuid(getuid());
				const char *homeDir = pw->pw_dir;
				int rc = chdir(homeDir);
		    }
		    char buffer[MAXPATHLEN];
		    string CurrentPath = getcwd(buffer, MAXPATHLEN);
	        cout << "Current directory: " << CurrentPath << endl;
		}

		else if(command == "pwd") {
			char buffer[MAXPATHLEN];
		    string CurrentPath = getcwd(buffer, MAXPATHLEN);
	        cout << "Current directory: " << CurrentPath << endl;
		}

		else if(command == "ls") {
			DIR *dir;
			struct dirent *ent;
			if ((dir = opendir(".")) != NULL) {
			  	while((ent = readdir(dir)) != NULL) {
			    	cout << ent->d_name << endl;
			  	}
			  	closedir (dir);
			} 
			else {
				cout << "could not open directory" << endl;
			}
		}

		else if(command == "cp") {
			ifstream  src(token[1].c_str(), ios::binary);
		    ofstream  dst(token[2].c_str(), ios::binary);

		    dst << src.rdbuf();
		}

		else {
			cout << "Unknown command." << endl;
		}
	}
	return 0;
}
