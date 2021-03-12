# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

int LocateElem(LinkList, ElemType, bool(*compare)(ElemType, ElemType));
bool ListDelete(LinkList &, int, ElemType &);

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

