# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

# define MAX_SIZE 20
# define N 10
# define T 3

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

void printk(SqList);
void ShellInsert(SqList &, int);
void ShellSort(SqList &, int dlta[], int);

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
	RedType r[N] = {{49, 1}, {38, 2}, {65, 3}, {97, 4}, {76, 5}, {13, 6}, {27, 7}, {49, 8}, {55, 9}, {4, 10}};
	int dt[T] = {5, 3, 1};
	
	for(i = 0; i < N; ++i)
	{
		L.r[i + 1] = r[i];
	}
	L.length = N;
	
	print(L);
	ShellSort(L, dt, T);
	print(L); 
	
	return 0;
}

void printk(SqList L)
{
	int i;
	
	for(i = 1; i <= L.length; ++i)
	{
		printf("%d ", L.r[i].key);
	}
	printf("\n");
}

void ShellInsert(SqList & L, int dk)
{
	int i, j;
	
	for(i = dk + 1; i <= L.length; ++i)
	{
		if LT(L.r[i].key,L.r[i-dk].key)
		{
			L.r[0] = L.r[i];
			
			for(j = i - dk; j > 0 && LT(L.r[0].key,L.r[j].key); j -= dk)
			{
				L.r[j + dk] = L.r[j];
			}
			
			L.r[j + dk] = L.r[0];
		}
	}
}

void ShellSort(SqList & L, int dlta[], int t)
{
	int k;
	
	for(k = 0; k < t; ++k)
	{
		ShellInsert(L, dlta[k]);
		printf("µÚ%dÌËÅÅÐò½á¹û£º", k + 1);
		printk(L);
	}
}

