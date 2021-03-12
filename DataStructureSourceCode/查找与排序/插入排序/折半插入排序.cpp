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

void BInsertSort(SqList &);

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
	BInsertSort(L);
	print(L);
	
	return 0;
}

void BInsertSort(SqList & L)
{
	int i, j;
	int low, high, mid;
	
	for(i = 2; i <= L.length; ++i)
	{
		L.r[0] = L.r[i];
		
		low = 1;
		high = i - 1;
		
		while(low <= high)
		{
			mid = (low + high) / 2;
			if LT(L.r[0].key,L.r[mid].key)
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}
		
		for(j = i - 1; j >= high + 1; --j)
		{
			L.r[j + 1] = L.r[j];
		}
		
		L.r[high + 1] = L.r[0];
	}
}

