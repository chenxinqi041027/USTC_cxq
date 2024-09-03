#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 20
//创建结点
typedef struct BiNode {
	char data;
	struct BiNode *lchild, *rchild;
}BiNode, *BiTree;

//先序遍历法创建二叉树
void CreateBTree(BiTree &T) {
	char ch;
	scanf("%c", &ch);
	if (ch == '#')T = NULL;//给左或右赋值为NULL
	else {
		T = new BiNode;
		T->data = ch;
		CreateBTree(T->lchild);//递归创建左子树
		CreateBTree(T->rchild);//递归创建右子树 
	}
}

//先序遍历二叉树输出
void PreOrder(BiTree &T){
    if(T != NULL){
        printf("%c ",T->data);
        PreOrder(T->lchild);//递归遍历左子树
        PreOrder(T->rchild);//递归遍历右子树
    } //else printf("#");
}

int main() {
	
    BiTree T;
	printf("Input:\n");
	CreateBTree(T);//先序遍历建立二叉树 
    printf("PreOrder Result:\n");
	PreOrder(T);//先序遍历输出二叉树
    printf("\n");
    free(T);
}

/*
AB#DG###CE#H##F##

AB#C##D#E##
C B E D A

A#B#C##
C B A

ABC####
C B A

AB#D#G##CE#H##F##  
G D B H E F C A 
*/