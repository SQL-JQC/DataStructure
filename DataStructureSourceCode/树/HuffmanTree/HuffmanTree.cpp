# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>

typedef struct HTNode
{
	unsigned int weight;
	unsigned int parent;
	unsigned int lchild;
	unsigned int rchild;
} HTNode, * HuffmanTree;

typedef char ** HuffmanCode;

int min(HuffmanTree, int);
void select(HuffmanTree, int, int &, int &);
void HuffmanCoding(HuffmanTree &, HuffmanCode &, int *, int);
void HuffmanCoding1(HuffmanTree &, HuffmanCode &, int *, int);

int main(void)
{
	HuffmanTree HT;
	HuffmanCode HC;
	int * w;
	int n;
	int i;
	
	printf("请输入权值的个数(>1)：");
	scanf("%d", &n);
	
	w = (int *)malloc(sizeof(int) * n);
	
	printf("请依次输入%d个权值(整型)：\n", n);
	for(i = 0; i <= n-1; ++i)
	{
		scanf("%d", w + i);
	}
	
	HuffmanCoding(HT, HC, w, n);
//	HuffmanCoding1(HT, HC, w, n);
	
	for(i = 1; i <= n; ++i)
	{
		puts(HC[i]);
	}
	
	//手动释放内存 
	free(w);
	free(HT);
	for(i = 1; i <= n; ++i)
	{
		free(HC[i]);
	}
	free(HC);
	
	return 0;
}

int min(HuffmanTree t, int i)
{
	int j;
	int flag;
	unsigned int k = UINT_MAX;
	
	for(j = 1; j <= i; ++j)
	{
		if(t[j].weight < k && t[j].parent == 0)
		{
			k = t[j].weight;
			flag = j;
		}
	}
	
	t[flag].parent = 1;
	
	return flag;
}

void select(HuffmanTree t, int i, int & s1, int & s2)
{
	int j;
	
	s1 = min(t, i);
	s2 = min(t, i);
	
	if(s1 > s2)
	{
		j = s1;
		s1 = s2;
		s2 = j;
	}
}

void HuffmanCoding(HuffmanTree & HT, HuffmanCode & HC, int * w, int n)
{
	int m, i, s1, s2, start;
	unsigned int c, f;
	HuffmanTree p;
	char * cd;
	
	if(n <= 1)
	{
		return;
	}
	
	m = n + (n - 1);
	
	HT = (HuffmanTree)malloc(sizeof(HTNode) * (m + 1));
	
	for(p = HT + 1, i = 1; i <= n; ++i, ++p, ++w)
	{
		(*p).weight = *w;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	for(; i <= m; ++i, ++p)
	{
		(*p).parent = 0;
	}
	
	for(i = n + 1; i <= m; ++i)
	{
		select(HT, i-1, s1, s2);
		HT[s1].parent = HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	
	//开始逆向求每个字符的赫夫曼编码 
	HC = (HuffmanCode)malloc(sizeof(char *) * (n + 1));
	
	cd = (char *)malloc(sizeof(char) * n);
	cd[n-1] = '\0';
	
	for(i = 1; i <= n; ++i)
	{
		start = n - 1;
		for(c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
		{
			if(HT[f].lchild == c)
			{
				cd[--start] = '0';
			}
			else
			{
				cd[--start] = '1';
			}
		}
		
		HC[i] = (char *)malloc(sizeof(char) * (n - start));
		
		strcpy(HC[i], &cd[start]);
	}
	
	free(cd);
}

void HuffmanCoding1(HuffmanTree & HT, HuffmanCode & HC, int * w, int n)
{
	int m, i, s1, s2;
	unsigned int c, cdlen;
	HuffmanTree p;
	char * cd;
	
	if(n <= 1)
	{
		return;
	}
	
	m = n + (n - 1);
	
	HT = (HuffmanTree)malloc(sizeof(HTNode) * (m + 1));
	
	for(p = HT + 1, i = 1; i <= n; ++i, ++p, ++w)
	{
		(*p).weight = *w;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	for(; i <= m; ++i, ++p)
	{
		(*p).parent = 0;
	}
	
	for(i = n + 1; i <= m; ++i)
	{
		select(HT, i-1, s1, s2);
		HT[s1].parent = HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	
	//开始正向求每个字符的赫夫曼编码 
	HC = (HuffmanCode)malloc(sizeof(char *) * (n + 1));
	
	cd = (char *)malloc(sizeof(char) * n);
	
	c = m;
	cdlen = 0;
	
	for(i = 1; i <= m; ++i)
	{
		HT[i].weight = 0;
	}
	
	while(c)
	{
		if(HT[c].weight == 0)
		{
			HT[c].weight = 1;
			
			if(HT[c].lchild != 0)
			{
				c = HT[c].lchild;
				cd[cdlen++] = '0';
			}
			else if(HT[c].rchild == 0)
			{
				HC[c] = (char *)malloc(sizeof(char) * (cdlen + 1));
				cd[cdlen] = '\0';
				strcpy(HC[c], cd);
			}
		}
		else if(HT[c].weight == 1)
		{
			HT[c].weight = 2;
			
			if(HT[c].rchild != 0)
			{
				c = HT[c].rchild;
				cd[cdlen++] = '1';
			}
		}
		else
		{
			HT[c].weight = 0;
			
			c = HT[c].parent;
			--cdlen;
		}
	}
	
	free(cd);
}

