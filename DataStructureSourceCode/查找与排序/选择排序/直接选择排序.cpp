# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

# define MAX_SIZE 20
# define N 8

typedef int KeyType;
typedef int InfoType;

typedef struct RedType
{
	KeyType key;
	InfoType otherinfo;
} RedType;

typedef struct SqList
{
	RedType r[MAX_SIZE + 1];
	int length;
} SqList;

# define EQ(a,b) ((a)==(b))
# define LT(a,b) ((a)<(b))
# define LQ(a,b) ((a)<=(b))

void SelectSort(SqList &);

void print(SqList L)
{
	int i;
	
	for(i = 1; i <= L.length; ++i)
	{
		printf("(%d, %d) ", L.r[i].key, L.r[i].otherinfo);
	}
	printf("\n");
}

int main(void)
{
	SqList L;
	int i;
	RedType r[N] = {{49, 1}, {38, 2}, {65, 3}, {97, 4}, {76, 5}, {13, 6}, {27, 7}, {49, 8}};
	
	for(i = 0; i < N; ++i)
	{
		L.r[i + 1] = r[i];
	}
	L.length = N;
	
	print(L);
	SelectSort(L);
	print(L);
	
	return 0;
}

void SelectSort(SqList & L)
{
	int i, j, min;
	
	for(i = 1; i <= L.length - 1; ++i)
	{
		for(min = i, j = i + 1; j <= L.length; ++j)
		{
			if LT(L.r[j].key,L.r[min].key)
			{
				min = j;
			}
		}
		
		if(min != i)
		{
			L.r[0] = L.r[i];
			L.r[i] = L.r[min];
			L.r[min] = L.r[0];
		}
	}
}

