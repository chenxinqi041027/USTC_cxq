#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct BiNode
{
    char data;
    struct BiNode *lchild, *rchild;
}BiNode, *BiTree;

typedef struct BiThrNode
{
    char data;
    int rtag,ltag;
    struct BiThrNode *lchild, *rchild;
}BiThrNode, *BiThrTree;

BiThrNode *pre;


void CreateBiTree(BiTree& T)
 {
 	char ch;
	scanf("%c",&ch);
	getchar();
	if(ch=='#') {
	T=NULL;
	return;}
	else{
		T->lchild = (BiTree)malloc(sizeof(BiNode));
  	    T->rchild = (BiTree)malloc(sizeof(BiNode));
		T->data=ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}

void PreOrder(BiTree T){
	if(T==NULL)	return; 
	else{
		printf("%c ",T->data);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}

void CreatBiThr(BiThrTree* bt, BiTree T)
{
	if(T==NULL)  {
		*bt=NULL;
		return;
	}
	else
	{
	  (*bt)=(BiThrTree)malloc(sizeof(BiThrNode));
	  (*bt)->data=T->data;
	  (*bt)->ltag=(*bt)->rtag=0;
	  CreatBiThr(&(*bt)->lchild, T->lchild);
	  CreatBiThr(&(*bt)->rchild, T->rchild);
    }   
} 

//把给定树复制到BiThrTree中 

void PostThreding(BiThrTree BT)
{
	if (BT)
	{
		PostThreding(BT->lchild);
		PostThreding(BT->rchild);
		if (!BT->ltag)
		{
			BT->ltag =1;
			BT->lchild = pre;
		}
		if (!pre->rtag)
		{
			pre->rtag =1;
			pre->rchild = BT;
		}
		pre = BT;
	}
}
//在树中构建完线索结构 

void PostorderThreding(BiThrTree *p, BiThrTree T)
{
	//p结点为头结点，T结点为树根结点
	*p = (BiThrNode*)malloc(sizeof(struct BiThrNode));
	(*p)->ltag = 0;
	(*p)->rtag = 1;
	(*p)->rchild=NULL;
 
	if (!T)  (*p)->lchild=NULL;
	else
	{
		(*p)->lchild= T;
		pre = *p;
		PostThreding(*p);  
		if (pre->rtag != 0)  // 最后一结点没有右孩子时 
		{
			pre->rchild= *p;  // 最后一个结点的后继指向头结点  
			pre->rtag =1;
		}
		(*p)->ltag = 0;
	}
}
void PostOrderTraverse(BiThrTree T)
{
	BiThrTree p=T;
	printf("p=%c %d %d\n",p->data,p->ltag,p->rtag);
	while (p&&(p->ltag ==0 || p->rtag == 0))
	{ 
		printf("get %c\n",p->data);
		while (p&&p->ltag == 0)
			p = p->lchild;
		if (p&&p->rtag == 0)                 
		{
			p = p->rchild;
		}
	}

	printf("%c ",p->data);
	while (p != T)                        //p不为头结点  
	{
		if (p->rtag ==0)              //P有右孩子 
		{
			if (pre->rtag == 1 || p == pre->rchild) //若p是双亲的右孩子或是独生左孩子，则后继为双亲  
				p = pre;
			else
			{
				p = pre->rchild;              //后继为双亲的右子树上按照后序遍历访问的第一个结点。  
				while (p->ltag == 0 || p->rtag == 0)
				{
				while (p->ltag == 0)
						p = p->lchild;
				if (p->rtag == 0)
						p = p->rchild;
				}
			}
		}
		else  p = p->rchild;             //p->rchild即为后继 
		printf("%c ",p->data);
	}
}

int main()
{
    BiTree A= (BiTree)malloc(sizeof(BiNode));
	BiThrTree D = NULL;
	BiThrTree BD = NULL;

 
	printf("按照前序遍历创建二叉树：\n");
	CreateBiTree(A);
	printf("先序遍历：\n");
	PreOrder(A);
	printf("\n后序线索化\n" );
	CreatBiThr(&D,A);
	PostorderThreding(&BD, D);
	printf("后序线索化后输出：\n");
	PostOrderTraverse(BD);
	return 0;
}
/*
A,B,#,D,G,#,#,#,C,E,#,H,#,#,F,#,#

*/