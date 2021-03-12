# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

# define N 10

typedef int KeyType;

typedef struct ElemType
{
	KeyType key;
	int others;
} ElemType;

typedef ElemType TElemType;

typedef struct BiTNode
{
	TElemType data;
	struct BiTNode * lchild;
	struct BiTNode * rchild;
} BiTNode, * BiTree;

# define EQ(a,b) ((a)==(b))
# define LT(a,b) ((a)<(b))
# define LQ(a,b) ((a)<=(b))

void InitBST(BiTree &);
BiTree SearchBST(BiTree, KeyType);
bool SearchBST(BiTree &, KeyType, BiTree, BiTree &);
bool InsertBST(BiTree &, ElemType);
void Delete(BiTree &);
bool DeleteBST(BiTree &, KeyType);
void DestroyBST(BiTree &);
void TraverseBST(BiTree, void(*Visit)(ElemType));
void PreOrderTraverse(BiTree, void(*Visit)(ElemType));

void print(ElemType e)
{
	printf("(%d,%d) ", e.key, e.others);
}

int main(void)
{
	BiTree T;
	BiTree p;
	ElemType e[N] = {{3, 1}, {2, 2}, {1, 3}, {7, 4}, {5, 5}, {10, 6}, {4, 7}, {9, 8}, {8, 9}, {6, 10}};
	int i;
	
//	InitBST(T);
//	for(i = 0; i < N; ++i)
//	{
//		InsertBST(T, e[i]);
//	}
//	TraverseBST(T, print);
//	printf("\n");
//	PreOrderTraverse(T, print);
	
//	p = SearchBST(T, 4);
//	printf("\n(%d, %d)\n", p->data.key, p->data.others);
	
//	DeleteBST(T, 4);
//	TraverseBST(T, print);
	
	DestroyBST(T);
	
	return 0;
}

void InitBST(BiTree & T)
{
	T = NULL;
}

BiTree SearchBST(BiTree T, KeyType key)
{
	if(!T || EQ(key,T->data.key))
	{
		return T;
	}
	else if LT(key,T->data.key)
	{
		return SearchBST(T->lchild, key);
	}
	else
	{
		return SearchBST(T->rchild, key);
	}
}

bool SearchBST(BiTree & T, KeyType key, BiTree f, BiTree & p)
{
	if(!T)
	{
		p = f;
		return false;
	}
	else if EQ(key,T->data.key)
	{
		p = T;
		return true;
	}
	else if LT(key,T->data.key)
	{
		return SearchBST(T->lchild, key, T, p);
	}
	else
	{
		return SearchBST(T->rchild, key, T, p);
	}
}

bool InsertBST(BiTree & T, ElemType e)
{
	BiTree p, s;
	
	if(!SearchBST(T, e.key, NULL, p))
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = e;
		s->lchild = NULL;
		s->rchild = NULL;
		
		if(!p)
		{
			T = s;
		}
		else if LT(e.key,p->data.key)
		{
			p->lchild = s;
		}
		else
		{
			p->rchild = s;
		}
		
		return true;
	}
	else
	{
		return false;
	}
}

void Delete(BiTree & p)
{
	BiTree q, s;
	
	if(!p->rchild)
	{
		q = p;
		p = p->lchild;
		free(q);
	}
	else if(!p->lchild)
	{
		q = p;
		p = p->rchild;
		free(q);
	}
	else
	{
		q = p;
		s = p->lchild;
		
		while(s->rchild)
		{
			q = s;
			s = s->rchild;
		}
		
		p->data = s->data;
		
		if(q != p)
		{
			q->rchild = s->lchild;
		}
		else
		{
			q->lchild = s->lchild;
		}
		
		free(s);
	}
}

bool DeleteBST(BiTree & T, KeyType key)
{
	if(!T)
	{
		return false;
	}
	else
	{
		if EQ(key,T->data.key)
		{
			Delete(T);
		}
		else if LT(key,T->data.key)
		{
			DeleteBST(T->lchild, key);
		}
		else
		{
			DeleteBST(T->rchild, key);
		}
		
		return true;
	}
}

void DestroyBST(BiTree & T)
{
	if(T)
	{
		if(T->lchild)
		{
			DestroyBST(T->lchild);
		}
		if(T->rchild)
		{
			DestroyBST(T->rchild);
		}
		free(T);
		T = NULL;
	}
}

void TraverseBST(BiTree T, void(*Visit)(ElemType))
{
	if(T)
	{
		TraverseBST(T->lchild, Visit);
		Visit(T->data);
		TraverseBST(T->rchild, Visit);
	}
}

void PreOrderTraverse(BiTree T, void(*Visit)(ElemType))
{
	if(T)
	{
		Visit(T->data);
		PreOrderTraverse(T->lchild, Visit);
		PreOrderTraverse(T->rchild, Visit);
	}
}

