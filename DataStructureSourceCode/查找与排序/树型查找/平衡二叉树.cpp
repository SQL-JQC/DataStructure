# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

# define N 10

typedef int KeyType;

typedef struct ElemType
{
	KeyType key;
	int order;
} ElemType;

typedef struct BSTNode
{
	ElemType data;
	int bf;
	struct BSTNode * lchild;
	struct BSTNode * rchild;
} BSTNode, * BSTree;

# define EQ(a,b) ((a)==(b))
# define LT(a,b) ((a)<(b))
# define LQ(a,b) ((a)<=(b))

void InitBST(BSTree &);
BSTree SearchBST(BSTree, KeyType);
void R_Rotate(BSTree &);
void L_Rotate(BSTree &);
void LeftBalance(BSTree &);
void RightBalance(BSTree &);
bool InsertAVL(BSTree &, ElemType, bool &);
bool DeleteAVL(BSTree &, KeyType, bool &);
void DestroyBST(BSTree &);
void TraverseBST(BSTree, void(*Visit)(ElemType));
void PreOrderTraverse(BSTree, void(*Visit)(ElemType));

void print(ElemType e)
{
	printf("(%d,%d) ", e.key, e.order);
}

int main(void)
{
	BSTree T;
	BSTree p;
	bool taller, shorter;
	int i;
	ElemType e[N] = {{3, 1}, {2, 2}, {1, 3}, {7, 4}, {5, 5}, {10, 6}, {4, 7}, {9, 8}, {8, 9}, {6, 10}};
	
//	InitBST(T);
//	for(i = 0; i < N; ++i)
//	{
//		InsertAVL(T, e[i], taller);
//	}
//	TraverseBST(T, print);
//	printf("\n");
//	PreOrderTraverse(T, print);
	
//	p = SearchBST(T, 4);
//	printf("\n(%d, %d)\n", p->data.key, p->data.order);
	
//	DeleteAVL(T, 10, shorter);
//	printf("\n");
//	TraverseBST(T, print);
//	printf("\n");
//	PreOrderTraverse(T, print);
	
	DestroyBST(T);
	
	return 0;
}

void InitBST(BSTree & T)
{
	T = NULL;
}

BSTree SearchBST(BSTree T, KeyType key)
{
	if(!T || EQ(key,T->data.key))
	{
		return T;
	}
	else if LT(key,T->data.key)
	{
		return SearchBST(T->lchild, key);
	}
	else
	{
		return SearchBST(T->rchild, key);
	}
}

void R_Rotate(BSTree & p)
{
	BSTree lc;
	
	lc = p->lchild;
	
	p->lchild = lc->rchild;
	lc->rchild = p;
	p = lc;
}

void L_Rotate(BSTree & p)
{
	BSTree rc;
	
	rc = p->rchild;
	
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
}

# define LH +1
# define EH 0
# define RH -1

void LeftBalance(BSTree & T)
{
	BSTree lc, rd;
	
	lc = T->lchild;
	
	switch(lc->bf)
	{
		case LH:
			T->bf = lc->bf = EH;
			R_Rotate(T);
			break;
		case RH:
			rd = lc->rchild;
			
			switch(rd->bf)
			{
				case LH:
					T->bf = RH;
					lc->bf = EH;
					break;
				case EH:
					T->bf = lc->bf = EH;
					break;
				case RH:
					T->bf = EH;
					lc->bf = LH;
					break;
			}
			rd->bf = EH;
			
			L_Rotate(T->lchild);
			R_Rotate(T);
			break;
		case EH:  //这种情况只有在平衡二叉树删除的操作中可能会出现，而插入的操作中不会出现此情况 
			T->bf = LH;
			lc->bf = RH;
			R_Rotate(T);
			break;
	}
}

void RightBalance(BSTree & T)
{
	BSTree rc, ld;
	
	rc = T->rchild;
	
	switch(rc->bf)
	{
		case RH:
			T->bf = rc->bf = EH;
			L_Rotate(T);
			break;
		case LH:
			ld = rc->lchild;
			
			switch(ld->bf)
			{
				case RH:
					T->bf = LH;
					rc->bf = EH;
					break;
				case EH:
					T->bf = rc->bf = EH;
					break;
				case LH:
					T->bf = EH;
					rc->bf = RH;
					break;
			}
			ld->bf = EH;
			
			R_Rotate(T->rchild);
			L_Rotate(T);
			break;
		case EH:  //这种情况只有在平衡二叉树删除的操作中可能会出现，而插入的操作中不会出现此情况 
			T->bf = RH;
			rc->bf = LH;
			L_Rotate(T);
			break;
	}
}

bool InsertAVL(BSTree & T, ElemType e, bool & taller)
{
	if(!T)
	{
		T = (BSTree)malloc(sizeof(BSTNode));
		T->data = e;
		T->lchild = NULL;
		T->rchild = NULL;
		T->bf = EH;
		taller = true;
	}
	else
	{
		if EQ(e.key,T->data.key)
		{
			taller = false;
			return false;
		}
		
		if LT(e.key,T->data.key)
		{
			if(!InsertAVL(T->lchild, e, taller))
			{
				return false;
			}
			
			if(taller)
			{
				switch(T->bf)
				{
					case LH:
						LeftBalance(T);
						taller = false;
						break;
					case EH:
						T->bf = LH;
						taller = true;
						break;
					case RH:
						T->bf = EH;
						taller = false;
						break;
				}
			}
		}
		else
		{
			if(!InsertAVL(T->rchild, e, taller))
			{
				return false;
			}
			
			if(taller)
			{
				switch(T->bf)
				{
					case LH:
						T->bf = EH;
						taller = false;
						break;
					case EH:
						T->bf = RH;
						taller = true;
						break;
					case RH:
						RightBalance(T);
						taller = false;
						break;
				}
			}
		}
	}
	
	return true;
}

bool DeleteAVL(BSTree & T, KeyType key, bool & shorter)
{
	if(!T)
	{
		shorter = false;
		return false;
	}
	else
	{
		if EQ(key,T->data.key)
		{
			BSTree p;
			
			if(!T->lchild)
			{
				p = T;
				T = T->rchild;
				free(p);
				
				shorter = true;
			}
			else if(!T->rchild)
			{
				p = T;
				T = T->lchild;
				free(p);
				
				shorter = true;
			}
			else
			{
				p = T->lchild;
				
				while(p->rchild)
				{
					p = p->rchild;
				}
				
				T->data = p->data;
				
				DeleteAVL(T->lchild, p->data.key, shorter); 
			}
		}
		else if LT(key,T->data.key)
		{
			if(!DeleteAVL(T->lchild, key, shorter))
			{
				return false;
			}
			
			if(shorter)
			{
				switch(T->bf)
				{
					case LH:
						T->bf = EH;
						shorter = true;
						break;
					case EH:
						T->bf = RH;
						shorter = false;
						break;
					case RH:
						if(T->rchild->bf == EH)
						{
							shorter = false;
						}
						else
						{
							shorter = true;
						}
						RightBalance(T);
						break;
				}
			}
		}
		else
		{
			if(!DeleteAVL(T->rchild, key, shorter))
			{
				return false;
			}
			
			if(shorter)
			{
				switch(T->bf)
				{
					case LH:
						if(T->lchild->bf == EH)
						{
							shorter = false;
						}
						else
						{
							shorter = true;
						}
						LeftBalance(T);
						break;
					case EH:
						T->bf = LH;
						shorter = false;
						break;
					case RH:
						T->bf = EH;
						shorter = true;
						break;
				}
			}
		}
		
		return true;
	}
}

void DestroyBST(BSTree & T)
{
	if(T)
	{
		if(T->lchild)
		{
			DestroyBST(T->lchild);
		}
		if(T->rchild)
		{
			DestroyBST(T->rchild);
		}
		free(T);
		T = NULL;
	}
}

void TraverseBST(BSTree T, void(*Visit)(ElemType))
{
	if(T)
	{
		TraverseBST(T->lchild, Visit);
		Visit(T->data);
		TraverseBST(T->rchild, Visit);
	}
}

void PreOrderTraverse(BSTree T, void(*Visit)(ElemType))
{
	if(T)
	{
		Visit(T->data);
		PreOrderTraverse(T->lchild, Visit);
		PreOrderTraverse(T->rchild, Visit);
	}
}

