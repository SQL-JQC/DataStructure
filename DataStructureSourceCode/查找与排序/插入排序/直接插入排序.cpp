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

void InsertSort(SqList &);

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
	InsertSort(L);
	print(L);
	
	return 0;
}

void InsertSort(SqList & L)
{
	int i, j;
	
	for(i = 2; i <= L.length; ++i)
	{
		if LT(L.r[i].key,L.r[i-1].key)
		{
			L.r[0] = L.r[i];
			
			for(j = i - 1; LT(L.r[0].key,L.r[j].key); --j)
			{
				L.r[j + 1] = L.r[j];
			}
			
			L.r[j + 1] = L.r[0];
		}
	}
}

