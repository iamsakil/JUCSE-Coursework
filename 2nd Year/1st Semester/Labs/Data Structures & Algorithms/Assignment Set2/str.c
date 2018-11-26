#include <stdio.h>
#include <stdlib.h>
typedef struct String
{
	char *s;
	int len;
	int max_len;
}String;

String* initString(int l){
	String *S;
	S->s=(char*)malloc(sizeof(char)*l + sizeof(int) + 1);
	S->len=0;
	S->max_len=l;
	return S;
}
int length(String s){
	return s.len; 
}
int compare(String s1,String s2){
	if(s1.len > s2.len){
		return 1;
	}else if(s1.len<s2.len){
		return -1;
	}else if(s1.len==s2.len){
		int i;
		for(i=1;i<=s1.len;i++){
			if(s1.s[i]>s1.s[i]){
				return 1;
			}else if(s1.s[i]<s1.s[i]){
				return -1;
			}else
				return 0;
		}
	}
	else{
		return 0;
	}
}
String* concat(String s1,String s2){
	String *s3=initString(s1.len+s2.len);
	int i;
	for(i=1;i<s1.len;i++){
		s3->s[i]=s1.s[i];
	}
	for(i=1;i<s2.len;i++){
		s3->s[i+s1.len]=s2.s[i];
	}
	return s3;
}
int substrSer(String s,char c[],int n){
	int i;
	for(i=0;i<s.len-n;i++){
		int j;int flag=1;
		for(j=0;j<n;j++){
			if(s.s[i]!=c[j]){
				flag=0;
				break;
			}
		}
		if(flag==1){
			return 1;
		}
	}return 0;
}
void freq(String s){
	int alpha[26];
	int i;
	for(i=0;i<26;i++){
		alpha[i]=0;
	}
	for(i=1;i<=s.len;i++){
		int a=65;
		if((int)s.s[i]>=97)
		a=97;
		alpha[(int)s.s[i]-a]++;
	}
	for(i=0;i<26;i++){
		printf("%c=%d\n",(char)(i+65),alpha[i]);
	}
}
void replace(String *s,char x,char y){
	int i;
	for(i=1;i<=s->len;i++){
		if(s->s[i]==x)
			s->s[i]=y;
	}
}
int wordCount(String s){
	int i;
	int count=0;
	for(i=1;i<s.len;i++){
		if(s.s[i]==' '){
			count++;
		}
	}return count;
}
void reverse(String *s){
	int i;
	for(i=1;i<=s->len/2;i++){
		char temp=s->s[i];
		s->s[i]=s->s[s->len-i+1];
		s->s[s->len-i+1]=temp;
	}
}
void display(String s){
	int i;
	for(i=1;i<=s.len;i++){
		printf("%c",s.s[i]);
	}
	printf("\n");
}
void set(String *S,char x[],int n){
	int i;
	for(i=1;i<=n;i++){
		S->s[i]=x[i-1];
	}S->len=n;
}
int main(){
	String *S=initString(100);
	char x[16]="my name is khan";
	set(S,x,16);
	display(*S);
	reverse(S);
	display(*S);
	freq(*S); 
	return 0;
}
