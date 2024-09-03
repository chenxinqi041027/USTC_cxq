//--------------二叉树--------------二叉树--------------二叉树--------------
#include<stdio.h>
#include<stdlib.h>
#define MAX 20
typedef struct BiNode {
	char data;
	struct BiNode *lchild, *rchild;
}BiNode, *BiTree;
 
//创建二叉树
void CreateBTree(BiTree &T) {
	char ch;
	int i;
	scanf("%c", &ch);
	if (ch == '#')T = NULL;//给左或右赋值为NULL
	else {
		T = new BiNode;
		T->data = ch;
		CreateBTree(T->lchild);//根变成左子 
		CreateBTree(T->rchild);//根变成右子 
	}
}
//输出二叉树中从每个叶子结点到根结点的路径
void PathTree(BiTree T, char path[], int location)
{	
	if (T == NULL) return;
	if (T->lchild == NULL && T->rchild == NULL)//如果是叶子则存到数组
	{
		path[location] = T->data;
		printf("%c path: ", T->data);//输出叶子结点作为题目
		for (int i = location; i >= 0; i--)
			printf("%c ", path[i]);
		printf("\n");
	}
	else
	{
		path[location] = T->data;//从根开始传入数组
		location++;
		PathTree(T->lchild, path, location);//遍历根
		PathTree(T->rchild, path, location);//遍历根
		location--;//因为上面有location++，所以这个时候location的位置是没有值的，所以要location--
	}
}

int main() {
	BiTree T;
	char path[MAX];
	int location = 0;
	printf("Input:\n");
	CreateBTree(T);//建立 
	PathTree(T,path,location);//输出各叶子到根的路径
	return 0;
}