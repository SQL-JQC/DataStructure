# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

# define INITSIZE 5
# define INCREMENT 3

typedef struct Stack
{
	int * pBase;
	int top;
	int bottom;
	int length;
} STACK, * PSTACK;

void init(PSTACK);
bool push(PSTACK, int);
void traverse(PSTACK);
bool full(PSTACK);
bool empty(PSTACK);
bool pop(PSTACK, int *);
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
	push(&S, 5);
	push(&S, 6);
	traverse(&S);
	
	pop(&S, &pop_value);
	traverse(&S);
	printf("出栈成功，弹出的数组元素的值是：%d\n", pop_value);
	
	int len = length(&S);
	printf("栈的长度是：%d\n", len);
	
	get(&S, &get_value);
	printf("得到栈顶元素的值是：%d\n", get_value);
	
	clear(&S);
	traverse(&S);
	
	destroy(&S);
	
	return 0;	
}

void init(PSTACK pS)
{
	pS->pBase = (int *)malloc(sizeof(int)*INITSIZE);
	if(NULL == pS->pBase)
	{
		printf("动态内存分配失败！\n");
		exit(-1); 
	}
	
	pS->bottom = 0;
	pS->top = 0;
	pS->length = INITSIZE;
	
	return;
}

void traverse(PSTACK pS)
{
	int i = pS->top;
	
	printf("\n");
	while(pS->bottom != i)
	{
		printf("%d ", pS->pBase[i-1]);
		i--;
	}
	printf("\n");
	
	return;
}

bool empty(PSTACK pS)
{
	if(pS->top == pS->bottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool full(PSTACK pS)
{
	if(pS->top - pS->bottom == pS->length)
	{
		int * pNewBase = (int *)realloc(pS->pBase, sizeof(int)*(pS->length + INCREMENT));
		if(NULL == pNewBase)
		{
			printf("重新动态内存分配失败！\n");
			exit(-1);
		}
		
		pS->pBase = pNewBase;
		pS->length += INCREMENT;
		
		return false;
	}
	else
	{
		return false;
	}
}

bool push(PSTACK pS, int val)
{
	if( full(pS) )
	{
		return false;
	}
	else
	{
		pS->pBase[pS->top] = val;
		pS->top++;
		
		return true;
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
		pS->top--;
		*pVal = pS->pBase[pS->top];
		
		return true;
	}
}

int length(PSTACK pS)
{
	int i = pS->top;
	int len = 0;
	
	while(pS->bottom != i)
	{
		len++;
		i--;
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
		int i = pS->top;
		
		*pVal = pS->pBase[i-1];
		
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
		pS->top = pS->bottom;
		
		return;
	}
}

void destroy(PSTACK pS)
{
	free(pS->pBase);
	printf("静态栈释放成功！\n");
	
	return;
}
