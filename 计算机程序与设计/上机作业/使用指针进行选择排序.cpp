#include<stdio.h>
#include<stdlib.h>
struct S{
	float value;
	char data[100];
};
void swap(struct S *a,struct S *b){
	struct S*temp=a;
	a=b;
	b=temp;
} 
void sort(struct S **p_list,int N){
	int i,j,t;
	int k;
	for(i=0;i<N-1;i++){
		for(j=i+1;j<N;j++){
			t=i;
			if((*(p_list[j])).value<(*(p_list[i])).value)
			t=j;
		}
		if(t!=i){
		swap((p_list[i]),(p_list[j]));
		}
	}
} 
int main(){
	int N=30,i;
	struct S*list=(struct S*)malloc(N*sizeof(struct S));
	struct S **p_list=(struct S**)malloc(N*sizeof(struct S*));
	for(i=0;i<N;i++){
		list[i].value=30-i;
		p_list[i]=list+i;
		}
		sort(p_list,N);
		for(i=0;i<N;i++)
		printf("%2.01f,",(*(p_list[i])).value);
		return 0; 
} 
