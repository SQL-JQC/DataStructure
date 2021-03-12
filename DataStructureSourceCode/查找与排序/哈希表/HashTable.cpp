# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

# define NULL_KEY 0
# define N 10

typedef int Status;

typedef int KeyType;

typedef struct ElemType
{
	KeyType key;
	int ord;
} ElemType;

typedef struct HashTable
{
	ElemType * elem;
	int count;
	int sizeindex;
} HashTable;

# define SUCCESS 1
# define UNSUCCESS 0
# define DUPLICATE -1

# define EQ(a,b) ((a)==(b))
# define LT(a,b) ((a)<(b))
# define LQ(a,b) ((a)<=(b))

void InitHashTable(HashTable &);
void DestroyHashTable(HashTable &);
int Hash(KeyType);
void collision(int &, int);
Status SearchHashTable(HashTable, KeyType, int &, int &);
void RecreateHashTable(HashTable &);
Status InsertHashTable(HashTable &, ElemType);
void TraverseHashTable(HashTable, void(*Visit)(int, ElemType));
Status Find(HashTable, KeyType, int &);

void print(int p, ElemType e)
{
	printf("address=%d (%d, %d)\n", p, e.key, e.ord);
}

int main(void)
{
	HashTable HT;
	int i, p;
	Status s;
	KeyType key;
	ElemType e[N] = {{17, 1}, {60, 2}, {29, 3}, {38, 4}, {1, 5}, {2, 6}, {3, 7}, {4, 8}, {60, 9}, {13, 10}};
	
//	InitHashTable(HT);
//	for(i = 0; i < N-1; ++i)
//	{
//		s = InsertHashTable(HT, e[i]);
//		if(s == DUPLICATE)
//		{
//			printf("表中已有关键字为%d的记录，无法再插入记录(%d, %d)\n", e[i].key, e[i].key, e[i].ord);
//		}
//	}
//	TraverseHashTable(HT, print);
//	printf("\n");
	
//	key = 60;
//	s = Find(HT, key, p);
//	if(s == SUCCESS)
//	{
//		print(p, HT.elem[p]);
//		printf("\n");
//	}
//	else
//	{
//		printf("没找到！\n");
//	}
	
	//插入最后一个元素制造过多的冲突，以导致哈希表重建 
//	s = InsertHashTable(HT, e[i]);
//	if(s == UNSUCCESS)
//	{
//		InsertHashTable(HT, e[i]);
//		TraverseHashTable(HT, print);
//	}
//	else
//	{
//		printf("哈希表没有重建\n");
//		TraverseHashTable(HT, print);
//	}
	
	DestroyHashTable(HT);
	
	return 0;
}

int hashsize[] = {11, 19, 29, 37};
int m = 0;

void InitHashTable(HashTable & H)
{
	int i;
	
	H.count = 0;
	H.sizeindex = 0;
	
	m = hashsize[0];
	
	H.elem = (ElemType *)malloc(sizeof(ElemType) * m);
	if(!H.elem)
	{
		exit(-1);
	}
	
	for(i = 0; i < m; ++i)
	{
		H.elem[i].key = NULL_KEY;
	}
}

void DestroyHashTable(HashTable & H)
{
	free(H.elem);
	H.elem = NULL;
	H.count = 0;
	H.sizeindex = 0;
}

int Hash(KeyType key)
{
	return key%m;
}

void collision(int & p, int d)
{
	p = (p + d)%m;
}

Status SearchHashTable(HashTable H, KeyType key, int & p, int & c)
{
	p = Hash(key);
	
	while(H.elem[p].key != NULL_KEY && !EQ(key,H.elem[p].key))
	{
		c++;
		if(c < m)
		{
			collision(p, c);
		}
		else
		{
			break;
		}
	}
	
	if EQ(key,H.elem[p].key)
	{
		return SUCCESS;
	}
	else
	{
		return UNSUCCESS;
	}
}

void RecreateHashTable(HashTable & H)
{
	int i;
	int count = H.count;
	ElemType * p;
	
	ElemType * elem = (ElemType *)malloc(sizeof(ElemType) * count);
	
	p = elem;
	
	printf("重建哈希表\n");
	
	for(i = 0; i < m; ++i)
	{
		if((H.elem + i)->key != NULL_KEY)
		{
			*p++ = *(H.elem + i);
		}
	}
	
	H.count = 0;
	H.sizeindex++;
	
	m = hashsize[H.sizeindex];
	p = (ElemType *)realloc(H.elem, sizeof(ElemType) * m);
	if(!p)
	{
		exit(-1);
	}
	
	H.elem = p;
	
	for(i = 0; i < m; ++i)
	{
		H.elem[i].key = NULL_KEY;
	}
	
	for(p = elem; p < elem + count; ++p)
	{
		InsertHashTable(H, *p);
	}
}

Status InsertHashTable(HashTable & H, ElemType e)
{
	int c, p;
	
	c = 0;
	
	if(SearchHashTable(H, e.key, p, c))
	{
		return DUPLICATE;
	}
	else if(c < (hashsize[H.sizeindex] / 2))
	{
		H.elem[p] = e;
		H.count++;
		return SUCCESS;
	}
	else
	{
		RecreateHashTable(H);
		return UNSUCCESS;
	}
}

void TraverseHashTable(HashTable H, void(*Visit)(int, ElemType))
{
	printf("哈希地址 0 ~ %d\n", (m - 1));
	for(int i = 0; i < m; ++i)
	{
		if(H.elem[i].key != NULL_KEY)
		{
			Visit(i, H.elem[i]);
		}
	}
}

Status Find(HashTable H, KeyType key, int & p)
{
	int c = 0;
	
	p = Hash(key);
	
	while(H.elem[p].key != NULL_KEY && !EQ(key,H.elem[p].key))
	{
		c++;
		if(c < m)
		{
			collision(p, c);
		}
		else
		{
			return UNSUCCESS;
		}
	}
	
	if EQ(key,H.elem[p].key)
	{
		return SUCCESS;
	}
	else
	{
		return UNSUCCESS;
	}
}

