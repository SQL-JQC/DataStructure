# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
//# include "LinkThreadBiTreeQueue.cpp"

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

typedef enum PointerTag
{
	Link, Thread
} PointerTag;

typedef struct BiThrNode
{
	TElemType data;
	struct BiThrNode * lchild;
	struct BiThrNode * rchild;
	PointerTag LTag, RTag;
} BiThrNode, * BiThrTree;

void InitBiThrTree(BiThrTree &);
void CreateBiThrTree(BiThrTree &);
void DestroyBiTree(BiThrTree &);
void DestroyBiThrTree(BiThrTree &);
BiThrTree Parent(BiThrTree, BiThrTree);
void PreThreading(BiThrTree);
void PreOrderThreading(BiThrTree &, BiThrTree);
void PreOrderTraverse_Thr(BiThrTree, void(*Visit)(TElemType));
void InThreading(BiThrTree);
void InOrderThreading(BiThrTree &, BiThrTree);
void InOrderTraverse_Thr(BiThrTree, void(*Visit)(TElemType));
void PostThreading(BiThrTree);
void PostOrderThreading(BiThrTree &, BiThrTree);
void PostOrderTraverse_Thr(BiThrTree, void(*Visit)(TElemType));

void visit(TElemType e)
{
	printf(format" ", e);
}

int main(void)
{
	BiThrTree T;
	BiThrTree Thrt;
	
//	InitBiThrTree(T);
//	CreateBiThrTree(T);
//	PreOrderThreading(Thrt, T);
//	PreOrderTraverse_Thr(Thrt, visit);
//	DestroyBiThrTree(Thrt);
	
//	InitBiThrTree(T);
//	CreateBiThrTree(T);
//	InOrderThreading(Thrt, T);
//	InOrderTraverse_Thr(Thrt, visit);
//	DestroyBiThrTree(Thrt);

//	InitBiThrTree(T);
//	CreateBiThrTree(T);
//	PostOrderThreading(Thrt, T);
//	PostOrderTraverse_Thr(Thrt, visit);
//	DestroyBiThrTree(Thrt);
	
	return 0;
}

void InitBiThrTree(BiThrTree & T)
{
	T = NULL;
}

void CreateBiThrTree(BiThrTree & T)
{
	TElemType ch;
	
	scanf(format, &ch);
	
	if(ch == Nil)
	{
		T = NULL;
	}
	else
	{
		T = (BiThrTree)malloc(sizeof(BiThrNode));
		if(T == NULL)
		{
			exit(-1);
		}
		
		T->data = ch;
		CreateBiThrTree(T->lchild);
		if(T->lchild)
		{
			T->LTag = Link;
		}
		CreateBiThrTree(T->rchild);
		if(T->rchild)
		{
			T->RTag = Link;
		}
	}
}

void DestroyBiTree(BiThrTree & T)
{
	if(T)
	{
		if(T->LTag == Link)
		{
			DestroyBiTree(T->lchild);
		}
		if(T->RTag == Link)
		{
			DestroyBiTree(T->rchild);
		}
		free(T);
		T = NULL;
	}
}

void DestroyBiThrTree(BiThrTree & Thrt)
{
	if(Thrt)
	{
		if(Thrt->lchild)
		{
			DestroyBiTree(Thrt->lchild);
		}
		free(Thrt);
		Thrt = NULL;
	}
}

BiThrTree pre;

void PreThreading(BiThrTree p)
{
	if(!pre->rchild)
	{
		pre->rchild = p;
		pre->RTag = Thread;
	}
	if(!p->lchild)
	{
		p->lchild = pre;
		p->LTag = Thread;
	}
	pre = p;
	if(p->LTag == Link)
	{
		PreThreading(p->lchild);
	}
	if(p->RTag == Link)
	{
		PreThreading(p->rchild);
	}
}

void PreOrderThreading(BiThrTree & Thrt, BiThrTree T)
{
	Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
	if(Thrt == NULL)
	{
		exit(-1);
	}
	
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	
	if(!T)
	{
		Thrt->lchild = Thrt;
	}
	else
	{
		Thrt->lchild = T;
		pre = Thrt;
		PreThreading(T);
		pre->rchild = Thrt;
		pre->RTag = Thread;
		Thrt->rchild = pre;
	}
}

void PreOrderTraverse_Thr(BiThrTree Thrt, void(*Visit)(TElemType))
{
	BiThrTree T = Thrt->lchild;
	while(T != Thrt)
	{
		Visit(T->data);
		if(T->LTag == Link)
		{
			T = T->lchild;
		}
		else
		{
			T = T->rchild;
		}
	}
}

void InThreading(BiThrTree p)
{
	if(p)
	{
		InThreading(p->lchild);
		if(!p->lchild)
		{
			p->lchild = pre;
			p->LTag = Thread;
		}
		if(!pre->rchild)
		{
			pre->rchild = p;
			pre->RTag = Thread;
		}
		pre = p;
		InThreading(p->rchild); 
	}
}

void InOrderThreading(BiThrTree & Thrt, BiThrTree T)
{
	Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
	if(Thrt == NULL)
	{
		exit(-1);
	}
	
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	
	if(!T)
	{
		Thrt->lchild = Thrt;
	}
	else
	{
		Thrt->lchild = T;
		pre = Thrt;
		InThreading(T);
		pre->rchild = Thrt;
		pre->RTag = Thread;
		Thrt->rchild = pre;
	}
}

void InOrderTraverse_Thr(BiThrTree Thrt, void(*Visit)(TElemType))
{
	BiThrTree T = Thrt->lchild;
	while(T != Thrt)
	{
		while(T->LTag == Link)
		{
			T = T->lchild;
		}
		Visit(T->data);
		while(T->RTag == Thread && T->rchild != Thrt)
		{
			T = T->rchild;
			Visit(T->data);
		}
		T = T->rchild;
	}
}

void PostThreading(BiThrTree p)
{
	if(p)
	{
		PostThreading(p->lchild);
		PostThreading(p->rchild);
		if(!p->lchild)
		{
			p->lchild = pre;
			p->LTag = Thread;
		}
		if(!pre->rchild)
		{
			pre->rchild = p;
			pre->RTag = Thread;
		}
		pre = p;
	}
}

void PostOrderThreading(BiThrTree & Thrt, BiThrTree T)
{
	Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
	if(Thrt == NULL)
	{
		exit(-1);
	}
	
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	
	if(!T)
	{
		Thrt->lchild = Thrt->rchild = Thrt;
	}
	else
	{
		Thrt->lchild = Thrt->rchild = T;
		pre = Thrt;
		PostThreading(T);
		if(pre->RTag != Link)
		{
			pre->rchild = Thrt;
			pre->RTag = Thread;
		}
	}
}

void PostOrderTraverse_Thr(BiThrTree Thrt, void(*Visit)(TElemType))
{
	BiThrTree p = Thrt;
	BiThrTree T = Thrt->lchild;
	
	while(T->LTag == Link || T->RTag == Link)
	{
		while(T->LTag == Link)
		{
			T = T->lchild;
		}
		if(T->RTag == Link)
		{
			T = T->rchild;
		}
	}
	
	while(T != Thrt)
	{
		Visit(T->data);
		p = Parent(Thrt, T);
		
		if(p == Thrt)
		{
			T = Thrt;
		}
		else if(p->rchild == T || p->RTag != Link)
		{
			T = p;
		}
		else
		{
			while(p->RTag == Link)
			{
				p = p->rchild;
				while(p->LTag == Link)
				{
					p = p->lchild;
				}
			}
			T = p;
		}
	}
}

# include "LinkThreadBiTreeQueue.cpp"

BiThrTree Parent(BiThrTree T, BiThrTree p)
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
			if(a->LTag == Link && a->lchild == p || a->RTag == Link && a->rchild == p)
			{
				destroyQueue(&q);
				return a;
			}
			else
			{
				if(a->LTag == Link)
				{
					enqueue(&q, a->lchild);
				}
				if(a->RTag == Link)
				{
					enqueue(&q, a->rchild);
				}
			}
		}
	}
	
	destroyQueue(&q);
	
	return NULL;
}

