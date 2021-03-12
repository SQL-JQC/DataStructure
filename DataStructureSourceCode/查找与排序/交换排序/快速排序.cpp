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

int Partition(SqList &, int, int);
void QSort(SqList &, int, int);
void QuickSort(SqList &);

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
	QuickSort(L);
	print(L);
	
	return 0;
}

int Partition(SqList & L, int low, int high)
{
	KeyType pivotkey;
	
	L.r[0] = L.r[low];
	pivotkey = L.r[low].key;
	
	while(low < high)
	{
		while(low < high && L.r[high].key >= pivotkey)
		{
			--high;
		}
		L.r[low] = L.r[high];
		
		while(low < high && L.r[low].key <= pivotkey)
		{
			++low;
		}
		L.r[high] = L.r[low];
	}
	
	L.r[low] = L.r[0];
	
	return low;
}

void QSort(SqList & L, int low, int high)
{
	int pos;
	
	if(low < high)
	{
		pos = Partition(L, low, high);
		QSort(L, low, pos-1);
		QSort(L, pos+1, high);
	}
}

void QuickSort(SqList & L)
{
	QSort(L, 1, L.length);
}

