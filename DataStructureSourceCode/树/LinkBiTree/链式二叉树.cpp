# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
//# include "LinkBiTreeQueue.cpp"
//# include "LinkBiTreeStack.cpp"

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

typedef struct BiTNode
{
	TElemType data;
	struct BiTNode * lchild;
	struct BiTNode * rchild;
} BiTNode, * BiTree;

void InitBiTree(BiTree &);
void CreateBiTree(BiTree &);
void DestroyBiTree(BiTree &);
bool BiTreeEmpty(BiTree);
int BiTreeDepth(BiTree);
TElemType Root(BiTree);
TElemType Value(BiTree);
void Assign(BiTree, TElemType);
TElemType Parent(BiTree, TElemType);
BiTree Point(BiTree, TElemType);
TElemType LeftChild(BiTree, TElemType);
TElemType RightChild(BiTree, TElemType);
TElemType LeftSibling(BiTree, TElemType);
TElemType RightSibling(BiTree, TElemType);
bool InsertChild(BiTree, int, BiTree);
bool DeleteChild(BiTree, int);
void InOrderTraverse1(BiTree, void(*Visit)(TElemType));
void InOrderTraverse2(BiTree, void(*Visit)(TElemType));
void LevelOrderTraverse(BiTree, void(*Visit)(TElemType));
void PreOrderTraverse(BiTree, void(*Visit)(TElemType));
void InOrderTraverse(BiTree, void(*Visit)(TElemType));
void PostOrderTraverse(BiTree, void(*Visit)(TElemType));

void visit(TElemType e)
{
	printf(format" ", e);
}

int main(void)
{
	BiTree T;
	int n;
	TElemType e;
	
	InitBiTree(T);
	CreateBiTree(T);
	
//	PreOrderTraverse(T, visit);
//	printf("\n");
//	InOrderTraverse(T, visit);
//	printf("\n");
//	PostOrderTraverse(T, visit);
//	printf("\n");
	
//	n = BiTreeDepth(T);
//	printf("%d\n", n);
	
//	e = Root(T);
//	printf("%d\n", e);

//	e = Parent(T, 4);
//	printf("%d\n", e);

//	e = LeftChild(T, 2);
//	printf("%d\n", e);
//	e = RightChild(T, 2);
//	printf("%d\n", e);
//	e = LeftSibling(T, 5);
//	printf("%d\n", e);
//	e = RightSibling(T, 3);
//	printf("%d\n", e);

//	InOrderTraverse1(T, visit);
//	InOrderTraverse2(T, visit);

//	LevelOrderTraverse(T, visit);
	
	DestroyBiTree(T);
	
	return 0;
}

void InitBiTree(BiTree & T)
{
	T = NULL;
}

void CreateBiTree(BiTree & T)
{
	TElemType ch;
	
	scanf(format, &ch);
	
	if(ch == Nil)
	{
		T = NULL;
	}
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));
		if(T == NULL)
		{
			exit(-1);
		}
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}

void DestroyBiTree(BiTree & T)
{
	if(T)
	{
		if(T->lchild)
		{
			DestroyBiTree(T->lchild);
		}
		if(T->rchild)
		{
			DestroyBiTree(T->rchild);
		}
		free(T);
		T = NULL;
	}
}

bool BiTreeEmpty(BiTree T)
{
	if(T == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int BiTreeDepth(BiTree T)
{
	int i;
	int j;
	
	if(!T)
	{
		return 0;
	}
	
	if(T->lchild)
	{
		i = BiTreeDepth(T->lchild);
	}
	else
	{
		i = 0;
	}
	
	if(T->rchild)
	{
		j = BiTreeDepth(T->rchild);
	}
	else
	{
		j = 0;
	}
	
	return i > j ? i + 1 : j + 1;
}

TElemType Root(BiTree T)
{
	if(BiTreeEmpty(T))
	{
		return Nil;
	}
	else
	{
		return T->data;
	}
}

TElemType Value(BiTree T)
{
	return T->data;
}

void Assign(BiTree T, TElemType value)
{
	T->data = value;
}

# include "LinkBiTreeQueue.cpp"

TElemType Parent(BiTree T, TElemType e)
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
			if(a->lchild && a->lchild->data == e || a->rchild && a->rchild->data == e)
			{
				destroyQueue(&q);
				return a->data;
			}
			else
			{
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
	}
	
	destroyQueue(&q);
	
	return Nil;
}

BiTree Point(BiTree T, TElemType e)
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

TElemType LeftChild(BiTree T, TElemType e)
{
	BiTree a;
	
	if(T)
	{
		a = Point(T, e);
		if(a && a->lchild)
		{
			return a->lchild->data;
		}
	}
	
	return Nil;
}

TElemType RightChild(BiTree T, TElemType e)
{
	BiTree a;
	
	if(T)
	{
		a = Point(T, e);
		if(a && a->rchild)
		{
			return a->rchild->data;
		}
	}
	
	return Nil;
}

TElemType LeftSibling(BiTree T, TElemType e)
{
	TElemType value;
	BiTree a;
	
	if(T)
	{
		value = Parent(T, e);
		if(value != Nil)
		{
			a = Point(T, value);
			if(a->lchild && a->rchild && a->rchild->data == e)
			{
				return a->lchild->data;
			}
		}
	}
	
	return Nil;
}

TElemType RightSibling(BiTree T, TElemType e)
{
	TElemType value;
	BiTree a;
	
	if(T)
	{
		value = Parent(T, e);
		if(value != Nil)
		{
			a = Point(T, value);
			if(a->rchild && a->lchild && a->lchild->data == e)
			{
				return a->rchild->data;
			}
		}
	}
	
	return Nil;
}

bool InsertChild(BiTree T, int LR, BiTree c)
{
	if(T)
	{
		if(LR == 0)
		{
			c->rchild = T->lchild;
			T->lchild = c;
		}
		else
		{
			c->rchild = T->rchild;
			T->rchild = c;
		}
		
		return true;
	}
	
	return false;
}

bool DeleteChild(BiTree T, int LR)
{
	if(T)
	{
		if(LR == 0)
		{
			DestroyBiTree(T->lchild);
		}
		else
		{
			DestroyBiTree(T->rchild);
		}
		
		return true;
	}
	
	return false;
}

# include "LinkBiTreeStack.cpp"

void InOrderTraverse1(BiTree T, void(*Visit)(TElemType))
{
	Stack s;
	
	initStack(&s);
	
	while(T || !emptyStack(&s))
	{
		if(T)
		{
			push(&s, T);
			T = T->lchild;
		}
		else
		{
			pop(&s, &T);
			Visit(T->data);
			T = T->rchild;
		}
	}
	
	destroyStack(&s);
	
	printf("\n");
}

void InOrderTraverse2(BiTree T, void(*Visit)(TElemType))
{
	Stack s;
	BiTree a;
	
	initStack(&s);
	push(&s, T);
	
	while(!emptyStack(&s))
	{
		while(get(&s, &a) && a)
		{
			push(&s, a->lchild);
		}
		
		pop(&s, &a);
		
		if(!emptyStack(&s))
		{
			pop(&s, &a);
			Visit(a->data);
			push(&s, a->rchild);
		}
	}
	
	destroyStack(&s);
	
	printf("\n");
}

void LevelOrderTraverse(BiTree T, void(*Visit)(TElemType))
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
			Visit(a->data);
			
			if(a->lchild)
			{
				enqueue(&q, a->lchild);
			}
			if(a->rchild)
			{
				enqueue(&q, a->rchild);
			}
		}
		printf("\n");
	}
	
	destroyQueue(&q);
}

void PreOrderTraverse(BiTree T, void(*Visit)(TElemType))
{
	if(T)
	{
		Visit(T->data);
		PreOrderTraverse(T->lchild, Visit);
		PreOrderTraverse(T->rchild, Visit);
	}
}

void InOrderTraverse(BiTree T, void(*Visit)(TElemType))
{
	if(T)
	{
		InOrderTraverse(T->lchild, Visit);
		Visit(T->data);
		InOrderTraverse(T->rchild, Visit);
	}
}

void PostOrderTraverse(BiTree T, void(*Visit)(TElemType))
{
	if(T)
	{
		PostOrderTraverse(T->lchild, Visit);
		PostOrderTraverse(T->rchild, Visit);
		Visit(T->data);
	}
}

