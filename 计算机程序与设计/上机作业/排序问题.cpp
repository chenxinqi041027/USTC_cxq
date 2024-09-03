#include<stdio.h>
/*void jiaohaun(int num,int a[])
{
	int i,j,t;
	for(i=0;i<num-1;i++){
		for(j=i+1;j<num;j++){
			if(a[i]>a[j]){
			t=a[i];
			a[i]=a[j];
			a[j]=a[i];}
		}
	}
	for(i=0;i<num;i++) printf("%d",a[i]);
}
void xuanze(int num,int a[]){
	int i,j,t,k;
	for(i=0;i<num-1;i++){
		k=i;
		for(j=i+1;j<num;j++){
			if(a[k]>a[j]){
			k=j; 
			}else 
			t=a[i];a[j]=a[k];a[k]=t;
		}
	}
	for(i=0;i<num;i++) printf("%d",a[i]);
}
void maopao(int num,int a[]){
	int i,j,t,m;
	for(i=0;i<num-1;i++){
		m=1;
		for(j=0;j<num-1-i;j++){
			if(a[j]>a[j+1])
			{t=a[j];a[j]=a[j+1];a[j+1]=t;
			m=0;
		}
		}
	if(m) break;
	}
	for(i=0;i<num;i++) printf("%d",a[i]);
}*/
int main(){
	int num=7;
	int a[num]={1,4,5,8,3,9,8};
	int i,j,t,k,m;
	printf("½»»»");
	for(i=0;i<num-1;i++){
		for(j=i+1;j<num;j++){
			if(a[i]>a[j]){
			t=a[i];
			a[i]=a[j];
			a[j]=t;}
		}
	}
	for(i=0;i<num;i++) printf("%d",a[i]);
	printf("Ñ¡Ôñ");
		for(i=0;i<num-1;i++){
		k=i;
		for(j=i+1;j<num;j++){
			if(a[k]>a[j]){
			k=j; 
			} 
		}
		t=a[i];a[i]=a[k];a[k]=t;
	}
	for(i=0;i<num;i++) printf("%d",a[i]);
	printf("Ã°ÅÝ");
	for(i=0;i<num-1;i++){
		m=1;
		for(j=0;j<num-1-i;j++){
			if(a[j]>a[j+1])
			{t=a[j];a[j]=a[j+1];a[j+1]=t;
			m=0;
		}
		}
	if(m) break;
	}
	for(i=0;i<num;i++) printf("%d",a[i]);
	
	
}
