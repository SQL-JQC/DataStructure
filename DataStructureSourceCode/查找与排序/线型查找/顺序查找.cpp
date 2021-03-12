# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

# define N 11

typedef int KeyType;

typedef struct ElemType
{
	KeyType key;
} ElemType;

typedef struct SSTable
{
	ElemType * elem;
	int length;
} SSTable;

# define EQ(a,b) ((a)==(b))
# define LT(a,b) ((a)<(b))
# define LQ(a,b) ((a)<=(b))

void Create_Seq(SSTable &, ElemType e[], int);
void Ascend(SSTable &);
void Create_Ord(SSTable &, ElemType e[], int);
bool Destroy(SSTable &);
int Search_Seq(SSTable, KeyType);
int Search_Bin(SSTable, KeyType);
void Traverse(SSTable, void(*Visit)(ElemType));

void print(ElemType e)
{
	printf("%d ", e.key);
}

int main(void)
{
	SSTable ST;
	ElemType e[N] = {3, 2, 1, 8, 6, 4, 5, 7, 11, 10, 9};
	int pos;
	
//	Create_Seq(ST, e, N);
//	Traverse(ST, print);
//	pos = Search_Seq(ST, 4);
//	printf("\n%d\n", pos);

//	Create_Ord(ST, e, N);
//	Traverse(ST, print);
//	pos = Search_Seq(ST, 4);
//	printf("\n%d\n", pos);
	
//	Create_Ord(ST, e, N);
//	Traverse(ST, print);
//	pos = Search_Bin(ST, 4);
//	printf("\n%d\n", pos);
	
	Destroy(ST);
	
	return 0;
}

void Create_Seq(SSTable & ST, ElemType e[], int n)
{
	int i;
	
	ST.elem = (ElemType *)calloc(n + 1, sizeof(ElemType));
	if(!ST.elem)
	{
		exit(-1);
	}
	
	for(i = 1; i <= n; ++i)
	{
		ST.elem[i] = e[i - 1];
	}
	
	ST.length = n;
}

void Ascend(SSTable & ST)
{
	int i, j, k;
	
	for(i = 1; i < ST.length; ++i)
	{
		k = i;
		
		ST.elem[0] = ST.elem[i];
		
		for(j = i + 1; j <= ST.length; ++j)
		{
			if LT(ST.elem[j].key,ST.elem[0].key)
			{
				k = j;
				ST.elem[0] = ST.elem[j];
			}
		}
		
		if(k != i)
		{
			ST.elem[k] = ST.elem[i];
			ST.elem[i] = ST.elem[0];
		}
	}
}

void Create_Ord(SSTable & ST, ElemType e[], int n)
{
	Create_Seq(ST, e, n);
	Ascend(ST);
}

bool Destroy(SSTable & ST)
{
	free(ST.elem);
	ST.elem = NULL;
	ST.length = 0;
	
	return true;
}

int Search_Seq(SSTable ST, KeyType key)
{
	int i;
	
	ST.elem[0].key = key;
	
	for(i = ST.length; !EQ(ST.elem[i].key,key); --i);
	
	return i;
}

int Search_Bin(SSTable ST, KeyType key)
{
	int low, high, mid;
	
	low = 1;
	high = ST.length;
	
	while(low <= high)
	{
		mid = (low + high) / 2;
		
		if EQ(key,ST.elem[mid].key)
		{
			return mid;
		}
		else if LT(key,ST.elem[mid].key)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
	
	return 0;
}

void Traverse(SSTable ST, void(*Visit)(ElemType))
{
	ElemType * p;
	int i;
	
	p = ++ST.elem;
	
	for(i = 1; i <= ST.length; ++i)
	{
		Visit(*p++);
	}
}

