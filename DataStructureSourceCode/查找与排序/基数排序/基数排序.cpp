# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

# define MAX_NUM_OF_KEY 8
# define RADIX 10
# define MAX_SPACE 1000
# define N 10

typedef int KeyType;
typedef int InfoType;

typedef struct RedType
{
	KeyType key;
	InfoType otherinfo;
} RedType;

typedef char KeysType;

typedef struct SLCell
{
	KeysType keys[MAX_NUM_OF_KEY];
	InfoType otheritems;
	int next;
} SLCell;

typedef struct SLList
{
	SLCell r[MAX_SPACE];
	int keynum;
	int recnum;
} SLList;

typedef int ArrType[RADIX];

void InitList(SLList &, RedType D[], int);
int ord(char);
void Distribute(SLCell r[], int, ArrType, ArrType);
int succ(int);
void Collect(SLCell r[], ArrType, ArrType);
void printl(SLList);
void RadixSort(SLList &);
void print(SLList);
void Sort(SLList, int adr[]);
void Rearrange(SLList &, int adr[]);

int main(void)
{
	SLList L;
	RedType r[N] = {{278, 1}, {109, 2}, {63, 3}, {930, 4}, {589, 5}, {184, 6}, {505, 7}, {269, 8}, {8, 9}, {83, 10}};
	int * adr;
	
	InitList(L, r, N);
	printf("排序前(next域还没赋值)：\n");
	print(L);
	RadixSort(L);
	printf("排序后(静态链表)：\n");
	print(L);
	
	adr = (int *)malloc(sizeof(int) * (L.recnum));
	Sort(L, adr);
	Rearrange(L, adr);
	printf("排序后(重排记录)：\n");
	print(L);
	
	free(adr);
	
	return 0;
}

void InitList(SLList & L, RedType D[], int n)
{
	char c[MAX_NUM_OF_KEY], c1[MAX_NUM_OF_KEY];
	int i, j, max = D[0].key;
	
	for(i = 1; i < n; ++i)
	{
		if(max < D[i].key)
		{
			max = D[i].key;
		}
	}
	
	L.keynum = int(ceil(log10(max)));
	L.recnum = n;
	
	for(i = 1; i <= n; ++i)
	{
		L.r[i].otheritems = D[i-1].otherinfo;
		itoa(D[i-1].key, c, 10);
		
		for(j = strlen(c); j < L.keynum; ++j)
		{
			strcpy(c1, "0");
			strcpy(c1, c);
			strcpy(c, c1);
		}
		
		for(j = 0; j < L.keynum; ++j)
		{
			L.r[i].keys[j] = c[L.keynum - 1 - j];
		}
	}
}

int ord(char c)
{
	return c - '0';
}

void Distribute(SLCell r[], int i, ArrType f, ArrType e)
{
	int j, p;
	
	for(j = 0; j < RADIX; ++j)
	{
		f[j] = 0;
	}
	
	for(p = r[0].next; p; p = r[p].next)
	{
		j = ord(r[p].keys[i]);
		if(!f[j])
		{
			f[j] = p;
		}
		else
		{
			r[e[j]].next = p;
		}
		e[j] = p;
	}
}

int succ(int i)
{
	return ++i;
}

void Collect(SLCell r[], ArrType f, ArrType e)
{
	int j, t;
	
	for(j = 0; !f[j]; j = succ(j));
	
	r[0].next = f[j];
	
	t = e[j];
	
	while(j < RADIX - 1)
	{
		for(j = succ(j); j < RADIX - 1 && !f[j]; j = succ(j));
		
		if(f[j])
		{
			r[t].next = f[j];
			t = e[j];
		}
	}
	
	r[t].next = 0;
}

void printl(SLList L)
{
	int i = L.r[0].next;
	int j;
	
	while(i)
	{
		for(j = L.keynum - 1; j >= 0; --j)
		{
			printf("%c", L.r[i].keys[j]);
		}
		printf(" ");
		
		i = L.r[i].next;
	}
}

void RadixSort(SLList & L)
{
	int i;
	ArrType f, e;
	
	for(i = 0; i < L.recnum; ++i)
	{
		L.r[i].next = i + 1;
	}
	L.r[L.recnum].next = 0;
	
	for(i = 0; i < L.keynum; ++i)
	{
		Distribute(L.r, i, f, e);
		Collect(L.r, f, e);
		printf("第%d趟收集后：\n", i + 1);
		printl(L);
		printf("\n");
	}
}

void print(SLList L)
{
	int i, j;
	
	printf("keynum=%d recnum=%d\n", L.keynum, L.recnum);
	
	for(i = 1; i <= L.recnum; ++i)
	{
		printf("keys=");
		for(j = L.keynum - 1; j >= 0; --j)
		{
			printf("%c", L.r[i].keys[j]);
		}
		printf(" otheritems=%d next=%d\n", L.r[i].otheritems, L.r[i].next);
	}
}

void Sort(SLList L, int adr[])
{
	int i = 1, p = L.r[0].next;
	
	while(p)
	{
		adr[i++] = p;
		p = L.r[p].next;
	}
}

void Rearrange(SLList & L, int adr[])
{
	int i, j, k;
	
	for(i = 1; i < L.recnum; ++i)
	{
		if(adr[i] != i)
		{
			j = i;
			L.r[0] = L.r[i];
			while(adr[j] != i)
			{
				k = adr[j];
				L.r[j] = L.r[k];
				adr[j] = j;
				j = k;
			}
			L.r[j] = L.r[0];
			adr[j] = j;
		}
	}
}

