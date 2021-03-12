# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node * pNext;
} NODE, * PNODE;

typedef struct Queue
{
	PNODE pFront;
	PNODE pRear;
} QUEUE, * PQUEUE;

void init(PQUEUE);
void enqueue(PQUEUE, int);
bool dequeue(PQUEUE, int *);
void traverse(PQUEUE);
bool empty(PQUEUE);
void clear(PQUEUE);
int length(PQUEUE);
bool get(PQUEUE, int *);
void destroy(PQUEUE);

int main(void)
{
	QUEUE Q;
	int dequeue_value;
	int get_value;
	
	init(&Q);
	
	enqueue(&Q, 1);
	enqueue(&Q, 2);
	enqueue(&Q, 3);
	enqueue(&Q, 4);
	traverse(&Q);
	
	if( dequeue(&Q, &dequeue_value) )
	{
		printf("出队成功，出去的结点的值是：%d\n", dequeue_value);
	}
	else
	{
		printf("出队失败！\n");
	}
	traverse(&Q);
	
	int len = length(&Q);
	printf("队列的长度是：%d\n", len);
	
	get(&Q, &get_value);
	printf("得到队列第一个结点的值是：%d\n", get_value);
	
	clear(&Q);
	traverse(&Q);
	
	destroy(&Q);
	
	return 0;
}

void init(PQUEUE pQ)
{
	pQ->pFront = (PNODE)malloc(sizeof(NODE));
	if(NULL == pQ->pFront)
	{
		printf("动态内存分配失败！\n");
		exit(-1);
	}
	else
	{
		pQ->pRear = pQ->pFront;
		pQ->pRear->pNext = NULL;
	}
	
	return;
}

void enqueue(PQUEUE pQ, int val)
{
	pQ->pRear->data = val;
	
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	pQ->pRear->pNext = pNew;
	pQ->pRear = pNew;
	pNew->pNext = NULL;
	
	return;
}

bool empty(PQUEUE pQ)
{
	if(pQ->pFront == pQ->pRear)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void traverse(PQUEUE pQ)
{
	if( empty(pQ) )
	{
		printf("队列为空，无法遍历！\n");
		return;
	}
	else
	{
		PNODE p = pQ->pFront;
		
		while(pQ->pRear != p)
		{
			printf("%d ", p->data);
			p = p->pNext;
		}
		printf("\n");
		
		return;
	}
}

bool dequeue(PQUEUE pQ, int * pVal)
{
	if( empty(pQ) )
	{
		return false;
	}
	else
	{
		PNODE p = pQ->pFront;
		*pVal = p->data;
		pQ->pFront = pQ->pFront->pNext;
		free(p);
		p = NULL;
		
		return true;
	}
}

void clear(PQUEUE pQ)
{
	if( empty(pQ) )
	{
		printf("队列为空，不需要清空了。\n");
		return;
	}
	else
	{
		PNODE p = pQ->pFront;
		PNODE q = NULL;
		
		while(pQ->pRear != p)
		{
			q = p->pNext;
			free(p);
			p = q;
		}
		pQ->pFront = pQ->pRear;
		
		return;
	}
}

int length(PQUEUE pQ)
{
	PNODE p = pQ->pFront;
	int len = 0;
	
	while(pQ->pRear != p)
	{
		len++;
		p = p->pNext;
	}
	
	return len;
}

bool get(PQUEUE pQ, int * pVal)
{
	if( empty(pQ) )
	{
		return false;
	}
	else
	{
		*pVal = pQ->pFront->data;
		
		return true;
	}
}

void destroy(PQUEUE pQ)
{
	PNODE p;
	
	while(NULL != pQ->pFront)
	{
		p = pQ->pFront->pNext;
		free(pQ->pFront);
		pQ->pFront = p;
	}
	printf("动态队列释放成功！\n");
	
	return;
}
