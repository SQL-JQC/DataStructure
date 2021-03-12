# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

typedef struct HString
{
	char * ch;
	int length;
} HString;

void InitStr(HString *);
void StrAssign(HString *, char *);
void StrPrint(HString *);
int StrLength(HString *);
bool StrEmpty(HString *);
void ClearString(HString *);
int Index_BF(HString *, HString *, int);
int Index_KMP(HString *, HString *, int);
void get_next(HString *, int *);
int Index_KMP_Improve(HString *, HString *, int);
void get_nextval(HString *, int *);

int main(void)
{
	HString S;
	HString T;
	
	char p[11] = {'H', 'e', 'l', 'l', 'o', 'W', 'o', 'r', 'l', 'd', '\0'};
	char q[4] = {'o', 'r', 'l', '\0'};
	
	//得到第一个串S（主串） 
	InitStr(&S);
	StrAssign(&S, p);
	StrPrint(&S);
	
	//得到第二个串T（子串）、（模式串） 
	InitStr(&T);
	StrAssign(&T, q);
	StrPrint(&T);
	
	//使用BF算法定位子串在主串中的位置 
	int pos = Index_BF(&S, &T, 3);
	printf("使用BF算法，位置是：%d\n", pos);
	
	//使用KMP算法定位子串在主串中的位置 
	int pos1 = Index_KMP(&S, &T, 3);
	printf("使用KMP算法，位置是：%d\n", pos1);

	//使用改进后的KMP算法定位子串在主串中的位置 
	int pos2 = Index_KMP_Improve(&S, &T, 3);
	printf("使用改进后的KMP算法，位置是：%d\n", pos2);

	ClearString(&S);
	ClearString(&T);
	
	return 0;
}

void InitStr(HString * S)
{
	S->ch = NULL;
	S->length = 0;
	
	return;
}

void StrAssign(HString * S, char * C)
{
	int i, j;
	
	if(S->ch)
	{
		free(S->ch);
	}
	
	char * c = C;
	for(i = 0; '\0' != c[i]; ++i);
	
	if(!i)
	{
		S->ch = NULL;
		S->length = 0;
	}
	else
	{
		S->ch = (char *)malloc(sizeof(char)*i);
		if(NULL == S->ch)
		{
			printf("动态内存分配失败！\n");
			exit(-1);
		}
		
		for(j = 0; j < i; ++j)
		{
			S->ch[j] = C[j];
		}
		S->length = i;
	}
	
	return;
}

void StrPrint(HString * S)
{
	int i;
	
	for(i = 0; i < S->length; ++i)
	{
		printf("%c", S->ch[i]);
	}
	printf("\n");
	
	return;
}

int StrLength(HString * S)
{
	return S->length;
}

bool StrEmpty(HString * S)
{
	if(S->length == 0 && S->ch == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ClearString(HString * S)
{
	free(S->ch);
	S->ch = NULL;
	S->length = 0;
	printf("堆 串的动态内存释放成功！\n");
	
	return;
}

int Index_BF(HString * S, HString * T, int pos)
{
	int i, j;
	
	if( StrEmpty(T) )
	{
		return 0;
	}
	if(pos < 1 || pos > StrLength(S))
	{
		return 0;
	}
	
	i = pos - 1;
	j = 0;
	
	while(i <= S->length - 1 && j <= T->length - 1)
	{
		if(S->ch[i] == T->ch[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	
	if(j > T->length - 1)
	{
		return i - (T->length - 1);
	}
	else
	{
		return 0;
	}
}

int Index_KMP(HString * S, HString * T, int pos)
{
	int i, j;
	int next[3];
	
	if( StrEmpty(T) )
	{
		return 0;
	}
	if(pos < 1 || pos > StrLength(S))
	{
		return 0;
	}
	
	i = pos - 1;
	j = 0;
	
	get_next(T, next);
	
	while(i <= S->length - 1 && j <= T->length - 1)
	{
		if(j == -1 || S->ch[i] == T->ch[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}
	
	if(j > T->length - 1)
	{
		return i - (T->length - 1);
	}
	else
	{
		return 0;
	}
}

void get_next(HString * T, int * next)
{
	int i = 0;
	int j = -1;
	next[0] = -1;
	
	while(i < T->length - 1)
	{
		if(j == -1 || T->ch[i] == T->ch[j])
		{
			i++;
			j++;
			next[i] = j;
		}
		else
		{
			j = next[j];
		}
	}
	
	return;
}


int Index_KMP_Improve(HString * S, HString * T, int pos)
{
	int i, j;
	int nextval[3];
	
	if( StrEmpty(T) )
	{
		return 0;
	}
	if(pos < 1 || pos > StrLength(S))
	{
		return 0;
	}
	
	i = pos - 1;
	j = 0;
	
	get_nextval(T, nextval);
	
	while(i <= S->length - 1 && j <= T->length - 1)
	{
		if(j == -1 || S->ch[i] == T->ch[j])
		{
			i++;
			j++;
		}
		else
		{
			j = nextval[j];
		}
	}
	
	if(j > T->length - 1)
	{
		return i - (T->length - 1);
	}
	else
	{
		return 0;
	}
}

void get_nextval(HString * T, int * nextval)
{
	int i = 0;
	int j = -1;
	nextval[0] = -1;
	
	while(i < T->length - 1)
	{
		if(j == -1 || T->ch[i] == T->ch[j])
		{
			i++;
			j++;
			if(T->ch[i] != T->ch[j])
			{
				nextval[i] = j;
			}
			else
			{
				nextval[i] = nextval[j];
			}
		}
		else
		{
			j = nextval[j];
		}
	}
	
	return;
}

