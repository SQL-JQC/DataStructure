//静态队列本质上是在使用数组实现，而数组长度有限，所以必须使用循环队列来实现和操作。 
# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

typedef struct Queue
{
	int * pBase;
	int front;
	int rear;
} QUEUE;

void init(QUEUE *, int);
bool enqueue(QUEUE *, int, int);
void traverse(QUEUE *, int);
bool dequeue(QUEUE *, int *, int);
bool empty(QUEUE *);
bool full(QUEUE *, int);

int main(void)
{
	QUEUE Q;
	int len = 6;  //初始化静态队列的长度是6，但队列满时，只允许有5个有效值，剩余一个不允许放有效数据。
	int dequeue_value;
	
	init(&Q, len);
	
	enqueue(&Q, 1, len);
	enqueue(&Q, 2, len);
	enqueue(&Q, 3, len);
	enqueue(&Q, 4, len);
	enqueue(&Q, 5, len);
	enqueue(&Q, 6, len);  //此时队列已满，该次入队无法完成，会返回false。
	traverse(&Q, len);
	
	if( dequeue(&Q, &dequeue_value, len) )
	{
		printf("出队成功，出去数组元素的值是：%d\n", dequeue_value);
	}
	else
	{
		printf("出队失败！\n");
	}
	traverse(&Q, len);
	
	return 0;
}

void init(QUEUE * pQ, int len)
{
	pQ->pBase = (int *)malloc(sizeof(int)*len);
	if(NULL == pQ->pBase)
	{
		printf("动态内存分配失败！\n");
		exit(-1);
	}
	else
	{
		pQ->front = 0;
		pQ->rear = 0;
	}
	
	return;
}

bool full(QUEUE * pQ, int len)
{
	if( (pQ->rear+1)%len == pQ->front )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool enqueue(QUEUE * pQ, int val, int len)
{
	if ( full(pQ, len) )
	{
		return false;
	}
	else
	{
		pQ->pBase[pQ->rear] = val;
		pQ->rear = (pQ->rear+1)%len;
		
		return true;
	}
}

bool empty(QUEUE * pQ)
{
	if( pQ->rear == pQ->front )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void traverse(QUEUE * pQ, int len)
{
	if( empty(pQ) )
	{
		printf("队列为空，无法遍历！\n");
		return;
	}
	else
	{
		int i = pQ->front;
		
		while(pQ->rear != i)
		{
			printf("%d ", pQ->pBase[i]);
			i = (i+1)%len;
		}
		printf("\n");
		
		return;
	}
}

bool dequeue(QUEUE * pQ, int * pVal, int len)
{
	if( empty(pQ) )
	{
		return false;
	}
	else
	{
		*pVal = pQ->pBase[pQ->front];
		pQ->front = (pQ->front+1)%len;
		
		return true;
	}
}
