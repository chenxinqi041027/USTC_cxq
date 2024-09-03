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

//�Ѹ��������Ƶ�BiThrTree�� 

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
//�����й����������ṹ 

void PostorderThreding(BiThrTree *p, BiThrTree T)
{
	//p���Ϊͷ��㣬T���Ϊ�������
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
		if (pre->rtag != 0)  // ���һ���û���Һ���ʱ 
		{
			pre->rchild= *p;  // ���һ�����ĺ��ָ��ͷ���  
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
	while (p != T)                        //p��Ϊͷ���  
	{
		if (p->rtag ==0)              //P���Һ��� 
		{
			if (pre->rtag == 1 || p == pre->rchild) //��p��˫�׵��Һ��ӻ��Ƕ������ӣ�����Ϊ˫��  
				p = pre;
			else
			{
				p = pre->rchild;              //���Ϊ˫�׵��������ϰ��պ���������ʵĵ�һ����㡣  
				while (p->ltag == 0 || p->rtag == 0)
				{
				while (p->ltag == 0)
						p = p->lchild;
				if (p->rtag == 0)
						p = p->rchild;
				}
			}
		}
		else  p = p->rchild;             //p->rchild��Ϊ��� 
		printf("%c ",p->data);
	}
}

int main()
{
    BiTree A= (BiTree)malloc(sizeof(BiNode));
	BiThrTree D = NULL;
	BiThrTree BD = NULL;

 
	printf("����ǰ�����������������\n");
	CreateBiTree(A);
	printf("���������\n");
	PreOrder(A);
	printf("\n����������\n" );
	CreatBiThr(&D,A);
	PostorderThreding(&BD, D);
	printf("�����������������\n");
	PostOrderTraverse(BD);
	return 0;
}
/*
A,B,#,D,G,#,#,#,C,E,#,H,#,#,F,#,#

*/