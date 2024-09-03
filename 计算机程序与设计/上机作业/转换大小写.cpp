#include<stdio.h>
int main(){
	char c,i;
	for(i=0;i<5;i++){
		c=getchar();
		if(c>='A' && c<='Z')
			putchar(c-'A'+'a');
		else putchar(c);
		
	}
} 
