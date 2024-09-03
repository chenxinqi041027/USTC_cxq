#include<stdio.h>
#include<stdlib.h>
struct S{
int data;
struct S* next;
};
struct S* CreateListL(void){
	struct S *head,*p;
	int data;
	
	head = NULL;
	scanf("%d",&data);
	while(data!=0){
		p = (struct S*)malloc(sizeof(struct S));
		p->data = data;
		p->next = head;
		head =p;
		scanf("%d",&data);
	}
	return head;
}
struct S* CreateListR(void){
	struct S *head, *rear, *p;
	int data;
	
	head = NULL;
	scanf("%d",&data);
	while(data!=0){
		p=(struct S *)malloc(sizeof(struct S));
		p->next = NULL;
		p->data = data;
		if(!head) head = p;
		else rear->next = p;
		rear = p;
		scanf("%d",&data);
	}
	return head;
}
void PrintfList(struct S *head){
	struct S *p = head;
	while(p){
		printf("%d ",p->data);
		p = p->next ;
	}
	printf("\n");
}
struct S *Exchange(struct S *head){
	if(head==NULL||head->next ==NULL) return head; 
	struct S *p = head;
    while(p->next->next!=NULL ){
        p = p->next ;
    };
    int a;
    a= p->next->data ;
    p->next->data =p->data;
    p->data=a;
    return head;
}
int main(){
	int i;
	struct S* p;
	//头插法建立链表 
	printf("Head Insertion,Data = ");
	p = CreateListL();
	PrintfList(p);
	//尾插法建立链表
	printf("Tail Insertion,Data = ");
	p = CreateListR();
	PrintfList(p);
	//链表最后两个元素的互换
	p = Exchange(p);
	PrintfList(p);
	return 0; 
} 
