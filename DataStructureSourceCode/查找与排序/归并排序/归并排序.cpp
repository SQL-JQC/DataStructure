# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

# define MAX_SIZE 20
# define N 7

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

void Merge(RedType SR[], RedType TR[], int, int, int);
void MSort(RedType SR[], RedType TR1[], int, int);
void MergeSort(SqList &);

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
	RedType r[N] = {{49, 1}, {38, 2}, {65, 3}, {97, 4}, {76, 5}, {13, 6}, {27, 7}};
	
	for(i = 0; i < N; ++i)
	{
		L.r[i + 1] = r[i];
	}
	L.length = N;
	
	print(L);
	MergeSort(L);
	print(L);
	
	return 0;
}

void Merge(RedType SR[], RedType TR[], int i, int m, int n)
{
	int j, k, l;
	
	for(j = m + 1, k = i; i <= m && j <= n; ++k)
	{
		if LQ(SR[i].key,SR[j].key)
		{
			TR[k] = SR[i++];
		}
		else
		{
			TR[k] = SR[j++];
		}
	}
	
	if(i <= m)
	{
		for(l = 0; l <= m - i; ++l)
		{
			TR[k + l] = SR[i + l];
		}
	}
	if(j <= n)
	{
		for(l = 0; l <= n - j; ++l)
		{
			TR[k + l] = SR[j + l];
		}
	}
}

void MSort(RedType SR[], RedType TR1[], int s, int t)
{
	int m;
	RedType TR2[MAX_SIZE + 1];
	
	if(s == t)
	{
		TR1[s] = SR[s];
	}
	else
	{
		m = (s + t) / 2;
		
		MSort(SR, TR2, s, m);
		MSort(SR, TR2, m+1, t);
		Merge(TR2, TR1, s, m, t);
	}
}

void MergeSort(SqList & L)
{
	MSort(L.r, L.r, 1, L.length);
}

