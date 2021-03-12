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

typedef SqList HeapType;

# define EQ(a,b) ((a)==(b))
# define LT(a,b) ((a)<(b))
# define LQ(a,b) ((a)<=(b))

void HeapAdjust(HeapType &, int, int);
void HeapSort(HeapType &);

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
	HeapType H;
	int i;
	RedType r[N] = {{49, 1}, {38, 2}, {65, 3}, {97, 4}, {76, 5}, {13, 6}, {27, 7}, {49, 8}};
	
	for(i = 0; i < N; ++i)
	{
		H.r[i + 1] = r[i];
	}
	H.length = N;
	
	print(H);
	HeapSort(H);
	print(H);
	
	return 0;
}

void HeapAdjust(HeapType & H, int s, int m)
{
	RedType rc;
	int j;
	
	rc = H.r[s];
	
	for(j = s * 2; j <= m; j *= 2)
	{
		if(j < m && LT(H.r[j].key,H.r[j+1].key))
		{
			++j;
		}
		
		if(!LT(rc.key,H.r[j].key))
		{
			break;
		}
		
		H.r[s] = H.r[j];
		
		s = j;
	}
	
	H.r[s] = rc;
}

void HeapSort(HeapType & H)
{
	RedType t;
	int i;
	
	for(i = H.length / 2; i > 0; --i)
	{
		HeapAdjust(H, i, H.length);
	}
	
	for(i = H.length; i > 1; --i)
	{
		t = H.r[1];
		H.r[1] = H.r[i];
		H.r[i] = t;
		
		HeapAdjust(H, 1, i - 1);
	}
}

