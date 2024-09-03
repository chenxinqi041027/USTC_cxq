#include<stdio.h>
#include<stdlib.h>
typedef struct link{		//定义链表
        int data;
        struct link *next;
}link;
link * initLink(int n){         //初始化链表，获取数据
        link *p,*q;
        printf("Input:");		//输入数据
        for(int i=0;i<n;i++){
                link *temp=(link*)malloc(sizeof(link));         //动态分配内存
                scanf("%d",&temp->data);        //填充数据
                temp->next=NULL;      //最后一个节点指针NULL
                if(i==0){
                        q=temp;         //给q,p赋值第一个结点
                        p=temp;
                }
                else{           //形成一条p链
                        p->next=temp;   //p陆续指向后边的结点
                        p=p->next;      //p移动到最后
                }
        }
        return q;	//返回头指针
}
link * turnlist(link *L){
    link *p,*q,*r;
    p=L;//p,q,r分别为三个不断移动的指针
    q=p->next;
    r=q->next;

    q->next=p;//进行第一个结点转换时要把第一个结点的尾指针变为空。
    L->next=NULL;

    while(r)
    {
       q->next=p;
       p=q;
       q=r;
       r=r->next;//改变结点后继续向下移动
    }//当r为空时，q指向最后一个元素
    q->next=p;
    return q;
}
int main(){
        int n;                //链表的长度
        printf("The length of the list:");
        scanf("%d",&n);
        link *L = initLink(n);  //初始化L
        L = turnlist(L);
        printf("Result:");
        while(L){//输出数据
                printf("%d ",L->data);
                L=L->next;
        }
        return 0;
}
