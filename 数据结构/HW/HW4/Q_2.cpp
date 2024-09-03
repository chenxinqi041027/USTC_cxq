#include<stdio.h>
#define Maxsize 50
//定义队列
typedef struct{
    int data[Maxsize];//存储行的数据
    int front,rear;//头尾指针
}SqQueue;
 
//初始化
void InitQueue(SqQueue &Q){
    Q.rear=Q.front=0;
}

//判空
int IsEmpty(SqQueue Q){
    if(Q.rear==Q.front)
        return 1;
    return 0;
}

//入队
int EnQueue(SqQueue &Q,int x){
    if((Q.rear+1)%Maxsize==Q.front)//判断队列是否满了
        return 0;
    Q.data[Q.rear]=x;
    Q.rear=(Q.rear+1)%Maxsize;
    return 1;
}

//出队
int DeQueue(SqQueue &Q,int &x){
    if(IsEmpty(Q))
        return 0;
    x=Q.data[Q.front];
    Q.front=(Q.front+1)%Maxsize;
    return 1;
}

//获取队头
int GetTop(SqQueue Q,int &x){
	if(IsEmpty(Q))
		return 0;
	x=Q.data[Q.front];
	return 1;
} 
 
void YangHuiTriangle(int N){
	int n,x,i,temp;
	SqQueue Q;
	InitQueue(Q); 
	
	EnQueue(Q,1);
	for(n=2;n<=N;n++){		
		EnQueue(Q,1);//每行第一个元素是1
		for(i=1;i<=n-2;i++){
			DeQueue(Q,temp);//出队	
			printf("%d ",temp); 
			GetTop(Q,x);	 
			temp=temp+x;//将队首的两个元素相加得到新的元素
			EnQueue(Q,temp);
		}
		DeQueue(Q,x);	
		printf("%d ",x);
		EnQueue(Q,1);//结尾安插一个1
		printf("\n");
	}
    //最后一行输出
	while(!IsEmpty(Q)){
		DeQueue(Q,x);
		printf("%d ",x);
	}
 
}
 
int main(){
    int N;
    printf("Input:");
    scanf("%d",&N);
    YangHuiTriangle(N);
	return 0;
}