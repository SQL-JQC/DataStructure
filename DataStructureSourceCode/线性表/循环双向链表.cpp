# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

typedef struct DuNode
{
	int data;
	struct DuNode * pPrior;
	struct DuNode * pNext;
} DUNODE, * PDUNODE;

PDUNODE create_DuList(void);
void traverse_DuList(PDUNODE);
bool insert_DuList(PDUNODE, int, int);
bool delete_DuList(PDUNODE, int, int *);
int length_DuList(PDUNODE);
void destroy_DuList(PDUNODE);

int main(void)
{
	PDUNODE pHead;
	int delete_value;
	
	pHead = create_DuList();
	
	traverse_DuList(pHead);
	
	insert_DuList(pHead, 3, 100);
	traverse_DuList(pHead);
	
	delete_DuList(pHead, 5, &delete_value);
	traverse_DuList(pHead);
	printf("删除链表中第5个结点的值是：%d\n", delete_value);
	
	destroy_DuList(pHead);
	
	return 0;
}

PDUNODE create_DuList(void)
{
	int i;
	int len;
	int val;
	PDUNODE pNew;
	
	PDUNODE pHead = (PDUNODE)malloc(sizeof(DUNODE));
	if(NULL == pHead)
	{
		printf("动态内存分配失败！\n");
		exit(-1);
	}
	PDUNODE pTail = pHead;
	pTail->pNext = pHead;
	pTail->pPrior = pHead;
	
	printf("请输入要生成的结点的个数：");
	scanf("%d", &len);
	
	for(i=0; i<len; ++i)
	{
		printf("请输入第%d个结点的值：", i+1);
		scanf("%d", &val);
		
		pNew = (PDUNODE)malloc(sizeof(DUNODE));
		if(NULL == pNew)
		{
			printf("动态内存分配失败！\n");
			exit(-1);
		}
		
		pNew->data = val;
		pNew->pNext = pHead;
		pNew->pPrior = pTail;
		pTail->pNext = pNew;
		pHead->pPrior = pNew;
		pTail = pNew;
	}
	
	return pHead;
}

void traverse_DuList(PDUNODE pHead)
{
	PDUNODE p = pHead->pNext;
	
	printf("\n");
	while(pHead != p)
	{
		printf("%d ", p->data);
		p = p->pNext; 
	}
	printf("\n");
	
	return;
}

int length_DuList(PDUNODE pHead)
{
	PDUNODE p = pHead->pNext;
	int len;
	
	while(pHead != p)
	{
		len++;
		p = p->pNext;
	}
	
	return len;
}

bool insert_DuList(PDUNODE pHead, int pos, int val)
{
	PDUNODE p = pHead;
	PDUNODE q;
	int len = length_DuList(pHead);
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
	q = p->pNext;
	
	PDUNODE pNew = (PDUNODE)malloc(sizeof(DUNODE));
	
	pNew->data = val;
	pNew->pNext = q;
	q->pPrior = pNew;
	pNew->pPrior = p;
	p->pNext = pNew;
	
	return true;
}

bool delete_DuList(PDUNODE pHead, int pos, int * pVal)
{
	PDUNODE p = pHead;
	PDUNODE q;
	int len = length_DuList(pHead);
	int i = 0;
	
	if(pos<1 || pos>len)
	{
		return false;
	}
	
	while(i < pos-1)
	{
		p = p->pNext;
		i++;
	}
	q = p->pNext->pNext;
	
	*pVal = p->pNext->data;
	free(p->pNext);
	p->pNext = q;
	q->pPrior = p;
	
	return true;
}

void destroy_DuList(PDUNODE pHead)
{
	PDUNODE p = pHead->pPrior;
	PDUNODE q;
	
	while(p != pHead)
	{
		q = pHead->pNext;
		free(pHead);
		pHead = q;
	}
	free(p);
	printf("链表释放成功！\n");
	
	return;
}
