# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node * pNext;
} NODE, * PNODE;

typedef struct Stack
{
	PNODE pTop;
	PNODE pBottom;
} STACK, * PSTACK;

void init(PSTACK);
void push(PSTACK, int);
void traverse(PSTACK);
bool pop(PSTACK, int *);
bool empty(PSTACK);
void clear(PSTACK);
void destroy(PSTACK);
int length(PSTACK);
bool get(PSTACK, int *);

int main(void)
{
	STACK S;
	int pop_value;
	int get_value;
	
	init(&S);
	push(&S, 1);
	push(&S, 2);
	push(&S, 3);
	push(&S, 4);
	traverse(&S);
	
	int len = length(&S);
	printf("栈的长度是：%d\n", len);
	
	get(&S, &get_value);
	printf("得到栈顶结点的值是：%d\n", get_value);
	
	if( pop(&S, &pop_value) )
	{
		printf("出栈成功，弹出结点的值是：%d\n", pop_value);
	}
	else
	{
		printf("出栈失败！\n");
	}
	traverse(&S);
	
	clear(&S);
	traverse(&S);
	
	destroy(&S);
	
	return 0;
}

void init(PSTACK pS)
{
	pS->pTop = (PNODE)malloc(sizeof(NODE));
	if(NULL == pS->pTop)
	{
		printf("动态内存分配失败！\n");
		exit(-1);
	}
	else
	{
		pS->pBottom = pS->pTop;
		pS->pBottom->pNext = NULL;
	}
	
	return;
}

void push(PSTACK pS, int val)
{
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	
	pNew->data = val;
	pNew->pNext = pS->pTop;
	pS->pTop = pNew;
	
	return;
}

void traverse(PSTACK pS)
{
	if( empty(pS) )
	{
		printf("栈为空，无法遍历！\n");
		return;
	}
	else
	{
		PNODE q = pS->pTop;
		
		while(pS->pBottom != q)
		{
			printf("%d ", q->data);
			q = q->pNext;
		}
		printf("\n");
		
		return;
	}
}

bool empty(PSTACK pS)
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

bool pop(PSTACK pS, int * pVal)
{
	if( empty(pS) )
	{
		return false;
	}
	else
	{
		PNODE q = pS->pTop;
		*pVal = q->data;
		pS->pTop = pS->pTop->pNext;
		free(q);
		q = NULL;
		
		return true;
	}
}

void clear(PSTACK pS)
{
	if( empty(pS) )
	{
		return;
	}
	else
	{
		PNODE p = pS->pTop;
		PNODE q = NULL;
		
		while(pS->pBottom != p)
		{
			q = p->pNext;
			free(p);
			p = q;
		}
		pS->pTop = pS->pBottom;
	}
	
	return;
}

void destroy(PSTACK pS)
{
	PNODE p;
	
	while(NULL != pS->pTop)
	{
		p = pS->pTop->pNext;
		free(pS->pTop);
		pS->pTop = p;
	}
	printf("动态栈释放成功！\n");
	
	return;
}

int length(PSTACK pS)
{
	PNODE p = pS->pTop;
	int len = 0;
	
	while(pS->pBottom != p)
	{
		len++;
		p = p->pNext;
	}
	
	return len;
}

bool get(PSTACK pS, int * pVal)
{
	if( empty(pS) )
	{
		return false;
	}
	else
	{
		*pVal = pS->pTop->data;
		
		return true;
	}
}
