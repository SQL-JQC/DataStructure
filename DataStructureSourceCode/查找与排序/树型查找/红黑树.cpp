# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

# define N 10

typedef enum Color
{
	RED, BLACK
} Color;

typedef int KeyType;

typedef struct ElemType
{
	KeyType key;
	int order;
} ElemType;

typedef struct RBTNode
{
	ElemType data;
	Color color;
	struct RBTNode * parent;
	struct RBTNode * left;
	struct RBTNode * right;
} RBTNode, * RBTree;

typedef struct RBRoot
{
	RBTree root;
} RBRoot;

# define EQ(a,b) ((a)==(b))
# define LT(a,b) ((a)<(b))
# define LQ(a,b) ((a)<=(b))

RBRoot * CreateRBTree(void);
void RBTreeDestroy(RBTree);
void DestroyRBTree(RBRoot *);
void PreOrder(RBTree);
void PreOrderTraverse(RBRoot *);
void InOrder(RBTree);
void InOrderTraverse(RBRoot *);
RBTree Search(RBTree, KeyType);
bool SearchRBTree(RBRoot *, KeyType);
void L_Rotate(RBRoot *, RBTree);
void R_Rotate(RBRoot *, RBTree);
void RBTreeInsertFixup(RBRoot *, RBTree);
void RBTreeInsert(RBRoot *, RBTree);
RBTree CreateRBTNode(ElemType, RBTree, RBTree, RBTree);
bool InsertRBTree(RBRoot *, ElemType);
void RBTreeDeleteFixup(RBRoot *, RBTree, RBTree);
void RBTreeDelete(RBRoot *, RBTree);
void DeleteRBTree(RBRoot *, KeyType);

int main(void)
{
	RBRoot * RBT;
	ElemType e[N] = {{3, 1}, {2, 2}, {1, 3}, {7, 4}, {5, 5}, {10, 6}, {4, 7}, {9, 8}, {8, 9}, {6, 10}};
	int i;
	
	RBT = CreateRBTree();
	
//	for(i = 0; i < N; ++i)
//	{
//		InsertRBTree(RBT, e[i]);
//	}
//	InOrderTraverse(RBT);
//	printf("\n");
//	PreOrderTraverse(RBT);
//	printf("\n");
	
//	DeleteRBTree(RBT, 3);
//	InOrderTraverse(RBT);
//	printf("\n");
//	PreOrderTraverse(RBT);
//	printf("\n");
	
	DestroyRBTree(RBT);
	
	return 0;
}

RBRoot * CreateRBTree(void)
{
	RBRoot * root = (RBRoot *)malloc(sizeof(RBRoot));
	root->root = NULL;
	
	return root;
}

void RBTreeDestroy(RBTree tree)
{
	if(tree)
	{
		if(tree->left)
		{
			RBTreeDestroy(tree->left);
		}
		if(tree->right)
		{
			RBTreeDestroy(tree->right);
		}
		free(tree);
		tree = NULL;
	}
}

void DestroyRBTree(RBRoot * root)
{
	if(root)
	{
		RBTreeDestroy(root->root);
	}
	
	free(root);
}

void PreOrder(RBTree tree)
{
	if(tree)
	{
		printf("%s(%d, %d) ", tree->color == RED ? "R" : "B", tree->data.key, tree->data.order);
		PreOrder(tree->left);
		PreOrder(tree->right);
	}
}

void PreOrderTraverse(RBRoot * root)
{
	if(root)
	{
		PreOrder(root->root);
	}
}

void InOrder(RBTree tree)
{
	if(tree)
	{
		InOrder(tree->left);
		printf("%s(%d, %d) ", tree->color == RED ? "R" : "B", tree->data.key, tree->data.order);
		InOrder(tree->right);
	}
}

void InOrderTraverse(RBRoot * root)
{
	if(root)
	{
		InOrder(root->root);
	}
}

RBTree Search(RBTree tree, KeyType key)
{
	if(!tree || EQ(key,tree->data.key))
	{
		return tree;
	}
	else if LT(key,tree->data.key)
	{
		return Search(tree->left, key);
	}
	else
	{
		return Search(tree->right, key);
	}
}

bool SearchRBTree(RBRoot * root, KeyType key)
{
	if(root)
	{
		return Search(root->root, key) ? true : false;
	}
}

void L_Rotate(RBRoot * root, RBTree p)
{
	RBTree rc;
	
	rc = p->right;
	
	p->right = rc->left;
	if(rc->left)
	{
		rc->left->parent = p;
	}
	
	rc->parent = p->parent;
	
	if(!p->parent)
	{
		root->root = rc;
	}
	else
	{
		if(p->parent->left == p)
		{
			p->parent->left = rc;
		}
		else
		{
			p->parent->right = rc;
		}
	}
	
	rc->left = p;
	
	p->parent = rc;
}

void R_Rotate(RBRoot * root, RBTree p)
{
	RBTree lc;
	
	lc = p->left;
	
	p->left = lc->right;
	if(lc->right)
	{
		lc->right->parent = p;
	}
	
	lc->parent = p->parent;
	
	if(!p->parent)
	{
		root->root = lc;
	}
	else
	{
		if(p->parent->left == p)
		{
			p->parent->left = lc;
		}
		else
		{
			p->parent->right = lc;
		}
	}
	
	lc->right = p;
	
	p->parent = lc;
}

void RBTreeInsertFixup(RBRoot * root, RBTree node)
{
	RBTree parent;
	RBTree gparent;
	
	while((parent = node->parent) && (parent->color == RED))
	{
		gparent = parent->parent;
		
		if(gparent->left == parent)
		{
			RBTree uncle = gparent->right;
			if(uncle && uncle->color == RED)
			{
				uncle->color = BLACK;
				parent->color = BLACK;
				gparent->color = RED;
				node = gparent;
				
				continue;
			}
			
			if(parent->right == node)
			{
				RBTree temp;
				L_Rotate(root, parent);
				temp = parent;
				parent = node;
				node = temp;
			}
			
			parent->color = BLACK;
			gparent->color = RED;
			R_Rotate(root, gparent);
		}
		else
		{
			RBTree uncle = gparent->left;
			if(uncle && uncle->color == RED)
			{
				uncle->color = BLACK;
				parent->color = BLACK;
				gparent->color = RED;
				node = gparent;
				
				continue;
			}
			
			if(parent->left == node)
			{
				RBTree temp;
				R_Rotate(root, parent);
				temp = parent;
				parent = node;
				node = temp;
			}
			
			parent->color = BLACK;
			gparent->color = RED;
			L_Rotate(root, gparent);
		}
	}
	
	root->root->color = BLACK;
}

void RBTreeInsert(RBRoot * root, RBTree node)
{
	RBTree p = root->root;
	RBTree q = NULL;
	
	while(p)
	{
		q = p;
		if LT(node->data.key,p->data.key)
		{
			p = p->left;
		}
		else
		{
			p = p->right;
		}
	}
	
	node->parent = q;
	
	if(q)
	{
		if LT(node->data.key,q->data.key)
		{
			q->left = node;
		}
		else
		{
			q->right = node;
		}
	}
	else
	{
		root->root = node;
	}
	
	node->color = RED;
	
	RBTreeInsertFixup(root, node);
}

RBTree CreateRBTNode(ElemType e, RBTree parent, RBTree left, RBTree right)
{
	RBTree p;
	
	p = (RBTree)malloc(sizeof(RBTNode));
	if(!p)
	{
		return NULL;
	}
	
	p->data = e;
	p->parent = parent;
	p->left = left;
	p->right = right;
	p->color = BLACK;
	
	return p;
}

bool InsertRBTree(RBRoot * root, ElemType e)
{
	RBTree node;
	
	if(Search(root->root, e.key))
	{
		return false;
	}
	
	node = CreateRBTNode(e, NULL, NULL, NULL);
	if(!node)
	{
		return false;
	}
	
	RBTreeInsert(root, node);
	
	return true;
}

void RBTreeDeleteFixup(RBRoot * root, RBTree node, RBTree parent)
{
	RBTree other;
	
	while((!node || node->color == BLACK) && node != root->root)
	{
		if(parent->left == node)
		{
			other = parent->right;
			if(other->color == RED)
			{
				other->color = BLACK;
				parent->color = RED;
				L_Rotate(root, parent);
				other = parent->right;
			}
			
			if((!other->left || other->left->color == BLACK) && (!other->right || other->right->color == BLACK))
			{
				other->color = RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if(!other->right || other->right->color == BLACK)
				{
					other->left->color = BLACK;
					other->color = RED;
					R_Rotate(root, other);
					other = parent->right;
				}
				
				other->color = parent->color;
				parent->color = BLACK;
				other->right->color = BLACK;
				L_Rotate(root, parent);
				node = root->root;
				
				break;
			}
		}
		else
		{
			other = parent->left;
			if(other->color == RED)
			{
				other->color = BLACK;
				parent->color = RED;
				R_Rotate(root, parent);
				other = parent->left;
			}
			
			if((!other->left || other->left->color == BLACK) && (!other->right || other->right->color == BLACK))
			{
				other->color = RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if(!other->left || other->left->color == BLACK)
				{
					other->right->color = BLACK;
					other->color = RED;
					L_Rotate(root, other);
					other = parent->left;
				}
				
				other->color = parent->color;
				parent->color = BLACK;
				other->left->color = BLACK;
				R_Rotate(root, parent);
				node = root->root;
				
				break;
			}
		}
	}
	
	if(node)
	{
		node->color = BLACK;
	}
}

void RBTreeDelete(RBRoot * root, RBTree node)
{
	RBTree child;
	RBTree parent;
	Color color;
	
	if(node->left && node->right)
	{
		RBTree replace = node;
		
		replace = replace->right;
		while(replace->left)
		{
			replace = replace->left;
		}
		
		if(node->parent)
		{
			if(node->parent->left == node)
			{
				node->parent->left = replace;
			}
			else
			{
				node->parent->right = replace;
			}
		}
		else
		{
			root->root = replace;
		}
		
		child = replace->right;
		parent = replace->parent;
		color = replace->color;
		
		if(parent == node)
		{
			parent = replace;
		}
		else
		{
			if(child)
			{
				child->parent = parent;
			}
			parent->left = child;
			
			replace->right = node->right;
			node->right->parent = replace;
		}
		
		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;
		
		if(color == BLACK)
		{
			RBTreeDeleteFixup(root, child, parent);
		}
		
		free(node);
		
		return;
	}
	
	if(node->left)
	{
		child = node->left;
	}
	else
	{
		child = node->right;
	}
	
	parent = node->parent;
	color = node->color;
	
	if(child)
	{
		child->parent = parent;
	}
	
	if(parent)
	{
		if(parent->left == node)
		{
			parent->left = child;
		}
		else
		{
			parent->right = child;
		}
	}
	else
	{
		root->root = child;
	}
	
	if(color == BLACK)
	{
		RBTreeDeleteFixup(root, child, parent);
	}
	
	free(node);
}

void DeleteRBTree(RBRoot * root, KeyType key)
{
	RBTree node;
	
	node = Search(root->root, key);
	if(node)
	{
		RBTreeDelete(root, node);
	}
}

