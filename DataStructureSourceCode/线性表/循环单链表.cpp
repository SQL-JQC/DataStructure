# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node * pNext;
} NODE, * PNODE;

PNODE create_list(void);
void traverse_list(PNODE);
bool insert_list(PNODE, int, int);
bool delete_list(PNODE *, int, int *);
void destroy_list(PNODE);
int length_list(PNODE);

int main(void)
{
	PNODE pTail;
	int delete_value;
	
	pTail = create_list();
	
	traverse_list(pTail);
	
	insert_list(pTail, 3, 100);
	traverse_list(pTail);
	
	delete_list(&pTail, 5, &delete_value);
	traverse_list(pTail);
	printf("删除链表的第5个结点的值是：%d\n", delete_value);
	
	destroy_list(pTail);
	
	return 0;
}

PNODE create_list(void)
{
	int i;
	int len;
	int val;
	
	PNODE pHead = (PNODE)malloc(sizeof(NODE));
	if(NULL == pHead)
	{
		printf("动态内存分配失败！\n");
		exit(-1);
	}
	PNODE pTail = pHead;
	pTail->pNext = pHead;
	
	printf("请输入要生成的结点的个数：");
	scanf("%d", &len);
	
	for(i=0; i<len; ++i)
	{
		printf("请输入第%d个结点的值：", i+1);
		scanf("%d", &val);
		
		PNODE pNew = (PNODE)malloc(sizeof(NODE));
		if(NULL == pNew)
		{
			printf("动态内存分配失败！\n");
			exit(-1);
		}
		
		pNew->data = val;
		pTail->pNext = pNew;
		pNew->pNext = pHead;
		pTail = pNew;
	}
	
	return pTail;
}

void traverse_list(PNODE pTail)
{
	PNODE p = pTail->pNext->pNext;
	
	printf("\n");
	while(pTail->pNext != p)
	{
		printf("%d ", p->data);
		p = p->pNext;
	}
	printf("\n");

	return;
}

int length_list(PNODE pTail)
{
	PNODE p = pTail->pNext->pNext;
	int len = 0;
	
	printf("\n");
	while(pTail->pNext != p)
	{
		len++;
		p = p->pNext;
	}
	printf("\n");
	
	return len;
}

bool insert_list(PNODE pTail, int pos, int val)
{
	PNODE p = pTail->pNext;
	int len = length_list(pTail);
	int i = 0;
	
	if(pos<1 || pos>len+1)
	{
		return false;
	}
	
	while(i < pos-1)
	{
		p = p->pNext;
		i++;
	}
	
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	pNew->data = val;
	pNew->pNext = p->pNext;
	p->pNext = pNew;
	
	if(pTail == p)
	{
		pTail = pNew;
	}
	
	return true;
}

bool delete_list(PNODE * pTail, int pos, int * pVal)
{
	PNODE p = (*pTail)->pNext;
	PNODE q;
	int len = length_list(*pTail);
	int i = 0;
	 
	if(0 == len)
	{
		return false;
	}
	if(pos<1 || pos>len)
	{
		return false;
	}
	
	while(i < pos-1)
	{
		p = p->pNext;
		i++;
	}
	
	q = p->pNext;
	*pVal = q->data;
	p->pNext = q->pNext;
	if(*pTail == q)
	{
		*pTail = p;
	}
	free(q);
	q = NULL;
	
	return true;
}

void destroy_list(PNODE pTail)
{
	PNODE p = pTail->pNext;
	PNODE q;
	
	while(pTail != p)
	{
		q = p->pNext;
		free(p);
		p = q;
	}
	free(pTail);
	pTail = NULL;
	
	return;
}
