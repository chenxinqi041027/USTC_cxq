#include<bits/stdc++.h>
#define max 100
typedef struct Tack{
    int *data;
    int top;
}Tack;

typedef struct QueueNode
{
	int data;
	struct QueueNode *next;
}QueueNode,*Queuelink;

typedef struct Queue
{
	QueueNode *front;
	QueueNode *rear;
}Queue;

void InitTack(Tack *s)
{
    s->data=(int *)malloc(sizeof(max));
    s->top=-1;
}

void EnTack(Tack *s,int e)
{
    s->data[++s->top]=e;
}

void OutTack(Tack *s)
{
      if(s->top==-1) return;
       s->top--;
}

void EnQueue(Queue *q, int n)
{
	Queuelink p;
	int e,i=0;
	while(i++<n){
		scanf("%d",&e);
		p = (Queuelink)malloc(sizeof(QueueNode));
		p->data = e;
		p->next = NULL;
		q->rear->next = p;
		q->rear = p;
	}
	puts("Q");
}

void OutQueue(Queue *q)
{
	Queuelink p;
	if (q->front == q->rear) return;
	p = q->front->next;
	q->front->next = p->next;
	if (q->rear == p)
	{
		q->rear = q->front;
	}
	free(p);
}


int check(Queue *q,int n){
	Tack* s=(Tack*)malloc(sizeof(Tack));
	InitTack(s); 
    for(int i=1;i<=n;i++){
	    EnTack(s,i);
	    if(s->top!=-1&&s->data[s->top]==q->front->next->data) {
		   	OutTack(s);
		   	OutQueue(q);
   		}
	}
	while(s->top!=-1&&s->data[s->top]==q->front->next->data){
	   	OutTack(s);
	   	OutQueue(q);
		  }
	if(s->top==-1) return 1;
	return 0;
}

int main(){
	int n;
	Queue *o=(Queue*)malloc(sizeof(Queue));
	puts("1");
	o->front=(QueueNode *)malloc(sizeof(QueueNode));
	puts("2");
	o->rear=o->front;
	puts("3");
	o->front->next=NULL;
	puts("P");
	scanf("%d",&n);
	puts("PP");
	EnQueue(o,n);
	if(check(o,n)) printf("YES");
	else printf("NO"); 
	return 0;
}
