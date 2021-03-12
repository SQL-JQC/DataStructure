# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <string.h>

# define CHUNKSIZE 5
char blank = '#';

typedef struct Chunk
{
	char ch[CHUNKSIZE];
	struct Chunk * pNext;
} Chunk;

typedef struct LString
{
	Chunk * pHead;
	Chunk * pTail;
	int curlen;
} LString;

void InitString(LString *);
bool StrAssign(LString *, char *);
void StrPrint(LString *);
int StrLength(LString *);
bool StrEmpty(LString *);
bool ToChars(LString *, char *);
bool StrCopy(LString *, LString *);
int StrCompare(LString *, LString *);
bool Concat(LString *, LString *, LString *);
bool SubString(LString *, LString *, int, int);
int Index(LString *, LString *, int);
bool StrInsert(LString *, int, LString *);
void ClearString(LString *);
bool StrDelete(LString *, int, int);
bool Replace(LString *, LString *, LString *);

int main(void)
{
	LString S, T, R, H, Z, Y;
	char p[10] = {'H', 'e', 'l', 'l', 'o', ' ', 'S', 't', 'r', '\0'};
	char a[4] = {'S', 't', 'r', '\0'};
	char b[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
	
	InitString(&S);
	InitString(&Z);
	InitString(&T);
	InitString(&R);
	InitString(&H);
	InitString(&Y);
	
	StrAssign(&S, p);
	StrAssign(&T, b);
	StrAssign(&Y, a);
	StrPrint(&S);
	
	StrCopy(&Z, &S);
	StrPrint(&Z);
	
	int i = StrCompare(&S, &T);
	printf("%d\n", i);
	
	Concat(&R, &S, &T);
	StrPrint(&R);
	
	SubString(&H, &S, 7, 3);
	StrPrint(&H);
	
	int index = Index(&S, &Y, 2);
	printf("%d\n", index);
	
	StrInsert(&S, 10, &Y);
	StrPrint(&S);
	
	StrDelete(&S, 6, 1);
	StrPrint(&S);
	
	Replace(&S, &Y, &T);
	StrPrint(&S);
	
	ClearString(&S);
	ClearString(&T);
	ClearString(&R);
	ClearString(&H);
	ClearString(&Z);
	ClearString(&Y);
	
	return 0;
}

void InitString(LString * S)
{
	S->curlen = 0;
	S->pHead = NULL;
	S->pTail = NULL;
	
	return;
}

bool StrAssign(LString * S, char * C)
{
	int i, j, k, m, n;
	Chunk * p;
	Chunk * q;
	
	for(i = 0; '\0' != C[i]; ++i);
	
	if(!i)
	{
		return false;
	}
	
	S->curlen = i;
	j = i/CHUNKSIZE;
	if(i%CHUNKSIZE)
	{
		j++;
	}
	
	n = 0;
	for(k = 0; k < j; ++k)
	{
		p = (Chunk *)malloc(sizeof(Chunk));
		if(NULL == p)
		{
			printf("动态内存分配失败！\n");
			exit(-1);
		}
		
		for(m = 0; m < CHUNKSIZE && '\0' != C[n]; ++m)
		{
			p->ch[m] = C[n];
			n++;
		}
		
		if(k == 0)
		{
			S->pHead = p;
			q = p;
		}
		else
		{
			q->pNext = p;
			q = p;
		}
		
		if('\0' == C[n])
		{
			S->pTail = q;
			q->pNext = NULL;
			for(;m < CHUNKSIZE; ++m)
			{
				q->ch[m] = blank;
			}
		}
	}
	
	return true;
}

void StrPrint(LString * S)
{
	int i = 0;
	int j;
	Chunk * p = S->pHead;
	
	printf("\n");
	while(i < S->curlen)
	{
		for(j = 0; j < CHUNKSIZE; ++j)
		{
			if(p->ch[j] != blank)
			{
				printf("%c", p->ch[j]);
				i++;
			}
		}
		p = p->pNext;
	}
	printf("\n");
	
	return;
}

int StrLength(LString * S)
{
	return S->curlen;
}

bool StrEmpty(LString * S)
{
	if(0 == S->curlen)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ToChars(LString * S, char * C)
{
	Chunk * p = S->pHead;
	int i;
	int j = 0;
	
//	if(0 == S->curlen)
//	{
//		return false;
//	}
	
//	C = (char *)malloc(sizeof(char)*(S->curlen+1));
//	if(NULL == C)
//	{
//		printf("动态内存分配失败！\n");
//		exit(-1);
//	}
	
	while(p)
	{
		for(i = 0; i < CHUNKSIZE; ++i)
		{
			if(p->ch[i] != blank)
			{
				C[j] = p->ch[i];
				j++;
			}
		}
		p = p->pNext;
	}
	C[j] = '\0';
	
	return true;
}

bool StrCopy(LString * Z, LString * S)
{
	if(0 == S->curlen)
	{
		return false;
	}
	
	char C[S->curlen+1];
	bool tf;
	
	if( !ToChars(S, C) )
	{
		return false;
	}
	
	tf = StrAssign(Z, C);
	
	return tf;
}

int StrCompare(LString * S, LString * T)
{
	char C[S->curlen+1];
	char D[T->curlen+1];
	
	ToChars(S, C);
	ToChars(T, D);
	
	int i = strcmp(C, D);
	
	return i;
}

bool Concat(LString * R, LString * S, LString * T)
{
	LString s, t;
	bool tf1, tf2;
	
	InitString(&s);
	InitString(&t);
	
	tf1 = StrCopy(&s, S);
	tf2 = StrCopy(&t, T);
	if(!tf1 || !tf2)
	{
		return false;
	}
	
	R->curlen = S->curlen + T->curlen;
	R->pHead = s.pHead;
	s.pTail->pNext = t.pHead;
	R->pTail = t.pTail;
	
	return true;
}

bool SubString(LString * H, LString * S, int pos, int len)
{
	int i;
	
	char b[len+1];
	if(0 == S->curlen)
	{
		return false;
	}
	char c[S->curlen+1];
	
	bool tf;
	
	if(pos < 1 || pos > S->curlen || len < 0 || len > S->curlen-pos+1)
	{
		return false;
	}
	
	if( !ToChars(S, c) )
	{
		return false;
	}
	
	for(i = 0; i < len+1; ++i)
	{
		b[i] = c[pos-1+i];
	}
	
	tf = StrAssign(H, b);
	
	return tf;
}

int Index(LString * S, LString * Y, int pos)
{
	int i, n, m;
	LString sub;
	
	if(pos >= 1 && pos <= StrLength(S))
	{
		n = StrLength(S);
		m = StrLength(Y);
		i = pos;
		
		while(i <= n-m+1)
		{
			SubString(&sub, S, i, m);
			
			if( StrCompare(&sub, Y) )
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

bool StrInsert(LString * S, int pos, LString * Y)
{
	char c[S->curlen + Y->curlen + 1];
	char b[Y->curlen+1];
	int i, j;
	bool tf;
	
	if(pos < 1 || pos > S->curlen+1)
	{
		return false;
	}
	
	if( !ToChars(S, c) )
	{
		return false;
	}
	if( !ToChars(Y, b) )
	{
		return false;
	}
	
	for(i = S->curlen; i >= pos-1; --i)
	{
		c[i+Y->curlen] = c[i];
	}
	
	for(j = 0; j < Y->curlen; ++j)
	{
		c[pos-1+j] = b[j];
	}
	
	ClearString(S);
	tf = StrAssign(S, c);
	
	return tf;
}

bool StrDelete(LString * S, int pos, int len)
{
	char c[S->curlen+1];
	char b[S->curlen-len+1];
	int i, j;
	bool tf;
	
	if(pos < 1 || pos > S->curlen-len+1 || len < 0)
	{
		return false;
	}
	
	if( !ToChars(S, c) )
	{
		return false;
	}
	
	for(i = pos+len-1; i <= S->curlen; ++i)
	{
		c[i-len] = c[i];
	}
	
	for(j = 0; j < S->curlen-len+1; ++j)
	{
		b[j] = c[j];
	}
	
	ClearString(S);
	tf = StrAssign(S, b);
	
	return tf;
}

bool Replace(LString * S, LString * Y, LString * T)
{
	int i = 1;
	
	if( StrEmpty(Y) )
	{
		return false;
	}
	
	do
	{
		i = Index(S, Y, i);
		
		if(i)
		{
			StrDelete(S, i, StrLength(Y));
			StrInsert(S, i, T);
			i += StrLength(T);
		}
	} while(i);
	
	return true;
}

void ClearString(LString * S)
{
	Chunk * p = S->pHead;
	Chunk * q;
	
	while(p)
	{
		q = p->pNext;
		free(p);
		p = q;
	}
	S->pHead = NULL;
	S->pTail = NULL;
	S->curlen = 0;
	printf("块链 串释放成功！\n");
	
	return;
}

