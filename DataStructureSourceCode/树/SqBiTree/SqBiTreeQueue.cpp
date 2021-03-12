# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

typedef int QElemType;

typedef struct Node
{
	QElemType data;
	struct Node * pNext;
} Node, * PNode;

typedef struct Queue
{
	PNode pFront;
	PNode pRear;
} Queue, * PQueue;

void init(PQueue);
void enqueue(PQueue, QElemType);
bool dequeue(PQueue, QElemType *);
bool empty(PQueue);
void destroy(PQueue);

void init(PQueue pQ)
{
	pQ->pFront = (PNode)malloc(sizeof(Node));
	if(NULL == pQ->pFront)
	{
		printf("¶¯Ì¬ÄÚ´æ·ÖÅäÊ§°Ü£¡\n");
		exit(-1);
	}
	else
	{
		pQ->pRear = pQ->pFront;
		pQ->pRear->pNext = NULL;
	}
	
	return;
}

void enqueue(PQueue pQ, QElemType val)
{
	pQ->pRear->data = val;
	
	PNode pNew = (PNode)malloc(sizeof(Node));
	pQ->pRear->pNext = pNew;
	pQ->pRear = pNew;
	pNew->pNext = NULL;
	
	return;
}

bool dequeue(PQueue pQ, QElemType * pVal)
{
	if( empty(pQ) )
	{
		return false;
	}
	else
	{
		PNode p = pQ->pFront;
		*pVal = p->data;
		pQ->pFront = pQ->pFront->pNext;
		free(p);
		p = NULL;
		
		return true;
	}
}

bool empty(PQueue pQ)
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

void destroy(PQueue pQ)
{
	PNode p;
	
	while(NULL != pQ->pFront)
	{
		p = pQ->pFront->pNext;
		free(pQ->pFront);
		pQ->pFront = p;
	}
	
	return;
}
