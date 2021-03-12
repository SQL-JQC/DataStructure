# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

typedef struct SElemType
{
	char ch;
	DLTree p;
} SElemType;

typedef struct SNode
{
	SElemType data;
	struct SNode * pNext;
} SNode, * PSNode;

typedef struct Stack
{
	PSNode pTop;
	PSNode pBottom;
} Stack, * PStack;

void initStack(PStack);
void push(PStack, SElemType);
bool pop(PStack, SElemType *);
bool emptyStack(PStack);
void destroyStack(PStack);
bool get(PStack, SElemType *);

void initStack(PStack pS)
{
	pS->pTop = (PSNode)malloc(sizeof(SNode));
	if(NULL == pS->pTop)
	{
		printf("¶¯Ì¬ÄÚ´æ·ÖÅäÊ§°Ü£¡\n");
		exit(-1);
	}
	else
	{
		pS->pBottom = pS->pTop;
		pS->pBottom->pNext = NULL;
	}
	
	return;
}

void push(PStack pS, SElemType val)
{
	PSNode pNew = (PSNode)malloc(sizeof(SNode));
	
	pNew->data = val;
	pNew->pNext = pS->pTop;
	pS->pTop = pNew;
	
	return;
}

bool emptyStack(PStack pS)
{
	if(pS->pTop == pS->pBottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool pop(PStack pS, SElemType * pVal)
{
	if( emptyStack(pS) )
	{
		return false;
	}
	else
	{
		PSNode q = pS->pTop;
		*pVal = q->data;
		pS->pTop = pS->pTop->pNext;
		free(q);
		q = NULL;
		
		return true;
	}
}

void destroyStack(PStack pS)
{
	PSNode p;
	
	while(NULL != pS->pTop)
	{
		p = pS->pTop->pNext;
		free(pS->pTop);
		pS->pTop = p;
	}
	
	return;
}

bool get(PStack pS, SElemType * pVal)
{
	if( emptyStack(pS) )
	{
		return false;
	}
	else
	{
		*pVal = pS->pTop->data;
		
		return true;
	}
}
