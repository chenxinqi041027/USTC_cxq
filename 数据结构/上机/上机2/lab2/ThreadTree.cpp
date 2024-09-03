#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Link 0
#define Thread 1
#define N 1001
/*
LTag  :若 LTag=0, lchild域指向左孩子；若 LTag=1, lchild域指向其前驱。
RTag  :若 RTag=0, rchild域指向右孩子；若 RTag=1, rchild域指向其后继。 
*/
//创建线索二叉树结点
typedef struct TreadNode {
    char data;
    struct TreadNode *lchild,*rchild;
    int ltag,rtag;//左右标志
}ThreadNode, *ThreadTree;
//先序遍历创建给定的二叉树
void CreateThreadTree(ThreadTree &T1){
    char ch;
    scanf("%c",&ch);
    if(ch == '#') T1 = NULL;
    else{
        T1 = new ThreadNode;
        T1->data = ch;
        CreateThreadTree(T1->lchild);
        CreateThreadTree(T1->rchild);
    }
}
//初始化tag
void InitThread(ThreadTree T1){
    if(T1 != NULL){
        T1->ltag = Thread;
        T1->rtag = Thread;
        InitThread(T1->lchild);
        InitThread(T1->rchild);
    }
}

ThreadNode* pre = NULL;//pre指向当前访问结点的前驱结点 
//后序线索化二叉树
void CreatePostThread(ThreadTree &p){
    if(p){
        CreatePostThread(p->lchild);  //递归后序线索化左子树
        CreatePostThread(p->rchild);  //递归后序线索化右子树

        p->ltag = (p->lchild) ? Link : Thread;
        p->rtag = (p->rchild) ? Link : Thread;

        if(pre){    //修改对应的指针域
            if(pre->ltag == Thread)
                p->lchild = pre; //改为前驱
            if(pre->rtag == Thread)
                pre->rchild = p; //改为后继
        }
        pre = p;    //更新pre指针
    }
}

char Stack[N];
int top = 0, cnt = 0;
void Push(char data){
	Stack[++top] = data;
}

void PostOrderThreadTraverse(ThreadTree &p){ //后序遍历后序线索化二叉树
    Push(p->data); //将数据逆序压入栈中
    if(p->lchild){ 
        if(p->ltag==Thread)
            PostOrderThreadTraverse(p->lchild);    //此时左孩子域为线索，指向直接前驱（找左端）
		if(p->ltag==Link){
            if((p->rtag==Link) )
                PostOrderThreadTraverse(p->rchild);    //此时右孩子域为右子树，为直接前驱
            else
                PostOrderThreadTraverse(p->lchild);    //其他情况，左孩子域指向直接前驱 （找左端）
        }
    }
    
}

/*void TestTraverse(ThreadTree &p){
	printf("%c %d %d %d\n", p->data, p->ltag, p->rtag, (p->rchild == NULL ? 1 : 0));
	if(p->lchild) TestTraverse(p->lchild);
	if(p->rchild) TestTraverse(p->rchild);
	return;
}*/


int main() {
    ThreadTree T1;
    printf("Input InOrder Sequence:\n");
    CreateThreadTree(T1);
    printf("Create Successfully\n");
    //TestTraverse(T1);
    InitThread(T1);
    CreatePostThread(T1);
    printf("Create Successfully\n");
    printf("PostOrderTraverse Result:\n");
    PostOrderThreadTraverse(T1);
    while(top)printf("%c ",Stack[top--]);//逆序输出
    printf("\n");
	return 0;
}

/*
AB#C##D#E##
C B E D A

A#B#C##
C B A

ABC####
C B A

AB#D#G##CE#H##F##  
G D B H E F C A 
*/