# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

# define N 16
# define m 3
# define MAX 5

typedef int KeyType;

typedef struct Others
{
	char info[MAX];
} Others;

typedef struct Record
{
	KeyType key;
	Others others;
} Record;

typedef struct BTNode
{
	int keynum;
	struct BTNode * parent;
	struct Node
	{
		KeyType key;
		struct BTNode * ptr;
		Record * recptr;
	} node[m + 1];
} BTNode, * BTree;

typedef struct Result
{
	BTree pt;
	int i;
	int tag;
} Result;

void InitBTree(BTree &);
void DestroyBTree(BTree &);
int Search(BTree, KeyType);
Result SearchBTree(BTree, KeyType);
void Insert(BTree &, int, Record *, BTree);
void split(BTree &, BTree &);
void NewRoot(BTree &, Record *, BTree);
void InsertBTree(BTree &, Record *, BTree, int);
void TraverseBTree(BTree, void(*Visit)(BTNode, int));

void print(BTNode n, int i)
{
	printf("(%d, %s) ", n.node[i].key, n.node[i].recptr->others.info);
}

int main(void)
{
	BTree BT;
	Result result;
	int i;
	Record r[N] = {{24,"1"}, {45,"2"}, {53,"3"}, {12,"4"},
				   {37,"5"}, {50,"6"}, {61,"7"}, {90,"8"},
				   {100,"9"}, {70,"10"}, {3,"11"}, {30,"12"},
				   {26,"13"}, {85,"14"}, {3,"15"}, {7,"16"}};
	
//	InitBTree(BT);
//	for(i = 0; i < N; ++i)
//	{
//		result = SearchBTree(BT, r[i].key);
//		if(!result.tag)
//		{
//			InsertBTree(BT, &r[i], result.pt, result.i);
//		}
//	}
//	TraverseBTree(BT, print);
//	printf("\n");
	
//	result = SearchBTree(BT, 70);
//	if(result.tag)
//	{
//		printf("\n");
//		print(*(result.pt), result.i);
//		printf("\n");
//	}
//	else
//	{
//		printf("\n");
//		printf("Ã»ÕÒµ½£¡\n");
//	}
	
	DestroyBTree(BT);
	
	return 0;
}

void InitBTree(BTree & BT)
{
	BT = NULL;
}

void DestroyBTree(BTree & BT)
{
	int i;
	
	if(BT)
	{
		for(i = 0; i <= BT->keynum; ++i)
		{
			DestroyBTree(BT->node[i].ptr);
		}
		free(BT);
		BT = NULL;
	}
}

int Search(BTree p, KeyType key)
{
	int i = 0;
	int j;
	
	for(j = 1; j <= p->keynum; ++j)
	{
		if(p->node[j].key <= key)
		{
			i = j;
		}
	}
	
	return i;
}

Result SearchBTree(BTree T, KeyType key)
{
	BTree p = T;
	BTree q = NULL;
	bool found = false;
	int i = 0;
	Result r;
	
	while(p && !found)
	{
		i = Search(p, key);
		if(i > 0 && p->node[i].key == key)
		{
			found = true;
		}
		else
		{
			q = p;
			p = p->node[i].ptr;
		}
	}
	
	r.i = i;
	if(found)
	{
		r.pt = p;
		r.tag = 1;
	}
	else
	{
		r.pt = q;
		r.tag = 0;
	}
	
	return r;
}

void Insert(BTree & q, int i, Record * r, BTree ap)
{
	int j;
	
	for(j = q->keynum; j > i; --j)
	{
		q->node[j + 1] = q->node[j];
	}
	
	q->node[i + 1].key = r->key;
	q->node[i + 1].ptr = ap;
	q->node[i + 1].recptr = r;
	q->keynum++;
}

void split(BTree & q, BTree & ap)
{
	int i;
	int s = (m + 1) / 2;
	
	ap = (BTree)malloc(sizeof(BTNode));
	
	ap->node[0].ptr = q->node[s].ptr;
	for(i = s + 1; i <= m; ++i)
	{
		ap->node[i - s] = q->node[i];
		if(ap->node[i - s].ptr)
		{
			ap->node[i - s].ptr->parent = ap;
		}
	}
	ap->keynum = m - s;
	ap->parent = q->parent;
	q->keynum = s - 1;
}

void NewRoot(BTree & T, Record * r, BTree ap)
{
	BTree p;
	
	p = (BTree)malloc(sizeof(BTNode));
	
	p->node[0].ptr = T;
	T = p;
	if(T->node[0].ptr)
	{
		T->node[0].ptr->parent = T;
	}
	
	T->parent = NULL;
	T->keynum = 1;
	T->node[1].key = r->key;
	T->node[1].recptr = r;
	T->node[1].ptr = ap;
	if(T->node[1].ptr)
	{
		T->node[1].ptr->parent = T;
	}
}

void InsertBTree(BTree & T, Record * r, BTree q, int i)
{
	BTree ap = NULL;
	bool finished = false;
	int s;
	Record * rx;
	
	rx = r;
	
	while(q && !finished)
	{
		Insert(q, i, rx, ap);
		
		if(q->keynum < m)
		{
			finished = true;
		}
		else
		{
			s = (m + 1) / 2;
			rx = q->node[s].recptr;
			split(q, ap);
			q = q->parent;
			if(q)
			{
				i = Search(q, rx->key);
			}
		}
	}
	
	if(!finished)
	{
		NewRoot(T, rx, ap);
	}
}

void TraverseBTree(BTree T, void(*Visit)(BTNode, int))
{
	int i;
	
	if(T)
	{
		if(T->node[0].ptr)
		{
			TraverseBTree(T->node[0].ptr, Visit);
		}
		for(i = 1; i <= T->keynum; ++i)
		{
			Visit(*T, i);
			if(T->node[i].ptr)
			{
				TraverseBTree(T->node[i].ptr, Visit);
			}
		}
	}
}

