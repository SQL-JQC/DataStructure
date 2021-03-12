# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <string.h>
//# include "SqPCTreeQueue.cpp"

//# define INT  //整型 
# define CHAR  //字符型 

#ifdef CHAR
	typedef char TElemType;
	TElemType Nil = ' ';
	# define format "%c"
#endif
#ifdef INT
	typedef int TElemType;
	TElemType Nil = 0;
	# define format "%d"
#endif

# define MAX_TREE_SIZE 100

typedef struct CTNode
{
	int child;
	struct CTNode * next;
} CTNode, * ChildPtr;

typedef struct PTNode
{
	TElemType data;
	int parent;
	ChildPtr firstchild;
} PCTBox;

typedef struct SqPCTree
{
	PCTBox nodes[MAX_TREE_SIZE];
	int r;
	int n;
} SqPCTree, * PCTree;

void InitTree(PCTree &);
void CreateTree(PCTree &);
void DestroyTree(PCTree &);
void showTree(PCTree);

int main(void)
{
	PCTree T;
	
	InitTree(T);
	CreateTree(T);
	
//	showTree(T);
	
	DestroyTree(T);
	
	return 0;
}

void InitTree(PCTree & T)
{
	T = (PCTree)malloc(sizeof(SqPCTree));
	if(T == NULL)
	{
		exit(-1);
	}
	T->r = 0;
	T->n = 0;
	
	int i;
	for(i = 0; i < MAX_TREE_SIZE; ++i)
	{
		T->nodes[i].firstchild = (ChildPtr)malloc(sizeof(CTNode));
		T->nodes[i].firstchild->next = NULL;
	}
}

# include "SqPCTreeQueue.cpp"

void CreateTree(PCTree & T)
{
	Queue q;
	QElemType p, qq;
	int i = 1;
	int k = 0;
	int j, l;
	char c[MAX_TREE_SIZE];
	
	initQueue(&q);
	
	printf("请输入根结点：");
	scanf("%c%*c", &T->nodes[0].data);
	if(T->nodes[0].data != Nil)
	{
		T->nodes[0].parent = -1;
		
		qq.name = T->nodes[0].data;
		qq.num = 0;
		
		enqueue(&q, qq);
		
		while(i < MAX_TREE_SIZE && !emptyQueue(&q))
		{
			dequeue(&q, &qq);
			
			printf("请按长幼顺序输入结点%c的所有孩子：", qq.name);
			gets(c);
			
			l = strlen(c);
			ChildPtr pTail = T->nodes[k].firstchild;
			for(j = 0; j < l; ++j)
			{
				T->nodes[i].data = c[j];
				T->nodes[i].parent = qq.num;
				
				p.name = c[j];
				p.num = i;
				
				enqueue(&q, p);
				i++;
				
				ChildPtr pNew = (ChildPtr)malloc(sizeof(CTNode));
				pNew->child = i - 1;
				pNew->next = NULL;
				pTail->next = pNew;
				pTail = pNew;
			}
			k++;
		}
		
		T->n = i;
	}
	else
	{
		T->n = 0;
	}
	
	destroyQueue(&q);	
}

void DestroyTree(PCTree & T)
{
	int i;
	ChildPtr p, q;
	
	if(T->n != 0)
	{
		for(i = 0; i < T->n; ++i)
		{
			p = T->nodes[i].firstchild;
			while(p != NULL)
			{
				q = p->next;
				free(p);
				p = q;
			}
		}
		free(T);
		T = NULL;
	}
}

void showTree(PCTree T)
{
	int i;
	ChildPtr p;
	
	if(T->n != 0)
	{
		for(i = 0; i < T->n; ++i)
		{
			printf(format" ", T->nodes[i].data);
			printf("%d ", T->nodes[i].parent);
			p = T->nodes[i].firstchild->next;
			while(p != NULL)
			{
				printf("%d ", p->child);
				p = p->next;
			}
			printf("\n");
		}
	}
	printf("\n");
}

