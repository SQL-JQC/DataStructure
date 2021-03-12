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

void BubbleSort(SqList &);

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
	BubbleSort(L);
	print(L);
	
	return 0;
}

void BubbleSort(SqList & L)
{
	int i, j;
	bool change;
	
	for(i = 1, change = true; i <= L.length - 1 && change; ++i)
	{
		change = false;
		
		for(j = 1; j <= L.length - i; ++j)
		{
			if LT(L.r[j+1].key,L.r[j].key)
			{
				L.r[0] = L.r[j];
				L.r[j] = L.r[j + 1];
				L.r[j + 1] = L.r[0];
				change = true;
			}
		}
	}
}

