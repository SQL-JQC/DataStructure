# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <string.h>

# define N 16
# define MAX_KEY_LEN 16
# define Nil ' '

typedef struct Others
{
	int ord;
} Others;

typedef struct KeysType
{
	char ch[MAX_KEY_LEN];
	int num;
} KeysType;

typedef struct Record
{
	KeysType key;
	Others others;
} Record;

typedef enum NodeKind
{
	LEAF, BRANCH
} NodeKind;

typedef struct DLTNode
{
	char symbol;
	struct DLTNode * next;
	NodeKind kind;
	union
	{
		Record * infoptr;
		struct DLTNode * first;
	};
} DLTNode, * DLTree;

void InitDLTree(DLTree &);
void DestroyDLTree(DLTree &);
Record * SearchDLTree(DLTree, KeysType);
void InsertDLTree(DLTree &, Record *);
void TraverseDLTree(DLTree, void(*Visit)(Record));

void print(Record r)
{
	int i;
	printf("(");
	for(i = 0; i < r.key.num; ++i)
	{
		printf("%c", r.key.ch[i]);
	}
	printf(", %d) ", r.others.ord);
}

int main(void)
{
	DLTree DLT;
	int i;
	KeysType K;
	Record * p;
	Record r[N] = {{{"CAI"},1}, {{"CAO"},2}, {{"LI"},3}, {{"LAN"},4},
				  {{"CHA"},5}, {{"CHANG"},6}, {{"WEN"},7}, {{"CHAO"},8},
				  {{"YUN"},9}, {{"YANG"},10}, {{"LONG"},11}, {{"WANG"},12},
				  {{"ZHAO"},13}, {{"LIU"},14}, {{"WU"},15}, {{"CHEN"},16}};
	
//	InitDLTree(DLT);
//	for(i = 0; i < N; ++i)
//	{
//		r[i].key.num = strlen(r[i].key.ch);
//		p = SearchDLTree(DLT, r[i].key);
//		if(!p)
//		{
//			InsertDLTree(DLT, &r[i]);
//		}
//	}
//	TraverseDLTree(DLT, print);
//	printf("\n");
	
//	K = r[14].key;
//	p = SearchDLTree(DLT, K);
//	if(p)
//	{
//		print(*p);
//		printf("\n");
//	}
//	else
//	{
//		printf("Ã»ÕÒµ½£¡\n");
//	}
	
	DestroyDLTree(DLT);
	
	return 0;
}

void InitDLTree(DLTree & T)
{
	T = NULL;
}

void DestroyDLTree(DLTree & T)
{
	if(T)
	{
		if(T->kind == BRANCH && T->first)
		{
			DestroyDLTree(T->first);
		}
		if(T->next)
		{
			DestroyDLTree(T->next);
		}
		free(T);
		T = NULL;
	}
}

Record * SearchDLTree(DLTree T, KeysType K)
{
	DLTree p;
	int i;
	
	if(T)
	{
		p = T;
		i = 0;
		
		while(p && i < K.num)
		{
			while(p && p->symbol != K.ch[i])
			{
				p = p->next;
			}
			if(p && i < K.num)
			{
				p = p->first;
			}
			i++;
		}
		
		if(!p)
		{
			return NULL;
		}
		else
		{
			return p->infoptr;
		}
	}
	else
	{
		return NULL;
	}
}

void InsertDLTree(DLTree & T, Record * r)
{
	DLTree p = NULL;
	DLTree q, ap;
	KeysType K = r->key;
	int i = 0;
	
	if(!T && K.num)
	{
		T = ap = (DLTree)malloc(sizeof(DLTNode));
		
		for(; i < K.num; ++i)
		{
			if(p)
			{
				p->first = ap;
			}
			ap->next = NULL;
			ap->symbol = K.ch[i];
			ap->kind = BRANCH;
			p = ap;
			ap = (DLTree)malloc(sizeof(DLTNode));
		}
		
		p->first = ap;
		ap->next = NULL;
		ap->symbol = Nil;
		ap->kind = LEAF;
		ap->infoptr = r;
	}
	else
	{
		p = T;
		
		while(p && i < K.num)
		{
			while(p && p->symbol < K.ch[i])
			{
				q = p;
				p = p->next;
			}
			if(p && p->symbol == K.ch[i])
			{
				q = p;
				p = p->first;
				i++;
			}
			else
			{
				ap = (DLTree)malloc(sizeof(DLTNode));
				
				if(q->first == p)
				{
					q->first = ap;
				}
				else
				{
					q->next = ap;
				}
				
				ap->next = p;
				ap->symbol = K.ch[i];
				ap->kind = BRANCH;
				
				p = ap;
				ap = (DLTree)malloc(sizeof(DLTNode));
				i++;
				
				for(; i < K.num; ++i)
				{
					p->first = ap;
					ap->next = NULL;
					ap->symbol = K.ch[i];
					ap->kind = BRANCH;
					p = ap;
					ap = (DLTree)malloc(sizeof(DLTNode));
				}
				
				p->first = ap;
				ap->next = NULL;
				ap->symbol = Nil;
				ap->kind = LEAF;
				ap->infoptr = r;
			}
		}
	}
}

# include "DictionaryTreeStack.cpp"

void TraverseDLTree(DLTree T, void(*Visit)(Record))
{
	Stack s;
	SElemType e;
	DLTree p;
	int i = 0;
	int n = 8;
	
	initStack(&s);
	
	if(T)
	{
		e.p = T;
		e.ch = T->symbol;
		push(&s, e);
		
		p = T->first;
		while(p->kind == BRANCH)
		{
			e.p = p;
			e.ch = p->symbol;
			push(&s, e);
			p = p->first;
		}
		
		e.p = p;
		e.ch = p->symbol;
		push(&s, e);
		
		Visit(*(p->infoptr));
		i++;
		
		while(!emptyStack(&s))
		{
			pop(&s, &e);
			
			p = e.p;
			if(p->next)
			{
				p = p->next;
				while(p->kind == BRANCH)
				{
					e.p = p;
					e.ch = p->symbol;
					push(&s, e);
					p = p->first;
				}
				
				e.p = p;
				e.ch = p->symbol;
				push(&s, e);
				
				Visit(*(p->infoptr));
				i++;
				
				if(i%n == 0)
				{
					printf("\n");
				}
			}
		}
	}
	
	destroyStack(&s);
}

