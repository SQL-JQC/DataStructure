# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
//# include "LinkPBiTreeQueue.cpp"

# define INT  //ÕûÐÍ 
//# define CHAR  //×Ö·ûÐÍ 

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

typedef struct BiPTNode
{
	TElemType data;
	struct BiPTNode * parent;
	struct BiPTNode * lchild, * rchild;
} BiPTNode, * BiPTree;

void InitBiPTree(BiPTree &);
void CreateBiPTree(BiPTree &);
void DestroyBiPTree(BiPTree &);
bool BiPTreeEmpty(BiPTree);
int BiPTreeDepth(BiPTree);
TElemType Root(BiPTree);
TElemType Value(BiPTree);
void Assign(BiPTree, TElemType);
BiPTree Point(BiPTree, TElemType);
TElemType Parent(BiPTree, TElemType);
TElemType LeftChild(BiPTree, TElemType);
TElemType RightChild(BiPTree, TElemType);
TElemType LeftSibling(BiPTree, TElemType);
TElemType RightSibling(BiPTree, TElemType);
bool InsertChild(BiPTree, int, BiPTree);
bool DeleteChild(BiPTree, int);
void PreOrderTraverse(BiPTree, void(*Visit)(BiPTree));
void InOrderTraverse(BiPTree, void(*Visit)(BiPTree));
void PostOrderTraverse(BiPTree, void(*Visit)(BiPTree));
void LevelOrderTraverse(BiPTree, void(*Visit)(BiPTree));

void visit(BiPTree T)
{
	if(T)
	{
		printf(format" ", T->data);
	}
}

int main(void)
{
	BiPTree T;
	int n;
	TElemType e;
	
	InitBiPTree(T);
	CreateBiPTree(T);

//	n = BiPTreeDepth(T);
//	printf("%d\n", n);
	
//	e = Parent(T, 4);
//	printf("%d\n", e);
	
//	e = LeftChild(T, 2);
//	printf("%d\n", e);
//	e = RightChild(T, 2);
//	printf("%d\n", e);
//	e = LeftSibling(T, 4);
//	printf("%d\n", e);
//	e = RightSibling(T, 3);
//	printf("%d\n", e);
	
//	PreOrderTraverse(T, visit);
//	printf("\n");
//	InOrderTraverse(T, visit);
//	printf("\n");
//	PostOrderTraverse(T, visit);
//	printf("\n");
//	LevelOrderTraverse(T, visit);
//	printf("\n");
	
	DestroyBiPTree(T);
	
	return 0;
}

void InitBiPTree(BiPTree & T)
{
	T = NULL;
}

void CreateBiPTree(BiPTree & T)
{
	TElemType ch;
	
	scanf(format, &ch);
	
	if(ch == Nil)
	{
		T = NULL;
	}
	else
	{
		T = (BiPTree)malloc(sizeof(BiPTNode));
		if(T == NULL)
		{
			exit(-1);
		}
		
		T->data = ch;
		T->parent = NULL;
		
		CreateBiPTree(T->lchild);
		if(T->lchild)
		{
			T->lchild->parent = T;
		}
		
		CreateBiPTree(T->rchild);
		if(T->rchild)
		{
			T->rchild->parent = T;
		}
	}
}

void DestroyBiPTree(BiPTree & T)
{
	if(T)
	{
		if(T->lchild)
		{
			DestroyBiPTree(T->lchild);
		}
		if(T->rchild)
		{
			DestroyBiPTree(T->rchild);
		}
		free(T);
		T = NULL;
	}
}

bool BiPTreeEmpty(BiPTree T)
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

int BiPTreeDepth(BiPTree T)
{
	int i, j;
	
	if(!T)
	{
		return 0;
	}
	
	if(T->lchild)
	{
		i = BiPTreeDepth(T->lchild);
	}
	else
	{
		i = 0;
	}
	if(T->rchild)
	{
		j = BiPTreeDepth(T->rchild);
	}
	else
	{
		j = 0;
	}
	
	return i > j ? i + 1 : j + 1;
}

TElemType Root(BiPTree T)
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

TElemType Value(BiPTree T)
{
	return T->data;
}

void Assign(BiPTree T, TElemType value)
{
	T->data = value;
}

# include "LinkPBiTreeQueue.cpp"

BiPTree Point(BiPTree T, TElemType e)
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
			if(a->lchild)
			{
				enqueue(&q, a->lchild);
			}
			if(a->rchild)
			{
				enqueue(&q, a->rchild);
			}
		}
	}
	
	destroyQueue(&q);
	
	return NULL;
}

TElemType Parent(BiPTree T, TElemType e)
{
	BiPTree p;
	
	if(T)
	{
		p = Point(T, e);
		if(p && p != T)
		{
			return p->parent->data;
		}
	}
	
	return Nil;
}

TElemType LeftChild(BiPTree T, TElemType e)
{
	BiPTree p;
	
	if(T)
	{
		p = Point(T, e);
		if(p && p->lchild)
		{
			return p->lchild->data;
		}
	}
	
	return Nil;
}

TElemType RightChild(BiPTree T, TElemType e)
{
	BiPTree p;
	
	if(T)
	{
		p = Point(T, e);
		if(p && p->rchild)
		{
			return p->rchild->data;
		}
	}
	
	return Nil;
}

TElemType LeftSibling(BiPTree T, TElemType e)
{
	BiPTree p;
	
	if(T)
	{
		p = Point(T, e);
		if(p && p != T && p->parent->lchild && p->parent->lchild != p)
		{
			return p->parent->lchild->data;
		}
	}
	
	return Nil;
}

TElemType RightSibling(BiPTree T, TElemType e)
{
	BiPTree p;
	
	if(T)
	{
		p = Point(T, e);
		if(p && p != T && p->parent->rchild && p->parent->rchild != p)
		{
			return p->parent->rchild->data;
		}
	}
	
	return Nil;
}

bool InsertChild(BiPTree T, int LR, BiPTree c)
{
	if(T)
	{
		if(LR == 0)
		{
			c->rchild = T->lchild;
			if(c->rchild)
			{
				c->rchild->parent = c;
			}
			T->lchild = c;
			c->parent = T;
		}
		else
		{
			c->rchild = T->rchild;
			if(c->rchild)
			{
				c->rchild->parent = c;
			}
			T->rchild = c;
			c->parent = T;
		}
		
		return true;
	}
	
	return false;
}

bool DeleteChild(BiPTree T, int LR)
{
	if(T)
	{
		if(LR == 0)
		{
			DestroyBiPTree(T->lchild);
		}
		else
		{
			DestroyBiPTree(T->rchild);
		}
		
		return true;
	}
	
	return false;
}

void PreOrderTraverse(BiPTree T, void(*Visit)(BiPTree))
{
	if(T)
	{
		Visit(T);
		PreOrderTraverse(T->lchild, Visit);
		PreOrderTraverse(T->rchild, Visit);
	}
}

void InOrderTraverse(BiPTree T, void(*Visit)(BiPTree))
{
	if(T)
	{
		InOrderTraverse(T->lchild, Visit);
		Visit(T);
		InOrderTraverse(T->rchild, Visit);
	}
}

void PostOrderTraverse(BiPTree T, void(*Visit)(BiPTree))
{
	if(T)
	{
		PostOrderTraverse(T->lchild, Visit);
		PostOrderTraverse(T->rchild, Visit);
		Visit(T);
	}
}

void LevelOrderTraverse(BiPTree T, void(*Visit)(BiPTree))
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
			
			Visit(a);
			if(a->lchild)
			{
				enqueue(&q, a->lchild);
			}
			if(a->rchild)
			{
				enqueue(&q, a->rchild);
			}
		}
	}
	
	destroyQueue(&q);
}

