#include<stdio.h>
#include<math.h>
struct coins{
	int x,y;
};
void swap(coins*a,coins*b){
	coins temp=*a;
	*a=*b;
	*b=temp;
	return;
}
int main(){
	while(1){
	struct coins a[100000];
	int N;
	scanf("%d",&N);
	a[0].x=a[0].y=0;
	N++;
	for(int i=1;i<N;i++){
		scanf("%d%d",&a[i].x,&a[i].y);
	}
	int j;
	for(int i=0;i<N-1;i++){
			for(j=i+1;j<N;j++)
			if(a[i].y>a[j].y) swap(&a[i],&a[j]);
		}	
	int flag=0;
	for(int i=0;i<N-1;i++){
		if(abs(a[i].x-a[i+1].x)>abs(a[i].y-a[i+1].y)){
			printf("Notabletocatch\n");
			flag=1;
			break;
		}
	}
	if(flag==0) printf("Abletocatch\n");
	}
	return 0;
}

