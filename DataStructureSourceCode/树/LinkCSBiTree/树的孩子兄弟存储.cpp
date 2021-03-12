# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <string.h>
//# include "LinkCSBiTreeQueue.cpp"

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

typedef struct CSNode
{
	TElemType data;
	struct CSNode * firstchild;
	struct CSNode * nextsibling;
} CSNode, * CSTree;

void InitTree(CSTree &);
void DestroyTree(CSTree &);
void CreateTree(CSTree &);
bool TreeEmpty(CSTree);
int TreeDepth(CSTree);
TElemType Root(CSTree);
TElemType Value(CSTree);
bool Assign(CSTree &, TElemType, TElemType);
CSTree Point(CSTree, TElemType);
TElemType Parent(CSTree, TElemType);
TElemType LeftChild(CSTree, TElemType);
TElemType RightSibling(CSTree, TElemType);
bool InsertChild(CSTree &, CSTree, int, CSTree);
bool DeleteChild(CSTree &, CSTree, int);
void PreOrderTraverse(CSTree, void(*Visit)(TElemType));
void PostOrderTraverse(CSTree, void(*Visit)(TElemType));
void LevelOrderTraverse(CSTree, void(*Visit)(TElemType));

void visit(TElemType e)
{
	printf(format" ", e);
}

int main(void)
{
	CSTree T;
	int n;
	TElemType e;
	
	InitTree(T);
	CreateTree(T);
	
//	n = TreeDepth(T);
//	printf("%d\n", n);
	
//	LevelOrderTraverse(T, visit);
//	printf("\n");
//	Assign(T, 'A', 'Q');
//	LevelOrderTraverse(T, visit);

//	e = Parent(T, 'H');
//	printf("%c\n", e);
//	e = LeftChild(T, 'F');
//	printf("%c\n", e);
//	e = RightSibling(T, 'H');
//	printf("%c\n", e);

//	PreOrderTraverse(T, visit);
//	printf("\n");
//	PostOrderTraverse(T, visit);
//	printf("\n");
//	LevelOrderTraverse(T, visit);
//	printf("\n");
	
	DestroyTree(T);
	
	return 0;
}

void InitTree(CSTree & T)
{
	T = NULL;
}

void DestroyTree(CSTree & T)
{
	if(T)
	{
		if(T->firstchild)
		{
			DestroyTree(T->firstchild);
		}
		if(T->nextsibling)
		{
			DestroyTree(T->nextsibling);
		}
		free(T);
		T = NULL;
	}
}

# include "LinkCSBiTreeQueue.cpp"

void CreateTree(CSTree & T)
{
	CSTree p, p1;
	Queue q;
	char c[20];
	int i, l;
	
	initQueue(&q);
	
	printf("请输入根结点：");
	scanf("%c%*c", &c[0]);
	
	if(c[0] != Nil)
	{
		T = (CSTree)malloc(sizeof(CSNode));
		T->data = c[0];
		T->nextsibling = NULL;
		
		enqueue(&q, T);
		
		while(!emptyQueue(&q))
		{
			dequeue(&q, &p);
			
			printf("请按长幼顺序输入结点%c的所有孩子：", p->data);
			gets(c);
			
			l = strlen(c);
			if(l > 0)
			{
				p1 = p->firstchild = (CSTree)malloc(sizeof(CSNode));
				
				p1->data = c[0];
				for(i = 1; i < l; ++i)
				{
					p1->nextsibling = (CSTree)malloc(sizeof(CSNode));
					enqueue(&q, p1);
					p1 = p1->nextsibling;
					p1->data = c[i];
				}
				p1->nextsibling = NULL;
				enqueue(&q, p1);
			}
			else
			{
				p->firstchild = NULL;
			}
		}
	}
	else
	{
		T = NULL;
	}
	
	destroyQueue(&q);
}

bool TreeEmpty(CSTree T)
{
	if(T)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int TreeDepth(CSTree T)
{
	CSTree p;
	int depth;
	int max = 0;
	
	if(!T)
	{
		return 0;
	}
	if(!T->firstchild)
	{
		return 1;
	}
	for(p = T->firstchild; p; p = p->nextsibling)
	{
		depth = TreeDepth(p);
		if(depth > max)
		{
			max = depth;
		}
	}
	
	return max + 1;
}

TElemType Root(CSTree T)
{
	if(T)
	{
		return T->data;
	}
	else
	{
		return Nil;
	}
}

TElemType Value(CSTree T)
{
	return T->data;
}

bool Assign(CSTree & T, TElemType cur_e, TElemType value)
{
	CSTree p;
	
	if(T)
	{
		p = Point(T, cur_e);
		if(p)
		{
			p->data = value;
			
			return true;
		}
	}
	
	return false;
}

CSTree Point(CSTree T, TElemType e)
{
	Queue q;
	QElemType a;
	
	if(T)
	{
		initQueue(&q);
		enqueue(&q, T);
		
		while(!emptyQueue(&q))
		{
			dequeue(&q, &a);
			if(a->data == e)
			{
				destroyQueue(&q);
				return a;
			}
			
			if(a->firstchild)
			{
				enqueue(&q, a->firstchild);
			}
			if(a->nextsibling)
			{
				enqueue(&q, a->nextsibling);
			}
		}
	}
	
	destroyQueue(&q);
	
	return NULL;
}

TElemType Parent(CSTree T, TElemType cur_e)
{
	CSTree p, t;
	Queue q;
	
	initQueue(&q);
	
	if(T)
	{
		if(T->data == cur_e)
		{
			destroyQueue(&q);
			return Nil;
		}
		
		enqueue(&q, T);
		
		while(!emptyQueue(&q))
		{
			dequeue(&q, &p);
			if(p->firstchild)
			{
				if(p->firstchild->data == cur_e)
				{
					destroyQueue(&q);
					return p->data;
				}
				
				t = p;
				p = p->firstchild;
				enqueue(&q, p);
				
				while(p->nextsibling)
				{
					p = p->nextsibling;
					if(p->data == cur_e)
					{
						destroyQueue(&q);
						return t->data;
					}
					enqueue(&q, p);
				}
			}
		}
	}
	
	destroyQueue(&q);
	
	return Nil;
}

TElemType LeftChild(CSTree T, TElemType cur_e)
{
	CSTree p;
	
	if(T)
	{
		p = Point(T, cur_e);
		if(p && p->firstchild)
		{
			return p->firstchild->data;
		}
	}
	
	return Nil;
}

TElemType RightSibling(CSTree T, TElemType cur_e)
{
	CSTree p;
	
	if(T)
	{
		p = Point(T, cur_e);
		if(p && p->nextsibling)
		{
			return p->nextsibling->data;
		}
	}
	
	return Nil;
}

bool InsertChild(CSTree & T, CSTree p, int i, CSTree c)
{
	int j;
	
	if(T)
	{
		if(i == 1)
		{
			c->nextsibling = p->firstchild;
			p->firstchild = c;
		}
		else
		{
			p = p->firstchild;
			j = 2;
			
			while(p && j < i)
			{
				p = p->nextsibling;
				j++;
			}
			if(j == i)
			{
				c->nextsibling = p->nextsibling;
				p->nextsibling = c;
			}
			else
			{
				return false;
			}
		}
		
		return true;
	}
	
	return false;
}

bool DeleteChild(CSTree & T, CSTree p, int i)
{
	CSTree b;
	int j;
	
	if(T)
	{
		if(i == 1)
		{
			b = p->firstchild;
			p->firstchild = b->nextsibling;
			b->nextsibling = NULL;
			DestroyTree(b);
		}
		else
		{
			p = p->firstchild;
			j = 2;
			
			while(p && j < i)
			{
				p = p->nextsibling;
				j++;
			}
			if(j == i)
			{
				b = p->nextsibling;
				p->nextsibling = b->nextsibling;
				b->nextsibling = NULL;
				DestroyTree(b);
			}
			else
			{
				return false;
			}
		}
		
		return true;
	}
	
	return false;
}

void PreOrderTraverse(CSTree T, void(*Visit)(TElemType))
{
	if(T)
	{
		Visit(T->data);
		PreOrderTraverse(T->firstchild, Visit);
		PreOrderTraverse(T->nextsibling, Visit);
	}
}

void PostOrderTraverse(CSTree T, void(*Visit)(TElemType))
{
	CSTree p;
	
	if(T)
	{
		if(T->firstchild)
		{
			PostOrderTraverse(T->firstchild, Visit);
			
			p = T->firstchild->nextsibling;
			
			while(p)
			{
				PostOrderTraverse(p, Visit);
				p = p->nextsibling;
			}
		}
		Visit(T->data);
	}
}

void LevelOrderTraverse(CSTree T, void(*Visit)(TElemType))
{
	CSTree p;
	Queue q;
	
	initQueue(&q);
	
	if(T)
	{
		Visit(T->data);
		
		enqueue(&q, T);
		
		while(!emptyQueue(&q))
		{
			dequeue(&q, &p);
			if(p->firstchild)
			{
				p = p->firstchild;
				Visit(p->data);
				
				enqueue(&q, p);
				
				while(p->nextsibling)
				{
					p = p->nextsibling;
					Visit(p->data);
					enqueue(&q, p);
				}
			}
		}
	}
	
	destroyQueue(&q);
}

