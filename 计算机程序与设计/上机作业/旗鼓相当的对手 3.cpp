#include<stdio.h>
#include<math.h>
#include<string.h>
int i,j;
struct student{
	char name[10];
	int Chinese,math,English;
	int sum; 
};
 
void paiXu(struct student stu1,struct student stu2)
{
	if(strcmp(stu1.name,stu2.name) < 0)
	{
		printf("%s",stu1.name);
		printf(" %s",stu2.name);
	}	
	if(strcmp(stu1.name,stu2.name) > 0)
	{
		printf("%s",stu2.name);	
		printf(" %s",stu1.name);
	}
	printf("\n");
}
void swap(student*a,student*b){
	student temp=*a;
	*a=*b;
	*b=temp;
}
 
int main()
{
	int n,a,b,c,d;
	struct student stu[10000];
	scanf("%d",&n);
	for(i = 0;i < n;i ++)
	{
		scanf("%s%d%d%d",stu[i].name,&stu[i].Chinese,&stu[i].math,&stu[i].English);
		stu[i].sum = stu[i].Chinese + stu[i].math + stu[i].English;
	}
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++)
		if(strcmp(stu[i].name,stu[j].name)>0){
		swap(&stu[i],&stu[j]);
				}
	} 
	for(i = 0;i <n-1;i ++) 
	{
		for(j = i+1;j<n;j ++)
		{
			a = stu[i].Chinese -stu[j].Chinese;
			b = stu[i].math -stu[j].math;
			c = stu[i].English -stu[j].English;
			d = stu[i].sum -stu[j].sum;
			if(abs(a)<=5 && abs(b)<=5 && abs(c)<=5 && abs(d)<=10)
			{
				paiXu(stu[i],stu[j]);
			}
		}
	}
	return 0;
 }
 /*4
 xiaohong 120 100 99
 xiaoming 121 103 98
 david 115 102 100
 alex 118 101 102 */
