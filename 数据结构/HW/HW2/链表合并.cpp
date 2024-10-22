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

link * mergeList(link *a,link *b){      //头插法合并两条传入的链表
        link *o,*p,*q;      //这里p中转，o指向最后一个元素，q指向最新元素
        int flag=1;                //第一次合并使用
        while (a||b){
                if(!a){         //如果a空了，直接指向b的结点
                        //printf("get %d from b\n",b->data);
                        p=b;
                        b=b->next;
                }               
                else if(!b||a->data<=b->data){//如果b空了或者a的数据<=b的数据时，p指向a的结点，获取a指向的数据
                        //printf("get %d from a\n",a->data);
                        p=a;
                        a=a->next;
                }             
                else {
                        //printf("get %d from b\n",b->data);//否则从b获取数据
                        p=b;
                        b=b->next;
                }
                if(flag){

                        o=q=p;          //初始化指针
                        flag=0;            //使用一次舍弃
                }
                else {
                        p->next=q;        //使取下的结点连上合并后的链
                        q=p;              //更新q的位置到最新结点
                }
        }
        o->next=NULL;   //使最后一个指向NULL输出结束条件
        free(b);        //a，b，q的空间可以释放
        free(a);
        return q;
}
int main(){
        int m,n;                //a，b的长度
        printf("The length of the first list:");
        scanf("%d",&m);
        link *a = initLink(m);  //初始化a
        printf("The length of the second list:");
        scanf("%d",&n);
        link *b = initLink(n);  //初始化b

        link *c = mergeList(a,b);//合并a，b
        printf("Result:");
        while(c){
                printf("%d ",c->data);
                c=c->next;
        }
        return 0;
}
