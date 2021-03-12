# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

typedef BiPTree QElemType;

typedef struct QNode
{
	QElemType data;
	struct QNode * pNext;
} QNode, * PQNode;

typedef struct Queue
{
	PQNode pFront;
	PQNode pRear;
} Queue, * PQueue;

void initQueue(PQueue);
void enqueue(PQueue, QElemType);
bool dequeue(PQueue, QElemType *);
bool emptyQueue(PQueue);
void destroyQueue(PQueue);

void initQueue(PQueue pQ)
{
	pQ->pFront = (PQNode)malloc(sizeof(QNode));
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
	
	PQNode pNew = (PQNode)malloc(sizeof(QNode));
	pQ->pRear->pNext = pNew;
	pQ->pRear = pNew;
	pNew->pNext = NULL;
	
	return;
}

bool dequeue(PQueue pQ, QElemType * pVal)
{
	if( emptyQueue(pQ) )
	{
		return false;
	}
	else
	{
		PQNode p = pQ->pFront;
		*pVal = p->data;
		pQ->pFront = pQ->pFront->pNext;
		free(p);
		p = NULL;
		
		return true;
	}
}

bool emptyQueue(PQueue pQ)
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

void destroyQueue(PQueue pQ)
{
	PQNode p;
	
	while(NULL != pQ->pFront)
	{
		p = pQ->pFront->pNext;
		free(pQ->pFront);
		pQ->pFront = p;
	}
	
	return;
}
