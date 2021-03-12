# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

# define ElemType int
# define MAX_SIZE 100

typedef struct Triple
{
	int i;
	int j;
	ElemType e;
} Triple;

typedef struct TSMatrix
{
	Triple data[MAX_SIZE + 1];
	int mu, nu, tu;
} TSMatrix;

void CreateSMatrix(TSMatrix *);
void DestroySMatrix(TSMatrix *);
void PrintSMatrix(TSMatrix *);
void PrintSMatrix1(TSMatrix *);
void CopySMatrix(TSMatrix *, TSMatrix *);
void AddSMatrix(TSMatrix *, TSMatrix *, TSMatrix *);
int comp(int, int);
void SubtSMatrix(TSMatrix *, TSMatrix *, TSMatrix *);
void TransposeSMatrix(TSMatrix *, TSMatrix *);
void MultSMatrix(TSMatrix *, TSMatrix *, TSMatrix *);

int main(void)
{
	TSMatrix A;
	TSMatrix B;
	TSMatrix C;
	
	CreateSMatrix(&A);
	PrintSMatrix(&A);
	PrintSMatrix1(&A);
	
//	CopySMatrix(&A, &B);
//	PrintSMatrix(&B);
//	DestroySMatrix(&B);
	
	CreateSMatrix(&B);
	PrintSMatrix1(&B);
	
	AddSMatrix(&A, &B, &C);
	printf("矩阵相加而得出的矩阵C为：\n");
	PrintSMatrix1(&C);
	DestroySMatrix(&C);
	
	SubtSMatrix(&A, &B, &C);
	printf("矩阵相减而得出的矩阵C为：\n");
	PrintSMatrix1(&C);
	DestroySMatrix(&C);
	
	TransposeSMatrix(&A, &C);
	printf("矩阵A转置后的矩阵C为：\n");
	PrintSMatrix1(&C);
	DestroySMatrix(&C);
	
	MultSMatrix(&A, &B, &C);
	printf("矩阵A与矩阵B相乘后的矩阵C为：\n");
	PrintSMatrix1(&C);
	DestroySMatrix(&C);
	
	DestroySMatrix(&A);
	DestroySMatrix(&B);
	
	return 0;
}

void CreateSMatrix(TSMatrix * M)
{
	int i;
	int m, n;
	ElemType e;
	int k;
	
	printf("请输入矩阵的行数，列数，非零元素数：");
	scanf("%d,%d,%d", &M->mu, &M->nu, &M->tu);
	if(M->tu > MAX_SIZE)
	{
		return;
	}
	
	M->data[0].i = 0;
	for(i = 1; i <= M->tu; ++i)
	{
		do
		{
			printf("请按行序顺序输入第%d个非零元素所在的行(1~%d)，列(1~%d)，元素值：", i, M->mu, M->nu);
			scanf("%d,%d,%d", &m, &n, &e);
			k = 0;
			
			if(m < 1 || m > M->mu || n < 1 || n > M->nu)
			{
				k = 1;
			}
			if(m < M->data[i-1].i || m == M->data[i-1].i && n <= M->data[i-1].j)
			{
				k = 1;
			}
		} while(k);
		
		M->data[i].i = m;
		M->data[i].j = n;
		M->data[i].e = e;
	}
	
	return;
}

void DestroySMatrix(TSMatrix * M)
{
	M->mu = 0;
	M->nu = 0;
	M->tu = 0;
	
	return;
}

void PrintSMatrix(TSMatrix * M)
{
	int i;
	
	printf("%d行%d列%d个非零元素。\n", M->mu, M->nu, M->tu);
	printf("行  列  元素值\n");
	for(i = 1; i <= M->tu; ++i)
	{
		printf("%2d%4d%8d\n", M->data[i].i, M->data[i].j, M->data[i].e);
	}
	
	return;
}

void PrintSMatrix1(TSMatrix * M)
{
	int i, j;
	int k = 1;
	Triple * p = M->data;
	
	p++;
	for(i = 1; i <= M->mu; ++i)
	{
		for(j = 1; j <= M->nu; ++j)
		{
			if(k <= M->tu && p->i == i && p->j == j)
			{
				printf("%3d", p->e);
				p++;
				k++;
			}
			else
			{
				printf("%3d", 0);
			}
		}
		printf("\n");
	}
	
	return;
}

void CopySMatrix(TSMatrix * M, TSMatrix * T)
{
	*T = *M;
	
	return;
}

int comp(int c1, int c2)
{
	if(c1 < c2)
	{
		return -1;
	}
	else if(c1 == c2)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void AddSMatrix(TSMatrix * M, TSMatrix * N, TSMatrix * Q)
{
	int m = 1;
	int n = 1;
	int q = 0;
	
	if(M->mu != N->mu || M->nu != N->nu)
	{
		return;
	}
	
	Q->mu = M->mu;
	Q->nu = M->nu;
	
	while(m <= M->tu && n <= N->tu)
	{
		switch(comp(M->data[m].i, N->data[n].i))
		{
			case -1:
				Q->data[++q] = M->data[m++];
				break;
			case 0:
				switch(comp(M->data[m].j, N->data[n].j))
				{
					case -1:
						Q->data[++q] = M->data[m++];
						break;
					case 0:
						Q->data[++q] = M->data[m++];
						Q->data[q].e += N->data[n++].e;
						if(Q->data[q].e == 0)
						{
							q--;
						}
						break;
					case 1:
						Q->data[++q] = N->data[n++];
						break;
				}
				break;
			case 1:
				Q->data[++q] = N->data[n++];
				break;
		}
	}
	
	while(m <= M->tu)
	{
		Q->data[++q] = M->data[m++];
	}
	while(n <= N->tu)
	{
		Q->data[++q] = N->data[n++];
	}
	
	Q->tu = q;
	
	if(q > MAX_SIZE)
	{
		return;
	}
	
	return;
}

void SubtSMatrix(TSMatrix * M, TSMatrix * N, TSMatrix * Q)
{
	int i;
	TSMatrix T = *N;
	
	for(i = 1; i <= T.tu; ++i)
	{
		T.data[i].e *= -1;
	}
	
	AddSMatrix(M, &T, Q);
	
	DestroySMatrix(&T);
	
	return;
}

void TransposeSMatrix(TSMatrix * M, TSMatrix * T)
{
	int p, q, col;
	
	T->mu = M->nu;
	T->nu = M->mu;
	T->tu = M->tu;
	
	if(T->tu)
	{
		q = 1;
		for(col = 1; col <= M->nu; ++col)
		{
			for(p = 1; p <= M->tu; ++p)
			{
				if(M->data[p].j == col)
				{
					T->data[q].i = M->data[p].j;
					T->data[q].j = M->data[p].i;
					T->data[q].e = M->data[p].e;
					++q;
				}
			}
		}
	}
	
	return;
}

void MultSMatrix(TSMatrix * M, TSMatrix * N, TSMatrix * Q)
{
	int i, j;
	ElemType * Nc, * Tc;
	TSMatrix T;
	
	if(M->nu != N->mu)
	{
		return;
	}
	
	T.mu = N->nu;
	T.nu = M->mu;
	T.tu = 0;
	Nc = (ElemType *)malloc(sizeof(ElemType) * (N->mu + 1));
	Tc = (ElemType *)malloc(sizeof(ElemType) * (M->nu + 1));
	if(!Nc || !Tc)
	{
		exit(-1);
	}
	
	for(i = 1; i <= N->nu; ++i)
	{
		for(j = 1; j <= N->mu; ++j)
		{
			Nc[j] = 0;
		}
		
		for(j = 1; j <= M->mu; ++j)
		{
			Tc[j] = 0;
		}
		
		for(j = 1; j <= N->tu; ++j)
		{
			if(N->data[j].j == i)
			{
				Nc[N->data[j].i] = N->data[j].e;
			}
		}
		
		for(j = 1; j <= M->tu; ++j)
		{
			Tc[M->data[j].i] += M->data[j].e * Nc[M->data[j].j];
		}
		
		for(j = 1; j <= M->mu; ++j)
		{
			if(Tc[j] != 0)
			{
				T.data[++T.tu].e = Tc[j];
				T.data[T.tu].i = i;
				T.data[T.tu].j = j;
			}
		}
	}
	
	if(T.tu > MAX_SIZE)
	{
		return;
	}
	
	TransposeSMatrix(&T, Q);
	
	DestroySMatrix(&T);
	free(Nc);
	free(Tc);
	
	return;
}

