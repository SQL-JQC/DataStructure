# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

void InitList(LinkList &);
void DestroyList(LinkList &);
bool ListEmpty(LinkList);
int ListLength(LinkList);
int LocateElem(LinkList, ElemType, bool(*compare)(ElemType, ElemType));
bool ListInsert(LinkList &, int, ElemType);
bool ListDelete(LinkList &, int, ElemType &);
LinkList Point(LinkList, ElemType, bool(*equal)(ElemType, ElemType), LinkList &);
bool DeleteElem(LinkList &, ElemType &, bool(*equal)(ElemType, ElemType));

void InitList(LinkList & L)
{
	L = NULL;
}

void DestroyList(LinkList & L)
{
	LinkList p;
	
	while(L)
	{
		p = L;
		L = L->next;
		free(p);
	}
}

bool ListEmpty(LinkList L)
{
	if(L)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int ListLength(LinkList L)
{
	int i = 0;
	LinkList p = L;
	
	while(p)
	{
		i++;
		p = p->next;
	}
	
	return i;
}

int LocateElem(LinkList L, ElemType e, bool(*compare)(ElemType, ElemType))
{
	int i = 0;
	LinkList p = L;
	
	while(p)
	{
		i++;
		if(compare(p->e, e))
		{
			return i;
		}
		p = p->next;
	}
	
	return 0;
}

bool ListInsert(LinkList & L, int i, ElemType e)
{
	int j = 1;
	LinkList p = L;
	LinkList q;
	
	if(i < 1)
	{
		return false;
	}
	
	q = (LinkList)malloc(sizeof(LNode));
	q->e = e;
	
	if(i == 1)
	{
		q->next = L;
		L = q;
	}
	else
	{
		while(p && j < i - 1)
		{
			p = p->next;
			j++;
		}
		
		if(!p)
		{
			return false;
		}
		
		q->next = p->next;
		p->next = q;
	}
	
	return true;
}

bool ListDelete(LinkList & L, int i, ElemType & e)
{
	int j = 1;
	LinkList p = L;
	LinkList q;
	
	if(i == 1)
	{
		L = p->next;
		e = p->e;
		free(p);
	}
	else
	{
		while(p->next && j < i - 1)
		{
			p = p->next;
			j++;
		}
		
		if(!p->next || j > i - 1)
		{
			return false;
		}
		
		q = p->next;
		p->next = q->next;
		e = q->e;
		free(q);
	}
	
	return true;
}

LinkList Point(LinkList L, ElemType e, bool(*equal)(ElemType, ElemType), LinkList & p)
{
	int i, j;
	
	i = LocateElem(L, e, equal);
	
	if(i)
	{
		if(i == 1)
		{
			p = NULL;
			return L;
		}
		else
		{
			p = L;
			for(j = 2; j < i; ++j)
			{
				p = p->next;
			}
			return p->next;
		}
	}
	
	return NULL;
}

bool DeleteElem(LinkList & L, ElemType & e, bool(*equal)(ElemType, ElemType))
{
	LinkList p, q;
	
	q = Point(L, e, equal, p);
	
	if(q)
	{
		if(p)
		{
			ListDelete(p, 2, e);
		}
		else
		{
			ListDelete(L, 1, e);
		}
		
		return true;
	}
	
	return false;
}

