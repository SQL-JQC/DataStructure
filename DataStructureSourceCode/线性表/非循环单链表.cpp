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
bool is_empty(PNODE);
int length_list(PNODE);
bool insert_list(PNODE, int, int);
bool delete_list(PNODE, int, int *);
void sort_list(PNODE, int);
bool get_list(PNODE, int, int *);
void delete_max(PNODE, int *);
void destroy_list(PNODE);

int main(void)
{
	PNODE pHead;
	int delete_value;
	int get_value;
	int delete_max_value;
	
	pHead = create_list();
	traverse_list(pHead);
	
	if( is_empty(pHead) )
		printf("链表为空！");
	else
		printf("链表不为空！");
		
	int len = length_list(pHead);
	printf("链表的长度为：%d\n", len);
	
	printf("\n对链表进行冒泡排序(升序)之后的结果是：\n");
	sort_list(pHead, len);
	traverse_list(pHead);
	
	printf("\n向链表中插入一个值后的结果是：\n");
	insert_list(pHead, 4, 100);
	traverse_list(pHead);
	
	printf("\n删除链表中一个结点后的结果是：\n");
	delete_list(pHead, 5, &delete_value);
	traverse_list(pHead);
	printf("删除的值为：%d\n", delete_value);
	
	get_list(pHead, 3, &get_value);
	printf("得到非循环单链表中第3个结点的值是：%d\n", get_value);
	
	delete_max(pHead, &delete_max_value);
	printf("删除单链表中的最大值是：%d\n", delete_max_value);
	traverse_list(pHead);
	
	destroy_list(pHead);  //释放整个链表 
	
	return 0;
}

PNODE create_list(void)
{
	int len;
	int i;
	int val;
	
	PNODE pHead = (PNODE)malloc(sizeof(NODE));
	if(NULL == pHead)
	{
		printf("系统分配失败！");
		exit(-1);
	}
	PNODE pTail = pHead;
	pTail->pNext = NULL;
	
	printf("请输入所要生成的结点个数：");
	scanf("%d", &len);
	
	for(i=0; i<len; ++i)
	{
		printf("请输入要存放在第%d个节点的值：", i+1);
		scanf("%d", &val);
		
		PNODE pNew = (PNODE)malloc(sizeof(NODE));
		if(NULL == pNew)
		{
			printf("系统分配失败！");
			exit(-1);
		}
		
		pNew->data = val;
		pTail->pNext = pNew;
		pNew->pNext = NULL;
		pTail = pNew;
	}
	
	return pHead;
}

void traverse_list(PNODE pHead)
{
	PNODE p = pHead->pNext;
	
	printf("\n");
	while(NULL != p)
	{
		printf("%d ", p->data);
		p = p->pNext;
	}
	printf("\n");
	
	return;
}

bool is_empty(PNODE pHead)
{
	printf("\n");
	if(NULL == pHead->pNext)
		return true;
	else
		return false;
}

int length_list(PNODE pHead)
{
	PNODE p = pHead->pNext;
	int cnt = 0;
	
	printf("\n");
	while(NULL != p)
	{
		++cnt;
		p = p->pNext;
	}
	printf("\n");
	
	return cnt;
}

void sort_list(PNODE pHead, int len)
{
	PNODE p, q;
	int i, j;
	int t;
	
	for(i=0; i<len-1; ++i)
	{
		p = pHead->pNext;
		q = pHead->pNext->pNext;
		
		for(j=0; j<len-1-i; ++j)
		{
			if(p->data > q->data)
			{
				t = p->data;
				p->data = q->data;
				q->data = t;
			}
			p = p->pNext;
			q = q->pNext;
		}
	}
	
	return;
}

bool insert_list(PNODE pHead, int pos, int val)
{
	int i = 0;
	PNODE p = pHead;
	
	//以下的while循环和if判断 为一个重要算法 
	while(NULL!=p && i<pos-1)
	{
		p = p->pNext;  //p在一会儿链表插入操作时很有帮助 
		i++;
	}
	if(i>pos-1 || NULL==p)
	{
		return false;
	}
	//该算法不仅能使得链表插入前判断无误，(如果有误则会返回false)，还能够方便后续真正插入操作的进行 
	
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	if(NULL == pNew)
	{
		printf("动态内存分配失败！");
		exit(-1);
	}
	
	pNew->data = val;
	//插入操作，两行代码。 
	pNew->pNext = p->pNext;
	p->pNext = pNew;
	
	return true;
}

bool delete_list(PNODE pHead, int pos, int * pVal)
{
	int i = 0;
	PNODE p = pHead;
	
	//还是这个重要算法 while循环+if判断
	while(NULL!=p->pNext && i<pos-1)
	{
		p = p->pNext;  //p在一会儿链表删除操作时很有帮助 
		i++;
	}
	if(i>pos-1 || NULL==p->pNext)
	{
		return false;
	}
	
	PNODE q = p->pNext;
	*pVal = p->pNext->data;  //等价于 *pVal = q->data; 
	p->pNext = p->pNext->pNext;  //等价于 p->pNext = q->pNext; 
	free(q);
	q = NULL;
	
	return true;
}

bool get_list(PNODE pHead, int pos, int * pVal)
{
	int i = 1;
	PNODE p = pHead->pNext;
	
	while(NULL!=p && i<pos)
	{
		p = p->pNext;
		i++;
	}
	if(i>pos || NULL==p)
	{
		return false;
	}
	
	*pVal = p->data;
	
	return true;
}

void delete_max(PNODE pHead, int * pVal)
{
	PNODE p = pHead->pNext;
	PNODE max = p;
	PNODE pre = pHead;
	PNODE maxpre = pre;
	
	while(NULL != p)
	{
		if(max->data < p->data)
		{
			max = p;
			maxpre = pre;
		}
		pre = p;
		p = p->pNext; 
	}
	
	*pVal = max->data;
	maxpre->pNext = max->pNext;
	free(max);
	
	return;
}

void destroy_list(PNODE pHead)
{
	if(NULL == pHead)
	{
		printf("链表不存在，无需释放。\n"); 
		return;
	}
	else
	{
		PNODE p;
		while(NULL != pHead)
		{
			p = pHead->pNext;
			free(pHead);
			pHead = p;
		}
		printf("链表释放成功！\n");
		
		return;
	}
}
