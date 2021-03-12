# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

# define ElemType int

typedef struct OLNode
{
	int i, j;
	ElemType e;
	struct OLNode * right;
	struct OLNode * down;
} OLNode, * OList;

typedef struct CrossList
{
	OList * rHead;
	OList * cHead;
	int mu, nu, tu;
} CrossList;

void InitSMatrix(CrossList *);
void InitSMatrixList(CrossList *);
void InsertAscend(CrossList *, OList);
void CreateSMatrix(CrossList *);
void PrintSMatrix(CrossList *);
void PrintSMatrix1(CrossList *);
void DestroySMatrix(CrossList *);
void CopySMatrix(CrossList *, CrossList *);

int main(void)
{
	CrossList A;
	CrossList B;
	CrossList C;
	
	InitSMatrix(&A);
	InitSMatrix(&B);
	
	CreateSMatrix(&A);
	PrintSMatrix(&A);
	printf("\n");
	PrintSMatrix1(&A);
	
	CopySMatrix(&A, &B);
	printf("\n");
	PrintSMatrix1(&B);
		
	DestroySMatrix(&A);
	DestroySMatrix(&B);
		
	return 0;
}

void InitSMatrix(CrossList * M)
{
	M->rHead = NULL;
	M->cHead = NULL;
	M->mu = 0;
	M->nu = 0;
	M->tu = 0;
	
	return;
}

void InitSMatrixList(CrossList * M)
{
	int i;
	
	M->rHead = (OList *)malloc(sizeof(OList) * (M->mu+1));
	if(!M->rHead)
	{
		exit(-1);
	}
	
	M->cHead = (OList *)malloc(sizeof(OList) * (M->nu+1));
	if(!M->cHead)
	{
		exit(-1);
	}
	
	for(i = 1; i <= M->mu; ++i)
	{
		M->rHead[i] = NULL;
	}
	for(i = 1; i <= M->nu; ++i)
	{
		M->cHead[i] = NULL;
	}
}

void InsertAscend(CrossList * M, OList p)
{
	OList q;
	
	if(M->rHead == NULL || p == NULL)
	{
		return;
	}
	
	q = M->rHead[p->i];
	if(!q || p->j < q->j)
	{
		p->right = M->rHead[p->i];
		M->rHead[p->i] = p;
	}
	else
	{
		while(q->right && q->right->j < p->j)
		{
			q = q->right;
		}
		p->right = q->right;
		q->right = p;
	}
	
	q = M->cHead[p->j];
	if(!q || p->i < q->i)
	{
		p->down = M->cHead[p->j];
		M->cHead[p->j] = p;
	}
	else
	{
		while(q->down && q->down->i < p->i)
		{
			q = q->down;
		}
		p->down = q->down;
		q->down = p;
	}
	
	M->tu++;
}

void CreateSMatrix(CrossList * M)
{
	int i, k;
	OList p;
	
	if(M->rHead)
	{
		DestroySMatrix(M);
	}
	
	printf("请输入稀疏矩阵的行数，列数，非零元素个数：");
	scanf("%d,%d,%d", &M->mu, &M->nu, &i);
	
	InitSMatrixList(M);
	
	printf("请按任意次序输入%d个非零元素所在的行，列和元素值：\n", i);
	for(k = 0; k < i; ++k)
	{
		p = (OList)malloc(sizeof(OLNode));
		if(!p)
		{
			exit(-1);
		}
		
		scanf("%d,%d,%d", &p->i, &p->j, &p->e);
		InsertAscend(M, p);
	}
}

void PrintSMatrix(CrossList * M)
{
	int i, j;
	OList p;
	
	printf("%d行%d列%d个非零元素\n", M->mu, M->nu, M->tu);
	printf("请输入选择(1.按行输出 2.按列输出)：");
	scanf("%d", &i);
	
	switch(i)
	{
		case 1:
			for(j = 1; j <= M->mu; ++j)
			{
				p = M->rHead[j];
				while(p)
				{
					printf("%d行%d列值为%d\n", p->i, p->j, p->e);
					p = p->right;
				}
			}
			break;
		case 2:
			for(j = 1; j <= M->nu; ++j)
			{
				p = M->cHead[j];
				while(p)
				{
					printf("%d行%d列值为%d\n", p->i, p->j, p->e);
					p = p->down;
				}
			}
			break;
	}
}

void PrintSMatrix1(CrossList * M)
{
	int i, j;
	OList p;
	
	for(i = 1; i <= M->mu; ++i)
	{
		p = M->rHead[i];
		for(j = 1; j <= M->nu; ++j)
		{
			if(!p || p->j != j)
			{
				printf("%-3d", 0);
			}
			else
			{
				printf("%-3d", p->e);
				p = p->right;
			}
		}
		printf("\n");
	}
}

void DestroySMatrix(CrossList * M)
{
	int i;
	OList p, q;
	
	if(M->rHead == NULL)
	{
		return;
	}
	
	for(i = 1; i <= M->mu; ++i)
	{
		p = *(M->rHead + i);
		while(p)
		{
			q = p;
			p = p->right;
			free(q);
		}
	}
	free(M->rHead);
	free(M->cHead);
	
	InitSMatrix(M);	
}

void CopySMatrix(CrossList * M, CrossList * T)
{
	int i;
	OList p, q;
	
	if(T->rHead)
	{
		DestroySMatrix(T);
	}
	
	T->mu = M->mu;
	T->nu = M->nu;
	InitSMatrixList(T);
	
	for(i = 1; i <= M->mu; ++i)
	{
		p = M->rHead[i];
		while(p)
		{
			q = (OList)malloc(sizeof(OLNode));
			if(!q)
			{
				exit(-1);
			}
			
			*q = *p;
			InsertAscend(T, q);
			p = p->right;
		}
	}
}


























