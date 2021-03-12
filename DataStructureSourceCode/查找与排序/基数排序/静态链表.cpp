# include <stdio.h>

# define MAXSIZE 100

typedef struct
{
	int data;
	int cur;
}component, SLL[MAXSIZE];

void init_list(SLL);
int malloc_S(SLL);
void free_S(SLL, int);
int create_list(SLL);
void traverse_list(SLL, int);
bool insert_list(SLL, int, int, int);
bool delete_list(SLL, int, int, int *);
int locate_list(SLL, int, int);

void init_list(SLL space)
{
	int i;
	
	for(i=0; i<MAXSIZE-1; ++i)
	{
		space[i].cur = i+1;
	}
	space[MAXSIZE-1].cur = 0;
}

int malloc_S(SLL space)
{
	int i;
	
	i = space[0].cur;
	if(space[0].cur)
	{
		space[0].cur = space[i].cur;
	}
	
	return i;
}

void free_S(SLL space, int k)
{
	space[k].cur = space[0].cur;
	space[0].cur = k;
	
	return;
}

int create_list(SLL space)
{
	int len;
	int i;
	int n;
	
	int S = malloc_S(space);
	int q = S;
	
	printf("请输入您要生成的结点的个数：");
	scanf("%d", &len);
	
	for(i=1; i<=len; ++i)
	{
		n = malloc_S(space);
		scanf("%d", &space[n].data);
		space[q].cur = n;
		q = n;
	}
	space[q].cur = 0;
	
	return S;
}

void traverse_list(SLL space, int S)
{
	int p = space[S].cur;
	
	printf("\n");
	while(0 != p)
	{
		printf("%d ", space[p].data);
		p = space[p].cur;
	}
	printf("\n");
	
	return;
}

bool insert_list(SLL space, int S, int pos, int val)
{
	int i = 0;
	int p = S;
	
	while(0!=p && i<pos-1)
	{
		p = space[p].cur;
		i++;
	}
	if(i>pos-1 || 0==p)
	{
		return false;
	}
	
	int n = malloc_S(space);
	if(n)
	{
		space[n].data = val;
		space[n].cur = space[p].cur;
		space[p].cur = n;
	}
	
	return true;
}

bool delete_list(SLL space, int S, int pos, int * pVal)
{
	int i = 0;
	int p = S;
	
	while(0!=space[p].cur && i<pos-1)
	{
		p = space[p].cur;
		i++;
	}
	if(i>pos-1 || 0==space[p].cur)
	{
		return false;
	}
	
	int q = space[p].cur;
	*pVal = space[q].data;
	space[p].cur = space[q].cur;
	free_S(space, q);
	
	return true;
}

int locate_list(SLL space, int S, int val)
{
	int locate = 1;
	int p = space[S].cur;
	
	while(p && val!=space[p].data)
	{
		p = space[p].cur;
		locate++;
	}
	if(0 == p)
	{
		return p;
	}
	else
	{
		return locate;
	}
}
