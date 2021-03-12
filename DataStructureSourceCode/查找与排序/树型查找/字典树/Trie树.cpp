# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <string.h>

# define N 16
# define LENGTH 27
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

typedef struct TrieNode
{
	NodeKind kind;
	union
	{
		struct
		{
			KeysType K;
			Record * infoptr;
		} lf;
		struct
		{
			struct TrieNode * ptr[LENGTH];
		} bh;
	};
} TrieNode, * TrieTree;

# define EQ(a,b) (!strcmp((a),(b)))
# define LT(a,b) (strcmp((a),(b))<0)
# define LQ(a,b) (strcmp((a),(b))<=0)

void InitTrieTree(TrieTree &);
void DestroyTrieTree(TrieTree &);
int ord(char);
Record * SearchTrieTree(TrieTree, KeysType);
void InsertTrieTree(TrieTree &, Record *);
void TraverseTrieTree(TrieTree, void(*Visit)(Record *));

void print(Record * r)
{
	printf("(%s, %d) ", r->key.ch, r->others.ord);
}

int main(void)
{
	TrieTree Trie;
	int i;
	KeysType K;
	Record * p;
	Record r[N] = {{{"CAI"},1}, {{"CAO"},2}, {{"LI"},3}, {{"LAN"},4},
				  {{"CHA"},5}, {{"CHANG"},6}, {{"WEN"},7}, {{"CHAO"},8},
				  {{"YUN"},9}, {{"YANG"},10}, {{"LONG"},11}, {{"WANG"},12},
				  {{"ZHAO"},13}, {{"LIU"},14}, {{"WU"},15}, {{"CHEN"},16}};
	
//	InitTrieTree(Trie);
//	for(i = 0; i < N; ++i)
//	{
//		r[i].key.num = strlen(r[i].key.ch) + 1;
//		r[i].key.ch[r[i].key.num] = Nil;
//		p = SearchTrieTree(Trie, r[i].key);
//		if(!p)
//		{
//			InsertTrieTree(Trie, &r[i]);
//		}
//	}
//	TraverseTrieTree(Trie, print);
//	printf("\n");
	
//	K = r[14].key;
//	p = SearchTrieTree(Trie, K);
//	if(p)
//	{
//		print(p);
//		printf("\n");
//	}
//	else
//	{
//		printf("Ã»ÕÒµ½£¡\n");
//	}
	
	DestroyTrieTree(Trie);
	
	return 0;
}

void InitTrieTree(TrieTree & T)
{
	T = NULL;
}

void DestroyTrieTree(TrieTree & T)
{
	int i;
	
	if(T)
	{
		for(i = 0; i < LENGTH; ++i)
		{
			if(T->kind == BRANCH && T->bh.ptr[i])
			{
				if(T->bh.ptr[i]->kind == BRANCH)
				{
					DestroyTrieTree(T->bh.ptr[i]);
				}
				else
				{
					free(T->bh.ptr[i]);
					T->bh.ptr[i] = NULL;
				}
			}
		}
		
		free(T);
		T = NULL;
	}
}

int ord(char c)
{
	if(c >= 'A' && c <= 'Z')
	{
		return c - 'A' + 1;
	}
	else
	{
		return 0;
	}
}

Record * SearchTrieTree(TrieTree T, KeysType K)
{
	TrieTree p;
	int i;
	
	for(p = T, i = 0; p && p->kind == BRANCH && i < K.num; p = p->bh.ptr[ord(K.ch[i])], ++i);
	
	if(p && p->kind == LEAF && p->lf.K.num == K.num && EQ(p->lf.K.ch,K.ch))
	{
		return p->lf.infoptr;
	}
	else
	{
		return NULL;
	}
}

void InsertTrieTree(TrieTree & T, Record * r)
{
	TrieTree p, q, ap;
	int i = 0, j;
	KeysType K1, K = r->key;
	
	if(!T)
	{
		T = (TrieTree)malloc(sizeof(TrieNode));
		T->kind = BRANCH;
		
		for(i = 0; i < LENGTH; ++i)
		{
			T->bh.ptr[i] = NULL;
		}
		
		p = T->bh.ptr[ord(K.ch[0])] = (TrieTree)malloc(sizeof(TrieNode));
		p->kind = LEAF;
		p->lf.K = K;
		p->lf.infoptr = r;
	}
	else
	{
		for(p = T, i = 0; p && p->kind == BRANCH && i < K.num; ++i)
		{
			q = p;
			p = p->bh.ptr[ord(K.ch[i])];
		}
		
		i--;
		
		if(p && p->kind == LEAF && p->lf.K.num == K.num && EQ(p->lf.K.ch,K.ch))
		{
			return;
		}
		else
		{
			if(!p)
			{
				p = q->bh.ptr[ord(K.ch[i])] = (TrieTree)malloc(sizeof(TrieNode));
				p->kind = LEAF;
				p->lf.K = K;
				p->lf.infoptr = r;
			}
			else if(p->kind == LEAF)
			{
				K1 = p->lf.K;
				do
				{
					ap = q->bh.ptr[ord(K.ch[i])] = (TrieTree)malloc(sizeof(TrieNode));
					ap->kind = BRANCH;
					for(j = 0; j < LENGTH; ++j)
					{
						ap->bh.ptr[j] = NULL;
					}
					q = ap;
					i++;
				} while(ord(K.ch[i]) == ord(K1.ch[i]));
				
				q->bh.ptr[ord(K1.ch[i])] = p;
				p = q->bh.ptr[ord(K.ch[i])] = (TrieTree)malloc(sizeof(TrieNode));
				p->kind = LEAF;
				p->lf.K = K;
				p->lf.infoptr = r;
			}
		}
	}
}

void TraverseTrieTree(TrieTree T, void(*Visit)(Record *))
{
	TrieTree p;
	int i;
	
	if(T)
	{
		for(i = 0; i < LENGTH; ++i)
		{
			p = T->bh.ptr[i];
			if(p && p->kind == LEAF)
			{
				Visit(p->lf.infoptr);
			}
			else if(p && p->kind == BRANCH)
			{
				TraverseTrieTree(p, Visit);
			}
		}
	}
}

