#include<stdio.h>
void REMOVE(int);//移除
void PUT(int);//放入
int a = 0;
int main(){
	int n;/*the value of n in x3100*/ 
	scanf("%d",&n);
	printf("result:\n");
	REMOVE(n);
	return 0;
}
void REMOVE(int n){
	if(n==0) return;/*the state remains*/
	if(n==1){
		a = a + 1;
		printf("%d\n",a);
		return;
	}else {
		REMOVE(n-2);
		int temp = 1;
		for(int i=0;i<n-1;i++){
			temp  = 2*temp;
		}
		a = a + temp;
		printf("%d\n",a);
		PUT(n-2);
		REMOVE(n-1);
	}
	return;
}
void PUT(int n){
	if(n==0) return;
	if(n==1){
		a = a - 1;
		printf("%d\n",a);
		return;
	}else {
		PUT(n-1);
		REMOVE(n-2);
		int temp = 1;
		for(int i=0;i<n-1;i++){
			temp = 2*temp;
		}
		a = a - temp;
		printf("%d\n",a);
		PUT(n-2);
	}
}
