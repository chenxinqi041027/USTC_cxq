#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//创建线索二叉树结点
typedef struct TreadNode {
    char data;
    struct TreadNode *lchild,*rchild;
    int ltag,rtag;//左右标志
}ThreadNode, *ThreadTree;
//先序遍历创建二叉树
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
        T1->ltag = 0;
        T1->rtag = 0;
        InitThread(T1->lchild);
        InitThread(T1->rchild);
    }
}
ThreadNode* pre = NULL;//前驱结点 
/*//线索化
void visit1(ThreadNode* q) {
	if (q->lchild == NULL) {	//左子树为空，建立前驱线索
		q->lchild = pre;
		q->ltag = 1;
	}
	if (q->rchild == NULL){
		q->rchild = pre;
		q-> rtag = 1;
	}
	if (pre != NULL) {	
		if(pre->rtag) pre->rchild = q;
		if(pre->ltag) q->lchild = pre;
	}
	pre = q;			//标记当前结点为刚刚访问过的结点
}

//遍历
void PostThread(ThreadTree T1) {
	if (T1 != NULL) {
		if (T1->ltag == 0)		//若rchild不是后继线索
			PostThread(T1->lchild);	//则线索化左子树
		if (T1->rtag == 0)		//若lchild不是前驱线索
			PostThread(T1->rchild);	//则线索化右子树
		visit1(T1);				//处理根节点
	}
}
//创建前驱节点
void CreatePreThread(ThreadTree &T1) {
	pre = NULL;			//pre初始化为NULL
	if (T1 != NULL) {	//非空二叉树才能线索化			
		PostThread(T1);	//后序线索化二叉树
		if (pre->lchild == NULL)	
			pre->ltag = 1;			//处理遍历的最后一个结点
	}
}
//寻找先序后继
ThreadNode* NextNode(ThreadNode* p) {
	if (p->ltag == 0) {		//若ltag=0，说明所找结点有左孩子
		if (p->rtag == 0)		//若rtag=0，说明所找结点有右孩子，根据后序遍历的特点(左-右-根)，则后继为根节点
			return NULL;
		else
			return p->rchild;  //若ltag=1，说明所找结点无左孩子，则后继结点为其右孩子
	}
	else
		return p->rchild;	//若ltag=1，说明所找结点无左孩子，则返回后继线索
}
//打印结点
void visit2(ThreadNode* p) {
	printf("%c %d %d\n", p->data,p->ltag,p->rtag);
}
//遍历
void PreOrder(ThreadNode* T1) {
	for (ThreadNode* p = T1; p != NULL; p = NextNode(p))
		visit2(p);
}*/
void PostThraed(ThreadTree p){
	if(p){
		PostThraed(p->lchild);
		PostThraed(p->rchild);
		p->ltag = (p->lchild) ? 0:1;
		p->rtag = (p->rchild) ? 0:1;
		if(pre){
			if(pre->rtag == 1)
			pre->rchild = p;
			if(p->ltag ==1)
			p->lchild = pre;
		}
		pre = p;
	}
}
//寻找前驱
ThreadNode* PreNode(ThreadNode* p) {
	if (p->ltag == 1) return p->lchild;
	if (p->ltag == 0){
		if(p->lchild != NULL) return p->rchild;
		else return p->lchild;
	}
}
//寻找后继
ThreadNode* NextNode(ThreadNode* p) {
	if (p->ltag == 1) return p->lchild;
	if (p->ltag == 0){
		if(p->lchild != NULL) return p->rchild;
		else return p->lchild;
	}
}

int main() {
    ThreadTree T1;
    printf("Input:\n");
    CreateThreadTree(T1);
    printf("Create Successfully\n");
    InitThread(T1);
    CreatePreThread(T1);
    printf("PostOrder Result\n");
    PreOrder(T1);
	return 0;
}

