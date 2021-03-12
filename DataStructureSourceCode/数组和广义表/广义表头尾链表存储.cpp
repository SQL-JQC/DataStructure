# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

typedef struct HString
{
	char * ch;
	int length;
} HString;

typedef char AtomType;

typedef enum ElemTag
{
	ATOM, LIST
} ElemTag;

typedef struct GLNode
{
	ElemTag tag;
	union
	{
		AtomType atom;
		struct
		{
			struct GLNode * hp;
			struct GLNode * tp;
		} ptr;
	};
} GLNode, * GList;

void InitGList(GList &);
void CreateGList(GList &, HString *);
void sever(HString *, HString *);
void DestroyGList(GList &);
int GListLength(GList);
int GListDepth(GList);
bool GListEmpty(GList);
void Traverse_GL(GList, void(*v)(AtomType));
void visit(AtomType);
void CopyGList(GList &, GList);
GList GetHead(GList);
GList GetTail(GList);
void InsertFirst_GL(GList &, GList);
void DeleteFirst_GL(GList &, GList &);

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
	char a[16] = {'(', '(', 'a', ',', 'b', ')', ',', 'c', ',', '(', 'd', ',', 'e', ')', ')', '\0'};
		
	HString S;
	GList l, m;
	
	InitGList(l);
	InitGList(m);
	
	InitStr(&S);
	StrAssign(&S, a);
	
	CreateGList(l, &S);
	Traverse_GL(l, visit);
	
	int len = GListLength(l);
	int dep = GListDepth(l);
	printf("\n");
	printf("%d  %d\n", len, dep);
	
	CopyGList(m, l);
	Traverse_GL(m, visit);
	
	//之后关于广义表的操作不再测试了 
	
	DestroyGList(l);
	DestroyGList(m);	
	ClearString(&S);
	
	return 0;
}

void InitGList(GList &L)
{
	L = NULL;
	
	return;
}

void CreateGList(GList &L, HString * S)
{
	HString emp, sub, hsub;
	GList p, q;
	
	char e[3] = {'(', ')', '\0'};
	InitStr(&emp);
	InitStr(&sub);
	InitStr(&hsub);
	StrAssign(&emp, e);
	
	if(!StrCompare(S, &emp))
	{
		L = NULL;
	}
	else
	{
		L = (GList)malloc(sizeof(GLNode));
		if(L == NULL)
		{
			exit(-1);
		}
		
		if(StrLength(S) == 1)
		{
			L->tag = ATOM;
			L->atom = S->ch[0];
		}
		else
		{
			L->tag = LIST;
			
			p = L;
			
			SubString(&sub, S, 2, StrLength(S) - 2);
			do
			{
				sever(&sub, &hsub);
				CreateGList(p->ptr.hp, &hsub);
				
				q = p;
				if(!StrEmpty(&sub))
				{
					p = (GList)malloc(sizeof(GLNode));
					if(p == NULL)
					{
						exit(-1);
					}
					p->tag = LIST;
					q->ptr.tp = p;
				}
			} while(!StrEmpty(&sub));
			q->ptr.tp = NULL;
		}
	}
}

void sever(HString * sub, HString * hsub)
{
	int n, k, i;
	HString c1, c2, c3, ch;
	InitStr(&c1);
	InitStr(&c2);
	InitStr(&c3);
	InitStr(&ch);
	
	n = StrLength(sub);
	
	char a[2] = {',', '\0'};
	char b[2] = {'(', '\0'};
	char c[2] = {')', '\0'};
	StrAssign(&c1, a);
	StrAssign(&c2, b);
	StrAssign(&c3, c);
	SubString(&ch, sub, 1, 1);
	
	for(i = 1, k = 0; i <= n && StrCompare(&ch, &c1) || k != 0; ++i)
	{
		SubString(&ch, sub, i, 1);
		if(!StrCompare(&ch, &c2))
		{
			k++;
		}
		else if(!StrCompare(&ch, &c3))
		{
			k--;
		}
	}
	
	if(i <= n)
	{
		SubString(hsub, sub, 1, i-2);
		SubString(sub, sub, i, n-i+1);
	}
	else
	{
		StrCopy(hsub, sub);
		ClearString(sub);
	}
}

void DestroyGList(GList &L)
{
	GList q1, q2;
	
	if(L)
	{
		if(L->tag == LIST)
		{
			q1 = L->ptr.hp;
			q2 = L->ptr.tp;
			DestroyGList(q1);
			DestroyGList(q2);
		}
		free(L);
		L = NULL;
	}
}

int GListLength(GList L)
{
	int len = 0;
	
	while(L)
	{
		L = L->ptr.tp;
		len++;
	}
	
	return len;
}

int GListDepth(GList L)
{
	int max, dep;
	GList p;
	
	if(!L)
	{
		return 1;
	}
	
	if(L->tag == ATOM)
	{
		return 0;
	}
	
	for(max = 0, p = L; p; p = p->ptr.tp)
	{
		dep = GListDepth(p->ptr.hp);
		if(dep > max)
		{
			max = dep;
		}
	}
	
	return max + 1;
}

bool GListEmpty(GList L)
{
	if(!L)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Traverse_GL(GList L, void(*v)(AtomType))
{
	if(L)
	{
		if(L->tag == ATOM)
		{
			v(L->atom);
		}
		else
		{
			Traverse_GL(L->ptr.hp, v);
			Traverse_GL(L->ptr.tp, v);
		}
	}
}

void visit(AtomType e)
{
	printf("%c ", e);
}

void CopyGList(GList & T, GList L)
{
	if(!L)
	{
		T = NULL;
	}
	else
	{
		T = (GList)malloc(sizeof(GLNode));
		if(T == NULL)
		{
			exit(-1);
		}
		
		T->tag = L->tag;
		if(L->tag == ATOM)
		{
			T->atom = L->atom;
		}
		else
		{
			CopyGList(T->ptr.hp, L->ptr.hp);
			CopyGList(T->ptr.tp, L->ptr.tp);
		}
	}
}

GList GetHead(GList L)
{
	GList h, p;
	
	if(!L)
	{
		return NULL;
	}
	
	p = L->ptr.hp;
	CopyGList(h, p);
	
	return h;
}

GList GetTail(GList L)
{
	GList t;
	
	if(!L)
	{
		return NULL;
	}
	
	CopyGList(t, L->ptr.tp);
	
	return t;
}

void InsertFirst_GL(GList & L, GList e)
{
	GList p = (GList)malloc(sizeof(GLNode));
	if(p == NULL)
	{
		exit(-1);
	}
	
	p->tag = LIST;
	p->ptr.hp = e;
	p->ptr.tp = L;
	L = p;
	
	return;
}

void DeleteFirst_GL(GList & L, GList & e)
{
	GList p = L;
	e = L->ptr.hp;
	L = L->ptr.tp;
	free(p);
	
	return;
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
	
	return;
}






















