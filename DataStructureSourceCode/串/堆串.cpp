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
int StrCompare(HString *, HString *);
bool StrEmpty(HString *);
void Concat(HString *, HString *, HString *);
bool SubString(HString *, HString *, int, int);
bool StrInsert(HString *, int, HString *);
bool StrDelete(HString *, int, int);
int Index(HString *, HString *, int);
bool Replace(HString *, HString *, HString *);
void StrCopy(HString *, HString *);
void ClearString(HString *);

int main(void)
{
	HString S, T, R, H, Z;
	char c;
	char p[10] = {'H', 'e', 'l', 'l', 'o', ' ', 'S', 't', 'r', '\0'};
	char q[9] = {'A', 'b', 's', 't', 'r', 'a', 'c', 't', '\0'};
	char a[4] = {'S', 't', 'r', '\0'};
	char b[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
	
	InitStr(&S);
	InitStr(&T);
	InitStr(&R);
	InitStr(&H);
	InitStr(&Z);
	
	StrAssign(&S, p);
	StrPrint(&S);
	StrAssign(&T, q);
	StrAssign(&R, a);
	StrAssign(&H, b);
	
	int i = StrCompare(&S, &H);
	if(i < 0)
		c = '<';
	else if(i == 0)
		c = '=';
	else
		c = '>';
	printf("串S %c 串H\n", c);
	
	Concat(&Z, &H, &R);
	StrPrint(&Z);
	
	SubString(&Z, &T, 4, 4);
	StrPrint(&Z);
	
	StrInsert(&Z, 4, &H);
	StrPrint(&Z);
	
	StrDelete(&Z, 4, 5);
	StrPrint(&Z);
	
	int pos = Index(&S, &R, 2);
	printf("%d\n", pos);
	
	StrAssign(&Z, p);
	Replace(&Z, &R, &H);
	StrPrint(&Z);
	
	StrCopy(&Z, &T);
	StrPrint(&Z);
	
	ClearString(&S);
	ClearString(&T);
	ClearString(&R);
	ClearString(&H);
	ClearString(&Z);
	
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

int StrCompare(HString * S, HString * H)
{
	int i;
	
	for(i = 0; i < S->length && i < H->length; ++i)
	{
		if(S->ch[i] != H->ch[i])
		{
			return S->ch[i] - H->ch[i];
		}
	}
	
	return S->length - H->length;
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

void Concat(HString * Z, HString * H, HString * R)
{
	int i;
	
	if(Z->ch)
	{
		free(Z->ch);
	}
	
	Z->ch = (char *)malloc(sizeof(char)*(H->length + R->length));
	if(NULL == Z->ch)
	{
		printf("动态内存分配失败！\n");
		exit(-1);
	}
	
	for(i = 0; i < H->length; ++i)
	{
		Z->ch[i] = H->ch[i];
	}
	for(i = 0; i < R->length; ++i)
	{
		Z->ch[H->length+i] = R->ch[i];
	}
	Z->length = H->length + R->length;
	
	return;
}

bool SubString(HString * Z, HString * T, int pos, int len)
{
	int i;
	
	if(pos < 1 || pos > T->length || len < 0 || len > T->length-pos+1)
	{
		return false;
	}
	
	if(Z->ch)
	{
		free(Z->ch);
	}
	
	if(0 == len)
	{
		Z->ch = NULL;
		Z->length = 0;
	}
	else
	{
		Z->ch = (char *)malloc(sizeof(char)*len);
		if(NULL == Z->ch)
		{
			printf("动态内存分配失败！\n");
			exit(-1);
		}
		
		for(i = 0; i < len; ++i)
		{
			Z->ch[i] = T->ch[pos-1+i];
		}
		Z->length = len;
	}
	
	return true;
}

bool StrInsert(HString * Z, int pos, HString * H)
{
	int i;
	
	if(pos < 1 || pos > Z->length+1)
	{
		return false;
	}
	
	if(H->length)
	{
		Z->ch = (char *)realloc(Z->ch, sizeof(char)*(Z->length + H->length));
		if(NULL == Z->ch)
		{
			printf("动态内存分配失败！\n");
			exit(-1);
		}
		
		for(i = Z->length-1; i >= pos-1; --i)
		{
			Z->ch[i+H->length] = Z->ch[i];
		}
		for(i = 0; i < H->length; ++i)
		{
			Z->ch[pos-1+i] = H->ch[i];
		}
		Z->length += H->length;
	}
	
	return true;
}

bool StrDelete(HString * Z, int pos, int len)
{
	int i;
	
	if(Z->length < pos+len-1)
	{
		return false;
	}
	
	for(i = pos-1; i < Z->length-len; ++i)
	{
		Z->ch[i] = Z->ch[i+len];
	}
	Z->length -= len;
	
	Z->ch = (char *)realloc(Z->ch, sizeof(char)*(Z->length));
	
	return true;
}

int Index(HString * S, HString * R, int pos)
{
	int n, m, i;
	HString sub;
	InitStr(&sub);
	
	if(pos > 0)
	{
		n = StrLength(S);
		m = StrLength(R);
		i = pos;
		
		while(i <= n-m+1)
		{
			SubString(&sub, S, i, m);
			
			if(0 != StrCompare(&sub, R))
			{
				i++;
			}
			else
			{
				return i;
			}
		}
	}
	
	return 0;
}

bool Replace(HString * Z, HString * R, HString * H)
{
	int i = 1;
	
	if(StrEmpty(R))
	{
		return false;
	}
	
	do
	{
		i = Index(Z, R, i);
		
		if(i)
		{
			StrDelete(Z, i, StrLength(R));
			StrInsert(Z, i, H);
			i += StrLength(H);
		}
	} while(i);
	
	return true;
}

void StrCopy(HString * Z, HString * T)
{
	int i;
	
	if(Z->ch)
	{
		free(Z->ch);
	}
	
	Z->ch = (char *)malloc(sizeof(char)*(T->length));
	if(NULL == Z->ch)
	{
		printf("动态内存分配失败！\n");
		exit(-1);
	}
	
	for(i = 0; i < T->length; ++i)
	{
		Z->ch[i] = T->ch[i];
	}
	Z->length = T->length;
	
	return;
}

void ClearString(HString * S)
{
	free(S->ch);
	S->ch = NULL;
	S->length = 0;
	printf("堆 串的动态内存释放成功！\n");
	
	return;
}
