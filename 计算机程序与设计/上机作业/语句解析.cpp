#include<stdio.h>
#include<string.h>
#define N 225
int main(){
	char ch[N];
	int i,z[3]={0};
	gets(ch);
	for(i=0;i<strlen(ch);i++){
		if(ch[i]=='=')
		{
			if(ch[i+1]>='0'&&ch[i+1]<='9')
				z[ch[i-1]-'a']=(ch[i+1]-'0');
			else
				z[ch[i-1]-'a']=z[ch[i+1]-'a'];
		}
	}
	printf("a = %d\nb = %d\nc = %d",z[0],z[1],z[2]);
	return 0;
} 
