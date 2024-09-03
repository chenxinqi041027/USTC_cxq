#include <stdio.h>
#define MaxSize 10000

//Ackerman递归算法
int Ack1(int m,int n){
	int q;
	if(m==0)
		return n+1;
	else if(n==0)
		return Ack1(m-1,1);
	else{
		q=Ack1(m,n-1);
		return Ack1(m-1,q);
	}

}

//Ackerman非递归算法
int Ack2(int m,int n){
	struct{
		int am,an;  //分别保存m和n值
		int af;     //保存akm(m,n)值
		int flag;  //标识是否求出akm(m,n)值，1:表示未求出，0:表示已求出
	}St[MaxSize];

	int top=0;  //栈指针
	top++;     //初值进栈
	St[top].am=m; St[top].an=n; St[top].flag=1;
	while(top>0){   //栈不空时循环
		if (St[top].flag==1)   //未计算出栈顶元素的af值
		{ 
			if (St[top].am==0)      //(1)式
			{
				St[top].af=St[top].an+1;
				St[top].flag=0;
			} 
			else if (St[top].an==0) //(2)式
			{
				top++;
				St[top].am=St[top-1].am-1;
				St[top].an=1;
				St[top].flag=1;
			}
			else                    //(3)式
			{
				top++;
				St[top].am=St[top-1].am;
				St[top].an=St[top-1].an-1;
				St[top].flag=1;
			}
		}
		else if (St[top].flag==0)  //已计算出vf值
		{
			if (top>0&&St[top-1].an==0) //(2)式
			{
				St[top-1].af=St[top].af;
				St[top-1].flag=0;
				top--;
			}
			else if (top > 0) //(3)式
			{
				St[top-1].am=St[top-1].am-1;
				St[top-1].an=St[top].af;
				St[top-1].flag=1;
				top--;
			}
		}
		if(top==0 && St[top].flag==0) //栈中只有一个已求出vf的元素时退出循环
			break;
	}
	return St[top].af;

}




/*void main()
{
	int num1=0,num2=0,num3=0;
// 	num1=akm1(0,1);
// 	num2=akm1(1,2);
// 	num3=akm1(3,3);

	num1=akm2(0,1);
	num2=akm2(1,2);
	num3=akm2(3,3);

	printf("akm2(0,1)= %d\n",num1);
 	printf("akm2(1,2)= %d\n",num2);
 	printf("akm2(3,3)= %d\n",num3);

}*/



int main(){
    int m,n;
    printf("Input m:");
    scanf("%d",&m);
    printf("Input n:");
    scanf("%d",&n);
    printf("%d\n",Ack1(m,n));
    printf("%d",Ack2(m,n));
    return 0;
}